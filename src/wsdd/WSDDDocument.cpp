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
 *   @author Sanjaya Singharage
 *   @author Suasntha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 *
 */

#include "WSDDDocument.h"
#include "WSDDKeywords.h"
#include "../engine/XMLParserFactory.h"
#include <axis/server/AxisTrace.h>

#define NAMESPACESEPARATOR 0x03    /* Heart */
#define FILEBUFFSIZE 1024

extern AxisTrace* g_pAT;

WSDDDocument::WSDDDocument(map<AxisString, int>* pLibNameIdMap)
{
    m_lev0 = WSDD_UNKNOWN;
    m_lev1 = WSDD_UNKNOWN;
    m_lev2 = WSDD_UNKNOWN;
    m_CurTrType = APTHTTP;    /* default is HTTP */
    m_nLibId = 0;
    m_pLibNameIdMap = pLibNameIdMap;
    /* Get the maximum Lib Id from the entries in the map if available */
    for (map<AxisString, int>::iterator itr = m_pLibNameIdMap->begin(); 
         itr != m_pLibNameIdMap->end(); itr++)
    {
        if (m_nLibId < (*itr).second) m_nLibId = (*itr).second;
    }
    m_bFatalError = false;
    m_bError = false;
}

WSDDDocument::~WSDDDocument()
{

}

int WSDDDocument::getDeployment(const AxisChar* pcWSDDFileName,
                                     WSDDDeployment* pDeployment)
{
    m_pDeployment = pDeployment;    
    /* this enables the access to Deployment object while parsing */
    if (AXIS_SUCCESS != parseDocument(pcWSDDFileName))
    {
        AXISTRACE1("Deployment descripter loading failed", CRITICAL);
        return AXIS_FAIL;
    }
    return AXIS_SUCCESS;
}

/* This function is never called. */
AXIS_TRANSPORT_STATUS WSDDDocument::WSDDFileInputStream::sendBytes(const char* pcSendBuffer, const void* pBufferid)
{
	return TRANSPORT_FINISHED;
}

AXIS_TRANSPORT_STATUS WSDDDocument::WSDDFileInputStream::getBytes(char* pcBuffer, int* piRetSize)
{
	if (!m_pFile)
		m_pFile = fopen(m_pcWSDDFileName, "r");
    if (NULL == m_pFile) 
    { 
        return TRANSPORT_FAILED;
    }
    if (feof(m_pFile))
	{
		fclose(m_pFile);
		pcBuffer[0]=0; /* put null */
		*piRetSize = 0;
        return TRANSPORT_FINISHED;
	}
    *piRetSize = fread(pcBuffer, 1, *piRetSize, m_pFile);
    if (ferror(m_pFile)) 
    {
        fclose(m_pFile);
		pcBuffer[0]=0; /* put null */
		*piRetSize = 0;
        return TRANSPORT_FAILED;
    }
	return TRANSPORT_IN_PROGRESS;
}

/* This function is never called. */
AXIS_TRANSPORT_STATUS WSDDDocument::WSDDMemBufInputStream::sendBytes(const char* pcSendBuffer, const void* pBufferid)
{
	return TRANSPORT_FINISHED;
}

AXIS_TRANSPORT_STATUS WSDDDocument::WSDDMemBufInputStream::getBytes(char* pcBuffer, int* piRetSize)
{
	if (!m_pcWSDDMemBuffer) return TRANSPORT_FAILED;
	int nBufLen = strlen(m_pcWSDDMemBuffer);
	if (0 == nBufLen) return TRANSPORT_FINISHED;
	nBufLen = ((*piRetSize - 1) < nBufLen) ? (*piRetSize - 1) : nBufLen;
	strncpy(pcBuffer, m_pcWSDDMemBuffer, nBufLen);
	pcBuffer[nBufLen] = 0;
	m_pcWSDDMemBuffer+=nBufLen;
	return TRANSPORT_IN_PROGRESS;
}

