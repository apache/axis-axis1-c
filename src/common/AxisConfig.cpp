#include "AxisConfig.h"
#include "GDefine.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

AxisConfig::AxisConfig()
{
    ReadConfFile();
}

AxisConfig::~AxisConfig()
{
}

int AxisConfig::ReadConfFile()
{
    FILE* fileConfig = NULL;
    FILE* fileConfig2 = NULL;
    char sConfPath[CONFBUFFSIZE] = {0};
    char sNewConfPath[CONFBUFFSIZE] = {0};
    char line[CONFBUFFSIZE] = {0};
    char key[CONFBUFFSIZE] = {0};
    char value[CONFBUFFSIZE] = {0};
    int i=0;
	char* echocmd;
	char* delcmd;
    #ifdef WIN32
		echocmd = "echo %AXIS_HOME% > ./__temp__axis";
		delcmd = "del __temp__axis";
    #else //linux
	    echocmd = "echo $AXIS_HOME>./__temp__axis";
		delcmd = "rm -f __temp__axis";
	#endif
    system(echocmd);
    if ((fileConfig = fopen("__temp__axis", "rb")) == NULL)
        return FAIL;

    else
    {
        fgets(sConfPath, CONFBUFFSIZE, fileConfig);
        while(true)
        {
            sNewConfPath[i] = sConfPath[i];
            i = i + 1;
            if(sConfPath[i] == '\n' || sConfPath[i] == EOF)
            break;
        }

        strcat(sNewConfPath, "/axiscpp.conf");
        system(delcmd);
        if ((fileConfig2 = fopen(sNewConfPath, "rb")) == NULL)
        return FAIL;

        while(fgets(line, CONFBUFFSIZE, fileConfig2) != NULL)
        {
            int k=0;
            while(line[k] != ':')
            {
                key[k]=line[k];
                k += 1;

            }
            k += 1;
            int j=0;
            while(line[k] != '\n')
            {
                value[j]=line[k];
                k += 1;
                j += 1;

            }
            if(strcmp(key, "WSDDFILEPATH") == 0)
                strcpy(m_sWsddFilePath, value);
            if(strcmp(key, "AXISLOGPATH") == 0)
                strcpy(m_sAxisLogPath, value);
        }
        fclose(fileConfig2);

    }
    fclose(fileConfig);
    return SUCCESS;
}

char* AxisConfig::GetWsddFilePath()
{
    return m_sWsddFilePath;
}

char* AxisConfig::GetAxisLogPath()
{
    return m_sAxisLogPath;
}