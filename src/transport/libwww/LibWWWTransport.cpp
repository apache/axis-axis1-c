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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */


#include "LibWWWTransport.h"
#include "WWWLib.h"
#include "WWWInit.h"

// The object that acquires the lock to start event loop
LibWWWTransport *
    LibWWWTransport::m_spLockingObject = NULL;

int
terminate_handler (HTRequest * request, HTResponse * response,
		   void *param, int status)
{
    if (status == HT_LOADED)
    {
	//HTChunk *chunk = (HTChunk *) HTRequest_context (request);
	//HTPrint("In Handler %s\n", HTChunk_data(chunk) );
	if (HTNet_isEmpty ())
	{
	    HTEventList_stopLoop ();
	    LibWWWTransport::m_spLockingObject = NULL;
	}

    }
#ifdef HT_EXT_CONTINUE
#else
    HTEventList_stopLoop ();
#endif
    return status;
}

PUBLIC HTChunk *
HTPostAnchorToChunk (HTParentAnchor * source,
		     HTAnchor * destination, HTRequest * request)
{
    if (source && destination && request)
    {
	HTChunk *
	    chunk = NULL;
	HTStream *
	    target = HTStreamToChunk (request, &chunk, 0);
	HTRequest_setOutputStream (request, target);
	if (HTPostAnchor (source, destination, request) == YES)
	    return chunk;
	else
	{
	    HTChunk_delete (chunk);
	    return NULL;
	}
    }
    return NULL;
}


LibWWWTransport::LibWWWTransport ():m_pRequest (NULL), m_pResult (NULL), m_pcData (NULL), m_pcProxy (NULL),
m_iBytesLeft (0), m_pcReceived (NULL)
{
    //Samisa moveed to initializeLibrary
    /*//Create a new premptive client 
       HTProfile_newNoCacheClient("AxisCpp", "1.3");
       //Disable interactive mode, could be useful when debugging
       HTAlert_setInteractive(NO);
       // Add our own filter to do the clean up after response received
       HTNet_addAfter(terminate_handler, NULL, NULL, HT_ALL, HT_FILTER_LAST);
       //How long we are going to wait for a response
       HTHost_setEventTimeout(20000);
     */
    m_eProtocolType = APTHTTP1_1;
    m_pRequest = HTRequest_new ();

}

LibWWWTransport::~LibWWWTransport ()
{
    if (m_pResult)
	HTChunk_delete (m_pResult);
    if (m_pRequest)
	HTRequest_delete (m_pRequest);
    if (m_pcData)
	free (m_pcData);
    if (m_pcProxy)
	free (m_pcProxy);
    //if (m_pcReceived) //This is not required as the m_pRequest Chunk deletion takes care of this
    //    free(m_pcReceived);

    //Terminate libwww 
    //HTProfile_delete();

    //Samisa:This deletion should also go to the base class 
    //destructos as is the setEndpointUri method should
    if (m_pcEndpointUri)
	free (m_pcEndpointUri);
}

AXIS_TRANSPORT_STATUS
    LibWWWTransport::sendBytes (const char *pcSendBuffer,
				const void *pBufferid)
{
    //Samisa: Why do I have to go through the buffers of Serializer?
    //If I am the transport, I would like the serializer 
    //to give me the m_pcData to be sent. 
    //This method causes, high degree of coupling between the transport 
    //and the Serializer. See the SOAPTrasport ducumetation for details.
    //SOAP transport expects the implementation to send the m_pcData over the wire
    //in flushOutput() and not in this method. I think there need to be some 
    //renaming here.

    //In LibWWW context, the library is going to handle the document content
    //that is to be posted. Hence I am not going to bother about buffering
    //here.

    //As per the SOAPTrasport documentation, I assume that if I get 
    //null pcSendBuffer, that indicated the end of the document to be sent.
    if (pcSendBuffer)
    {
	char *temp = m_pcData;
	if (m_pcData)
	    m_pcData =
		(char *) malloc (sizeof (char) *
				 (strlen (m_pcData) + strlen (pcSendBuffer) +
				  1));
	else
	    m_pcData =
		(char *) malloc (sizeof (char) * (strlen (pcSendBuffer) + 1));

	m_pcData[0] = '\0';
	if (temp)
	{
	    strcat (m_pcData, temp);
	    free (temp);
	}
	strcat (m_pcData, pcSendBuffer);
	//Samisa: Callback to free memeory has been removed
	//Q: who should relese memory in this case? A: Serializer
	//m_pReleaseBufferCallback(pcSendBuffer, pBufferid);
    }

    return TRANSPORT_IN_PROGRESS;

}

