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

#include <axis/common/AxisConfig.h>
#include <axis/common/GDefine.h>
#include <axis/common/AxisUtils.h>
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
	if (!sConfPath) return AXIS_FAIL;
	strcpy(sNewConfPath, sConfPath);
    strcat(sNewConfPath, "/axiscpp.conf");
    if ((fileConfig = fopen(sNewConfPath, "rt")) == NULL)
		return AXIS_FAIL;

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
		
		/*
		 *To clear the character array named value
		 */
		AxisUtils::clearArray(value, CONFBUFFSIZE);

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
