#include "GDefine.h"

#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "../soap/Attribute.h"
#include "../soap/SoapEnvVersions.h"

void Ax_Sleep(int nTime)
{
#ifdef WIN32
		Sleep(0);
#else
		sleep(0);
#endif
}

void ModuleInitialize()
{

}