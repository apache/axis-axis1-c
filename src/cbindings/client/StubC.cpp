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
        return (AXISCHANDLE)stub;
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubDestroy(AXISCHANDLE stub) 
{
	if ((AXISCHANDLE)NULL == stub)
		return;
			
    StubC *s = (StubC*)stub;
    
    try
    {
        delete s;
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetEndPoint(AXISCHANDLE stub, 
                      const char * pcEndPointURI) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        s->setEndPoint(pcEndPointURI);
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetTransportProperty(AXISCHANDLE stub, 
                                   const char * pcKey, 
                                   const char * pcValue) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        s->setTransportProperty(pcKey,pcValue);
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
const char * axiscStubGetTransportProperty(AXISCHANDLE stub, 
                                           const char *key, 
                                           AxiscBool response) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        return s->getTransportProperty(key, (bool)(response !=0 ));
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (const char *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
const char * axiscStubGetFirstTransportPropertyKey(AXISCHANDLE stub, 
                                               AxiscBool response) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        return s->getFirstTransportPropertyKey( (bool)(response!=0));
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
    
    return (const char *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
const char * axiscStubGetNextTransportPropertyKey(AXISCHANDLE stub, 
                                              AxiscBool response) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        return s->getNextTransportPropertyKey((bool)(response!=0));
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (const char *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
const char * axiscStubGetCurrentTransportPropertyKey(AXISCHANDLE stub, 
                                                 AxiscBool response) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        return s->getCurrentTransportPropertyKey((bool)(response!=0));
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (const char *)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
const char * axiscStubGetCurrentTransportPropertyValue(AXISCHANDLE stub, 
                                                   AxiscBool response) 
{
    
    
    Stub *s = (Stub*)stub;

    try
    {
        return s->getCurrentTransportPropertyValue((bool)(response!=0));
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (const char *)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubDeleteCurrentTransportProperty(AXISCHANDLE stub, 
                                         AxiscBool response) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        s->deleteCurrentTransportProperty((bool)(response!=0));
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubDeleteTransportProperty(AXISCHANDLE stub, 
                                  char * pcKey, 
                                  unsigned int uiOccurance) 
{
    
    
    Stub *s = (Stub*)stub;

    try
    {
        s->deleteTransportProperty(pcKey,uiOccurance);
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetHandlerProperty(AXISCHANDLE stub, 
                                 AxiscChar * name, 
                                 void * value, 
                                 int len) 
{
    
    
    Stub *s = (Stub*)stub;

    try
    {
        s->setHandlerProperty(name,value,len);
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscStubCreateSOAPHeaderBlock(AXISCHANDLE stub, 
                                       AxiscChar * pachLocalName, 
                                       AxiscChar * pachUri, 
                                       AxiscChar * pachPrefix) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        if (pachPrefix)
            return (AXISCHANDLE)s->createSOAPHeaderBlock(pachLocalName,pachUri,pachPrefix);
        else
            return (AXISCHANDLE)s->createSOAPHeaderBlock(pachLocalName,pachUri);        
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscStubGetFirstSOAPHeaderBlock(AXISCHANDLE stub) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        return (AXISCHANDLE)s->getFirstSOAPHeaderBlock();
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (AXISCHANDLE)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscStubGetNextSOAPHeaderBlock(AXISCHANDLE stub) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        return (AXISCHANDLE)s->getNextSOAPHeaderBlock();
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (AXISCHANDLE)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscStubGetCurrentSOAPHeaderBlock(AXISCHANDLE stub) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        return (AXISCHANDLE)s->getCurrentSOAPHeaderBlock();
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (AXISCHANDLE)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubDeleteCurrentSOAPHeaderBlock(AXISCHANDLE stub) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        s->deleteCurrentSOAPHeaderBlock();
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubDeleteSOAPHeaderBlock(AXISCHANDLE stub, AXISCHANDLE pHeaderBlock) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        s->deleteSOAPHeaderBlock((IHeaderBlock*)pHeaderBlock);
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetProxy(AXISCHANDLE stub, 
                       const char * pcProxyHost, 
                       unsigned int uiProxyPort) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        s->setProxy(pcProxyHost,uiProxyPort);
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetTransportTimeout(AXISCHANDLE stub, 
                              long lSeconds) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        s->setTransportTimeout(lSeconds);
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
int axiscStubGetStatus(AXISCHANDLE stub) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        return s->getStatus();
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return -1;
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetMaintainSession(AXISCHANDLE stub, 
                             AxiscBool bSession) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        s->setMaintainSession(0!=bSession);
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetTransportProtocol(AXISCHANDLE stub, 
                               AXISC_PROTOCOL_TYPE eProtocol) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        s->setTransportProtocol((AXIS_PROTOCOL_TYPE)eProtocol);
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
AXISC_PROTOCOL_TYPE axiscStubGetTransportProtocol(AXISCHANDLE stub) 
{
    
    
    Stub *s = (Stub*)stub;
    
    try
    {
        return (AXISC_PROTOCOL_TYPE)(s->getTransportProtocol());
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
    
    return (AXISC_PROTOCOL_TYPE)-1;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscStubGetCall(AXISCHANDLE stub) 
{ 
    
    
    StubC *s = (StubC*)stub;
    
    try
    {
        Call *c = s->getCallStubC();
        c->setCStub(s);
        return (AXISCHANDLE)c;
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (AXISCHANDLE)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubApplyUserPreferences(AXISCHANDLE stub) 
{ 
    
    
    StubC *s = (StubC*)stub;
    
    try
    {
        s->applyUserPreferencesStubC();
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}
AXISC_STORAGE_CLASS_INFO 
void axiscStubIncludeSecure(AXISCHANDLE stub)
{ 
    
    
    StubC *s = (StubC*)stub;
    
    try
    {
        s->includeSecureStubC();
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
void axiscStubSetSOAPHeaders(AXISCHANDLE stub) 
{ 
    
    
    StubC *s = (StubC*)stub;
    
    try
    {
        s->setSOAPHeadersStubC(); 
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}


AXISC_STORAGE_CLASS_INFO 
void axiscStubSetSecure(AXISCHANDLE stub, 
                        char * pszArguments, 
                        ... )
{ 
    
    
    StubC *s = (StubC*)stub;
    
    try
    {
        va_list args;
    
        va_start( args, pszArguments);    
        s->SetSecure(pszArguments, args);
        va_end( args);    
    }
    catch ( AxisException& e  )
    {
        
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
          
          
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

}



