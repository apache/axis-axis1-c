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
 * @author Susantha Kumara (skumara@virtusa.com)
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *
 */

// AxisUtils.cpp: implementation of the AxisUtils class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/common/AxisUtils.h>
#include <axis/common/GDefine.h>

AxisXMLCh AxisUtils::m_Buffer[CONVERT_BUFFER_SIZE]; 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AxisUtils::AxisUtils()
{

}

AxisUtils::~AxisUtils()
{

}

const AxisXMLCh* AxisUtils::ToAxisXMLCh(const AxisChar* pch)
{
//	return XMLString::transcode(pch); //this is ok as long as we use xerces library.
	return pch;
}

void AxisUtils::Initialize()
{
}

//following functions is not thread safe and should only be used 
//for initialization purposes.
const AxisXMLCh* AxisUtils::Convert(const AxisChar* pch)
{
//	if (XMLString::transcode(pch, m_Buffer, CONVERT_BUFFER_SIZE))
//		return m_Buffer;
//	return NULL;
	return pch;
}


int AxisUtils::clearArray(char *arrCh, int iSize)
{
	for(int iTmp=0; iTmp<iSize; iTmp++) {
		arrCh[iTmp] = '\0';
	}

	return AXIS_SUCCESS;
}

bool AxisUtils::isCharacterAvailable(const string &sString, const char cCharacter)
{
	bool bFoundStatus = false;

	if ((sString.find(cCharacter, 0)) != string::npos) {
		bFoundStatus = true;
	}

	return bFoundStatus;
}

bool AxisUtils::isCharacterAvailable(const char *pchStringToSearch, const char cCharacter)
{
	bool bFoundStatus = false;

	if ( strchr(pchStringToSearch, cCharacter) ) {
		bFoundStatus = true;
	}

	return bFoundStatus;
}

string AxisUtils::toUpperCase(const string sWord)
{
	/*Fill the code*/

	return NULL;
}

char* AxisUtils::toUpperCase(const char *pchWord)
{
	/*Fill the code*/

	return NULL;
}

string AxisUtils::toLowerCase(const string sWord)
{
	/*Fill the code*/

	return NULL;
}

char* AxisUtils::toLowerCase(const char *pchWord)
{
	/*Fill the code*/

	return NULL;
}
