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

#include <axis/AxisException.hpp>
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

AXISC_STORAGE_CLASS_INFO const AxiscChar* axiscGetCmplxFaultObjectName(AXISCHANDLE soapFault) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return sf->getCmplxFaultObjectName();
}

AXISC_STORAGE_CLASS_INFO void * axiscGetCmplxFaultObject(AXISCHANDLE soapFault, void * pDZFunct, 
	void * pCreFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return sf->getCmplxFaultObject(pDZFunct,pCreFunct,pDelFunct,pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO const AxisChar* axiscGetSimpleFaultDetail(AXISCHANDLE soapFault) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return sf->getSimpleFaultDetail();
}

AXISC_STORAGE_CLASS_INFO const AxisChar* axiscGetFaultcode(AXISCHANDLE soapFault) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return sf->getFaultcode();
}

AXISC_STORAGE_CLASS_INFO const AxisChar* axiscGetFaultstring(AXISCHANDLE soapFault) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return sf->getFaultstring();
}

AXISC_STORAGE_CLASS_INFO const AxisChar* axiscGetFaultactor(AXISCHANDLE soapFault) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return sf->getFaultactor();
}

AXISC_STORAGE_CLASS_INFO int axiscSetFaultcode(AXISCHANDLE soapFault, const AxisChar*  sFaultcode) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return sf->setFaultcode(sFaultcode);
}

AXISC_STORAGE_CLASS_INFO int axiscSetFaultstring(AXISCHANDLE soapFault, const AxisChar*  sFaultstring) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return sf->setFaultstring(sFaultstring);
}

AXISC_STORAGE_CLASS_INFO int axiscSetFaultactor(AXISCHANDLE soapFault, const AxisChar*  sFaultactor) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return sf->setFaultactor(sFaultactor);
}

AXISC_STORAGE_CLASS_INFO int axiscSetFaultDetail(AXISCHANDLE soapFault, const AxisChar*  sFaultdetail) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return sf->setFaultDetail(sFaultdetail);
}

AXISC_STORAGE_CLASS_INFO int axiscSetCmplxFaultObject(AXISCHANDLE soapFault, const void * pCmplxFaultObject) {
	ISoapFault *sf = (ISoapFault*)soapFault;
	return sf->setCmplxFaultObject(pCmplxFaultObject);
}

}
