/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains Client Stub Class for remote web service 
 */

#if !defined(__MATHOPS_CLIENTSTUB_H__INCLUDED_)
#define __MATHOPS_CLIENTSTUB_H__INCLUDED_

#include <axis/client/Stub.h>
/*include Exception header files here*/
#include "DivByZeroStruct.h"
#include "SpecialDetailStruct.h"
#include "OutOfBoundStruct.h"
#include "AxisClientException.h"

/**
  * @class MathOps.h
  * @brief A test class for fault mapping.
  *
  * This class is used to demonstrate fault mapping
  * testing. Here I have generated the stuff using FaultMapping.wsdl. This wsdl
  * simply have several complex types. One such type is DivByZeroStruct which 
  * consists of three simple types(xsd:int,* xsd:foat and xsd:string). 
  * For portType operation "div" we have a fault named
  * DivByZero the message for which is DivByZeroFault which is of the complex
  * type mentioned above(DivByZeroStruct). The server side for this client
  * sample is in $AXISCPP_HOME/tests/server/exceptionTest.
  * When you generated the client side it will generate header and
  * implementation files for the following
  *
  * MathOps: Service request class which calls div service method in the server
  *     and getFaultDetails if there's any.
  *
  * DivByZeroStruct: The type corresponding to the complex type DivByZeroStruct
  *     in the MathOps.wsdl
  *
  * OutOfBoundStruct: The type corresponding to the complex type OutOfBoundStruct
  *     in the MathOps.wsdl
  *
  * SpecialDetailStruct:The type corresponding to the complex type SpecialDetailStruct
  *     in the MathOps.wsdl
  *
  * AxisDivByZeroException: For each fault in wsdl we generate an exception
  *     class which is derived from AxisException base class which is the root
  *     class for exceptions in Axis C++. This root class in tern is derived
  *     from std::exception. AxisDivByzeroException is the exception type
  *     corresponding to DivByZero fault.
  *
  * AxisOutOfBountException: Exception type corresponding to OutOfBound fault.
  *
  * AxisNormalDetailException: Exception type corresponding to NormalDetail fault.
  *
  * In the server side if division by zero fault is encountered
  * in the service method it will call
  * <PRE>
  * ...
  * ...
  * pIWSSZ->createSoapFault("DivByZeroStruct", "http://soapinterop.org/wsdl");
  * ...
  * ...
  * where pIWSSZ is the soap serializer interface.
  * Once this method is called
  * m_pSoapEnvelope->m_pSoapBody->m_pSoapFault is assigned a new soap fault
  * object. After that,
  *
  * DivByZeroStruct* pObjFault = new DivByZeroStruct();
  *  //User may write code here to fill the struct
  * pObjFault->varString = "Division by zero exception";
  * pObjFault->varInt = 1;
  * pObjFault->varFloat = 10.52;
  * if (pObjFault)
  *  pIWSSZ->addFaultDetail(pObjFault, (void*) Axis_Serialize_DivByZeroStruct,
  *  (void*) Axis_Delete_DivByZeroStruct,"DivByZero", Axis_URI_DivByZeroStruct);
  *  ...
  *  ...
  * </PRE>
  * Here the service developer fills the  DivByZeroStruct with appropriate
  * values and call SoapSerialzer's addFaultDetail method with the knowledge
  * of serializing and deserializing. Once this method is called setFaultDetail
  * method of SoapFault is called from SoapSerializer.
  * <PRE>
  * ...
  * ...
  * int SoapFault::setFaultDetail(const Param* pFaultDetail)
  * {
  *     m_pFaultDetail = (Param*) pFaultDetail;
  *     return AXIS_SUCCESS;
  * }
  * ...
  * ...
  * </PRE>
  *
  * So once the serialize method of SoapSerializer is called then in addition to
  * serializing Faultcode, Faultstring and Faultactor, SoapFault's FaultDetail
  * object is also serialized into the soap body's fault detail tag.
  * So in the wire comes the Soap message with a soap fault.
  *
  * Now when you run the client here, if it catch an exception
  * <PRE>
  * ...
  * ...
  * catch(AxisException& e)
  * {
  *     int iExceptionCode = e.getExceptionCode();
  *     if(AXISC_NODE_VALUE_MISMATCH_EXCEPTION != iExceptionCode)
  *     {
  *         throw;
  *     }
  * ...
  * ...
  * </PRE>
  * it checks the exception code and if exception code is not equal to
  * AXISC_NODE_VALUE_MISMATCH_EXCEPTION value it means that the exception
  * thrown not because of a soap fault. Exception is caused by some other
  * mean in the client side. If a soap fault comes in the wire SoapDeseriazer's
  * checkMessageBody  method throws and exception
  * <PRE>
  * ...
  * ...
  * throw AxisGenException(AXISC_NODE_VALUE_MISMATCH_EXCEPTION);
  * ...
  * ...
  *</PRE>
  *
  * When we catch that exception we knows that a soap fault has come.
  * <PRE>
  * ...
  * ...
  * else if (AXIS_SUCCESS == m_pCall->checkFault("Fault",
  *     "http://localhost/axis/MathOps" ))
  *      //Exception handling code goes here
  *  {
  *      cFaultcode = m_pCall->getElementAsString("faultcode", 0);
  *      cFaultstring = m_pCall->getElementAsString("faultstring", 0);
  *      cFaultactor = m_pCall->getElementAsString("faultactor", 0);
  * ...
  * ...
  *      else if(0 == strcmp("DivByZeroStruct", cFaultstring))
  *      {
  *          if (AXIS_SUCCESS == m_pCall->checkFault("faultdetail",
  *              "http://localhost/axis/MathOps"))
  *          {
  *              DivByZeroStruct* pFaultDetail = NULL;
  *              pFaultDetail = (DivByZeroStruct*)m_pCall->
  *                  getCmplxObject((void*) Axis_DeSerialize_DivByZeroStruct,
  *                  (void*) Axis_Create_DivByZeroStruct,
  *                  (void*) Axis_Delete_DivByZeroStruct,"faultstruct1", 0);
  *              //Client developers code goes here to handle the struct can
  *              //be inserted here
  *              printf("faultcode:%s\n", cFaultcode);
  *              printf("faultstring:%s\n", cFaultstring);
  *              printf("faultactor:%s\n", cFaultactor);
  *              m_pCall->unInitialize();
  *              throw AxisDivByZeroException(pFaultDetail);
  *          }
  *      }
  * ...
  * ...
  * </PRE>
  *
  * Note that we compares cFaultstring which contains soap fault's faultstring
  * with the DivByZeroStruct. This is so because in the server side we set the
  * faultstring to take the fault's generated type name. If the faultdetail
  * is just a simple string
  * <PRE>
  * ...
  * ...
  * else
  * {
  *     cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
  *     throw AxisGenException(cFaultdetail);
  * }
  * ...
  * ...
  * </PRE>
  *
  * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
  */

class MathOps :public Stub
{
public:
	MathOps(const char* pchEndpointUri, AXIS_PROTOCOL_TYPE eProtocol=APTHTTP);
	MathOps();
public:
	virtual ~MathOps();
public: 
	int div(int Value0,int Value1);
	int getFaultDetail(char** ppcDetail);
};

#endif /* !defined(__MATHOPS_CLIENTSTUB_H__INCLUDED_)*/
