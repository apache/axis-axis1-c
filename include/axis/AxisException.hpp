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
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */
 
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED TO THE        */
/* C-EQUIVALENT HEADER FILE IN SUPPORT OF THE C-BINDING INTERFACES.   */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifndef __AXISEXCEPTION_H_OF_AXIS_INCLUDED_
#define __AXISEXCEPTION_H_OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <string>
#include <exception>
#include <new>
#include <typeinfo>
#include <stdexcept>

AXIS_CPP_NAMESPACE_START
using namespace std;

/*
 * The following enumeration is used to serve the Axis C++ codes for 
 * faults.
 */
#define CLIENT_FAULT_OFFSET      0x0
#define SERVER_FAULT_OFFSET      0x1000
#define SOAP_FAULT_OFFSET        0x2000
#define ENGINE_FAULT_OFFSET      0x3000
#define WSDD_FAULT_OFFSET        0x4000
#define TRANSPORT_FAULT_OFFSET   0x5000
#define CONFIG_FAULT_OFFSET      0x6000
#define AXISC_FAULT_OFFSET       0x7000

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
     *ENGINE that comes next to CLIENT/SERVER means this is a axisc++ engine
     *    related exception
     *WSDD that comes next to CLIENT/SERVER means this is a wsdd releated
     *    exception
     *TRANSPORT that comes next to CLIENT/SERVER means this is a transport releated
     *    exception
     *CONFIG that comes next to CLIENT/SERVER means this is a axisc++ configuration
     *    related exception
     *AXISC ?
     */
    /* SOAP faults */
        /** AxisSoapException:Soap Version mismatch fault occurred */
/*0*/    SOAP_VERSION_MISMATCH, 
        /** AxisSoapException:Soap Must understand fault occurred */
/*1*/    SOAP_MUST_UNDERSTAND,    

    /* Client faults */
        /**
         * AxisSoapException:Received message is incomplete
         */
/*2*/    CLIENT_SOAP_MESSAGE_INCOMPLETE,
        /**
         * AxisSoapException:Soap action is empty
         */
/*3*/    CLIENT_SOAP_SOAP_ACTION_EMTPY,
        /**
         * AxisSoapException:Received content is faulty
         */
/*4*/    CLIENT_SOAP_SOAP_CONTENT_ERROR,
        /**
         * AxisSoapException:Request method is not a soap method
         */
/*5*/    CLIENT_SOAP_NO_SOAP_METHOD,
        /**
         * AxisSoapException:Content is not a valid soap message
         */
/*6*/    CLIENT_SOAP_CONTENT_NOT_SOAP,
        /**
         * AxisWsddException:Requested service not found
         */
/*7*/    CLIENT_WSDD_SERVICE_NOT_FOUND,
        /**
         * AxisWsddException:Requested method is not allowed
         */
/*8*/    CLIENT_WSDD_METHOD_NOT_ALLOWED,
        /**
         * AxisWsddException: Parameter type mismatch
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
         * AxisSoapException:Content is not unique within the MIME message
         */
/*24*/   CLIENT_MIME_CONTENT_ID_NOT_UNIQUE,

    /* Server faults */
        /**
         * SERVER_ENGINE_EXCEPTION
         */
/*25*/    SERVER_ENGINE_EXCEPTION,
        /**
         * AxisEngineException:Could not load service
         */
/*26*/    SERVER_ENGINE_COULD_NOT_LOAD_SRV,
        /**
         * AxisEngineException:Could not load handler
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
         * AxisEngineException:Handler failed
         */
/*30*/    SERVER_ENGINE_HANDLER_FAILED,
        /**
         * AxisEngineException:Web Service failed
         */
/*31*/    SERVER_ENGINE_WEBSERVICE_FAILED,
        /**
         * AxisEngineException:Handler initialization failed
         */
/*32*/    SERVER_ENGINE_HANDLER_INIT_FAILED,
        /**
         * AxisEngineException:Handler creation failed
         */
