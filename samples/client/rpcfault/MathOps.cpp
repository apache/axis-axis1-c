/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * MathOps.cpp: implemtation for the MathOps.
 *
 */

#include "MathOps.h"

#include <axis/server/AxisWrapperAPI.h>

extern int Axis_DeSerialize_SOAPStructFault(SOAPStructFault* param,
    IWrapperSoapDeSerializer *pDZ);
                                                                                                                             
extern void* Axis_Create_SOAPStructFault(SOAPStructFault *Obj, bool bArray = false,
    int nSize=0);
                                                                                                                             
extern void Axis_Delete_SOAPStructFault(SOAPStructFault* param, bool bArray = false,
    int nSize=0);
                                                                                                                             
extern int Axis_Serialize_SOAPStructFault(SOAPStructFault* param, IWrapperSoapSerializer* pSZ,
    bool bArray = false);
                                                                                                                             
extern int Axis_GetSize_SOAPStructFault();

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
    char* cFaultdetail;
    try
    {
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
        }
    }
    catch(AxisException& e)
    {
        if(AXIS_SUCCESS == m_pCall->checkFault("Fault",
            "http://localhost/axis/MathOps")) //Exception handling code goes here
        {
            cFaultcode = m_pCall->getElementAsString("faultcode", 0);
            cFaultstring = m_pCall->getElementAsString("faultstring", 0); 
            cFaultactor = m_pCall->getElementAsString("faultactor", 0);
            if(0 == strcmp("SOAPStructFault", cFaultstring))
            {
                if(AXIS_SUCCESS == m_pCall->checkFault("faultdetail",
                    "http://localhost/axis/MathOps"))
                {
                    SOAPStructFault* pFaultDetail = NULL;
                    pFaultDetail = (SOAPStructFault*)m_pCall->
                    getCmplxObject((void*) Axis_DeSerialize_SOAPStructFault, 
                        (void*) Axis_Create_SOAPStructFault, 
                        (void*) Axis_Delete_SOAPStructFault,"faultstruct", 0);

                    /*start user code*/
                    char* temp = pFaultDetail->varString;
                    printf("%s\n", temp);
                    printf("faultcode:%s\n", cFaultcode);
                    printf("faultstring:%s\n", cFaultstring);
                    printf("faultactor:%s\n", cFaultactor);
                    /*end user code*/
                    m_pCall->unInitialize();
                    throw AxisDivByZeroException(pFaultDetail);
                }
            }
            else//fault detail consists of a simple string
            {
                cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
                throw AxisException(cFaultdetail);
            }
        }
        else throw;
    }
    m_pCall->unInitialize();
    return Ret;
}

int MathOps::getFaultDetail(char** ppcDetail)
{
    m_pCall->getFaultDetail(ppcDetail);
}

