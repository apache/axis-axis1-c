/* -*- C++ -*- */

/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
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
 */

/*
 *
 *
 * @author Lilantha Darshana (lilantha@virtusa.com)
 *
 */

#include "libAxiscpp.h"
#include "AxisCppContentHandler.h"
#include "../../common/Packet.h"
#include <new>


static void
jni_throw(JNIEnv* env, const char* exception, const char* msg)
{
    if (env->ExceptionOccurred())
        return;
    jclass jexception = env->FindClass(exception);
    if (env->ExceptionOccurred())
      return;
    if (jexception == NULL)
        env->FatalError(exception);
    env->ThrowNew(jexception, msg);
}


#define JNI_ASSERT(assert, name, msg) \
    do \
    { \
        if (p_Env->ExceptionOccurred()) \
            return; \
        if (! assert) \
        { \
            jni_throw(p_Env, name, msg); \
            return; \
        } \
    } while (0)


class JNIVector
{
public:
    JNIVector(JNIEnv* p_Env, jobject p_jVector)
        : m_pEnv(p_Env), m_jVector(p_jVector)
    {
		jclass clazz = p_Env->FindClass("java/util/Vector");
		JNI_ASSERT(clazz != NULL, "java/lang/NoClassDefFoundError", "java.util.Vector");
    
		JNI_ASSERT(p_Env->IsInstanceOf(p_jVector, clazz),
						 "java/lang/IllegalArgumentException",
						 "p_jVector not a java.util.Vector object!");

		m_jmGet = p_Env->GetMethodID(clazz, "get", "(I)Ljava/lang/Object");

		JNI_ASSERT(m_jmGet != NULL,
                     "java/lang/NoSuchMethodError",
                     "method 'public Object get(int index)' not found!");
    }
	///Destructor
    ~JNIVector()
    {

    }

    char* operator [] (int i) const
    {
		jboolean isCopy;
		jobject obj = m_pEnv->CallObjectMethod(m_jVector, m_jmGet, i);
		jstring str = (jstring) obj;
		const char *pch = m_pEnv->GetStringUTFChars(str, &isCopy);
		if (m_pEnv->ExceptionOccurred())
            throw std::bad_alloc();
        return (char*)pch;
    }

	void push_back(const char* str) 
	{
	
	}

private:

    JNIEnv* m_pEnv;
    jobject m_jVector;
	jmethodID m_jmGet;
};

JNIEXPORT void JNICALL Java_AxisCppContentHandler_Delegate
  (JNIEnv *p_Env, jclass, jcharArray p_jBody, jint p_nBodySize, jobject p_jvHeaders, 
  jint p_nHeaderCount)
{
	//TODO: populate soapstream with the headers & the body;
	// invoke to process the contents
	soapstream* str = new soapstream;
	str->trtype = APTHTTP;
	str->so.http.ip_soap = new char[p_nBodySize*sizeof(jchar)];
	p_Env->GetCharArrayRegion(p_jBody, 0, p_nBodySize, (jchar*)str->so.http.ip_soap);
	str->so.http.ip_soapcount = p_nBodySize;
	//set method name as a http header.
	str->so.http.ip_headers = new header[p_nHeaderCount*2];

	JNIVector jvHeader(p_Env, p_jvHeaders);
	for(int i=0;i < p_nHeaderCount; i++)
	{
		str->so.http.ip_headers[i].headername  = jvHeader[i];
		str->so.http.ip_headers[i].headervalue = jvHeader[i+1];
	}
	str->so.http.ip_headercount = p_nHeaderCount;


	delete [] str->so.http.ip_headers;
	delete str;
}



