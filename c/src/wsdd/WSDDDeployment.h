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

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(AXIS_WSDDDEPLOYMENT_H__INCLUDED_)
#define AXIS_WSDDDEPLOYMENT_H__INCLUDED_

#include <axis/server/WSDDService.h>
#include <axis/server/WSDDHandler.h>
#include "WSDDTransport.h"

#include <list>

using namespace std;

enum DEPLOYMENTTYPE {DT_DEPLOYMENT, DT_UNDEPLOYMENT};
/*
 *  @class WSDDDeployment
 *  @brief interface for the WSDDDeployment class.
 *  @author Susantha Kumara (skumara@virtusa.com)
 */
class WSDDDeployment
{
    friend class WSDDDocumentExpat;
    friend class WSDDDocumentXerces;
public:
    int LoadWSDD(const AxisChar* sWSDD);
    int UpdateWSDD(const AxisChar* sWSDD);
    int SaveWSDD();
    const AxisChar* GetLibName(int nLibId);
    const WSDDService* GetService(const AxisChar* sServiceName);
    const WSDDHandlerList* GetGlobalRequestFlowHandlers();
    const WSDDHandlerList* GetGlobalResponseFlowHandlers();
    const WSDDHandlerList* GetTransportRequestFlowHandlers
        (AXIS_PROTOCOL_TYPE protocol);
    const WSDDHandlerList* GetTransportResponseFlowHandlers
        (AXIS_PROTOCOL_TYPE protocol);
    const WSDDServiceMap* GetWSDDServiceMap() const;
    DEPLOYMENTTYPE GetDeploymentType() const;
    WSDDDeployment();
    virtual ~WSDDDeployment();
private: /* methods that only be used by WSDDDepolyment. */
    int AddService(WSDDService* pService);
    int AddHandler(bool bGlobal, bool bRequestFlow, WSDDHandler* pHandler,
        AXIS_PROTOCOL_TYPE protocol=APTHTTP);
    int RemoveService(WSDDService* pService);
    int RemoveHandler(bool bGlobal, bool bRequestFlow, WSDDHandler* pHandler,
        AXIS_PROTOCOL_TYPE protocol=APTHTTP);
    void SetDeploymentType(DEPLOYMENTTYPE nType);
private:
    WSDDServiceMap* m_DeployedServices;
    WSDDHandlerList* m_GlobalRequestHandlers;
    WSDDHandlerList* m_GlobalResponseHandlers;
    WSDDTransport* m_pTransportHandlers;
    map<AxisString, int>* m_pLibNameIdMap;
    AxisString m_sAux;
    string m_sWSDDPath;
    DEPLOYMENTTYPE m_DeplType;
};

#endif 

