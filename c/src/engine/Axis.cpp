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
 *
 * @author Sanjaya Sinharage (sanjayasing@opensource.lk)
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */
#ifdef WIN32
#pragma warning (disable : 4503)
#endif

#ifdef WIN32
#include <Windows.h>            //for Sleep(0);
#else
#include <unistd.h>
#endif

#ifdef AXIS_CLIENT_LIB
#include <axis/client/Call.h>
#else
#include "server/ServerAxisEngine.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <axis/server/Packet.h>
#include <string>
#include <map>

#include <axis/server/SoapFault.h>
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
#include <axis/server/AxisConfig.h>
#include "../wsdd/WSDDKeywords.h"
#include <axis/server/AxisTrace.h>
#ifdef USE_XERCES_PARSER
#include <xercesc/util/PlatformUtils.hpp>
#endif

#define BYTESTOREAD 64
// The relative location of the wsdl files hardcoded
#define WSDLDIRECTORY "/wsdls/"

// Define all global variables of the axisengine
#ifdef _AXISTRACE
unsigned char chEBuf[1024];
#endif

#ifdef USE_XERCES_PARSER
XERCES_CPP_NAMESPACE_USE
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
AxisTrace* g_pAT;


#ifndef AXIS_CLIENT_LIB

extern "C" int process_request (Ax_soapstream* stream)
{
    int Status = AXIS_FAIL;
    FILE* WsddFile;
    char ReadBuffer[BYTESTOREAD];
    ReadBuffer[0] = '\0';

    const WSDDServiceMap* pSrvMap = NULL;
    WSDDServiceMap::const_iterator iter;
    WSDDService* pService = NULL;

    /* If there is no send function given in the Ax_soapstream struct */
    if (!stream->transport.pSendFunct)
        return AXIS_FAIL;

    switch (stream->trtype)
    {
        case APTHTTP:
            // Handle the POST method
            if (stream->so.http->ip_method == AXIS_HTTP_POST)
            {
                AxisEngine *engine = new ServerAxisEngine ();
                if (engine)
                {
                    if (AXIS_SUCCESS == engine->initialize ())
                    {
                        Status = engine->process (stream);
                        if(AXIS_SUCCESS != Status)
                        {
                            ServerAxisEngine* objTempServer = (ServerAxisEngine*) engine;
                            objTempServer->setFaultOutputStream(Status, stream);
                            objTempServer = NULL;
                            Status = AXIS_SUCCESS;
                        }
                    }
                    delete engine;
                }
            }
          // Handle the GET method
            else if (stream->so.http->ip_method == AXIS_HTTP_GET)
            {
                // get the uri path
                // i.e "/abc/xyz/" part of http://somehost/abc/xyz/
                string sUriWOAxis =
                    stream->transport.pGetTrtFunct (SERVICE_URI, stream);
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
                        stream->transport.pSendFunct ("<html><body>\
                            <h1 align=\"center\">Welcome to Axis C++</h1>\
                            <br>\
                            <h2>Deployment Descripter Not Found</h2>\
                            <br>\
                            </body></html>", NULL, stream);
                        return AXIS_FAIL;
                    }
                    stream->transport.pSendFunct ("<html><body>\
                        <h1 align=\"center\">Welcome to Axis C++</h1>\
                        <br>\
                        <h2 align=\"center\">List of Deployed Web services<br></h2>\
                        <table width=\"100%\" border=1 align=\"center\"><tbody>", NULL, stream);

                    stream->transport.pSendFunct
                        ("<tr><td width=\"20%\"><b>Web Service</b></td>\
                        <td width=\"10%\" align=\"left\"><b>WSDL</b></td>\
                        <td width=\"70%\"><b>Description</b></td></tr>", NULL, stream);
                    for (iter = pSrvMap->begin (); iter != pSrvMap->end ();
                        iter++)
                    {
                        pService = (*iter).second;
                        stream->transport.
                            pSendFunct ("<tr><td width=\"20%\">", NULL,
                                            stream);
                        stream->transport.pSendFunct ((char*) pService->
                            getServiceName (), NULL, stream);
                        stream->transport.pSendFunct
                            ("</td><td width=\"10%\" align=\"left\"><a href=\"./",
                            NULL, stream);
                        if (bNoExt) stream->transport.pSendFunct ("axis/", NULL,
                            stream);
                        stream->transport.pSendFunct ((char*) pService->
                            getServiceName (), NULL, stream);
                        stream->transport.pSendFunct ("?wsdl", NULL, stream);
                        stream->transport.pSendFunct
                            ("\">wsdl</a></td><td width=\"70%\">", NULL, stream);
                        stream->transport.pSendFunct ((char*) pService->
                            getDescription (), NULL, stream);
                        stream->transport.pSendFunct ("</td></tr>", NULL, stream);
                    }
                    stream->transport.pSendFunct ("</tbody></table>", NULL,
                        stream);
                    stream->transport.pSendFunct
                        ("<br><p align=\"center\">Copyright © 2001-2003 The Apache Software Foundation<br></p></body></html>", NULL, stream);
                        Status = AXIS_SUCCESS;
                }
                else
                {
                    sServiceName = g_pConfig->getAxisHomePath ();
                    sServiceName += WSDLDIRECTORY + sUriWOAxis + ".wsdl";
                    // Check whether wsdl file is available
                    if ((WsddFile = fopen (sServiceName.c_str (), "r")) == NULL)
                    {
                        stream->transport.pSendFunct ("<h3>Url not available</h3>",
                            NULL, stream);
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
                            stream->transport.pSendFunct (ReadBuffer,
                                NULL, stream);
                        }
                        Status = AXIS_SUCCESS;
                        fclose (WsddFile);
                    }
                }
            }
            
	    break;

        default:
            stream->transport.pSendFunct ("Unknown Protocol", NULL, stream);
            break;
    }

    return Status;
}

