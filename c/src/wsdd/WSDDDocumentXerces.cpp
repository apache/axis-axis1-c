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
 * @author Sanjaya Singharage
 * @author Suasntha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 *
 */

#include "WSDDDocumentXerces.h"
#include "WSDDKeywords.h"
#include <xercesc/framework/MemBufInputSource.hpp>
#include <axis/server/AxisTrace.h>
extern AxisTrace* g_pAT;

WSDDDocumentXerces::WSDDDocumentXerces(map<AxisString, int>* pLibNameIdMap)
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

WSDDDocumentXerces::~WSDDDocumentXerces()
{

}

int WSDDDocumentXerces::getDeployment(const AxisChar* sWSDD,
                                      WSDDDeployment* pDeployment)
{
    m_pDeployment = pDeployment;   
    /* this enables the access to Deployment object while parsing */
    if (AXIS_SUCCESS != ParseDocument(sWSDD)) 
    {
        AXISTRACE1("Deployment descripter loading failed", CRITICAL);
        return AXIS_FAIL;
    }
    return AXIS_SUCCESS;
}

int WSDDDocumentXerces::parseDocument(const AxisChar* sWSDD)
{
    try
    {
        SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
        parser->setContentHandler(this);
        parser->setErrorHandler(this);             
        parser->parse(sWSDD);   
        delete parser;
        if (m_bFatalError || m_bError) return AXIS_FAIL;
    }
    catch (...)
    {
        return AXIS_FAIL;
    }
    return AXIS_SUCCESS;
}

int WSDDDocumentXerces::updateDeployment(const AxisChar* sWSDD,
                                         WSDDDeployment* pDeployment)
{
    m_pDeployment = pDeployment; 
    /* this enables the access to Deployment object while parsing */
    try
    {
        MemBufInputSource Input((const unsigned char*)sWSDD, strlen(sWSDD) ,
            "wsddbufferid");
        SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
        parser->setContentHandler(this);
        parser->setErrorHandler(this);             
        parser->parse(Input);   
        delete parser;
        if (m_bFatalError || m_bError)
        {
            AXISTRACE1("Deployment descripte update failed", CRITICAL);
            return AXIS_FAIL;
        }
    }
    catch (...)
    {
        AXISTRACE1("Deployment descripte update failed", CRITICAL);
        return AXIS_FAIL;
    }
    return AXIS_SUCCESS;
}

void  WSDDDocumentXerces::endElement (const XMLCh *const uri, 
                                      const XMLCh *const localname, 
                                      const XMLCh *const qname)
{
    AxisXMLString sLname = __XTRC(localname);
    const AxisXMLCh* lname = sLname.c_str();
    if (!XMLString::equals(lname, kw_param)) 
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
                if (XMLString::equals(lname, kw_srv))
                {
                    /* add service object to Deployment object */
                    if (DT_DEPLOYMENT == m_pDeployment->GetDeploymentType())
                        /* deployment */
                    {
                        m_pDeployment->AddService(m_pService);
                    }
                    else
                    {
                        m_pDeployment->RemoveService(m_pService);
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
                m_CurTrType = APTHTTP;   /* default is HTTP */
                m_lev0 = WSDD_DEPLOYMENT;
                break;
            break;

            default:;
            }
        }
        else /* inside a requestFlow or responseFlow elements */
        {
            if(XMLString::equals(lname, kw_hdl))
            {
                m_lev2 = WSDD_UNKNOWN;
                /* add handler in m_pHandler to the corresponding container. */
                switch (m_lev0)
                {
                case WSDD_GLOBCONF:
                    {
                        if (DT_DEPLOYMENT ==
                            m_pDeployment->GetDeploymentType())/* deployment */
                        {
                            m_pDeployment->AddHandler(true,
                                (m_lev1 == WSDD_REQFLOW) , m_pHandler);
                        }
                        else
                        {
                            m_pDeployment->RemoveHandler(true,
                                (m_lev1 == WSDD_REQFLOW) , m_pHandler);
                        }
                        m_pHandler = NULL;
                    }
                        break;
                case WSDD_TRANSPORT:
                    {
                        if (DT_DEPLOYMENT == 
                            m_pDeployment->GetDeploymentType()) /* deployment */
                        {
                            m_pDeployment->AddHandler(false,
                                (m_lev1 == WSDD_REQFLOW) , m_pHandler,
                                m_CurTrType);
                        }
                        else
                        {
                            m_pDeployment->RemoveHandler(false,
                                (m_lev1 == WSDD_REQFLOW) , m_pHandler,
                                m_CurTrType);
                        }
                        m_pHandler = NULL;
                    }
                        break;
                case WSDD_SERVICE:
                    {
                        if (DT_DEPLOYMENT == 
                            m_pDeployment->GetDeploymentType()) /* deployment */
                        {
                            m_pService->AddHandler((m_lev1 == WSDD_REQFLOW) ,
                                m_pHandler);
                        }
                        else
                        {
                            m_pService->RemoveHandler((m_lev1 == WSDD_REQFLOW) ,
                                m_pHandler);
                        }
                        m_pHandler = NULL;
                    }
                        break;
                default: ; /* this cannot happen ?? */
                }
            }
            else if(XMLString::equals(lname, kw_rqf))
            {  
                m_lev1 = WSDD_UNKNOWN;
            }
            else if(XMLString::equals(lname, kw_rsf))
            {  
                m_lev1 = WSDD_UNKNOWN;
            }                        
        }
    }
}

