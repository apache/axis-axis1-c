/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * MathOps.cpp: implemtation for the MathOps.
 *
 */

#include "MathOps.h"

#include <axis/server/AxisWrapperAPI.h>

bool CallBase::bInitialized;
CallFunctions CallBase::ms_VFtable;
extern int Axis_DeSerialize_DivByZeroFault(DivByZeroFault* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_DivByZeroFault(DivByZeroFault *Obj, bool bArray = false, int nSize=0);
extern void Axis_Delete_DivByZeroFault(DivByZeroFault* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_DivByZeroFault(DivByZeroFault* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_DivByZeroFault();

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
	m_pCall->setOperation("div", "http://soapinterop.org/wsdl");
	m_pCall->addParameter((void*)&Value0, "int0", XSD_INT);
	m_pCall->addParameter((void*)&Value1, "int1", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("divResponse", "http://soapinterop.org/wsdl"))
		{
			Ret = m_pCall->getElementAsInt("addReturn", 0);
		}
	}
    }
    catch(AxisException& e)
    {
        if(AXIS_SUCCESS == m_pCall->checkFault("Fault",
            "http://localhost/axis/MathOps/types")) //Exception handling code goes here
        {
            cFaultcode = m_pCall->getElementAsString("faultcode", 0);
            cFaultstring = m_pCall->getElementAsString("faultstring", 0);
            cFaultactor = m_pCall->getElementAsString("faultactor", 0);
            if(AXIS_SUCCESS == m_pCall->checkFault("faultdetail",
                "http://localhost/axis/MathOps/types"))
            {
                m_pCall->getFaultDetail(&cFaultdetail);
                throw AxisException(cFaultdetail);
            }
            else
            {
                DivByZeroFault* pFaultDetail = NULL;
                pFaultDetail = (DivByZeroFault*)m_pCall->
                    getCmplxObject((void*) Axis_DeSerialize_DivByZeroFault,
                    (void*) Axis_Create_DivByZeroFault,
                    (void*) Axis_Delete_DivByZeroFault,"faultstruct", 0);
                                                                                                                                             
                char* temp = pFaultDetail->varString;
                printf("%s\n", temp);
                /*start user code*/
                printf("faultcode:%s\n", cFaultcode);
                printf("faultstring:%s\n", cFaultstring);
                printf("faultactor:%s\n", cFaultactor);
                /*end user code*/
                m_pCall->unInitialize();
                throw AxisDivByZeroException(pFaultDetail);
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

//int MathOps::getStatus(){if ( m_pCall==NULL ) return AXIS_SUCCESS; else return m_pCall->getStatus();}
