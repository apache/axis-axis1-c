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

#if !defined(_WSDDKEYWORDS_H____OF_AXIS_INCLUDED_)
#define _WSDDKEYWORDS_H____OF_AXIS_INCLUDED_

#include <axis/server/GDefine.hpp>

/* keywords used in the wsdd file */
extern const AxisXMLCh* kw_depl;
extern const AxisXMLCh* kw_undepl;    /* to represent the 'undeployment' tag */
extern const AxisXMLCh* kw_srv;
extern const AxisXMLCh* kw_glconf;
extern const AxisXMLCh* kw_param; 
extern const AxisXMLCh* kw_hdl;
extern const AxisXMLCh* kw_chain;
extern const AxisXMLCh* kw_ns;
extern const AxisXMLCh* kw_prv;
extern const AxisXMLCh* kw_cn; /* must be changed to libname or so */
extern const AxisXMLCh* kw_am;
extern const AxisXMLCh* kw_ar;
extern const AxisXMLCh* kw_rqf;
extern const AxisXMLCh* kw_rsf;
extern const AxisXMLCh* kw_tr;
extern const AxisXMLCh* kw_name;
extern const AxisXMLCh* kw_value;
extern const AxisXMLCh* kw_type; /* what about this ? change to libname ? */
extern const AxisXMLCh* kw_scope;
extern const AxisXMLCh* kw_http;
extern const AxisXMLCh* kw_smtp;
extern const AxisXMLCh* kw_desc;
/*
 *  @class WSDDKeywords
 *  @brief interface for the WSDDKeywords class.
 *  @author Suasntha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 */

AXIS_CPP_NAMESPACE_START

class WSDDKeywords  
{
public:
    static void initialize();
    static void unInitialize();
    WSDDKeywords();
    virtual ~WSDDKeywords();
private:
    static volatile bool m_bInit;
};

AXIS_CPP_NAMESPACE_END

#endif 

