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

#include "AxisConfigException.h"

/**
 *    Default when no parameter passed. When thrown with no parameter
 *    more general SERVER_CONFIG_EXCEPTION is assumed.
*/

AXIS_CPP_NAMESPACE_START

AxisConfigException::AxisConfigException(const int iExceptionCode, const char* pcMessage):AxisException(iExceptionCode)
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

AxisConfigException::AxisConfigException (const AxisConfigException& e):AxisException(e)
{}

AxisConfigException::~AxisConfigException() throw ()
{}


string AxisConfigException::getMessageForExceptionCode(const int iExceptionCode)
{
    
	switch(iExceptionCode)
    {
        case SERVER_CONFIG_TRANSPORT_CONF_FAILED:
            m_sMessageForExceptionCode = "AxisConfigException:Transport layer is not"\
                " configured properly";
            break;
        case SERVER_CONFIG_LIBRARY_PATH_EMPTY:
            m_sMessageForExceptionCode = "AxisConfigException:Library path is empty(Not in" \
                " server.wsdd file)";
            break;
        case CONFIG_DEFAULTS_ALREADY_SET:
            m_sMessageForExceptionCode = "AxisConfigException:configuration defaults "\
                " have already been set";
            break;
        default:
            m_sMessageForExceptionCode = "AxisConfigException:Unknown Axis C++" \
                " Configuration Exception";
    }
    return m_sMessageForExceptionCode;
}

AXIS_CPP_NAMESPACE_END
