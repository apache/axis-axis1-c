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

#include "GDefine.hpp"
#include "IHandlerSoapDeSerializer.hpp"
#include "IHandlerSoapSerializer.hpp"
#include "IWrapperSoapDeSerializer.hpp"
#include "IWrapperSoapSerializer.hpp"

AXIS_CPP_NAMESPACE_START

class WSDDService;
class IAdminUtils;

/*
 *   @class IMessageData
 *   @brief interface for the IMessageData class.
 *   @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 *   @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
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
    virtual int setProperty(const AxisChar* pachName, const AxisChar* pachValue)=0;
    virtual int setProperty(const AxisChar* pachName, const void* pachValue, int len)=0;
    virtual void setComplexProperty(const AxisChar* pachName, void* pachValue, int iObjectSize)=0;
    virtual const void* getProperty(const AxisChar* sName)=0;
    virtual void* getComplexProperty(const AxisChar* pachName)=0;
    virtual const AxisChar* AXISCALL getOperationName()=0;
    virtual void AXISCALL getSoapSerializer(IWrapperSoapSerializer** pIWSS)=0;
    virtual void AXISCALL getSoapDeSerializer
        (IWrapperSoapDeSerializer** pIWSDS)=0;
    virtual void getSoapSerializer
        (IHandlerSoapSerializer** pIHandlerSoapSerializer)=0;
    virtual void getSoapDeSerializer
        (IHandlerSoapDeSerializer** pIHandlerSoapDeSerializer)=0;
    virtual void setUserName(string& m_sUserName)=0;
    virtual string& getUserName()=0;
    virtual bool isPastPivot()=0;
    virtual int setPastPivotState(bool bState)=0;
};

AXIS_CPP_NAMESPACE_END

#endif





