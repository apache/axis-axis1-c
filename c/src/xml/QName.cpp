/* -*- C++ -*- */
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
 *
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 *
 */

// QName.cpp: implementation of the QName class.
//
//////////////////////////////////////////////////////////////////////

#include "QName.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

QName::QName()
{
	uri = 0;
	localname = 0;
}

QName::~QName()
{

}

void QName::SplitQNameString(const XML_Ch* qname, XML_Ch sep)
{
	XML_Ch *p = const_cast<XML_Ch*>(qname);
	while (*p)
	{
		if (*p == sep)
		{
			*p = '\0'; //put null to separate local name from namespace
			localname = ++p; //now p points to localpart
			uri = qname; //qname points to uri
			return; 
		}
		p++;
	}
	//if there is no separator that means there is no uri
	localname = qname;
	uri = 0; //no uri
}

void QName::MergeQNameString(XML_Ch sep)
{
	if (uri)
	{
		XML_Ch* p = const_cast<XML_Ch*>(localname);
		*(--p) = sep;
	}
}
