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
 *
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

/**
 * @file WSDDDefines.hpp
 */

#if !defined(__WSDD_DEFINES_H__OF_AXIS_INCLUDEDED__)
#define __WSDD_DEFINES_H__OF_AXIS_INCLUDEDED__

AXIS_CPP_NAMESPACE_START

/**
 * @enum PROVIDERTYPE
 * 
 * Enumeration of provider types
 */
typedef enum  
{
    /**
     * Unknown or unable to determine provider type
     */
    UNKNOWN_PROVIDER=0,
    
    /**
     * RPC style C provider
     */
    C_RPC_PROVIDER,
    
    /**
     * Doc style C provider
     */
    C_DOC_PROVIDER,
    
    /**
     * RPC style C++ provider
     */
    CPP_RPC_PROVIDER,
    
    /**
     * Doc style C++ provider
     */
    CPP_DOC_PROVIDER,
    
    /**
     * 
     */
    COM_PROVIDER
} PROVIDERTYPE;

AXIS_CPP_NAMESPACE_END
#endif

