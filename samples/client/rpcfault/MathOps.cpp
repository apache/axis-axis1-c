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
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "MathOps#div");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("div", "http://localhost/axis/MathOps");
	m_pCall->addParameter((void*)&Value0, "in0", XSD_INT);
	m_pCall->addParameter((void*)&Value1, "in1", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("divResponse", "http://localhost/axis/MathOps"))
		{
			Ret = m_pCall->getElementAsInt("addReturn", 0);
		}
                else//Exception handling code goes here
                {
                }
	}
	m_pCall->unInitialize();
	return Ret;



        SOAPStruct* pReturn = NULL;
        if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return pReturn;
        m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoStruct");
        m_pCall->setSOAPVersion(SOAP_VER_1_1);
        m_pCall->setOperation("echoStruct", "http://soapinterop.org/");
        m_pCall->addCmplxParameter(Value0, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "inputStruct", Axis_URI_SOAPStruct);
        if (AXIS_SUCCESS == m_pCall->invoke())
        {
                if(AXIS_SUCCESS == m_pCall->checkMessage("echoStructResponse", ""))
                {
                        pReturn = (SOAPStruct*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct,"return", 0);
                }
        }
        m_pCall->unInitialize();
        return pReturn;


}

int MathOps::getFaultDetail(char** ppcDetail)
{
    m_pCall->getFaultDetail(ppcDetail);
}
