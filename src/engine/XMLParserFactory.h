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
 *
 */


#if !defined(AXIS_XMLPARSERFACTORY_H__OF_AXIS_INCLUDED_)
#define AXIS_XMLPARSERFACTORY_H__OF_AXIS_INCLUDED_

#include "../platforms/PlatformAutoSense.hpp"

#include <axis/GDefine.hpp>
#include "../xml/XMLParser.h"

#define CREATE_FUNCTION2 "CreateInstance"
#define DELETE_FUNCTION2 "DestroyInstance"
#define INIT_FUNCTION2   "initializeLibrary"
#define UNINIT_FUNCTION2 "uninitializeLibrary"

typedef int (* CREATE_OBJECT2) (XMLParser** inst);
typedef int (* DELETE_OBJECT2) (XMLParser* inst);
typedef void (* INIT_OBJECT2) (AxisTraceEntrypoints& ep);
typedef void (* UNINIT_OBJECT2) ();

AXIS_CPP_NAMESPACE_START
class XMLParserFactory  
{
public:
	XMLParserFactory();
	virtual ~XMLParserFactory();
	/**
     * Used to initialize the global object. Following tasks are done
     * 1. Get the parser library name from the configuration file.
     * 2. Load that dynamic parser library.
     * 3. Get the function pointers of the exported functions
     * 4. Get any other information about the library.
     */
	static int initialize();
	/** 
	 * Used to uninitialize the global object.
	 * 1. Unloads dynamic parser library.
	 */
	static int uninitialize();
	/**
	 * Used to create a parser object 
	 */
	static XMLParser* getParserObject();
	/**
	 * Destroys the parser object 
	 */
	static void destroyParserObject(XMLParser* pObject);

	static int loadLib();
	static int unloadLib();

private:
	static const char* m_pcLibraryPath;
	static DLHandler m_LibHandler;
    static CREATE_OBJECT2 m_Create;
    static DELETE_OBJECT2 m_Delete;

};
AXIS_CPP_NAMESPACE_END
#endif 

