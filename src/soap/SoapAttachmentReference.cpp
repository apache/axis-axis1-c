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

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include "SoapAttachmentReference.hpp"
#include "SoapSerializer.h"
#include "Attribute.h"

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START

SoapAttachmentReference::SoapAttachmentReference(SoapAttachment *att)
{	
	m_attachment = att;
}

SoapAttachmentReference::~SoapAttachmentReference() {}

void SoapAttachmentReference::serialize(SoapSerializer& pSZ, const char *name)
{
	string data = "<";
	data += name;
	if (NULL==m_attachment->getBody())
		data += " xsi:nil=\"true\"";
	else
	{
		data += " href=\"cid:";
		data += m_attachment->getHeader(AXIS_CONTENT_ID);
		data += "\"";
	}
	pSZ.serialize(data.c_str(), NULL);

	list<Attribute*>::iterator it = m_attributes.begin();
	while (it != m_attributes.end())
	{
		pSZ.serialize("\r\n  ",NULL);
		(*it)->serialize(pSZ);
		it++;
	}
	pSZ.serialize("/>\r\n",NULL);
}

void SoapAttachmentReference::addAttributes(IAttribute **attributes, int nAttributes)
{
	if (0==nAttributes || NULL==attributes) return;
	for (int i=0; i<nAttributes; i++)
		if (NULL!=attributes[i]) 
			m_attributes.push_back(static_cast<Attribute*>(attributes[i]));

	return;
}

AXIS_CPP_NAMESPACE_END









