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
        case SERVER_TEST_EXCEPTION:
            m_sMessage = "This is a testing error";
            break;
        case AXISC_NODE_VALUE_MISMATCH_EXCEPTION:
            m_sMessage = "Cannot deserialize the requested element";
            break;
        case SERVER_CONFIG_TRANSPORT_CONF_FAILED:
            m_sMessage = "Transport layer is not configured properly";
            break;
        case SERVER_CONFIG_LIBRARY_PATH_EMPTY:
            m_sMessage = "Library path is empty(Not in server.wsdd file)";
            break; 
        case SOAP_VERSION_MISMATCH :
            m_sMessage = "Soap Version mismatch fault occured";
            break;
        case SOAP_MUST_UNDERSTAND:
            m_sMessage = "Soap Must understand fault occured";
            break;
        case CLIENT_SOAP_MESSAGE_INCOMPLETE:
            m_sMessage = "Received message is incomplete";
            break;
        case CLIENT_SOAP_SOAP_ACTION_EMTPY:
            m_sMessage = "Soap action is empty";
            break;
        case CLIENT_SOAP_SOAP_CONTENT_ERROR:
            m_sMessage = "Received content is faulty";
            break;
        case CLIENT_SOAP_NO_SOAP_METHOD:
            m_sMessage = "Request method is not a soap method";
            break; 
        case CLIENT_WSDD_SERVICE_NOT_FOUND:
            m_sMessage = "Requested service not found";
            break;
        case CLIENT_WSDD_METHOD_NOT_ALLOWED:
            m_sMessage = "Requested method is not allowed";
            break;
        case CLIENT_WSDD_PARA_TYPE_MISMATCH:
            m_sMessage = "Parameter type mismatch";
            break;
        case SERVER_WSDD_NO_HANDLERS_CONFIGURED:
            m_sMessage = "No handlers configured in server.wsdd";
            break;
        case SERVER_ENGINE_COULD_NOT_LOAD_SRV:
            m_sMessage = "Could not load service";
            break;
        case SERVER_ENGINE_COULD_NOT_LOAD_HDL:
            m_sMessage = "Could not load handler";
            break;
        case SERVER_ENGINE_HANDLER_FAILED:
            m_sMessage = "Handler failed";
            break;
        case SERVER_ENGINE_WEBSERVICE_FAILED:
            m_sMessage = "Web Service failed";
            break;
        case SERVER_ENGINE_HANDLER_INIT_FAILED:
            m_sMessage = "Handler initialization failed";
            break;
        case SERVER_ENGINE_HANDLER_CREATION_FAILED:
            m_sMessage = "Handler creation failed";
            break;
        case SERVER_ENGINE_LIBRARY_LOADING_FAILED:
            m_sMessage = "Library loading failed";
            break;
        case SERVER_ENGINE_HANDLER_NOT_LOADED:
            m_sMessage = "Handler is not loaded";
            break;
        case SERVER_ENGINE_HANDLER_BEING_USED:
            m_sMessage = "Handler is being used";
            break;
        case SERVER_ENGINE_GET_HANDLER_FAILED:
            m_sMessage = "Get handler failed"; 
            break;
        case SERVER_ENGINE_WRONG_HANDLER_TYPE:
            m_sMessage = "Wrong handler type";
            break;
        case SERVER_TRANSPORT_RECEPTION_EXCEPTION:
            m_sMessage = "Problem occured when receiving the stream";
            break;
        case SERVER_TRANSPORT_SENDING_EXCEPTION:
            m_sMessage = "Problem occured when sending the stream";
            break;
        case SERVER_TRANSPORT_HTTP_EXCEPTION:
            m_sMessage = "HTTP transport error";
            break;
        case SERVER_TRANSPORT_PROCESS_EXCEPTION:
            m_sMessage = "HTTP Error, cannot process response message";
            break;
        case SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE:
            m_sMessage = "Unknow HTTP response, cannot process response message";
            break;

        default:
            m_sMessage = "Unknown Exception has occured";

    }
    return m_sMessage;
}