void WSDDDocumentXerces::processAttributes(WSDDLevels ElementType,
                                           const Attributes &attrs)
{
    AxisXMLString sLocal;
    AxisXMLString sValue;
    const AxisXMLCh* local;
    const AxisXMLCh* value;
    for (int i = 0; i < attrs.getLength(); i++) 
    {
        sLocal = __XTRC(attrs.getLocalName(i));
        sValue = __XTRC(attrs.getValue(i));
        local = sLocal.c_str();
        value = sValue.c_str();
        switch(ElementType)
        {
        case WSDD_SERVICE: /* add this attribute to current service object */
            if (XMLString::equals(local, kw_name))
            {
                m_pService->SetName(value);
            }
            else if (XMLString::equals(local, kw_prv))
            {
                m_pService->SetProvider(value);
            }
            else if (XMLString::equals(local, kw_desc))
            {
                m_pService->SetDescription(value);
            }
            else
            {
                /* unknown attribute */
            }
            break;
        case WSDD_HANDLER: /* add this attribute to current handler object */
            if (XMLString::equals(local, kw_name))
            {
                m_pHandler->SetName(value);
            }
            else if (XMLString::equals(local, kw_type))
            {
                /* we get the libname for the hanlder here ??? */
                m_pHandler->SetLibName(value);
                if (m_pLibNameIdMap->find(value) != 
                    m_pLibNameIdMap->end()) 
                    /* libray name already in the map */
                {
                    m_pHandler->SetLibId((*m_pLibNameIdMap)[value]);
                }
                else
                {
                    (*m_pLibNameIdMap)[value] = ++m_nLibId;
                    m_pHandler->SetLibId((*m_pLibNameIdMap)[value]);
                }
            }
            else if (XMLString::equals(local, kw_desc))
            {
                m_pHandler->SetDescription(value);
            }
            else
            {
                /* unknown attribute */
            }
            break;
        case WSDD_REQFLOW:
        case WSDD_RESFLOW:
            if (XMLString::equals(local, kw_name))
            {
                /* usefull ? ignore for now .. TODO */
            }
            else
            {
                /* unknown attribute */
            }
            break;
        case WSDD_TRANSPORT:
            if (XMLString::equals(local, kw_name))
            {
                /* get tranport type */
                if (XMLString::equals(value, kw_http))
                    m_CurTrType = APTHTTP;
                else if (XMLString::equals(value, kw_smtp))
                    m_CurTrType = APTSMTP;
                else
                {
                    //unhandled transport type
                }
            }
            else
            {
                //unknown attribute
            }
            break;
        default:;
        }
    }
}

