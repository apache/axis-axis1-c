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

#pragma warning (disable : 4786)

#include "AxisTransport.h"
#include "TransportFactory.hpp"
#include "Transport.hpp"
#include "Sender.hpp"
#include "Receiver.hpp"

AxisTransport::AxisTransport(Ax_soapstream* pSoap)
{
    m_pSoap = pSoap;
    m_pSender = NULL;
    m_pReceiver = NULL;
    m_pHttpTransport = NULL;       
}

AxisTransport::~AxisTransport()
{
    if(m_pSender)
        delete m_pSender;
    if(m_pReceiver)
        delete m_pReceiver;
    if(m_pHttpTransport)
        delete m_pHttpTransport;
}

int AxisTransport::OpenConnection()
{
    //Step 1 - Open Transport layer connection taking into account protocol and endpoint URI in m_Soap
    Url objUrl(m_pSoap->so.http.uri_path);
    m_pHttpTransport = TransportFactory::GetTransport(objUrl);
    if(m_pHttpTransport->Init())
    {
       m_pSender = new Sender(m_pHttpTransport);
       m_pReceiver = new Receiver(m_pHttpTransport);
       //Step 2 - Set Created streams to m_pSoap->str.ip_stream and m_pSoap->str.op_stream
       m_pSoap->str.op_stream = m_pSender;
       m_pSoap->str.ip_stream = m_pReceiver;
       
       //Step 3 - Add function pointers to the m_Soap structure
       m_pSoap->transport.pGetFunct = Get_bytes;
       m_pSoap->transport.pSendFunct = Send_bytes;
       m_pSoap->transport.pGetTrtFunct = Receive_transport_information;
       m_pSoap->transport.pSendTrtFunct = Send_transport_information; 
	   return SUCCESS;
    }
    else
	{
        return FAIL;
	}
}        

void AxisTransport::CloseConnection()
{
	//Step 1 - Close Transport and 2 streams
	m_pHttpTransport->Fini();
	//Step 2 - Delete the streams
	delete m_pSender;
	m_pSender = NULL;
	delete m_pReceiver;
	m_pReceiver = NULL;
	m_pSoap->str.op_stream = NULL;
	m_pSoap->str.ip_stream = NULL;
	//Step 3 - Set function pointers in the m_Soap structure to NULL;
	delete m_pHttpTransport;
	m_pHttpTransport = NULL;
	m_pSoap->transport.pGetFunct = NULL;
	m_pSoap->transport.pSendFunct = NULL;
	m_pSoap->transport.pGetTrtFunct = NULL;
	m_pSoap->transport.pSendTrtFunct = NULL;
}

int AxisTransport::Send_bytes(const char* pSendBuffer, const void* pStream)
{
    Sender* pSender = (Sender*) pStream;
    if(pSender->Send(pSendBuffer))
        return SUCCESS;
    return FAIL;
    
}

int AxisTransport::Get_bytes(char* pRecvBuffer, int nBuffSize, int* pRecvSize, const void* pStream)
{
    Receiver* pReceiver = (Receiver*) pStream;
    const string& strReceive =  pReceiver->Recv();
    int nLen = strlen(strReceive.c_str());
    if(nLen < nBuffSize)
    {
        strcpy(pRecvBuffer, strReceive.c_str());
        *pRecvSize = nLen;
        return SUCCESS;
    }
    else
        return FAIL;
    
}

int AxisTransport::Send_transport_information(void* pSoapStream)
{
    Ax_soapstream* pSStream = (Ax_soapstream*) pSoapStream;
	return SUCCESS;
}

int AxisTransport::Receive_transport_information(void* pSoapStream)
{
	return SUCCESS;
}