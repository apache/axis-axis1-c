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
    char* sConfPath = NULL;
    char sNewConfPath[CONFBUFFSIZE] = {0};
    char line[CONFBUFFSIZE] = {0};
    char key[CONFBUFFSIZE] = {0};
    char value[CONFBUFFSIZE] = {0};

	sConfPath = getenv("AXIS_HOME");
	if (!sConfPath) return FAIL;
	strcpy(sNewConfPath, sConfPath);
    strcat(sNewConfPath, "/axiscpp.conf");
    if ((fileConfig = fopen(sNewConfPath, "rt")) == NULL)
		return FAIL;

    while(fgets(line, CONFBUFFSIZE, fileConfig) != NULL)
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