/* -*- C++ -*- */
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
 *
 *
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 *
 */

#if !defined(AFX_SERVERHELPER_H__INCLUDED_)
#define AFX_SERVERHELPER_H__INCLUDED_

#include <string>
#include <map>

#include "HTTP_KeyWords.h"
#include <axis/server/Packet.h>

using namespace std;

enum CONTENT_TYPE
{
    HTTP_KEYWORD_TYPE,
    STRING_TYPE
};

union uHttpMapContent /* This is used to store both the HTTP_KEYWORDS enumerated
                       * contents and strings 
		       */
{
    HTTP_KEYWORDS eHTTP_KEYWORD; //for HTTP_KEYWORDS enumerated contents
    const char* msValue;         //for string content
};

struct HTTP_MAP_TYPE
{
    CONTENT_TYPE eCONTENT_TYPE;
    uHttpMapContent* objuHttpMapContent;
};

struct HttpHeaders
{
    char* header_name;
    char* header_value;
};

int getSeperatedHTTPParts (string sClientReqStream, string &sHTTPHeaders,
    string & sHTTPBody, map < HTTP_MAP_KEYWORDS, 
    HTTP_MAP_TYPE* > *map_HTTP_Headers, Ax_soapstream* str,
    HttpHeaders* pHttpHeaders, int iHeaderArraySize, int* piHeaderCount);

int initializeHeaderMap (const string & HeaderLine, map < HTTP_MAP_KEYWORDS,
    HTTP_MAP_TYPE* > *map_HTTP_Headers, Ax_soapstream* str, 
    HttpHeaders* pHttpHeaders, int* piHeaderCount);

int getHttpHeader (HTTP_MAP_KEYWORDS eKeyWord, map < HTTP_MAP_KEYWORDS,
    HTTP_MAP_TYPE* > *map_HTTP_Headers, HTTP_MAP_TYPE* objMapContent);

#endif 
