// WsService.cpp : Defines the entry point for the DLL application.
//
#ifdef WIN32
#define STORAGE_CLASS_INFO __declspec(dllexport)
#else
#define STORAGE_CLASS_INFO
#endif

#include "LogHandler.h"

extern "C" {
//the two export functions////////////////////////////////////////////

//Following describes how the export function of the handler DLLs (or .so s)

STORAGE_CLASS_INFO
int GetClassInstance(BasicHandler **inst)
{
	*inst = new LogHandler();
	if (*inst)
	{
		return SUCCESS;
	}
	return FAIL;
}
STORAGE_CLASS_INFO
int DestroyInstance(BasicHandler *inst)
{
	if (inst)
	{
		delete inst;
		return SUCCESS;
	}
	return FAIL;
}

}