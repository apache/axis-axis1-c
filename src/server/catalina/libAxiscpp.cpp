/* -*- C++ -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/*
 *
 * @author Lilantha Darshana (lilantha@virtusa.com)
 *
 */

#include "libAxiscpp.h"
#include "Packet.h"
#include "Axis.hpp"
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
    (JNIEnv* p_Env, jclass, jobject p_jBodyReader, jobject p_jvHeaders, 
    jobject p_jBodyWriter, jint p_jnContentLength)
{
    // TODO: populate soapstream with the headers & the body;
    // invoke to process the contents
    axstream *paxstream = new axstream;

    JNIInputStream inputBody (p_Env, p_jBodyReader);
    JNIOutputStream outputBody (p_Env, p_jBodyWriter);
    paxstream->m_pInputContent = new std::istream (&inputBody);
    paxstream->m_pOutputContent = new std::ostream (&outputBody);

    paxstream->m_nContentLen = p_jnContentLength;

    JNIVector jvHeader (p_Env, p_jvHeaders);
    // set method name as a http header.
    int nHeaderCount = jvHeader.size () / 2;
    paxstream->m_pHeaders = new axstream::PROT_HEADER[nHeaderCount];

    for (int i = 0; i < nHeaderCount; i++)
    {
        paxstream->m_pHeaders[i].pchName = jvHeader[i * 2];
        paxstream->m_pHeaders[i].pchValue = jvHeader[i * 2 + 1];
        Trace (paxstream->m_pHeaders[i].pchName);
        Trace (paxstream->m_pHeaders[i].pchValue);
    }
    paxstream->m_nHeaderCount = nHeaderCount;

    paxstream->m_enProtocolType = axstream::HTTP;
    paxstream->m_pExtendedInfo = new axstream::EXTENDED_INFO;
    paxstream->m_pExtendedInfo->infHttp.enMethod = axstream::HTTP_INFO::POST;

    // just add some sessionid
    paxstream->m_pchSessionId = strdup ("tmp session id");

    AxisContentHandler::Init ();
    if (0 != AxisContentHandler::HandleContent (*paxstream))
    {
        throw "SOAP Engine failed to response";
    }

    jvHeader.clear ();
    nHeaderCount = paxstream->m_nHeaderCount;

    for (int j = 0; j < nHeaderCount; j++)
    {
        jvHeader.push_back (paxstream->m_pHeaders[j].pchName);
        jvHeader.push_back (paxstream->m_pHeaders[j].pchValue);
        Trace (paxstream->m_pHeaders[j].pchName);
        Trace (paxstream->m_pHeaders[j].pchValue);
    }

    *paxstream->m_pOutputContent << std::flush;

    delete paxstream;
}


JNIVector::JNIVector (JNIEnv* p_Env, jobject p_jVector):m_pEnv (p_Env),
m_jVector (p_jVector)
{
    jclass clazz = p_Env->FindClass ("java/util/Vector");
    JNI_ASSERT (clazz != NULL, "java/lang/NoClassDefFoundError",
        "java.util.Vector");

    JNI_ASSERT (p_Env->IsInstanceOf (p_jVector, clazz),
        "java/lang/IllegalArgumentException",
        "p_jVector not a java.util.Vector object!");

    m_jmGet = p_Env->GetMethodID (clazz, "get", "(I)Ljava/lang/Object;");

    JNI_ASSERT (m_jmGet != NULL, "java/lang/NoSuchMethodError",
        "method 'public Object get(int index)' not found!");

    m_jmAdd = p_Env->GetMethodID (clazz, "addElement", "(Ljava/lang/Object;)V");

    JNI_ASSERT (m_jmGet != NULL, "java/lang/NoSuchMethodError",
        "method 'public void addElement(Object obj)' not found!");

    m_jmClear = p_Env->GetMethodID (clazz, "clear", "()V");

    JNI_ASSERT (m_jmGet != NULL, "java/lang/NoSuchMethodError",
        "method 'public void clear()' not found!");

    m_jmSize = p_Env->GetMethodID (clazz, "size", "()I");
    JNI_ASSERT (m_jmGet != NULL, "java/lang/NoSuchMethodError",
        "method 'public void size()' not found!");
}


JNIVector::~JNIVector ()
{

}

char* JNIVector::operator [] (int i)
    const
    {
        jboolean isCopy;
        jobject obj = m_pEnv-> CallObjectMethod (m_jVector, m_jmGet, i);
        jstring str = (jstring) obj;
        const char* pch = m_pEnv->GetStringUTFChars (str, &isCopy);
        if (m_pEnv->ExceptionOccurred ())
            throw std::bad_alloc ();
        return (char*)
            pch;
    }

    void JNIVector::push_back (const char* str)
    {
        m_pEnv->CallVoidMethod (m_jVector, m_jmAdd, m_pEnv->NewStringUTF (str));
        if (m_pEnv->ExceptionOccurred ())
            throw std::bad_exception ("can't push_back"); 
	    // need to set up a exception
    }

void JNIVector::clear ()
{
    m_pEnv->CallVoidMethod (m_jVector, m_jmClear);
    if (m_pEnv->ExceptionOccurred ())
        throw std::bad_exception ("Can't clear the vector");    
        // need to set up a exception
}

int JNIVector::size ()
{
    int size = m_pEnv->CallIntMethod (m_jVector, m_jmSize);
    if (m_pEnv->ExceptionOccurred ())
        throw std::bad_exception ("Don't know the vector size");        
        // need to set up a exception
        return size;
}


