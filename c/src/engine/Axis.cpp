#include "AxisEngine.h"
#include "../common/Debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "../common/Packet.h"

unsigned char chEBuf[1024];

//17.07.2003 the name process is changed to process_request(soapstream * str)
extern "C" int process_request(soapstream *str)
{
    DEBUG1("in axis.cpp");	
	AxisEngine* engine = AxisEngine::GetAxisEngine();	
	int ret = FAIL;
	//the location of the wsdl hardcoded
	char * wsdlloc = "e:\\Axis\\Calculator.wsdl";
	//char pointer to which the wsdl file will be read
	char * wsdl = NULL;
	FILE * outfile;
	const int bytestoread = 6;
	char oneword [bytestoread];
	oneword[bytestoread-1] = '\0';

	switch(str->trtype)
	{
		case APTHTTP:
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

			if(str->so.http.ip_method==GET)
			{
DEBUG1("method is GET");
				if((outfile = fopen(wsdlloc,"r"))==NULL)
				{
                  send_response_bytes("no wsdl to be found");
					//handle the error
					//str->so.http.op_soap = "Error in reading wsdl file";		
				}
				else
				{
					int charcount = 0;
					int acc = 0;
						while((charcount=fread(oneword,1,bytestoread-1, outfile)) != 0)
						{
							if(wsdl==NULL)
							{
								acc += charcount;
								wsdl = (char *)realloc(wsdl,acc);
                            wsdl = strcpy(wsdl,oneword);
							}
							else
							{
								wsdl = (char *)realloc(wsdl,acc+charcount);
								*(wsdl+(acc))='\0';
								acc += charcount;
								wsdl = strncat(wsdl, oneword,charcount);
							}
						}
					//assign the char pointer that contains the 
					//wsdl file to the response
					//str->so.http.op_soap = wsdl;
					send_response_bytes("dummy wsdl");
					ret = SUCCESS;
					fclose(outfile);
					//free (wsdl);
				}
			}
		break;

		default:
			//str->so.http.op_soap = "Unknown protocol";		
		break;

	}

	//str->op_soap = chEBuf;
	return ret;
}