AXIS_TRANSPORT_STATUS
    LibWWWTransport::getBytes (char *pcBuffer, int *piRetSize)
{
    if (m_iBytesLeft > 0)
    {
	int iToCopy = (*piRetSize < m_iBytesLeft) ? *piRetSize : m_iBytesLeft;
	strncpy (pcBuffer,
		 m_pcReceived + (strlen (m_pcReceived) - m_iBytesLeft),
		 iToCopy);
	m_iBytesLeft -= iToCopy;
	*piRetSize = iToCopy;
	return TRANSPORT_IN_PROGRESS;
    }
    else
    {
	return TRANSPORT_FINISHED;
    }

}

int
LibWWWTransport::openConnection ()
{
    //Samisa: I wonder this should be an API call.
    //It should not be the job of the upper layers to tell the trasport 
    //to open and close connections. Rather the transport should determine 
    //when to do that, when sendBytes is called
    //Infact, in LibWWW, opening and closing the connection is trasparernt.
    //Rather the user has to focus on the content to be sent, formats, semantics etc.
    //So I think there is nothing to be done here, in case of LibWWW. 
    //I think it is better to rename this method to intialize in SOAP transport.
    return AXIS_SUCCESS;
}

void
LibWWWTransport::closeConnection ()
{
    //Samisa: comment on openConnection apply here too.
}

void
LibWWWTransport::

registerReleaseBufferCallback (AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER
			       pFunct)
{
    m_pReleaseBufferCallback = pFunct;
}

void
LibWWWTransport::setTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE eType,
				       const char *pcValue)
{
    char *key = NULL;
    switch (eType)
    {
    case SOAPACTION_HEADER:
	key = "SOAPAction";
	break;
    case SERVICE_URI:		/* need to set ? NO */
	break;
    case OPERATION_NAME:	/* need to set ? NO */
	break;
    case SOAP_MESSAGE_LENGTH:	//No need to set, LibWWW sets this
	break;
    default:;
    }

    if (!key)
	return;

    char *value = const_cast < char *>(pcValue);
    HTRequest_addExtraHeader (m_pRequest, key, value);
}

const char *
LibWWWTransport::getTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE eType)
{
    return "TODO";
}

void
LibWWWTransport::setTransportProperty (const char *pcKey, const char *pcValue)
{
    char *key = const_cast < char *>(pcKey);
    char *value = const_cast < char *>(pcValue);
    HTRequest_addExtraHeader (m_pRequest, key, value);
}

const char *
LibWWWTransport::getTransportProperty (const char *pcKey)
{
    return "TODO";		//this could be implemented with HTAssocList * HTRequest_extraHeader (HTRequest * request); 
}

void
LibWWWTransport::setAttachment (const char *pcAttachmentid,
				const char *pcAttachment)
{
    //TODO
}

const char *
LibWWWTransport::getAttachment (const char *pcAttachmentid)
{
    return "TODO";
}

void
LibWWWTransport::setEndpointUri (const char *pcEndpointUri)
{
    //Samisa:This too should go to the base class SOAPTransport
    //It is not point duplicating this method in all transport implementations
    m_pcEndpointUri = strdup (pcEndpointUri);
}

void
LibWWWTransport::setSessionId (const char *pcSessionId)
{
    //TODO
}

const char *
LibWWWTransport::getSessionId ()
{
    return "TODO";
}

