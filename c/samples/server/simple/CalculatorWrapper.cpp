/*
 * This is the Service implementation CPP file genarated by theWSDL2Ws.
 * CalculatorWrapper.cpp: implemtation for the CalculatorWrapper.
 * 
 */

#include "CalculatorWrapper.h"

CalculatorWrapper::CalculatorWrapper()
{
	pWs = new Calculator();
}

CalculatorWrapper::~CalculatorWrapper()
{
	delete pWs;
}

/*implementation of WrapperClassHandler interface*/
void CalculatorWrapper::OnFault(void *pMsg)
{
}

int CalculatorWrapper::Init()
{
	return AXIS_SUCCESS;
}

int CalculatorWrapper::Fini()
{
	return AXIS_SUCCESS;
}


/*
 * This method invokes the right service method 
 */
int CalculatorWrapper::Invoke(void *pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	const AxisChar *method = mc->GetOperationName();
	if (0 == strcmp(method, "add"))
		return add(mc);
	else if (0 == strcmp(method, "sub"))
		return sub(mc);
	else if (0 == strcmp(method, "mul"))
		return mul(mc);
	else if (0 == strcmp(method, "div"))
		return div(mc);
	else return AXIS_FAIL;
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service method 
 */
int CalculatorWrapper::add(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("add", "http://localhost/axis/Calculator")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("addResponse", "http://localhost/axis/Calculator");
	int v0 = pIWSDZ->GetElementAsInt("in0",0);
	int v1 = pIWSDZ->GetElementAsInt("in1",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	int ret = pWs->add(v0,v1);
	return pIWSSZ->AddOutputParam("addReturn", (void*)&ret, XSD_INT);
}


/*
 * This method wrap the service method 
 */
int CalculatorWrapper::sub(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("sub", "http://localhost/axis/Calculator")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("subResponse", "http://localhost/axis/Calculator");
	int v0 = pIWSDZ->GetElementAsInt("in0",0);
	int v1 = pIWSDZ->GetElementAsInt("in1",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	int ret = pWs->sub(v0,v1);
	return pIWSSZ->AddOutputParam("subReturn", (void*)&ret, XSD_INT);
}


/*
 * This method wrap the service method 
 */
int CalculatorWrapper::mul(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("mul", "http://localhost/axis/Calculator")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("mulResponse", "http://localhost/axis/Calculator");
	int v0 = pIWSDZ->GetElementAsInt("in0",0);
	int v1 = pIWSDZ->GetElementAsInt("in1",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	int ret = pWs->mul(v0,v1);
	return pIWSSZ->AddOutputParam("mulReturn", (void*)&ret, XSD_INT);
}


/*
 * This method wrap the service method 
 */
int CalculatorWrapper::div(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("div", "http://localhost/axis/Calculator")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("divResponse", "http://localhost/axis/Calculator");
	int v0 = pIWSDZ->GetElementAsInt("in0",0);
	int v1 = pIWSDZ->GetElementAsInt("in1",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	int ret = pWs->div(v0,v1);
	return pIWSSZ->AddOutputParam("divReturn", (void*)&ret, XSD_INT);
}

