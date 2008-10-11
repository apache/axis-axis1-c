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
 * @author Roshan Weerasuriya (roshanw@jkcsworld.com, roshan@opensource.lk)
 */

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <axis/GDefine.hpp>

#include "SoapHeader.h"
#include "SoapSerializer.h"
#include "Attribute.h"
#include "HeaderBlock.h"

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START

extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];

SoapHeader::SoapHeader()
{	
}

SoapHeader::~SoapHeader()
{
    // Header blocks are not deleted here any more. Its the responsibility of
    // either a handler or stub etc to delete any header block created by them
    // Here we will just clear the list of header block pointers
    m_headerBlocks.clear();

    // deletion of attributes 
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while(itCurrAttribute != m_attributes.end())
    {        
        delete *itCurrAttribute;
        itCurrAttribute++;
    }

    m_attributes.clear();
}

void SoapHeader::addHeaderBlock(IHeaderBlock* pHeaderBlock)
{
    if (pHeaderBlock)
    {
        m_headerBlocks.push_back(pHeaderBlock);
    }
}

int SoapHeader::serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion)
{    
    int iStatus= AXIS_SUCCESS;

    do
    {
		if (0 == m_headerBlocks.size()) break;
        
        pSZ.serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_HEADER],
            NULL);

        iStatus= serializeNamespaceDecl(pSZ);
        iStatus= serializeAttributes(pSZ);

        if(iStatus==AXIS_FAIL)
        {
            break;
        }
        
        pSZ.serialize(">", NULL);

        list<IHeaderBlock*>::iterator itCurrHeaderBlock= m_headerBlocks.begin();

        while(itCurrHeaderBlock != m_headerBlocks.end())
        {
            iStatus= ((HeaderBlock*)(*itCurrHeaderBlock))->serialize(pSZ);
            if(iStatus==AXIS_FAIL)
            {
                break;
            }
            itCurrHeaderBlock++;            
        }

        if(iStatus==AXIS_FAIL)
        {
            break;
        }
        
        pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_HEADER],
            ">\n", NULL);
        
    } while(0);

    return iStatus;

}

int SoapHeader::addAttribute(Attribute *pAttribute)
{
    if (pAttribute)
    {
        m_attributes.push_back(pAttribute);

        return AXIS_SUCCESS;
    }
    else
    {
        return AXIS_FAIL;
    }
}


int SoapHeader::serializeAttributes(SoapSerializer& pSZ)
{
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while(itCurrAttribute != m_attributes.end())
    {
        (*itCurrAttribute)->serialize(pSZ);
        itCurrAttribute++;        
    }    

    return AXIS_SUCCESS;    
}

int SoapHeader::addNamespaceDecl(Attribute *pAttribute)
{
    if (pAttribute)
    {
        m_namespaceDecls.push_back(pAttribute);

        return AXIS_SUCCESS;
    }
    else
    {
        return AXIS_FAIL;
    }
}

int SoapHeader::serializeNamespaceDecl(SoapSerializer& pSZ)
{
    list<Attribute*>::iterator itCurrNamespaceDecl= m_namespaceDecls.begin();

    while(itCurrNamespaceDecl != m_namespaceDecls.end())
    {

        (*itCurrNamespaceDecl)->serialize(pSZ);
        itCurrNamespaceDecl++;        
    }    

    return AXIS_SUCCESS;
}

IHeaderBlock* SoapHeader::getHeaderBlock(bool bRemoveOrNot)
{
    IHeaderBlock* tmpHeaderBlock = NULL;

    list<IHeaderBlock*>::iterator itCurrHeaderBlock= m_headerBlocks.begin();

    if(itCurrHeaderBlock != m_headerBlocks.end())
    {
        tmpHeaderBlock = (*itCurrHeaderBlock);
		if (bRemoveOrNot == true) {
			m_headerBlocks.pop_front();
		}
    }

    return tmpHeaderBlock;

}

