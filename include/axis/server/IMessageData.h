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
 */
/* IMessageData.h:*/



#if !defined(AFX_IMESSAGEDATA_H__EEFDCDB4_6ABA_48CA_8B45_B4FDA6045822__INCLUDED_)
#define AFX_IMESSAGEDATA_H__EEFDCDB4_6ABA_48CA_8B45_B4FDA6045822__INCLUDED_

#ifdef __cplusplus

#include "../wsdd/WSDDService.h"
#include <string>
using namespace std;

#include "IHandlerSoapDeSerializer.h"
#include "IHandlerSoapSerializer.h"
class IDeployerUtils;
#endif

#include "IWrapperSoapDeSerializer.h"
#include "IWrapperSoapSerializer.h"

typedef struct {
	const AxisChar* (AXISCALL* GetOperationName)(void* pObj);
	void (AXISCALL* GetSoapSerializer)(void* pObj, IWrapperSoapSerializer_C* pIWSS);
	void (AXISCALL* GetSoapDeSerializer)(void* pObj, IWrapperSoapDeSerializer_C* pIWSDS);
} IMessageDataFunctions;

typedef struct
{
	void* _object; /* this will be C++ MessageData Object */
	IMessageDataFunctions* _functions; /* this is the static function table */
} IMessageData_C;

#ifndef __cplusplus
typedef IMessageData_C IMessageData;
#else
/**
    @class IMessageData
    @brief interface for the IMessageData class.

    @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
    @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
*/
class IMessageData
{
	friend class CPP_DeploymentWrapper;
public:
    virtual ~IMessageData(){};
private:
	virtual void getWSDDDeployment(IDeployerUtils** pIDeployerUtils) = 0;
public:
	virtual int setProperty(AxisChar* pachName, const AxisChar* pachValue)=0;
	virtual const AxisChar* getProperty(AxisChar* sName)=0;
	virtual const AxisChar* AXISCALL GetOperationName()=0;
	virtual void AXISCALL GetSoapSerializer(IWrapperSoapSerializer** pIWSS)=0;
	virtual void AXISCALL GetSoapDeSerializer(IWrapperSoapDeSerializer** pIWSDS)=0;
	virtual void getSoapSerializer(IHandlerSoapSerializer** pIHandlerSoapSerializer)=0;
	virtual void getSoapDeSerializer(IHandlerSoapDeSerializer** pIHandlerSoapDeSerializer)=0;
	virtual void SetUserName(string& m_sUserName)=0;
	virtual string& GetUserName()=0;
    virtual void SetService(const WSDDService* argService) = 0;
	virtual const WSDDService* GetService() = 0; 
	virtual bool isPastPivot()=0;
	virtual int setPastPivotState(bool bState)=0;

	/* following stuff is needed to provide the interface for C web services */
public:
	static IMessageDataFunctions ms_VFtable;
	static const AxisChar* AXISCALL s_GetOperationName(void* pObj) 
	{ return ((IMessageData*)pObj)->GetOperationName();};
	static void AXISCALL s_GetSoapSerializer(void* pObj, IWrapperSoapSerializer_C* pIWSS)
	{ ((IMessageData*)pObj)->GetSoapSerializer((IWrapperSoapSerializer**)&(pIWSS->_object)); pIWSS->_functions = &(IWrapperSoapSerializer::ms_VFtable);};
	static void AXISCALL s_GetSoapDeSerializer(void* pObj, IWrapperSoapDeSerializer_C* pIWSDS)
	{ ((IMessageData*)pObj)->GetSoapDeSerializer((IWrapperSoapDeSerializer**)&(pIWSDS->_object)); pIWSDS->_functions = &(IWrapperSoapDeSerializer::ms_VFtable);};
	static void s_Initialize()
	{
		ms_VFtable.GetOperationName = s_GetOperationName;
		ms_VFtable.GetSoapSerializer = s_GetSoapSerializer;
		ms_VFtable.GetSoapDeSerializer = s_GetSoapDeSerializer;
	}
};

#endif

#endif /* !defined(AFX_IMESSAGEDATA_H__EEFDCDB4_6ABA_48CA_8B45_B4FDA6045822__INCLUDED_) */





