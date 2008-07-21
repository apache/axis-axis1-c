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
 * @file UnknownElementException.hpp
 *
 *
 */
 
#ifndef __UNKNOWNELEMENTEXCEPTION_H_OF_AXIS_INCLUDED_
#define __UNKNOWNELEMENTEXCEPTION_H_OF_AXIS_INCLUDED_

#include <axis/AxisException.hpp>

AXIS_CPP_NAMESPACE_START
using namespace std;


/**
 *   @class UnknownElementException
 *   @brief Exception class for unknown elements.
 *
 *   This exception class is thrown when an unknown or unexpected element is 
 *   encountered. 
 */
class STORAGE_CLASS_INFO UnknownElementException : public AxisException
{
public:
    /** 
     * Constructor.
     * 
     * @param elem The name of the unexpected element.
     */
    UnknownElementException(const char *elem): AxisException()
    {
        if (!elem) elem = (const char *)"";
        std::string msg = "Unexpected or extraneous element (" + std::string(elem) + std::string(") encountered.");
        setMessage(CLIENT_SOAP_SOAP_CONTENT_ERROR, "", msg.c_str());
    }
};


AXIS_CPP_NAMESPACE_END

#endif



