/***************************************************************************
 *
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
 ***************************************************************************/
#include "XmlPullParser.hpp"
 
 void XmlPullParser::relocateTokens(int offset)
{
	int size= token->count();
	for (int ii= 0; ii < size; ii++)
		(*token)[ii].relocate(offset);	
}

void XmlPullParser::shift()
{
	memmove(buffer->get(), buffer->get()+offset, _next-offset);
	_next -= offset;
	last -= offset;
	offset= 0;
}

int XmlPullParser::read()
{
	if (_next == buffer->getSize()) {
		if (offset > 0) {
			relocateTokens(offset);
			shift();
		}
		else {
			char *p= buffer->get();
			buffer->grow();
			relocateTokens(p - buffer->get());
		}
	}
	int c= s->read(buffer->get(), _next, buffer->getSize()-_next);
	last += c;
	return !c;
}

int XmlPullParser::nextCh(int eof)
{
	if (_next > last && read())
		if (eof)
			return -1;
		else
			throw new XmlPullParserException();
	//Update next 
	// FIXME:
	//printf("%c", buffer->get()[_next]);
	
	return buffer->get()[_next++];
	//update next depending on the encoding type
}
 
char *XmlPullParser::lastCh()
{
	return buffer->get()+_next-1;
}

void XmlPullParser::reset()
{
	offset= _next;
	token->trunc(0);
	attr->trunc(0);
	if (event == ETag || event == EmptyElemTag) {
		DEPTH &l= depth->getLast();
		if (l.count) {
			NAMESPACE *p= ns->get()+l.first;
			for (int ii= l.first; ii < l.total; ii++, p++) {
				free(p->prefix);
				free(p->uri);
			}
			ns->trunc(l.first);
		}
		depth->chip();
//		printf("\ndepth=%d\n", depth->count());
	}
	name= -1;
	_ns= -1;
}

void XmlPullParser::startToken()
{
	TOKEN &t= token->append();
	t.type= TOKEN::Unknown;
	t.start= lastCh();	
}
	
void XmlPullParser::endToken(int type)
{
	TOKEN &t= token->getLast();
	t.type= type;
	t.end= lastCh()-1;
}


XmlPullParser::XmlPullParser(InputStream *s)
{
	this->s= s;
	state= S_1;
	offset= 0;
	last= -1;
	_next= 0;
	buffer= new Buffer<char>(1024);
	token= new Array<TOKEN>(64);
	ns= new Array<NAMESPACE>(64);
	depth= new Array<DEPTH>(16);
	attr= new Array<ATTR>(64);
}

XmlPullParser::~XmlPullParser()
{
	delete buffer;
	delete token;
	delete ns;
	delete depth;
	delete attr;
}

int XmlPullParser::isS(int c)
{
	return 0x9 == c || 0xA == c || 0xD == c || 0x20 == c;
}


int XmlPullParser::parseS(int c)
{
	while (isS(c))
		c= nextCh();
	return c;
}

int XmlPullParser::parseEq(int c)
{
	if ('=' == parseS(c))
		return parseS(nextCh());
	else
		throw new XmlPullParserException();
}

int XmlPullParser::parseNameToken(int c)
{
	startToken();
	while (!(isS(c) || '/' == c || '?' == c || '=' == c || '>' == c)) {
		if (':' == c) {
			endToken(TOKEN::Prefix);
			c= nextCh();
			startToken();
		}
		else
			c= nextCh();
	}
	endToken(TOKEN::Name);
	return c;
}

int XmlPullParser::parseAttValueToken(int quote)
{
	if ('\'' == quote || '"' == quote) {
		int c= nextCh();
		startToken();
		while ('&' != c && '<' != c) {
			if (c == quote) {
				endToken(TOKEN::AttValue);
				return nextCh();
			}		
			c= nextCh();
		}
	}
	throw new XmlPullParserException();
}

int XmlPullParser::parseAttribute(int c)
{
	c= parseEq(parseNameToken(c));
	c= parseAttValueToken(c);
	return parseS(c);
}

void XmlPullParser::parseXMLDecl()
{
	if (nextCh() == 'x' &&
		nextCh() == 'm' &&
		nextCh() == 'l') {
		int c= parseAttribute(parseS(nextCh()));
		if (c == 'e')
			c= parseAttribute(c);
		if (c == 's')
			c= parseAttribute(c);
		if (c == '?' && nextCh() == '>') {
			event= XMLDecl;
			return;
		}
	}
	throw new XmlPullParserException();
}

void XmlPullParser::parseSTagOrEmptyElemTag(int c)
{
	c= parseS(parseNameToken(c));
	event= STag;
	for (;;) {
		if (c == '/') {
			event= EmptyElemTag;
			if (nextCh() == '>')
				return;
			else
				throw new XmlPullParserException();
		}
		else
			if (c == '>')
				return;
			else
				c= parseAttribute(c);
	}
}

void XmlPullParser::parseETag()
{
	if (parseS(parseNameToken(nextCh())) == '>')
		event= ETag;
	else
		throw new XmlPullParserException();
}

int XmlPullParser::parseCharData()
{
	int c;
	event= Content;
	startToken();
	do {
		c= nextCh(-1);
		if (-1 == c) {
			endToken(TOKEN::CharData);
			return 0;
		}
	} while ('<' != c);
	endToken(TOKEN::CharData);
	return c;
}