int WSDDDocument::parseDocument(const AxisChar* pcWSDDFileName)
{
	if (!pcWSDDFileName) return AXIS_FAIL;
	WSDDFileInputStream stream(pcWSDDFileName);
	XMLParser* pParser = XMLParserFactory::getParserObject();
	if (!pParser) return AXIS_FAIL;
	pParser->setInputStream(&stream);
	const AnyElement* pNode;

	while(true)
	{
		/* We are lucky as long as there is no useful data as character data
		 * in wsdd. If there are any we are in trouble and we will not be able
		 * to use the same parser which is used to parse SOAP. Now we never
		 * ask for character data events. To support character data in a
		 * wsdd this entire file will have to be re-written in true
		 * XML PULL model
		 */
		pNode = pParser->next();
		if (AXIS_FAIL == pParser->getStatus()) 
		{
			XMLParserFactory::destroyParserObject(pParser);
			return AXIS_FAIL;
		}
		if (!pNode) break;
		/* Now fire corresponding SAX event. This is a trick to re-use the 
		 * already written code which uses SAX model.
		 */
		switch(pNode->m_type)
		{
		case START_ELEMENT:
			startElement(pNode);
			break;
		case CHARACTER_ELEMENT:
			/* Not used at the moment */
			break;
		case END_ELEMENT:
			endElement(pNode);
			break;
                default:
                        break;
		}
	}
	XMLParserFactory::destroyParserObject(pParser);
	return AXIS_SUCCESS;
}

int WSDDDocument::updateDeployment(const AxisChar* pcWSDDMemBuffer,
                                        WSDDDeployment* pDeployment)
{
    m_pDeployment = pDeployment;/* this enables the access to Deployment 
								object while parsing */
	if (!pcWSDDMemBuffer) return AXIS_FAIL;
	WSDDMemBufInputStream stream(pcWSDDMemBuffer);
	XMLParser* pParser = XMLParserFactory::getParserObject();
	if (!pParser) return AXIS_FAIL;
	pParser->setInputStream(&stream);
	const AnyElement* pNode;

	while(true)
	{
		/* We are lucky as long as there is no useful data as character data
		 * in wsdd. If there are any we are in trouble and we will not be able
		 * to use the same parser which is used to parse SOAP. Now we never
		 * ask for character data events. To support character data in a
		 * wsdd this entire file will have to be re-written in true
		 * XML PULL model
		 */
		pNode = pParser->next();
		if (AXIS_FAIL == pParser->getStatus()) return AXIS_FAIL;
		if (!pNode) break;
		/* Now fire corresponding SAX event. This is a trick to re-use the 
		 * already written code which uses SAX model.
		 */
		switch(pNode->m_type)
		{
		case START_ELEMENT:
			startElement(pNode);
			break;
		case CHARACTER_ELEMENT:
			/* Not used at the moment */
			break;
		case END_ELEMENT:
			endElement(pNode);
			break;
                default:
                        break;
		}
	}
	XMLParserFactory::destroyParserObject(pParser);
	return AXIS_SUCCESS;
}

