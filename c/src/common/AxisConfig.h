#if !defined(__AXIS_AXISCONFIG_H_INCLUDED__)
#define __AXIS_AXISCONFIG_H_INCLUDED__


#ifdef WIN32
#ifdef AXIS_APACHE1_3
#define WSDDFILEPATH "./Axis/conf/server.wsdd"
#else
#define WSDDFILEPATH "C:/Axis/conf/server.wsdd"
#endif
#else //For linux
#ifdef AXIS_APACHE1_3
#define WSDDFILEPATH "/usr/local/apache/Axis/conf/server.wsdd"
#else
#define WSDDFILEPATH "/usr/local/apache/Axis/conf/server.wsdd"
#endif
#endif

#endif