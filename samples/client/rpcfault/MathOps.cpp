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

using namespace std;

 bool CallBase::bInitialized;
CallFunctions CallBase::ms_VFtable;
extern int Axis_DeSerialize_DivByZeroStruct(DivByZeroStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_DivByZeroStruct(DivByZeroStruct *Obj, bool bArray = false, int nSize=0);
extern void Axis_Delete_DivByZeroStruct(DivByZeroStruct* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_DivByZeroStruct(DivByZeroStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_DivByZeroStruct();

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
 * This method wrap the service method div
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
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return Ret;
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
		else if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/MathOps" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
			if(0 == strcmp("DivByZeroStruct", cFaultstring))
			{
				if (AXIS_SUCCESS == m_pCall->checkFault("faultdetail","http://localhost/axis/MathOps"))
				{
					DivByZeroStruct* pFaultDetail = NULL;
					pFaultDetail = (DivByZeroStruct*)m_pCall->
						getCmplxObject((void*) Axis_DeSerialize_DivByZeroStruct,
						(void*) Axis_Create_DivByZeroStruct,
						(void*) Axis_Delete_DivByZeroStruct,"faultstruct1", 0);
					/*User code to handle the struct can be inserted here*/
                                        char* temp = pFaultDetail->varString;
                                        printf("%s\n", temp);
                                        printf("faultcode:%s\n", cFaultcode);
                                        printf("faultstring:%s\n", cFaultstring);
                                        printf("faultactor:%s\n", cFaultactor);
					m_pCall->unInitialize();
					throw AxisDivByZeroException(pFaultDetail);
				}
			}
			else
			{
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisGenException(cFaultdetail);
			}
		}
		else throw;
	}
}

int MathOps::getStatus()
{
	if ( m_pCall==NULL ) 
		return AXIS_SUCCESS; 
	else 
		return m_pCall->getStatus();
}

int MathOps::getFaultDetail(char** ppcDetail)
{
	return m_pCall->getFaultDetail(ppcDetail);
	return 0;
}