const char *
LibWWWTransport::getServiceName ()
{
    //Samisa: Copied and pasted from AxisTrasport class.
    //Should be moved to SOAPTrasport class as it is always derived from the 
    //inherited attribute
    char *pachTmp = strrchr (m_pcEndpointUri, '/');

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

AXIS_PROTOCOL_TYPE LibWWWTransport::getProtocol ()
{
    return m_eProtocolType;		//HTTP
}

int LibWWWTransport::setProtocol(AXIS_PROTOCOL_TYPE eProtocol)
{
    if( eProtocol == APTHTTP1_1 || eProtocol == APTHTTP1_0 )
    {
       m_eProtocolType = eProtocol;
       return AXIS_SUCCESS;
    }
    else
        return AXIS_FAIL;
}

int
LibWWWTransport::getSubProtocol ()
{
    return 0;			//TODO:Should return POST
}

AXIS_TRANSPORT_STATUS LibWWWTransport::flushOutput ()
{


#ifdef HT_EXT_CONTINUE		//this block sends the message immediately after HTTP headers
    //without using 100-continue

    //HTRequest_clear(m_pRequest);
    HTRequest_setFlush (m_pRequest, YES);
    //HTRequest_setOutputFormat(m_pRequest, WWW_SOURCE);
    HTRequest_setOutputFormat (m_pRequest, HTAtom_for ("text/xml"));
    HTRequest_setMethod (m_pRequest, METHOD_EXT_0);

    if (HTRequest_setMessageBody (m_pRequest, m_pcData) == NO)
	return TRANSPORT_FAILED;

    HTRequest_setMessageBodyFormat (m_pRequest, HTAtom_for ("text/xml"));
    HTRequest_setMessageBodyLength (m_pRequest, strlen (m_pcData));
    if (m_pResult)
	HTChunk_delete (m_pResult);

    //m_pResult = HTLoadToChunk(m_pcEndpointUri, m_pRequest);

    HTStream *
	target = HTStreamToChunk (m_pRequest, &m_pResult, 0);
    HTRequest_setOutputStream (m_pRequest, target);

    HTRequest_setContext (m_pRequest, m_pResult);

    HTAnchor *
	anchor = HTAnchor_findAddress (m_pcEndpointUri);
    HTRequest_setAnchor (m_pRequest, anchor);

    BOOL
	status = HTLoadToStream (m_pcEndpointUri, target, m_pRequest);

    if (LibWWWTransport::m_spLockingObject == NULL)
    {
	LibWWWTransport::m_spLockingObject = this;
    }
    if (LibWWWTransport::m_spLockingObject == this)
    {
	HTEventList_loop (m_pRequest);
    }
    //if (m_pcReceived)
//      free (m_pcReceived);

    int
	count = 0;
    do
    {
	if (m_pResult)
	{
	    m_pcReceived = HTChunk_data (m_pResult);
	    if (m_pcReceived)
	    {
		m_iBytesLeft = strlen (m_pcReceived);
		return TRANSPORT_FINISHED;
	    }
	    else
		sleep (1);
	}
	else
	    sleep (1);
    }
    while (count++ < 2 && (HTRequest_bodyRead (m_pRequest) == 0));

    if (count == 2)		// possible deadlock
    {
	//stop loop
	if (HTNet_isEmpty ())
	{
	    HTEventList_stopLoop ();
	    LibWWWTransport::m_spLockingObject = NULL;
	}
	//start loop
	if (LibWWWTransport::m_spLockingObject == NULL)
	{
	    LibWWWTransport::m_spLockingObject = this;
	}
	if (LibWWWTransport::m_spLockingObject == this)
	{
	    HTEventList_loop (m_pRequest);
	}


    }

    if (m_pResult)
    {
	m_pcReceived = HTChunk_data (m_pResult);
	if (m_pcReceived)
	{
	    m_iBytesLeft = strlen (m_pcReceived);
	    return TRANSPORT_FINISHED;
	}
	else
	    return TRANSPORT_FAILED;
    }

    return TRANSPORT_FAILED;
#else

    HTParentAnchor *
	src = NULL;
    HTAnchor *
	dst = NULL;

    dst = HTAnchor_findAddress (m_pcEndpointUri);
    src = HTTmpAnchor (NULL);
    HTAnchor_setDocument (src, m_pcData);
    HTAnchor_setFormat (src, HTAtom_for ("text/xml"));
    HTRequest_setOutputFormat (m_pRequest, HTAtom_for ("text/xml"));
    HTAnchor_setLength (src, strlen (m_pcData));

    if (m_pResult)
	HTChunk_delete (m_pResult);

    m_pResult = HTPostAnchorToChunk (src, dst, m_pRequest);
    HTEventList_loop (m_pRequest);

    if (m_pResult)
    {
	m_pcReceived = HTChunk_data (m_pResult);
	if (m_pcReceived)
	{
	    m_iBytesLeft = strlen (m_pcReceived);
	    return TRANSPORT_FINISHED;
	}
	else
	    return TRANSPORT_FAILED;
    }
    else
	return TRANSPORT_FAILED;

#endif
}

void
LibWWWTransport::setProxy (const char *pcProxyHost, unsigned int uiProxyPort)
{
    if (m_pcProxy)
	free (m_pcProxy);

    char port[10];
    sprintf (port, "%d", uiProxyPort);
    m_pcProxy =
	(char *) malloc (sizeof (char) *
			 (strlen (pcProxyHost) + strlen (":") +
			  strlen (port) + 1));
    strcat (m_pcProxy, pcProxyHost);
    strcat (m_pcProxy, ":");
    strcat (m_pcProxy, port);
    HTRequest_setProxy (m_pRequest, m_pcProxy);
}

void
LibWWWTransport::setTimeout (const long lSeconds)
{
    //Samisa: Got the feeling that LibWWWTransport::setTimeout 
    //should use milliseconds rather than seconds
    HTHost_setEventTimeout (lSeconds * 1000);
}


extern "C"
{
    STORAGE_CLASS_INFO int CreateInstance (SOAPTransport ** inst)
    {
	*inst = new LibWWWTransport ();
	if (*inst)
	{
	    return AXIS_SUCCESS;
	}
	return AXIS_FAIL;
    }
    STORAGE_CLASS_INFO int DestroyInstance (SOAPTransport * inst)
    {
	if (inst)
	{
	    delete inst;
	    return AXIS_SUCCESS;
	}
	return AXIS_FAIL;
    }
}

bool g_bLibWWWinitialized = false;

extern "C"
{
    STORAGE_CLASS_INFO void initializeLibrary (void)
    {
	if (g_bLibWWWinitialized)	//make sure the lib is initialized only once per client
	    return;
#ifdef HT_EXT_CONTINUE
	//Create a new non-premptive client
	HTProfile_newNoCacheClient ("AxisCpp", "1.3");
	//Create a new premptive client (in this case no event loop is required)
	//HTProfile_newPreemptiveClient("AxisCpp", "1.3");
	HTMethod_setExtensionMethod (METHOD_EXT_0, "POST", NO);
#else
	//Create a new non-premptive client
	HTProfile_newNoCacheClient ("AxisCpp", "1.3");
#endif
	g_bLibWWWinitialized = true;
	//Disable interactive mode, could be useful when debugging
	HTAlert_setInteractive (NO);
	// Add our own filter to do the clean up after response received
	HTNet_addAfter (terminate_handler, NULL, NULL, HT_ALL,
			HT_FILTER_LAST);
	//How long we are going to wait for a response
	HTHost_setEventTimeout (10000);

    }
}

extern "C"
{
    STORAGE_CLASS_INFO void uninitializeLibrary (void)
    {
	//Terminate libwww 
//    HTProfile_delete();
    }
}

/*
extern "C"
{
    STORAGE_CLASS_INFO void startEventLoop(void)
    {
        HTEventList_newLoop();
    }
}

extern "C"
{
    STORAGE_CLASS_INFO void stopEventLoop(void)
    {
        HTEventList_stopLoop();
    }
}
*/
