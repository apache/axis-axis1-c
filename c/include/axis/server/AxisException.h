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
 
#ifndef __AXISEXCEPTION_H_OF_AXIS_INCLUDED_
#define __AXISEXCEPTION_H_OF_AXIS_INCLUDED_

#include <string>
#include <exception>
#include "SoapFault.h"
using namespace std;

#define TEST_EXCEPTION FAULT_LAST+1
#define RECEPTION_ERROR FAULT_LAST+2
#define SENDING_ERROR FAULT_LAST+3
#define HTTP_ERROR FAULT_LAST+4

#ifdef _DEBUG
#define AXIS_TRY try {
#define AXIS_CATCH(X) } catch (X) { 
#define AXIS_ENDCATCH }
#else
#define AXIS_TRY 
#define AXIS_CATCH(X) 
#define AXIS_ENDCATCH
#endif

class AxisException :public exception
{

  public:
  AxisException(int exceptionCode);
  AxisException(exception* e);
  AxisException(exception* e, int exceptionCode);
  virtual ~AxisException() throw();
  const char* what() const throw();

  private:
    void processException(exception* e);
    void processException(exception* e, int exceptionCode);
    void processException(int e);
    string getMessage(exception* e);
    string getMessage(int e);    
    string m_sMessage;
};

#endif

