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

#if !defined(_WSDDSERVICE_H__OF_AXIS_INCLUDED_)
#define _WSDDSERVICE_H__OF_AXIS_INCLUDED_

#include "WSDDHandler.h"
#include <axis/server/WSDDDefines.hpp>

/**
 *  @class WSDDService
 *  @brief interface for the WSDDService class.
 *  @author Susantha Kumara (skumara@virtusa.com)
 */

AXIS_CPP_NAMESPACE_START

class WSDDService : public WSDDHandler 
{
public:
    const list<AxisString> getAllowedMethods() const;
    void setProvider(const AxisChar* sProvider);
    PROVIDERTYPE getProvider() const;
    const AxisChar* getServiceName() const;
    bool isAllowedMethod(const AxisChar* sMethodName) const;
    void addAllowedMethod(const AxisChar* sMethodName);
    const WSDDHandlerList* getResponseFlowHandlers() const;
    void addHandler(bool bRequestFlow, WSDDHandler* pHandler);
    int removeHandler(bool bRequestFlow, WSDDHandler* pHandler);
    const WSDDHandlerList* getRequestFlowHandlers() const;
    void addAllowedRole(const AxisChar* sRole);
    const list<AxisString>& getAllowedRoles();
    WSDDService();
    virtual ~WSDDService();
    int updateWSDD(FILE* wsddfile, int tabcount);
private:
    const char* getProviderString();
private:
    PROVIDERTYPE m_Provider;
    list<AxisString> m_AllowedMethods;
    WSDDHandlerList* m_RequestHandlers;
    WSDDHandlerList* m_ResponseHandlers;
    list<AxisString> m_AllowedRoles;
};

typedef map<AxisString, WSDDService*> WSDDServiceMap;

AXIS_CPP_NAMESPACE_END

#endif