void  WSDDDocument::endElement(const AnyElement* pEvent)
{
    if (0 != strcmp(pEvent->m_pchNameOrValue, kw_param))   
    /* just neglect endElement of parameter */
    {
        if (m_lev1 == WSDD_UNKNOWN)    
        /* not inside a requestFlow or responseFlow elements */
        {
            switch(m_lev0)
            {
            case WSDD_DEPLOYMENT:
                m_lev0 = WSDD_UNKNOWN;
                break;
            case WSDD_GLOBCONF:
                m_lev0 = WSDD_DEPLOYMENT;
                break;
            case WSDD_SERVICE:
                if (0 == strcmp(pEvent->m_pchNameOrValue, kw_srv))
                {
                    /* add service object to Deployment object */
                    if (DT_DEPLOYMENT == m_pDeployment->getDeploymentType()) 
                        /* deployment */
                    {
                        m_pDeployment->addService(m_pService);
                    }
                    else
                    {
                        m_pDeployment->removeService(m_pService);
                    }
                    m_pService = NULL;
                    m_lev0 = WSDD_DEPLOYMENT;
                }
                else
                {

                }
                break;
            case WSDD_HANDLER:
                /* just ignore the handlers defined outside ??? TODO */
                delete m_pHandler;
                m_pHandler = NULL;
                m_lev0 = WSDD_DEPLOYMENT;
                break;
            case WSDD_TRANSPORT:
                m_CurTrType = APTHTTP;    /* default is HTTP */
                m_lev0 = WSDD_DEPLOYMENT;
                break;
            break;

            default:;
            }
        }
        else    /* inside a requestFlow or responseFlow elements */
        {
            if(0 == strcmp(pEvent->m_pchNameOrValue, kw_hdl))
            {
                m_lev2 = WSDD_UNKNOWN;
                /* add handler in m_pHandler to the corresponding container. */
                switch (m_lev0)
                {
                case WSDD_GLOBCONF:
                    {
                        if (DT_DEPLOYMENT == m_pDeployment->getDeploymentType())  
                            /* deployment */
                        {
                            m_pDeployment->addHandler(true,(m_lev1 == 
                                WSDD_REQFLOW) , m_pHandler);
                        }
                        else
                        {
                            m_pDeployment->removeHandler(true,(m_lev1 ==
                                WSDD_REQFLOW) , m_pHandler);
                        }
                        m_pHandler = NULL;
                    }
                        break;
                case WSDD_TRANSPORT:
                    {
                        if (DT_DEPLOYMENT == m_pDeployment->getDeploymentType())
                            /* deployment */
                        {
                            m_pDeployment->addHandler(false,(m_lev1 == 
                                WSDD_REQFLOW) , m_pHandler, m_CurTrType);
                        }
                        else
                        {
                            m_pDeployment->removeHandler(false,(m_lev1 == 
                                WSDD_REQFLOW) , m_pHandler, m_CurTrType);
                        }
                        m_pHandler = NULL;
                    }
                        break;
                case WSDD_SERVICE:
                    {
                        if (DT_DEPLOYMENT == m_pDeployment->getDeploymentType())
                            /* deployment */
                        {
                            m_pService->addHandler((m_lev1 == WSDD_REQFLOW) ,
                                m_pHandler);
                        }
                        else
                        {
                            m_pService->removeHandler((m_lev1 ==
                                WSDD_REQFLOW) , m_pHandler);
                        }
                        m_pHandler = NULL;
                    }
                        break;
                default: ;    /* this cannot happen ?? */
                }
            }
            else if(0 == strcmp(pEvent->m_pchNameOrValue, kw_rqf))
            {  
                m_lev1 = WSDD_UNKNOWN;
            }
            else if(0 == strcmp(pEvent->m_pchNameOrValue, kw_rsf))
            {  
                m_lev1 = WSDD_UNKNOWN;
            }                        
        }
    }
}

void WSDDDocument::processAttributes(WSDDLevels eElementType,
                                   const AnyElement* pEvent)
{
	const XML_Ch* pcLocalname;
	const XML_Ch* pcNamespace;
    const XML_Ch* pcValue;
	for (int i=0; pEvent->m_pchAttributes[i]; i+=3)
	{
		pcLocalname = pEvent->m_pchAttributes[i];
		pcNamespace = pEvent->m_pchAttributes[i+1];
        pcValue = pEvent->m_pchAttributes[i+2];
        switch(eElementType)
        {
        case WSDD_SERVICE: /* add this attribute to current service object */
            if (0 == strcmp(pcLocalname, kw_name))
            {
                m_pService->setName(pcValue);
            }
            else if (0 == strcmp(pcLocalname, kw_prv))
            {
                m_pService->setProvider(pcValue);
            }
            else if (0 == strcmp(pcLocalname, kw_desc))
            {
                m_pService->setDescription(pcValue);
            }
            else
            {
                /* unknown attribute */
            }
            break;
        case WSDD_HANDLER:  /* add this attribute to current handler object */
            if (0 == strcmp(pcLocalname, kw_name))
            {
                m_pHandler->setName(pcValue);
            }
            else if (0 == strcmp(pcLocalname, kw_type))
            {
                /* we get the libname for the hanlder here ??? */
                m_pHandler->setLibName(pcValue);
                if (m_pLibNameIdMap->find(pcValue) != m_pLibNameIdMap->end())
                    /* libray name already in the map */
                {
                    m_pHandler->setLibId((*m_pLibNameIdMap)[pcValue]);
                }
                else
                {
                    (*m_pLibNameIdMap)[pcValue] = ++m_nLibId;
                    m_pHandler->setLibId((*m_pLibNameIdMap)[pcValue]);
                }
            }
            else if (0 == strcmp(pcLocalname, kw_desc))
            {
                m_pHandler->setDescription(pcValue);
            }
            else
            {
                /* unknown attribute */
            }
            break;
        case WSDD_REQFLOW:
        case WSDD_RESFLOW:
            if (0 == strcmp(pcLocalname, kw_name))
            {
                /* usefull ? ignore for now .. TODO */
            }
            else
            {
                /* unknown attribute */
            }
            break;
        case WSDD_TRANSPORT:
            if (0 == strcmp(pcLocalname, kw_name))
            {
                /* get tranport type */
                if (0 == strcmp(pcValue, kw_http))
                    m_CurTrType = APTHTTP;
                else if (0 == strcmp(pcValue, kw_smtp))
                    m_CurTrType = APTSMTP;
                else
                {
                    /* unhandled transport type */
                }
            }
            else
            {
                /* unknown attribute */
            }
            break;
        default:;
        }
    }
}

