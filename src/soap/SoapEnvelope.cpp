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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 * @author Samisa Abeysinghe (samisa.abeysinghe@gmail.com)
 */

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <stdio.h>

#include <axis/GDefine.hpp>

#include "SoapEnvelope.h"
#include "SoapSerializer.h"
#include "Attribute.h"

#include "../common/AxisTrace.h"


AXIS_CPP_NAMESPACE_START

extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];

SoapEnvelope::
SoapEnvelope()
{
    logEntryEngine("SoapEnvelope::SoapEnvelope")

    m_pSoapHeader= NULL;
    m_pSoapBody= NULL;
    
    logExit()
}

SoapEnvelope::
~SoapEnvelope()
{
    logEntryEngine("SoapEnvelope::~SoapEnvelope")

    // deletion of attributes 
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while (itCurrAttribute != m_attributes.end())
    {        
        delete *itCurrAttribute;
        itCurrAttribute++;
    }

    m_attributes.clear();

    clearNonStandardNamespaceDecl();

    // deletion of soap header 
    delete m_pSoapHeader;

    // deletion of soap body 
    delete m_pSoapBody;
    
    logExit()
}

void SoapEnvelope::
setSoapHeader(SoapHeader* soapHeader)
{
    logEntryEngine("SoapEnvelope::setSoapHeader")

    m_pSoapHeader= soapHeader;
    
    logExit()
}

void SoapEnvelope::
setSoapBody(SoapBody* soapBody)
{
    logEntryEngine("SoapEnvelope::setSoapBody")

    m_pSoapBody= soapBody;
    
    logExit()
}

int SoapEnvelope::
serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion)
{    
    logEntryEngine("SoapEnvelope::serialize")

    int iStatus= AXIS_SUCCESS;
    do
    {            
        pSZ.serialize("\n<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_ENVELOPE],
            NULL);    
        serializeStandardNamespaceDecl(pSZ);
        serializeNamespaceDecl(pSZ);
        serializeAttributes(pSZ);
        pSZ.serialize(">\n", NULL);
        if (m_pSoapHeader!=NULL)
        {
            iStatus= m_pSoapHeader->serialize(pSZ, eSoapVersion);
            if (iStatus == AXIS_FAIL)
                break;
        }
        if (m_pSoapBody!=NULL)
        {
            iStatus= m_pSoapBody->serialize(pSZ, eSoapVersion);
            if (iStatus == AXIS_FAIL)
                break;
        }
        else
             iStatus = AXIS_FAIL;
                
        pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_ENVELOPE],
            ">\n\n", NULL);
    } 
    while (0);

    logExitWithReturnCode(iStatus)
    
    return iStatus;
}

int SoapEnvelope::
addAttribute(Attribute *pAttribute)
{
    logEntryEngine("SoapEnvelope::addAttribute")

    m_attributes.push_back(pAttribute);

    logExitWithReturnCode(AXIS_SUCCESS)
    
    return AXIS_SUCCESS;
}

int SoapEnvelope::
addNamespaceDecl(Attribute *pAttribute)
{
    logEntryEngine("SoapEnvelope::addNamespaceDecl")

    m_namespaceDecls.push_back(pAttribute);

    logExitWithReturnCode(AXIS_SUCCESS)
    
    return AXIS_SUCCESS;
}

int SoapEnvelope::
serializeAttributes(SoapSerializer& pSZ)
{    
    logEntryEngine("SoapEnvelope::serializeAttributes")

    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while (itCurrAttribute != m_attributes.end())
    {
        (*itCurrAttribute)->serialize(pSZ);
        itCurrAttribute++;        
    }    

    logExitWithReturnCode(AXIS_SUCCESS)
    
    return AXIS_SUCCESS;    
}

int SoapEnvelope::
serializeNamespaceDecl(SoapSerializer& pSZ)
{    
    logEntryEngine("SoapEnvelope::serializeNamespaceDecl")

    list<Attribute*>::iterator itCurrNamespaceDecl= m_namespaceDecls.begin();

    while (itCurrNamespaceDecl != m_namespaceDecls.end())
    {            

        (*itCurrNamespaceDecl)->serialize(pSZ);
        itCurrNamespaceDecl++;        
    }    
    
    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

int SoapEnvelope::
setPrefix(const AxisChar* prefix)
{
    logEntryEngine("SoapEnvelope::setPrefix")

    m_sPrefix= prefix;
    
    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

int SoapEnvelope::
addStandardNamespaceDecl(const Attribute *pAttribute)
{
    logEntryEngine("SoapEnvelope::addStandardNamespaceDecl")

    m_StandardNamespaceDecls.push_back(pAttribute);
    
    logExitWithReturnCode(AXIS_SUCCESS)
    
    return AXIS_SUCCESS;
}

void SoapEnvelope::
clearStandardNamespaceDecl()
{
    logEntryEngine("SoapEnvelope::clearStandardNamespaceDecl")

    m_StandardNamespaceDecls.clear();
    
    logExit()
}

void SoapEnvelope::
clearNonStandardNamespaceDecl()
{
    logEntryEngine("SoapEnvelope::clearNonStandardNamespaceDecl")

    list<Attribute*>::iterator itCurrNamespaceDecls= m_namespaceDecls.begin();

    while (itCurrNamespaceDecls != m_namespaceDecls.end())
    {
        delete *itCurrNamespaceDecls;
        itCurrNamespaceDecls++;
    }

    m_namespaceDecls.clear();      
    
    logExit()
}

int SoapEnvelope::
serializeStandardNamespaceDecl(SoapSerializer &pSZ)
{
    logEntryEngine("SoapEnvelope::serializeStandardNamespaceDecl")

    list<const Attribute*>::iterator itCurrNamespaceDecl= m_StandardNamespaceDecls.begin();
    while (itCurrNamespaceDecl != m_StandardNamespaceDecls.end()) 
    {            
        (*itCurrNamespaceDecl)->serialize(pSZ);
        itCurrNamespaceDecl++;        
    }    
    
    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

void SoapEnvelope::
reset()
{
    logEntryEngine("SoapEnvelope::reset")

    clearNonStandardNamespaceDecl();
    
    if (m_pSoapBody)
    {
        SoapMethod * soapMethod = m_pSoapBody->getSoapMethod();
        if ( soapMethod )
            soapMethod->clearOutParams(); 
    } 
    
    if ( m_pSoapHeader )
        m_pSoapHeader->clear();
    
    logExit()
}
AXIS_CPP_NAMESPACE_END

