/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

#include <axis/server/AxisConfig.h>
#include <axis/server/GDefine.h>
#include "AxisUtils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

AxisConfig::AxisConfig()
{
    m_sWsddFilePath = 0;
    m_sAxisLogPath = 0;
	m_sClientWsddFilePath = 0;
    m_sAxisHome = 0;
    m_sValue = NULL;
}

AxisConfig::~AxisConfig()
{
    if(m_sWsddFilePath) delete m_sWsddFilePath;
    if(m_sAxisLogPath) delete m_sAxisLogPath;
	if(m_sClientWsddFilePath) delete m_sClientWsddFilePath;
    if(m_sAxisHome) delete m_sAxisHome;
    if(m_sValue) delete m_sValue;

}

int AxisConfig::ReadConfFile()
{
    FILE* fileConfig = NULL;
    char* sConfPath = NULL;
    char sNewConfPath[CONFBUFFSIZE] = {0};
    //char key[CONFBUFFSIZE] = {0};
    char* key;
    //char m_sLine[CONFBUFFSIZE] = {0};
    //char value[CONFBUFFSIZE] = {0};
 

	sConfPath = getenv("AXIS_HOME");
    if (!sConfPath)
        return AXIS_FAIL;
	m_sAxisHome = (char*) malloc(CONFBUFFSIZE);
    strcpy(m_sAxisHome, sConfPath);        
  
	strcpy(sNewConfPath, sConfPath);
    strcat(sNewConfPath, "/axiscpp.conf");
    if ((fileConfig = fopen(sNewConfPath, "r")) == NULL)
		return AXIS_FAIL;

    while(fgets(m_sLine, CONFBUFFSIZE, fileConfig) != NULL)
    {
        int linesize = strlen(m_sLine);
        m_sValue = strpbrk(m_sLine, ":");
        if(!m_sValue) break;
        key = (char*) malloc(strlen(m_sValue));
        m_sValue[0] = '\0';
        sscanf(m_sLine,"%s", key);

        if(strcmp(key, "WSDDFILEPATH") == 0)
        {
			m_sWsddFilePath = (char*) malloc(CONFBUFFSIZE);
            strncpy(m_sWsddFilePath, m_sValue + 1, linesize  - strlen(key) - 2);
            m_sWsddFilePath[linesize  - strlen(key) - 2] = '\0';
        }
        if(strcmp(key, "AXISLOGPATH") == 0)
        {
			m_sAxisLogPath = (char*) malloc(CONFBUFFSIZE);
            strncpy(m_sAxisLogPath, m_sValue + 1, linesize  - strlen(key) - 2);
            m_sAxisLogPath[linesize  - strlen(key) - 2] = '\0';
        }
		if(strcmp(key, "CLIENTWSDDFILEPATH") == 0)
        {
			m_sClientWsddFilePath = (char*) malloc(CONFBUFFSIZE);
            strncpy(m_sClientWsddFilePath, m_sValue + 1, linesize  - strlen(key) - 2);
            m_sClientWsddFilePath[linesize  - strlen(key) - 2] = '\0';
        }
    }


    return AXIS_SUCCESS;
}

char* AxisConfig::GetWsddFilePath()
{
    return m_sWsddFilePath;
}

char* AxisConfig::GetAxisLogPath()
{
    return m_sAxisLogPath;
}


char* AxisConfig::GetClientWsddFilePath()
{
    return m_sClientWsddFilePath;
}

char* AxisConfig::GetAxisHomePath()
{
        return m_sAxisHome;
}

/*int main(void)
{
    AxisConfig* objConfig = new AxisConfig();
    objConfig->ReadConfFile();
    char* pWsddPath = objConfig->GetWsddFilePath();
    printf("pWsddPath:%s\n", pWsddPath);
    char* LogPath = objConfig->GetAxisLogPath();

}
*/
