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
 */
 
#include <axis/OtherFaultException.hpp>

AXIS_CPP_NAMESPACE_START

/*
 * All the methods in this class do a deep copy of the data so that the fault can be
 * processed whatever state the engine is in. Doing a deep copy means this class owns
 * the storage and can delete it in its destructor making client programming simpler.
 */
#define STRINGCOPY(tgt,src)                  \
{                                            \
    delete [] tgt;                           \
    tgt = NULL;                              \
    if (NULL != src && 0 != strlen(src))     \
    {                                        \
        tgt = new AxisChar[strlen(src)+1];   \
        strcpy(tgt, src);                    \
    }                                        \
}

OtherFaultException::
OtherFaultException() : SoapFaultException()
{
    m_detail = NULL;
}

OtherFaultException::
OtherFaultException(const AxisChar *code, const AxisChar *string, const AxisChar *actor, 
                    const AxisChar *detail, int exceptionCode) :
    SoapFaultException(code,string,actor,exceptionCode)
{
    m_detail = NULL;
    STRINGCOPY(m_detail,detail);
}

OtherFaultException::
OtherFaultException(AxisException& ae) : SoapFaultException(ae)
{
    m_detail = NULL;
}

OtherFaultException::
OtherFaultException(const OtherFaultException& copy) : SoapFaultException(copy)
{
    STRINGCOPY(m_detail, copy.m_detail);
}

OtherFaultException& OtherFaultException::
operator=(const OtherFaultException& copy)
{
    SoapFaultException::operator=(copy);
    STRINGCOPY(m_detail, copy.m_detail);
    return *this;
}

OtherFaultException::
~OtherFaultException() throw()
{
    delete [] m_detail;
}

const AxisChar *OtherFaultException::
getFaultDetail() const
{
    return m_detail;
}

void OtherFaultException::
setFaultDetail(const AxisChar *detail)
{
    STRINGCOPY(m_detail,detail);
}

AXIS_CPP_NAMESPACE_END

