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

#if !defined(__MATHOPS_CLIENTSTUB_H__INCLUDED_)
#define __MATHOPS_CLIENTSTUB_H__INCLUDED_

#include <axis/client/Call.h>
/*include Exception header files here*/
#include "AxisDivByZeroException.h"
#include "DivByZeroStruct.h"

/**
  * @class MathOps.h
  * @brief A test class for exception and fault mapping.
  *
  * This class is used to demonstrate error handling and fault mapping 
  * testing. Here I have generated the stuff using MathOps.wsdl. This wsdl
  * simply have a complex type which consists of three simple types(xsd:int,
  * xsd:foat and xsd:string). For portType operation "div" we have a fault named
  * DivByZero the message for which is DivByZeroFault which is of the complex
  * type mentioned above(DivByZeroStruct). The server side for this client
  * sample is in $AXISCPP_HOME/samples/server/rpcfault.
  * When you generated the client side it will generate header and
  * implementation files for three different types, namely,
  * MathOps: Service request class which calls div service method in the server
  *     and getFaultDetails if there's any.
  * DivByZeroStruct: The type corresponding to the complex type DivByZeroStruct
  *     in the MathOps.wsdl
  * AxisDivByZeroException: For each fault in wsdl we generate an exception
  *     class which is derived from AxisException base class which is the root
  *     class for exceptions in Axis C++. This root class in tern is derived
  *     from std::exception. 
  * In the server side if division by zero fault is encountered
  * in the service method it will call
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
  * pObjFault->varString = "Division by zero exception";
  * pObjFault->varInt = 1;
  * pObjFault->varFloat = 10.52;
  * if (pObjFault)
  *  pIWSSZ->addFaultDetail(pObjFault, (void*) Axis_Serialize_DivByZeroStruct,
  *  (void*) Axis_Delete_DivByZeroStruct,"DivByZero", Axis_URI_DivByZeroStruct);
  * 
  * Here the service developer fills the  DivByZeroStruct with appropriate
  * values and call SoapSerialzer's addFaultDetail method with the knowledge
  * of serializing and deserializing. Once this method is called setFaultDetail
  * method of SoapFault is called from SoapSerializer.
  * ...
  * ...
  * int SoapFault::setFaultDetail(const Param* pFaultDetail)
  * {
  *     m_pFaultDetail = (Param*) pFaultDetail;
  *     return AXIS_SUCCESS;
  * }
  * ...
  * ...
  * 
  * So once the serialize method of SoapSerializer is called then in addition to
  * serializing Faultcode, Faultstring and Faultactor, SoapFault's FaultDetail
  * object is also serialized into the soap body's fault detail tag.
  * So in the wire comes the Soap message with a soap fault.
  * 
  * Now when you run the client here, if it catch an exception 
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
  * it checks the exception code and if exception code is not equal to
  * AXISC_NODE_VALUE_MISMATCH_EXCEPTION value it means that the exception
  * thrown not because of a soap fault. Exception is caused by some other
  * mean in the client side. If a soap fault comes in the wire SoapDeseriazer's 
  * checkMessageBody  method throws and exception
  * ...
  * ...
  * throw AxisException(AXISC_NODE_VALUE_MISMATCH_EXCEPTION);
  * ...
  * ...
  *
  * When we catch that exception we knows that a soap fault has come.
  * ...
  * ...
  * else if (AXIS_SUCCESS == m_pCall->checkFault("Fault",
  *     "http://localhost/axis/MathOps" ))
  *      //Exception handling code goes here
  *  {
  *      cFaultcode = m_pCall->getElementAsString("faultcode", 0);
  *      cFaultstring = m_pCall->getElementAsString("faultstring", 0);
  *      cFaultactor = m_pCall->getElementAsString("faultactor", 0);
  *      if(0 == strcmp("DivByZeroStruct", cFaultstring))
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
  *              char* temp = pFaultDetail->varString;
  *              printf("%s\n", temp);
  *              printf("faultcode:%s\n", cFaultcode);
  *              printf("faultstring:%s\n", cFaultstring);
  *              printf("faultactor:%s\n", cFaultactor);
  *              m_pCall->unInitialize();
  *              throw AxisDivByZeroException(pFaultDetail);
  *          }
  *      }
  * ...
  * ...
  * Note that we compares cFaultstring which contains soap fault's faultstring 
  * with the DivByZeroStruct. This is so because in the server side we set the 
  * faultstring to take the fault's generated type name. If the faultdetail
  * is just a simple string
  * ...
  * ...
  * else
  * {
  *     cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
  *     throw AxisException(cFaultdetail);
  * }
  * ...
  * ...
  *
  * You can also use this class as a test utility to test exceptions. You
  * can generate exception in the server side and client side and test
  * from here whether the correct exception messages come to the client.
  * For example you can remove the shared libraries for MathOps service
  * (libmathops.so) from $AXIS_HOME/webservices folder and try to run
  * client here. The you will get an exception message like "Service library
  * is not loaded to the engine".
  * 
  * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
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
