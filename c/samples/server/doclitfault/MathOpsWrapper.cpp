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

/*
 * This is the Service implementation CPP file genarated by theWSDL2Ws.
 * MathOpsWrapper.cpp: implemtation for the MathOpsWrapper.
 * 
 */

#include "MathOpsWrapper.h"

extern int Axis_DeSerialize_DivByZeroFault(DivByZeroFault* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_DivByZeroFault(DivByZeroFault *Obj, bool bArray = false, int nSize=0);
extern void Axis_Delete_DivByZeroFault(DivByZeroFault* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_DivByZeroFault(DivByZeroFault* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_DivByZeroFault();

MathOpsWrapper::MathOpsWrapper()
{
	pWs = new MathOps();
}

MathOpsWrapper::~MathOpsWrapper()
{
	delete pWs;
}

/*implementation of WrapperClassHandler interface*/
void MathOpsWrapper::onFault(void *pMsg)
{
}

int MathOpsWrapper::init()
{
	return AXIS_SUCCESS;
}

int MathOpsWrapper::fini()
{
	return AXIS_SUCCESS;
}


/*
 * This method invokes the right service method 
 */
int MathOpsWrapper::invoke(void *pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	const AxisChar *method = mc->getOperationName();
	if (0 == strcmp(method, "div"))
		return div(mc);
	else return AXIS_FAIL;
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service method 
 */
int MathOpsWrapper::div(void* pMsg) throw(AxisDivByZeroException)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
        int ret;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("div", "http://soapinterop.org/wsdl")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("divResponse", "http://soapinterop.org/wsdl");
	int v0 = pIWSDZ->getElementAsInt("int0",0);
	int v1 = pIWSDZ->getElementAsInt("int1",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
        try
        {
	    ret = pWs->div(v0,v1);
        }
        catch(AxisDivByZeroException& e)
        {
            pIWSSZ->createSoapFault("DivByZeroFault", "http://soapinterop.org/");
            DivByZeroFault* pObjFault = new DivByZeroFault();
            pObjFault->varString = "Division by zero exception";
            pObjFault->varInt = 1;
            pObjFault->varFloat = 10.52;

            if(pObjFault)
                pIWSSZ->addFaultDetail(pObjFault, (void*)Axis_Serialize_DivByZeroFault,
                    (void*)Axis_Delete_DivByZeroFault, "DivByZeroException", "");

            throw;
        }
	return pIWSSZ->addOutputParam("divReturn", (void*)&ret, XSD_INT);
}

