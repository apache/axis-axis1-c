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
#include "../../common/Packet.h"
#include <new>
#include <exception>

#if defined (_DEBUG)
	#include <iostream>
	#define Trace(x)	std::cout << x << std::endl;
#else
	#define Trace(x)
#endif



JNIEXPORT void JNICALL Java_AxisCppContentHandler_processContent
  (JNIEnv *p_Env, 
   jclass, 
   jbyteArray p_jBody, 
   jint p_nBodySize, 
   jobject p_jvHeaders, 
   jint p_nHeaderCount)
{
	//TODO: populate soapstream with the headers & the body;
	// invoke to process the contents
	HTTP_PACKET* pHttpPkt = new HTTP_PACKET;
	pHttpPkt->pchContent = new char[p_nBodySize+1];
	
	p_Env->GetByteArrayRegion(p_jBody, 0, p_nBodySize, (jbyte*)pHttpPkt->pchContent);

	Trace(pHttpPkt->pchContent);
	
	pHttpPkt->nContentLen = p_nBodySize;
	//set method name as a http header.
	pHttpPkt->pHeaders    = new HTTP_HEADER[p_nHeaderCount];

	JNIVector jvHeader(p_Env, p_jvHeaders);
	for(int i=0;i < p_nHeaderCount; i++)
	{
		pHttpPkt->pHeaders[i].name  = jvHeader[i*2];
		pHttpPkt->pHeaders[i].value = jvHeader[i*2+1];
		Trace(pHttpPkt->pHeaders[i].name );
		Trace(pHttpPkt->pHeaders[i].value);
	}
	pHttpPkt->nHeaderCount = p_nHeaderCount;
	pHttpPkt->enMethod = POST;

	jvHeader.clear();
	jvHeader.push_back("Name_p1"); // Name_p1
	jvHeader.push_back("Value_p1");
	jvHeader.push_back("Name_p2");
	jvHeader.push_back("Value_p2");

	delete [] pHttpPkt->pchContent;
	p_jBody = p_Env->NewByteArray(strlen(pHttpPkt->pchContent)+1);
	p_Env->SetByteArrayRegion(p_jBody, 0, strlen(pHttpPkt->pchContent), 
								(jbyte*)pHttpPkt->pchContent);

	delete [] pHttpPkt->pHeaders;
	delete [] pHttpPkt->pchContent;
	delete pHttpPkt;
}


JNIVector::JNIVector(JNIEnv* p_Env, jobject p_jVector)
        : m_pEnv(p_Env), m_jVector(p_jVector)
{
	jclass clazz = p_Env->FindClass("java/util/Vector");
	JNI_ASSERT(clazz != NULL, "java/lang/NoClassDefFoundError", "java.util.Vector");

	JNI_ASSERT(p_Env->IsInstanceOf(p_jVector, clazz),
					 "java/lang/IllegalArgumentException",
					 "p_jVector not a java.util.Vector object!");

	m_jmGet = p_Env->GetMethodID(clazz, "get", "(I)Ljava/lang/Object;");

	JNI_ASSERT(m_jmGet != NULL,
                 "java/lang/NoSuchMethodError",
                 "method 'public Object get(int index)' not found!");

	m_jmAdd = p_Env->GetMethodID(clazz, "addElement", "(Ljava/lang/Object;)V");

	JNI_ASSERT(m_jmGet != NULL,
                 "java/lang/NoSuchMethodError",
                 "method 'public void addElement(Object obj)' not found!");

	m_jmClear = p_Env->GetMethodID(clazz, "clear", "()V");

	JNI_ASSERT(m_jmGet != NULL,
                 "java/lang/NoSuchMethodError",
                 "method 'public void clear()' not found!");

}
	///Destructor
JNIVector::~JNIVector()
{

}

char* JNIVector::operator [] (int i) const
{
	jboolean isCopy;
	jobject obj = m_pEnv->CallObjectMethod(m_jVector, m_jmGet, i);
	jstring str = (jstring) obj;
	const char *pch = m_pEnv->GetStringUTFChars(str, &isCopy);
	if (m_pEnv->ExceptionOccurred())
        throw std::bad_alloc();
    return (char*)pch;
}

void JNIVector::push_back(const char* str) 
{
	m_pEnv->CallVoidMethod(m_jVector, m_jmAdd, m_pEnv->NewStringUTF(str));
	if (m_pEnv->ExceptionOccurred())
		throw std::bad_exception("can't push_back"); //need to set up a exception
}

void JNIVector::clear()
{
	m_pEnv->CallVoidMethod(m_jVector, m_jmClear);
	if (m_pEnv->ExceptionOccurred())
		throw std::bad_exception("Can't clear the vector"); //need to set up a exception
}


/*
JNIString::JNIString(JNIEnv* p_Env, jstring p_jStr) throw(std::bad_alloc)
        : m_pEnv(p_Env), m_jStr(p_jStr)
{
    m_pch = (m_jStr == NULL)? NULL : m_pEnv->GetStringUTFChars(m_jStr, NULL);
    if (m_pEnv->ExceptionOccurred())
        throw std::bad_alloc();
}

JNIString::~JNIString()
{
    if (m_pch != NULL)
        m_pEnv->ReleaseStringUTFChars(m_jStr, m_pch);
}

JNIString::operator const char* () const
{
    return m_pch;
}

JNIString& JNIString::operator = (const char* p_pch)
{
	if (m_pch != NULL)
        m_pEnv->ReleaseStringUTFChars(m_jStr, m_pch);

	m_pch = p_pch;
	m_pch = (m_jStr == NULL)? NULL : m_pEnv->GetStringUTFChars(m_jStr, NULL);
    if (m_pEnv->ExceptionOccurred())
        throw std::bad_alloc();
	return *this;
}

jstring JNIString::getJNIString()
{
	return m_pEnv->NewStringUTF(m_pch);
}
*/


JNIEXPORT jint JNICALL
JNI_OnLoad( JavaVM *jvm, void *reserved )
{
    return JNI_VERSION_1_2;
}


JNIEXPORT void JNICALL
JNI_OnUnload( JavaVM *jvm, void *reserved )
{
}


