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
 */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(_WSDDHANDLER_H__NCLUDED_)
#define _WSDDHANDLER_H__NCLUDED_

#include "GDefine.h"
#include <stdio.h>
#include <string>
#include <map>
#include <list>

using namespace std;

enum AXIS_HANDLER_SCOPE {AH_APPLICATION=1, AH_SESSION, AH_REQUEST};

const AxisChar kw_scope_app[] = "application";
const AxisChar kw_scope_ses[] = "session";
const AxisChar kw_scope_req[] = "request";
/*
 *  @class WSDDHandler
 *  @brief interface for the WSDDHandler class.
 *  @author Susantha Kumara (skumara@virtusa.com)
 */
class WSDDHandler  
{
public:
    const AxisChar* getLibName() const;
    int getLibId() const;
    int getScope() const;
    void setScope(const AxisChar* sScope);
    void setLibName(const AxisChar* sLibName);
    void setLibId(int nLibId);
    void setName(const AxisChar* sName);
    const AxisChar* getParameter(const AxisChar* sKey) const;
    void addParameter(const AxisChar* sKey, const AxisChar* sValue);
    const map<AxisString, AxisString>* getParameterList() const; 
    WSDDHandler();
    virtual ~WSDDHandler();
    void setDescription(const AxisChar* sDescription);
    const AxisChar* getDescription() const;
    virtual int updateWSDD(FILE* wsddfile, int tabcount);
public:
    void printTabs(int count);
    WSDDHandler& operator << (const char* str);
protected:
    int m_nLibId;
    int m_nScope;
    AxisString m_sName;
    AxisString m_sLibName;
    AxisString m_sDescription;
    map<AxisString, AxisString>* m_Params;
    FILE* m_file; /* temporary file handler to wsdd file */
};

typedef list<WSDDHandler*> WSDDHandlerList;

#endif 

