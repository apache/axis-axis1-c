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

/*
 * @author Lilantha Darshana (lilantha@virtusa.com)
 * @author Damitha Kumarage (damitha@jkcsworld.com, damitha@opensource.lk)
 *
 */


#if !defined(_AXIS_RECEIVER_HPP)
#define _AXIS_RECEIVER_HPP

#include <axis/server/AxisException.h>
#include "AxisTransportException.h"
#include <axis/server/AxisTrace.h>
extern AxisTrace* g_pAT;

#include "Transport.hpp"

class Receiver  
{
public:
    Receiver(Transport *pTr) : m_pMsg(NULL), m_MsgSize(0), m_BytesRead(0), 
        m_pTrChannel(pTr){}
    ~Receiver();

    const char* Recv() throw (AxisException);
    int getBytesRead();

private:
    const char* m_pMsg;


    unsigned int m_RecvPort;

    int m_MsgSize;
    int m_BytesRead;
    Transport *m_pTrChannel;
};

#endif