#endif

extern "C" int initialize_module (int bServer)
{
    int status = 0;
    // order of these initialization method invocation should not be changed
#ifdef USE_XERCES_PARSER
    XMLPlatformUtils::Initialize ();
#endif
    AxisEngine::m_bServer = bServer;
    AxisUtils::initialize ();
    WSDDKeywords::initialize ();
    SoapKeywordMapping::initialize ();
    TypeMapping::initialize ();
    URIMapping::initialize ();
    SoapFault::initialize ();
#ifdef AXIS_CLIENT_LIB
    CallBase::s_Initialize ();
#endif
    IWrapperSoapDeSerializer::s_Initialize ();
    IWrapperSoapSerializer::s_Initialize ();
    IMessageData::s_Initialize ();
    ModuleInitialize ();
    if (bServer) // no client side wsdd processing at the moment
    {
        int status = g_pConfig->readConfFile (); /* Read from the configuration
						  * file 
						  */
        if (status == AXIS_SUCCESS)
        {
            char *pWsddPath = g_pConfig->getWsddFilePath ();
#if defined(__AXISTRACE__)
            status = g_pAT->openFile ();
            if (status == AXIS_FAIL)
            {
                return AXIS_FAIL;
            }
#endif
            if (AXIS_SUCCESS != g_pWSDDDeployment->loadWSDD (pWsddPath))
                    return AXIS_FAIL;
        }
        else
        {
            return AXIS_FAIL;
        }

    }
    else if (bServer == 0)      // client side module initialization
    {
        int status = g_pConfig->readConfFile (); /* Read from the configuration
						  * file 
						  */
        if (status == AXIS_SUCCESS)
        {
#if defined(__AXISTRACE__)
            status = g_pAT->openFileByClient ();
            if (status == AXIS_FAIL)
            {
                return AXIS_FAIL;
            }
#endif
            char *pClientWsddPath = g_pConfig->getClientWsddFilePath ();
            /* May be there is no client side handlers configured. So may not 
	     * have CLIENTWSDDFILEPATH entry in axiscpp.conf 
	     */
            if (!pClientWsddPath)
                return status;
            if (AXIS_SUCCESS != g_pWSDDDeployment->loadWSDD (pClientWsddPath))
                return AXIS_FAIL;
        }
        else
        {
            return AXIS_FAIL;
        }
    }
    return AXIS_SUCCESS;
}

extern "C" int uninitialize_module ()
{
#ifdef USE_XERCES_PARSER
    XMLPlatformUtils::Terminate ();
#endif
    ModuleUnInitialize ();
    SoapKeywordMapping::uninitialize ();
    return AXIS_SUCCESS;
}

void Ax_Sleep (int nTime)
{
#ifdef WIN32
    Sleep (0);
#else
    sleep (0);
#endif
}

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
    g_pConfig = new AxisConfig ();
    g_pAT = new AxisTrace ();
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
    delete g_pAT;

}
