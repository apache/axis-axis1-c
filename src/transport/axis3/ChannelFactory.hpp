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

#if !defined(AXIS_CHANNELFACTORY_H__OF_AXIS_INCLUDED_)
#define AXIS_CHANNELFACTORY_H__OF_AXIS_INCLUDED_

#include "../../platforms/PlatformAutoSense.hpp"

#include <axis/GDefine.hpp>
#include "IChannel.hpp"

#define ChannelFactory_MaxListSize	2
#define CREATE_FUNCTION3			"CreateInstance"
#define DELETE_FUNCTION3			"DestroyInstance"
#define INIT_FUNCTION3  			"initializeLibrary"
#define UNINIT_FUNCTION3			"uninitializeLibrary"

typedef int (* CREATE_OBJECT3) (IChannel** inst);
typedef int (* DELETE_OBJECT3) (IChannel* inst);
typedef void (* INIT_OBJECT3) (AxisTraceEntrypoints& ep);
typedef void (* UNINIT_OBJECT3) ();

AXIS_CPP_NAMESPACE_START
class ChannelFactory  
{
public:
	ChannelFactory();
	virtual ~ChannelFactory();
	virtual IChannel * LoadChannelLibrary( const char * pcLibraryName);
	virtual bool UnLoadChannelLibrary( IChannel *);

private:
	int				m_iLibCount;
	char *			m_pLibName[ChannelFactory_MaxListSize];
	DLHandler		m_LibHandler[ChannelFactory_MaxListSize];
	IChannel *		m_pChannel[ChannelFactory_MaxListSize];
};
AXIS_CPP_NAMESPACE_END
#endif 

