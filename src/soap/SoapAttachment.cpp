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
	m_AttachementHeaders = new SoapAttachementHeaders();
	m_AttachementBody = 0;
}

SoapAttachment::~SoapAttachment()
{
	delete m_AttachementHeaders;
	m_AttachementHeaders =0;

	delete m_AttachementBody;
	m_AttachementBody =0;
}

void SoapAttachment::addHeader(const char* pchName, const char* pchValue)
{
	m_AttachementHeaders->addHeader(pchName, pchValue);
}

void SoapAttachment::addBody(xsd__base64Binary* objBody)
{
    iEncodingStyle = AXIS_BASE64;
	m_AttachementBody = objBody;
}

void SoapAttachment::addBody(char* pchBinaryBody)
{ 
    iEncodingStyle = AXIS_BINARY;
    m_binaryBody = new char[strlen(pchBinaryBody) + 1];
    strcpy(m_binaryBody,pchBinaryBody);

}

void SoapAttachment::serialize(SoapSerializer &pSZ)
{
	/* Serialize the Attachment Headers */
	pSZ.serialize("\n", NULL);
	m_AttachementHeaders->serialize(pSZ);

	/* Serialize the Attachment Body */
    if (iEncodingStyle == AXIS_BASE64)
    {
	    if (m_AttachementBody) {
		    pSZ.serialize("\n", NULL);
		    pSZ.serializeAsChardata(m_AttachementBody, XSD_BASE64BINARY);
	    }
    } 
    else if (iEncodingStyle == AXIS_BINARY)
    {
        pSZ.serialize("\n", NULL);
        pSZ.serialize(m_binaryBody, NULL);
    }

	pSZ.serialize("\n", NULL);
}

xsd__base64Binary* SoapAttachment::getBody()
{
	return m_AttachementBody;
}

const char* SoapAttachment::getHeader(const char *pchName)
{
	if (m_AttachementHeaders->getHeader(pchName).empty())
		return "";
	else
		return m_AttachementHeaders->getHeader(pchName).c_str();
}

const char* SoapAttachment::getAttachmentId()
{
   return getHeader("Content-Id");
}

AXIS_CPP_NAMESPACE_END









