/* -*- C++ -*- */
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

#if !defined(AXIS_SERVERAXISENGINE_H__OF_AXIS_INCLUDED_)
#define AXIS_SERVERAXISENGINE_H__OF_AXIS_INCLUDED_

#include "../AxisEngine.h"
#include "../AxisEngineException.h"
#include "../../soap/AxisSoapException.h"
#include "../../wsdd/AxisWsddException.h"
#include "../../common/AxisConfigException.h"
/*
 *  @class ServerAxisEngine
 *  @brief interface for the ServerAxisEngine class.
 *
 *
 *  @author Susantha Kumara (skumara@virtusa.com)
 */

AXIS_CPP_NAMESPACE_START class ServerAxisEngine:public AxisEngine
{
  private:
    BasicHandler * m_pWebService;
    const WSDDService *m_pService;
  public:
    ServerAxisEngine ();
    virtual ~ ServerAxisEngine ();
  public:
    int process (SOAPTransport * pSoap);

	/** When fault occures it need to be written to the stream. If fail is 
         *  returned from the process method of ServerAxisEngine this method is
         *  called within the process_request method of Axis.cpp
         */
    int setFaultOutputStream (int iFaultCode, SOAPTransport * pSoap);
    int setFaultOutputStream (AxisException iFault, SOAPTransport * pSoap);
                  
	/** When finished with handlers and webservices release them
         *  back to the pool
         */
    int releaseHandlers (SOAPTransport * pSoap);

  protected:
    virtual int invoke (MessageData * pMsg);
    virtual void onFault (MessageData * pMsg);
};

AXIS_CPP_NAMESPACE_END
#endif
