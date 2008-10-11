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


// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"


#include "SoapAttachmentHeaders.hpp"
#include "SoapSerializer.h"

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START


SoapAttachmentHeaders::SoapAttachmentHeaders()
{
}

SoapAttachmentHeaders::~SoapAttachmentHeaders()
{
}

void SoapAttachmentHeaders::addHeader(AxisString name, AxisString value)
{
	bool found = false;
	for (unsigned int i = 0; i < m_AttachHeaders.size (); i++)
	{
		if (m_AttachHeaders[i].first == name)
		{
			m_AttachHeaders[i] = make_pair(name, value);
			found = true;
			break;
		}
	}

	if (!found)
		m_AttachHeaders.push_back (make_pair (name, value));
}

void SoapAttachmentHeaders::serialize(SoapSerializer &pSZ)
{
	for (unsigned int i = 0; i < m_AttachHeaders.size (); i++)
	{
	    if (m_AttachHeaders[i].first == AXIS_CONTENT_ID)
	    {
			pSZ.serialize((m_AttachHeaders[i].first).c_str(), ": <", NULL);
			pSZ.serialize((m_AttachHeaders[i].second).c_str(), ">\r\n", NULL);
		} else {
			pSZ.serialize((m_AttachHeaders[i].first).c_str(), ": ", NULL);
			pSZ.serialize((m_AttachHeaders[i].second).c_str(), "\r\n", NULL); 
		}
	}
}

const char *SoapAttachmentHeaders::getHeader(AxisString sName)
{

	for (unsigned int i = 0; i < m_AttachHeaders.size (); i++)
	{
		if (m_AttachHeaders[i].first == AXIS_CONTENT_ID)
		{
			return m_AttachHeaders[i].second.c_str();
		}
	}

	return "";
}

AXIS_CPP_NAMESPACE_END


