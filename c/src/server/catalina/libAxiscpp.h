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


#if !defined(_AXIS_LIBAXISCPP_HPP)
#define _AXIS_LIBAXISCPP_HPP

#include "AxisCppContentHandler.h"
#include <strstream>

#ifdef LIBAXISCPP_EXPORTS
#define LIBAXIS_DLL_API __declspec(dllexport)
#else
#define LIBAXIS_DLL_API __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

    static void jni_throw (JNIEnv* env, const char* exception, const char* msg)
    {
        if (env->ExceptionOccurred ())
            return;
        jclass jexception = env->FindClass (exception);
        if (env->ExceptionOccurred ())
            return;
        if (jexception == NULL)
            env->FatalError (exception);
            env->ThrowNew (jexception, msg);
    }


#ifdef __cplusplus
}
#endif

#define JNI_ASSERT(assert, name, msg) \
    do \
    { \
        if (m_pEnv->ExceptionOccurred()) \
            return; \
        if (! assert) \
        { \
            jni_throw(m_pEnv, name, msg); \
            return; \
        } \
    } while (0)


class JNIVector
{
    public:
        JNIVector (JNIEnv* p_Env, jobject p_jVector);
        ~JNIVector ();

    char* operator [] (int i) const;
    void push_back (const char* str);
    void clear ();
    int size ();

    private:
        JNIEnv* m_pEnv;
        jobject m_jVector;
        jmethodID m_jmGet;
        jmethodID m_jmClear;
        jmethodID m_jmAdd;
        jmethodID m_jmSize;
};

class JNIOutputStream:public std::strstreambuf
{
    public:
        JNIOutputStream (JNIEnv* env, jobject stream, unsigned bufsize = 16300);
        virtual ~ JNIOutputStream ();

    protected:
        virtual int overflow (int c);
        virtual int sync ();

    private:
        JNIEnv * m_pEnv;
        jobject _output;
        jmethodID _write;
        jmethodID _flush;
        unsigned _bufsize;
        jbyteArray _jbuf;
};


class JNIInputStream : public std::strstreambuf
{
    public:
        JNIInputStream (JNIEnv* env, jobject stream, unsigned bufsize = 16300);
        virtual ~ JNIInputStream ();
        int available ();

    protected:
        virtual int underflow ();

    private:
        JNIEnv* m_pEnv;
        jobject _input;
        jmethodID _read;
        jmethodID _close;
        jmethodID _available;
        unsigned _bufsize;
        jbyteArray _jbuf;
        char* _buf;
};

#endif 
