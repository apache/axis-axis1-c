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
 
#include <axis/SoapFaultException.hpp>

AXIS_CPP_NAMESPACE_START

/*
 * All the methods in this class do a deep copy of the data so that the fault can be
 * processed whatever state the engine is in. Doing a deep copy means this class owns
 * the storage and can delete it in its destructor making client programming simpler.
 */
#define STRINGCOPY(tgt,src)					\
{											\
	if (NULL != src && 0 != strlen(src))	\
	{										\
		tgt = new AxisChar[strlen(src)+1];	\
		strcpy(tgt, src);					\
	} else tgt = NULL;						\
}

#define STRINGREPLACE(tgt,src)				\
{											\
	if (NULL != tgt)						\
		delete [] tgt;						\
	STRINGCOPY(tgt,src);					\
}

SoapFaultException::SoapFaultException()
{
	m_code = NULL;
	m_sMessage = NULL;
	m_actor = NULL;
	m_iExceptionCode = 0;
}

SoapFaultException::SoapFaultException(
	const AxisChar *code, const AxisChar *string, const AxisChar *actor, int exceptionCode) 
{
	STRINGCOPY(m_code,code);
	STRINGCOPY(m_sMessage,string);
	STRINGCOPY(m_actor,actor);
	m_iExceptionCode = exceptionCode;
}

SoapFaultException::SoapFaultException(AxisException& ae)
{
	STRINGCOPY(m_sMessage,ae.what());
	m_iExceptionCode = ae.getExceptionCode();
	m_code = NULL;
	m_actor = NULL;
}

SoapFaultException::SoapFaultException(const SoapFaultException& copy)
{
	STRINGCOPY(m_code	,copy.m_code);
	STRINGCOPY(m_sMessage	,copy.m_sMessage);
	STRINGCOPY(m_actor	,copy.m_actor);
	m_iExceptionCode = copy.m_iExceptionCode;
}

SoapFaultException& SoapFaultException::operator=(const SoapFaultException& copy)
{
	exception::operator=(copy);
	STRINGREPLACE(m_code	,copy.m_code);
	STRINGREPLACE(m_sMessage	,copy.m_sMessage);
	STRINGREPLACE(m_actor	,copy.m_actor);
	m_iExceptionCode = copy.m_iExceptionCode;
	return *this;
}

SoapFaultException::~SoapFaultException() throw()
{
	if (NULL != m_code) delete [] m_code;
	if (NULL != m_sMessage) delete [] m_sMessage;
	if (NULL != m_actor) delete [] m_actor;
	m_code = NULL;
	m_sMessage = NULL;
	m_actor = NULL;
	m_iExceptionCode = 0;
}


const AxisChar *SoapFaultException::getFaultCode() const
{
	return m_code;
}

const AxisChar *SoapFaultException::getFaultString() const
{
	return m_sMessage;
}

const AxisChar *SoapFaultException::getFaultActor() const 
{
	return m_actor;
}

void SoapFaultException::setFaultCode(const AxisChar *code)
{
	STRINGCOPY(m_code,code);
}

void SoapFaultException::setFaultString(const AxisChar *string)
{
	STRINGCOPY(m_sMessage,string);
}

void SoapFaultException::setFaultActor(const AxisChar *actor)
{
	STRINGCOPY(m_actor,actor);
}


AXIS_CPP_NAMESPACE_END

