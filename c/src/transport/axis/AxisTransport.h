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
 * @author Damitha Kumarage (damitha@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */

#if !defined(_AXIS_AXIS_TRANSPORT_HPP)
#define _AXIS_AXIS_TRANSPORT_HPP

#include <axis/server/Packet.h>
#include "Sender.hpp"
#include "Receiver.hpp"

class AxisTransport
{
public:
    AxisTransport(Ax_soapstream* pSoap);
    virtual ~AxisTransport();

    int openConnection(int secure);
    void closeConnection();
    AXIS_TRANSPORT_STATUS sendBytes(const char* pSendBuffer, 
        const void* bufferid, const void* pSStream);
    AXIS_TRANSPORT_STATUS getBytes(const char** res, int* retsize, 
        const void* pSStream);
    void setTransportInformation(AXIS_TRANSPORT_INFORMATION_TYPE type, 
        const char* value, const void* pSStream);

    static AXIS_TRANSPORT_STATUS AXISCALL s_Send_bytes(const char* pSendBuffer,
        const void* bufferid, const void* pSStream);
    static AXIS_TRANSPORT_STATUS AXISCALL s_Get_bytes(const char** res, 
        int* retsize, const void* pSStream);
    static void AXISCALL s_SetTransportInformation
        (AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value, 
        const void* pSStream);
    static const char* AXISCALL s_ReceiveTransportInformation
        (AXIS_TRANSPORT_INFORMATION_TYPE type, const void* pSStream);
    static void AXISCALL s_ReleaseReceiveBuffer(const char* buffer, 
        const void* pSStream);

private:
    Transport* m_pHttpTransport;
    Sender* m_pSender;
    Receiver* m_pReceiver;
    Ax_soapstream* m_pSoap;
    sendbuffers m_SendBuffers[NO_OF_SERIALIZE_BUFFERS]; 
    /* Accumulates the serialized buffers to be transported */
};

#endif

    
