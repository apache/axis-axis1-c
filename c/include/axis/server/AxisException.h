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
#include <ios>
using namespace std;


#ifdef __ENABLE_AXIS_EXCEPTION__
#define AXISC_TRY try {
#define AXISC_CATCH(X) } catch (X) { 
#define AXISC_ENDCATCH }

#define AXISC_THROW(X) throw AxisException(X)
#define THROW_AXIS_EXCEPTION() throw AxisException()
#define THROW_AXIS_EXCEPTION(X) throw AxisException(X)
#define THROW_AXIS_CONFIG_EXCEPTION() throw AxisConfigException()
#define THROW_AXIS_CONFIG_EXCEPTION(X) throw AxisConfigException(X)
#define THROW_AXIS_SOAP_EXCEPTION() throw AxisSoapException()
#define THROW_AXIS_SOAP_EXCEPTION(X) throw AxisSoapException(X)
#define THROW_AXIS_WSDD_EXCEPTION() throw AxisWsddException()
#define THROW_AXIS_WSDD_EXCEPTION(X) throw AxisWsddException(X)
#define THROW_AXIS_BAD_ALLOC() throw std::bad_alloc
#define THROW_AXIS_BAD_CAST() throw std::bad_cast
#define THROW_AXIS_BAD_TYPEID() throw std::bad_typeid
#define THROW_AXIS_BAD_EXCEPTION() throw std::bad_exception
#define THROW_AXIS_OUT_OF_RANGE(X) throw std::out_of_range
#define THROW_AXIS_INVALID_ARGUMENT(X) throw std::invalid_argument
#define THROW_AXIS_OVERFLOW_ERROR(X) throw std::overflow_error
#define THROW_AXIS_IOS_BASE_FAILURE(X) throw std::ios_base::failure


#define AXISC_THROW_SAME throw;
#else
#define AXISC_TRY 
#define AXISC_CATCH(X) 
#define AXISC_ENDCATCH
#define AXISC_THROW(X) return X
#define AXISC_THROW_SAME 
#endif

/*
 * The following enumeration is used to serve the Axis C++ codes for 
 * soap faults.
 */
enum AXISC_EXCEPTIONS 
{
    /* VersionMismatch faults */
    SF_VERSION_MISMATCH,
    
    /* MustUnderstand faults */
    SF_MUST_UNDERSTAND,

    /* Client faults */
    SF_MESSAGEINCOMPLETE,
    SF_SOAPACTIONEMPTY,
    SF_SERVICENOTFOUND,
    SF_SOAPCONTENTERROR,
    SF_NOSOAPMETHOD,
    SF_METHODNOTALLOWED,
    SF_PARATYPEMISMATCH,
    SF_CLIENTHANDLERFAILED,

    /* Server faults */
    SF_COULDNOTLOADSRV,
    SF_COULDNOTLOADHDL,
    SF_HANDLERFAILED,
    SF_WEBSERVICEFAILED,
    AXISC_TRANSPORT_CONF_ERROR,
    HANDLER_INIT_FAIL,
    HANDLER_CREATION_FAILED,
    LOADLIBRARY_FAILED,
    LIBRARY_PATH_EMPTY,
    HANDLER_NOT_LOADED,
    HANDLER_BEING_USED,
    GET_HANDLER_FAILED,
    WRONG_HANDLER_TYPE,
    NO_HANDLERS_CONFIGURED,
    AXISC_UNKNOWN_ERROR,

    /*
     * This FAULT_LAST is not used as a fault code, but instead is used 
     * internaly in the code. Developers should not use this as a fault 
     * code.
     */
    FAULT_LAST,

   /*
    * Exceptions that appear afterwords are not related to Soap faults
    */
    AXISC_SOAP_EXCEPTION,
    AXISC_WSDD_EXCEPTION,
    AXISC_CONFIG_EXCEPTION,
    AXISC_ENGINE_EXCEPTION,
    AXISC_ERROR_NONE,
    AXISC_TEST_EXCEPTION,
    AXISC_RECEPTION_ERROR,
    AXISC_SENDING_ERROR,
    AXISC_HTTP_ERROR,
    AXISC_TEST_ERROR
    
};

class AxisException :public exception
{

public:
    AxisException(int iExceptionCode);
    AxisException(exception* e);
    AxisException(exception* e, int iExceptionCode);
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

