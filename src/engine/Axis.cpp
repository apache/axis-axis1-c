#pragma warning (disable : 4503)

#include "AxisEngine.h"
#include "../common/Debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "../common/Packet.h"
#include <string>
#include <map>

#include "../soap/SoapFaults.h"
#include "../soap/URIMapping.h"
#include "HandlerLoader.h"
#include "AppScopeHandlerPool.h"
#include "RequestScopeHandlerPool.h"
#include "SessionScopeHandlerPool.h"
#include "HandlerPool.h"
#include "SerializerPool.h"
#include "DeserializerPool.h"
#include "../wsdd/WSDDDeployment.h"

#define BYTESTOREAD 64
//the relative location of the wsdl files hardcoded
#define WSDLDIRECTORY	"./Axis/wsdl/"

#ifdef WIN32
#ifdef AXIS_APACHE1_3
#define WSDDFILEPATH "./Axis/conf/server.wsdd"
#else
#define WSDDFILEPATH "C:/Axis/conf/server.wsdd"
#endif
#else //For linux
#ifdef AXIS_APACHE1_3
#define WSDDFILEPATH "./Axis/conf/server.wsdd"
#else
#define WSDDFILEPATH "/usr/local/axiscpp/axis/server.wsdd"
#endif
#endif

//define all global variables of the axisengine
#ifdef _DEBUG
unsigned char chEBuf[1024];
#endif

//synchronized global variables.
HandlerLoader g_HandlerLoader;
AppScopeHandlerPool g_AppScopeHandlerPool;
RequestScopeHandlerPool g_RequestScopeHandlerPool;
SessionScopeHandlerPool g_SessionScopeHandlerPool;
DeserializerPool g_DeserializerPool;
SerializerPool g_SerializerPool;
HandlerPool g_HandlerPool;
//un synchronized read-only global variables.
WSDDDeployment g_WSDDDeployment;

extern "C" int process_request(Ax_soapstream *str)
{
	DEBUG1("in axis.cpp");	
	int Status = FAIL;
	FILE * WsddFile;
	char ReadBuffer[BYTESTOREAD];
	ReadBuffer[0] = '\0';

	const WSDDServiceMap* pSrvMap = NULL;
	WSDDServiceMap::const_iterator iter;
	WSDDService* pService = NULL;

	switch (str->trtype)
	{
		case APTHTTP:
			//Handle the POST method
			if (str->so.http.ip_method == AXIS_HTTP_POST)
			{
				DEBUG1("method is POST");
				AxisEngine* engine = new AxisEngine();	
				if (engine)
				{
					Status = engine->Process(str);
					DEBUG1("Status = engine->Process(str);");
				    DEBUG1("are we successful?");            
					Status = SUCCESS;
					delete engine;
				}
			}
			//Handler the GET method
			if (str->so.http.ip_method == AXIS_HTTP_GET)
			{
				//get the uri path
				//i.e "/abc/xyz/" part of http://somehost/abc/xyz/
				string sUri = str->so.http.uri_path;
				string sUriWOAxis = "";
				string sServiceName;
				bool bNoSlash = false;

				if (sUri.find("/axis/") != string::npos)
				{
					sUriWOAxis = sUri.substr(sUri.find("/axis/") + 6);
				}
				else
				{	
					bNoSlash = true;
				}

				if (sUriWOAxis.empty())
				{
					pSrvMap = g_WSDDDeployment.GetWSDDServiceMap();
					send_response_bytes("<html><body>\
						<h1 align=\"center\">Welcome to Axis C++</h1>\
						<br>\
						<h2>List of Deployed Web services<br></h2>\
						<h3>click on the links to view the WSDL</h3>\
						<br>\
						<table width=\"400\">", str->str.op_stream);

					for (iter = pSrvMap->begin();iter != pSrvMap->end();iter++)
					{
						pService = iter->second;
						send_response_bytes("<tr><td width=\"200\">", str->str.op_stream);
						send_response_bytes((char *)pService->GetServiceName().c_str(), str->str.op_stream);
						send_response_bytes("</td><td width=\"200\"><a href=\"./", str->str.op_stream);
						if (bNoSlash) send_response_bytes("axis/", str->str.op_stream); 
						send_response_bytes((char *)pService->GetServiceName().c_str(), str->str.op_stream);
						send_response_bytes("?wsdl", str->str.op_stream);
						send_response_bytes("\">wsdl</a></td>", str->str.op_stream);
						send_response_bytes("</tr>", str->str.op_stream);
					}
					send_response_bytes("</table></body></html>", str->str.op_stream);
				}
				else 
				{
					sServiceName = WSDLDIRECTORY + sUriWOAxis + ".wsdl";
					//check whether wsdl file is available
					if((WsddFile = fopen(sServiceName.c_str(),"r"))==NULL)
					{
						send_response_bytes("<h3>Url not available</h3>", str->str.op_stream);
						//handle the error
					}
					else
					{
						int charcount = 0;
						while((charcount = fread(ReadBuffer, 1, BYTESTOREAD-1, WsddFile)) != 0)
						{
							*(ReadBuffer + charcount) = '\0';
							send_response_bytes(ReadBuffer, str->str.op_stream);
  						}
						Status = SUCCESS;
						fclose(WsddFile);
					}
				}
			}
		break;

		default:
			send_response_bytes("Unknown Protocol", str->str.op_stream);
		break;
	}
	return Status;
}

extern "C" int initialize_module()
{
	TypeMapping::Initialize();
	URIMapping::Initialize();
	SoapFault::initialize();
	XMLPlatformUtils::Initialize();
	string ConfFile = WSDDFILEPATH;
	if (SUCCESS != g_WSDDDeployment.LoadWSDD(ConfFile)) return FAIL;
	return SUCCESS;
}
