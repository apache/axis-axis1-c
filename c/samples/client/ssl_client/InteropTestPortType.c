/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * InteropTestPortType.c: implemtation for the InteropTestPortType.
 *
 */

#include "InteropTestPortType.h"


void* get_InteropTestPortType_stub(){
	return GetStubObject(APTHTTPS, "https://192.168.101.4:443/axis/InteropBase");
}
void destroy_InteropTestPortType_stub(void* p){
	DestroyStubObject(p);
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
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, 0)) return Ret;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoString");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoString", "http://soapinterop.org/");
	pCall->_functions->AddParameter(pCall->_object, (void*)&Value0, "inputString", XSD_STRING);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoStringResponse", ""))
		{
			Ret = pCall->_functions->GetElementAsString(pCall->_object, 0, 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return Ret;
}

