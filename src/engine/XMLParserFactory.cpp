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

#include "../platforms/PlatformAutoSense.hpp"

#include "XMLParserFactory.h"
#include "../xml/XMLParser.h"
#include <stdio.h>
#include "../common/AxisConfig.h"
#include "AxisEngineException.h"
#include "../common/AxisTrace.h"
                                                                                                                             
extern AXIS_CPP_NAMESPACE_PREFIX AxisTrace* g_pAT;
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
        m_Delete = (DELETE_OBJECT2) PLATFORM_GETPROCADDR(m_LibHandler, DELETE_FUNCTION2);
        if (!m_Create || !m_Delete)
        {
            unloadLib();
            AXISTRACE1("SERVER_ENGINE_LOADING_PARSER_FAILED" , CRITICAL);
            char *s = new char[strlen(m_pcLibraryPath)+1];
            strcpy(s,m_pcLibraryPath);
            throw AxisEngineException(SERVER_ENGINE_LOADING_PARSER_FAILED, s);
        }
	}
	else
	{
        AXISTRACE1("SERVER_ENGINE_LOADING_PARSER_FAILED" , CRITICAL);
        char *s = new char[strlen(m_pcLibraryPath)+1];
        strcpy(s,m_pcLibraryPath);
        throw AxisEngineException(SERVER_ENGINE_LOADING_PARSER_FAILED, s);
	}
   return AXIS_SUCCESS;
}

int XMLParserFactory::uninitialize()
{
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
        AXISTRACE1("SERVER_ENGINE_LOADING_PARSER_FAILED" , CRITICAL);
        throw AxisEngineException(SERVER_ENGINE_LOADING_PARSER_FAILED);
    }

    return AXIS_SUCCESS;
}

int XMLParserFactory::unloadLib()
{
    PLATFORM_UNLOADLIB(m_LibHandler);

    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END
