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
using namespace std;


#ifdef __ENABLE_AXIS_EXCEPTION__
#define AXISC_TRY try {
#define AXISC_CATCH(X) } catch (X) { 
#define AXISC_ENDCATCH }
#define AXISC_THROW(X) throw AxisException(X)
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
  AxisException(int exceptionCode);
  AxisException(exception* e);
  AxisException(exception* e, int exceptionCode);
  virtual ~AxisException() throw();
  const char* what() const throw();
  const int getExceptionCode();
  string getMessage(exception* e);
  string getMessage(int e);    

  private:
    void processException(exception* e);
    void processException(exception* e, int exceptionCode);
    void processException(int e);
    string m_sMessage;
    int m_iExceptionCode;
};

#endif

