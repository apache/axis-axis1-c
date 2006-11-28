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

// !!! This include file must be first thing in file !!!
#include "../../platforms/PlatformAutoSense.hpp"

#include <stdio.h>

#include "ChannelFactory.hpp"
#include "HTTPTransportException.hpp"
#include "../../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START

#define MAXCHANNELS (int)MaxChannelCount
ChannelLibrary *ChannelFactory::m_ChannelLibrary[MAXCHANNELS] = {NULL,NULL};

ChannelFactory::
ChannelFactory()
{
    for( int iCount = 0; iCount < (int) MaxChannelCount; iCount++)
    {
        m_pLibName[iCount] = NULL;
        m_LibHandler[iCount] = NULL;
        m_pChannel[iCount] = NULL;
    }
}

ChannelFactory::
~ChannelFactory()
{
    for( int eChannelType = 0; eChannelType < (int) MaxChannelCount; eChannelType++)
    {
        UnLoadChannelLibrary( (g_ChannelType) eChannelType);
    }
}

IChannel * ChannelFactory::
LoadChannelLibrary( g_ChannelType eChannelType, const char * pcLibraryName)
{
    DLHandler    sLibHandler;
    IChannel *    pChannel = NULL;
    int            iLibCount = (int) eChannelType;

    // Additional code added to block reloading of DLL if name has not changed.
    if( m_pLibName[iLibCount] == NULL ||
        strcmp( pcLibraryName, m_pLibName[iLibCount]) != 0)
    {
        sLibHandler = PLATFORM_LOADLIB( pcLibraryName);

        if( !sLibHandler)
        {
            // get load lib error information
            string sFullMessage = "Failed to load transport channel library " +  
                                  string(pcLibraryName) + ". " + PLATFORM_LOADLIB_ERROR;

            throw HTTPTransportException( SERVER_TRANSPORT_LOADING_CHANNEL_FAILED, sFullMessage.c_str());
        }
        else
        {
            CREATE_OBJECT3 sCreate = (CREATE_OBJECT3)NULL;
            DELETE_OBJECT3 sDelete = (DELETE_OBJECT3)NULL;
            
            sCreate = (CREATE_OBJECT3) PLATFORM_GETPROCADDR( sLibHandler, CREATE_FUNCTION3);
            if (sCreate)
                sDelete = (DELETE_OBJECT3) PLATFORM_GETPROCADDR( sLibHandler, DELETE_FUNCTION3);

            if (!sCreate || !sDelete)
            {
                // get load lib error information
                string sFullMessage = "Failed to resolve to transport channel procedures in library " +
                                      string(pcLibraryName) + ". " +  PLATFORM_LOADLIB_ERROR;
                
                // Unload library - this must be done after obtaining error info above
                PLATFORM_UNLOADLIB( sLibHandler);

                if( eChannelType == UnsecureChannel)
                {
                    throw HTTPTransportException( SERVER_TRANSPORT_LOADING_CHANNEL_FAILED, sFullMessage.c_str());
                }
                else
                {
                    throw HTTPTransportException( SERVER_TRANSPORT_LOADING_SSLCHANNEL_FAILED, sFullMessage.c_str());
                }
            }

#ifdef ENABLE_AXISTRACE
// Load function to do lib level inits
            void (*initializeLibrary) (AxisTraceEntrypoints*);
            initializeLibrary = (void (*)(AxisTraceEntrypoints*))PLATFORM_GETPROCADDR(sLibHandler, "initializeLibrary");

            if( initializeLibrary)
            {
                (*initializeLibrary) (AxisTrace::getTraceEntrypoints());
            }
#endif

            // Additional code added to that when the user wants to load a different
            // library from that which is already loaded, it will now allow the change.
            UnLoadChannelLibrary(eChannelType);
                        
            delete [] m_pLibName[iLibCount];
            m_pLibName[iLibCount] = NULL;

            m_pLibName[iLibCount] = new char[ strlen( pcLibraryName) + 1];
            strcpy( m_pLibName[iLibCount], pcLibraryName);
            m_LibHandler[iLibCount] = sLibHandler;

            if( sCreate)
            {
                sCreate( &pChannel);
                m_pChannel[iLibCount] = pChannel;
            }
        }
    }
    else
        pChannel = m_pChannel[iLibCount];

    return pChannel;
}

