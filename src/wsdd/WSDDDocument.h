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
#pragma warning(disable : 4786)
#endif

#if !defined(__WSDDDOCUMENT_H_OF_AXIS_INCLUDED__)
#define __WSDDDOCUMENT_H_OF_AXIS_INCLUDED__

#include "WSDDDocument.h"
#include <axis/SOAPTransport.h>
#include <axis/server/AnyElement.h>
#include "WSDDDeployment.h"
#include <axis/server/WSDDService.h>
#include "../xml/QName.h"

#include <string>
#include <map>

using namespace std;

enum WSDDLevels {WSDD_UNKNOWN=1, WSDD_DEPLOYMENT, WSDD_UNDEPLOYMENT,
                 WSDD_GLOBCONF, WSDD_SERVICE, WSDD_HANDLER, WSDD_CHAIN,
                 WSDD_TRANSPORT, WSDD_REQFLOW, WSDD_RESFLOW, WSDD_PARAM };

#define METHODNAME_SEPARATOR ' '
#define ROLENAME_SEPARATOR ','
#define TRANSCODE_BUFFER_SIZE 1024

/*
 *  @class WSDDDocument
 *  @brief
 *  @author Sanjaya Sinharage(sanjaya@opensource.lk)
 *  @author Suasntha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 */
class WSDDDocument
{

public:
    WSDDDocument(map<AxisString, int>* pLibNameIdMap);
    ~WSDDDocument();
    int getDeployment(const AxisChar* pcWSDDFileName, WSDDDeployment* pDeployment);
    int updateDeployment(const AxisChar* pcWSDDMemBuffer, WSDDDeployment* pDeployment);
    void startElement(const AnyElement* pEvent);
    void endElement(const AnyElement* pEvent);

	/* inner class */
	class WSDDFileInputStream : public AxisIOStream
	{
	private:
		const char* m_pcWSDDFileName;
		FILE *m_pFile;
	public:
		WSDDFileInputStream(const char* pcWSDDFileName)
		{m_pcWSDDFileName = pcWSDDFileName; m_pFile = 0;};
		virtual ~WSDDFileInputStream(){};
		AXIS_TRANSPORT_STATUS sendBytes(const char* pcSendBuffer, const void* pBufferid);
		AXIS_TRANSPORT_STATUS getBytes(char* pcBuffer, int* piRetSize);
	};

	class WSDDMemBufInputStream : public AxisIOStream
	{
	private:
		const char* m_pcWSDDMemBuffer;
	public:
		WSDDMemBufInputStream(const char* pcWSDDMemBuffer)
		{m_pcWSDDMemBuffer = pcWSDDMemBuffer;};
		virtual ~WSDDMemBufInputStream(){};
		AXIS_TRANSPORT_STATUS sendBytes(const char* pcSendBuffer, const void* pBufferid);
		AXIS_TRANSPORT_STATUS getBytes(char* pcBuffer, int* piRetSize);
	};
private:
    void processAttributes(WSDDLevels eElementType, const AnyElement* pEvent);
    void getParameters(WSDDLevels eElementType, const AnyElement* pEvent);
    void addAllowedRolesToService(const AxisXMLCh* pcValue);
    void addAllowedMethodsToService(const AxisXMLCh* pcValue);
    int parseDocument(const AxisChar* pcWSDDFileName);
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
};

#endif
 