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
 *
 *
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/24 samisa
 * Filled in the empty body of setTransportProperty
 */


#include "ApacheTransport.h"

#define AXIS_URI_EXTENSION "/axis"

/* Following is the character that should be used to separate the method name in
 * the SOAPAction header value. Ex: "Calculator#Add"
 */
#define SOAPACTION_METHODNAME_SEPARATOR "#"

ApacheTransport::ApacheTransport(void* pContext)
{
    m_eProtocolType = APTHTTP1_1;
    m_bHeadersSent = false;
	m_pContext = pContext;
#ifndef CHUNCKED_DATA_SUPPORTED
    m_pBuffers = new BufferInfo[NO_OF_SERIALIZE_BUFFERS];
	memset((void*)m_pBuffers, 0, sizeof(BufferInfo)*NO_OF_SERIALIZE_BUFFERS);
#endif
}

ApacheTransport::~ApacheTransport()
{

}

AXIS_TRANSPORT_STATUS ApacheTransport::sendBytes(const char* pcSendBuffer, const void* pBufferId)
{
    if (!m_bHeadersSent)
    {
        ap_send_http_header ((request_rec*)m_pContext);
        m_bHeadersSent = true;
    }

#ifndef CHUNCKED_DATA_SUPPORTED
    int index;
#endif

    if (!pBufferId) /* temporary buffers should always sent immediately */
    {
		ap_rputs(pcSendBuffer, (request_rec*)m_pContext);
        return TRANSPORT_FINISHED;
    }

#ifdef CHUNCKED_DATA_SUPPORTED
    // Do we need to send any headers and length of this chunk ? 
	ap_rputs(pcSendBuffer, (request_rec*)m_pContext);
    /* Do we need to send any indication to mark the end of this 
     * chunk ?
     */ 
    return TRANSPORT_FINISHED;
#else
    for (index = 0; index < NO_OF_SERIALIZE_BUFFERS; index++)
    {
        if (!m_pBuffers[index].pcBuffer)
        {
            m_pBuffers[index].pcBuffer = pcSendBuffer;
            m_pBuffers[index].pBufferId = pBufferId;
            break;
        }
    }
    return TRANSPORT_IN_PROGRESS;
#endif	
}

int ApacheTransport::setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)
{
    const char* key = NULL;
    switch (type)
    {
        case SOAPACTION_HEADER:  /* needed only in the client side ? */
            break;
        case SERVICE_URI:        /* need to set ? */
            break;
        case OPERATION_NAME:     /* need to set ? */
            break;
        case SOAP_MESSAGE_LENGTH:
		/* This is apache module and transport is http so the key */ 
            key = "Content-Length"; 
            break;
        default:;
    }
    if (key)
    {
		ap_table_set (((request_rec*)m_pContext)->headers_out, key, value);
#ifdef CHUNCKED_DATA_SUPPORTED
		ap_send_http_header ((request_rec*)m_pContext);
		/* Should we remove the sent headers ? */
#endif
	}
    return 0;
}

AXIS_TRANSPORT_STATUS ApacheTransport::flushOutput()
{
#ifndef CHUNCKED_DATA_SUPPORTED
    int contentLength = 0;
    int index;
    char strtonum[8];
#endif
#ifdef CHUNCKED_DATA_SUPPORTED
    /* headers have already been sent. see set_transport_information
     * http body too have been sent
     * Do we need to send any indication to mark end of chuncked 
     * data ?  
     */
#else
    /* Calculate Content-Length and set header */
    for (index = 0; index < NO_OF_SERIALIZE_BUFFERS; index++)
    {
        if (!m_pBuffers[index].pcBuffer)
            break;
        contentLength += strlen(m_pBuffers[index].pcBuffer);
    }
    if (contentLength != 0)     /* do only if the http body is not empty. */
    {
        sprintf (strtonum, "%d", contentLength);
        setTransportProperty(SOAP_MESSAGE_LENGTH, strtonum);
        ap_send_http_header((request_rec*)m_pContext);
        /* Send all buffers */
        for (index = 0; index < NO_OF_SERIALIZE_BUFFERS; index++)
        {
            if (!m_pBuffers[index].pcBuffer)
                break;
            ap_rputs(m_pBuffers[index].pcBuffer, (request_rec*)m_pContext);
            /* Let Axis know that the buffer is no longer in use */
            m_pReleaseBufferCallback(m_pBuffers[index].pcBuffer, 
                m_pBuffers[index].pBufferId);
        }
    }
#endif
	return TRANSPORT_FINISHED;
}

