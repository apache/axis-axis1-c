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
 *
 */

/**
 * @file AxisException.h
 *
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */
 
#ifndef __AXISEXCEPTION_H_OF_AXIS_INCLUDED_
#define __AXISEXCEPTION_H_OF_AXIS_INCLUDED_

#include <axis/server/GDefine.h>

#include <string>
#include <exception>
#include <new>
#include <typeinfo>
#include <stdexcept>
using namespace std;

/*
 * The following enumeration is used to serve the Axis C++ codes for 
 * faults.
 */
enum AXISC_EXCEPTIONS 
{
    /* VersionMismatch faults */
    SOAP_VERSION_MISMATCH,
    
    /* MustUnderstand faults */
    SOAP_MUST_UNDERSTAND,

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
     */
     
    /* Client faults */
    CLIENT_SOAP_MESSAGE_INCOMPLETE,
    CLIENT_SOAP_SOAP_ACTION_EMTPY,
    CLIENT_SOAP_SOAP_CONTENT_ERROR,
    CLIENT_SOAP_NO_SOAP_METHOD,
    CLIENT_SOAP_CONTENT_NOT_SOAP,
    CLIENT_WSDD_SERVICE_NOT_FOUND,
    CLIENT_WSDD_METHOD_NOT_ALLOWED,
    CLIENT_WSDD_PARA_TYPE_MISMATCH,
    CLIENT_ENGINE_CLIENT_HANDLER_FAILED,

    /* Server faults */
    SERVER_ENGINE_EXCEPTION,
    SERVER_ENGINE_COULD_NOT_LOAD_SRV,
    SERVER_ENGINE_COULD_NOT_LOAD_HDL,
    SERVER_ENGINE_LOADING_TRANSPORT_FAILED,
    SERVER_ENGINE_LOADING_PARSER_FAILED,
    SERVER_ENGINE_HANDLER_FAILED,
    SERVER_ENGINE_WEBSERVICE_FAILED,
    SERVER_ENGINE_HANDLER_INIT_FAILED,
    SERVER_ENGINE_HANDLER_CREATION_FAILED,
    SERVER_ENGINE_LIBRARY_LOADING_FAILED,
    SERVER_ENGINE_HANDLER_NOT_LOADED,
    SERVER_ENGINE_HANDLER_BEING_USED,
    SERVER_ENGINE_GET_HANDLER_FAILED,
    SERVER_ENGINE_WRONG_HANDLER_TYPE,
    SERVER_CONFIG_EXCEPTION,
    SERVER_CONFIG_TRANSPORT_CONF_FAILED,
    SERVER_CONFIG_LIBRARY_PATH_EMPTY,
	SERVER_WSDD_FILE_NOT_FOUND,
    SERVER_WSDD_EXCEPTION,
    SERVER_WSDD_NO_HANDLERS_CONFIGURED,
    SERVER_SOAP_EXCEPTION,
    SERVER_TRANSPORT_EXCEPTION,
    SERVER_TRANSPORT_RECEPTION_EXCEPTION,
    SERVER_TRANSPORT_SENDING_EXCEPTION,
    SERVER_TRANSPORT_PROCESS_EXCEPTION,
    SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE,
    SERVER_TRANSPORT_HTTP_EXCEPTION,
    SERVER_TRANSPORT_UNEXPECTED_STRING,
    SERVER_TRANSPORT_CHANNEL_INIT_ERROR,
    SERVER_TRANSPORT_SOCKET_CREATE_ERROR,
    SERVER_TRANSPORT_SOCKET_CONNECT_ERROR,
    SERVER_TRANSPORT_INVALID_SOCKET,
    SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR,
    SERVER_TRANSPORT_INPUT_STREAMING_ERROR,
    SERVER_TRANSPORT_TIMEOUT_EXCEPTION,
    SERVER_TRANSPORT_TIMEOUT_EXPIRED,
    SERVER_TRANSPORT_BUFFER_EMPTY,
    SERVER_PARSE_BUFFER_EMPTY,
    SERVER_PARSE_PARSER_FAILED, 
    SERVER_PARSE_TRANSPORT_FAILED,
 
    SERVER_TEST_EXCEPTION,
    SERVER_UNKNOWN_ERROR,
    /*Following exceptions are not releated to soap faults
     */
    AXISC_SERVICE_THROWN_EXCEPTION,
    AXISC_UNKNOWN_ELEMENT_EXCEPTION,
    AXISC_NODE_VALUE_MISMATCH_EXCEPTION,
    AXISC_READ_CONF_EXCEPTION,

    /*
     * This FAULT_LAST is not used as a fault code, but instead is used 
     * internaly in the code. Developers should not use this as a fault 
     * code.
     */
    FAULT_LAST 
};

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
    //AxisException(){};

    /** This can be used to throw an exception with the exception code
      * which is defined in the AxisException.h file, under AXISC_EXCEPTIONS
      * type. Axis C++ exception model heavily use this.
      *
      * @param Exception code which is defined in the AxisException.h file, 
      * under AXISC_EXCEPTIONS type.
      * 
      * @example throw AxisException(AXISC_NODE_VALUE_MISMATCH_EXCEPTION);
      */
    //AxisException(const int iExceptionCode);

    /** This can be used to throw an exception with exception code which is
      * is defined in the AxisException.h file, under AXISC_EXCEPTIONS type.
      * An additional description of the exception could be appended.
      *
      * @param Exception code which is defined in the AxisException.h file,
      *  under AXISC_EXCEPTIONS type.
      * @param A char pointer that will point to an exception message.
      *
      * @example throw AxisException(AXISC_NODE_VALUE_MISMATCH_EXCEPTION, 
            "Some additional exception info");
      */
    //AxisException(const int iExceptionCode, char* pcMessage);

    /** This can be used to throw an exception with another exception as a
      * parameter. One situation in which this can be used is when we catch
      * a standard exception like std::bad_alloc
      *
      * @param An exception class derived from std::exception
      *
      * @example throw AxisException(std::bad_alloc);
      */
    //AxisException(const exception* e);

    /** This accept two parameters, both an exception code an exception object
      * derived from std::exception
      *
      * @param An exception class derived from std::exception
      * @param An exception code
      */
    //AxisException(const exception* e, const int iExceptionCode);
    
    /** This accept an exception message
      *
      * @param An exception message
      */
    //AxisException(const char* pcMessage){m_sMessage = pcMessage;};
    
    /** Destructor */
    virtual ~AxisException() throw(){};

    /** This method is defined in std::exception. AxisException and derived
      * classes will override this to print exception messages
      */
    virtual const char* what() throw() = 0;

    /** This can be called to get the exception code which is passed
      * in the constructor. This returns -1 value when the 
      * constructor does not have a exception code parameter
      * 
      * @return the exception code if the construct have a exception code
      * int parameter. Else return -1.
      *
      * @return exception message
      */
    virtual const int getExceptionCode() = 0;
};

#endif

