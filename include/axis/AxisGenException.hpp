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
 
#ifndef __AXISGENEXCEPTION_H_OF_AXIS_INCLUDED_
#define __AXISGENEXCEPTION_H_OF_AXIS_INCLUDED_

#include <string>
#include <exception>
#include <axis/server/AxisException.h>

AXIS_CPP_NAMESPACE_START

using namespace std;

class STORAGE_CLASS_INFO AxisGenException :public AxisException
{

public:
    AxisGenException();

    /** This can be used to throw an exception with the exception code
      * which is defined in the AxisException.h file, under AXISC_EXCEPTIONS
      * type. Axis C++ exception model heavily use this.
      *
      * @param Exception code which is defined in the AxisException.h file,
      * under AXISC_EXCEPTIONS type.
      *
      * @example throw AxisGenException(AXISC_NODE_VALUE_MISMATCH_EXCEPTION);
      */
    AxisGenException(const int iExceptionCode);
    /** This can be used to throw an exception with exception code which is
      * is defined in the AxisException.h file, under AXISC_EXCEPTIONS type.
      * An additional description of the exception could be appended.
      *
      * @param Exception code which is defined in the AxisException.h file,
      *  under AXISC_EXCEPTIONS type.
      * @param A char pointer that will point to an exception message.
      *
      * @example throw AxisGenException(AXISC_NODE_VALUE_MISMATCH_EXCEPTION,
            "Some additional exception info");
      */

    AxisGenException(const int iExceptionCode, char* pcMessage);

    /** This can be used to throw an exception with another exception as a
      * parameter. One situation in which this can be used is when we catch
      * a standard exception like std::bad_alloc
      *
      * @param An exception class derived from std::exception
      *
      * @example throw AxisGenException(std::bad_alloc);
      */
    AxisGenException(const exception* e);

    /** This accept two parameters, both an exception code an exception object
      * derived from std::exception
      *
      * @param An exception class derived from std::exception
      * @param An exception code
      */
    AxisGenException(const exception* e, const int iExceptionCode);

    /** This accept an exception message
      *
      * @param An exception message
      */
    AxisGenException(const char* pcMessage);
    virtual ~AxisGenException() throw();
    const char* what() throw();
    const int getExceptionCode();

private:
    const string getMessage(const exception* e);
    const string getMessage(const int iExceptionCode);
    void processException(const exception* e);
    void processException(const exception* e, const int iExceptionCode);
    void processException (const exception* e, char* pcMessage);
    void processException(const int iExceptionCode);
    void processException(const int iExceptionCode, char* pcMessage); 
    string m_sMessage;
    int m_iExceptionCode;
};

AXIS_CPP_NAMESPACE_END

#endif

