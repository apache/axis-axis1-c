/* -*- C++ -*- */
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


#if !defined(AXIS_DESERIALIZERPOOL_H__INCLUDED_)
#define AXIS_DESERIALIZERPOOL_H__INCLUDED_

#include "SharedObject.h"
#ifdef USER_DESERIALIZER
#include <axis/server/IWrapperSoapDeSerializer.h>
extern void* GetUserDeSerializer();
#else
#include <axis/server/SoapDeSerializer.h>
#endif
#include <axis/server/GDefine.h>
#include <list>

using namespace std;
/**
    @class DeserializerPool
    @brief interface for the DeserializerPool class.


    @author Susantha Kumara (skumara@virtusa.com)
*/
class DeserializerPool:protected SharedObject
{
    public:
        DeserializerPool ();
        virtual ~ DeserializerPool ();
    private:
        list <IWrapperSoapDeSerializer*>m_DZList;
    public:
        int GetInstance (IWrapperSoapDeSerializer** ppDZ);
        int PutInstance (IWrapperSoapDeSerializer* pDZ);
};

#endif 
