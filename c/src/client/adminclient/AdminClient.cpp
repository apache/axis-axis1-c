#include "AxisAdminService.h"
#include <string>
using namespace std;

#define FILEBUFFSIZE 256

int main(int argc, char* argv[])
{
	int done;
	int len;
	char Buff[FILEBUFFSIZE];
	string Uri = "http://";
	string wsdd;
	if (argc < 3)
	{
		printf("Usage: %s <server> <port> <wsdd file>\n", argv[0]);	
		exit(1);
	}
	Uri += argv[1];
	Uri += ":";
	Uri += argv[2];
	Uri += "/axis/AxisAdmin";
	wsdd = argv[3];

	FILE *file = fopen(wsdd.c_str(), "r");
	if (NULL == file) 
	{ 
		printf("WSDD file %s cannot be opened\n", wsdd.c_str());
		printf("Usage: %s <server> <port> <wsdd file>\n", argv[0]);	
		exit(1);
	}
	wsdd = "";
	while (true) 
	{
		len = fread(Buff, 1, FILEBUFFSIZE, file);
		Buff[len]=0;
		if (ferror(file)) 
		{
			fclose(file);
			printf("WSDD file %s cannot be read\n", wsdd.c_str());
			printf("Usage: %s <server> <port> <wsdd file>\n", argv[0]);	
			exit(1);
		}
		done = feof(file);
		wsdd += Buff;
		if (done)
			break;
	}
	fclose(file);

	AxisAdminService ws(Uri.c_str());
	xsd__base64Binary v;
	v.__ptr = (unsigned char*)wsdd.c_str();
	v.__size = wsdd.length();
	if (true_ == ws.updateWSDD(v))
	{
		printf("server wsdd at %s updated successfully\n", Uri.c_str());
	}
	else
	{
		printf("wsdd update at %s failed\n", Uri.c_str());
	}
	return 0;
}