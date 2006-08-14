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
 *  @author Dinesh Premalal (xydinesh@gmail.com
 *			     premalal@opensource.lk)
 *
 */

#include "XMLParserGuththila.hpp"
#include "AxisInputStream.hpp"

XMLParserGuththila::XMLParserGuththila ()
{
  parser = 0;
  stream = 0;
  element.m_pchNamespace = 0;
  element.m_pchNameOrValue = 0;
  element.m_pchAttributes[0] = 0;
  
  // This is just to set it up. Not sure if this 
  // parser is functional - if so, following needs
  // to be set correctly.
  m_bCanParseMore = true;
}


/* This constructor used only for Testing purpose*/
XMLParserGuththila::XMLParserGuththila (FileInputStream *fstr)
{
  parser = new XmlPullParser (fstr);
  stream = 0;
  element.m_pchNamespace = 0;
  element.m_pchNameOrValue = 0;
  element.m_pchAttributes[0] = 0;
}


XMLParserGuththila::~XMLParserGuththila ()
{
  if (parser)
    delete parser;
  if (stream)
    delete stream;
}


int
XMLParserGuththila::setInputStream (AxisIOStream* pInputStream)
{
  try{
    if (stream)
      delete stream;
    stream = new AxisInputStream (pInputStream);
    
    if (parser)
      delete parser;
    
    parser = new XmlPullParser(stream);
    return AXIS_SUCCESS;
  }
  catch (XmlPullParserException* e)
    {
      delete e;
      throw new AxisParseException (245, "set InputStream");
    }
}


const XML_Ch*
XMLParserGuththila::getNS4Prefix (const XML_Ch* pcPrefix)
{
  return parser->getNamespaceForPrefix ((char *)pcPrefix);
}


const XML_Ch*
XMLParserGuththila::getPrefix4NS (const XML_Ch* pcNS)
{
  return parser->getPrefixForNamespace ((char *)pcNS);
}


int 
XMLParserGuththila::getStatus ()
{
  return 0;
}


void
XMLParserGuththila::setNamespace ()
{
  int d, i, j;
  char *x = parser->getPrefix ();
  if (!x)
    {
      d = parser->getDepth ();
      if (d > 0)
	{
	  i = parser->getNamespaceCount (d);
	  if (d > 1)
	    j = parser->getNamespaceCount (d-1);
	  else 
	j = 0;
	  for (; j < i; j++)
	    element.m_pchNamespace = parser->getNamespaceUri (j);
	}
    }
  else
    element.m_pchNamespace = parser->getNamespaceForPrefix (x);
}


void
XMLParserGuththila::setAttributes ()
{
  int count;
  count = parser->getAttributeCount ();
  element.m_pchAttributes[count*3];
  for (int ix = 0; ix<count; ix++)
    {
      int iAttx = ix*3;
      element.m_pchAttributes[iAttx] = parser->getAttributeName (ix);
      element.m_pchAttributes[iAttx+1] = parser->getAttributePrefix (ix);
      if (element.m_pchAttributes[iAttx+1])
	element.m_pchAttributes[iAttx+1] = parser->getNamespaceForPrefix ((char*)element.m_pchAttributes[iAttx+1]);
      element.m_pchAttributes[iAttx+2] = parser->getAttributeValue (ix);
    }
}


void 
XMLParserGuththila::freeAttributes ()
{
  for (int ix = 0; element.m_pchAttributes[ix]; ix +=3)
    {
      element.m_pchAttributes[ix] = NULL;
      if (element.m_pchAttributes[ix+1])
	element.m_pchAttributes[ix+1] = NULL;
      if (element.m_pchAttributes[ix+2])
	element.m_pchAttributes[ix+2] = NULL;
    }
}


void
XMLParserGuththila::freeElements ()
{
  if (element.m_pchNameOrValue)
    element.m_pchNameOrValue = NULL;
  if (element.m_pchNamespace)
    element.m_pchNamespace = NULL;
  freeAttributes ();
}

int 
XMLParserGuththila::isSpace (char *c)
{
  char *ic;
  ic = c;
  if (ic[0] == 0xa)
    return 1;
  else
    return 0;
}


const AnyElement*
XMLParserGuththila::next (bool isCharData)
{
  int nValue;
  freeElements ();
  try 
    {
      while (true)
	{
	start:
	  if ((nValue = parser->next ()) != -1)
	    {
	      switch (nValue)
		{
		case XmlPullParser::XMLDecl:
		  goto start;
		case XmlPullParser::STag:
		  element.m_type = START_ELEMENT;
		  element.m_type2 = START_ELEMENT;
		  element.m_pchNameOrValue = parser->getName ();
		  setNamespace ();
		  setAttributes ();
		  break;
		case XmlPullParser::EmptyElemTag:
		  element.m_type = START_ELEMENT;
		  element.m_type2 = END_ELEMENT;
		  element.m_pchNameOrValue = parser->getName ();
		  setNamespace ();
		  setAttributes ();
		  break;
		case XmlPullParser::ETag:
		  element.m_type = END_ELEMENT;
		  element.m_type2 = END_ELEMENT;
		  element.m_pchNameOrValue = parser->getName ();
		  setNamespace ();
		  break;
		case XmlPullParser::Content:
		  if (isCharData)
		    {
		      element.m_type = CHARACTER_ELEMENT;
		      element.m_type2 = CHARACTER_ELEMENT;
		      element.m_pchNameOrValue = parser->getValue ();
		    }
		  else
		    goto start;
		  
		  break;
		default:;
		}
	    }
	  return &element;
	}
    }
  catch (XmlPullParserException *e)
    {
      delete e;
      throw new AxisParseException (245, "next Method XMLParserGuththila");
    }
}

const AnyElement*
XMLParserGuththila::anyNext ()
{
  int nValue;
  freeElements ();
  try 
    {
      while (true)
	{
	  if ((nValue = parser->next ()) != -1)
	    {
	      switch (nValue)
		{
		case XmlPullParser::STag:
		  element.m_type = START_ELEMENT;
		  element.m_type2 = START_ELEMENT;
		  element.m_pchNameOrValue = parser->getName ();
		  setNamespace ();
		  setAttributes ();
		  break;
		case XmlPullParser::EmptyElemTag:
		  element.m_type = START_ELEMENT;
		  element.m_type2 = END_ELEMENT;
		  element.m_pchNameOrValue = parser->getName ();
		  setNamespace ();
		  setAttributes ();
		  break;
		case XmlPullParser::ETag:
		  element.m_type = END_ELEMENT;
		  element.m_type2 = END_ELEMENT;
		  element.m_pchNameOrValue = parser->getName ();
		  setNamespace ();
		  break;
		case XmlPullParser::Content:
		  element.m_type = CHARACTER_ELEMENT;
		  element.m_type2 = CHARACTER_ELEMENT;
		  element.m_pchNameOrValue = parser->getValue ();
		  break;
		default:;
		}
	    }
	  return &element;
	}
    }
  catch (XmlPullParserException *e)
    {
      delete e;
      throw new AxisParseException (245, "any next method XMLParserGuththila");
    }
}

const char*
XMLParserGuththila::peek ()
{
  int peekValue;
  const char* peekName;
  peekValue = parser->next ();
  while ( peekValue == XmlPullParser::Content || peekValue == XmlPullParser::XMLDecl)
      peekValue = parser->next ();
    peekName = parser->getName ();
    m_pchPeek = true;
    return peekName;
}
