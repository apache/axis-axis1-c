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
 *
 *
 *   @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
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
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "MathOpsDL#div");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("div", "http://soapinterop.org/wsdl");
	m_pCall->addParameter((void*)&Value0, "int0", XSD_INT);
	m_pCall->addParameter((void*)&Value1, "int1", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("divResponse", "http://soapinterop.org/wsdl"))
		{
			Ret = m_pCall->getElementAsInt("divReturn", 0);
		}
	}
        m_pCall->unInitialize();
        return Ret;
    }
    catch(AxisException& e)
    {
        int iExceptionCode = e.getExceptionCode();
        if(AXISC_NODE_VALUE_MISMATCH_EXCEPTION != iExceptionCode)
        {
            throw;
        }
        if(AXIS_SUCCESS == m_pCall->checkFault("Fault",
            "http://localhost/axis/MathOps/types")) //Exception handling code goes here
        {
            cFaultcode = m_pCall->getElementAsString("faultcode", 0);
            cFaultstring = m_pCall->getElementAsString("faultstring", 0);
            cFaultactor = m_pCall->getElementAsString("faultactor", 0);
            if(0 == strcmp("DivByZeroFault", cFaultstring))
            {
                if(AXIS_SUCCESS == m_pCall->checkFault("faultdetail",
                    "http://localhost/axis/MathOps/types"))
                {
                    DivByZeroFault* pFaultDetail = NULL;
                    pFaultDetail = (DivByZeroFault*)m_pCall->
                        getCmplxObject((void*) Axis_DeSerialize_DivByZeroFault,
                        (void*) Axis_Create_DivByZeroFault,
                        (void*) Axis_Delete_DivByZeroFault,"DivByZeroException", 0);
                                                                                                                                             
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
            else
            {
                cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
                throw AxisException(cFaultdetail);
            }
        }
        else throw;
    }

}

int MathOps::getFaultDetail(char** ppcDetail)
{
    m_pCall->getFaultDetail(ppcDetail);
    return 0;
}

//int MathOps::getStatus(){if ( m_pCall==NULL ) return AXIS_SUCCESS; else return m_pCall->getStatus();}
