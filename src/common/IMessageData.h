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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *
 */
// IMessageData.h: interface for the IMessageData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMESSAGEDATA_H__EEFDCDB4_6ABA_48CA_8B45_B4FDA6045822__INCLUDED_)
#define AFX_IMESSAGEDATA_H__EEFDCDB4_6ABA_48CA_8B45_B4FDA6045822__INCLUDED_

#include <string>
using namespace std;

class IWrapperSoapDeSerializer;
class IHandlerSoapDeSerializer;
//class ISoapSerializer;
class IHandlerSoapSerializer;
class IWrapperSoapSerializer;

class IMessageData
{
public:
	virtual int setProperty(string& sName, string& sValue)=0;
	virtual string& getProperty(string& sName)=0;

	virtual void getSoapSerializer(IHandlerSoapSerializer** pIHandlerSoapSerializer)=0;
	virtual void getSoapSerializer(IWrapperSoapSerializer** pIWrapperSoapSerializer)=0;
	/*
	comm on 26Jul2003 2.50pm
	virtual ISoapSerializer* getSoapSerializer()=0;
	*/
	virtual IWrapperSoapDeSerializer* getSoapDeserializer()=0;

	virtual void getSoapDeSerializer(IWrapperSoapDeSerializer** pIWrapperSoapDeSerializer)=0;
	virtual void getSoapDeSerializer(IHandlerSoapDeSerializer** pIHandlerSoapDeSerializer)=0;

	virtual void SetUserName(string& m_sUserName)=0;
	virtual string& GetUserName()=0;
	virtual bool isPastPivot()=0;
	virtual int setPastPivotState(bool bState)=0;

protected:
  string m_sUserName;  
};

#endif // !defined(AFX_IMESSAGEDATA_H__EEFDCDB4_6ABA_48CA_8B45_B4FDA6045822__INCLUDED_)





