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

#if !defined(__WSDDDOCUMENT_H_OF_AXIS_INCLUDED__)
#define __WSDDDOCUMENT_H_OF_AXIS_INCLUDED__

#include "WSDDDeployment.h"
#include <axis/server/WSDDService.h>
#include "../xml/QName.h"

enum WSDDLevels {WSDD_UNKNOWN=1, WSDD_DEPLOYMENT, WSDD_UNDEPLOYMENT,
                 WSDD_GLOBCONF, WSDD_SERVICE, WSDD_HANDLER, WSDD_CHAIN,
                 WSDD_TRANSPORT, WSDD_REQFLOW, WSDD_RESFLOW, WSDD_PARAM };

/* wsdd file related defines */
#define METHODNAME_SEPARATOR ' '
#define ROLENAME_SEPARATOR ','
#define TRANSCODE_BUFFER_SIZE 1024
/*
 *   @class WSDDDocument
 *   @brief Interface for WSDD processor
 *   @author Suasntha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 */
class WSDDDocument
{
protected: 
    bool m_bFatalError;
    bool m_bError;
    int m_nLibId;
    map<AxisString, int>* m_pLibNameIdMap;
    WSDDDeployment* m_pDeployment; 
    WSDDLevels m_lev0;
    WSDDLevels m_lev1;   /* gets values WSDD_REQFLOW or WSDD_RESFLOW */
    WSDDLevels m_lev2;   /* gets values WSDD_HANDLER or WSDD_CHAIN */
    map<AxisXMLString, AxisXMLString> m_NsStack;
    WSDDService* m_pService;   
    /* Place holder for currently created Service object */
    WSDDHandler* m_pHandler;   
    /* Place holder for currently created Handler object */
    AXIS_PROTOCOL_TYPE m_CurTrType;   
    /* Current transport type of transport handlers */
    AxisChar m_Buffer[TRANSCODE_BUFFER_SIZE];   
    /* used to transcode 'XMLCh' to AxisChar */
public:
    virtual ~WSDDDocument(){};
    virtual int getDeployment(const AxisChar* sWSDD,
        WSDDDeployment* pDeployment)=0;
    virtual int updateDeployment(const AxisChar* sWSDD,
        WSDDDeployment* pDeployment)=0;
};

#endif 