void WSDDDocumentXerces::getParameters(WSDDLevels ElementType,
                                       const Attributes &attrs)
{
    AxisXMLString sName, sValue, sType;
    const AxisXMLCh *name, *value, *type;
    /* bool locked; */
    AxisXMLString Localname, Value;
    for (int i = 0; i < attrs.getLength(); i++) 
    {
        Localname = __XTRC(attrs.getLocalName(i));
        Value = __XTRC(attrs.getValue(i));
        if (XMLString::equals(Localname.c_str(), kw_name))
        {
            sName = Value.c_str();
        }
        else if (XMLString::equals(Localname.c_str(), kw_value))
        {
            sValue = Value.c_str();
        }
        else if (XMLString::equals(Localname.c_str(), kw_type))
        {
            sType = Value.c_str();
        }
    }
    
    name = sName.c_str();
    value = sValue.c_str();
    type = sType.c_str();

    switch(ElementType)
    {
    case WSDD_GLOBCONF: /* parameters just inside globalConfiguration */
        /* TODO */
        break;
    case WSDD_SERVICE:
        if (XMLString::equals(name, kw_am))
        {
            AddAllowedMethodsToService(value);
        }
        else if(XMLString::equals(name, kw_cn))
        {
            m_pService->SetLibName(value);
            if (m_pLibNameIdMap->find(value) != m_pLibNameIdMap->end()) 
                /* libray name already in the map */
            {
                m_pService->SetLibId((*m_pLibNameIdMap)[value]);
            }
            else
            {
                (*m_pLibNameIdMap)[value] = ++m_nLibId;
                m_pService->SetLibId((*m_pLibNameIdMap)[value]);
            }
        }
        else if (XMLString::equals(name, kw_scope))
        {
            m_pService->SetScope(value);
        }
        else if (XMLString::equals(name, kw_ar))
        {
            AddAllowedRolesToService(value);
        }
        else
        {
            m_pService->AddParameter(name, value);
        }
        break;
    case WSDD_HANDLER:
        if (XMLString::equals(name, kw_scope))
        {
            m_pHandler->SetScope(value);
        }
        else
        {
            m_pHandler->AddParameter(name, value);
        }
        break;

     default:;
    }
}

void WSDDDocumentXerces::addAllowedRolesToService(const AxisXMLCh* value)
{
    AxisString sValue = value;
    int prepos = 0, pos = 0;
    if (sValue.find('*') == AxisString::npos)
    {
        do 
        {
            pos = sValue.find(ROLENAME_SEPARATOR, prepos);
            if (AxisString::npos == pos) break;
            m_pService->AddAllowedRole(sValue.
                substr(prepos, pos-prepos).c_str());
            prepos = pos + 1;
        } while (true);
    }
}

void WSDDDocumentXerces::addAllowedMethodsToService(const AxisXMLCh* value)
{
    AxisString sValue = value;
    int prepos = 0, pos = 0, len = 0;
    /*
     * Fix for bug 23556.
     * This routine makes sure that the value of allowedMethods (a list
     * of method names separated by spaces) in the WSDD file is immune 
     * to having trailing and leading spaces, and multiple spaces 
     * between items.
     */
    if (sValue.find('*') == AxisString::npos)
    {
        len = sValue.length();
        do 
        {
            pos = sValue.find(METHODNAME_SEPARATOR, prepos);

            if((AxisString::npos != pos) && (pos!=prepos))
            {
                m_pService->AddAllowedMethod(sValue.substr(prepos,
                    pos-prepos).c_str());
            }
            else if (AxisString::npos != pos)
            {
                prepos = pos+1;
            }
            else if (strchr(sValue.substr(prepos, len-(prepos+1)).c_str(), 
                METHODNAME_SEPARATOR)==NULL && (len!=prepos))
            {
                m_pService->AddAllowedMethod(sValue.substr(prepos,
                    len-(prepos-1)).c_str());
                break;
            }
            else
            {
                break;
            }

            prepos = pos+1;

        } while (true);

    }
}

