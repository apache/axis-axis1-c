/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * InteropTestPortType.c: implemtation for the InteropTestPortType.
 *
 */

#include "InteropTestPortType.h"


void* get_InteropTestPortType_stub(){
	return getStubObject(APTHTTPS, "https://192.168.101.4:443/axis/InteropBase");
}
void destroy_InteropTestPortType_stub(void* p){
	destroyStubObject(p);
}

/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methodechoString
 */
xsd__string echoString(void* pStub, xsd__string Value0)
{
	Call* pCall = (Call*)pStub;
	xsd__string Ret;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->initialize(pCall->_object, C_RPC_PROVIDER, 0)) return Ret;
	pCall->_functions->setTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoString");
	pCall->_functions->setSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->setOperation(pCall->_object, "echoString", "http://soapinterop.org/");
	pCall->_functions->addParameter(pCall->_object, (void*)&Value0, "inputString", XSD_STRING);
	if (AXIS_SUCCESS == pCall->_functions->invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->checkMessage(pCall->_object, "echoStringResponse", ""))
		{
			Ret = pCall->_functions->getElementAsString(pCall->_object, 0, 0);
		}
	}
	pCall->_functions->unInitialize(pCall->_object);
	return Ret;
}

