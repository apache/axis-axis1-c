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


// SoapAttachment.h: interface for the SoapAttachment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPATTACHMENT_H__7E7B50DC_21AF_4C6E_83E0_F77985A38E43__INCLUDED_)
#define AFX_SOAPATTACHMENT_H__7E7B50DC_21AF_4C6E_83E0_F77985A38E43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <axis/GDefine.hpp>
#include <axis/AxisUserAPI.hpp>
#include "SoapAttachementHeaders.hpp"

#include <string>
using namespace std;

AXIS_CPP_NAMESPACE_START

class SoapSerializer;

class SoapAttachment
{
private:
	SoapAttachementHeaders m_AttachementHeaders;
	xsd__base64Binary* m_AttachementBody;
public:
	
	void serialize(SoapSerializer& pSZ);
	void addBody(xsd__base64Binary* objBody);	
	void addHeader(AxisString name, AxisString value);
	SoapAttachment();
	virtual ~SoapAttachment();	
};

AXIS_CPP_NAMESPACE_END
#endif // !defined(AFX_SOAPATTACHMENT_H__7E7B50DC_21AF_4C6E_83E0_F77985A38E43__INCLUDED_)
