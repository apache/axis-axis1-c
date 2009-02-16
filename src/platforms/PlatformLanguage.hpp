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
 */

#if !defined(AXIS_PLATFORMLANGUAGE_H__OF_AXIS_INCLUDED_)
#define AXIS_PLATFORMLANGUAGE_H__OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <string>
#include <wchar.h>

using namespace std;


AXIS_CPP_NAMESPACE_START

/**
 * Contains methods in support of national languages. 
 */
class STORAGE_CLASS_INFO PlatformLanguage
{
  public:
	/**
	  * Must be called once to initialize/allocate any internal objects that are needed. 
	  * Can be called multiple times - subsequent calls are no-ops. 
	  */ 
	static void initialize();
	
	/**
	  * Reclaims any allocated objects. Can be called multiple times.
	  */ 
	static void uninitialize();
	  
    /**
     * Returns dynamially allocated buffer containing the wide character representation 
     * of the passed-in character string.  Caller owns the memory returned. 
     * 
     * @param pointer to character string buffer.
     * @param number of characters in string, including null-terminator. 
     * 
     * @return pointer to null-terminated wide-character string.
     */
    static wchar_t * toWchar(const char *charBuf, int charLen);
    
    /**
     * Returns dynamially allocated buffer containing the character representation 
     * of the passed-in wide-character string.  Caller owns the memory returned. 
     * 
     * @param pointer to null-terminated wide-character buffer string.
     * @param number of characters in wide-character string, including null-terminator.
     * 
     * @return pointer to null-terminated character string.
     */
    static char *    toChar(const wchar_t *wcharBuf, int wcharLen);
    
    /**
     * Returns dynamically allocated buffer containing UTF-8 representation
     * of passed-in character data. Caller owns the memory returned.
     * 
     * @param pointer to null-terminated character string.
     * @param length of character string, including null-terminator.
     * 
     * @return pointer to null-terminated UTF-8 character string.
     */
    static char *    toUTF8(const char *charBuf, int charLen);
};

AXIS_CPP_NAMESPACE_END

#endif 
