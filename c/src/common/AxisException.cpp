/* -*- C++ -*- */
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
 * @author  Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

#include <axis/server/AxisException.h>
#include <exception>
using namespace std;

AxisException::AxisException (int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisException::AxisException (exception* e)
{
    processException (e);
}

AxisException::AxisException (exception* e, int iExceptionCode)
{
    processException (e, iExceptionCode);
}

void AxisException::processException (exception* e, int iExceptionCode)
{
    m_sMessage = getMessage (e) + getMessage (iExceptionCode);
}

void AxisException::processException (exception* e)
{
    m_sMessage = getMessage (e);
}

void AxisException::processException(int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

const string AxisException::getMessage (exception* objException)
{
    string sMessage = objException->what();
    /* to do */
/*  exception *objType = static_cast<std::bad_alloc*> (e);
  if(objType != NULL)
  {
    sMessage = "thrown by new";
  }

  objType = static_cast<std::bad_cast*> (e);
  if(objType != NULL)
  {
    sMessage = "thrown by dynamic_cast when fails with a referenced type";
  }

  objType = static_cast<bad_exception*> (e);
  if(objType != NULL)
  {
    sMessage = "thrown when an exception doesn't match any catch";
  }

  objType = static_cast<bad_typeid*> (e);
  if(objType != NULL)
  {
    sMessage = "thrown by typeid";
  }
*/

    return sMessage;
}

const string AxisException::getMessage (int iExceptionCode)
{
    string sMessage;
    switch(iExceptionCode)
    {
        case SF_VERSION_MISMATCH:
            sMessage = "Soap Version mismatch fault occured";
            break;
        case SF_MUST_UNDERSTAND:
            sMessage = "Soap Must understand fault occured";
            break;
        case SF_MESSAGEINCOMPLETE:
            sMessage = "Received message is incomplete";
            break;
        case SF_SOAPACTIONEMPTY:
            sMessage = "Soap action is empty";
            break;
        case SF_SERVICENOTFOUND:
            sMessage = "Requested service not found";
            break;
        case SF_SOAPCONTENTERROR:
            sMessage = "Received content is faulty";
            break;
        case SF_NOSOAPMETHOD:
            sMessage = "Request method is not a soap method";
            break;
        case SF_METHODNOTALLOWED:
            sMessage = "Requested method is not allowed";
            break;
        case SF_PARATYPEMISMATCH:
            sMessage = "Parameter type mismatch";
            break;
        case SF_CLIENTHANDLERFAILED:
            sMessage = "Client handler failed";
	case SF_COULDNOTLOADSRV:
	    sMessage = "Could not load service";
	    break;
        case SF_COULDNOTLOADHDL:
            sMessage = "Could not load handler";
            break;
            break;
        case SF_HANDLERFAILED:
            sMessage = "Handler failed";
            break;
        case SF_WEBSERVICEFAILED:
            sMessage = "Web Service failed";
            break;
        case AXISC_RECEPTION_ERROR:
            sMessage = "Problem occured when receiving the stream";
            break;
        case AXISC_SENDING_ERROR:
            sMessage = "Problem occured when sending the stream";
            break;
        case AXISC_HTTP_ERROR:
            sMessage = "HTTP transport error";
            break;
        case AXISC_TRANSPORT_CONF_ERROR:
            sMessage = "Transport layer is not configured properly";
            break;
        case HANDLER_INIT_FAIL:
            sMessage = "Handler initialization failed";
            break;
        case HANDLER_CREATION_FAILED:
            sMessage = "Handler creation failed";
            break;
        case LOADLIBRARY_FAILED:
            sMessage = "Library loading failed";
            break;
        case LIBRARY_PATH_EMPTY:
            sMessage = "Library path is empty(Not in server.wsdd file)";
            break;
        case HANDLER_NOT_LOADED:
            sMessage = "Handler is not loaded";
            break;
        case HANDLER_BEING_USED:
            sMessage = "Handler is being used";
            break;
        case GET_HANDLER_FAILED:
            sMessage = "Get handler failed";
            break;
        case WRONG_HANDLER_TYPE:
            sMessage = "Wrong handler type";
            break;
        case NO_HANDLERS_CONFIGURED:
            sMessage = "No handlers configured in server.wsdd";
            break;
        case AXISC_TEST_ERROR:
            sMessage = "This is a testing error";
            break;
        default:
            sMessage = "Unknown error has occured";

    } 

    return sMessage;

}

AxisException::~AxisException() throw ()
{

}

const char* AxisException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisException::getExceptionCode()
{
    return m_iExceptionCode; 
}