/*33*/    SERVER_ENGINE_HANDLER_CREATION_FAILED,
        /**
         * AxisEngineException:Library loading failed
         */
/*34*/    SERVER_ENGINE_LIBRARY_LOADING_FAILED,
        /**
         * AxisEngineException:Handler is not loaded
         */
/*35*/    SERVER_ENGINE_HANDLER_NOT_LOADED,
        /**
         * AxisEngineException:Handler is being used
         */
/*36*/    SERVER_ENGINE_HANDLER_BEING_USED,
        /**
         * AxisEngineException:Get handler failed
         */
/*37*/    SERVER_ENGINE_GET_HANDLER_FAILED,
        /**
         * AxisEngineException:Wrong handler type
         */
/*38*/    SERVER_ENGINE_WRONG_HANDLER_TYPE,
        /**
         * AxisConfigException:Unknown Axis C++ Configuration Exception
         */
/*39*/    SERVER_CONFIG_EXCEPTION,
        /**
         * AxisConfigException:Transport layer is not configured properly
         */
/*40*/    SERVER_CONFIG_TRANSPORT_CONF_FAILED,
        /**
         * AxisConfigException:Library path is empty(Not in server.wsdd file)
         */
/*41*/    SERVER_CONFIG_LIBRARY_PATH_EMPTY,
        /**
         * AxisWsddException:WSDD loading fail
         */
/*42*/    SERVER_WSDD_FILE_NOT_FOUND,
        /**
         * AxisWsddException:Unknown wsdd exception
         */
/*43*/    SERVER_WSDD_EXCEPTION,
        /**
         * AxisWsddException:No handlers configured in server.wsdd
         */
/*44*/    SERVER_WSDD_NO_HANDLERS_CONFIGURED,
        /**
         * AxisSoapException:Unknown Soap Exception
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
         * AxisTransportException:Sockets error Couldn't create socket
         */
/*54*/    SERVER_TRANSPORT_SOCKET_CREATE_ERROR,
        /**
         * AxisTransportException:Cannot open a channel to the remote end, shutting down the channel
         */
/*55*/    SERVER_TRANSPORT_SOCKET_CONNECT_ERROR,
        /**
         * AxisTransportException:Invalid socket. Socket may not be open
         */
/*56*/    SERVER_TRANSPORT_INVALID_SOCKET,
        /**
         * AxisTransportException:Output streaming error on Channel while writing data
         */
/*57*/    SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR,
        /**
         * AxisTransportException:Input streaming error while getting data
         */
/*58*/    SERVER_TRANSPORT_INPUT_STREAMING_ERROR,
        /**
         * AxisTransportException:Channel error while waiting for timeout
         */
/*59*/    SERVER_TRANSPORT_TIMEOUT_EXCEPTION,
        /**
         * AxisTransportException:Channel error connection timeout before receiving
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
         * AxisTransportException:Transport buffer is empty
         */
/*63*/    SERVER_TRANSPORT_BUFFER_EMPTY,
        /**
         * AxisParseException:Buffer received from the parser is empty.  
         */
/*64*/    SERVER_PARSE_BUFFER_EMPTY,
        /**
         * AxisParseException:XML_STATUS_ERROR thrown from parser.  
         */
/*65*/    SERVER_PARSE_PARSER_FAILED, 
        /**
         * AxisParseException:Error when getting the byte stream from the transport.  
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
         * AxisEngineException:Engine cannot be initialized as both client and server
         */
/*69*/    SERVER_CLIENT_ENGINE_MISMATCH,

    /* AXIS C faults */
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
         * AxisConfigException:configuration defaults have already been set
         */
/*74*/    CONFIG_DEFAULTS_ALREADY_SET,
    /*
     * This FAULT_LAST is not used as a fault code, but instead is used 
     * internaly in the code. Developers should not use this as a fault 
     * code.
     */
/*75*/    FAULT_LAST 
} AXISC_EXCEPTIONS;

