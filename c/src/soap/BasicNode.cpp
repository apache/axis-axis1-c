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
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Roshan Weerasuriya (roshan@jkcsworld.com, roshan@opensource.lk)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/25 samisa
 * Added constructors, copy constructure and pure virtual clone for copy constructing derived classes
 */


#include <axis/server/BasicNode.h>
BasicNode::BasicNode():m_iNodeType(ELEMENT_NODE), m_pachValue(NULL)
{}

BasicNode::BasicNode(const AxisChar* pachValue, NODE_TYPE eNodeType):m_iNodeType(ELEMENT_NODE), m_pachValue(NULL)
{
    if(pachValue)
    	this->m_pachValue = strdup(pachValue);

}

BasicNode::BasicNode(const BasicNode& rCopy):m_iNodeType(ELEMENT_NODE), m_pachValue(NULL)
{
	if(this->m_pachValue)
	    free(this->m_pachValue);
	this->m_pachValue = NULL;
	
	if( rCopy.m_pachValue)
	{	
		this->m_pachValue = strdup(rCopy.m_pachValue);
	}		
}

BasicNode::~BasicNode()
{
	if(m_pachValue)
		free(m_pachValue);
}

