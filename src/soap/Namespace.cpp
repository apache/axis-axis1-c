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
 */

/**
 *  @author Roshan Weerasuriya (roshan@opensource.lk, roshan@jkcsworld.com, roshan_444@yahoo.com)
 */

#include "Namespace.h"
#include "SoapSerializer.h"

AXIS_CPP_NAMESPACE_START

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Namespace::Namespace()
{

}

Namespace::~Namespace()
{

}

Namespace::Namespace(const AxisChar* achPrefix, const AxisChar* achURI)
{
	m_asPrefix = achPrefix;
	m_asURI = achURI;
}

void Namespace::setPrefix(const AxisChar* achPrefix)
{
	m_asPrefix = achPrefix;
}

void Namespace::setURI(const AxisChar* achURI)
{
	m_asURI = achURI;
}

const AxisChar* Namespace::getURI()
{
	return m_asURI.c_str();
}

const AxisChar* Namespace::getPrefix()
{
	return m_asPrefix.c_str();
}

int Namespace::serialize(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack)
{
	/*Adding the new namespace to the Serializer*/
	pSZ.addNamespaceToNamespaceList(m_asURI.c_str(), m_asPrefix.c_str());
	/*Adding the namespace to the temporary stack, so that it will be removed
	*  at the end of the logical block. The logical block could be a HeaderBlock,
	*  a Soap Method etc.
	*/
	lstTmpNameSpaceStack.push_back((AxisChar*)m_asURI.c_str());

	pSZ.serialize(" xmlns:", m_asPrefix.c_str(), "=\"", m_asURI.c_str(), "\"", NULL);

	return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END
