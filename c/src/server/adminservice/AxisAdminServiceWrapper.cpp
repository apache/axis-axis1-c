/*
 * This is the Service implementation CPP file genarated by theWSDL2Ws.
 * AxisAdminServiceWrapper.cpp: implemtation for the AxisAdminServiceWrapper.
 * 
 */

#include "AxisAdminServiceWrapper.h"

AxisAdminServiceWrapper::AxisAdminServiceWrapper()
{
	pWs = new AxisAdminService();
}

AxisAdminServiceWrapper::~AxisAdminServiceWrapper()
{
	delete pWs;
}

/*implementation of WrapperClassHandler interface*/
void AxisAdminServiceWrapper::OnFault(IMessageData *pMsg)
{
}

int AxisAdminServiceWrapper::Init()
{
	return AXIS_SUCCESS;
}

int AxisAdminServiceWrapper::Fini()
{
	return AXIS_SUCCESS;
}


/*
 * This method invokes the right service method 
 */
int AxisAdminServiceWrapper::Invoke(IMessageData *mc)
{
	const AxisChar *method = mc->GetOperationName();
	if (0 == strcmp(method, "deploy"))
		return deploy(mc);
	else if (0 == strcmp(method, "undeploy"))
		return undeploy(mc);
	else return AXIS_FAIL;
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service method 
 */
int AxisAdminServiceWrapper::deploy(IMessageData* mc)
{
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("deploy", "http://www.opensource.lk/xsd")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("deployResponse", "http://www.opensource.lk/xsd");
	xsd__base64Binary v0 = pIWSDZ->GetElementAsBase64Binary("wsdd",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	xsd__boolean ret = pWs->deploy(v0);
	return pIWSSZ->AddOutputParam("return", (void*)&ret, XSD_BOOLEAN);
}


/*
 * This method wrap the service method 
 */
int AxisAdminServiceWrapper::undeploy(IMessageData* mc)
{
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("undeploy", "http://www.opensource.lk/xsd")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("undeployResponse", "http://www.opensource.lk/xsd");
	xsd__base64Binary v0 = pIWSDZ->GetElementAsBase64Binary("wsdd",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	xsd__boolean ret = pWs->undeploy(v0);
	return pIWSSZ->AddOutputParam("return", (void*)&ret, XSD_BOOLEAN);
}

