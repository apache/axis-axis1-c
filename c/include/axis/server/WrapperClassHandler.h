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

#if !defined(__WRAPPERCLASSHANDLER_OF_AXIS_INCLUDED__)
#define __WRAPPERCLASSHANDLER_OF_AXIS_INCLUDED__

#include <axis/server/BasicHandler.h>
/**
    @class WrapperClassHandler
    @brief
    @author Susantha Kumara (skumara@virtusa.com)

*/
class WrapperClassHandler : public HandlerBase 
{
public:
	WrapperClassHandler(){};
	virtual ~WrapperClassHandler(){};
	virtual AXIS_BINDING_STYLE AXISCALL getBindingStyle()=0;
	int AXISCALL getType(){return WEBSERVICE_HANDLER;};
};

#endif //__WRAPPERCLASSHANDLER_OF_AXIS_INCLUDED__