int SoapHeader::setPrefix(const char* pcPrefix)
{
    m_pcPrefix = pcPrefix;

    return AXIS_SUCCESS;
}

IHeaderBlock* SoapHeader::getHeaderBlock(const AxisChar *pName,
                                         const AxisChar *pNamespace, 
										 bool bRemoveOrNot)
{
    HeaderBlock* tmpHeaderBlock = NULL;

    list<IHeaderBlock*>::iterator itCurrHeaderBlock= m_headerBlocks.begin();
    bool blnFoundStatus = false;

    while (itCurrHeaderBlock != m_headerBlocks.end())
    {
        tmpHeaderBlock = (HeaderBlock*)(*itCurrHeaderBlock);

        if ((strcmp(((tmpHeaderBlock)->m_localname).c_str(), pName) == 0) && 
                (strcmp(((tmpHeaderBlock)->m_uri).c_str(), pNamespace) == 0))
        {
            blnFoundStatus = true;
			if (bRemoveOrNot == true) {
				m_headerBlocks.remove(tmpHeaderBlock);
			}
            break;
        }
        else
        {
            itCurrHeaderBlock++;
        }
    }

    if (blnFoundStatus == true)
    {
        return tmpHeaderBlock;
    }
    else
    {
        return NULL;
    }
}

 
IHeaderBlock* SoapHeader::getFirstHeaderBlock() 
{
	m_itHeaderBlocks = m_headerBlocks.begin();
	IHeaderBlock* tmpIHeaderBlock=NULL;
	if (m_itHeaderBlocks != m_headerBlocks.end())
		tmpIHeaderBlock = *m_itHeaderBlocks;
	return tmpIHeaderBlock;
}

IHeaderBlock* SoapHeader::getNextHeaderBlock() 
{
	m_itHeaderBlocks++;
	IHeaderBlock* tmpIHeaderBlock=NULL;
	if (m_itHeaderBlocks != m_headerBlocks.end())
		tmpIHeaderBlock = *m_itHeaderBlocks;
	return tmpIHeaderBlock;
}

IHeaderBlock* SoapHeader::getCurrentHeaderBlock()
{
	IHeaderBlock* tmpIHeaderBlock=NULL;
	if (m_itHeaderBlocks != m_headerBlocks.end())
		tmpIHeaderBlock = *m_itHeaderBlocks;

	return tmpIHeaderBlock;
}


int SoapHeader::deleteHeaderBlock(const AxisChar *pName,
                                         const AxisChar *pNamespace)
{
    int iStatus = AXIS_SUCCESS;
    HeaderBlock* tmpHeaderBlock = NULL;

    list<IHeaderBlock*>::iterator itCurrHeaderBlock= m_headerBlocks.begin();
    
    while (itCurrHeaderBlock != m_headerBlocks.end())
    {
        tmpHeaderBlock = (HeaderBlock*)(*itCurrHeaderBlock);

        if ((strcmp(((tmpHeaderBlock)->m_localname).c_str(), pName) == 0) && 
                (strcmp(((tmpHeaderBlock)->m_uri).c_str(), pNamespace) == 0))
        {
            m_headerBlocks.remove(tmpHeaderBlock);            
            break; 
        }
        else
        {
            itCurrHeaderBlock++;
        }
    
    }

    if (m_headerBlocks.empty())
    {
        iStatus = AXIS_NO_REMAINING_SOAP_HEADERS;                     
    }
    
    return iStatus;
}
void SoapHeader::clear()
{
    // Header blocks are not deleted here. Its the responsibility of
    // either a handler or stub etc to delete any header block created by them
    // Here we will just clear the list of header block pointers
    m_headerBlocks.clear();

    // deletion of attributes 
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while(itCurrAttribute != m_attributes.end())
    {
        delete *itCurrAttribute;
        itCurrAttribute++;
    }

    m_attributes.clear();
}


AXIS_CPP_NAMESPACE_END
