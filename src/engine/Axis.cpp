#include "AxisEngine.h"
#include "../common/Debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "../common/Packet.h"
#include <string>
#include <map>

#define res(X); send_response_bytes(X);

unsigned char chEBuf[1024];

extern "C" int process_request(soapstream *str)
{
DEBUG1("in axis.cpp");	
	AxisEngine* engine = AxisEngine::GetAxisEngine();	
	int ret = FAIL;
	char * wsdlloc = NULL;
	char * uri = NULL;
	int pos=0;
	int slashcount=0;
	int len = 0;

	FILE * outfile;
	const int bytestoread = 6;
	char oneword [bytestoread];
	oneword[bytestoread-1] = '\0';


	const WSDDServiceMap * svsmap = NULL;
	WSDDServiceMap::const_iterator iter;
	WSDDService * svs = NULL;
	//the location of the wsdl files hardcoded
	string svr("./Axis/wsdl/");

	switch(str->trtype)
	{
		case APTHTTP:
			//Handle the POST method
			if(str->so.http.ip_method==POST)
			{
DEBUG1("method is POST");                
				if (engine)
				{
					ret = engine->Process(str);
					DEBUG1("ret = engine->Process(str);");
				    DEBUG1("are we successful?");            
					ret = SUCCESS;
				}
			}

			//Handler the GET method
			if(str->so.http.ip_method==GET)
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
					svsmap = engine->getWSDDDeployment()->GetWSDDServiceMap();
					//dep = engine->getWSDDDeployment();
					//svsmap = depGetWSDDServiceMap();
					res("<html><body>\
						<h1 align=\"center\">Welcome to Axis C++</h1>\
						<br>\
						<h2>List of Deployed Web services<br></h2>\
						<h3>click on the links to view the WSDL</h3>\
						<br>\
						<table width=\"400\">");

					for (iter=svsmap->begin();iter!=svsmap->end();iter++)
					{
						svs = iter->second;
						res("<tr><td width=\"200\">");
						res((char *)svs->GetServiceName().c_str());
						res("</td><td width=\"200\"><a href=\"./");
						if (bNoSlash) send_response_bytes("axis/"); 
						send_response_bytes((char *)svs->GetServiceName().c_str());
						send_response_bytes("?wsdl");
						send_response_bytes("\">wsdl</a></td>");
						res("</tr>");
					}
					res("</table></body></html>");
				}
				else 
				{
					sServiceName = "./Axis/wsdl/" + sUriWOAxis + ".wsdl";
					//check whether wsdl file is available
					if((outfile = fopen(sServiceName.c_str(),"r"))==NULL)
					{
						send_response_bytes("<h3>Url not available</h3>");
						//handle the error
					}
					else
					{
						int charcount = 0;
						int acc = 0;	
						while((charcount=fread(oneword,1,bytestoread-1, outfile)) != 0)
						{
							*(oneword+charcount) = '\0';
							send_response_bytes(oneword);
  						}
						ret = SUCCESS;
						fclose(outfile);
					}
				}
			}
		break;

		default:
			send_response_bytes("Unknown Protocol");
		break;
	}
	svsmap = NULL;
	svs =NULL;
	return ret;
}

