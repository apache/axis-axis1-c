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

/**
 * This class 
 *
 * @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */


#if !defined(AXIS_SOAPTRANSPORTFACTORY_H__OF_AXIS_INCLUDED_)
#define AXIS_SOAPTRANSPORTFACTORY_H__OF_AXIS_INCLUDED_

#include <axis/server/GDefine.hpp>

#define CREATE_FUNCTION1 "CreateInstance"
#define DELETE_FUNCTION1 "DestroyInstance"

//function to do lib level init jobs
#define INIT_FUNCTION "initializeLibrary"
//function to do lib level uninit jobs
#define UNINIT_FUNCTION "uninitializeLibrary"

/*
//function to start event loop for transport (libWWW)
#define START_EVENT_LOOP_FUNCTION "startEventLoop"
//function to stop event loop for transport (libWWW)
#define STOP_EVENT_LOOP_FUNCTION "stopEventLoop"
*/

#if defined(USE_LTDL)
#include <ltdl.h>
#define DLHandler lt_dlhandle
#elif defined(WIN32)
#include <windows.h>
#define DLHandler HINSTANCE
#define RTLD_LAZY 0
#else /* Linux */
#include <dlfcn.h>
#define DLHandler void*
#endif

AXIS_CPP_NAMESPACE_START

class SOAPTransport;

typedef int (* CREATE_OBJECT1) (SOAPTransport** inst);
typedef int (* DELETE_OBJECT1) (SOAPTransport* inst);

class SOAPTransportFactory  
{
public:
	SOAPTransportFactory();
	virtual ~SOAPTransportFactory();
	/**
     * Used to initialize the global object. Following tasks are done
     * 1. Get the transport library name(s) from the configuration file.
     * 2. Load those dynamic transport libraries.
     * 3. Get the function pointers of the exported functions
     * 4. Get any other information about the library. (ex: what protocols
     *    are supported etc)
     */
	static int initialize();
	/** 
	 * Used to uninitialize the global object.
	 * 1. Unloads all dynamic transport libraries.
	 */
	static int uninitialize();
	/**
	 * Used to create a transport object of given protocol 
	 */
	static SOAPTransport* getTransportObject(AXIS_PROTOCOL_TYPE eProtocol);
	static void destroyTransportObject(SOAPTransport* pObject);

    //static void startEventLoop();
    //static void stopEventLoop();

	static int loadLib();
	static int unloadLib();

private:
	static const char* m_pcLibraryPath; /* later this should be a list with libraries with thier other information */
	static DLHandler m_LibHandler;
    static CREATE_OBJECT1 m_Create;
    static DELETE_OBJECT1 m_Delete;
   
//    static void (*m_startEventLoop) (void);
//    static void (*m_stopEventLoop) (void);

};

AXIS_CPP_NAMESPACE_END

#endif 

