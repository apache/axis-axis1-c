/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

#include "../platforms/PlatformAutoSense.hpp"

#include "XMLParserFactory.h"
#include "../xml/XMLParser.h"
#include <stdio.h>
#include "../common/AxisConfig.h"
#include "AxisEngineException.h"
#include "../common/AxisTrace.h"
                                                                                                                             
extern AXIS_CPP_NAMESPACE_PREFIX AxisConfig* g_pConfig;

AXIS_CPP_NAMESPACE_START

const char* XMLParserFactory::m_pcLibraryPath = 0;
DLHandler XMLParserFactory::m_LibHandler = 0;
CREATE_OBJECT2 XMLParserFactory::m_Create = 0;
DELETE_OBJECT2 XMLParserFactory::m_Delete = 0;

XMLParserFactory::XMLParserFactory()
{
	m_LibHandler = 0;
}

XMLParserFactory::~XMLParserFactory()
{

}

int XMLParserFactory::initialize()
{
    m_pcLibraryPath = g_pConfig->getAxisConfProperty(AXCONF_XMLPARSER);

	if (!loadLib())
	{
        m_Create = (CREATE_OBJECT2) PLATFORM_GETPROCADDR(m_LibHandler, CREATE_FUNCTION2);
        if (m_Create)
            m_Delete = (DELETE_OBJECT2) PLATFORM_GETPROCADDR(m_LibHandler, DELETE_FUNCTION2);
            
        if (!m_Create || !m_Delete)
        {
            // get load lib error information
            string sFullMessage = "Failed to resolve to XML Parser procedures in library " +  
                                  string(m_pcLibraryPath) + ". " + PLATFORM_LOADLIB_ERROR;
            
            // Unload library - this must be done after obtaining error info above            
            unloadLib();

            throw AxisEngineException(SERVER_ENGINE_LOADING_PARSER_FAILED, sFullMessage.c_str());
        } 
	  else
	  {
#ifdef ENABLE_AXISTRACE
            // Load function to do lib level inits
            INIT_OBJECT2 initializeLibrary;
            initializeLibrary = (INIT_OBJECT2) PLATFORM_GETPROCADDR(m_LibHandler, INIT_FUNCTION2);

            if (initializeLibrary)
                 (*initializeLibrary)(AxisTrace::getTraceEntrypoints());
#endif
	  }
	}
	else
	{
        // dead code - will never be reached, need to remove.
        throw AxisEngineException(SERVER_ENGINE_LOADING_PARSER_FAILED);
	}
   return AXIS_SUCCESS;
}

int XMLParserFactory::uninitialize()
{
#ifdef ENABLE_AXISTRACE
      UNINIT_OBJECT2 uninitializeLibrary;
      uninitializeLibrary = (UNINIT_OBJECT2) PLATFORM_GETPROCADDR(m_LibHandler, UNINIT_FUNCTION2);

      if (uninitializeLibrary)
          (*uninitializeLibrary)();
#endif
	return unloadLib();
}

/**
 * Should create an instance of transport of type given by eProtocol
 */
XMLParser* XMLParserFactory::getParserObject()
{
	XMLParser* pTpt = 0;
	if (m_Create) m_Create(&pTpt);
	return pTpt;
}

void XMLParserFactory::destroyParserObject(XMLParser* pObject)
{
	m_Delete(pObject);
}

int XMLParserFactory::loadLib()
{
    m_LibHandler = PLATFORM_LOADLIB(m_pcLibraryPath);

    if (!m_LibHandler)
    {
        // get load lib error information
        string sFullMessage = "Failed to load XML Parser library " +  
                              string(m_pcLibraryPath) + ". " + PLATFORM_LOADLIB_ERROR;

        throw AxisEngineException(SERVER_ENGINE_LOADING_PARSER_FAILED, sFullMessage.c_str());
    }

    return AXIS_SUCCESS;
}

int XMLParserFactory::unloadLib()
{
    PLATFORM_UNLOADLIB(m_LibHandler);

    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END
