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

#if !defined(AFX_HTTPKEYWORDS_H__INCLUDED_)
#define AFX_HTTPKEYWORDS_H__INCLUDED_

#include <string>

using namespace std;

enum HTTP_MAP_KEYWORDS
{
    HMK_URI,              /* For HTTP URI */
    HMK_METHOD,           /* For HTTP method (eg: GET, POST etc) */
    HMK_VERSION,          /* For HTTP Version */
    HMK_HOST,             /* For Host name */
    HMK_CONTENT_TYPE,     /* For Content Type */
    HMK_CONTENT_LENGTH,   /* For Content Length */
    HMK_LAST              /* For Representing the last item of the enumeration */
};

enum HTTP_KEYWORDS
{
    HK_POST,                  /* For HTTP POST */
    HK_GET,                   /* For HTTP GET */
    HK_HTTP_1_1,              /* For HTTP 1.1 */
    HK_HTTP_UNKNOWN_VERSION,  /* For unknown versions of HTTP */

    HK_LAST                   /* For Representing the last item of the 
                               * enumeration 
			       */
};

#endif 
