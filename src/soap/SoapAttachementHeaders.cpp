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

// SoapAttachementHeaders.cpp: implementation of the SoapAttachementHeaders class.

//

//////////////////////////////////////////////////////////////////////

#include "SoapAttachementHeaders.hpp"
#include "SoapSerializer.h"

AXIS_CPP_NAMESPACE_START

//////////////////////////////////////////////////////////////////////

// Construction/Destruction

//////////////////////////////////////////////////////////////////////

SoapAttachementHeaders::SoapAttachementHeaders()
{
}

SoapAttachementHeaders::~SoapAttachementHeaders()
{
}

void SoapAttachementHeaders::addHeader(AxisString name, AxisString value)
{
	m_AttachHeaders.push_back (make_pair (name, value));
}

void SoapAttachementHeaders::serialize(SoapSerializer &pSZ)
{

	for (unsigned int i = 0; i < m_AttachHeaders.size (); i++)
	{
	    if (m_AttachHeaders[i].first == "Content-Id")
	    {
			pSZ.serialize((m_AttachHeaders[i].first).c_str(), ": <", NULL);
			pSZ.serialize((m_AttachHeaders[i].second).c_str(), ">\n", NULL);
		} else {
			pSZ.serialize((m_AttachHeaders[i].first).c_str(), ":", NULL);
			pSZ.serialize((m_AttachHeaders[i].second).c_str(), "\n", NULL); 
		}
	}
}

AxisString SoapAttachementHeaders::getHeader(AxisString sName)
{

	for (unsigned int i = 0; i < m_AttachHeaders.size (); i++)
	{
		if (m_AttachHeaders[i].first == "Content-Id")
		{
			return m_AttachHeaders[i].second;
		}
	}

	return "";
}

AXIS_CPP_NAMESPACE_END
