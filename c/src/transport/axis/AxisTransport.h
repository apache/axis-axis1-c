/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
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

    int OpenConnection(int secure);
    void CloseConnection();
	AXIS_TRANSPORT_STATUS Send_bytes(const char* pSendBuffer, const void* bufferid, const void* pSStream);
	AXIS_TRANSPORT_STATUS Get_bytes(const char** res, int* retsize, const void* pSStream);
    void SetTransportInformation(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value, const void* pSStream);

	static AXIS_TRANSPORT_STATUS AXISCALL s_Send_bytes(const char* pSendBuffer, const void* bufferid, const void* pSStream);
	static AXIS_TRANSPORT_STATUS AXISCALL s_Get_bytes(const char** res, int* retsize, const void* pSStream);
    static void AXISCALL s_SetTransportInformation(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value, const void* pSStream);
    static const char* AXISCALL s_ReceiveTransportInformation(AXIS_TRANSPORT_INFORMATION_TYPE type, const void* pSStream);
	static void AXISCALL s_ReleaseReceiveBuffer(const char* buffer, const void* pSStream);

private:
    Transport* m_pHttpTransport;
    Sender* m_pSender;
    Receiver* m_pReceiver;
    Ax_soapstream* m_pSoap;
	sendbuffers m_SendBuffers[NO_OF_SERIALIZE_BUFFERS]; /* Accumulates the serialized buffers to be transported */
};

#endif

    