JNIOutputStream::JNIOutputStream (JNIEnv* p_pEnv, jobject stream, 
    unsigned bufsize):std::strstreambuf (bufsize), m_pEnv (p_pEnv), 
    _output (stream), _write (NULL), _flush (NULL), _bufsize (bufsize), 
    _jbuf (NULL)
{
    jclass clazz = m_pEnv->FindClass ("java/io/OutputStream");
    JNI_ASSERT (clazz != NULL, "java/lang/NoClassDefFoundError", 
        "java.io.OutputStream");

    JNI_ASSERT (m_pEnv->IsInstanceOf (stream, clazz),
        "java/lang/IllegalArgumentException",
        "stream not a java.io.OutputStream object!");

    _write = m_pEnv->GetMethodID (clazz, "write", "([BII)V");   
    // void write(byte[], int, int)
    JNI_ASSERT (_write != NULL, "java/lang/NoSuchMethodError",
       "method 'void java.io.OutputStream.write(byte[], int, int)' not found!");

    _flush = m_pEnv->GetMethodID (clazz, "flush", "()V"); // void flush()
    JNI_ASSERT (_flush != NULL, "java/lang/NoSuchMethodError",
        "method 'void java.io.OutputStream.flush()' not found!");

    _jbuf = m_pEnv->NewByteArray (_bufsize);
    JNI_ASSERT (_jbuf != NULL, "java/lang/OutOfMemoryError", "");
}

JNIOutputStream::~JNIOutputStream ()
{
    m_pEnv->DeleteLocalRef (_jbuf);
}

int JNIOutputStream::overflow (int c)
{
    /* WIN32 has a bug in nested scope resolution - it can't
     * handle std::strstreambuf::overflow - so we pull in the
     * std namespace here.
     */ 
    using namespace std;

    if (m_pEnv->ExceptionOccurred ())
        return EOF;

    unsigned count = pcount ();
    for (unsigned start = 0, n; count > 0; count -= n, start += n)
    {
        n = MIN (count, _bufsize);

        m_pEnv->SetByteArrayRegion (_jbuf, 0, n, (jbyte*) pbase () + start);
        if (m_pEnv->ExceptionOccurred ())
            return EOF;

        m_pEnv->CallVoidMethod (_output, _write, _jbuf, 0, n);
        if (m_pEnv->ExceptionOccurred ())
            return EOF;
    }

    setp (pbase (), epptr ());  // (put) buffer is empty

    return strstreambuf::overflow (c);
}

int JNIOutputStream::sync ()
{
    if (m_pEnv->ExceptionOccurred ())
        return EOF;

    overflow (EOF); // empty buffer...

    if (_output)
    {
        m_pEnv->CallVoidMethod (_output, _flush);
        if (m_pEnv->ExceptionOccurred ())
            return EOF;
    }

    return 0;
}

JNIInputStream::JNIInputStream (JNIEnv* env, jobject stream, 
    unsigned bufsize):std::strstreambuf (_buf = new char[bufsize], bufsize),
    m_pEnv (env), _input (stream), _read (NULL), _close (NULL), 
    _bufsize (bufsize), _jbuf (NULL)
{
    jclass clazz = m_pEnv->FindClass ("java/io/InputStream");
    JNI_ASSERT (clazz != NULL, "java/lang/NoClassDefFoundError", 
        "java.io.InputStream");

    JNI_ASSERT (m_pEnv->IsInstanceOf (stream, clazz), 
        "java/lang/IllegalArgumentException",
        "stream not a java.io.InputStream object!");

    _read = m_pEnv->GetMethodID (clazz, "read", "([BII)I");
    // int read(byte[], int, int)
    JNI_ASSERT (_read != NULL, "java/lang/NoSuchMethodError",
        "method 'int java.io.InputStream.read(byte[], int, int)' not found!");

    _close = m_pEnv->GetMethodID (clazz, "close", "()V"); // void close()
    JNI_ASSERT (_read != NULL, "java/lang/NoSuchMethodError",
        "method 'int java.io.InputStream.read(byte[], int, int)' not found!");

    _available = m_pEnv->GetMethodID (clazz, "available", "()I");
    // int available()
    JNI_ASSERT (_available != NULL, "java/lang/NoSuchMethodError",
        "method 'int java.io.InputStream.available()' not found!");

    _jbuf = m_pEnv->NewByteArray (_bufsize);
    JNI_ASSERT (_jbuf != NULL, "java/lang/OutOfMemoryError", "");

    setg (eback (), egptr (), egptr ()); // (get) buffer is empty
}

JNIInputStream::~JNIInputStream ()
{
    delete[]_buf;
    m_pEnv->DeleteLocalRef (_jbuf);

    m_pEnv->CallVoidMethod (_input, _close);
}

int JNIInputStream::available ()
{
    int n = m_pEnv->CallIntMethod (_input, _available);
    if (m_pEnv->ExceptionOccurred ())
    {
        return EOF;
    }

    return n;
}

int JNIInputStream::underflow ()
{
    /* WIN32 has a bug in nested scope resolution - it can't
     * handle std::strstreambuf::overflow - so we pull in the
     * std namespace here.
     */
    using namespace std;

    if (m_pEnv->ExceptionOccurred ())
        return EOF;

    int n = m_pEnv->CallIntMethod (_input, _read, _jbuf, 0, _bufsize);
    if (m_pEnv->ExceptionOccurred () || n == -1)
        return EOF;

    setg (eback (), egptr () - n, egptr ()); // (get) buffer has n chars

    m_pEnv->GetByteArrayRegion (_jbuf, 0, n, (jbyte*) gptr ());
    if (m_pEnv->ExceptionOccurred ())
        return EOF;

    return strstreambuf::underflow ();
}


JNIEXPORT jint JNICALL JNI_OnLoad (JavaVM* jvm, void* reserved)
{
    return JNI_VERSION_1_2;
}


JNIEXPORT void JNICALL JNI_OnUnload (JavaVM* jvm, void* reserved)
{
}
