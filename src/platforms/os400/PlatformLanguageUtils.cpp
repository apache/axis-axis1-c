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
#include "../PlatformAutoSense.hpp"

#include <limits.h>                     // MB_LEN_MAX
#include <iconv.h>                      // iconv_t, iconv()
#include <qtqiconv.h>                   // QtqCode_T, QtqIconvOpen()
#include <errno.h>

#include "../PlatformLanguageUtils.hpp"

#include "../../engine/AxisEngineException.h"
#include "../../common/AxisTrace.h"

// code pages for job, utf-8, and ucs2 
#define CCSID_JOB 0
#define CCSID_UTF8 1208
#define CCSID_UCS2 13488

AXIS_CPP_NAMESPACE_START

// Following helper function is defined at the bottom.
static iconv_t generateConverter(int fromCcsid, int toCcsid);

//******************************************************************************
//
// PlatformLanguageUtils::toWchar() Implementation
//
// Notes: 
//   - Wide character is implemented as UCS-2 when compiled with LOCALETYPE(*LOCALEUCS2).
//     Because the C runtime wide-character routines depend on locale, and
//     locale is not normally set, we need to do the conversions using iconv.
//
//******************************************************************************
static iconv_t cvtrJobToUCS2 = generateConverter(CCSID_JOB, CCSID_UCS2);

wchar_t * PlatformLanguageUtils::
toWchar(const char *charBuf, int charLen)
{
	logSetFunctionNameEngine("PlatformLanguageUtils::toWchar")

	if (charLen == 0 || charBuf == NULL)
		return NULL;

	size_t outBytesLeft = charLen*sizeof(wchar_t);
	wchar_t *outBuffer = (wchar_t *) new wchar_t[charLen];

	int myToBufLen = outBytesLeft;
	char *myToBuf = (char *)outBuffer;

	size_t irc = iconv(cvtrJobToUCS2, (char **)&charBuf, (size_t *)&charLen, &myToBuf, &outBytesLeft);
	myToBufLen -= outBytesLeft;

	if (irc == (size_t)-1)
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
// Notes: 
//   - Wide character is implemented as UCS-2 when compiled with LOCALETYPE(*LOCALEUCS2).
//     Because the C runtime wide-character routines depend on locale, and
//     locale is not normally set, we need to do the conversions using iconv.
//
//******************************************************************************
static iconv_t cvtrUCS2ToJob = generateConverter(CCSID_UCS2, CCSID_JOB);
char * PlatformLanguageUtils:: 
toChar(const wchar_t *wcharBuf, int wcharLen)
{
	logSetFunctionNameEngine("PlatformLanguageUtils::toChar")

	if (wcharLen == 0 || wcharBuf == NULL)
		return NULL;

	size_t outBytesLeft = (wcharLen * MB_LEN_MAX);
	char *outBuffer = (char *) new char[wcharLen * MB_LEN_MAX];

	int myToBufLen = outBytesLeft;
	char *myToBuf = outBuffer;

	size_t irc = iconv(cvtrUCS2ToJob, (char **)&wcharBuf, (size_t *)&wcharLen, &myToBuf, &outBytesLeft);
	myToBufLen -= outBytesLeft;

	if (irc == (size_t)-1)
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
static iconv_t cvtrJobToUtf8 = generateConverter(CCSID_JOB, CCSID_UTF8);

char * PlatformLanguageUtils::
toUTF8(const char *charBuf, int charLen)
{
   logSetFunctionNameEngine("PlatformLanguageUtils::toUTF8")

   if (charLen == 0 || charBuf == NULL)
      return strdup("");

   size_t outBytesLeft = 4*charLen;
   char *outBuffer = (char *) new char[outBytesLeft];

   int myToBufLen = outBytesLeft;
   char *myToBuf = outBuffer;

   size_t irc = iconv(cvtrJobToUtf8, (char **)&charBuf, (size_t *)&charLen,&myToBuf, &outBytesLeft);
   myToBufLen -= outBytesLeft;
        
   if (irc == (size_t)-1)
   {
	   delete [] outBuffer;
	   
       logThrowExceptionNoExit("AxisEngineException: Error converting to UTF-8.")

       throw AxisEngineException(-999, "Error converting to utf-8.");   
   }

   return outBuffer;
}

// +++++++++++++++++++++++++++++++++++++++++
// FOLLOWING ARE UTILITY ROUTINES
// +++++++++++++++++++++++++++++++++++++++++

//==============================================================================
//
// generateConverter() Implementation
//
//==============================================================================

iconv_t generateConverter
(
 int fromCcsid,
 int toCcsid
 )
{
    iconv_t converterObject;
    
    QtqCode_T toCode, fromCode;
    
    memset(&toCode, 0x00, sizeof(QtqCode_T));
    memset(&fromCode, 0x00, sizeof(QtqCode_T));

    fromCode.CCSID = fromCcsid;
    fromCode.shift_alternative = 1;
    toCode.CCSID = toCcsid;
    converterObject = QtqIconvOpen(&toCode, &fromCode);

    return converterObject;
}

AXIS_CPP_NAMESPACE_END
