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
void CalculatorWrapper::onFault(void *pMsg)
{
}

int CalculatorWrapper::init()
{
	return AXIS_SUCCESS;
}

int CalculatorWrapper::fini()
{
	return AXIS_SUCCESS;
}


/*
 * This method invokes the right service method 
 */
int CalculatorWrapper::invoke(void *pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	const AxisChar *method = mc->getOperationName();
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
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("add", "http://localhost/axis/Calculator")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("addResponse", "http://localhost/axis/Calculator");
	int v0;pIWSDZ->getElementAsInt("in0",0, v0);
	int v1;pIWSDZ->getElementAsInt("in1",0, v1);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	int ret = pWs->add(v0,v1);
	return pIWSSZ->addOutputParam("addReturn", (void*)&ret, XSD_INT);
}


/*
 * This method wrap the service method 
 */
int CalculatorWrapper::sub(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("sub", "http://localhost/axis/Calculator")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("subResponse", "http://localhost/axis/Calculator");
	int v0;pIWSDZ->getElementAsInt("in0",0, v0);
	int v1;pIWSDZ->getElementAsInt("in1",0, v1);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	int ret = pWs->sub(v0,v1);
	return pIWSSZ->addOutputParam("subReturn", (void*)&ret, XSD_INT);
}


/*
 * This method wrap the service method 
 */
int CalculatorWrapper::mul(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("mul", "http://localhost/axis/Calculator")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("mulResponse", "http://localhost/axis/Calculator");
	int v0; pIWSDZ->getElementAsInt("in0",0, v0);
	int v1; pIWSDZ->getElementAsInt("in1",0, v1);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	int ret = pWs->mul(v0,v1);
	return pIWSSZ->addOutputParam("mulReturn", (void*)&ret, XSD_INT);
}


/*
 * This method wrap the service method 
 */
int CalculatorWrapper::div(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("div", "http://localhost/axis/Calculator")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("divResponse", "http://localhost/axis/Calculator");
	int v0; pIWSDZ->getElementAsInt("in0",0, v0 );
	int v1; pIWSDZ->getElementAsInt("in1",0, v1);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	int ret = pWs->div(v0,v1);
	return pIWSSZ->addOutputParam("divReturn", (void*)&ret, XSD_INT);
}

