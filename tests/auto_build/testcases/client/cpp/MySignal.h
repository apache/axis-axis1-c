
#if !defined(__MYSIGNAL_H__INCLUDED_)
#define __MYSIGNAL_H__INCLUDED_

#include <csignal>

#ifdef WIN32
void __cdecl trap_signal(int sig);
#else
void trap_signal(int sig);
#endif

#endif
