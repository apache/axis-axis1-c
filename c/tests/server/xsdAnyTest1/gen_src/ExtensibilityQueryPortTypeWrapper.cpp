/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains Web Service Wrapper implementations
 */

#include "ExtensibilityQueryPortTypeWrapper.h"

extern int Axis_DeSerialize_ExtensibilityType(ExtensibilityType* param, IWrapperSoapDeSerializer* pDZ);
extern void* Axis_Create_ExtensibilityType(ExtensibilityType *Obj, bool bArray = false, int nSize=0);
extern void Axis_Delete_ExtensibilityType(ExtensibilityType* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_ExtensibilityType(ExtensibilityType* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_ExtensibilityType();

ExtensibilityQueryPortTypeWrapper::ExtensibilityQueryPortTypeWrapper()
{
	pWs = new ExtensibilityQueryPortType();
}

ExtensibilityQueryPortTypeWrapper::~ExtensibilityQueryPortTypeWrapper()
{
	delete pWs;
}

/*implementation of WrapperClassHandler interface*/
void ExtensibilityQueryPortTypeWrapper::onFault(void *pMsg)
{
}

int ExtensibilityQueryPortTypeWrapper::init()
{
	return AXIS_SUCCESS;
}

int ExtensibilityQueryPortTypeWrapper::fini()
{
	return AXIS_SUCCESS;
}


/*
 * This method invokes the right service method 
 */
int ExtensibilityQueryPortTypeWrapper::invoke(void *pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	const AxisChar *method = mc->getOperationName();
	if (0 == strcmp(method, "query"))
		return query(mc);
	else return AXIS_FAIL;
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service method 
 */
int ExtensibilityQueryPortTypeWrapper::query(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer* pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer* pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("query", "urn:ExtensibilityQuery")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("queryResponse", "urn:ExtensibilityQuery");
	AnyType *v0 = (AnyType*)pIWSDZ->getAnyObject();
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	try
	{
	AnyType *ret = pWs->query(v0);
	return pIWSSZ->addOutputAnyObject(ret);
	}
	catch(...){
	}
}

