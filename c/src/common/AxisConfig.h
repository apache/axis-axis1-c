#ifdef WIN32
#ifdef AXIS_APACHE1_3
#define WSDDFILEPATH "C:/Program Files/Apache Group/Apache/Axis/conf/server.wsdd"
#else
#define WSDDFILEPATH "e:/Axis/server.wsdd"
#endif
#else //For linux
#ifdef AXIS_APACHE1_3
#define WSDDFILEPATH "/usr/local/apache/Axis/conf/server.wsdd"
#else
#define WSDDFILEPATH "/usr/local/apache/Axis/conf/server.wsdd"
#endif
#endif