AXIS_TRANSPORT_STATUS ApacheTransport::getBytes(char* pBuffer, int* piSize)
{
    int nBufSize = *piSize;
    int len_read;
    ap_hard_timeout ("util_read", (request_rec*) m_pContext);
    len_read = ap_get_client_block ((request_rec*) m_pContext, pBuffer, *piSize);
    ap_reset_timeout ((request_rec*) m_pContext);
    *piSize = len_read;
    if (len_read < nBufSize)
    {
        pBuffer[len_read] = '\0';
        return TRANSPORT_FINISHED;
    }
    else
        return TRANSPORT_IN_PROGRESS;
}

const char* ApacheTransport::getTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE eType)
{
    const char* pcValue = NULL;
	/* the member, "path" of "parsed_uri" contains the uri of the
       request (i.e "/abc/xyz" part of http://somehost/abc/xyz) */
    const char* pcUriPath =  ((request_rec*)m_pContext)->parsed_uri.path;

    switch (eType)
    {
        case SOAPACTION_HEADER:
			return getTransportProperty("SOAPAction");
        case SERVICE_URI:
            if (strstr(pcUriPath, AXIS_URI_EXTENSION))
            {
                return strstr(pcUriPath, AXIS_URI_EXTENSION) +
                    strlen (AXIS_URI_EXTENSION) + 1;
            }
            else
            {
                return pcUriPath;
            }
        case OPERATION_NAME:
            pcValue = getTransportProperty("SOAPAction");
            if (pcValue)
            {
                if (strstr(pcValue, SOAPACTION_METHODNAME_SEPARATOR))
                {
                    return strstr(pcValue, SOAPACTION_METHODNAME_SEPARATOR) +
                          strlen(SOAPACTION_METHODNAME_SEPARATOR);
                }
                else
                {
                    return pcValue;
                }
            }
        case SOAP_MESSAGE_LENGTH:
			return getTransportProperty("Content-Length");
	    /* this is apache module and transport is http so the key */
        default:;
    }
    return NULL;
}

int ApacheTransport::setTransportProperty(const char* pcKey, const char* pcValue)
{
	 if (pcKey && pcValue)
    {
		ap_table_set (((request_rec*)m_pContext)->headers_out, pcKey, pcValue);
#ifdef CHUNCKED_DATA_SUPPORTED
		ap_send_http_header ((request_rec*)m_pContext);
		/* Should we remove the sent headers ? */
#endif
	}
    return 0;

}

const char* ApacheTransport::getTransportProperty(const char* pcKey, bool response)
{
    /* ap_table_elts returns an array_header struct. The nelts element of that 
     * struct contains the number of input header elements. Finally assigns that
     * to the axis soap data structure. */
    array_header* arr = NULL;
	int headercount = ap_table_elts(((request_rec*)m_pContext)->headers_in)->nelts;
	Ax_header* pHeaders = 0;
    /* casting req_rec->headers_in to axis header struct and assigning that to 
     * the axis soap structure. Hope this is ok 
     */

    /* obtain the array_header from the headers_in table and assign it to the 
     * axis soap structure 
     */
    arr = ap_table_elts(((request_rec*)m_pContext)->headers_in);
	pHeaders = (Ax_header*) arr->elts;
	for (int ix=0; ix<headercount; ix++)
	{
		if (!strcmp(pHeaders->headername, pcKey))
			return pHeaders->headervalue;
		pHeaders++;
	}
	return 0;
}

void ApacheTransport::setSessionId(const char* pcSessionId)
{
}

const char* ApacheTransport::getSessionId()
{
	return "this is temporary session id"; //TODO
}

const char* ApacheTransport::getServiceName()
{
	return 0; //TODO
}

AXIS_PROTOCOL_TYPE ApacheTransport::getProtocol()
{
	return m_eProtocolType;
}

int ApacheTransport::setProtocol(AXIS_PROTOCOL_TYPE eProtocol)
{
    if( eProtocol == APTHTTP1_1 || eProtocol == APTHTTP1_0 )
    {
       m_eProtocolType = eProtocol;
       return AXIS_SUCCESS;
    }
    else
        return AXIS_FAIL;
}

int ApacheTransport::getSubProtocol()
{
    /*Determine the http method and assign it to the axis soap structure */
    switch (((request_rec*)m_pContext)->method_number)
    {
        case M_GET:
            return AXIS_HTTP_GET;
        case M_POST:
            return AXIS_HTTP_POST;
        default:
            return AXIS_HTTP_UNSUPPORTED;
    }
}
