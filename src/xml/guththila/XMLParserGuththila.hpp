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

#ifndef __XMLPARSERGUTHTHILA_HPP_INCLUDE__
#define __XMLPARSERGUTHTHILA_HPP_INCLUDE__
#include "../XMLParser.h"
#include "../AxisParseException.h"
#include "../../../src/guththila/XmlPullParser.hpp"

AXIS_CPP_NAMESPACE_USE

class XMLParserGuththila: public XMLParser
{
public:
  XMLParserGuththila ();
  XMLParserGuththila (FileInputStream *fstr);
  ~XMLParserGuththila ();
  int setInputStream (AxisIOStream* pInputStream);
  const XML_Ch* getNS4Prefix (const XML_Ch* pcPrefix);
  int getStatus ();
  const AnyElement* next (bool bIsCharData = false);
  const AnyElement* anyNext ();
  const XML_Ch* getPrefix4NS (const XML_Ch* pcNS);
  const char* peek ();
private:
  XmlPullParser *parser;
  AnyElement element;
  InputStream *stream;
  bool m_pchPeek;
  int isSpace (char *c);
  void setNamespace ();
  void setAttributes ();
  void freeAttributes ();
  void freeElements ();

};
#endif
