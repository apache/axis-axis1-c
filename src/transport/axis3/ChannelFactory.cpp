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

#include "../../platforms/PlatformAutoSense.hpp"

#include "ChannelFactory.hpp"
#include <stdio.h>
#include "HTTPTransportException.hpp"
#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START

ChannelFactory::ChannelFactory()
{
	m_iLibCount = 0;

	for( int iCount = 0; iCount < ChannelFactory_MaxListSize; iCount++)
	{
		m_pLibName[iCount] = NULL;
		m_LibHandler[iCount] = NULL;
		m_pChannel[iCount] = NULL;
	}
}

ChannelFactory::~ChannelFactory()
{
	for( int iCount = 0; iCount < m_iLibCount; iCount++)
	{
		if( m_pLibName[iCount] != NULL)
		{
			delete m_pLibName[iCount];
		}

		if( m_pChannel[iCount] != NULL)
		{
			if( m_LibHandler[iCount] != NULL)
			{
				DELETE_OBJECT3 sDelete = (DELETE_OBJECT3) PLATFORM_GETPROCADDR( m_LibHandler[iCount], DELETE_FUNCTION3);

				sDelete( m_pChannel[iCount]);
			}

			m_pChannel[iCount] = 0;
		}

		if( m_LibHandler[iCount] != NULL)
		{
		    PLATFORM_UNLOADLIB( m_LibHandler[iCount]);

			m_LibHandler[iCount] = 0;
		}
	}
}

IChannel * ChannelFactory::LoadChannelLibrary( const char * pcLibraryName)
{
	DLHandler	sLibHandler;
	IChannel *	pChannel = NULL;

    sLibHandler = PLATFORM_LOADLIB( pcLibraryName);

    if( !sLibHandler)
    {
        throw HTTPTransportException( SERVER_TRANSPORT_LOADING_CHANNEL_FAILED);
    }
	else
	{
        CREATE_OBJECT3 sCreate = (CREATE_OBJECT3) PLATFORM_GETPROCADDR( sLibHandler, CREATE_FUNCTION3);
        DELETE_OBJECT3 sDelete = (DELETE_OBJECT3) PLATFORM_GETPROCADDR( sLibHandler, DELETE_FUNCTION3);

        if (!sCreate || !sDelete)
        {
		    PLATFORM_UNLOADLIB( sLibHandler);

            char * pszErrorInfo = new char[ strlen( pcLibraryName) + 1];

            strcpy( pszErrorInfo, pcLibraryName);

            throw HTTPTransportException( SERVER_TRANSPORT_LOADING_CHANNEL_FAILED, pszErrorInfo);
        }

            // Load function to do lib level inits
            void (*initializeLibrary) (AxisTraceEntrypoints&);
            initializeLibrary = (void (*)(AxisTraceEntrypoints&))PLATFORM_GETPROCADDR(m_LibHandler, "initializeLibrary");

            AxisTraceEntrypoints ep;
            AxisTrace::getTraceEntrypoints(ep);
            if (initializeLibrary)
                 (*initializeLibrary)(ep);

		m_pLibName[m_iLibCount] = new char[ strlen( pcLibraryName) + 1];

		strcpy( m_pLibName[m_iLibCount], pcLibraryName);

		m_LibHandler[m_iLibCount] = sLibHandler;

		if( sCreate)
		{
			sCreate( &pChannel);

			m_pChannel[m_iLibCount] = pChannel;
		}

		if( m_iLibCount < ChannelFactory_MaxListSize)
		{
			m_iLibCount++;
		}
	}

	return pChannel;
}

bool ChannelFactory::UnLoadChannelLibrary( IChannel * pIChannel)
{
	bool	bSuccess = false;

	for( int iCount = 0; iCount < m_iLibCount && !bSuccess; iCount++)
	{
		if( m_pChannel[iCount] == pIChannel)
		{
			DELETE_OBJECT3 sDelete = (DELETE_OBJECT3) PLATFORM_GETPROCADDR( m_LibHandler[iCount], DELETE_FUNCTION3);

			sDelete( pIChannel);

			m_pChannel[iCount] = 0;

		    PLATFORM_UNLOADLIB( m_LibHandler[iCount]);

			m_LibHandler[iCount] = 0;

			bSuccess = true;
		}
	}

	return bSuccess;
}

AXIS_CPP_NAMESPACE_END
