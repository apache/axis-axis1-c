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
            m_sMessage = "AxisConfigException:Transport layer is not" \
                " configured properly";
            break;
        case SERVER_CONFIG_LIBRARY_PATH_EMPTY:
            m_sMessage = "AxisConfigException:Library path is empty(Not" \
                " in server.wsdd file)";
            break; 
        case SOAP_VERSION_MISMATCH :
            m_sMessage = "AxisSoapException:Soap Version mismatch fault" \
                " occured";
            break;
        case SOAP_MUST_UNDERSTAND:
            m_sMessage = "AxisSoapException:Soap Must understand fault" \
                " occured";
            break;
        case CLIENT_SOAP_MESSAGE_INCOMPLETE:
            m_sMessage = "AxisSoapException:Received message is incomplete";
            break;
        case CLIENT_SOAP_SOAP_ACTION_EMTPY:
            m_sMessage = "AxisSoapException:Soap action is empty";
            break;
        case CLIENT_SOAP_SOAP_CONTENT_ERROR:
            m_sMessage = "AxisSoapException:Received content is faulty";
            break;
        case CLIENT_SOAP_NO_SOAP_METHOD:
            m_sMessage = "AxisSoapException:Request method is not a soap" \
                " method";
            break; 
        case CLIENT_SOAP_CONTENT_NOT_SOAP:
            m_sMessage = "AxisSoapException:Content is not a valid soap" \
                " message";
            break;
        case CLIENT_WSDD_SERVICE_NOT_FOUND:
            m_sMessage = "AxisWsddException:Requested service not found";
            break;
        case CLIENT_WSDD_METHOD_NOT_ALLOWED:
            m_sMessage = "AxisWsddException:Requested method is not allowed";
            break;
        case CLIENT_WSDD_PARA_TYPE_MISMATCH:
            m_sMessage = "AxisWsddException:Parameter type mismatch";
            break;
        case SERVER_WSDD_NO_HANDLERS_CONFIGURED:
            m_sMessage = "AxisWsddException:No handlers configured in" \
                " server.wsdd";
            break;
        case SERVER_ENGINE_COULD_NOT_LOAD_SRV:
            m_sMessage = "AxisEngineException:Could not load service";
            break;
        case SERVER_ENGINE_COULD_NOT_LOAD_HDL:
            m_sMessage = "AxisEngineException:Could not load handler";
            break;
        case SERVER_ENGINE_HANDLER_FAILED:
            m_sMessage = "AxisEngineException:Handler failed";
            break;
        case SERVER_ENGINE_WEBSERVICE_FAILED:
            m_sMessage = "AxisEngineException:Web Service failed";
            break;
        case SERVER_ENGINE_HANDLER_INIT_FAILED:
            m_sMessage = "AxisEngineException:Handler initialization failed";
            break;
        case SERVER_ENGINE_HANDLER_CREATION_FAILED:
            m_sMessage = "AxisEngineException:Handler creation failed";
            break;
        case SERVER_ENGINE_LIBRARY_LOADING_FAILED:
            m_sMessage = "AxisEngineException:Library loading failed";
            break;
        case SERVER_ENGINE_HANDLER_NOT_LOADED:
            m_sMessage = "AxisEngineException:Handler is not loaded";
            break;
        case SERVER_ENGINE_HANDLER_BEING_USED:
            m_sMessage = "AxisEngineException:Handler is being used";
            break;
        case SERVER_ENGINE_GET_HANDLER_FAILED:
            m_sMessage = "AxisEngineException:Get handler failed"; 
            break;
        case SERVER_ENGINE_WRONG_HANDLER_TYPE:
            m_sMessage = "AxisEngineException:Wrong handler type";
            break;
        case SERVER_TRANSPORT_RECEPTION_EXCEPTION:
            m_sMessage = "AxisTransportException:Problem occured when" \
                " receiving the stream";
            break;
        case SERVER_TRANSPORT_SENDING_EXCEPTION:
            m_sMessage = "AxisTransportException:Problem occured when" \
                " sending the stream";
            break;
        case SERVER_TRANSPORT_HTTP_EXCEPTION:
            m_sMessage = "AxisTransportException:HTTP transport error";
            break;
        case SERVER_TRANSPORT_PROCESS_EXCEPTION:
            m_sMessage = "AxisTransportException:HTTP Error, cannot" \
                " process response message";
            break;
        case SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE:
            m_sMessage = "AxisTransportException:Unknow HTTP response," \
                " cannot process response message";
            break;
        case SERVER_TRANSPORT_UNEXPECTED_STRING:
            m_sMessage = "AxisTransportException:Unexpected string";
            break;
        case SERVER_TRANSPORT_CHANNEL_INIT_ERROR:
            m_sMessage = "AxisTransportException:Cannot initialize a channel" \
                " to the remote end";
            break;
        case SERVER_TRANSPORT_SOCKET_CREATE_ERROR:
            m_sMessage = "AxisTransportException:Sockets error Couldn't" \
                " create socket"; 
            break;
        case SERVER_TRANSPORT_SOCKET_CONNECT_ERROR:
            m_sMessage = "AxisTransportException:Cannot open a channel to" \
                " the remote end, shutting down the channel";
            break;
        case SERVER_TRANSPORT_INVALID_SOCKET:
            m_sMessage = "AxisTransportException:Invalid socket. Socket may" \
                " not be open";
            break;
        case SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR:
            m_sMessage = "AxisTransportException:Output streaming error on" \
                " Channel while writing data";
            break;
        case SERVER_TRANSPORT_INPUT_STREAMING_ERROR:
            m_sMessage = "AxisTransportException:Input streaming error while" \
                " getting data";
            break;
        case SERVER_TRANSPORT_TIMEOUT_EXCEPTION:
            m_sMessage = "AxisTransportException:Channel error while waiting" \
                " for timeout";
            break;
        case SERVER_TRANSPORT_TIMEOUT_EXPIRED:
            m_sMessage = "AxisTransportException:Channel error connection" \
                " timeout before receving";
            break;
        case SERVER_TRANSPORT_BUFFER_EMPTY:
            m_sMessage = "AxisTransportException:Transport buffer is empty";
            break;
        case SERVER_PARSE_BUFFER_EMPTY:
            m_sMessage = "AxisParseException:Buffer received from the parser" \
                " is empty";
            break;
        case SERVER_PARSE_PARSER_FAILED:
            m_sMessage = "AxisParseException:XML_STATUS_ERROR thrown from" \
                " parser";
            break;
        case SERVER_PARSE_TRANSPORT_FAILED:
            m_sMessage = "AxisParseException:Error when getting the byte" \
                " stream from the transport";
            break;
        default:
            m_sMessage = "Unknown Exception has occured";

    }
    return m_sMessage;
}

