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
 */

#include "mod_axis_isapi.h"

DWORD WINAPI HttpExtensionProc(IN EXTENSION_CONTROL_BLOCK *pECB)
{
    static char szMessage[] = 
    "<hello>Test</hello>\r\n";

    HSE_SEND_HEADER_EX_INFO HeaderExInfo;

    /* prepare headers  */

    HeaderExInfo.pszStatus = "200 OK";
    HeaderExInfo.pszHeader = "Content-type: text/xml\r\n\r\n";
    HeaderExInfo.cchStatus = strlen(HeaderExInfo.pszStatus);
    HeaderExInfo.cchHeader = strlen(HeaderExInfo.pszHeader);
    HeaderExInfo.fKeepConn = FALSE;

    /* send headers using IIS-provided callback
     *
     * Note - if we needed to keep connection open, we would set fKeepConn 
     * to TRUE *and* we would need to provide correct Content-Length: header
     */

    pECB->ServerSupportFunction(pECB->ConnID, HSE_REQ_SEND_RESPONSE_HEADER_EX, 
        &HeaderExInfo, NULL, NULL);

    /* Calculate length of string to output to client */

    DWORD dwBytesToWrite = strlen( szMessage );

    /* send text using IIS-provied callback */

    pECB->WriteClient( pECB->ConnID, szMessage, &dwBytesToWrite, 0 );

    /* Indicate that the call to HttpExtensionProc was successful */

    return HSE_STATUS_SUCCESS;
}


BOOL WINAPI TerminateExtension(IN DWORD dwFlags)
{
    // Note: We must not agree to be unloaded if we have any pending requests.

    return TRUE;
}

BOOL WINAPI DllMain(IN HINSTANCE hinstDll, IN DWORD dwReason, 
                    IN LPVOID lpvContext)
{
    // Note that appropriate initialization and termination code
    // would be written within the switch statement below.  Because
    // this example is very simple, none is currently needed.

    switch(dwReason)
    {

        case DLL_PROCESS_ATTACH :

            break;

        case DLL_PROCESS_DETACH :

            break;
    }

    return TRUE;
}


BOOL WINAPI GetExtensionVersion(OUT HSE_VERSION_INFO *pVer)
{
    pVer->dwExtensionVersion = MAKELONG(HSE_VERSION_MINOR, HSE_VERSION_MAJOR);

    lstrcpyn(pVer->lpszExtensionDesc, "IIS SDK Simple ISAPI Extension", 
        HSE_MAX_EXT_DLL_NAME_LEN - 1);

    return TRUE;
}





