/* -*- C++ -*- */
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
 * @author  Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

#include <axis/server/AxisException.h>
#include <exception>
using namespace std;

AxisException::AxisException (int exceptionCode)
{
    processException (exceptionCode);
}

AxisException::AxisException (exception* e)
{
    processException (e);
}

AxisException::AxisException (exception* e, int exceptionCode)
{
    processException (e);
}

void AxisException::processException (exception* e, int exceptionCode)
{
    m_sMessage = getMessage (e) + getMessage (exceptionCode);
}

void AxisException::processException (exception* e)
{
    m_sMessage = getMessage (e);
}

void AxisException::processException (int exceptionCode)
{
    m_sMessage = getMessage (exceptionCode);
}

string AxisException::getMessage (exception* e)
{
    string sMessage = "to do";
    /* to do */
/*  exception *objType = static_cast<std::bad_alloc*> (e);
  if(objType != NULL)
  {
    sMessage = "thrown by new";
  }

  objType = static_cast<std::bad_cast*> (e);
  if(objType != NULL)
  {
    sMessage = "thrown by dynamic_cast when fails with a referenced type";
  }

  objType = static_cast<bad_exception*> (e);
  if(objType != NULL)
  {
    sMessage = "thrown when an exception doesn't match any catch";
  }

  objType = static_cast<bad_typeid*> (e);
  if(objType != NULL)
  {
    sMessage = "thrown by typeid";
  }
*/

    return sMessage;
}

string AxisException::getMessage (int e)
{
    const char* sMessage = NULL;
    SoapFault* objSoap = SoapFault::getSoapFault (e);
    //following is not the proper thing to do. but a temporary solution
    if (objSoap)
    {
        sMessage = objSoap->getSoapString ();
        delete objSoap;
    }

    if (sMessage == NULL)
    {
        switch (e)
        {
            case TEST_EXCEPTION:
                sMessage = "Axis test exception";
            case RECEPTION_ERROR:
                sMessage = "Exception on receiving the message";
            case SENDING_ERROR:
                sMessage = "Exception on sending the message";
            case HTTP_ERROR:
                sMessage = "HTTP Error, cannot process response message...";
            default:
                sMessage = "Undefined exception";
        }
    }

    return sMessage;

}

AxisException::~AxisException() throw ()
{

}

const char* AxisException::what() const throw ()
{
    return m_sMessage.c_str ();
}
