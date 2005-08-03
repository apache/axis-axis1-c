/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 * @author Dasarath Weerathunga (dasarath@opensource.lk)

 * @author Dinesh Premalal (xydinesh@gmail.com
                            premalal@opensource.lk)
 *
  *@author  Susantha Kumara  ( susantha@opensource.lk )
 */

#include "XmlPullParser.hpp"

void
XmlPullParser::relocateTokens (int offset)
{
  int size = token->count ();
  for (int i = 0; i < size; i++)
    token->get (i)->relocate (offset);
}


void
XmlPullParser::shift ()
{
  memmove (buffer->get (), buffer->get () + offset, _next - offset);
  _next -= offset;
  last -= offset;
  offset = 0;
}


int
XmlPullParser::read ()
{
  if (_next == buffer->getSize ())
    {
      if (offset > 0)
	{
	  relocateTokens (offset);
	  shift ();
	}
      else
	{
	  char *p = buffer->get ();
	  buffer->grow ();
	  relocateTokens (p - buffer->get ());
	}
    }
  int c = s->read (buffer->get (), _next, buffer->getSize () - _next);
  last += c;
  return !c;
}


/*! check with BOM
   *This may or may not be presant with utf8 documents 
   *But UTF-16 document must have BOM 0xff 0xfe in any order, 
   * for LE = 0xff 0xfe, 
   * for BE = 0xfe 0xff,  
   * for UTF-8 = 0xef 0xbb 0xbf ( not necessary) */

int
XmlPullParser::isUtf8 ()
{
  UTF8_char utf[3] = { 0, 0, 0 };
  for (int i = 0; i < 3; i++)
    utf[i] = (UTF8_char) buffer->get ()[_next++];

  
  if (0xef == utf[0] && 0xbb == utf[1] && 0xbf == utf[2])
    {
      unicodeState = None;
      return _next;
    }
  else
    return _next = 0;
}


/*! check for BOM */
int
XmlPullParser::isUtf16 ()
{
  if (_next == 0)
    {
      UTF8_char utf[2];
      int i;
      for (i = 0; i < 2; i++)
	utf[i] = (UTF8_char) buffer->get ()[_next++];
      if (0xff == utf[0] && 0xfe == utf[1])
	return LE;
      else if (0xfe == utf[0] && 0xff == utf[1])
	return BE;
      else
	{
	  _next = 0;
	  return None;
	}
    }
  else
    return None;
}


/*!since we are interested in special charactes such as "<",
 *  "/",">","?","!",""",... nextCh() method suppose to return those 
 * values. Those values are retrieved form UTF-16 characters
 * ,Here we need not to do a convertion. Because those values are
 * < 128 */

int
XmlPullParser::fromUtf16 (int eof)
{
  int c = buffer->get ()[_next++];
  
  if (_next > last && read ())
    if (eof)
      {
	term = 1;
	return -1;
      }
    else
      throw new XmlPullParserException ();

  /*UTF16_char d = *((UTF16_char *) & buffer->get ()[_next]);
  if (!d)
  {
  term = 1;
  return -1;
  }*/
  while (!c)
    c = buffer->get ()[_next++];
  return c;
}


int
XmlPullParser::nextCh (int eof)
{
  if (_next > last && read ())
    if (eof)
      {
	term = 1;
	return -1;
      }
    else
      throw new XmlPullParserException ();

  if (_next == 0)
    {
      if (isUtf8 ());
      else
	(unicodeState = isUtf16 ());
    }

  if (unicodeState == None)
    return buffer->get ()[_next++];
  else
      return fromUtf16 (eof);
}


char *
XmlPullParser::lastCh ()
{
  int i = 1;
  char c = buffer->get ()[_next - 1];

  /*! If term has set to true then that is a buffer termination */
  if (term)
    return buffer->get () + _next - 1;
  else
    {
      while (!c)
	c = buffer->get ()[_next - (++i)];
      return buffer->get () + _next - i;
    }
}


void
XmlPullParser::reset (int del)
{
  offset = _next;
  name = NULL;
  prefix = NULL;
  namesp = NULL;
  term = 0;
  token->trunc (0);
  attr->trunc (0);
  if (!del)
    {
      if (ETag == event || EmptyElemTag == event)
	closeElement ();
    }
}


void
XmlPullParser::openToken ()
{
  token_t *t = token->append ();
  t->type = token_t::Unknown;
  t->start = lastCh ();
}


void
XmlPullParser::closeToken (int type)
{
  token_t *t = token->last ();
  t->type = type;
  t->end = lastCh () - 1;
}


XmlPullParser::XmlPullParser (InputStream * s)
{
  this->s = s;
  state = S_1;
  offset = 0;
  last = -1;
  _next = 0;
  buffer = new Buffer < char >(1024);
  token = new Array < token_t > (64);
  namespa = new Array < namespace_t > (64);
  depth = new Array < depth_t > (16);
  attr = new Array < attr_t > (64);
}


XmlPullParser::~XmlPullParser ()
{
  reset (-1);
  delete buffer;
  delete token;
  delete namespa;
  delete depth;
  delete attr;
}


