/* -*- C++ -*- */
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
 */

// !!! This include file must be first thing in file !!!
#include "PlatformAutoSense.hpp"

#include "PlatformLanguageUtils.hpp"

#include "../engine/AxisEngineException.h"
#include "../common/AxisTrace.h"


AXIS_CPP_NAMESPACE_START

//******************************************************************************
//
// PlatformLanguageUtils::toWchar() Implementation
//
//******************************************************************************
wchar_t * PlatformLanguageUtils::
toWchar(const char *charBuf, int charLen)
{
	logSetFunctionNameEngine("PlatformLanguageUtils::toWchar")
	
	if (charBuf == NULL || charLen == 0)
		return NULL;
	
	// Allocate buffer.  Need to make sure buffer will fit wide-character
	// representation of character string, including null-terminating character.
	wchar_t *outBuffer = new wchar_t[charLen];
	
	// Now call wide-character function to convert string to wide-character.
	size_t nbrGenerated = mbstowcs(outBuffer, charBuf, charLen);
	
	if (nbrGenerated == (size_t)-1)
	{
		delete [] outBuffer;
		
		logThrowExceptionNoExit("AxisEngineException: Error converting from character to wide-character.")
		
		throw AxisEngineException(-999, "Error converting from character to wide-character.");
	}
	
	return outBuffer;
}

//******************************************************************************
//
// PlatformLanguageUtils::toChar() Implementation
//
//******************************************************************************
char * PlatformLanguageUtils:: 
toChar(const wchar_t *wcharBuf, int wcharLen)
{
	logSetFunctionNameEngine("PlatformLanguageUtils::toChar")
	
	if (wcharBuf == NULL || wcharLen == 0)
		return NULL;
	
	// Allocate buffer.  Need to make sure buffer will fit character
	// representation of wide-character string, including null-terminating character.
	int bufLen = (wcharLen * MB_CUR_MAX);
	char *outBuffer = new char[bufLen];
	
	// Now call wide-character function to convert wide-character to character string.
	size_t nbrGenerated = wcstombs(outBuffer, wcharBuf, bufLen);
	
	if (nbrGenerated == (size_t)-1)
	{
		delete [] outBuffer;
		
		logThrowExceptionNoExit("AxisEngineException: Error converting from wide-character to character.")

		throw AxisEngineException(-999, "Error converting from wide-character to character.");
	}
	
	return outBuffer;
}

//******************************************************************************
//
// PlatformLanguageUtils::toUTF8() Implementation
//
//******************************************************************************
char * PlatformLanguageUtils:: 
toUTF8(const char *charBuf, int charLen)
{
	logSetFunctionNameEngine("PlatformLanguageUtils::toUTF8")
	
	if (charBuf == NULL || charLen == 0)
		return NULL;
	
	// TODO
	// I do not think there is a generic way to do this 
	// that is acceptable by windows and unix platforms (maybe iconv?), so if someone
	// wants to do this then they have to create plarform-specific copy of this file and
	// put in proper directory and update the build/buildClient.xml file to pick the 
	// platform file instead of the common file. See how os400 does it. 
	logThrowExceptionNoExit("AxisEngineException: Error converting to UTF-8.")

	throw AxisEngineException(-999, "Error converting to utf-8.");
}

AXIS_CPP_NAMESPACE_END