/**
 *   @class AxisException
 *   @brief Base class for Axis C++ exception hierarchy.
 *
 *   This will act as the base class for Axis C++ exception hierarchy. 
 *   This is class is derived from the std c++ exception class. Derived
 *   from this class are AxisConfigExceptin, AxisSoapExceptin, AxisWsddException,
 *   AxisEngineException, AxisTransportException and AxisParseException.
 *
 *   @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 */
class STORAGE_CLASS_INFO AxisException : public exception
{
public:
    /** No parameter constructor*/
    AxisException():m_iExceptionCode(0), m_sMessage("") { }

    /** This can be used to throw an exception with exception code which is
      * is defined in the AxisException.h file, under AXISC_EXCEPTIONS type.
      * An additional description of the exception could be appended.
      *
      * @param iExceptionCode Exception code which is defined in the AxisException.h file,
      *  under AXISC_EXCEPTIONS type.
      * @param pcMessage A char pointer that will point to an exception message.
      * 
      * Example usage:
      * <pre>
      * throw AxisException(AXISC_NODE_VALUE_MISMATCH_EXCEPTION, 
      *                     "Some additional exception info");
        </pre>
      */
    AxisException(int iExceptionCode, const char* pcMessage = NULL):m_iExceptionCode(iExceptionCode)
    {
        setMessage(pcMessage);    
    }

    /** This can be used to throw an exception with another exception as a
      * parameter. One situation in which this can be used is when we catch
      * a standard exception like std::bad_alloc
      *
      * @param e An exception class derived from std::exception
      *
      * Example usage:
      * <pre>
      * throw AxisException(std::bad_alloc);
      * </pre>
      */
    AxisException(const AxisException& e):m_iExceptionCode(e.m_iExceptionCode)
    {
        setMessage(e.m_sMessage.c_str());
    }
    
    /** Destructor */
    virtual ~AxisException() throw() { }

    /**
     *  This method is defined in std::exception. AxisException and derived
     * classes will override this to print exception messages
     * 
     * @return Exception message
     */
    virtual const char* what() const throw() { return m_sMessage.c_str(); }

    /**
     * This can be called to get the exception code.
     *
     * @return Exception code
     */
    virtual int getExceptionCode() const { return m_iExceptionCode; }

    /**
     * This can be called to set the exception code
     * 
     * @param exceptionCode for this exception.
     */
    void setExceptionCode(int exceptionCode) { m_iExceptionCode = exceptionCode;}

    /**
     * 
     * Get error message text
     * @deprecated This method has now been deprecated, use AxisException::what()
     * 
     * @return Exception message
     */
    const char* getMessage() const { return what(); }
    
    /**
      * The method setMessage(std::string psMessage) uses to set the private data member m_sMessage
      * This method should be used to set the m_sMessage variable in derived classes.
      * 
      * @param psMessage The exception message to be set.
      */
    void setMessage(const char* psMessage) { m_sMessage = psMessage ? psMessage : "";  }
     
    /**
      * The method setMessage(std::string psMessage) uses to set the code and message.
      * This method will retrieve the corresponding message for the exceptionCode and then append 
      * the detailMessage if set.
      * 
      * @param exceptionCode The exception code for which message is to be retrieved.
      * @param defaultMsg    If exception code cannot be mapped to message, this will be used.
      * @param detailMessage Additional message information that will be appended to the exception message.
      */
    void setMessage(int exceptionCode, const char *defaultMsg, const char* detailMessage=NULL)
    {
        m_iExceptionCode = exceptionCode;
        std::string sMessage = detailMessage ? detailMessage : "";
        m_sMessage = getMessageForExceptionCode(exceptionCode, defaultMsg) + " " + sMessage;
    }
    
    /** 
     * The method will set exception data from another exception
     * 
     * @param e Exception from which data is to be set.
     */
    void setExceptionFromException(const AxisException& e)
    {
        m_iExceptionCode = e.m_iExceptionCode;
        m_sMessage       = e.m_sMessage;
    }

