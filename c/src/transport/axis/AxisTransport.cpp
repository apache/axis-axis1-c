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
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/24 samisa
 * Filled in the empty body of setTransportProperty
 */

/*
 * Revision 1.2  2004/05/31 samisa
 * Added setProxy
 */

/*
 * Revision 1.3  2004/06/08 samisa
 * Added setTimeout
 */

#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4101)
#endif

#include "AxisTransport.h"
#include "TransportFactory.hpp"
#include <stdio.h>

AxisTransport::AxisTransport()
:m_strProxyHost(""), m_uiProxyPort(0), m_bUseProxy(false)
{
    m_pSender = NULL;
    m_pReceiver = NULL;
    m_pHttpTransport = NULL;
	m_pcEndpointUri = 0;
	m_pReleaseBufferCallback = 0;
    memset(&m_SendBuffers, 0, sizeof(BufferInfo)*NO_OF_SERIALIZE_BUFFERS);
	m_iBytesLeft = 0;
	m_pcReceived = 0;
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

int AxisTransport::openConnection()
{
	int secure = 0;
    /* Step 1 - Open Transport layer connection taking into account protocol
     * and endpoint URI in m_Soap
     */
    Url objUrl(m_pcEndpointUri);
    try
    {
    m_pHttpTransport = TransportFactory::GetTransport(objUrl, secure);
    memset(&m_SendBuffers, 0, sizeof(BufferInfo)*NO_OF_SERIALIZE_BUFFERS); 
    //set the proxy
    if(m_bUseProxy)
        m_pHttpTransport->setProxy(m_strProxyHost.c_str(), m_uiProxyPort);
    if(m_pHttpTransport->Init())
    {
       m_pSender = new Sender(m_pHttpTransport);
       m_pReceiver = new Receiver(m_pHttpTransport);
       /* Step 2 - Set Created streams to m_pSoap->str.ip_stream 
        * and m_pSoap->str.op_stream 
        */
/*
       m_pSoap->str.op_stream = this;
       m_pSoap->str.ip_stream = this;
       
       // Step 3 - Add function pointers to the m_Soap structure 
       m_pSoap->transport.pGetFunct = s_Get_bytes;
       m_pSoap->transport.pSendFunct = s_Send_bytes;
       m_pSoap->transport.pGetTrtFunct = s_ReceiveTransportInformation;
       m_pSoap->transport.pSetTrtFunct = s_SetTransportInformation; 
       m_pSoap->transport.pRelBufFunct = s_ReleaseReceiveBuffer;
*/
       return AXIS_SUCCESS;
    }
    else
    {
        return AXIS_FAIL;
    }
    }
    catch(AxisTransportException& e)
    {
        throw;
    }
    catch(AxisException& e)
    {
        throw;
    }
    catch(...)
    {
        throw;
    }

}        

void AxisTransport::closeConnection()
{
    /* Step 1 - Close Transport and 2 streams */
    m_pHttpTransport->Fini();
    /* Step 2 - Delete the streams */
    delete m_pSender;
    m_pSender = NULL;
    delete m_pReceiver;
    m_pReceiver = NULL;
    delete m_pHttpTransport;
    m_pHttpTransport = NULL;
/*
    m_pSoap->str.op_stream = NULL;
    m_pSoap->str.ip_stream = NULL;
    // Step 3 - Set function pointers in the m_Soap structure to NULL; 
    m_pSoap->transport.pGetFunct = NULL;
    m_pSoap->transport.pSendFunct = NULL;
    m_pSoap->transport.pGetTrtFunct = NULL;
    m_pSoap->transport.pSetTrtFunct = NULL;
*/
}

/*
AXIS_TRANSPORT_STATUS AXISCALL AxisTransport::s_Send_bytes(const char* 
                                                           pSendBuffer, const 
                                                           void* bufferid, 
                                                           const void* 
                                                           pSStream)
{
    Ax_soapstream* pStream = (Ax_soapstream*) pSStream;
    AxisTransport* pTransport = (AxisTransport*)(pStream->str.op_stream);
    return pTransport->sendBytes(pSendBuffer, bufferid, pSStream);
}
*/

AXIS_TRANSPORT_STATUS AxisTransport::flushOutput()
{
    int index;
    /* calculate content length */
    int nContentLength = 0;
    for (index=0;index < NO_OF_SERIALIZE_BUFFERS; index++)
    {
        if(!m_SendBuffers[index].pcBuffer) break;
        else
        {
            nContentLength += strlen(m_SendBuffers[index].pcBuffer);
        }
    }
    char buff[8];
    sprintf(buff, "%d", nContentLength); 
    m_pSender->SetProperty("Content-Length" , buff);
    for (index=0;index < NO_OF_SERIALIZE_BUFFERS; index++)
    {
        if(!m_SendBuffers[index].pcBuffer) break;
        else
        {    
            if(!m_pSender->Send(m_SendBuffers[index].pcBuffer))
            /* some error occured in the transport */
            {
                /* release all the buffers */
                for (int x=index; x<NO_OF_SERIALIZE_BUFFERS; x++)
                {
                    if(!m_SendBuffers[x].pcBuffer) break;
                    m_pReleaseBufferCallback(m_SendBuffers[x].pcBuffer, 
                        m_SendBuffers[x].pBufferId);
                }
                return TRANSPORT_FAILED;
            }
            /* release buffer */
			if (m_pReleaseBufferCallback)
				m_pReleaseBufferCallback(m_SendBuffers[index].pcBuffer, 
				m_SendBuffers[index].pBufferId);
        }
    }
    return TRANSPORT_FINISHED;
}

/**
 * This method accumulates all buffers until this is called with 
 * pSendBuffer == NULL which means the end of buffers. Then this function 
 * sends all the accumulated buffers through the transport. Note that the 
 * buffers provided should be NULL terminated (no length parameter is passed.
 */

AXIS_TRANSPORT_STATUS AxisTransport::sendBytes(const char* pcSendBuffer, 
                                                const void* pBufferId)
{
    for (int index=0;index < NO_OF_SERIALIZE_BUFFERS; index++)
    {
        if(!m_SendBuffers[index].pcBuffer)
        {
            m_SendBuffers[index].pcBuffer = pcSendBuffer;
            m_SendBuffers[index].pBufferId = pBufferId;
            break;
        }
    }
    return TRANSPORT_IN_PROGRESS;
}

/*
AXIS_TRANSPORT_STATUS AXISCALL AxisTransport::s_Get_bytes(const char** res, 
                                                          int* retsize, 
                                                          const void* pSStream)
{
    Ax_soapstream* pStream = (Ax_soapstream*) pSStream;
    AxisTransport* pTransport = (AxisTransport*)(pStream->str.ip_stream);
    return pTransport->getBytes(res, retsize, pSStream);
}
*/

AXIS_TRANSPORT_STATUS AxisTransport::getBytes(char* pcBuffer, int* pSize)
{
    if (0 <= m_iBytesLeft)
    {
        try
        {
            m_pcReceived = m_pReceiver->Recv();
            AXISTRACE1("CAME4", INFO);
            if (m_pcReceived)
                m_iBytesLeft = strlen(m_pcReceived);
            else
                throw AxisTransportException(SERVER_TRANSPORT_BUFFER_EMPTY);
        }
        catch(AxisTransportException& e)
        {
            throw;
        }
        catch(AxisException& e)
        {
            throw;
        }
        catch(...)
        {
            throw;
        }
    }
    if (m_pcReceived)
    {
		int iToCopy = (*pSize < m_iBytesLeft) ? *pSize : m_iBytesLeft;
        strncpy(pcBuffer, m_pcReceived, iToCopy);
		m_iBytesLeft -= iToCopy;
		m_pcReceived += iToCopy;
        *pSize = iToCopy;
        return TRANSPORT_IN_PROGRESS;
    }
    else
    {
        return TRANSPORT_FINISHED;
    }
}

/*
void AXISCALL AxisTransport::s_SetTransportInformation
    (AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value, 
    const void* pSStream)
{
    Ax_soapstream* pStream = (Ax_soapstream*) pSStream;
    AxisTransport* pTransport = (AxisTransport*)(pStream->str.op_stream);
    pTransport->setTransportInformation(type, value, pSStream);
}
*/

void AxisTransport::setTransportProperty
    (AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)
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
        key = "Content-Length"; /* this Axis transport is http so the key */
        break;
    default:;
    }
    if (!key) return;
    m_pSender->SetProperty(key, value);
}

