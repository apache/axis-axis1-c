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
 * @author damitha kumarage (damitha@hsenid.lk, damitha@opensource.lk)
 *
 */

#if !defined(AXIS_CHANNELFACTORY_H__OF_AXIS_INCLUDED_)
#define AXIS_CHANNELFACTORY_H__OF_AXIS_INCLUDED_

#include "../../platforms/PlatformAutoSense.hpp"

#include <axis/GDefine.hpp>
#include "IChannel.hpp"

#define CREATE_FUNCTION3            "CreateInstance"
#define DELETE_FUNCTION3            "DestroyInstance"

typedef int (* CREATE_OBJECT3) (IChannel** inst);
typedef int (* DELETE_OBJECT3) (IChannel* inst);

AXIS_CPP_NAMESPACE_START

class ChannelLibrary
{
public:
    DLHandler m_Library;
    CREATE_OBJECT3 m_Create;
    DELETE_OBJECT3 m_Delete;
};

class ChannelFactory  
{
public:
    ChannelFactory();
    virtual ~ChannelFactory();
    virtual IChannel * LoadChannelLibrary( g_ChannelType eChannelType, const char * pcLibraryName);
    static void preloadChannels(char *unsecChannel, char *secChannel);
    static void unloadChannels();
    virtual IChannel *createChannel(g_ChannelType eChannelType);

private:
    static void preloadChannel(g_ChannelType eChannelType, const char *pcLibraryName);
    virtual bool UnLoadChannelLibrary( g_ChannelType eChannelType);

    char *                    m_pLibName[(int) MaxChannelCount];
    DLHandler                 m_LibHandler[(int) MaxChannelCount];
    IChannel *                m_pChannel[(int) MaxChannelCount];
    static ChannelLibrary    *m_ChannelLibrary[(int) MaxChannelCount];
};
AXIS_CPP_NAMESPACE_END
#endif 

