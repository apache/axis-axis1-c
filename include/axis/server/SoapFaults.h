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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 *
 */

// SoapFaults.h:
//
//////////////////////////////////////////////////////////////////////

#ifndef __SOAPFAULTS_H_INCLUDED___
#define __SOAPFAULTS_H_INCLUDED___

/*
 *The structure which is used as a container for soap faults.
 */
struct SoapFaultStruct
{
	const char* pchFaultcode;
	const char* pchFaultstring;
	const char* pchFaultactor;
	const char* pchDetail;
	
};

/*
 *The following enumeration is used to serve the Axis C++ codes for 
 * soap faults.
 */
enum SOAP_FAULTS {
	//VersionMismatch faults
	SF_VERSION_MISMATCH,
	
	//MustUnderstand faults
	SF_MUST_UNDERSTAND,

	//Client faults
	SF_SOAPACTIONEMPTY,
	SF_SERVICENOTFOUND,
	SF_SOAPCONTENTERROR,
	SF_NOSOAPMETHOD,
	SF_METHODNOTALLOWED,
	SF_PARATYPEMISMATCH,
	SF_CLIENTHANDLERFAILED,

	//Server faults
	SF_COULDNOTLOADSRV,
	SF_COULDNOTLOADHDL,
	SF_HANDLERFAILED,
	SF_WEBSERVICEFAILED,

	//This FAULT_LAST is not used as a fault code, but instead is used 
	// internaly in the code. Developers should not use this as a fault 
	// code.
	FAULT_LAST
};

/*
 *The following array of structure is used to store all the soap faults
 * which are used in Axis C++. Each time a fault object is needed it is
 * created using this array, in SoapFault class.
 */
static SoapFaultStruct g_sObjSoapFaultStruct[FAULT_LAST] = 
						{
//VersionMismatch faults
	/*SF_VERSION_MISMATCH*/	{"VersionMismatch", "Soap Version Mismatch error", "none", ""},

//MustUnderstand faults
	/*SF_MUST_UNDERSTAND*/	{"MustUnderstand", "Soap Must Understand  error", "none", ""},

//Client faults
	/*SF_SOAPACTIONEMPTY*/	{"Client", "Soap Action header empty", "none", ""},
	/*SF_SERVICENOTFOUND*/	{"Client", "Requested service is not registerd at the server", "none", ""},
	/*SF_SOAPCONTENTERROR*/ {"Client", "Soap content is not valid", "none", ""},
	/*SF_NOSOAPMETHOD*/		{"Client", "No method to invoke", "none", ""},
	/*SF_METHODNOTALLOWED*/	{"Client", "Soap method is not allowed to invoke", "none", ""},
  /*SF_PARATYPEMISMATCH*/	{"Client", "Parameter type mismatch", "none", ""},
  /*SF_CLIENTHANDLERFAILED*/{"Client", "A client handler failed", "none", ""},

//Server faults
	/*SF_COULDNOTLOADSRV*/	{"Server", "Cannot load web service", "none", ""},
	/*SF_COULDNOTLOADHDL*/	{"Server", "Cannot load service handlers", "none", ""},
	/*SF_HANDLERFAILED*/	{"Server", "A service handler failed", "none", ""},
	/*SF_WEBSERVICEFAILED*/	{"Server", "Webservice failed", "none", ""}
						};		

#endif //__SOAPFAULTS_H_INCLUDED___
