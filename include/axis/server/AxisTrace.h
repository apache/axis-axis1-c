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

#ifndef __AXISLOG_H_INCLUDED_
#define __AXISLOG_H_INCLUDED_

#include "GDefine.h"
#include <list>
#include <string>
#include <stdio.h>

#define __AXISTRACE__
#if defined(__AXISTRACE__)
  #define AXISTRACE1(X) tracer.trace(X,__FILE__,__LINE__);
  #define AXISTRACE2(X,Y) tracer.trace(X,Y,__FILE__,__LINE__);
  #define AXISTRACE3(X) tracer.trace(X);
#endif
#if !defined(__AXISTRACE__)
  #define AXISTRACE1(X) "";
  #define AXISTRACE2(X,Y) "";
  #define AXISTRACE3(X) "";
#endif

//extern unsigned char chEBuf[1024];
using namespace std;
/**
This is class is used to log messages when AXISTRACE is defined.
*/
class AxisTrace
{
public:
    AxisTrace();
	virtual ~AxisTrace();
    int trace(const char* sLog, char* arg2, int arg3);
    int trace(const char* sLog1, const char* sLog2, char* arg3, int arg4);
	/**
	 * Writes the given string to the standard console.
	 * @param pchLog The given string which will be printed to the standard console.
	 * @return The status which indicates whether the operation is success (SUCCESS) or not (FAIL).
	 */
	int trace(const char* pchLog);
    int GetConfPath();
  
private:
    char strLine[4];
    char* m_sFileName;
    FILE* fileTrace;
    FILE* ConfFile; 

};

static AxisTrace tracer;

#endif
