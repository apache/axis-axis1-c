
#include "MySignal.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
void __cdecl trap_signal(int sig) {
#else
void trap_signal(int sig) {
#endif
	char *strSig = "unknown";
	switch(sig) {
		case SIGABRT:
			strSig = "SIGABRT";
			break;
		case SIGILL:
			strSig = "SIGILL";
			break;
		case SIGSEGV:
			strSig = "SIGSEGV";
			break;
		case SIGTERM:
			strSig = "SIGTERM";
			break;
	}
	printf("ERROR: SIGNAL %s (%d) caught\n", strSig, sig);
	exit(1);
}

