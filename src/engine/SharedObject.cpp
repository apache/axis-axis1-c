// SharedObject.cpp: implementation of the SharedObject class.
//
//////////////////////////////////////////////////////////////////////

#include "SharedObject.h"
#ifdef WIN32
#include <Windows.h>
#else

#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SharedObject::SharedObject()
{
	m_bLocked = false;
}

SharedObject::~SharedObject()
{

}
//Following functions should be improved to avoid chances of failure
//using platform specific mechanisms
int SharedObject::lock()
{
	while (m_bLocked)
	{
#ifdef WIN32
		Sleep(0);
#else
		sleep(0);
#endif
	}
	m_bLocked = true;
	return 0;
}

int SharedObject::unlock()
{
	m_bLocked = false;
	return 0;
}