int
XmlPullParser::isS (int c)
{
  return 0x9 == c || 0xA == c || 0xD == c || 0x20 == c;
}

int
XmlPullParser::parseS (int c)
{
  while (isS (c))
    c = nextCh ();
  return c;
}


int
XmlPullParser::parseEq (int c)
{
  if ('=' == parseS (c))
    return parseS (nextCh ());
  else
    throw new XmlPullParserException ();
}


int
XmlPullParser::parseNameToken (int c)
{
  openToken ();
  while (!(isS (c) || '/' == c || '?' == c || '=' == c || '>' == c))
    {
      if (':' == c)
	{
	  closeToken (token_t::Prefix);
	  c = nextCh ();
	  openToken ();
	}
      else
	c = nextCh ();
    }
  closeToken (token_t::Name);
  return c;
}


int
XmlPullParser::parseAttValueToken (int quote)
{
  if ('\'' == quote || '"' == quote)
    {
      int c = nextCh ();
      openToken ();
      while ('&' != c && '<' != c)
	{
	  if (c == quote)
	    {
	      closeToken (token_t::AttValue);
	      return nextCh ();
	    }
	  c = nextCh ();
	}
    }
  throw new XmlPullParserException ();
}


int
XmlPullParser::parseAttribute (int c)
{
  c = parseEq (parseNameToken (c));
  c = parseAttValueToken (c);
  return parseS (c);
}


void
XmlPullParser::parseXMLDecl ()
{
  if (nextCh () == 'x' && nextCh () == 'm' && nextCh () == 'l')
    {
      int c = parseAttribute (parseS (nextCh ()));
      if (c == 'e')
	c = parseAttribute (c);
      if (c == 's')
	c = parseAttribute (c);
      if (c == '?' && nextCh () == '>')
	{
	  event = XMLDecl;
	  return;
	}
    }
  throw new XmlPullParserException ();
}


void
XmlPullParser::parseSTagOrEmptyElemTag (int c)
{
  c = parseS (parseNameToken (c));
  event = STag;
  for (;;)
    {
      if (c == '/')
	{
	  event = EmptyElemTag;
	  if (nextCh () == '>')
	    return;
	  else
	    throw new XmlPullParserException ();
	}
      else if (c == '>')
	return;
      else
	c = parseAttribute (c);
    }
}


void
XmlPullParser::parseETag ()
{
  if (parseS (parseNameToken (nextCh ())) == '>')
    event = ETag;
  else
    throw new XmlPullParserException ();
}


int
XmlPullParser::parseCharData ()
{
  int c;
  event = Content;
  openToken ();
  do
    {
      c = nextCh (-1);
      if (-1 == c)
	{
	  closeToken (token_t::CharData);
	  return 0;
	}
    }
  while ('<' != c);
  closeToken (token_t::CharData);
  return c;
}


int
XmlPullParser::tokenize ()
{
  do
    {
      int c = nextCh (-1);
      if (-1 == c)
	return -1;
      switch (state)
	{
	case S_1:
	  if ('<' == c)
	    state = S_2;
	  else
	    state = S_0;
	  break;

	case S_2:
	  if ('?' == c)
	    parseXMLDecl ();
	  else
	    parseSTagOrEmptyElemTag (c);
	  state = S_3;
	  break;

	case S_3:
	  if ('<' == c)
	    state = S_4;
	  else
	    {
	      c = parseCharData ();
	      if ('<' == c)
		{
		  state = S_4;
		  return event;
		}
	      else if ('\0' == c)
		state = S_3;
	      else
		state = S_0;
	    }
	  break;

	case S_4:
	  if ('/' == c)
	    {
	      parseETag ();
	      state = S_3;
	    }
	  else if ('!' == c)
	    state = S_0;
	  else if ('?' == c)
	    state = S_0;
	  else
	    {
	      parseSTagOrEmptyElemTag (c);
	      state = S_3;
	    }
	}
      if (state == S_0)
	throw new XmlPullParserException ();
    }
  while (state != S_3);
  return event;
}


int
XmlPullParser::addNamespace (token_t * uri)
{
  namespace_t *r = namespa->append ();
  r->prefix = NULL;
  r->length = 0;
  r->uri = uri->toString (unicodeState);
  r->lengthUri = strlen(r->uri);
}


int
XmlPullParser::addNamespace (token_t * prefix, token_t * uri)
{
  namespace_t *r = namespa->append ();
  r->prefix = prefix->toString (unicodeState);
  r->length = strlen (r->prefix);
  r->uri = uri->toString (unicodeState);
  r->lengthUri = strlen(r->uri);
}


int
XmlPullParser::addAttribute (token_t * prefix, token_t * name,
			     token_t * value)
{
  attr_t *r = attr->append ();
  r->prefix = prefix;
  r->name = name;
  r->value = value;
  r->namesp = NULL;
}


