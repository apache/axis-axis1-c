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
 
#ifndef __AXISEXCEPTION_H_OF_AXIS_INCLUDED_
#define __AXISEXCEPTION_H_OF_AXIS_INCLUDED_

#include <string>
#include <exception>
#include <new>
#include <typeinfo>
#include <stdexcept>
//#include <ios>
using namespace std;


#ifdef ENABLE_AXIS_EXCEPTION
#define AXISC_TRY try {
#define AXISC_CATCH(X) } catch (X) { 
#define AXISC_ENDCATCH }

#define THROW_AXIS_EXCEPTION(X) throw AxisException(X)
#define THROW_AXIS_CONFIG_EXCEPTION(X) throw AxisConfigException(X)
#define THROW_AXIS_SOAP_EXCEPTION(X) throw AxisSoapException(X)
#define THROW_AXIS_WSDD_EXCEPTION(X) throw AxisWsddException(X)
#define THROW_AXIS_ENGINE_EXCEPTION(X) throw AxisEngineException(X)
#define THROW_AXIS_TRANSPORT_EXCEPTION(X) throw AxisTransportException(X)

#define THROW_AXIS_BAD_ALLOC() throw std::bad_alloc
#define THROW_AXIS_BAD_CAST() throw std::bad_cast
#define THROW_AXIS_BAD_TYPEID() throw std::bad_typeid
#define THROW_AXIS_BAD_EXCEPTION() throw std::bad_exception
#define THROW_AXIS_OUT_OF_RANGE(X) throw std::out_of_range
#define THROW_AXIS_INVALID_ARGUMENT(X) throw std::invalid_argument
#define THROW_AXIS_OVERFLOW_ERROR(X) throw std::overflow_error
//#define THROW_AXIS_IOS_BASE_FAILURE(X) throw std::ios_base::failure

#define AXISC_THROW_SAME throw

#else

#define AXISC_TRY 
#define AXISC_CATCH(X) 
#define AXISC_ENDCATCH

#define THROW_AXIS_EXCEPTION(X) throw AxisException(X) return X
#define THROW_AXIS_CONFIG_EXCEPTION(X) throw AxisConfigException(X) return X
#define THROW_AXIS_SOAP_EXCEPTION(X) throw AxisSoapException(X) return X
#define THROW_AXIS_WSDD_EXCEPTION(X) throw AxisWsddException(X) return X
#define THROW_AXIS_ENGINE_EXCEPTION(X) throw AxisEngineException(X) return X
#define THROW_AXIS_TRANSPORT_EXCEPTION(X) throw AxisTransportException(X) return X

#define THROW_AXIS_BAD_ALLOC()
#define THROW_AXIS_BAD_CAST()
#define THROW_AXIS_BAD_TYPEID()
#define THROW_AXIS_BAD_EXCEPTION()
#define THROW_AXIS_OUT_OF_RANGE(X)
#define THROW_AXIS_INVALID_ARGUMENT(X)
#define THROW_AXIS_OVERFLOW_ERROR(X)
#define THROW_AXIS_IOS_BASE_FAILURE(X)

#define AXISC_THROW_SAME 
#endif

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
    CLIENT_WSDD_SERVICE_NOT_FOUND,
    CLIENT_WSDD_METHOD_NOT_ALLOWED,
    CLIENT_WSDD_PARA_TYPE_MISMATCH,
    CLIENT_ENGINE_CLIENT_HANDLER_FAILED,

    /* Server faults */
    SERVER_ENGINE_EXCEPTION,
    SERVER_ENGINE_COULD_NOT_LOAD_SRV,
    SERVER_ENGINE_COULD_NOT_LOAD_HDL,
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
    SERVER_WSDD_EXCEPTION,
    SERVER_WSDD_NO_HANDLERS_CONFIGURED,
    SERVER_SOAP_EXCEPTION,
    SERVER_TRANSPORT_EXCEPTION,
    SERVER_TRANSPORT_RECEPTION_EXCEPTION,
    SERVER_TRANSPORT_SENDING_EXCEPTION,
    SERVER_TRANSPORT_PROCESS_EXCEPTION,
    SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE,
    SERVER_TRANSPORT_HTTP_EXCEPTION,
 
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

class AxisException :public exception
{

public:
    AxisException(){};
    AxisException(int iExceptionCode);
    AxisException(exception* e);
    AxisException(exception* e, int iExceptionCode);
    AxisException(char* pcMessage){m_sMessage = pcMessage;};
    virtual ~AxisException() throw();
    virtual const char* what() throw();
    virtual const int getExceptionCode();
    virtual const string getMessage(exception* e);
    virtual const string getMessage(int iExceptionCode);    

private:
    void processException(exception* e);
    void processException(exception* e, int iExceptionCode);
    void processException(int iExceptionCode);
    string m_sMessage;
    int m_iExceptionCode;
};

#endif
