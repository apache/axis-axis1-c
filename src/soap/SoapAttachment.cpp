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

/*
 * @author Rangika Mendis (rangika@opensource.lk)
 * @author Nithyakala Thangarajah (nithya@opensource.lk)
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshan@jkcsworld.com)
 *
 */

// SoapAttachment.cpp: implementation of the SoapAttachment class.
//
//////////////////////////////////////////////////////////////////////

#include "SoapAttachment.hpp"
#include "SoapSerializer.h"

AXIS_CPP_NAMESPACE_START

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SoapAttachment::SoapAttachment()
{	
	//Assigning to NULL
	m_AttachementBody = 0;
}

SoapAttachment::~SoapAttachment()
{

}

void SoapAttachment::addHeader(AxisString name, AxisString value)
{
	m_AttachementHeaders.addHeader(name, value);
}

/*
void SoapAttachment::addBody(AxisString sBody)
{
	m_AttachementBody = sBody;
}
*/

void SoapAttachment::addBody(xsd__base64Binary* objBody)
{
	m_AttachementBody = objBody;
}

void SoapAttachment::serialize(SoapSerializer &pSZ)
{
	/* Serialize the Attachment Headers */
	pSZ.serialize("\n", NULL);
	m_AttachementHeaders.serialize(pSZ);

	/* Serialize the Attachment Body */
	//pSZ.serialize("\n", m_AttachementBody.c_str(), NULL);

	if (m_AttachementBody) {
		pSZ.serialize("\n", NULL);
		pSZ.serializeAsChardata(m_AttachementBody, XSD_BASE64BINARY);
	}

	pSZ.serialize("\n", NULL);
}

AXIS_CPP_NAMESPACE_END