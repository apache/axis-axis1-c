#include "HandlerLoader.h"
#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string sLib = "E:/axiscpp/release/win32/WsService.dll";
	HandlerLoader* pDL = new HandlerLoader(sLib);
	if (SUCCESS == pDL->Initialize())
	{	
		printf("Loaded Library %s\n", sLib.c_str());
		pDL->Finalize();
		printf("Unloaded Library %s\n", sLib.c_str());
	}
	return 0;
}