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

/*
 *    @author Dasarath Weerathunga
 *    @author Susantha Kumara (susantha@opensource.lk)
 */

#if !defined(_XMLPULLPARSER_HPP__INCLUDED_)
#define _XMLPULLPARSER_HPP__INCLUDED_

#include <stdlib.h>
#include <string.h>
#include "Buffer.hpp"
#include "Array.hpp"
#include "InputStream.hpp"
#include "XmlPullParserException.hpp"

struct TOKEN
{
	int type;
	char *start, *end;

	enum {
		Unknown, Name, AttValue, Prefix, CharData
	};		

	void relocate(int offset)
	{
		start -= offset;
		end -= offset;
	}

	int length()
	{
		if (end)
			return end-start+1;
		else
			throw new XmlPullParserException();
	}
	
	char *toString()
	{
		int len= length();
		char *p= (char *)malloc(len+1);
		strncpy(p, start, len);
		p[len]= 0;
		return p;
	}

	int compare(const char *s, int n)
	{
		return strncmp(start, s, n);
	}
};

struct NAMESPACE
{
	char *prefix;
	char *uri;
};

struct ATTR
{
	int prefix;
	int name;
	int value;
	int ns;
};

struct DEPTH
{
	int first;
	int count;
	int total;
};

 class XmlPullParser
{
	InputStream *s;
	Buffer<char> *buffer;
	int offset;
	int last;
	int _next;
	int event;
	Array<TOKEN> *token;
	Array<NAMESPACE> *ns;
	Array<ATTR> *attr;
	Array<DEPTH> *depth;
	int name;
	int _ns;
	
	enum {
		S_0, S_1, S_2, S_3, S_4
	} state;

	int read();
	void shift();	
	void relocateTokens(int offset);
	int nextCh(int eof= 0);
	char *lastCh();
	void reset();
	int parse();
	void startToken();
	void endToken(int type);
	int resolve(TOKEN *prefix);
	
	int isS(int c);
	int parseS(int c);
	int parseEq(int c);
	int parseNameToken(int c);
	int parseAttValueToken(int quote);
	int parseAttribute(int c);
	void parseXMLDecl();
	void parseSTagOrEmptyElemTag(int c);
	void parseETag();
	int parseCharData();

public:	
	char* getPrefix4Namespace(const char* pcNs);
	char* getNamespace4Prefix(const char* pcPrefix);
	enum {
		XMLDecl, STag, EmptyElemTag, ETag, Content
	};
	
	XmlPullParser(InputStream *in);
	~XmlPullParser();

	int next();
	
	char *getName();
	char *getPrefix();
	char *getNamespaceUri();

	int getAttributeCount();
	char *getAttributeName(int ii);
	char *getAttributePrefix(int ii);
	char *getAttributeNamespaceUri(int ii);
	char *getAttributeValue(int ii);

	int getDepth();
	int getNamespaceCount(int ii);
	char *getNamespacePrefix(int ii);
	char *getNamespaceUri(int ii);
	
	char *getCharData();
};

#endif
