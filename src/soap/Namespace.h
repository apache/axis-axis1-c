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
 *  @class Namespace
 *  @brief interface for the Namespace class.
 *
 *
 *
 *  @author Roshan Weerasuriya (roshan@opensource.lk, roshan@jkcsworld.com, roshan_444@yahoo.com)
 */

#if !defined(AFX_NAMESPACE_H__9B3E8218_FB18_4AE0_B88E_899B0A01549D__INCLUDED_)
#define AFX_NAMESPACE_H__9B3E8218_FB18_4AE0_B88E_899B0A01549D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <axis/AxisUserAPI.hpp>
#include <axis/INamespace.hpp>
#include <string>
#include <list>

AXIS_CPP_NAMESPACE_START
using namespace std;

class SoapSerializer;

class Namespace : public INamespace
{
public:
	int serialize(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack);
	const AxisChar* getPrefix();
	const AxisChar* getURI();
	void setURI(const AxisChar* achURI);
	void setPrefix(const AxisChar* achPrefix);
	Namespace(const AxisChar* achPrefix, const AxisChar* achURI);
	Namespace();
	virtual ~Namespace();

private:
	AxisString m_asPrefix;
	AxisString m_asURI;

};

AXIS_CPP_NAMESPACE_END

#endif // !defined(AFX_NAMESPACE_H__9B3E8218_FB18_4AE0_B88E_899B0A01549D__INCLUDED_)
