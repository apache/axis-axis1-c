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
 */
 
#if !defined(__AXIS_AXISCONFIG_H_INCLUDED__)
#define __AXIS_AXISCONFIG_H_INCLUDED__

#define CONFBUFFSIZE 256

/**
    @class AxisConfig
    @brief class for taking configuration parameters.
    
    The purpose of this class is to provide a way so that
    the server takes the configuration path where the
    axiscpp.conf lies from the environment variable AXIS_HOME.
    User has to set this variable pointing the path to axiscpp.conf file.
    This axiscpp.conf file contains all the configuration paths
    like wsdd configuration file path, axis log path etc.

    @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
*/
class AxisConfig
{
    public:
        AxisConfig();
        ~AxisConfig();
        /**
	     * This is called to get the server.wsdd file path.
         * 
	     * @return the server.wsdd file path 
	     */
        char* GetWsddFilePath();
        /**
	     * This is called to get the AxisLog file path.
         *
	     * @return the AxisLog file path.
	     */
        char* GetAxisLogPath();

        /**
	     * This method will read from the configuration file called axiscpp.conf
         * which is located in a place defined by AXIS_HOME environment variable. 
	 
	     * @return The status which indicates whether the operation is success (AXIS_SUCCESS) or not (AXIS_FAIL).
	     */
        int ReadConfFile();

		char* GetAxisHomePath();
        
    private:		 
        //char m_WsddFilePath[CONFBUFFSIZE];
        //char m_AxisLogPath[CONFBUFFSIZE];
        //char m_sWsddFilePath[CONFBUFFSIZE];
        //char m_sAxisLogPath[CONFBUFFSIZE];
		char* m_sAxisHome;
        char* m_sWsddFilePath;
        char* m_sAxisLogPath;
        char* m_sValue;
        char m_sLine[CONFBUFFSIZE];
};
#endif
