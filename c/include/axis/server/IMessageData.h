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

#if !defined(_IMESSAGEDATA_H___OF_AXIS_INCLUDED_)
#define _IMESSAGEDATA_H___OF_AXIS_INCLUDED_

#ifdef __cplusplus

#include "WSDDService.h"
#include "IAdminUtils.h"

#include <string>
using namespace std;

#include "IHandlerSoapDeSerializer.h"
#include "IHandlerSoapSerializer.h"
class IDeployerUtils;
#endif

#include "IWrapperSoapDeSerializer.h"
#include "IWrapperSoapSerializer.h"

typedef struct {
	const AxisChar* (AXISCALL* getOperationName)(void* pObj);
	void (AXISCALL* getSoapSerializer)(void* pObj, IWrapperSoapSerializer_C* pIWSS);
	void (AXISCALL* getSoapDeSerializer)(void* pObj, IWrapperSoapDeSerializer_C* pIWSDS);
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
	/* Allow AxisAdminService access to the private methods */
	friend class AxisAdminServiceWrapper; 
public:
    virtual ~IMessageData(){};
private:
	virtual void getAdminUtils(IAdminUtils** pIAdminUtils)=0;
public:
	virtual int setProperty(AxisChar* pachName, const AxisChar* pachValue)=0;
	virtual const AxisChar* getProperty(AxisChar* sName)=0;
	virtual const AxisChar* AXISCALL getOperationName()=0;
	virtual void AXISCALL getSoapSerializer(IWrapperSoapSerializer** pIWSS)=0;
	virtual void AXISCALL getSoapDeSerializer(IWrapperSoapDeSerializer** pIWSDS)=0;
	virtual void getSoapSerializer(IHandlerSoapSerializer** pIHandlerSoapSerializer)=0;
	virtual void getSoapDeSerializer(IHandlerSoapDeSerializer** pIHandlerSoapDeSerializer)=0;
	virtual void setUserName(string& m_sUserName)=0;
	virtual string& getUserName()=0;
    virtual void setService(const WSDDService* argService) = 0;
	virtual const WSDDService* getService() = 0; 
	virtual bool isPastPivot()=0;
	virtual int setPastPivotState(bool bState)=0;

	/* following stuff is needed to provide the interface for C web services */
public:
	static IMessageDataFunctions ms_VFtable;
	static const AxisChar* AXISCALL s_GetOperationName(void* pObj) 
	{ return ((IMessageData*)pObj)->getOperationName();};
	static void AXISCALL s_GetSoapSerializer(void* pObj, IWrapperSoapSerializer_C* pIWSS)
	{ ((IMessageData*)pObj)->getSoapSerializer((IWrapperSoapSerializer**)&(pIWSS->_object)); pIWSS->_functions = &(IWrapperSoapSerializer::ms_VFtable);};
	static void AXISCALL s_GetSoapDeSerializer(void* pObj, IWrapperSoapDeSerializer_C* pIWSDS)
	{ ((IMessageData*)pObj)->getSoapDeSerializer((IWrapperSoapDeSerializer**)&(pIWSDS->_object)); pIWSDS->_functions = &(IWrapperSoapDeSerializer::ms_VFtable);};
	static void s_Initialize()
	{
		ms_VFtable.getOperationName = s_GetOperationName;
		ms_VFtable.getSoapSerializer = s_GetSoapSerializer;
		ms_VFtable.getSoapDeSerializer = s_GetSoapDeSerializer;
	}
};

#endif

#endif /* !defined(_IMESSAGEDATA_H___OF_AXIS_INCLUDED_) */





