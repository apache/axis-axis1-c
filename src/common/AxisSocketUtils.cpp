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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *
 */

#include "AxisSocketUtils.h"
#include <axis/GDefine.hpp>
#include <stdio.h>
#if defined(WIN32) && !defined(CYGWIN)
#include <winsock.h>            /* for socket(),... */
#else //Linux
#endif

AxisSocketUtils::AxisSocketUtils ()
{

}

AxisSocketUtils::~AxisSocketUtils ()
{

}

int AxisSocketUtils::printSocketErrorDescription ()
{
#if defined(WIN32) && !defined(CYGWIN)
    int iErrorCode = WSAGetLastError ();

    if (iErrorCode == WSANOTINITIALISED)
    {
        printf ("%s\n", "WSANOTINITIALISED");
    }
    else if (iErrorCode == WSAENETDOWN)
    {
        printf ("%s\n", "WSAENETDOWN");
    }
    else if (iErrorCode == WSAEFAULT)
    {
        printf ("%s\n", "WSAEFAULT");
    }
    else if (iErrorCode == WSAEINTR)
    {
        printf ("%s\n", "WSAEINTR");
    }
    else if (iErrorCode == WSAEINPROGRESS)
    {
        printf ("%s\n", "WSAEINPROGRESS");
    }
    else if (iErrorCode == WSAEINVAL)
    {
        printf ("%s\n", "WSAEINVAL");
    }
    else if (iErrorCode == WSAEMFILE)
    {
        printf ("%s\n", "WSAEMFILE");
    }
    else if (iErrorCode == WSAENOBUFS)
    {
        printf ("%s\n", "WSAENOBUFS");
    }
    else if (iErrorCode == WSAENOTSOCK)
    {
        printf ("%s\n", "WSAENOTSOCK");
    }
    else if (iErrorCode == WSAEOPNOTSUPP)
    {
        printf ("%s\n", "WSAEOPNOTSUPP");
    }
    else if (iErrorCode == WSAEWOULDBLOCK)
    {
        printf ("%s\n", "WSAEWOULDBLOCK");
    }
#else //Linux
#endif

    return AXIS_SUCCESS;
}