void WSDDDocumentXerces::startElement(const XMLCh *const uri,
                                      const XMLCh *const localname, 
                                      const XMLCh *const qname,
                                      const Attributes &attrs)
{
    AxisXMLString sLname = __XTRC(localname);
    const AxisXMLCh* lname = sLname.c_str();

    if (m_lev1 == WSDD_UNKNOWN) /* not inside a requestFlow or responseFlow
        elements */
    {
        switch(m_lev0)
        {
        case WSDD_UNKNOWN:
            if(XMLString::equals(lname, kw_depl))
            {  
                m_lev0 = WSDD_DEPLOYMENT;
                m_pDeployment->SetDeploymentType(DT_DEPLOYMENT);
            }
            else if(XMLString::equals(lname, kw_undepl))
            {  
                m_lev0 = WSDD_DEPLOYMENT;
                m_pDeployment->SetDeploymentType(DT_UNDEPLOYMENT);
            }
            break;
        case WSDD_DEPLOYMENT:
            if(XMLString::equals(lname, kw_glconf))
            {  
                m_lev0 = WSDD_GLOBCONF;
                /* nothing to get */
            }
            else if(XMLString::equals(lname, kw_srv))
            {  
                m_lev0 = WSDD_SERVICE;
                m_pService = new WSDDService();
                /* get service name and proider if any */
                ProcessAttributes(WSDD_SERVICE, attrs);
            }
            else if(XMLString::equals(lname, kw_hdl))
            {  
                m_lev0 = WSDD_HANDLER;
                m_pHandler = new WSDDHandler();
                ProcessAttributes(WSDD_HANDLER, attrs);
                /* get handler name and type if any */
            }
            else if(XMLString::equals(lname, kw_tr))
            {  
                m_lev0 = WSDD_TRANSPORT;
                ProcessAttributes(WSDD_TRANSPORT, attrs);
            }
            else
            {
                /* error : unknown element type in wsdd file */
            }
            break;
        case WSDD_GLOBCONF:
            if(XMLString::equals(lname, kw_param))
            {  
                GetParameters(WSDD_GLOBCONF, attrs);
            }
            else if(XMLString::equals(lname, kw_rqf))
            {  
                m_lev1 = WSDD_REQFLOW;
                ProcessAttributes(WSDD_REQFLOW, attrs);
            }
            else if(XMLString::equals(lname, kw_rsf))
            {  
                m_lev1 = WSDD_RESFLOW;
                ProcessAttributes(WSDD_RESFLOW, attrs);
            }
            else
            {
                /* yet unhandled element type */
            }
        break; 
        case WSDD_SERVICE:
            if(XMLString::equals(lname, kw_param))
            {  
                GetParameters(WSDD_SERVICE, attrs);
            }
            else if(XMLString::equals(lname, kw_rqf))
            {  
                m_lev1 = WSDD_REQFLOW;
                ProcessAttributes(WSDD_REQFLOW, attrs);
            }
            else if(XMLString::equals(lname, kw_rsf))
            {  
                m_lev1 = WSDD_RESFLOW;
                ProcessAttributes(WSDD_RESFLOW, attrs);
            }
            else
            {
                /* yet unhandled element type like namespace */
            }
        break;
        case WSDD_HANDLER:
            if(XMLString::equals(lname, kw_param))
            {  
                GetParameters(WSDD_HANDLER, attrs);
            }

        break;
        case WSDD_TRANSPORT:
            if(XMLString::equals(lname, kw_rqf))
            {  
                m_lev1 = WSDD_REQFLOW;
                ProcessAttributes(WSDD_REQFLOW, attrs);
            }
            else if(XMLString::equals(lname, kw_rsf))
            {  
                m_lev1 = WSDD_RESFLOW;
                ProcessAttributes(WSDD_RESFLOW, attrs);
            }
        break;
        default:;
        }
    }
    else /* inside a requestFlow or responseFlow elements */
    {
        if(XMLString::equals(lname, kw_param))
        {  
            GetParameters(m_lev2, attrs); 
            /* must be parameters of a handler or a chain */
        }

        else if(XMLString::equals(lname, kw_hdl))
        {  
            m_lev2 = WSDD_HANDLER;
            m_pHandler = new WSDDHandler();
            ProcessAttributes(WSDD_HANDLER, attrs);
            /* get handler name and type if any */
        }
        else if(XMLString::equals(lname, kw_chain))
        {

        }
        else
        {
            /* error : unknown element type in wsdd file */
        }

    }
}

void WSDDDocumentXerces::startPrefixMapping(const XMLCh* const prefix,
                                            const XMLCh* const uri)
{
    m_NsStack[__XTRC(prefix)] = __XTRC(uri); 
    /* I think the same prifix cannot repeat ??? */
}

void WSDDDocumentXerces::endPrefixMapping(const XMLCh* const prefix)
{
//    string sPrifix = prefix;
    m_NsStack.erase(__XTRC(prefix)); 
    /* I think the same prifix cannot repeat ??? */
}

void  WSDDDocumentXerces::characters (const XMLCh *const chars,
                                      const unsigned int length)
{
    /* cout<<"==="<<XMLString::transcode(chars)<<"==="<<endl; */
}

const AxisChar* WSDDDocumentXerces::__XTRC(const XMLCh *pChar)
{
    if (true == (XMLString::transcode(pChar, m_Buffer, 
        TRANSCODE_BUFFER_SIZE-1)))
        return m_Buffer;
    else 
        return ""; 
}

void WSDDDocumentXerces::warning(const SAXParseException& exception)
{
}
void WSDDDocumentXerces::error(const SAXParseException& exception)
{
    m_bError = true;
}
void WSDDDocumentXerces::fatalError(const SAXParseException& exception)
{
    m_bFatalError = true;
}

