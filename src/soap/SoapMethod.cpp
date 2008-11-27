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
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 *
 */

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <axis/GDefine.hpp>

#include "SoapMethod.h"
#include "Attribute.h"

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START

SoapMethod::
SoapMethod()
{
	logEntryEngine("SoapMethod::SoapMethod")

	reset();
	
	logExit()
}

SoapMethod::
~SoapMethod()
{
	logEntryEngine("SoapMethod::~SoapMethod")

    clearAttributes();
    clearOutParams();
    
	logExit()
}

void SoapMethod::
setPrefix(const AxisChar* prefix)
{
	logEntryEngine("SoapMethod::setPrefix")

	if (NULL == prefix)
		m_strPrefix = "";
	else
		m_strPrefix = prefix;
	
	logExit()
}

void SoapMethod::
setLocalName(const AxisChar* localname)
{
	logEntryEngine("SoapMethod::setLocalName")

	if (NULL == localname)
		m_strLocalname = "";
	else
		m_strLocalname = localname;
	
	logExit()
}

void SoapMethod::
setURI(const AxisChar* uri)
{
	logEntryEngine("SoapMethod::setURI")

	if (NULL == uri)
		m_strUri = "";
	else
		m_strUri = uri;
	
	logExit()
}

void SoapMethod::
addOutputParam(Param *param)
{
	logEntryEngine("SoapMethod::addOutputParam")

    if (param)
    {
    	if (m_OutputParams.empty() && param->isSimpleType())
    		m_addEndTagForUnwrapped = true;
    	
        m_OutputParams.push_back(param);
    }
	
	logExit()
}

int SoapMethod::
serialize(SoapSerializer& pSZ)
{   
	logEntryEngine("SoapMethod::serialize")

    int iStatus= AXIS_SUCCESS;

    do
    {
        if(isSerializable())
        {           
            pSZ.serialize("<", m_strPrefix.c_str(), ":", m_strLocalname.c_str(),
                " xmlns:", m_strPrefix.c_str(),
                "=\"", m_strUri.c_str(), "\"", NULL);

            list<AxisChar*> lstTmpNameSpaceStack;

            iStatus= serializeAttributes(pSZ, lstTmpNameSpaceStack);
            if(iStatus==AXIS_FAIL)
                break;
            
            // If not wrapper style, then end tag will be added by bean - if parameter is complex type. 
            // This is a hack in order to keep backward compatibility.
            if (m_isWrapperStyle || m_addEndTagForUnwrapped)
            	pSZ.serialize(">\n", NULL);

            // push the current NS to the NS stack
            pSZ.getNamespacePrefix(m_strUri.c_str());

            iStatus= serializeOutputParam(pSZ);

            // remove the current NS from the NS stack
            pSZ.removeNamespacePrefix(m_strUri.c_str());

            if(iStatus==AXIS_FAIL)
                break;
            
            pSZ.serialize("</", NULL);

            if(m_strPrefix.length() != 0)
                pSZ.serialize(m_strPrefix.c_str(), ":", NULL);
            
            pSZ.serialize(m_strLocalname.c_str(), ">\n", NULL);

            // Removing the namespace list of this SOAPMethod from the stack.
            list<AxisChar*>::iterator itCurrentNamespace = lstTmpNameSpaceStack.begin();
            while (itCurrentNamespace != lstTmpNameSpaceStack.end())
            {
                pSZ.removeNamespacePrefix(*itCurrentNamespace);
                itCurrentNamespace++;
            }

            iStatus= AXIS_SUCCESS;
        }
        else
            iStatus= AXIS_FAIL;
    } 
    while(0);
            
	logExitWithReturnCode(iStatus)

    return iStatus;
}

int SoapMethod::
serializeOutputParam(SoapSerializer& pSZ)
{
	logEntryEngine("SoapMethod::serializeOutputParam")

    int nStatus = AXIS_SUCCESS;
    

    for (list<Param*>::iterator it = m_OutputParams.begin(); it != m_OutputParams.end(); it++)
        if (AXIS_SUCCESS != (nStatus = (*it)->serialize(pSZ)))
            break;

	logExitWithReturnCode(nStatus)

    return nStatus;
}

const AxisChar* SoapMethod::
getMethodName()
{
    return m_strLocalname.c_str();
}

bool SoapMethod::
isSerializable()
{
	logEntryEngine("SoapMethod::isSerializable")

    bool bStatus= true;    

    // checking whether namespace qualified, if not return AXIS_FAIL 
    do
    {
        if(m_strPrefix.length() == 0)
        {            
            bStatus= false;        
            break;
        }
        else if(m_strUri.length() == 0)
        {
            bStatus= false;
            break;
        }
    } 
    while(0);

    logExitWithBoolean(bStatus)
    
    return bStatus;
}

int SoapMethod::
addAttribute(Attribute *pAttribute)
{
	logEntryEngine("SoapMethod::addAttribute")

	if (pAttribute)
		m_attributes.push_back(pAttribute);

	logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

int SoapMethod::
serializeAttributes(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack)
{
	logEntryEngine("SoapMethod::serializeAttributes")

    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while(itCurrAttribute != m_attributes.end())
    {        
        (*itCurrAttribute)->serialize(pSZ, lstTmpNameSpaceStack);
        itCurrAttribute++;        
    }    

	logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;    
}

int SoapMethod::
reset()
{
	logEntryEngine("SoapMethod::reset")

    m_addEndTagForUnwrapped = false;
	m_isWrapperStyle = true;
    m_strUri = "";
    m_strLocalname = "";
    m_strPrefix = "";
    m_OutputParams.clear();
    m_attributes.clear();

	logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

void SoapMethod::
clearOutParams()
{
	logEntryEngine("SoapMethod::clearOutParams")

    if ( !m_OutputParams.empty() )
    {
	    list<Param*>::iterator itParam;
	    
	    for (itParam = m_OutputParams.begin(); itParam != m_OutputParams.end(); itParam++)
	        delete *itParam;
	        
	    m_OutputParams.clear();
    }
    
    logExit()
}

void SoapMethod::
clearAttributes()
{
	logEntryEngine("SoapMethod::clearAttributes")

    if (!m_attributes.empty())
    {
	    list<Attribute*>::iterator it;
	    
	    for (it = m_attributes.begin(); it != m_attributes.end(); ++it)
	        delete *it;
	    
	    m_attributes.clear();
    }
    
    logExit()
}

AXIS_CPP_NAMESPACE_END

