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

SoapAttachment::SoapAttachment(ContentIdSet *pContentIdSet)
{	
	m_AttachmentHeaders = new SoapAttachmentHeaders();
	m_AttachmentBody = 0;
	m_pContentIdSet = pContentIdSet;
	if (NULL!=m_pContentIdSet)
		m_AttachmentHeaders->addHeader(AXIS_CONTENT_ID, pContentIdSet->generateId());
}

SoapAttachment::~SoapAttachment()
{
	delete m_AttachmentHeaders;
	if (m_AttachmentBody) delete m_AttachmentBody;
	m_AttachmentBody =0;
}

void SoapAttachment::addHeader(const char* pchName, const char* pchValue)
{
	// Registering the contentid here ensures that it is unique within the mime message.
	if (NULL!=m_pContentIdSet && 0==strcmp(AXIS_CONTENT_ID,pchName)) 
		m_pContentIdSet->registerId(pchValue);
	m_AttachmentHeaders->addHeader(pchName, pchValue);
}

void SoapAttachment::addBody(xsd__base64Binary* objBody)
{
    iEncodingStyle = AXIS_BASE64;
	m_AttachmentBody = objBody;
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
	m_AttachmentHeaders->serialize(pSZ);

	/* Serialize the Attachment Body */
    if (iEncodingStyle == AXIS_BASE64)
    {
	    if (m_AttachmentBody) {
		    pSZ.serialize("\n", NULL);
		    pSZ.serializeAsChardata(m_AttachmentBody, XSD_BASE64BINARY);
	    }
    } 
    else if (iEncodingStyle == AXIS_BINARY)
    {
        pSZ.serialize("\n", NULL);
        
        
        string attachBody = m_binaryBody;
       
        int boundary = attachBody.find("------=_Part_0_6349096.11054186923",0);
        if (boundary != -1)
        {
            string attachment = attachBody.substr(0,(boundary-1));
            char* binary = new char[attachment.length() + 1];
            strcpy(binary, attachment.c_str());        
             m_binaryBody = binary;            
            pSZ.serialize(m_binaryBody, NULL);
        }
        else              
        pSZ.serialize(m_binaryBody, NULL);
    }

	pSZ.serialize("\n", NULL);
}

xsd__base64Binary* SoapAttachment::getBody()
{
	return m_AttachmentBody;
}

const char* SoapAttachment::getHeader(const char *pchName)
{
	if (m_AttachmentHeaders->getHeader(pchName).empty())
		return "";
	else
		return m_AttachmentHeaders->getHeader(pchName).c_str();
}

const char* SoapAttachment::getAttachmentId()
{
   return getHeader(AXIS_CONTENT_ID);
}

void SoapAttachment::serializeReference(SoapSerializer& pSZ, const char *name)
{
	string data = "<";
	data += name;
	data += " href=\"cid:";
	data += m_AttachmentHeaders->getHeader(AXIS_CONTENT_ID);
	data += "\" />";
	pSZ.serialize(data.c_str());
}

AXIS_CPP_NAMESPACE_END









