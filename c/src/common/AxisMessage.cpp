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
 *   @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */
 
#include <axis/server/AxisMessage.h>

const string AxisMessage::getMessage(int iExceptionCode)
{
    switch(iExceptionCode)
    {
        case AXISC_SERVICE_THROWN_EXCEPTION:
            m_sMessage = "A service has thrown an exception. see detail";
            break;
        case SERVER_TESTEXCEPTION:
            m_sMessage = "This is a testing error";
            break;
        case AXISC_NODEVALUE_MISMATCH_EXCEPTION:
            m_sMessage = "Cannot deserialize the requested element";
            break;
        case SERVER_CONFIG_TRANSPORTCONFFAILED:
            m_sMessage = "Transport layer is not configured properly";
            break;
        case SERVER_CONFIG_LIBRARYPATHEMPTY:
            m_sMessage = "Library path is empty(Not in server.wsdd file)";
            break; 
        case SOAP_VERSIONMISMATCH :
            m_sMessage = "Soap Version mismatch fault occured";
            break;
        case SOAP_MUSTUNDERSTAND:
            m_sMessage = "Soap Must understand fault occured";
            break;
        case CLIENT_SOAP_MESSAGEINCOMPLETE:
            m_sMessage = "Received message is incomplete";
            break;
        case CLIENT_SOAP_SOAPACTIONEMTPY:
            m_sMessage = "Soap action is empty";
            break;
        case CLIENT_SOAP_SOAPCONTENTERROR:
            m_sMessage = "Received content is faulty";
            break;
        case CLIENT_SOAP_NOSOAPMETHOD:
            m_sMessage = "Request method is not a soap method";
            break; 
        case CLIENT_WSDD_SERVICENOTFOUND:
            m_sMessage = "Requested service not found";
            break;
        case CLIENT_WSDD_METHODNOTALLOWED:
            m_sMessage = "Requested method is not allowed";
            break;
        case CLIENT_WSDD_PARATYPEMISMATCH:
            m_sMessage = "Parameter type mismatch";
            break;
        case SERVER_WSDD_NOHANDLERSCONFIGURED:
            m_sMessage = "No handlers configured in server.wsdd";
            break;
        case SERVER_ENGINE_COULDNOTLOADSRV:
            m_sMessage = "Could not load service";
            break;
        case SERVER_ENGINE_COULDNOTLOADHDL:
            m_sMessage = "Could not load handler";
            break;
        case SERVER_ENGINE_HANDLERFAILED:
            m_sMessage = "Handler failed";
            break;
        case SERVER_ENGINE_WEBSERVICEFAILED:
            m_sMessage = "Web Service failed";
            break;
        case SERVER_ENGINE_HANDLERINITFAILED:
            m_sMessage = "Handler initialization failed";
            break;
        case SERVER_ENGINE_HANDLERCREATIONFAILED:
            m_sMessage = "Handler creation failed";
            break;
        case SERVER_ENGINE_LIBRARYLOADINGFAILED:
            m_sMessage = "Library loading failed";
            break;
        case SERVER_ENGINE_HANDLERNOTLOADED:
            m_sMessage = "Handler is not loaded";
            break;
        case SERVER_ENGINE_HANDLERBEINGUSED:
            m_sMessage = "Handler is being used";
            break;
        case SERVER_ENGINE_GETHANDLERFAILED:
            m_sMessage = "Get handler failed"; 
            break;
        case SERVER_ENGINE_WRONGHANDLERTYPE:
            m_sMessage = "Wrong handler type";
            break;
        case SERVER_TRANSPORT_RECEPTIONEXCEPTION:
            m_sMessage = "Problem occured when receiving the stream";
            break;
        case SERVER_TRANSPORT_SENDINGEXCEPTION:
            m_sMessage = "Problem occured when sending the stream";
            break;
        case SERVER_TRANSPORT_HTTP_EXCEPTION:
            m_sMessage = "HTTP transport error";
            break;

        default:
            m_sMessage = "Unknown Exception has occured";

    }
    return m_sMessage;
}

