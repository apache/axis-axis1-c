#if !defined(__AXIS_AXISCONFIG_H_INCLUDED__)
#define __AXIS_AXISCONFIG_H_INCLUDED__

#define CONFBUFFSIZE 200

/*
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
*/

class AxisConfig
{
    public:
        AxisConfig();
        ~AxisConfig();
        char* GetWsddFilePath();
        char* GetAxisLogPath();
        
    private:
        bool ReadConfFile();
        char m_WsddFilePath[CONFBUFFSIZE];
        char m_AxisLogPath[CONFBUFFSIZE];
        char m_sWsddFilePath[CONFBUFFSIZE];
        char m_sAxisLogPath[CONFBUFFSIZE];
};
#endif