void
XmlPullParser::openElement ()
{
  if (depth->count ())
    {
      depth_t *l = depth->last ();
      depth_t *m = depth->append ();
      m->first = l->first + l->count;
      m->total = namespa->count ();
      m->count = m->total - l->total;
    }
  else
    {
      depth_t *m = depth->append ();
      m->first = 0;
      m->total = namespa->count ();
      m->count = m->total;
    }
}


void
XmlPullParser::closeElement ()
{
  depth_t *d = depth->last ();
  if (d->count)
    {
      namespace_t *p = namespa->get (d->first);
      for (int i = 0; i < d->count; i++, p++)
	{
	  if (p->prefix)
	    free (p->prefix);
	  if(p->uri)
	    free(p->uri);
	}
      namespa->trunc (d->first);
    }
  depth->chip ();
}


int
XmlPullParser::next ()
{
  token_t *p;
  reset ();
  switch (tokenize ())
    {
    case -1:
      return -1;

    case XMLDecl:
    case STag:
    case EmptyElemTag:
      p = token->last ();
      while (p->isOfType (token_t::AttValue))
	{
	  token_t *value = p--;
	  token_t *name = p--;
	  if (p->isOfType (token_t::Prefix))
	    {
	      if (!p->compare ("xmlns", 5))
		addNamespace (name, value);
	      else
		addAttribute (p, name, value);
	      p--;
	    }
	  else if (!name->compare ("xmlns", 5))
	    addNamespace (value);
	  else
	    addAttribute (NULL, name, value);
	}
      openElement ();

    case ETag:
      p = token->get ();
      if (p->isOfType (token_t::Prefix))
	prefix = p++;
      name = p;

    case Content:
    defualt:
      return event;
    }
}


namespace_t *
XmlPullParser::getNamespace (token_t * prefix)
{
  namespace_t *p = namespa->last (), *q = namespa->get ();
  while (1)
    {
      if (prefix == NULL)
	{
	  if (p->prefix == NULL)
	    return p;
	}
      else
	{
	  if (p->prefix && !prefix->compare (p->prefix, p->length))
	    return p;
	}
      if (p == q)
	throw new XmlPullParserException ();
      p--;
    }
}


char *
XmlPullParser::getName ()
{
  if (name)
    return name->toString (unicodeState);
  throw new XmlPullParserException ();
}
 

char *
XmlPullParser::getPrefix ()
{
  if (prefix)
    return prefix->toString (unicodeState);
  return NULL;
}


char*
XmlPullParser::getNamespaceUri ()
{
  if (!namesp)
    namesp = getNamespace (prefix);
  return strndup (namesp->uri, namesp->lengthUri);
}

char*
XmlPullParser::getValue ()
{
  return token->get ()->toString (unicodeState);
}


int
XmlPullParser::getDepth ()
{
  return depth->count ();
}


int
XmlPullParser::getAttributeCount ()
{
  return attr->count ();
}


char*
XmlPullParser::getAttributeName (int i)
{
  return attr->get (i)->name->toString (unicodeState);
}


char*
XmlPullParser::getAttributeValue (int i)
{
  return attr->get (i)->value->toString (unicodeState);
}


char*
XmlPullParser::getAttributePrefix (int i)
{
  attr_t *p = attr->get (i);
  if (p->prefix)
    return p->prefix->toString (unicodeState);
  return NULL;
}


char*
XmlPullParser::getAttributeNamespaceUri (int i)
{
  attr_t *p = attr->get (i);
  if (!p->namesp)
    p->namesp = getNamespace (p->prefix);
  return strndup(p->namesp->uri, p->namesp->lengthUri);
}


int
XmlPullParser::getNamespaceCount (int i)
{
  return depth->get (i - 1)->total;
}


char *
XmlPullParser::getNamespacePrefix (int i)
{
  namespace_t *p = namespa->get (i);
  if (p->prefix)
   	return strndup(p->prefix, p->length);
  return NULL;
}


char *
XmlPullParser::getNamespaceUri (int i)
{
  return strndup(namespa->get(i)->uri, namespa->get(i)->lengthUri);
}

char *
XmlPullParser::getNamespaceForPrefix (char *prefix)
{
  namespace_t *p = namespa->last (), *q = namespa->get ();
  while (1)
    {
      if (prefix == NULL)
	{
	  if (p->prefix == NULL)
	    return strndup (p->uri, p->lengthUri);
	}
      else 
	{
	  if (p->prefix && !strncmp (p->prefix, prefix, p->length))
	    return strndup (p->uri, p->lengthUri);
	}
      if (p == q)
	throw new XmlPullParserException ();
      p--;
    }
}

char *
XmlPullParser::getPrefixForNamespace (char *ns)
{
  namespace_t *p = namespa->last (), *q = namespa->get ();
  while (1)
    {
      if (ns == NULL)
	throw new XmlPullParserException ();
      /* No Namespace exsist with NULL URI*/
      else 
	{
	  if (p->uri && !strncmp (p->uri, ns, p->lengthUri))
	    return strndup (p->prefix, p->length);
	}
      if (p == q)
	throw new XmlPullParserException ();
      p--;
    }
}


      
