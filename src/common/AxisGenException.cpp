/* -*- C++ -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

#include "AxisGenException.h"
#include <exception>

AXIS_CPP_NAMESPACE_START

//using namespace std;

AxisGenException::AxisGenException(const int iExceptionCode, const char* pcMessage):AxisException(iExceptionCode,pcMessage)
{
	std::string sMessage = "";
	if (pcMessage) 
	{
		sMessage = string(pcMessage);
		getMessageForExceptionCode(iExceptionCode);
		m_sMessageForExceptionCode = getMessageForExceptionCode(iExceptionCode) + " " + sMessage;
		setMessage(m_sMessageForExceptionCode.c_str());

	}
	else
		setMessage(getMessageForExceptionCode(iExceptionCode).c_str());
}

AxisGenException::AxisGenException (const AxisGenException& e):AxisException(e)
{}

AxisGenException::~AxisGenException() throw ()
{}

string AxisGenException::getMessageForExceptionCode (const int iExceptionCode)
{
    
	switch(iExceptionCode)
    {
        case AXISC_SERVICE_THROWN_EXCEPTION:
            m_sMessageForExceptionCode = "A service has thrown an exception. see detail ";
            break;

        case SERVER_TEST_EXCEPTION:
            m_sMessageForExceptionCode = "This is a testing error ";
            break;

        case AXISC_NODE_VALUE_MISMATCH_EXCEPTION:
            m_sMessageForExceptionCode = "Cannot deserialize the requested element ";
            break;

        default:
            m_sMessageForExceptionCode =  "";

    }
    return m_sMessageForExceptionCode;
}



AXIS_CPP_NAMESPACE_END
