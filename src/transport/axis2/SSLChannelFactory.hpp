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
 * @author damitha kumarage (damitha@hsenid.lk, damitha@opensource.lk)
 *
 */


#if !defined(AXIS_SSLCHANNELFACTORY_H__OF_AXIS_INCLUDED_)
#define AXIS_SSLCHANNELFACTORY_H__OF_AXIS_INCLUDED_

#include "../../platforms/PlatformAutoSense.hpp"

#include <axis/GDefine.hpp>
#include "../SSLChannel.hpp"

#define CREATE_FUNCTION3 "CreateInstance"
#define DELETE_FUNCTION3 "DestroyInstance"

typedef int (* CREATE_OBJECT3) (SSLChannel** inst);
typedef int (* DELETE_OBJECT3) (SSLChannel* inst);
AXIS_CPP_NAMESPACE_START
class SSLChannelFactory  
{
public:
	SSLChannelFactory();
	virtual ~SSLChannelFactory();
	/**
     * Used to initialize the global object. Following tasks are done
     * 1. Get the parser library name from the configuration file.
     * 2. Load that dynamic parser library.
     * 3. Get the function pointers of the exported functions
     * 4. Get any other information about the library.
     */
	static int initialize(const char* pcLibraryName);
	/** 
	 * Used to uninitialize the global object.
	 * 1. Unloads dynamic parser library.
	 */
	static int uninitialize();
	/**
	 * Used to create a parser object 
	 */
	static SSLChannel* getSSLChannelObject();
	/**
	 * Destroys the parser object 
	 */
	static void destroySSLChannelObject(SSLChannel* pObject);

	static int loadLib();
	static int unloadLib();

private:
	static const char* m_pcLibraryName;
	static DLHandler m_LibHandler;
    static CREATE_OBJECT3 m_Create;
    static DELETE_OBJECT3 m_Delete;

};
AXIS_CPP_NAMESPACE_END
#endif 