void WSDDDocument::getParameters(WSDDLevels eElementType,
                             const AnyElement* pEvent)
{
    const XML_Ch* pcLocalname;
    const XML_Ch* pcNamespace;
    const XML_Ch* pcValue = 0;
    const XML_Ch* pcType;
    const XML_Ch* pcName = 0;
    for (int i=0; pEvent->m_pchAttributes[i]; i+=3)
    {
        pcLocalname = pEvent->m_pchAttributes[i];
        pcNamespace = pEvent->m_pchAttributes[i+1];
        pcValue = pEvent->m_pchAttributes[i+2];
        if (0 == strcmp(pcLocalname, kw_name))
        {
            pcName = pcValue;
        }
        else if (0 == strcmp(pcLocalname, kw_type))
        {
            pcType = pcValue;
        }
    }

    switch(eElementType)
    {
    case WSDD_GLOBCONF:    /* parameters just inside globalConfiguration */
        /* TODO */
        break;
    case WSDD_SERVICE:
        if (0 == strcmp(pcName, kw_am))
        {
            addAllowedMethodsToService(pcValue);
        }
        else if(0 == strcmp(pcName, kw_cn))
        {
            m_pService->setLibName(pcValue);
            if (m_pLibNameIdMap->find(pcValue) != m_pLibNameIdMap->end())  
                /* libray name already in the map */
            {
                m_pService->setLibId((*m_pLibNameIdMap)[pcValue]);
            }
            else
            {
                (*m_pLibNameIdMap)[pcValue] = ++m_nLibId;
                m_pService->setLibId((*m_pLibNameIdMap)[pcValue]);
            }
        }
        else if (0 == strcmp(pcName, kw_scope))
        {
            m_pService->setScope(pcValue);
        }
        else if (0 == strcmp(pcName, kw_ar))
        {
            addAllowedRolesToService(pcValue);
        }
        else
        {
            m_pService->addParameter(pcName, pcValue);
        }
        break;
    case WSDD_HANDLER:
        if (0 == strcmp(pcName, kw_scope))
        {
            m_pHandler->setScope(pcValue);
        }
        else
        {
            m_pHandler->addParameter(pcName, pcValue);
        }
        break;

     default:;
    }
}

void WSDDDocument::addAllowedRolesToService(const AxisXMLCh* pcValue)
{
    AxisString sValue = pcValue;
    unsigned int prepos = 0, pos = 0;
    if (sValue.find('*') == AxisString::npos)
    {
        do 
        {
            pos = sValue.find(ROLENAME_SEPARATOR, prepos);
            if (AxisString::npos == pos) break;
            m_pService->addAllowedRole(sValue.substr(prepos,
                pos-prepos).c_str());
            prepos = pos + 1;
        } while (true);
    }
}

void WSDDDocument::addAllowedMethodsToService(const AxisXMLCh* pcValue)
{
    AxisString sValue = pcValue;
    int prepos = 0, pos = 0;
    if (sValue.find('*') == AxisString::npos)
    {
        do 
        {
            pos = sValue.find(METHODNAME_SEPARATOR, prepos);
            if (AxisString::npos == pos) break;
            m_pService->addAllowedMethod(sValue.substr(prepos,
                pos-prepos).c_str());
            prepos = pos + 1;
        } while (true);
    }
}