void AxisTransport::setTransportProperty(const char* pcKey, const char* pcValue)
{
	if (pcKey && pcValue) 
	    m_pSender->SetProperty(pcKey, pcValue);

}

const char* AxisTransport::getTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE eType)
{
	//TODO
	return 0;
}

/*
const char* AXISCALL AxisTransport::s_ReceiveTransportInformation
    (AXIS_TRANSPORT_INFORMATION_TYPE type, const void* pSStream)
{
    return NULL;
}

void AXISCALL AxisTransport::s_ReleaseReceiveBuffer(const char* buffer, 
                                                    const void* pSStream)
{

}
*/

const char* AxisTransport::getServiceName()
{
   char* pachTmp = strrchr (m_pcEndpointUri, '/');

    if (pachTmp != NULL)
    {
        int iTmp = strlen (pachTmp);

        if (iTmp <= 1)
        {
            return NULL;
        }
        else
        {
            pachTmp = pachTmp + 1;
        }
    }

    return pachTmp;
}

AXIS_PROTOCOL_TYPE AxisTransport::getProtocol()
{
	return APTHTTP;
}


/**
 * This method is supposed to return whether it is http GET or POST
 */
int AxisTransport::getSubProtocol()
{
	//TODO
	return 0;
}

void 
AxisTransport::setProxy(const char* pcProxyHost, unsigned int uiProxyPort)
{
    m_strProxyHost = pcProxyHost;
    m_uiProxyPort = uiProxyPort;
    m_bUseProxy = true;    
}

void AxisTransport::setTimeout(const long lSeconds)
{
    m_pHttpTransport->setTimeout(lSeconds);
}

extern "C" {
STORAGE_CLASS_INFO
int CreateInstance(SOAPTransport **inst)
{
	*inst = new AxisTransport();
	if (*inst)
	{
		return AXIS_SUCCESS;
	}
	return AXIS_FAIL;
}
STORAGE_CLASS_INFO 
int DestroyInstance(SOAPTransport *inst)
{
	if (inst)
	{
		delete inst;
		return AXIS_SUCCESS;
	}
	return AXIS_FAIL;
}
}
