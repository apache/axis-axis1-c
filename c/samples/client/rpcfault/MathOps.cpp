/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * MathOps.cpp: implemtation for the MathOps.
 *
 */

#include "MathOps.h"

#include <axis/server/AxisWrapperAPI.h>

bool CallBase::bInitialized;
CallFunctions CallBase::ms_VFtable;
MathOps::MathOps(const char* pchEndpointUri)
{
	m_pCall = new Call();
	m_pCall->setProtocol(APTHTTP);
	m_pCall->setEndpointURI(pchEndpointUri);
}

MathOps::~MathOps()
{
	delete m_pCall;
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methoddiv
 */
int MathOps::div(int Value0, int Value1)
{
	int Ret;
        char* cFaultcode;
        char* cFaultstring;
        char* cFaultactor;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "MathOps#div");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("div", "http://localhost/axis/MathOps");
	m_pCall->addParameter((void*)&Value0, "in0", XSD_INT);
	m_pCall->addParameter((void*)&Value1, "in1", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("divResponse",
                     "http://localhost/axis/MathOps"))
		{
			Ret = m_pCall->getElementAsInt("addReturn", 0);
		}
                else if(AXIS_SUCCESS == m_pCall->checkMessage("fault",
                    "http://localhost/axis/MathOps")) //Exception handling code goes here
                {
                    cFaultcode = m_pCall->getElementAsChar("", 0);
                    cFaultstring = m_pCall->getElementAsChar("", 0); 
                    cFaultactor = m_pCall->getElementAsChar("", 0);
                    SOAPStructFault* pFaultDetail = NULL;
                    pFaultDetail = (SOAPStructFault*)m_pCall->
                        getCmplxObject((void*) Axis_DeSerialize_SOAPStructFault, 
                        (void*) Axis_Create_SOAPStructFault, 
                        (void*) Axis_Delete_SOAPStructFault,"faultstruct", 0);
                }
	}
	m_pCall->unInitialize();
	return Ret;
}

int MathOps::getFaultDetail(char** ppcDetail)
{
    m_pCall->getFaultDetail(ppcDetail);
}

