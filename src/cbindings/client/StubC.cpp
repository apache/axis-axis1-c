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

#include <axis/client/Stub.hpp>

AXIS_CPP_NAMESPACE_START
class StubC : Stub
{
public :
	StubC(const char *ep, AXIS_PROTOCOL_TYPE pt):Stub(ep,pt) {}
	virtual ~StubC() {}
	Call* getCallStubC() { return getCall(); }
	void applyUserPreferencesStubC() { applyUserPreferences(); }
	void setSOAPHeadersStubC() { setSOAPHeaders(); }
	void setSOAPMethodAttributesStubC() { setSOAPMethodAttributes(); }
};
AXIS_CPP_NAMESPACE_END

AXIS_CPP_NAMESPACE_USE

extern "C" {
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/client/Stub.h>

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateStub(const char * pcEndPointURI, 
	AXISC_PROTOCOL_TYPE eProtocol) {
	StubC *stub = new StubC(pcEndPointURI, static_cast<AXIS_PROTOCOL_TYPE>(eProtocol));
	return (AXISCHANDLE)stub;
}

AXISC_STORAGE_CLASS_INFO void axiscDestroyStub(AXISCHANDLE stub) {
	StubC *s = (StubC*)stub;
	delete s;
}

AXISC_STORAGE_CLASS_INFO void axiscSetEndPoint(AXISCHANDLE stub, const char * pcEndPointURI) {
	Stub *s = (Stub*)stub;
	s->setEndPoint(pcEndPointURI);
}

AXISC_STORAGE_CLASS_INFO void axiscSetTransportPropertyStub(AXISCHANDLE stub, const char * pcKey, 
	const char * pcValue) {
	Stub *s = (Stub*)stub;
	s->setTransportProperty(pcKey,pcValue);
}

AXISC_STORAGE_CLASS_INFO const char * axiscGetFirstTransportPropertyKey(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	return s->getFirstTransportPropertyKey();
}

AXISC_STORAGE_CLASS_INFO const char * axiscGetNextTransportPropertyKey(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	return s->getNextTransportPropertyKey();
}

AXISC_STORAGE_CLASS_INFO const char * axiscGetCurrentTransportPropertyKey(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	return s->getCurrentTransportPropertyKey();
}

AXISC_STORAGE_CLASS_INFO const char * axiscGetCurrentTransportPropertyValue(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	return s->getCurrentTransportPropertyValue();
}

AXISC_STORAGE_CLASS_INFO void axiscDeleteCurrentTransportProperty(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	s->deleteCurrentTransportProperty();
}

AXISC_STORAGE_CLASS_INFO void axiscDeleteTransportProperty(AXISCHANDLE stub, char * pcKey, 
	unsigned int uiOccurance) {
	Stub *s = (Stub*)stub;
	s->deleteTransportProperty(pcKey,uiOccurance);
}

AXISC_STORAGE_CLASS_INFO void axiscSetHandlerPropertyStub(AXISCHANDLE stub, AxiscChar * name, 
	void * value, int len) {
	Stub *s = (Stub*)stub;
	s->setHandlerProperty(name,value,len);
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateSOAPHeaderBlock(AXISCHANDLE stub, AxiscChar * pachLocalName, 
	AxiscChar * pachUri, AxiscChar * pachPrefix) {
	Stub *s = (Stub*)stub;
	return (AXISCHANDLE)s->createSOAPHeaderBlock(pachLocalName,pachUri,pachPrefix);
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetFirstSOAPHeaderBlock(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	return (AXISCHANDLE)s->getFirstSOAPHeaderBlock();
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetNextSOAPHeaderBlock(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	return (AXISCHANDLE)s->getNextSOAPHeaderBlock();
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetCurrentSOAPHeaderBlock(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	return (AXISCHANDLE)s->getCurrentSOAPHeaderBlock();
}

AXISC_STORAGE_CLASS_INFO void axiscDeleteCurrentSOAPHeaderBlock(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	s->deleteCurrentSOAPHeaderBlock();
}

AXISC_STORAGE_CLASS_INFO void axiscDeleteSOAPHeaderBlock(AXISCHANDLE stub, AXISCHANDLE pHeaderBlock) {
	Stub *s = (Stub*)stub;
	s->deleteSOAPHeaderBlock((IHeaderBlock*)pHeaderBlock);
}

AXISC_STORAGE_CLASS_INFO void axiscSetProxyStub(AXISCHANDLE stub, const char * pcProxyHost, 
	unsigned int uiProxyPort) {
	Stub *s = (Stub*)stub;
	s->setProxy(pcProxyHost,uiProxyPort);
}

AXISC_STORAGE_CLASS_INFO void axiscSetSOAPMethodAttribute(AXISCHANDLE stub, const AxiscChar * pLocalname, 
	const AxiscChar * pPrefix, const AxiscChar * pUri, 
	const AxiscChar * pValue) {
	Stub *s = (Stub*)stub;
	s->setSOAPMethodAttribute(pLocalname,pPrefix,pUri,pValue);
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetFirstSOAPMethodAttribute(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	return (AXISCHANDLE)s->getFirstSOAPMethodAttribute();
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetNextSOAPMethodAttribute(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	return (AXISCHANDLE)s->getNextSOAPMethodAttribute();
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetCurrentSOAPMethodAttribute(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	return (AXISCHANDLE)s->getCurrentSOAPMethodAttribute();
}

AXISC_STORAGE_CLASS_INFO void axiscDeleteCurrentSOAPMethodAttribute(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	s->deleteCurrentSOAPMethodAttribute();
}

AXISC_STORAGE_CLASS_INFO void axiscDeleteSOAPMethodAttribute(AXISCHANDLE stub, AXISCHANDLE pAttribute) {
	Stub *s = (Stub*)stub;
	s->deleteSOAPMethodAttribute((IAttribute*)pAttribute);
}

AXISC_STORAGE_CLASS_INFO void axiscSetTransportTimeout(AXISCHANDLE stub, const long lSeconds) {
	Stub *s = (Stub*)stub;
	s->setTransportTimeout(lSeconds);
}

AXISC_STORAGE_CLASS_INFO int axiscGetStatusStub(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	return s->getStatus();
}

AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetNamespacePrefixStub(AXISCHANDLE stub, const AxiscChar * pNamespace) {
	Stub *s = (Stub*)stub;
	return s->getNamespacePrefix(pNamespace);
}

AXISC_STORAGE_CLASS_INFO void axiscSetMaintainSession(AXISCHANDLE stub, AxiscBool bSession) {
	Stub *s = (Stub*)stub;
	s->setMaintainSession(0!=bSession);
}

AXISC_STORAGE_CLASS_INFO void axiscSetTransportProtocol(AXISCHANDLE stub, AXISC_PROTOCOL_TYPE eProtocol) {
	Stub *s = (Stub*)stub;
	s->setTransportProtocol(static_cast<AXIS_PROTOCOL_TYPE>(eProtocol));
}

AXISC_STORAGE_CLASS_INFO AXISC_PROTOCOL_TYPE axiscGetTransportProtocol(AXISCHANDLE stub) {
	Stub *s = (Stub*)stub;
	return (AXISC_PROTOCOL_TYPE)(s->getTransportProtocol());
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetCall(AXISCHANDLE stub) { 
	StubC *s = (StubC*)stub;
	return s->getCallStubC();
}

AXISC_STORAGE_CLASS_INFO void axiscApplyUserPreferences(AXISCHANDLE stub) { 
	StubC *s = (StubC*)stub;
	s->applyUserPreferencesStubC(); 
}

AXISC_STORAGE_CLASS_INFO void axiscSetSOAPHeaders(AXISCHANDLE stub) { 
	StubC *s = (StubC*)stub;
	s->setSOAPHeadersStubC(); 
}

AXISC_STORAGE_CLASS_INFO void axiscSetSOAPMethodAttributes(AXISCHANDLE stub) { 
	StubC *s = (StubC*)stub;
	s->setSOAPMethodAttributesStubC(); 
}

}