void WSDDDocument::startElement(const AnyElement* pEvent)
{
    if (m_lev1 == WSDD_UNKNOWN)    
    /* not inside a requestFlow or responseFlow elements */
    {
        switch(m_lev0)
        {
        case WSDD_UNKNOWN:
            if(0 == strcmp(pEvent->m_pchNameOrValue, kw_depl))
            {  
                m_lev0 = WSDD_DEPLOYMENT;
                m_pDeployment->setDeploymentType(DT_DEPLOYMENT);
            }
            else if(0 == strcmp(pEvent->m_pchNameOrValue, kw_undepl))
            {  
                m_lev0 = WSDD_DEPLOYMENT;
                m_pDeployment->setDeploymentType(DT_UNDEPLOYMENT);
            }
            break;
        case WSDD_DEPLOYMENT:
            if(0 == strcmp(pEvent->m_pchNameOrValue, kw_glconf))
            {  
                m_lev0 = WSDD_GLOBCONF;
                /* nothing to get */
            }
            else if(0 == strcmp(pEvent->m_pchNameOrValue, kw_srv))
            {  
                m_lev0 = WSDD_SERVICE;
                m_pService = new WSDDService();
                /* get service name and proider if any */
                processAttributes(WSDD_SERVICE, pEvent);
            }
            else if(0 == strcmp(pEvent->m_pchNameOrValue, kw_hdl))
            {  
                m_lev0 = WSDD_HANDLER;
                m_pHandler = new WSDDHandler();
                processAttributes(WSDD_HANDLER, pEvent);
                /* get handler name and type if any */
            }
            else if(0 == strcmp(pEvent->m_pchNameOrValue, kw_tr))
            {  
                m_lev0 = WSDD_TRANSPORT;
                processAttributes(WSDD_TRANSPORT, pEvent);
            }
            else
            {
                /* error : unknown element type in wsdd file */
            }
            break;
        case WSDD_GLOBCONF:
            if(0 == strcmp(pEvent->m_pchNameOrValue, kw_param))
            {  
                getParameters(WSDD_GLOBCONF, pEvent);
            }
            else if(0 == strcmp(pEvent->m_pchNameOrValue, kw_rqf))
            {  
                m_lev1 = WSDD_REQFLOW;
                processAttributes(WSDD_REQFLOW, pEvent);
            }
            else if(0 == strcmp(pEvent->m_pchNameOrValue, kw_rsf))
            {  
                m_lev1 = WSDD_RESFLOW;
                processAttributes(WSDD_RESFLOW, pEvent);
            }
            else
            {
                /* yet unhandled element type */
            }
        break; 
        case WSDD_SERVICE:
            if(0 == strcmp(pEvent->m_pchNameOrValue, kw_param))
            {  
                getParameters(WSDD_SERVICE, pEvent);
            }
            else if(0 == strcmp(pEvent->m_pchNameOrValue, kw_rqf))
            {  
                m_lev1 = WSDD_REQFLOW;
                processAttributes(WSDD_REQFLOW, pEvent);
            }
            else if(0 == strcmp(pEvent->m_pchNameOrValue, kw_rsf))
            {  
                m_lev1 = WSDD_RESFLOW;
                processAttributes(WSDD_RESFLOW, pEvent);
            }
            else
            {
                /* yet unhandled element type like namespace */
            }
        break;
        case WSDD_HANDLER:
            if(0 == strcmp(pEvent->m_pchNameOrValue, kw_param))
            {  
                getParameters(WSDD_HANDLER, pEvent);
            }

        break;
        case WSDD_TRANSPORT:
            if(0 == strcmp(pEvent->m_pchNameOrValue, kw_rqf))
            {  
                m_lev1 = WSDD_REQFLOW;
                processAttributes(WSDD_REQFLOW, pEvent);
            }
            else if(0 == strcmp(pEvent->m_pchNameOrValue, kw_rsf))
            {  
                m_lev1 = WSDD_RESFLOW;
                processAttributes(WSDD_RESFLOW, pEvent);
            }
        break;
        default:;
        }
    }
    else    /* inside a requestFlow or responseFlow elements */
    {
        if(0 == strcmp(pEvent->m_pchNameOrValue, kw_param))
        {  
            getParameters(m_lev2, pEvent);    
            /* must be parameters of a handler or a chain */
        }

        else if(0 == strcmp(pEvent->m_pchNameOrValue, kw_hdl))
        {  
            m_lev2 = WSDD_HANDLER;
            m_pHandler = new WSDDHandler();
            processAttributes(WSDD_HANDLER, pEvent);
            /* get handler name and type if any */
        }
        else if(0 == strcmp(pEvent->m_pchNameOrValue, kw_chain))
        {

        }
        else
        {
            /* error : unknown element type in wsdd file */
        }
    }
}




