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
	AxisString sMessage = "";
	if (pcMessage) 
	{
		sMessage = pcMessage;
	}
	m_sMessage = getMessageForExceptionCode(m_iExceptionCode) + " " + sMessage;
}

AxisConfigException::AxisConfigException (const AxisConfigException& e):AxisException(e)
{}

AxisConfigException::~AxisConfigException() throw ()
{}


const string AxisConfigException::getMessageForExceptionCode(const int iExceptionCode)
{
    switch(iExceptionCode)
    {
        case SERVER_CONFIG_TRANSPORT_CONF_FAILED:
            m_sMessage = "AxisConfigException:Transport layer is not" \
                " configured properly";
            break;
        case SERVER_CONFIG_LIBRARY_PATH_EMPTY:
            m_sMessage = "AxisConfigException:Library path is empty(Not in" \
                " server.wsdd file)";
            break;
        default:
            m_sMessage = "AxisConfigException:Unknown Axis C++" \
                " Configuration Exception";
    }
    return m_sMessage;
}

AXIS_CPP_NAMESPACE_END
