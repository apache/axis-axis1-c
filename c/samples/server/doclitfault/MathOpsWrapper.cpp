///////////////////////////////////////////////////////////////////////
//This is the Service implementation CPP file genarated by theWSDL2Ws.
//		MathOpsWrapper.cpp: implemtation for the MathOpsWrapper.
//
//////////////////////////////////////////////////////////////////////

#include "MathOpsWrapper.h"

extern int Axis_DeSerialize_DivByZeroFault(DivByZeroFault* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_DivByZeroFault(bool bArray = false, int nSize=0);
extern void Axis_Delete_DivByZeroFault(DivByZeroFault* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_DivByZeroFault(DivByZeroFault* param, IWrapperSoapSerializer& pSZ, bool bArray = false);
extern int Axis_GetSize_DivByZeroFault();

MathOpsWrapper::MathOpsWrapper()
{
	pWs = new MathOps();
}

MathOpsWrapper::~MathOpsWrapper()
{
	delete pWs;
}

//implementation of WrapperClassHandler interface
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


/////////////////////////////////////////////////////////////////
// This method invokes the right service method 
//////////////////////////////////////////////////////////////////
int MathOpsWrapper::invoke(void* pMsg)
{
        IMessageData* mc = (IMessageData*)pMsg;
	const AxisChar *method = mc->getOperationName();
	if (0 == strcmp(method, "div"))
		return div(mc);
	else return AXIS_FAIL;
}


//Methods corresponding to the web service methods

/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
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
        if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("div", "http://soapinterop.org/types")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("divResponse", "http://soapinterop.org/types");
        int v0 = pIWSDZ->getElementAsInt("in0",0);
        int v1 = pIWSDZ->getElementAsInt("in1",0);
        if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	 try
        {
            ret = pWs->div(v0,v1);
        }
        catch(AxisDivByZeroException& e)
        {
            pIWSSZ->createSoapFault("SOAPStructFault", "http://soapinterop.org/");
            DivByZeroFault* pObjFault = new DivByZeroFault();
            pObjFault->varString = "Division by zero exception";
            pObjFault->varInt = 1;
            pObjFault->varFloat = 10.52;
                                                                                                                                             
            if(pObjFault)
                pIWSSZ->addFaultDetail(pObjFault, (void*)Axis_Serialize_DivByZeroFault,
                    (void*)Axis_Delete_DivByZeroFault, "DivByZeroException",
                    Axis_URI_DivByZeroFault);
                                                                                                                                             
            throw;
        }
        return pIWSSZ->addOutputParam("divReturn", (void*)&ret, XSD_INT);
}

