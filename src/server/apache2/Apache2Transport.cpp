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
 *
 */

#include "Apache2Transport.h"

#define AXIS_URI_EXTENSION "/axis"

/* Following is the character that should be used to separate the method name in
 * the SOAPAction header value. Ex: "http://localhost:80/axis/Calculator#Add"
 */
#define SOAPACTION_METHODNAME_SEPARATOR "#"

Apache2Transport::Apache2Transport(void* pContext)
{
    m_eProtocolType = APTHTTP1_1;
	m_pContext = pContext;
#ifndef CHUNCKED_DATA_SUPPORTED
    m_pBuffers = new BufferInfo[NO_OF_SERIALIZE_BUFFERS];
	memset((void*)m_pBuffers, 0, sizeof(BufferInfo)*NO_OF_SERIALIZE_BUFFERS);
#endif

	
}

Apache2Transport::~Apache2Transport()
{

}

AXIS_TRANSPORT_STATUS Apache2Transport::sendBytes(const char* pcSendBuffer, const void* pBufferId)
{
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

void Apache2Transport::setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)
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
		ap_table_set(((request_rec*)m_pContext)->headers_out, key, value);
#ifdef CHUNCKED_DATA_SUPPORTED
		ap_send_http_header((request_rec*)m_pContext);
		/* Should we remove the sent headers ? */
#endif
	}
}

AXIS_TRANSPORT_STATUS Apache2Transport::flushOutput()
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
        sprintf(strtonum, "%d", contentLength);
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

AXIS_TRANSPORT_STATUS Apache2Transport::getBytes(char* pBuffer, int* piSize)
{
	
	int nBufSize = *piSize;
    int len_read;
    len_read = ap_get_client_block((request_rec*) m_pContext, pBuffer, *piSize);
	
 	if (strstr(pBuffer, "Content-Id")) {
		pAttachmentHelper = new AttachmentHelper();
		char *pAttachBuffer = (char*)malloc(1000);
		char *mimeBoundary = (char*)malloc(1000);		

		pAttachmentHelper->extract_Attachment(pBuffer);		
		pAttachmentHelper->extract_SOAPMimeHeaders(pBuffer);	
		pAttachmentHelper->extract_Soap(pBuffer);
				
	}

    *piSize = len_read;

    if (len_read < nBufSize)
    {
        pBuffer[len_read] = '\0';

        return TRANSPORT_FINISHED;
    }
    else
        return TRANSPORT_IN_PROGRESS;
}

const char* Apache2Transport::getTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE eType)
{
    const char* pcValue;
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
                    strlen(AXIS_URI_EXTENSION) + 1;
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

void Apache2Transport::setTransportProperty(const char* pcKey, const char* pcValue)
{

}

const char* Apache2Transport::getTransportProperty(const char* pcKey)
{
    /* ap_table_elts returns an array_header struct. The nelts element of that 
     * struct contains the number of input header elements. Finally assigns that
     * to the axis soap data structure. */
    const apr_array_header_t* arr;
	int headercount = ap_table_elts(((request_rec*)m_pContext)->headers_in)->nelts;
	apr_table_entry_t* pHeaders = 0;
    /* casting req_rec->headers_in to axis header struct and assigning that to 
     * the axis soap structure. Hope this is ok 
     */

    /* obtain the array_header from the headers_in table and assign it to the 
     * axis soap structure 
     */
    arr = ap_table_elts(((request_rec*)m_pContext)->headers_in);
	pHeaders = (apr_table_entry_t*)arr->elts;
	for (int ix=0; ix<headercount; ix++)
	{
		if (!strcmp(pHeaders->key, pcKey))
			return pHeaders->val;
		pHeaders++;
	}
	return 0;
}

void Apache2Transport::setSessionId(const char* pcSessionId)
{
}

const char* Apache2Transport::getSessionId()
{
	return "this is temporary session id"; //TODO
}

const char* Apache2Transport::getServiceName()
{
	return 0; //TODO
}

AXIS_PROTOCOL_TYPE Apache2Transport::getProtocol()
{
	return m_eProtocolType;
}
 
int Apache2Transport::setProtocol(AXIS_PROTOCOL_TYPE eProtocol)
{
    if( eProtocol == APTHTTP1_1 || eProtocol == APTHTTP1_0 )
    {
       m_eProtocolType = eProtocol;
       return AXIS_SUCCESS;
    }
    else
        return AXIS_FAIL;
}


int Apache2Transport::getSubProtocol()
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

ISoapAttachment*  Apache2Transport::getAttachment(const char* pcAttachmentid)
{		
	ISoapAttachment* pAttch = pAttachmentHelper->getAttachment(pcAttachmentid);
	return pAttch;
};

char* Apache2Transport::getIncomingSOAPMimeHeaders()
{
	return pAttachmentHelper->getIncomingSOAPMimeHeaders();
}