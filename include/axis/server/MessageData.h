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

#if !defined(_MESSAGEDATA_H____OF_AXIS_INCLUDED_)
#define _MESSAGEDATA_H____OF_AXIS_INCLUDED_

#include "GDefine.h"
#include "IMessageData.h"
#include "WSDDService.h"
#include "SoapSerializer.h"
#include "SoapDeSerializer.h"
#include "Param.h"
#include "AdminUtils.h"

#include <string>
#include <list>
#include <map>

using namespace std;
/**
    @class MessageData
    @brief interface for the MessageData class.


    @author Susantha Kumara (skumara@virtusa.com)
*/

struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

class MessageData : public IMessageData
{
public:
	MessageData();
	virtual ~MessageData();
public:
	IWrapperSoapSerializer* m_pSZ;
	IWrapperSoapDeSerializer* m_pDZ;
private:
	void getAdminUtils(IAdminUtils** pIAdminUtils);
public:
	const AxisChar* getProperty(AxisChar* pachName);
	int setProperty(AxisChar* pachName, const AxisChar* pachValue);
	void setOperationName(const AxisChar* pchOperation){m_sOperationName = pchOperation;};
	void getSoapDeSerializer(IHandlerSoapDeSerializer** pIHandlerSoapDeSerializer);
	const AxisChar* AXISCALL getOperationName(){return m_sOperationName.c_str();};
	void AXISCALL getSoapSerializer(IWrapperSoapSerializer** pIWSS);
	void AXISCALL getSoapDeSerializer(IWrapperSoapDeSerializer** pIWSDS);
	void getSoapSerializer(IHandlerSoapSerializer** pIHandlerSoapSerializer);
	IWrapperSoapDeSerializer* getSoapDeserializer();
	int setPastPivotState(bool bState);
	bool isPastPivot();
	void setDeSerializer(IWrapperSoapDeSerializer* pDZ);
	void setSerializer(IWrapperSoapSerializer* pSZ);
	void setUserName(string& m_sUserName);
	string& getUserName();
	void setService(const WSDDService* argService);
	const WSDDService* getService();  
	AXIS_PROTOCOL_TYPE m_Protocol;
	
protected:
  string m_sUserName;
  string m_sOperationName;
  const WSDDService* m_Service;

private:
	static AdminUtils m_AdminUtil;
	bool m_bPastPivotState;
	map <AxisChar*, AxisChar*, ltstr> m_Properties;
	static const AxisChar* m_pachBlankPropertyValue;
};

#endif // !defined(_MESSAGEDATA_H____OF_AXIS_INCLUDED_)