int XmlPullParser::parse()
{
	do {
		int c= nextCh(-1);
		if (-1 == c)
			return -1;
		switch (state) {
		case S_1:
			if ('<' == c)
				state= S_2;
			else
				state= S_0;
			break;

		case S_2:
			if ('?' == c)
				parseXMLDecl();
			else
				parseSTagOrEmptyElemTag(c);
			state= S_3;
			break;

		case S_3:
			if ('<' == c)
				state= S_4;
			else {
				c= parseCharData();
				if ('<' == c) {
					state= S_4;
					return event;
				}
				else if ('\0' == c)
					state= S_3;
				else
					state= S_0;
			}
			break;

		case S_4:
			if ('/' == c) {
				parseETag();
				state= S_3;
			}
			else if ('!' == c)
				state= S_0;
			else if ('?' == c)
				state= S_0;
			else {
				parseSTagOrEmptyElemTag(c);
				state= S_3;
			}
		}
		if (state == S_0)
			throw new XmlPullParserException();
	} while (state != S_3);
	return event;
}


int XmlPullParser::next()
{
	reset();
	if (parse() != -1) {
		if (STag == event || EmptyElemTag == event || ETag == event) {
			TOKEN *p= token->get();
			int ii= 0;
			if (p->type == TOKEN::Prefix) {
				_ns= 0xffff;
				name= 1;
				p += 2;
				ii += 2;
			}
			else {
				_ns = -1;
				name= 0;
				p++;
				ii++;
			}
			if (ETag == event)
				return event;
			int count= token->count();
			while (ii < count) {
				if (p->type == TOKEN::Prefix) {
					if (!p->compare("xmlns", 5)) {
						NAMESPACE &n= ns->append();
						p++;
						n.prefix= p->toString();
						p++;
						n.uri= p->toString();
						p++;
						ii += 3;					
					}
					else {
						ATTR &a= attr->append();
						a.prefix= ii++;
						a.name= ii++;
						a.value= ii++;
						a.ns= -1;
						p += 3;
					}					
				}
				else {
					if (!p->compare("xmlns", 5)) {
						NAMESPACE &n= ns->append();
						n.prefix= NULL;
						p++;
						n.uri= p->toString();
						p++;
						ii += 2;					
					}
					else {
						ATTR &a= attr->append();
						a.prefix= -1;
						a.name= ii++;
						a.value= ii++;
						a.ns= -1;						
						p += 2;
					}
				}
			}
			if (depth->count()) {
				DEPTH &l= depth->getLast();			
				DEPTH &m= depth->append();
				m.first= l.first+l.count;
				m.total= ns->count();
				m.count= m.total-l.total;			
			}
			else {
				DEPTH &m= depth->append();
				m.first= 0;
				m.total= ns->count();
				m.count= m.total;			
			}
			_ns= resolve(_ns == -1 ? NULL : token->get());
		}
		return event;
	}
	return -1;
}

int XmlPullParser::getAttributeCount()
{
	if (STag != event && EmptyElemTag != event)
		throw new XmlPullParserException();
	return attr->count();	
}

char *XmlPullParser::getAttributePrefix(int ii)
{
	if (STag != event && EmptyElemTag != event)
		throw new XmlPullParserException();
	ii= (*attr)[ii].prefix;
	if (ii == -1)
		return NULL;
	return (*token)[ii].toString();	
}

char *XmlPullParser::getAttributeName(int ii)
{
	if (STag != event && EmptyElemTag != event)
		throw new XmlPullParserException();
	ii= (*attr)[ii].name;
	if (ii == -1)
		return NULL;
	return (*token)[ii].toString();	
}

char *XmlPullParser::getAttributeValue(int ii)
{
	if (STag != event && EmptyElemTag != event)
		throw new XmlPullParserException();
	ii= (*attr)[ii].value;
	if (ii == -1)
		return NULL;
	return (*token)[ii].toString();	
}

char *XmlPullParser::getAttributeNamespaceUri(int ii)
{
	if (STag != event && EmptyElemTag != event)
		throw new XmlPullParserException();
	ATTR &t= (*attr)[ii];
	if (t.ns == -1)
		t.ns= resolve(t.prefix == -1 ? NULL : token->get()+t.prefix);
	return strdup((*ns)[t.ns].uri);
}


int XmlPullParser::resolve(TOKEN *prefix)
{
	int ii= ns->count()-1;
	NAMESPACE *p= &ns->getLast();
	while (ii >= 0) {
		if (prefix == NULL) {
			if (p->prefix == NULL)
				return ii;
		}
		else
			if (p->prefix && !prefix->compare(p->prefix, strlen(p->prefix)))
				return ii;
		ii--;
		p--;
	}
	throw new XmlPullParserException();
}


int XmlPullParser::getDepth()
{
	return depth->count();
}

int XmlPullParser::getNamespaceCount(int ii)
{
	if (ii > getDepth())
		throw new XmlPullParserException();
	else
		return (*depth)[ii-1].total;
}

char *XmlPullParser::getNamespacePrefix(int ii)
{
	if (ii > ns->count())
		throw new XmlPullParserException();
	else {
		char *p= (*ns)[ii].prefix;
		return p == NULL ? NULL : strdup(p); 
	}
}
	
char *XmlPullParser::getNamespaceUri(int ii)
{
	if (ii > ns->count())
		throw new XmlPullParserException();
	else {
		char *p= (*ns)[ii].uri;
		return p == NULL ? NULL : strdup(p); 
	}
}

char *XmlPullParser::getName()
{
	return (*token)[name].toString();
}

char *XmlPullParser::getCharData()
{
	return (*token)[0].toString();
}

char *XmlPullParser::getNamespaceUri()
{
	if (_ns == -1)
		_ns= resolve(NULL);
	else
		if (_ns == 0xffff)
			_ns= resolve(token->get());
	return strdup((*ns)[_ns].uri);
}

