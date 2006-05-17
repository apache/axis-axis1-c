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
 
#include <stdarg.h>

#include <axis/client/Stub.hpp>
#include <axis/AxisException.hpp>

#include "../AxisObjectContainer.hpp"

#include <axis/Axis.h>
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/client/Stub.h>

AXIS_CPP_NAMESPACE_START
class StubC : public Stub
{
public :
    StubC(const char *ep, AXIS_PROTOCOL_TYPE pt):Stub(ep,pt) {}
    virtual ~StubC() {}
    Call* getCallStubC() { return getCall(); }
    void applyUserPreferencesStubC() { applyUserPreferences(); }
    void includeSecureStubC() { includeSecure(); }
    void setSOAPHeadersStubC() { setSOAPHeaders(); }
};
AXIS_CPP_NAMESPACE_END

AXIS_CPP_NAMESPACE_USE

extern "C" {

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscStubCreate(const char * pcEndPointURI, 
                            AXISC_PROTOCOL_TYPE eProtocol) 
{  
    try
    {
        StubC *stub = new StubC(pcEndPointURI, (AXIS_PROTOCOL_TYPE)eProtocol);
        AxisObjectContainer *h = new AxisObjectContainer(stub);
        return (AXISCHANDLE)h;
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubDestroy(AXISCHANDLE stub) 
{
	if ((AXISCHANDLE)NULL == stub)
		return;
			
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    StubC *s = (StubC*)h->_objHandle;
    
    try
    {
        delete h;
        delete s;
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetEndPoint(AXISCHANDLE stub, 
                      const char * pcEndPointURI) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        s->setEndPoint(pcEndPointURI);
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetTransportProperty(AXISCHANDLE stub, 
                                   const char * pcKey, 
                                   const char * pcValue) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        s->setTransportProperty(pcKey,pcValue);
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
const char * axiscStubGetTransportProperty(AXISCHANDLE stub, 
                                           const char *key, 
                                           AxiscBool response) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        return s->getTransportProperty(key, (bool)(response !=0 ));
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (const char *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
const char * axiscStubGetFirstTransportPropertyKey(AXISCHANDLE stub, 
                                               AxiscBool response) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        return s->getFirstTransportPropertyKey( (bool)(response!=0));
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (const char *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
const char * axiscStubGetNextTransportPropertyKey(AXISCHANDLE stub, 
                                              AxiscBool response) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        return s->getNextTransportPropertyKey((bool)(response!=0));
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (const char *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
const char * axiscStubGetCurrentTransportPropertyKey(AXISCHANDLE stub, 
                                                 AxiscBool response) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        return s->getCurrentTransportPropertyKey((bool)(response!=0));
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (const char *)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
const char * axiscStubGetCurrentTransportPropertyValue(AXISCHANDLE stub, 
                                                   AxiscBool response) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;

    try
    {
        return s->getCurrentTransportPropertyValue((bool)(response!=0));
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (const char *)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubDeleteCurrentTransportProperty(AXISCHANDLE stub, 
                                         AxiscBool response) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        s->deleteCurrentTransportProperty((bool)(response!=0));
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubDeleteTransportProperty(AXISCHANDLE stub, 
                                  char * pcKey, 
                                  unsigned int uiOccurance) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;

    try
    {
        s->deleteTransportProperty(pcKey,uiOccurance);
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetHandlerProperty(AXISCHANDLE stub, 
                                 AxiscChar * name, 
                                 void * value, 
                                 int len) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;

    try
    {
        s->setHandlerProperty(name,value,len);
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscStubCreateSOAPHeaderBlock(AXISCHANDLE stub, 
                                       AxiscChar * pachLocalName, 
                                       AxiscChar * pachUri, 
                                       AxiscChar * pachPrefix) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        if (pachPrefix)
            return (AXISCHANDLE)s->createSOAPHeaderBlock(pachLocalName,pachUri,pachPrefix);
        else
            return (AXISCHANDLE)s->createSOAPHeaderBlock(pachLocalName,pachUri);        
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscStubGetFirstSOAPHeaderBlock(AXISCHANDLE stub) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        return (AXISCHANDLE)s->getFirstSOAPHeaderBlock();
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (AXISCHANDLE)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscStubGetNextSOAPHeaderBlock(AXISCHANDLE stub) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        return (AXISCHANDLE)s->getNextSOAPHeaderBlock();
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (AXISCHANDLE)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscStubGetCurrentSOAPHeaderBlock(AXISCHANDLE stub) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        return (AXISCHANDLE)s->getCurrentSOAPHeaderBlock();
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (AXISCHANDLE)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubDeleteCurrentSOAPHeaderBlock(AXISCHANDLE stub) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        s->deleteCurrentSOAPHeaderBlock();
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubDeleteSOAPHeaderBlock(AXISCHANDLE stub, AXISCHANDLE pHeaderBlock) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        s->deleteSOAPHeaderBlock((IHeaderBlock*)pHeaderBlock);
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetProxy(AXISCHANDLE stub, 
                       const char * pcProxyHost, 
                       unsigned int uiProxyPort) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        s->setProxy(pcProxyHost,uiProxyPort);
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetTransportTimeout(AXISCHANDLE stub, 
                              long lSeconds) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        s->setTransportTimeout(lSeconds);
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
int axiscStubGetStatus(AXISCHANDLE stub) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        return s->getStatus();
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return -1;
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetMaintainSession(AXISCHANDLE stub, 
                             AxiscBool bSession) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        s->setMaintainSession(0!=bSession);
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetTransportProtocol(AXISCHANDLE stub, 
                               AXISC_PROTOCOL_TYPE eProtocol) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        s->setTransportProtocol((AXIS_PROTOCOL_TYPE)eProtocol);
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
AXISC_PROTOCOL_TYPE axiscStubGetTransportProtocol(AXISCHANDLE stub) 
{
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    Stub *s = (Stub*)h->_objHandle;
    
    try
    {
        return (AXISC_PROTOCOL_TYPE)(s->getTransportProtocol());
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISC_PROTOCOL_TYPE)-1;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscStubGetCall(AXISCHANDLE stub) 
{ 
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    StubC *s = (StubC*)h->_objHandle;
    
    try
    {
        AxisObjectContainer *newH = new AxisObjectContainer(s->getCallStubC());

        return (AXISCHANDLE)newH;
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (AXISCHANDLE)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubApplyUserPreferences(AXISCHANDLE stub) 
{ 
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    StubC *s = (StubC*)h->_objHandle;
    
    try
    {
        s->applyUserPreferencesStubC();
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}
AXISC_STORAGE_CLASS_INFO 
void axiscStubIncludeSecure(AXISCHANDLE stub)
{ 
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    StubC *s = (StubC*)h->_objHandle;
    
    try
    {
        s->includeSecureStubC();
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetSOAPHeaders(AXISCHANDLE stub) 
{ 
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    StubC *s = (StubC*)h->_objHandle;
    
    try
    {
        s->setSOAPHeadersStubC(); 
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}


AXISC_STORAGE_CLASS_INFO 
void axiscStubSetSecure(AXISCHANDLE stub, 
                        char * pszArguments, 
                        ... )
{ 
    AxisObjectContainer *h = (AxisObjectContainer *)stub;
    h->_exception.resetException();
    StubC *s = (StubC*)h->_objHandle;
    
    try
    {
        va_list args;
    
        va_start( args, pszArguments);    
        s->SetSecure(pszArguments, args);
        va_end( args);    
    }
    catch ( AxisException& e  )
    {
        h->_exception.setExceptionFromException(e);
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        h->_exception.setExceptionCode(-1);  
        h->_exception.setMessage("Unrecognized exception thrown.");  
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

}



