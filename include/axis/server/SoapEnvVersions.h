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
 /**
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshan@jkcs.slt.lk)
 *
 */

/* SoapEnvVersions.h:*/

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#ifndef __SOAPENVVERSIONS_H_OF_AXIS_INCLUDED___
#define __SOAPENVVERSIONS_H_OF_AXIS_INCLUDED___

#include <stdlib.h>
#include "GDefine.h"

/*
 *Here SKW stands for SoapKeyWord. This is a internal naming convension
 * for Axis C++.
 */
typedef enum SOAP_WORDSTag {
	SKW_ENVELOPE=0, /*this should always be 0*/
	SKW_HEADER,
	SKW_BODY,
	SKW_MUSTUNDERSTAND,
	SKW_ACTOR,
	SKW_ENCODING_STYLE,
	SKW_FAULT,
	SKW_FAULT_CODE,
	SKW_FAULT_STRING,
	SKW_FAULT_ACTOR,
	SKW_DETAIL,
	SKW_MULTIREF,
	
	SKW_TYPE,
	SKW_ARRAYTYPE,
	SKW_HREF,
	SKW_ID,

	SOAP_WORDS_LAST /*this should be the number of entries in this enum */
} SOAP_WORDS;

typedef enum SOAP_VERSIONTag {
	SOAP_VER_1_1=0,
	SOAP_VER_1_2,

	VERSION_LAST
} SOAP_VERSION;

#ifdef __cplusplus

class Attribute;

struct SoapEnvVersionsStruct 
{	
	const AxisChar* pchNamespaceUri;
	const AxisChar* pchPrefix;
	const AxisChar* pchWords[SOAP_WORDS_LAST];
};

static SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST]=
{
	/*SOAP_VER_1_1*/
	{ 
		"http://schemas.xmlsoap.org/soap/envelope/",
		"SOAP-ENV",
		{
/*SKW_ENVELOPE*/		"Envelope",
/*SKW_HEADER*/			"Header",
/*SKW_BODY*/			"Body",
/*SKW_MUSTUNDERSTAND*/	"mustUnderstand",
/*SKW_ACTOR*/			"actor",
/*SKW_ENCODING_STYLE*/	"encodingStyle",
/*SKW_FAULT*/			"Fault",
/*SKW_FAULT_CODE*/		"faultcode",
/*SKW_FAULT_STRING*/	"faultstring",
/*SKW_FAULT_ACTOR*/		"faultactor",
/*SKW_DETAIL*/			"detail",
/*SKW_MULTIREF*/		"multiRef",

/*SKW_TYPE*/			"type",
/*SKW_ARRAYTYPE*/		"arrayType",
/*SKW_HREF*/			"href",
/*SKW_ID*/				"id"
		},
	},

	/*SOAP_VER_1_2*/
	{ 
		"http://www.w3.org/2003/05/soap-envelope",
		"env",
		{
/*SKW_ENVELOPE*/		"Envelope",
/*SKW_HEADER*/			"Header",
/*SKW_BODY*/			"Body",
/*SKW_MUSTUNDERSTAND*/	"mustUnderstand",
/*SKW_ACTOR*/			"actor",
/*SKW_ENCODING_STYLE*/	"encodingStyle",
/*SKW_FAULT*/			"Fault",
/*SKW_FAULT_CODE*/		"Code",
/*SKW_FAULT_STRING*/	"Reason",
/*SKW_FAULT_ACTOR*/		"Role",
/*SKW_DETAIL*/			"Detail",
/*SKW_MULTIREF*/		"multiRef",

/*SKW_TYPE*/			"type",
/*SKW_ARRAYTYPE*/		"arrayType",
/*SKW_HREF*/			"href",
/*SKW_ID*/				"id"
		},
	}
};
#endif

#endif /*__SOAPENVVERSIONS_H_OF_AXIS_INCLUDED___*/
