// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#if !defined(_AXIS_ISECURECHANNEL_HPP)
#define _AXIS_ISECURECHANNEL_HPP
#include <string>
#include <axis/GDefine.hpp>

using namespace std;
AXIS_CPP_NAMESPACE_USE

class ISecureChannel
{
public:
	virtual void			setSecureProperties( const char *)=0;
	virtual const char *	getSecureProperties()=0;
	virtual int setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)=0;
};

#endif

