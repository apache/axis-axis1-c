// SharedObject.cpp: implementation of the SharedObject class.
//
//////////////////////////////////////////////////////////////////////

#include "SharedObject.h"

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
		Ax_Sleep(0);
	}
	m_bLocked = true;
	return 0;
}

int SharedObject::unlock()
{
	m_bLocked = false;
	return 0;
}

