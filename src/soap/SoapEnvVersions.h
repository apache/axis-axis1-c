/* -*- C++ -*- */

/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Roshan
 *
 */

// SoapEnvVersions.h:
//
//////////////////////////////////////////////////////////////////////

#ifndef __SOAPENVVERSIONS_H_INCLUDED___
#define __SOAPENVVERSIONS_H_INCLUDED___

/*
 *Here SKW stands for SoapKeyWord. This is a internal naming convension
 * for Axis C++.
 */
enum SOAP_WORDS {
	SKW_ENVELOPE,
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

	SOAP_WORDS_LAST
};

enum SOAP_VERSION {
	SOAP_VER_1_1=0,
	SOAP_VER_1_2,

	VERSION_LAST
};

struct SoapEnvVersionsStruct {	
	char* pchEnvelopeNamespaceUri;
	char* pchEnvelopePrefix;
	char* pcharWords[SOAP_WORDS_LAST];
};

static SoapEnvVersionsStruct g_sObjSoapEnvVersionsStruct[VERSION_LAST]=
	{
		//SOAP_VER_1_1
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
/*SKW_MULTIREF*/		"multiRef"
			} 
		},

		//SOAP_VER_1_2
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
/*SKW_MULTIREF*/		"multiRef"
			} 
		}
	};	

#endif //__SOAPENVVERSIONS_H_INCLUDED___