/*
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * MathOps.h: interface for the MathOpsclass.
 *
 */
#if !defined(__MATHOPS_CLIENTSTUB_H__INCLUDED_)
#define __MATHOPS_CLIENTSTUB_H__INCLUDED_

#include <axis/client/Call.h>
/*include Exception header files here*/
#include "AxisDivByZeroException.h"
#include "DivByZeroStruct.h"

/** This class is used to demonstrate error handling and fault mapping 
  * testing. Here I have generated the stuff using MathOps.wsdl. This wsdl
  * simply have a complex type which consists of three simple types(xsd:int,
  * xsd:foat and xsd:string). For portType operation div we have a fault named
  * DivByZero the message for which is DivByZeroFault which is of the complex
  * type mentioned above(DivByZeroStruct). The server side for this client sample
  * is in $AXISCPP_HOME/samples/server/rpcfault.
  * When you generated the client side it will generate header and implementation
  * files for four different types, namely,
  * MathOps: Service request class which calls div service method in the server
  *          and getFaultDetails if there's any.
  * DivByZeroStruct: The type corresponding to the complex type DivByZeroStruct
  *                  in the MathOps.wsdl
  * AxisDivByZeroException: For each fault in wsdl we generate an exception
  * class which is derived from AxisException base class which is the root class
  * for exceptions in Axis C++. This root class in tern is derived from std::exception.
  * In the server side if division by zero fault is encountered in the service method
  * it will call
  * pIWSSZ->createSoapFault("DivByZeroStruct", "http://soapinterop.org/wsdl");
  * where pIWSSZ is the soap serializer interface.
  * Once this method is called 
  * m_pSoapEnvelope->m_pSoapBody->m_pSoapFault is assigned a new soap fault object.
  * After that,
  * DivByZeroStruct* pObjFault = new DivByZeroStruct();
  * pObjFault->varString = "Division by zero exception";
  * pObjFault->varInt = 1;
  * pObjFault->varFloat = 10.52;
  * if (pObjFault)
  *     pIWSSZ->addFaultDetail(pObjFault, (void*) Axis_Serialize_DivByZeroStruct,
  *     (void*) Axis_Delete_DivByZeroStruct,"DivByZero", Axis_URI_DivByZeroStruct);
  * 
  * Here the service developer fills the  DivByZeroStruct with appropriate values and
  * call soap serialzers addFaultDetail method with the knowledge of serializing
  * and deserializing. Once this method is called setFaultDetail method of SoapFault
  * is called from SoapSerializer.
  * 
  * int SoapFault::setFaultDetail(const Param* pFaultDetail)
  * {
  *     m_pFaultDetail = (Param*) pFaultDetail;
  *     return AXIS_SUCCESS;
  * }
  * 
  * So once the serialize method of SoapSerializer is called the in addition to
  * serializing Faultcode, Faultstring and Faultactor SoapFault's FaultDetail
  * object is also serialized into the soap body's fault detail tag.
  * So in the wire comes the Soap message with a soap fault.
  * 
  * Now when you run the client here, if it catch an exception 
  * catch(AxisException& e)
  * {
  *     int iExceptionCode = e.getExceptionCode();
  *     if(AXISC_NODE_VALUE_MISMATCH_EXCEPTION != iExceptionCode)
  *     {
  *         throw;
  *     }
  * ...
  * ...
  * it checks the exception code and if exception code is not equal to
  * AXISC_NODE_VALUE_MISMATCH_EXCEPTION value it means that the exception
  * thrown not because of a soap fault. Exception is caused by some other
  * mean in the client side. If a soap fault comes in the wire SoapDeseriazers 
  * checkMessageBody  method throws and exception
  * throw AxisException(AXISC_NODE_VALUE_MISMATCH_EXCEPTION);
  * When we catch that exception we knows that a soap fault has come.
  *
  * 
  *                                                                                             
  * 
  *         
  * 
  */



class MathOps 
{
private:
	Call* m_pCall;
public:
	MathOps(const char* pchEndpointUri);
public:
	virtual ~MathOps();
public: 
	int div(int Value0,int Value1);
	int getStatus();
	int getFaultDetail(char** ppcDetail);
};

#endif /* !defined(__MATHOPS_CLIENTSTUB_H__INCLUDED_)*/
