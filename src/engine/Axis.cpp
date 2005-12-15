/* -*- C++ -*- */
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
 *
 *
 * @author Sanjaya Sinharage (sanjayasing@opensource.lk)
 * @author Susantha Kumara (skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

#ifdef WIN32
#pragma warning (disable : 4503)
#endif

#ifdef WIN32
#include <Windows.h>            //for Sleep(0);
#else
#include <unistd.h>
#endif

#include <axis/Axis.hpp>

#ifdef AXIS_CLIENT_LIB
#include <axis/client/Call.hpp>
#include "AxisEngine.h"
#else
#include "server/ServerAxisEngine.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <iostream>

#include <axis/AxisUserAPI.hpp>

#include "../soap/SoapFault.h"
#include "../soap/URIMapping.h"
#include "../soap/SoapKeywordMapping.h"
#include "HandlerLoader.h"
#include "AppScopeHandlerPool.h"
#include "RequestScopeHandlerPool.h"
#include "SessionScopeHandlerPool.h"
#include "HandlerPool.h"
#include "SerializerPool.h"
#include "DeserializerPool.h"
#include "../wsdd/WSDDDeployment.h"
#include "../common/AxisUtils.h"
#include "../common/AxisConfig.h"
#include "../wsdd/WSDDKeywords.h"
#include "../common/AxisTrace.h"
#include "SOAPTransportFactory.h"
#include "XMLParserFactory.h"

AXIS_CPP_NAMESPACE_USE

#define BYTESTOREAD 64
// The relative location of the wsdl files hardcoded
#define WSDLDIRECTORY "/wsdls/"

// Define all global variables of the axisengine
#ifdef ENABLE_AXISTRACE
unsigned char chEBuf[1024];
#endif

// Synchronized global variables.
HandlerLoader* g_pHandlerLoader;
AppScopeHandlerPool* g_pAppScopeHandlerPool;
RequestScopeHandlerPool* g_pRequestScopeHandlerPool;
SessionScopeHandlerPool* g_pSessionScopeHandlerPool;
DeserializerPool* g_pDeserializerPool;
SerializerPool* g_pSerializerPool;
HandlerPool* g_pHandlerPool;
// Unsynchronized read-only global variables.
WSDDDeployment* g_pWSDDDeployment;
AxisConfig* g_pConfig;

//Keeps track of how many times initialize_module/uninitialize_module was called
static volatile long g_uModuleInitialize = 0;


void ModuleInitialize ()
{    
    // synchronized global variables.
    g_pHandlerLoader = new HandlerLoader ();
    g_pAppScopeHandlerPool = new AppScopeHandlerPool ();
    g_pRequestScopeHandlerPool = new RequestScopeHandlerPool ();
    g_pSessionScopeHandlerPool = new SessionScopeHandlerPool ();
    g_pDeserializerPool = new DeserializerPool ();
    g_pSerializerPool = new SerializerPool ();
    g_pHandlerPool = new HandlerPool ();
    // unsynchronized read-only global variables.
    g_pWSDDDeployment = new WSDDDeployment ();

	if( g_pConfig != NULL)
	{
		g_pConfig = new AxisConfig( g_pConfig);
	}
	else
	{
		g_pConfig = new AxisConfig();
	}
}

void ModuleUnInitialize ()
{
    // synchronized global variables.
    delete g_pAppScopeHandlerPool;
    delete g_pRequestScopeHandlerPool;
    delete g_pSessionScopeHandlerPool;
    delete g_pHandlerLoader;
    delete g_pDeserializerPool;
    delete g_pSerializerPool;
    delete g_pHandlerPool;
    // unsynchronized read-only global variables.
    delete g_pWSDDDeployment;
    delete g_pConfig;

	g_pConfig = NULL;
	g_pWSDDDeployment = NULL;

    AxisTrace::terminate();
}

#ifndef AXIS_CLIENT_LIB

STORAGE_CLASS_INFO int process_request(SOAPTransport* pStream)
{
    int Status = AXIS_FAIL;
    FILE* WsddFile = NULL;
    char ReadBuffer[BYTESTOREAD];
    ReadBuffer[0] = '\0';

    const WSDDServiceMap* pSrvMap = NULL;
    WSDDServiceMap::const_iterator iter;
    WSDDService* pService = NULL;

    /* If there is no transport object provided */
    if (!pStream)
        return AXIS_FAIL;

    switch (pStream->getProtocol())
    {
        case APTHTTP1_1:
        case APTHTTP1_0:
            // Handle the POST method
            if (AXIS_HTTP_POST == pStream->getSubProtocol())
            {
                AxisEngine *engine = new ServerAxisEngine ();
                if (engine)
                {
                    if (AXIS_SUCCESS == engine->initialize ())
                    {
                        Status = engine->process(pStream);
						if (AXIS_SUCCESS == Status)
						{
							pStream->flushOutput();
						}
						else
                        {
                            ServerAxisEngine* pObjTempServer = (ServerAxisEngine*) engine;
                            pObjTempServer->setFaultOutputStream(Status, pStream);
                            pStream->flushOutput();
                            pObjTempServer = NULL;
                            Status = AXIS_SUCCESS;
                        }
                    }
                    delete engine;
                }
            }
          // Handle the GET method
            else if (AXIS_HTTP_GET == pStream->getSubProtocol())
            {
                // get the uri path
                // i.e "/abc/xyz/" part of http://somehost/abc/xyz/
                string sUriWOAxis = pStream->getTransportProperty(SERVICE_URI);
                string sServiceName;
                bool bNoExt = true;
                if (sUriWOAxis == "/")
                {
                    bNoExt = false;
                    sUriWOAxis = "";
                }

                if (sUriWOAxis.empty ())
                {
                    pSrvMap = g_pWSDDDeployment->getWSDDServiceMap ();
                    if (!pSrvMap)
                    {
                        // Samisa: the string continuation lines in the following
                        // code segments should *NOT* be indented
                        // in order to make sure the HTML is indented properly.
                        pStream->sendBytes("<html> \n\
\t<head>\n\
\t\t<title>Welcome to Axis C++</title>\n\
\t</head>\n\
\t<body>\n\
\t\t<h1 align=\"center\">Welcome to Axis C++</h1>\n\
\t\t<br>\n\
\t\t<h2>Deployment Descriptor Not Found</h2>\n\
\t\t<br>\n\
\t</body>\n\
</html>\n", NULL);
                        return AXIS_FAIL;
                    }
                    pStream->sendBytes("<html>\n\
\t<head>\n\
\t\t<title>Welcome to Axis C++</title>\n\
\t</head>\n\
\t<body>\n\
\t\t<h1 align=\"center\">Welcome to Axis C++</h1>\n\
\t\t<br>\n\
\t\t<h2 align=\"center\">List of Deployed Web services</h2>\n\
\t\t<br>\n\
\t\t<table width=\"100%\" border=1 align=\"center\">\n\
\t\t\t<tbody>\n", NULL);

                    pStream->sendBytes
                        ("\t\t\t\t<tr>\n\
\t\t\t\t\t<td width=\"20%\"><b>Web Service</b></td>\n\
\t\t\t\t\t<td width=\"10%\" align=\"left\"><b>WSDL</b></td>\n\
\t\t\t\t\t<td width=\"70%\"><b>Description</b></td>\n\
\t\t\t\t</tr>\n", NULL);
                    for (iter = pSrvMap->begin (); iter != pSrvMap->end ();
                        iter++)
                    {
                        pService = (*iter).second;
                        pStream->sendBytes("\t\t\t\t<tr>\n\
\t\t\t\t\t<td width=\"20%\">", NULL);
                        pStream->sendBytes((char*) pService->
                            getServiceName (), NULL);
                        pStream->sendBytes
                            ("</td>\n\
\t\t\t\t\t<td width=\"10%\" align=\"left\">\n\
\t\t\t\t\t\t<a href=\"./",
                            NULL);
                        //if (bNoExt) pStream->sendBytes("axis/", NULL);
                        pStream->sendBytes((char*) pService->
                            getServiceName (), NULL);
                        pStream->sendBytes("?wsdl", NULL);
                        pStream->sendBytes("\">wsdl</a>\n\
\t\t\t\t\t</td>\n\
\t\t\t\t\t<td width=\"70%\">", NULL);
                        pStream->sendBytes((char*) pService->
                            getDescription (), NULL);
                        pStream->sendBytes("</td>\n\
\t\t\t\t</tr>\n", NULL);
                    }
                    pStream->sendBytes("\t\t\t</tbody>\n\
\t\t</table>\n", NULL);
                    pStream->sendBytes
                        ("\t\t<br><p align=\"center\">Copyright  2001-2003 The Apache Software Foundation<br></p>\n\t</body>\n</html>\n", NULL);
                        Status = AXIS_SUCCESS;
                }
                else
                {
					sServiceName = g_pConfig->getAxisConfProperty(AXCONF_AXISHOME);
                    sServiceName += WSDLDIRECTORY + sUriWOAxis + ".wsdl";
                    // Check whether wsdl file is available
                    if ((WsddFile = fopen (sServiceName.c_str (), "r")) == NULL)
                    {
                        pStream->sendBytes("<h3>Url not available</h3>",
                            NULL);
                        Status = AXIS_SUCCESS;
                        // Handle the error
                    }
                    else
                    {
                        int charcount = 0;
                        while ((charcount = fread (ReadBuffer, 1,
                            BYTESTOREAD - 1, WsddFile)) != 0)
                        {
                            *(ReadBuffer + charcount) = '\0';
                            pStream->sendBytes(ReadBuffer,
                                NULL);
                        }
                        Status = AXIS_SUCCESS;
                        fclose (WsddFile);
                    }
                }
            }
            
	    break;

        default:
            pStream->sendBytes("Unknown Protocol", NULL);
            break;
    }

    return Status;
}

#endif

#ifdef WIN32

static volatile long g_uModuleInitializing = 0; 
static void start_initializing() 
{ 
    while (InterlockedIncrement((LONG*)&g_uModuleInitializing) != 1) { 
        InterlockedDecrement((LONG*)&g_uModuleInitializing); 
    } 
} 
static void done_initializing() 
{ 
    InterlockedDecrement((LONG*)&g_uModuleInitializing); 
} 

#else

#include <pthread.h>
static pthread_mutex_t initializingMutex = PTHREAD_MUTEX_INITIALIZER;

static void start_initializing()
{
    pthread_mutex_lock(&initializingMutex);
}

static void done_initializing()
{
    pthread_mutex_unlock(&initializingMutex);
}

#endif
 


extern "C" {
STORAGE_CLASS_INFO
int initialize_module (int bServer)
{
    start_initializing();
    
    int status = AXIS_SUCCESS;

    try
    {
        if (g_uModuleInitialize == 0)
        {
            // order of these initialization method invocation should not be changed
            AxisEngine::m_bServer = bServer;
            AxisUtils::initialize ();
            WSDDKeywords::initialize ();
            SoapKeywordMapping::initialize ();
            TypeMapping::initialize ();
            URIMapping::initialize ();
            SoapFault::initialize ();
            ModuleInitialize ();

            if (bServer) // no client side wsdd processing at the moment
            {
    		    // Read from the configuration file
                status = g_pConfig->readConfFile (); 

                if (status == AXIS_SUCCESS)
                {					
					try
					{            
						XMLParserFactory::initialize();
					}
					catch (AxisException& e)
                    {
                        throw AxisEngineException(e.getExceptionCode(), e.what());
                    }

                    char *pWsddPath = g_pConfig->getAxisConfProperty(AXCONF_WSDDFILEPATH);
#if defined(ENABLE_AXISTRACE)
                    status = AxisTrace::openFile ();
                    if (status == AXIS_FAIL)
                    {
                        // Samisa - make sure that we start service, even if we cannot open log file
                        // Hence do not return from here, may be we can log an error here
                    }
#endif
                    try
                    {            
                        if (AXIS_SUCCESS != g_pWSDDDeployment->loadWSDD (pWsddPath))
                        {
                            status = AXIS_FAIL;
                        }
                    }
                    catch (AxisException& e)
                    {
                        throw AxisEngineException(e.getExceptionCode(), e.what());
                    }
                }
                else
                {
                    status = AXIS_FAIL;
                }
           }
           else if (bServer == 0)      // client side module initialization
           {
                status = g_pConfig->readConfFile (); //Read from the configuration file 

                if (status == AXIS_SUCCESS)
                {
#if defined(ENABLE_AXISTRACE)
                    status = AxisTrace::openFileByClient ();
#endif
                   XMLParserFactory::initialize();
                   SOAPTransportFactory::initialize();

                   char *	pClientWsddPath = g_pConfig->getAxisConfProperty(AXCONF_CLIENTWSDDFILEPATH);
    
// May be there is no client side handlers configured. So may not have CLIENTWSDDFILEPATH entry in axiscpp.conf 
                   if (pClientWsddPath)
                   {
                       if (AXIS_SUCCESS != g_pWSDDDeployment->loadWSDD (pClientWsddPath))
                       {
                           status = AXIS_FAIL;
                       }
                   }
                }
                else
                {
                    AXISTRACE3( "Reading from the configuration file failed. \
								Check for error in the configuration file.\n\
								Handlers and logging are not working");
                    /* TODO:Improve the AxisTrace so that it will log these kind of 
                     * messages into a log file according to the critical level 
                     * specified.
                     */
                }
           }
           else
           {
               /* Ok if we can't read config file */
               status = AXIS_SUCCESS;
           }
       }
       else if (AxisEngine::m_bServer != bServer)
       {
		   throw AxisEngineException(SERVER_ENGINE_EXCEPTION);
       }
    }
    catch (...)
    {
        done_initializing();
        throw;
    }

    ++g_uModuleInitialize;
    done_initializing();

    return status;
}
}


extern "C" {
STORAGE_CLASS_INFO
int uninitialize_module ()
{
    start_initializing();

    try
    {
        if (g_uModuleInitialize > 0)
        {
            if (--g_uModuleInitialize == 0)
            {
                TypeMapping::uninitialize();
                URIMapping::uninitialize();
                if (!AxisEngine::m_bServer) // we have to deal with transport factory only if it is the client
                    SOAPTransportFactory::uninitialize();
                ModuleUnInitialize();
                SoapKeywordMapping::uninitialize();
                XMLParserFactory::uninitialize();
            }
        }
    }
    catch (...)
    {
        done_initializing();
        throw;
    }

    done_initializing();

    return AXIS_SUCCESS;
}
}


void Ax_Sleep (int nTime)
{
#ifdef WIN32
    Sleep (0);
#else
    sleep (0);
#endif
}


// Axis class method implementations

void Axis::initialize(bool bIsServer)
{
    initialize_module(bIsServer);
}

void Axis::terminate()
{
    uninitialize_module();
}

void Axis::AxisDelete(void *pValue, XSDTYPE type)
{
    if (pValue != NULL)
    {
        switch (type)
        {
            case XSD_DURATION:
            {
                delete (xsd__duration*) pValue;
                pValue = NULL;
    			break;
            }
            case XSD_DATETIME:
            {
                delete (xsd__dateTime*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_TIME:
            {
                delete (xsd__time*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_DATE:
            {
                delete (xsd__date*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_GYEARMONTH:
            {
                delete (xsd__gYearMonth*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_GYEAR:
            {
                delete (xsd__gYear*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_GMONTHDAY:
            {
                delete (xsd__gMonthDay*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_GDAY:
            {
                delete (xsd__gDay*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_GMONTH:
            {
                delete (xsd__gMonth*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_STRING:
            {
                delete [] (xsd__string) pValue;
                pValue = NULL;
                break;
            }
            case XSD_NORMALIZEDSTRING:
            {
                delete [] (xsd__normalizedString) pValue;
                pValue = NULL;
                break;
            }
            case XSD_TOKEN:
            {
                delete [] (xsd__token) pValue;
                pValue = NULL;
                break;
            }
            case XSD_LANGUAGE:
            {
                delete [] (xsd__language) pValue;
                pValue = NULL;
                break;
            }
            case XSD_NAME:
            {
                delete [] (xsd__Name) pValue;
                pValue = NULL;
                break;
            }
            case XSD_NCNAME:
            {
                delete [] (xsd__NCName) pValue;
                pValue = NULL;
                break;
            }
            case XSD_ID:
            {
                delete [] (xsd__ID) pValue;
                pValue = NULL;
                break;
            }
            case XSD_IDREF:
            {
                delete [] (xsd__IDREF) pValue;
                pValue = NULL;
                break;
            }
            case XSD_IDREFS:
            {
                delete [] (xsd__IDREFS) pValue;
                pValue = NULL;
                break;
            }
            case XSD_ENTITY:
            {
                delete [] (xsd__ENTITY) pValue;
                pValue = NULL;
                break;
            }
            case XSD_ENTITIES:
            {
                delete [] (xsd__ENTITIES) pValue;
                pValue = NULL;
                break;
            }
            case XSD_NMTOKEN:
            {
                delete [] (xsd__NMTOKEN) pValue;
                pValue = NULL;
                break;
            }
            case XSD_NMTOKENS:
            {
                delete [] (xsd__NMTOKENS) pValue;
                pValue = NULL;
                break;
            }
            case XSD_BOOLEAN:
            {
                delete (xsd__boolean*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_BASE64BINARY:
            {
				if(	((xsd__base64Binary*) pValue)->__ptr != NULL)
				{
					delete [] ((xsd__base64Binary*) pValue)->__ptr;
					((xsd__base64Binary*) pValue)->__ptr = NULL;
				}

                delete (xsd__base64Binary*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_HEXBINARY:
            {
				if(	((xsd__hexBinary*) pValue)->__ptr != NULL)
				{
					delete [] ((xsd__hexBinary*) pValue)->__ptr;
					((xsd__hexBinary*) pValue)->__ptr = NULL;
				}

                delete (xsd__hexBinary*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_FLOAT:
            {
                delete (xsd__float*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_DECIMAL:
            {
                delete (xsd__decimal*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_NONPOSITIVEINTEGER:
            {
                delete (xsd__nonPositiveInteger*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_NEGATIVEINTEGER:
            {
                delete (xsd__negativeInteger*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_INTEGER:
            {
                delete (xsd__integer*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_LONG:
            {
                delete (xsd__long*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_INT:
            {
                delete (xsd__int*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_SHORT:
            {
                delete (xsd__short*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_BYTE:
            {
                delete (xsd__byte*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_NONNEGATIVEINTEGER:
            {
                delete (xsd__nonNegativeInteger*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_UNSIGNEDLONG:
            {
                delete (xsd__unsignedLong*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_UNSIGNEDINT:
            {
                delete (xsd__unsignedInt*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_UNSIGNEDSHORT:
            {
                delete (xsd__unsignedShort*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_UNSIGNEDBYTE:
            {
                delete (xsd__unsignedByte*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_POSITIVEINTEGER:
            {
                delete (xsd__positiveInteger*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_DOUBLE:
            {
                delete (xsd__double*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_ANYURI:
            {
                delete [] (xsd__anyURI) pValue;
                pValue = NULL;
                break;
            }
            case XSD_QNAME:
            {
                delete [] (xsd__QName) pValue;
                pValue = NULL;
                break;
            }
            case XSD_NOTATION:
            {
                delete [] (xsd__NOTATION) pValue;
                pValue = NULL;
                break;
            }
            case USER_TYPE:
                // The USER_TYPE object should be cleared by the Application
                break;
            case XSD_ARRAY:
            {
                delete (Axis_Array*) pValue;
                pValue = NULL;
                break;
            }
            case XSD_ANY:
            case ATTACHMENT:
            case XSD_UNKNOWN:
            default:
    			;
        }
    }
}
