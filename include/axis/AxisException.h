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
 *
 */
/**
 * @file AxisException.hpp
 *
 *
 */
#ifndef AXISEXCEPTION_INCLUDED
#define AXISEXCEPTION_INCLUDED

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE C APIS.                                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifdef __cplusplus
 extern "C" {
#endif


#include <axis/GDefine.h>

/*
 * The following enumeration is used to serve the Axis C++ codes for
 * faults.
 */


/**
 * @enum AXISC_EXCEPTIONS
 * Enumeration of exception codes used by AxisException
 */
typedef enum 
{
    /*The notation used for naming these exceptions is as follows
     *CLIENT at the beginning means when this interpreted as a soap fault
     *    it's fault code is CLIENT
     *SERVER at the beginning means when this interpreted as a soap fault
     *    it's fault code is SERVER
     *SOAP that comes next to CLIENT/SERVER means this is a soap releated
     *    exception
     *ENGINE that comes next to CLIENT/SERVER means this is a axiscc++ engine
     *    related exception
     *WSDD that comes next to CLIENT/SERVER means this is a wsdd releated
     *    exception
     *TRANSPORT that comes next to CLIENT/SERVER means this is a transport releated
     *    exception
     *CONFIG that comes next to CLIENT/SERVER means this is a axiscc++ configuration
     *    related exception
     *AXISCC ?
     */
    /* SOAP faults */
        /** AxiscSoapException:Soap Version mismatch fault occurred */
/*0*/    SOAP_VERSION_MISMATCH, 
        /** AxiscSoapException:Soap Must understand fault occurred */
/*1*/    SOAP_MUST_UNDERSTAND,    

    /* Client faults */
        /**
         * AxiscSoapException:Received message is incomplete
         */
/*2*/    CLIENT_SOAP_MESSAGE_INCOMPLETE,
        /**
         * AxiscSoapException:Soap action is empty
         */
/*3*/    CLIENT_SOAP_SOAP_ACTION_EMTPY,
        /**
         * AxiscSoapException:Received content is faulty
         */
/*4*/    CLIENT_SOAP_SOAP_CONTENT_ERROR,
        /**
         * AxiscSoapException:Request method is not a soap method
         */
/*5*/    CLIENT_SOAP_NO_SOAP_METHOD,
        /**
         * AxiscSoapException:Content is not a valid soap message
         */
/*6*/    CLIENT_SOAP_CONTENT_NOT_SOAP,
        /**
         * AxiscWsddException:Requested service not found
         */
/*7*/    CLIENT_WSDD_SERVICE_NOT_FOUND,
        /**
         * AxiscWsddException:Requested method is not allowed
         */
/*8*/    CLIENT_WSDD_METHOD_NOT_ALLOWED,
        /**
         * AxiscWsddException: Parameter type mismatch
         */
/*9*/    CLIENT_WSDD_PARA_TYPE_MISMATCH,
        /**
         * 
         */
/*10*/   CLIENT_ENGINE_CLIENT_HANDLER_FAILED,
        /**
         * HTTPTransportException:Generic client transport exception
         */
/*11*/   CLIENT_TRANSPORT_EXCEPTION,
        /**
         * HTTPTransportException:Client failed to open connection to server
         */
/*12*/   CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED,
        /**
         * HTTPTransportException:Client attempted to use SSL functions without the proper prerquistes
         */
/*13*/   CLIENT_TRANSPORT_TYPE_MISMATCH,
        /**
         * CLIENT_TRANSPORT_HAS_NO_UNSECURE_TRANSPORT_LAYER
         */
/*14*/   CLIENT_TRANSPORT_HAS_NO_UNSECURE_TRANSPORT_LAYER,
        /**
         * HTTPTransportException:Client attempted to use secure transport (https) without an SSL layer
         */
/*15*/   CLIENT_TRANSPORT_HAS_NO_SECURE_TRANSPORT_LAYER,
        /**
         * 
         */
/*16*/   CLIENT_SSLCHANNEL_RECEPTION_EXCEPTION,
        /**
         * 
         */
/*17*/   CLIENT_SSLCHANNEL_SENDING_EXCEPTION,
        /**
         * 
         */
/*18*/   CLIENT_SSLCHANNEL_CHANNEL_INIT_ERROR,
        /**
         * 
         */
/*19*/   CLIENT_SSLCHANNEL_SOCKET_CREATE_ERROR,
        /**
         * 
         */
/*20*/   CLIENT_SSLCHANNEL_SOCKET_CONNECT_ERROR,
        /**
         * 
         */
/*21*/   CLIENT_SSLCHANNEL_INVALID_SOCKET_ERROR,
        /**
         * Check implementation specific error message
         */
/*22*/   CLIENT_SSLCHANNEL_CONTEXT_CREATE_ERROR,
        /**
         * Check implementation specific error message
         */
/*23*/   CLIENT_SSLCHANNEL_ERROR,
        /**
         * AxiscSoapException:Content is not unique within the MIME message
         */
/*24*/   CLIENT_MIME_CONTENT_ID_NOT_UNIQUE,

    /* Server faults */
        /**
         * SERVER_ENGINE_EXCEPTION
         */
/*25*/    SERVER_ENGINE_EXCEPTION,
        /**
         * AxiscEngineException:Could not load service
         */
/*26*/    SERVER_ENGINE_COULD_NOT_LOAD_SRV,
        /**
         * AxiscEngineException:Could not load handler
         */
/*27*/    SERVER_ENGINE_COULD_NOT_LOAD_HDL,
        /**
         * DLOPEN FAILED in loading transport library
         */
/*28*/    SERVER_ENGINE_LOADING_TRANSPORT_FAILED,
        /**
         * DLOPEN FAILED in loading parser library
         */
/*29*/    SERVER_ENGINE_LOADING_PARSER_FAILED,
        /**
         * AxiscEngineException:Handler failed
         */
/*30*/    SERVER_ENGINE_HANDLER_FAILED,
        /**
         * AxiscEngineException:Web Service failed
         */
/*31*/    SERVER_ENGINE_WEBSERVICE_FAILED,
        /**
         * AxiscEngineException:Handler initialization failed
         */
/*32*/    SERVER_ENGINE_HANDLER_INIT_FAILED,
        /**
         * AxiscEngineException:Handler creation failed
         */
/*33*/    SERVER_ENGINE_HANDLER_CREATION_FAILED,
        /**
         * AxiscEngineException:Library loading failed
         */
/*34*/    SERVER_ENGINE_LIBRARY_LOADING_FAILED,
        /**
         * AxiscEngineException:Handler is not loaded
         */
/*35*/    SERVER_ENGINE_HANDLER_NOT_LOADED,
        /**
         * AxiscEngineException:Handler is being used
         */
/*36*/    SERVER_ENGINE_HANDLER_BEING_USED,
        /**
         * AxiscEngineException:Get handler failed
         */
/*37*/    SERVER_ENGINE_GET_HANDLER_FAILED,
        /**
         * AxiscEngineException:Wrong handler type
         */
/*38*/    SERVER_ENGINE_WRONG_HANDLER_TYPE,
        /**
         * AxiscConfigException:Unknown Axisc C++ Configuration Exception
         */
/*39*/    SERVER_CONFIG_EXCEPTION,
        /**
         * AxiscConfigException:Transport layer is not configured properly
         */
/*40*/    SERVER_CONFIG_TRANSPORT_CONF_FAILED,
        /**
         * AxiscConfigException:Library path is empty(Not in server.wsdd file)
         */
/*41*/    SERVER_CONFIG_LIBRARY_PATH_EMPTY,
        /**
         * AxiscWsddException:WSDD loading fail
         */
/*42*/    SERVER_WSDD_FILE_NOT_FOUND,
        /**
         * AxiscWsddException:Unknown wsdd exception
         */
/*43*/    SERVER_WSDD_EXCEPTION,
        /**
         * AxiscWsddException:No handlers configured in server.wsdd
         */
/*44*/    SERVER_WSDD_NO_HANDLERS_CONFIGURED,
        /**
         * AxiscSoapException:Unknown Soap Exception
         */
/*45*/    SERVER_SOAP_EXCEPTION,
        /**
         * 
         */
/*46*/    SERVER_TRANSPORT_EXCEPTION,
        /**
         * HTTPTransportException:Problem occurred when receiving the stream
         */
/*47*/    SERVER_TRANSPORT_RECEPTION_EXCEPTION,
        /**
         * HTTPTransportException:Problem occurred when sending the stream
         */
/*48*/    SERVER_TRANSPORT_SENDING_EXCEPTION,
        /**
         * HTTPTransportException:HTTP Error, cannot process response message
         */
/*49*/    SERVER_TRANSPORT_PROCESS_EXCEPTION,
        /**
         * HTTPTransportException:Unknow HTTP response, cannot process response message
         */
/*50*/    SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE,
        /**
         * HTTPTransportException:HTTP transport error
         */
/*51*/    SERVER_TRANSPORT_HTTP_EXCEPTION,
        /**
         * HTTPTransportException:Unexpected string received.
         * Most probably server returned an empty stream
         */
/*52*/    SERVER_TRANSPORT_UNEXPECTED_STRING,
        /**
         * HTTPTransportException:Cannot initialize a channel to the remote end
         */
/*53*/    SERVER_TRANSPORT_CHANNEL_INIT_ERROR,
        /**
         * AxiscTransportException:Sockets error Couldn't create socket
         */
/*54*/    SERVER_TRANSPORT_SOCKET_CREATE_ERROR,
        /**
         * AxiscTransportException:Cannot open a channel to the remote end, shutting down the channel
         */
/*55*/    SERVER_TRANSPORT_SOCKET_CONNECT_ERROR,
        /**
         * AxiscTransportException:Invalid socket. Socket may not be open
         */
/*56*/    SERVER_TRANSPORT_INVALID_SOCKET,
        /**
         * AxiscTransportException:Output streaming error on Channel while writing data
         */
/*57*/    SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR,
        /**
         * AxiscTransportException:Input streaming error while getting data
         */
/*58*/    SERVER_TRANSPORT_INPUT_STREAMING_ERROR,
        /**
         * AxiscTransportException:Channel error while waiting for timeout
         */
/*59*/    SERVER_TRANSPORT_TIMEOUT_EXCEPTION,
        /**
         * AxiscTransportException:Channel error connection timeout before receiving
         */
/*60*/    SERVER_TRANSPORT_TIMEOUT_EXPIRED,
        /**
         * See implementation specific error message
         */
/*61*/    SERVER_TRANSPORT_LOADING_SSLCHANNEL_FAILED,
        /**
         * DLOPEN FAILED in loading channel library
         */
/*62*/    SERVER_TRANSPORT_LOADING_CHANNEL_FAILED,
        /**
         * AxiscTransportException:Transport buffer is empty
         */
/*63*/    SERVER_TRANSPORT_BUFFER_EMPTY,
        /**
         * AxiscParseException:Buffer received from the parser is empty.  
         */
/*64*/    SERVER_PARSE_BUFFER_EMPTY,
        /**
         * AxiscParseException:XML_STATUS_ERROR thrown from parser.  
         */
/*65*/    SERVER_PARSE_PARSER_FAILED, 
        /**
         * AxiscParseException:Error when getting the byte stream from the transport.  
         */
/*66*/    SERVER_PARSE_TRANSPORT_FAILED,
        /**
         * This is a testing error
         */
/*67*/    SERVER_TEST_EXCEPTION,
        /**
         * Unknown error
         */
/*68*/    SERVER_UNKNOWN_ERROR,
        /**
         * AxiscEngineException:Engine cannot be initialized as both client and server
         */
/*69*/    SERVER_CLIENT_ENGINE_MISMATCH,

    /* AXISC C faults */
    /*Following exceptions are not releated to soap faults
     */
        /**
         * A service has thrown an exception. see detail 
         */
/*70*/    AXISC_SERVICE_THROWN_EXCEPTION,
        /**
         * 
         */
/*71*/    AXISC_UNKNOWN_ELEMENT_EXCEPTION,
        /**
         * Cannot deserialize the requested element.
         * This may indicate a fault has been received.
         */
/*72*/    AXISC_NODE_VALUE_MISMATCH_EXCEPTION,
        /**
         * 
         */
/*73*/    AXISC_READ_CONF_EXCEPTION,

    /* CONFIG faults */
    /*Following exceptions are releated to configuration faults
     */
        /**
         * AxiscConfigException:configuration defaults have already been set
         */
/*74*/    CONFIG_DEFAULTS_ALREADY_SET,
    /*
     * This FAULT_LAST is not used as a fault code, but instead is used 
     * internaly in the code. Developers should not use this as a fault 
     * code.
     */
/*75*/    FAULT_LAST 
} AXISC_AXISC_EXCEPTIONS;

/**
 *   @class AxisException
 *   @brief Base class for Axis C++ exception hierarchy.
 *
 *   This will act as the base class for Axis C++ exception hierarchy.
 *   This is class is derived from the std c++ exception class. Derived
 *   from this class are AxisConfigExceptin, AxisSoapExceptin, AxisWsddException,
 *   AxisEngineException, AxisTransportException and AxisParseException.
 *
 */


/** Destructor */
AXISC_STORAGE_CLASS_INFO
void axiscExceptionDestroy(AXISCHANDLE axisException);

/**
 *  This method is defined in std::exception. AxisException and derived
 * classes will override this to print exception messages
 *
 * @return Exception message
 */
AXISC_STORAGE_CLASS_INFO
const char * axiscExceptionWhat(AXISCHANDLE axisException);

/**
 * This can be called to get the exception code.
 *
 * @return Exception code
 */
AXISC_STORAGE_CLASS_INFO
int axiscExceptionGetExceptionCode(AXISCHANDLE axisException);

/**
 * This can be called to set the exception code
 *
 * @param exceptionCode for this exception.
 */
AXISC_STORAGE_CLASS_INFO
void axiscExceptionSetExceptionCode(AXISCHANDLE axisException, int exceptionCode);

/**
 * The method setMessage(std::string psMessage) uses to set the private data member m_sMessage
 * This method should be used to set the m_sMessage variable in derived classes.
 *
 * @param psMessage The exception message to be set.
 */
AXISC_STORAGE_CLASS_INFO
void axiscExceptionSetMessage(AXISCHANDLE axisException, const char * psMessage);

/**
 * The method will reset exception object as if no parameters
 * where passed to constructor
 */
AXISC_STORAGE_CLASS_INFO
void axiscExceptionResetException(AXISCHANDLE axisException);

#ifdef __cplusplus
 }
#endif

#endif /* AXISEXCEPTION_INCLUDED */
