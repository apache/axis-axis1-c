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
 */


//////////////////////////////////////////////////////////////////////
// StartElement.cpp: implementation of the StartElement class.
//
//////////////////////////////////////////////////////////////////////

#include "StartElement.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace axisxml {

StartElement::StartElement()
{

}

StartElement::~StartElement()
{
	for (list<Attribute*>::iterator it = m_Attributes.begin(); it != m_Attributes.end(); it++)
	{
		delete *it;
	}
}

}

