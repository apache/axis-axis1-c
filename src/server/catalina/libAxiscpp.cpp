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

#define MIN(X,Y) (((X)<(Y))?(X):(Y))

/* Inaccessible static: DEBUG */
/*
 * Class:     AxisCppContentHandler
 * Method:    processContent
 * Signature: (Ljava/io/InputStream;Ljava/util/Vector;Ljava/io/OutputStream;)V
 */
JNIEXPORT void JNICALL Java_AxisCppContentHandler_processContent
  (JNIEnv * p_Env, jclass, 
  jobject p_jBodyReader, 
  jobject p_jvHeaders, 
  jobject p_jBodyWriter,
  jint	  p_jnContentLength)
{
	//TODO: populate soapstream with the headers & the body;
	// invoke to process the contents
	HTTP_PACKET* pHttpPkt = new HTTP_PACKET;
	pHttpPkt->pchContent = new char[p_jnContentLength+1];
	
	JNIInputStream inputBody(p_Env,p_jBodyReader);
	JNIOutputStream outputBody(p_Env,p_jBodyWriter);
	std::istream in(&inputBody);
    std::ostream out(&outputBody);

	in.read(pHttpPkt->pchContent, p_jnContentLength);
	pHttpPkt->pchContent[p_jnContentLength] = '\0';
	Trace(pHttpPkt->pchContent);
	
	pHttpPkt->nContentLen = p_jnContentLength;
	
	JNIVector jvHeader(p_Env, p_jvHeaders);
	//set method name as a http header.
	const int p_nHeaderCount = jvHeader.size()/2;
	pHttpPkt->pHeaders    = new HTTP_HEADER[p_nHeaderCount];

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
	const char *p = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
	p_jnContentLength = strlen(p);
	pHttpPkt->pchContent = new char[1+p_jnContentLength];
	strcpy(pHttpPkt->pchContent, p);

	out << pHttpPkt->pchContent << std::flush;

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

	m_jmSize = p_Env->GetMethodID(clazz, "size", "()I");
	JNI_ASSERT(m_jmGet != NULL,
                 "java/lang/NoSuchMethodError",
                 "method 'public void size()' not found!");

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

int JNIVector::size()
{
	int size = m_pEnv->CallIntMethod(m_jVector, m_jmSize);
	if (m_pEnv->ExceptionOccurred())
		throw std::bad_exception("Don't know the vector size"); //need to set up a exception
	return size;
}


JNIOutputStream::JNIOutputStream(JNIEnv* p_pEnv,
                                       jobject stream,
                                       unsigned bufsize)
    : std::strstreambuf(bufsize),
      m_pEnv(p_pEnv),
      _output(stream),
      _write(NULL),
      _flush(NULL),
      _bufsize(bufsize),
      _jbuf(NULL)
{
    jclass clazz = m_pEnv->FindClass("java/io/OutputStream");
    JNI_ASSERT(clazz != NULL,
                     "java/lang/NoClassDefFoundError",
                     "java.io.OutputStream");

    JNI_ASSERT(m_pEnv->IsInstanceOf(stream, clazz),
                     "java/lang/IllegalArgumentException",
                     "stream not a java.io.OutputStream object!");

    _write = m_pEnv->GetMethodID(clazz,
                               "write",
                               "([BII)V"); // void write(byte[], int, int)
    JNI_ASSERT(_write != NULL,
                     "java/lang/NoSuchMethodError",
                     "method 'void java.io.OutputStream.write(byte[], int, int)' not found!");
    
    _flush = m_pEnv->GetMethodID(clazz,
                               "flush",
                               "()V"); // void flush()
    JNI_ASSERT(_flush != NULL,
                     "java/lang/NoSuchMethodError",
                     "method 'void java.io.OutputStream.flush()' not found!");
    
    _jbuf = m_pEnv->NewByteArray(_bufsize);
    JNI_ASSERT(_jbuf != NULL,
                     "java/lang/OutOfMemoryError",
                     "");
}

JNIOutputStream::~JNIOutputStream()
{
    m_pEnv->DeleteLocalRef(_jbuf);
}

int
JNIOutputStream::overflow(int c)
{
    // WIN32 has a bug in nested scope resolution - it can't
    // handle std::strstreambuf::overflow - so we pull in the
    // std namespace here.
    using namespace std;

    if (m_pEnv->ExceptionOccurred())
        return EOF;
    
    unsigned count = pcount();
    for (unsigned start = 0, n;
         count > 0;
         count -= n, start += n)
    {
		n = MIN(count, _bufsize);
        
        m_pEnv->SetByteArrayRegion(_jbuf, 0, n, (jbyte*)pbase() + start);
        if (m_pEnv->ExceptionOccurred())
            return EOF;
        
        m_pEnv->CallVoidMethod(_output, _write, _jbuf, 0, n);
        if (m_pEnv->ExceptionOccurred())
            return EOF;
    }
    
    setp(pbase(), epptr()); // (put) buffer is empty
    
    return strstreambuf::overflow(c);
}

int
JNIOutputStream::sync()
{
    if (m_pEnv->ExceptionOccurred())
        return EOF;
    
    overflow(EOF); // empty buffer...

    if (_output)
    {
        m_pEnv->CallVoidMethod(_output, _flush);
        if (m_pEnv->ExceptionOccurred())
            return EOF;
    }
    
    return 0;
}

JNIInputStream::JNIInputStream(JNIEnv* env,
                                     jobject stream,
                                     unsigned bufsize)
    : std::strstreambuf(_buf = new char[bufsize], bufsize),
      m_pEnv(env),
      _input(stream),
      _read(NULL),
      _close(NULL),
      _bufsize(bufsize),
      _jbuf(NULL)
{
    jclass clazz = m_pEnv->FindClass("java/io/InputStream");
    JNI_ASSERT(clazz != NULL,
                     "java/lang/NoClassDefFoundError",
                     "java.io.InputStream");
    
    JNI_ASSERT(m_pEnv->IsInstanceOf(stream, clazz),
                     "java/lang/IllegalArgumentException",
                     "stream not a java.io.InputStream object!");

    _read = m_pEnv->GetMethodID(clazz,
                              "read",
                              "([BII)I"); // int read(byte[], int, int)
    JNI_ASSERT(_read != NULL,
                     "java/lang/NoSuchMethodError",
                     "method 'int java.io.InputStream.read(byte[], int, int)' not found!");
    
    _close = m_pEnv->GetMethodID(clazz,
                               "close",
                               "()V"); // void close()
    JNI_ASSERT(_read != NULL,
                     "java/lang/NoSuchMethodError",
                     "method 'int java.io.InputStream.read(byte[], int, int)' not found!");

    _available = m_pEnv->GetMethodID(clazz,
				   "available",
				   "()I"); // int available()
    JNI_ASSERT(_available != NULL,
                     "java/lang/NoSuchMethodError",
                     "method 'int java.io.InputStream.available()' not found!");
	
    _jbuf = m_pEnv->NewByteArray(_bufsize);
    JNI_ASSERT(_jbuf != NULL,
                     "java/lang/OutOfMemoryError",
                     "");

    setg(eback(), egptr(), egptr()); // (get) buffer is empty


}

JNIInputStream::~JNIInputStream()
{
    delete[] _buf;
    m_pEnv->DeleteLocalRef(_jbuf);

    m_pEnv->CallVoidMethod(_input, _close);        
}

int
JNIInputStream::available()
{
    int n = m_pEnv->CallIntMethod(_input,_available);
    if (m_pEnv->ExceptionOccurred())
    {
        return EOF;
    }

    return n;
}

int
JNIInputStream::underflow()
{
    // WIN32 has a bug in nested scope resolution - it can't
    // handle std::strstreambuf::overflow - so we pull in the
    // std namespace here.
    using namespace std;

    if (m_pEnv->ExceptionOccurred())
        return EOF;
    
    int n = m_pEnv->CallIntMethod(_input, _read, _jbuf, 0, _bufsize);
    if (m_pEnv->ExceptionOccurred() || n == -1)
        return EOF;
    
    setg(eback(), egptr() - n, egptr()); // (get) buffer has n chars

    m_pEnv->GetByteArrayRegion(_jbuf, 0, n, (jbyte*)gptr());
    if (m_pEnv->ExceptionOccurred())
        return EOF;

    return strstreambuf::underflow();
}


JNIEXPORT jint JNICALL
JNI_OnLoad( JavaVM *jvm, void *reserved )
{
    return JNI_VERSION_1_2;
}


JNIEXPORT void JNICALL
JNI_OnUnload( JavaVM *jvm, void *reserved )
{
}


