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

AxisException::AxisException (int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisException::AxisException (exception* e)
{
    processException (e);
}

AxisException::AxisException (exception* e, int iExceptionCode)
{
    processException (e, iExceptionCode);
}

void AxisException::processException (exception* e, int iExceptionCode)
{
    m_sMessage = getMessage (e) + getMessage (iExceptionCode);
}

void AxisException::processException (exception* e)
{
    m_sMessage = getMessage (e);
}

void AxisException::processException(int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

const string AxisException::getMessage (exception* objException)
{
    string sMessage = objException->what();

    return sMessage;
}

const string AxisException::getMessage (int iExceptionCode)
{
    string sMessage;
    switch(iExceptionCode)
    {
        case SERVER_TESTEXCEPTION:
            sMessage = "This is a testing error";
            break;
        case AXISC_NODEVALUE_MISMATCH_EXCEPTION:
            sMessage = "Cannot deserialize the requested element";
            break;
        default:
            sMessage = "Unknown Exception has occured";

    } 

    return sMessage;

}

AxisException::~AxisException() throw ()
{

}

const char* AxisException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisException::getExceptionCode()
{
    return m_iExceptionCode; 
}

