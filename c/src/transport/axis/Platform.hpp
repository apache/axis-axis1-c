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

/*
 *
 * @author Lilantha Darshana (lilantha@erunway.com)
 *
 */


#if !defined(_AXIS_STDAFX_H)
#define _AXIS_STDAFX_H


#ifdef WIN32

#if _MSC_VER > 1000
#pragma once
#endif /* _MSC_VER > 1000 */

#define WIN32_LEAN_AND_MEAN        
/* Exclude rarely-used stuff from Windows headers */

#pragma warning ( disable : 4786 )


/* #include <afx.h> */
/* #include <afxwin.h> */

#ifdef AXIS_EXPORTS
#define AXIS_API __declspec(dllexport)
#else
#define AXIS_API __declspec(dllimport)
#endif


#else /* WIN32 */

#define AXIS_API
#include <unistd.h>
/* other OS specific stuff goes here */

#endif

#if defined(_DEBUG)
#    include <iostream>
#    define DebugMsg(x)    std::cout << x <<std::endl;
#else
#    define DebugMsg(x)
#endif

#endif




