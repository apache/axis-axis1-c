/*
 *   Copyright 2004-2004 The Apache Software Foundation.
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


#include "PlatformSpecificOS400.hpp"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <qusec.h>                      // Qus_EC_t
#include <mih/rslvsp.h>                 // rslvsp()
#include <mih/micommon.h>               // _AUTH_EXECUTE
#include <qleawi.h>                     // QleActBndPgm(), QleGetExp()
#include <qp0lstdi.h>                   // Qp0lCvtPathToQSYSObjName()
#include <unistd.h>                     // readlink()
#include <except.h>

typedef int HMODULE;

/*
 * ==========================================
 * dlopen()
 * Gain access to an executable object file.
 * ==========================================
 */
void * os400_dlopen(const char *file)
{
    Qus_EC_t err = { sizeof(err),  0};

    // Assume symbolic link, if error, assume actual path
    char  dllPath[4*1024+1];
    memset(dllPath, 0x00, 4*1024+1);
    int rc = readlink ( file  , dllPath, 4*1024);
    if (rc == -1)
       strcpy(dllPath, file);

    // Uppercase file
    char *fp = dllPath;
    while (*fp++) *fp = toupper(*fp);

    // Parse the path to its QSYS.LIB file system name: library and service program.
    char pathNameBuffer[8*1024];
    Qlg_Path_Name_T *pathName = (Qlg_Path_Name_T *)pathNameBuffer;
    Qp0l_QSYS_Info_t  qsys_info;

    memset(pathNameBuffer, 0x00, sizeof (pathNameBuffer));
    pathName->Path_Length = strlen(dllPath);
    memcpy( &(((char *) pathName)[sizeof(Qlg_Path_Name_T)]), dllPath, pathName->Path_Length);
    pathName->Path_Name_Delimiter[0] = '/';

    Qp0lCvtPathToQSYSObjName(pathName,&qsys_info,"QSYS0100",sizeof(Qp0l_QSYS_Info_t), 0, &err);

    if (err.Bytes_Available)
        return NULL;

    // blank pad object name and library in order to use on rslvsp().
    char objectName[11];
    char objectLibrary[11];
    sprintf(objectName,   "%-10.10s", qsys_info.Obj_Name);
    sprintf(objectLibrary,"%-10.10s", qsys_info.Lib_Name);

    _SYSPTR sysP;
    _OBJ_TYPE_T objectType;

#pragma exception_handler (LBL_RSLV_EH, 0,_C1_ALL,_C2_MH_ESCAPE |_C2_MH_FUNCTION_CHECK, _CTLA_HANDLE)

    // Resolve pointer to DLL.
    objectType = WLI_SRVPGM;
    sysP = rslvsp(objectType,objectName, objectLibrary,_AUTH_EXECUTE);

#pragma disable_handler

    // We got a pointer to the DLL.  Activate it (i.e. load it).
    HMODULE handle;
    int actInfoLen;
    Qle_ABP_Info_t activationInfo;
    actInfoLen = sizeof(activationInfo);
    QleActBndPgm (&sysP,&handle,&activationInfo,&actInfoLen,&err);
    if (err.Bytes_Available)
        return NULL;

    // Return the dlopen object.
    void *returnHandle = malloc(sizeof(HMODULE));
    memcpy(returnHandle, &handle, sizeof(HMODULE));
    return returnHandle;

    LBL_RSLV_EH:
      return NULL;
}

/*
 * dlsym()
 * Obtain the address to symbol from a dlopen() object.
 */
void * os400_dlsym(void *handle, const char * name)
{
    void *symbolAddress = NULL;
    int exportType;

    Qus_EC_t err = {sizeof(err),0 };

#pragma exception_handler (LBL_RSLV_EH, 0,_C1_ALL,_C2_MH_ESCAPE |_C2_MH_FUNCTION_CHECK, _CTLA_HANDLE)

    // Get the function pointer.
    // Export type of 1 means that that the pointer is to a procedure.

    QleGetExp ((int *)handle,0,0,(char *)name,&symbolAddress,&exportType,&err);
    if (err.Bytes_Available)
        return NULL;

    return symbolAddress;

#pragma disable_handler

    LBL_RSLV_EH:
      return NULL;
}


/*
 * ==========================================
 * dlclose()
 * Close a dlopen() object.
 * ==========================================
 */
int os400_dlclose(void *handle)
{
    *(int *)handle = -1;
    free(handle);
    return 0;
}


