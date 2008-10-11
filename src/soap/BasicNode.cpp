/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"


#include <axis/BasicNode.hpp>

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START

BasicNode::BasicNode():m_pachValue(NULL)
{}

BasicNode::BasicNode(const AxisChar* pachValue, NODE_TYPE eNodeType):m_iNodeType(eNodeType), m_pachValue(NULL)
{
    if(pachValue) {
        m_pachValue = new char[strlen(pachValue)+1];
        strcpy(m_pachValue,pachValue);
    }

}

BasicNode::BasicNode(const BasicNode& rCopy):m_iNodeType(rCopy.m_iNodeType), m_pachValue(NULL)
{
	if(this->m_pachValue)
	    delete [] this->m_pachValue;
	this->m_pachValue = NULL;
	
	if( rCopy.m_pachValue)
	{	
          this->m_pachValue = new char[strlen(rCopy.m_pachValue)+1];
          strcpy(this->m_pachValue,rCopy.m_pachValue);
	}		
}

BasicNode::~BasicNode()
{
	if(m_pachValue)
		delete [] m_pachValue;
}

AXIS_CPP_NAMESPACE_END
