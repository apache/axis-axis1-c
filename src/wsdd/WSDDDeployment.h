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

#if !defined(AXIS_WSDDDEPLOYMENT_H__OF_AXIS_INCLUDED_)
#define AXIS_WSDDDEPLOYMENT_H__OF_AXIS_INCLUDED_

#include "WSDDService.h"
#include "WSDDHandler.h"
#include "WSDDTransport.h"

#include <list>

enum DEPLOYMENTTYPE {DT_DEPLOYMENT, DT_UNDEPLOYMENT};

AXIS_CPP_NAMESPACE_START

using namespace std;

/*
 *  @class WSDDDeployment
 *  @brief interface for the WSDDDeployment class.
 *  @author Susantha Kumara (skumara@virtusa.com)
 */
class WSDDDeployment
{
    friend class WSDDDocument;
public:
    int loadWSDD(const AxisChar* sWSDD);
    int updateWSDD(const AxisChar* sWSDD);
    int saveWSDD();
    const AxisChar* getLibName(int nLibId);
    const WSDDService* getService(const AxisChar* sServiceName);
    const WSDDHandlerList* getGlobalRequestFlowHandlers();
    const WSDDHandlerList* getGlobalResponseFlowHandlers();
    const WSDDHandlerList* getTransportRequestFlowHandlers
        (AXIS_PROTOCOL_TYPE protocol);
    const WSDDHandlerList* getTransportResponseFlowHandlers
        (AXIS_PROTOCOL_TYPE protocol);
    const WSDDServiceMap* getWSDDServiceMap() const;
    DEPLOYMENTTYPE getDeploymentType() const;
    WSDDDeployment();
    virtual ~WSDDDeployment();
private: /* methods that only be used by WSDDDepolyment. */
    int addService(WSDDService* pService);
    int addHandler(bool bGlobal, bool bRequestFlow, WSDDHandler* pHandler,
        AXIS_PROTOCOL_TYPE protocol=APTHTTP1_1);
    int removeService(WSDDService* pService);
    int removeHandler(bool bGlobal, bool bRequestFlow, WSDDHandler* pHandler,
        AXIS_PROTOCOL_TYPE protocol=APTHTTP1_1);
    void setDeploymentType(DEPLOYMENTTYPE nType);
private:
    WSDDServiceMap* m_DeployedServices;
    WSDDHandlerList* m_GlobalRequestHandlers;
    WSDDHandlerList* m_GlobalResponseHandlers;
    WSDDTransport* m_pTransportHandlers;
    std::map<AxisString, int>* m_pLibNameIdMap;
    AxisString m_sAux;
    std::string m_sWSDDPath;
    DEPLOYMENTTYPE m_DeplType;
};

AXIS_CPP_NAMESPACE_END

#endif 

