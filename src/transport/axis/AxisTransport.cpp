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
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */
#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include "AxisTransport.h"
#include "TransportFactory.hpp"
#include <stdio.h>

AxisTransport::AxisTransport(Ax_soapstream* pSoap)
{
    m_pSoap = pSoap;
    m_pSender = NULL;
    m_pReceiver = NULL;
    m_pHttpTransport = NULL;
	memset(&m_SendBuffers, 0, sizeof(sendbuffers)*NO_OF_SERIALIZE_BUFFERS); 
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

int AxisTransport::OpenConnection(int secure)
{
    //Step 1 - Open Transport layer connection taking into account protocol and endpoint URI in m_Soap
    Url objUrl(m_pSoap->so.http->uri_path);
    m_pHttpTransport = TransportFactory::GetTransport(objUrl, secure);
	memset(&m_SendBuffers, 0, sizeof(sendbuffers)*NO_OF_SERIALIZE_BUFFERS); 
    if(m_pHttpTransport->Init())
    {
       m_pSender = new Sender(m_pHttpTransport);
       m_pReceiver = new Receiver(m_pHttpTransport);
       //Step 2 - Set Created streams to m_pSoap->str.ip_stream and m_pSoap->str.op_stream
       m_pSoap->str.op_stream = this;
       m_pSoap->str.ip_stream = this;
       
       //Step 3 - Add function pointers to the m_Soap structure
       m_pSoap->transport.pGetFunct = s_Get_bytes;
       m_pSoap->transport.pSendFunct = s_Send_bytes;
       m_pSoap->transport.pGetTrtFunct = s_ReceiveTransportInformation;
       m_pSoap->transport.pSetTrtFunct = s_SetTransportInformation; 
	   m_pSoap->transport.pRelBufFunct = s_ReleaseReceiveBuffer;
	   return AXIS_SUCCESS;
    }
    else
	{
        return AXIS_FAIL;
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
	m_pSoap->transport.pSetTrtFunct = NULL;
}

AXIS_TRANSPORT_STATUS AXISCALL AxisTransport::s_Send_bytes(const char* pSendBuffer, const void* bufferid, const void* pSStream)
{
	Ax_soapstream* pStream = (Ax_soapstream*) pSStream;
    AxisTransport* pTransport = (AxisTransport*)(pStream->str.op_stream);
	return pTransport->Send_bytes(pSendBuffer, bufferid, pSStream);
}

/**
 * This method accumulates all buffers until this is called with pSendBuffer == NULL
 * which means the end of buffers. Then this function sends all the accumulated buffers
 * through the transport. Note that the buffers provided should be NULL terminated (no
 * length parameter is passed.
 */
AXIS_TRANSPORT_STATUS AxisTransport::Send_bytes(const char* pSendBuffer, const void* bufferid, const void* pSStream)
{
	int index;
	if (NULL == pSendBuffer) /* end of the buffers */
	{
		/* calculate content length */
		int nContentLength = 0;
		for (index=0;index < NO_OF_SERIALIZE_BUFFERS; index++)
		{
			if(!m_SendBuffers[index].buffer) break;
			else
			{
				nContentLength += strlen(m_SendBuffers[index].buffer);
			}
		}
		char buff[8];
		sprintf(buff, "%d", nContentLength); 
		m_pSender->SetProperty("Content-Length" , buff);
		for (index=0;index < NO_OF_SERIALIZE_BUFFERS; index++)
		{
			if(!m_SendBuffers[index].buffer) break;
			else
			{
				if(!m_pSender->Send(m_SendBuffers[index].buffer))
				/* some error occured in the transport */
				{
					/* release all the buffers */
					for (int x=index; x<NO_OF_SERIALIZE_BUFFERS; x++)
					{
						if(!m_SendBuffers[x].buffer) break;
						axis_buffer_release(m_SendBuffers[x].buffer, m_SendBuffers[x].bufferid, m_pSoap);
					}
					return TRANSPORT_FAILED;
				}
				/* release buffer */
				axis_buffer_release(m_SendBuffers[index].buffer, m_SendBuffers[index].bufferid, m_pSoap);
			}
		}
		return TRANSPORT_FINISHED;
	}
	else
	{
		for (index=0;index < NO_OF_SERIALIZE_BUFFERS; index++)
		{
			if(!m_SendBuffers[index].buffer)
			{
				m_SendBuffers[index].buffer = pSendBuffer;
				m_SendBuffers[index].bufferid = bufferid;
				break;
			}
		}
		return TRANSPORT_IN_PROGRESS;
	}
}

AXIS_TRANSPORT_STATUS AXISCALL AxisTransport::s_Get_bytes(const char** res, int* retsize, const void* pSStream)
{
	Ax_soapstream* pStream = (Ax_soapstream*) pSStream;
    AxisTransport* pTransport = (AxisTransport*)(pStream->str.ip_stream);
	return pTransport->Get_bytes(res, retsize, pSStream);
}

AXIS_TRANSPORT_STATUS AxisTransport::Get_bytes(const char** res, int* retsize, const void* pSStream)
{
    const char* strReceive =  m_pReceiver->Recv();
	if (strReceive)
	{
		*res = strReceive;
		*retsize = strlen(strReceive);
		return TRANSPORT_IN_PROGRESS;
	}
	else
	{
		*res = NULL;
		*retsize = 0;
		return TRANSPORT_FINISHED;
	}
}

void AXISCALL AxisTransport::s_SetTransportInformation(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value, const void* pSStream)
{
	Ax_soapstream* pStream = (Ax_soapstream*) pSStream;
    AxisTransport* pTransport = (AxisTransport*)(pStream->str.op_stream);
	pTransport->SetTransportInformation(type, value, pSStream);
}

void AxisTransport::SetTransportInformation(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value, const void* pSStream)
{
	const char* key = NULL;
	switch(type)
	{
	case SOAPACTION_HEADER:
		key = "SOAPAction";
		break;
	case SERVICE_URI: /* need to set ? */
		break;
	case OPERATION_NAME: /* need to set ? */
		break;
	case SOAP_MESSAGE_LENGTH: 
		key = "Content-Length"; //this Axis transport is http so the key
		break;
	default:;
	}
	if (!key) return;
	m_pSender->SetProperty(key, value);
}

const char* AXISCALL AxisTransport::s_ReceiveTransportInformation(AXIS_TRANSPORT_INFORMATION_TYPE type, const void* pSStream)
{
	return NULL;
}

void AXISCALL AxisTransport::s_ReleaseReceiveBuffer(const char* buffer, const void* pSStream)
{

}