bool ChannelFactory::
UnLoadChannelLibrary( g_ChannelType eChannelType)
{
    bool    bSuccess = false;
    int        iLibIndex = (int) eChannelType;

    if( m_pChannel[iLibIndex] != NULL)
    {
        if( m_LibHandler[iLibIndex] != NULL)
        {
            // If there is a channel library object handle then find the entry point in
            // the library to call the channel library destructor (DestroyInstance) which
            // in turn calls the channel destructor.  On return from this call, the
            // m_pChannel[iLibIndex] object no longer exists.
            DELETE_OBJECT3 sDelete = (DELETE_OBJECT3) PLATFORM_GETPROCADDR( m_LibHandler[iLibIndex], DELETE_FUNCTION3);
            sDelete( m_pChannel[iLibIndex]);
        }
        else
        {
            // Samisa: somehow, the above block does not seem to deallocate the channel
            // As a workaround, I delete the channel here and seems this logic is not having any side effects
            // More importantly I could get rid of the memory leak
            delete m_pChannel[iLibIndex];
        }

        m_pChannel[iLibIndex] = NULL;
    }

    // Delete library name from the library name list.
    delete [] m_pLibName[iLibIndex];
    m_pLibName[iLibIndex] = NULL;

    // If a channel library object handle is valid, then unload the library and
    // reset the handle.
    if( m_LibHandler[iLibIndex] != NULL)
    {
        PLATFORM_UNLOADLIB( m_LibHandler[iLibIndex]);
        m_LibHandler[iLibIndex] = 0;
        bSuccess = true;
    }

    return bSuccess;
}

void ChannelFactory::
preloadChannels(char *unsecChannel, char *secChannel)
{
	if (unsecChannel && strcmp(unsecChannel,"Unknown")) preloadChannel(UnsecureChannel, unsecChannel);
	if (secChannel && strcmp(secChannel,"Unknown")) preloadChannel(SecureChannel, secChannel);
}

void ChannelFactory::
preloadChannel(g_ChannelType type, const char *pcLibraryName)
{
    int iLibCount = (int)type;
    ChannelLibrary *pCh = new ChannelLibrary();

    pCh->m_Library = PLATFORM_LOADLIB( pcLibraryName);
    if( !pCh->m_Library)
    {
        // get load lib error information
        string sFullMessage = "Failed to pre-load transport channel library " +  
                              string(pcLibraryName) + ". " + PLATFORM_LOADLIB_ERROR;
        
        delete pCh;

        throw HTTPTransportException( SERVER_TRANSPORT_LOADING_CHANNEL_FAILED, sFullMessage.c_str());
    }

    pCh->m_Create = (CREATE_OBJECT3) PLATFORM_GETPROCADDR( pCh->m_Library, CREATE_FUNCTION3);
    if (pCh->m_Create)
        pCh->m_Delete = (DELETE_OBJECT3) PLATFORM_GETPROCADDR( pCh->m_Library, DELETE_FUNCTION3);
        
    if (!pCh->m_Create || !pCh->m_Delete)
    {
        // get load lib error information
        string sFullMessage = "Failed to resolve to transport channel procedures in library " +
                              string(pcLibraryName) + ". " +  PLATFORM_LOADLIB_ERROR;
        
        // Unload library - this must be done after obtaining error info above
        PLATFORM_UNLOADLIB( pCh->m_Library);
        
        delete pCh;

        if( type == UnsecureChannel)
        {
            throw HTTPTransportException( SERVER_TRANSPORT_LOADING_CHANNEL_FAILED, sFullMessage.c_str());
        }
        else
        {
            throw HTTPTransportException( SERVER_TRANSPORT_LOADING_SSLCHANNEL_FAILED, sFullMessage.c_str());
        }
    }

#ifdef ENABLE_AXISTRACE
    // Load function to do lib level inits
    void (*initializeLibrary) (AxisTraceEntrypoints*);
    initializeLibrary = (void (*)(AxisTraceEntrypoints*))PLATFORM_GETPROCADDR(pCh->m_Library, "initializeLibrary");
    if( initializeLibrary)
    {
        (*initializeLibrary) (AxisTrace::getTraceEntrypoints());
    }
#endif
    m_ChannelLibrary[iLibCount] = pCh;
}

IChannel *ChannelFactory::
createChannel(g_ChannelType type) 
{
    int iLibCount = (int)type;
    IChannel *pChannel = NULL;
    if (m_ChannelLibrary[iLibCount])
    {
        m_ChannelLibrary[iLibCount]->m_Create(&pChannel);
        m_pChannel[iLibCount] = pChannel;
    }
    return pChannel;
}

void ChannelFactory::
unloadChannels()
{
    for (int i=0; i<(int)MaxChannelCount; i++) 
    {
        if (m_ChannelLibrary[i])
        {
            PLATFORM_UNLOADLIB(m_ChannelLibrary[i]->m_Library);
            delete m_ChannelLibrary[i];
            m_ChannelLibrary[i] = NULL;
        }
    }
}

AXIS_CPP_NAMESPACE_END
