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

#include <axis/ISoapFault.hpp>
AXIS_CPP_NAMESPACE_USE

extern "C" {
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/ISoapFault.h>

AXISC_STORAGE_CLASS_INFO void axiscDestroyISoapFault(AXISCHANDLE soapFault) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	delete sf;
}

AXISC_STORAGE_CLASS_INFO char* axiscGetCmplxFaultObjectName(AXISCHANDLE soapFault) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return const_cast<char*>(sf->getCmplxFaultObjectName().c_str());
}

AXISC_STORAGE_CLASS_INFO void * axiscGetCmplxFaultObject(AXISCHANDLE soapFault, void * pDZFunct, 
	void * pCreFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return sf->getCmplxFaultObject(pDZFunct,pCreFunct,pDelFunct,pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO char* axiscGetSimpleFaultDetail(AXISCHANDLE soapFault) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return const_cast<char*>(sf->getSimpleFaultDetail().c_str());
}

AXISC_STORAGE_CLASS_INFO char* axiscGetFaultcode(AXISCHANDLE soapFault) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return const_cast<char*>(sf->getFaultcode().c_str());
}

AXISC_STORAGE_CLASS_INFO char* axiscGetFaultstring(AXISCHANDLE soapFault) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return const_cast<char*>(sf->getFaultstring().c_str());
}

AXISC_STORAGE_CLASS_INFO char* axiscGetFaultactor(AXISCHANDLE soapFault) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return const_cast<char*>(sf->getFaultactor().c_str());
}

AXISC_STORAGE_CLASS_INFO int axiscSetFaultcode(AXISCHANDLE soapFault, const char*  sFaultcode) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	string fc(sFaultcode);
	return sf->setFaultcode(fc);
}

AXISC_STORAGE_CLASS_INFO int axiscSetFaultstring(AXISCHANDLE soapFault, const char*  sFaultstring) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	string fs(sFaultstring);
	return sf->setFaultstring(fs);
}

AXISC_STORAGE_CLASS_INFO int axiscSetFaultactor(AXISCHANDLE soapFault, const char*  sFaultactor) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	string fa(sFaultactor);
	return sf->setFaultactor(fa);
}

AXISC_STORAGE_CLASS_INFO int axiscSetFaultDetail(AXISCHANDLE soapFault, const char*  sFaultdetail) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	string fd(sFaultdetail);
	return sf->setFaultDetail(fd);
}

AXISC_STORAGE_CLASS_INFO int axiscSetCmplxFaultObject(AXISCHANDLE soapFault, const void * pCmplxFaultObject) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return sf->setCmplxFaultObject(pCmplxFaultObject);
}

}
