/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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


#if !defined(_STUBC_H____OF_AXIS_INCLUDED_)
#define _STUBC_H____OF_AXIS_INCLUDED_

#include <axis/client/Stub.hpp>

#include <axis/Axis.h>
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>

AXIS_CPP_NAMESPACE_START

class StubC : public Stub
{
public :
    StubC(const char *ep, AXIS_PROTOCOL_TYPE pt):Stub(ep,pt) 
    {
    	doNotPerformClientRequest = false;
    }
    virtual ~StubC() {}
    Call* getCallStubC() { return getCall(); }
    void applyUserPreferencesStubC() { applyUserPreferences(); }
    void includeSecureStubC() { includeSecure(); }
    void setSOAPHeadersStubC() { setSOAPHeaders(); }
    void checkForExtraneousElementsStubC() { checkForExtraneousElements(); }
    
    // flag to indicate invocations should fail without actually trying to perform 
    // client request due to errors prior to the invocation. When set to true, it
    // will be reset to false only after an axiscCallUnInitialize() is issued.
    int doNotPerformClientRequest;
};
AXIS_CPP_NAMESPACE_END

#endif 