    /**
      * The method will reset exception object as if no parameters
      * where passed to constructor
      */
    void resetException()
    {
        m_iExceptionCode = 0;
        m_sMessage       = "";
    }
    
    /**
     * This method is used to map AXIS exception code to a text message. Primarily used
     * by classes that inherit from AxisException. 
     * 
     * @param exceptionCode The exception code for which message is to be retrieved.
     * @param defaultMsg    If exception code cannot be mapped to message, this will be returned.
     */
     static std::string getMessageForExceptionCode(int exceptionCode, const char *defaultMsg=NULL)
     {
        std::string sMsg;
        
        switch (exceptionCode)
        {
            case SOAP_VERSION_MISMATCH:
                sMsg = "AxisSoapException: Soap VersionMismatch fault occurred.";
                break;
            case SOAP_MUST_UNDERSTAND:    
                sMsg = "AxisSoapException: Soap MustUnderstand fault occurred.";
                break;
            case CLIENT_SOAP_MESSAGE_INCOMPLETE:
                sMsg = "AxisSoapException: Received message is incomplete.";
                break;
            case CLIENT_SOAP_SOAP_ACTION_EMTPY:
                sMsg = "AxisSoapException: SOAPAction HTTP header is empty.";
                break;
            case CLIENT_SOAP_SOAP_CONTENT_ERROR:
                sMsg = "AxisSoapException: Received content is faulty.";
                break;
            case CLIENT_SOAP_NO_SOAP_METHOD:
                sMsg = "AxisSoapException: Request method is not a soap method.";
                break;
            case CLIENT_SOAP_CONTENT_NOT_SOAP:
                sMsg = "AxisSoapException: Content is not a valid soap message.";
                break;
            case CLIENT_WSDD_SERVICE_NOT_FOUND:
                sMsg = "AxisWsddException: Requested service not found.";
                break;
            case CLIENT_WSDD_METHOD_NOT_ALLOWED:
                sMsg = "AxisWsddException: Requested method is not allowed.";
                break;
            case CLIENT_WSDD_PARA_TYPE_MISMATCH:
                sMsg = "AxisWsddException: Parameter type mismatch.";
                break;
            case CLIENT_ENGINE_CLIENT_HANDLER_FAILED:
                sMsg = "AxisEngineException: Client handler failed.";
                break;
            case CLIENT_TRANSPORT_EXCEPTION:
                sMsg = "HTTPTransportException: Client transport exception.";
                break;
            case CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED:
                sMsg = "HTTPTransportException: Client failed to open.";
                break;
            case CLIENT_TRANSPORT_TYPE_MISMATCH:
                sMsg = "HTTPTransportException: Client attempted to use SSL functions without the proper prerequisites.";
                break;
            case CLIENT_TRANSPORT_HAS_NO_UNSECURE_TRANSPORT_LAYER:
                sMsg = "HTTPTransportException: Client attempted to use non-existant unsecure transport (http).";
                break;
            case CLIENT_TRANSPORT_HAS_NO_SECURE_TRANSPORT_LAYER:
                sMsg = "HTTPTransportException: Client attempted to use non-existant secure transport (https).";
                break;
            case CLIENT_MIME_CONTENT_ID_NOT_UNIQUE:
                sMsg = "AxisSoapException: Content is not unique within the MIME message.";
                break;
            case SERVER_ENGINE_EXCEPTION:
                sMsg = "AxisEngineException: Exception occurred.";
                break;
            case SERVER_ENGINE_COULD_NOT_LOAD_SRV:
                sMsg = "AxisEngineException: Could not load service.";
                break;
            case SERVER_ENGINE_COULD_NOT_LOAD_HDL:
                sMsg = "AxisEngineException: Could not load handler.";
                break;
            case SERVER_ENGINE_LOADING_TRANSPORT_FAILED:
                sMsg = "AxisEngineException: Failed to load transport library.";
                break;
            case SERVER_ENGINE_LOADING_PARSER_FAILED:
                sMsg = "AxisEngineException: Failed to load parser library.";
                break;
            case SERVER_ENGINE_HANDLER_FAILED:
                sMsg = "AxisEngineException: Handler failed.";
                break;
            case SERVER_ENGINE_WEBSERVICE_FAILED:
                sMsg = "AxisEngineException: Web service failed.";
                break;
            case SERVER_ENGINE_HANDLER_INIT_FAILED:
                sMsg = "AxisEngineException: Handler initialization failed.";
                break;
            case SERVER_ENGINE_HANDLER_CREATION_FAILED:
                sMsg = "AxisEngineException: Handler creation failed.";
                break;
            case SERVER_ENGINE_LIBRARY_LOADING_FAILED:
                sMsg = "AxisEngineException: Library loading failed.";
                break;
            case SERVER_ENGINE_HANDLER_NOT_LOADED:
                sMsg = "AxisEngineException: Handler is not loaded.";
                break;
            case SERVER_ENGINE_HANDLER_BEING_USED:
                sMsg = "AxisEngineException: Handler is being used.";
                break;
            case SERVER_ENGINE_GET_HANDLER_FAILED:
                sMsg = "AxisEngineException: Failed to get handler.";
                break;
            case SERVER_ENGINE_WRONG_HANDLER_TYPE:
                sMsg = "AxisEngineException: Wrong handler type.";
                break;
            case SERVER_CONFIG_EXCEPTION:
                sMsg = "AxisConfigException: Exception occurred.";
                break;
            case SERVER_CONFIG_TRANSPORT_CONF_FAILED:
                sMsg = "AxisConfigException: Transport layer is not configured properly.";
                break;
            case SERVER_CONFIG_LIBRARY_PATH_EMPTY:
                sMsg = "AxisConfigException: Library path is empty (not in server.wsdd file).";
                break;
            case SERVER_WSDD_FILE_NOT_FOUND:
                sMsg = "AxisWsddException: Unable to load file.";
                break;
            case SERVER_WSDD_EXCEPTION:
                sMsg = "AxisWsddException: Exception occurred.";
                break;
            case SERVER_WSDD_NO_HANDLERS_CONFIGURED:
                sMsg = "AxisWsddException: No handlers configured in server.wsdd file.";
                break;
            case SERVER_SOAP_EXCEPTION:
                sMsg = "AxisSoapException: Exception occurred.";
                break;
            case SERVER_TRANSPORT_EXCEPTION:
                sMsg = "HTTPTransportException: Exception occurred.";
                break;
            case CLIENT_SSLCHANNEL_RECEPTION_EXCEPTION:
            case SERVER_TRANSPORT_RECEPTION_EXCEPTION:
                sMsg = "HTTPTransportException: Problem occurred when receiving the stream.";
                break;
            case CLIENT_SSLCHANNEL_SENDING_EXCEPTION:
            case SERVER_TRANSPORT_SENDING_EXCEPTION:
                sMsg = "HTTPTransportException: Problem occurred when sending the stream.";
                break;
            case SERVER_TRANSPORT_PROCESS_EXCEPTION:
                sMsg = "HTTPTransportException: Cannot process response message.";
                break;
            case SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE:
                sMsg = "HTTPTransportException: Unknown HTTP response, cannot process response message.";
                break;
            case CLIENT_SSLCHANNEL_CONTEXT_CREATE_ERROR:
                sMsg = "HTTPTransportException: Context creation error.";
                break;
            case CLIENT_SSLCHANNEL_ERROR:
                sMsg = "HTTPTransportException: HTTPS transport error.";
                break;
            case SERVER_TRANSPORT_HTTP_EXCEPTION:
                sMsg = "HTTPTransportException: HTTP transport error.";
                break;
            case SERVER_TRANSPORT_UNEXPECTED_STRING:
                sMsg = "HTTPTransportException: Unexpected string received.";
                break;
            case CLIENT_SSLCHANNEL_CHANNEL_INIT_ERROR:    
            case SERVER_TRANSPORT_CHANNEL_INIT_ERROR:
                sMsg = "HTTPTransportException: Cannot initialize a channel to the remote end.";
                break;
            case CLIENT_SSLCHANNEL_SOCKET_CREATE_ERROR:                
            case SERVER_TRANSPORT_SOCKET_CREATE_ERROR:
                sMsg = "AxisTransportException: Unable to create a socket.";
                break;
            case CLIENT_SSLCHANNEL_SOCKET_CONNECT_ERROR:                
            case SERVER_TRANSPORT_SOCKET_CONNECT_ERROR:
                sMsg = "AxisTransportException: Cannot open a channel to the remote end.";
                break;
            case CLIENT_SSLCHANNEL_INVALID_SOCKET_ERROR:                
            case SERVER_TRANSPORT_INVALID_SOCKET:
                sMsg = "AxisTransportException: Socket not valid.";
                break;
            case SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR:
                sMsg = "HTTPTransportException: Output streaming error while writing to channel.";
                break;
            case SERVER_TRANSPORT_INPUT_STREAMING_ERROR:
                sMsg = "HTTPTransportException: Input streaming error while reading from channel.";
                break;
            case SERVER_TRANSPORT_TIMEOUT_EXCEPTION:
                sMsg = "HTTPTransportException: Channel error while doing a timed wait.";
                break;
            case SERVER_TRANSPORT_TIMEOUT_EXPIRED:
                sMsg = "HTTPTransportException: Channel I/O operation timed out.";
                break;
            case SERVER_TRANSPORT_LOADING_SSLCHANNEL_FAILED:
            case SERVER_TRANSPORT_LOADING_CHANNEL_FAILED:
                sMsg = "HTTPTransportException: Unable to load channel library.";
                break;
            case SERVER_TRANSPORT_BUFFER_EMPTY:
                sMsg = "HTTPTransportException: Transport buffer is empty.";
                break;
            case SERVER_PARSE_BUFFER_EMPTY:
                sMsg = "AxisParseException: Buffer received from the parser is empty.";
                break;
            case SERVER_PARSE_PARSER_FAILED: 
                sMsg = "AxisParseException: XML_STATUS_ERROR thrown from parser.";
                break;
            case SERVER_PARSE_TRANSPORT_FAILED:
                sMsg = "AxisParseException: Error when getting the byte stream from the transport.";
                break;
            case SERVER_TEST_EXCEPTION:
                sMsg = "This is a testing error.";
                break;
            case SERVER_CLIENT_ENGINE_MISMATCH:
                sMsg = "AxisEngineException: Engine cannot be initialized as both client and server.";
                break;
            case AXISC_SERVICE_THROWN_EXCEPTION:
                sMsg = "A service has thrown an exception.";
                break;
            case AXISC_UNKNOWN_ELEMENT_EXCEPTION:
                sMsg = "AxisParseException: Unknown element encountered.";
                break;
            case AXISC_NODE_VALUE_MISMATCH_EXCEPTION:
                sMsg = "Cannot deserialize the requested element.";
                break;
            case AXISC_READ_CONF_EXCEPTION:
                sMsg = "AxisConfigException: Unable to read configuration file.";
                break;
            case CONFIG_DEFAULTS_ALREADY_SET:  
                sMsg = "AxisConfigException: Configuration defaults have already been set.";
                break;
            case SERVER_UNKNOWN_ERROR:
            default:    
                sMsg= defaultMsg ? defaultMsg : "AxisException:";      
                break;
        }
        
        return sMsg;
     }

protected:
    /**
      * This data member is common to all the inherited classes of this base class.
      * The integer variable m_iExceptionCode stores the Exception code
      */
    int m_iExceptionCode;

    /**
      * This data member is common to all the inherited classes of this base class.
      * The variable m_sMessage is used to store the Exception message
      */
    std::string m_sMessage;
};

AXIS_CPP_NAMESPACE_END

#endif

