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

#include <axis/server/AxisWsddException.h>
#include <exception>
using namespace std;

/**
 *    Default when no parameter passed. When thrown with no parameter
 *    more general AXISC_WSDD_EXCEPTION is assumed.
*/
AxisWsddException::AxisWsddException()
{
    processException(AXISC_WSDD_EXCEPTION);
}

AxisWsddException::AxisWsddException (int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisWsddException::AxisWsddException (exception* e)
{
    processException (e);
}

AxisWsddException::AxisWsddException (exception* e, int iExceptionCode)
{
    processException (e, iExceptionCode);
}

AxisWsddException::~AxisWsddException() throw ()
{

}

