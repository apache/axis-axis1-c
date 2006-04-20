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
class STORAGE_CLASS_INFO AxisException :public exception
{
public:
    /** No parameter constructor*/
    AxisException():m_iExceptionCode(0), m_sMessage(NULL){};

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
    AxisException(const int iExceptionCode, const char* pcMessage = NULL):m_iExceptionCode(iExceptionCode), m_sMessage(NULL)
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
    AxisException(const AxisException& e):m_iExceptionCode(e.m_iExceptionCode), m_sMessage(NULL)
    {
        setMessage(e.m_sMessage);
    };
    
    /** Destructor */
    virtual ~AxisException() throw()
    {
        if (m_sMessage)
            delete [] m_sMessage;
    };

    /**
     *  This method is defined in std::exception. AxisException and derived
     * classes will override this to print exception messages
     * 
     * @return Exception message
     */
    virtual const char* what() const throw() { return m_sMessage; };

    /**
     * This can be called to get the exception code.
     *
     * @return Exception code
     */
    virtual const int getExceptionCode() const { return m_iExceptionCode; }

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
    void setMessage(const char* psMessage)
    {
        if (m_sMessage)
        {
            delete [] m_sMessage;
            m_sMessage = NULL;
        }

        if (psMessage)
        {
            m_sMessage = new char[strlen(psMessage) + 1];
            strcpy(m_sMessage,psMessage);
        }        
    }
    
    /** 
     * The method will set exception data from another exception
     * 
     * @param e Exception from which data is to be set.
     */
    void setExceptionFromException(const AxisException& e)
    {
        m_iExceptionCode = e.m_iExceptionCode;
        setMessage(e.m_sMessage);
    }

    /**
      * The method will reset exception object as if no parameters
      * where passed to constructor
      */
    void resetException()
    {
        m_iExceptionCode = 0;
        setMessage((const char *)NULL);
    }

protected:
    /**
      * This data member is common to all the inherited classes of this base class.
      * The integer variable m_iExceptionCode stores the Exception code
      */
    int m_iExceptionCode;

    /**
      * This data member is common to all the inherited classes of this base class.
      * The char* variable m_sMessage is used to store the Exception message
      * Whenever you want to set this variable use method setMessage(std::string psMessage)
      */
    char* m_sMessage;
};

AXIS_CPP_NAMESPACE_END

#endif

