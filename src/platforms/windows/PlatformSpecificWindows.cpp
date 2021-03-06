/*
 *   Copyright 2004-2004 The Apache Software Foundation.
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
 */


#include "PlatformSpecificWindows.hpp"
#include <stdio.h>



std::string getPlatformErrorMessage(long errorNumber)
{
    LPVOID lpMsgBuf;

	FormatMessage(
	FORMAT_MESSAGE_ALLOCATE_BUFFER | 
	FORMAT_MESSAGE_FROM_SYSTEM,
	NULL,
	errorNumber,
	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	(LPTSTR) &lpMsgBuf,
	0, NULL );

	std::string returningString((LPTSTR)lpMsgBuf);
    LocalFree(lpMsgBuf);
		    
    return returningString;
}

HMODULE callLoadLib(LPCTSTR lib)
{

        SetErrorMode(SEM_FAILCRITICALERRORS); //Disable display of the critical-error-handler message box
        return LoadLibrary(lib);
}



