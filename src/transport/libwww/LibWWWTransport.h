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

#if !defined(AXIS_LIB_WWW_TRANSPORT_H__OF_AXIS_INCLUDED_)
#define AXIS_LIB_WWW_TRANSPORT_H__OF_AXIS_INCLUDED_

#include "../SOAPTransport.h"
#include "WWWLib.h"
#include "WWWInit.h"

/**
 * @file LibWWWTransport.h
 *
 * Implementation of SOAPTransport using LibWWW library.
 */

#ifdef __cplusplus

/**
 * @class LibWWWTransport
 *
 * Class that implements the SOAPTransport interface with LibWWW library.
 *
 * @brief Class that implements the SOAPTransport interface with LibWWW library.
 *
 */

AXIS_CPP_NAMESPACE_USE class LibWWWTransport:public SOAPTransport
{
  public:
    /**
     * Constructor.
     */
    LibWWWTransport ();

    /**
     * Destructor.
     */
    ~LibWWWTransport ();

    /**
     * Sends a buffer to the transport layer. A Caller may call this method
     * multiple times to send several buffers. Its upto the transport to
     * decide how they are sent (chunked/unchunked etc). But should return the
     * appropriate status code.
     *
     * @brief Sends a buffer to the transport layer.
     * @pre   1. Transport connection should have been established by calling
     *           Openconnection of the LibWWWTransport's implementaion.
     *        2. If the implementaion of LibWWWTransport intends to accumulate
     * @param pcSendBuffer Null terminated character buffer to be sent.
     * @param pBufferid void* that represents the buffer id. This pointer will
     *        only be needed by the transport layer when it needs to call
     *        caller provided callback function to indicate that transport
     *        layer has finished using the buffer. So when the transport layer
     *        intends to keep the pcSendBuffer for late sending, the value of
     *        pBufferid should also be stored. In case when pBufferid is NULL
     *        the transport layer can keep the buffer for late sending. But
     *        MUST never call the release buffer callback.
     *
     * @return Transport status. Three states are possible. They are,
     *       TRANSPORT_FINISHED    - Passed buffer has been sent. So the caller
     *                               can re-use the buffer
     *       TRANSPORT_IN_PROGRESS - Passed buffer is not yet sent. So the
     *                               caller cannot re-use the buffer
     *       TRANSPORT_FAILED      - Transport layer has failed. So the caller
     *                               should not send any more buffers.
     * @post In case this function returns TRANSPORT_IN_PROGRESS. The caller
     *       should wait till the transport layer calls the provided callback
     *       function with the bufferid to indicate that it can re-use
     *       the buffer. The transport layer MUST call the callback function
     *       for each buffer for which this function returned the status
     *       code TRANSPORT_IN_PROGRESS.
     */
    AXIS_TRANSPORT_STATUS sendBytes (const char *pcSendBuffer,
				     const void *pBufferid);
    /**
     * Gets a part of or full SOAP message. A Caller may call this method
     * multiple times to get parts of the SOAP message until the function
     * return status says that no more data available.
     *
     * @brief Gets a part of or full SOAP message.
     * @pre   Transport connection should have been established by calling
     *        Openconnection of the LibWWWTransport's implementaion.
     * @param pcBuffer The character buffer provided by the caller to be
     *        filled by the transport layer. The size of the buffer is given
     *        by the value of second parameter piRetSize. The transport layer
     *        should fill the buffer and put the number of bytes filled into
     *        the inout parameter piRetSize.
     * @param piRetSize Inout parameter which contain the size of the buffer
     *        as the in value. On return the transport layer should populate
     *        this parameter with the number of bytes copied to the buffer.
     *
     * @return Transport status. Three states are possible. They are,
     *       TRANSPORT_FINISHED    - Method call successful. No more data
     *                               is available. If pcBuffer contains any
     *                               data this is the final part of the message.
     *                               can re-use the buffer.
     *       TRANSPORT_IN_PROGRESS - Method call is successful. There can be
     *                               more data of this message for subsequent
     *                               calls to this method. pcBuffer must have
     *                               been filled to its maximum capacity.
     *       TRANSPORT_FAILED      - Transport layer has failed. So the caller
     *                               should not call this method again. Any
     *                               data in the pcBuffer are not reliable and
     *                               should not be used.
     */
    AXIS_TRANSPORT_STATUS getBytes (char *pcBuffer, int *piRetSize);
    /**
     * Opens a connection with the provided endpoint URI. The connection
     * type (protocol) is decided by the implementation and the protocol
     * set. See example implementation.
     *
     * @brief Opens a connection with the provided endpoint URI.
     * @pre   The endpoint URI and the protocol type (if needed) MUST have
     *        been set.
     * @example AxisTransport.h
     * @return Returns AXIS_SUCCESS if connection established successfully.
     *         Else returns AXIS_FAIL
     */
    int openConnection ();
    /**
     * @brief Closes the connection established with OpenConnection.
     * @example AxisTransport.h
     */
    void closeConnection ();
    /**
     * Registers the callback function which is used by transport layer to
     * inform the caller that a buffer given to be sent was sent and it can
     * be re-used by the caller.
     *
     * @brief Registers the m_pReleaseBufferCallback callback function.
     * @param pFunct Function pointer to caller's function signature of
     *        this function is defined in Packet.h
     */
    void registerReleaseBufferCallback
	(AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER pFunct);
    /**
     * Sets a predefined transport property to be included in the outgoing
     * message. This transport property is not persistent in the transport
     * layer. These transport properties should be set for each outgoing
     * message.
     *
     * @brief Sets a predefined transport property for outgoing message.
     * @param eType Predefined transport property to be set. See Packet.h
     *        for predefined transport property types.
     * @param pcValue Transport property value to be set.
     */
    void setTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE eType,
			       const char *pcValue);
    /**
     * @brief Gets a predefined transport property in the arrived message
     *
     * @param eType Predefined transport property to get. See Packet.h
     *        for predefined transport property types.
     * @return Value of the transport property if available. Returns null
     *         if unavailable.
     */
    const char *getTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE eType);
    /**
     * Sets any transport property to be included in the outgoing message.
     * This transport property is not persistent in the transport layer.
     * These transport properties should be set for each outgoing message.
     *
     * @brief Sets any transport property.
     * @param pcKey Key for the transport property to be set.
     * @param pcValue Value for transport property to be set.
     */
    void setTransportProperty (const char *pcKey, const char *pcValue);
    /**
     * @brief Gets any transport property in the arrived message
     *
     * @param pcKey The key of the transport property to get.
     * @return Value of the transport property if available. Returns null
     *         if unavailable.
     */
    const char *getTransportProperty (const char *pcKey);
    /**
     * Sets a SOAP attachment to be sent with outgoing message. This
     * attachment is usually the base64 or hex encoded character buffer
     * that is null terminated.
     *
     * @brief Sets a SOAP attachment to be sent with outgoing message
     * @param pcAttachmentid An identifier for the attachment. This identifier also
     *        will go in to the SOAP message so that the recipient will know that
     *        there is an attachemet in the message.
     * @param pcAttachment The attachment. This is usually a null terminated string
     *        encoded to base64 or hex binary.
     */
    void setAttachment (const char *pcAttachmentid, const char *pcAttachment);
    /**
     * Gets an attachment arrived in the inbound message. Usually the SOAP message will
     * contain the information indicating that there is an attachment arrived at the
     * transport. The SOAP message also contain the attachement id which is required
     * to request the transport for the particular attachment.
     *
     * @brief Gets an attachment arrived in the inbound message.
     * @pre To get an attachment the attachment id must be provided. The SOAP message
     *      should contain the attachment id.
     * @param pcAttachmentid Attachment identifier that the caller should find from
     *        the SOAP message and pass in. The transport will use this identifier
     *        to locate the corresponding attachment.
     * @return The attachment if available. Returns null if the attachment
     *         corresponding to the pcAttachmentid is not found.
     */
    const char *getAttachment (const char *pcAttachmentid);
    /**
     * Sets the the remote endpoint for tranport to connect to. This URI
     * depends on the the transport type. 
     *
     * @pre   A caller should use the method getProtocol() to get the type
     *        of the transport. Then the caller should set the endpoint URI
     *        accordingly. For example if the transport is HTTP this
     *        endpoint can be "http://www.xxx.com/"and if the transport is
     *        SMTP this endpoint can be the mail server and port.
     *
     * @brief Sets the remote endpoint for tranport to connect to.
     * @param pcEndpointUri Endpoint URI to connect to.
     */
    void setEndpointUri (const char *pcEndpointUri);
    /**
     * Sets the session id for the transport session. Actual usage of this
     * session id is depend on the implementation of the transport.
     *
     * @brief Sets the session id for the transport session.
     * @param pcSessionId The session id.
     */
    void setSessionId (const char *pcSessionId);
    /**
     * Gets the session id of the transport session sent by the remote end if
     * any. 
     *
     * @brief  Sets the session id for the transport session.
     * @return Session id if available. Returns null otherwise.
     */
    const char *getSessionId ();
    /**
     * Gets the service name of the web service to be invoked. How this
     * service name is found is upto the type of the transport layer. For
     * example HTTP transports will look at the value of http header
     * "soapAction" and extract the service name. Whereas a SMTP transport
     * will look at recepitent address.
     *
     * @brief  Gets the service name of the web service to be invoked.
     * @return Service name if available and null otherwise.
     */
    const char *getServiceName ();
    /**
     * Gets the protocol type of the transport library. The caller should
     * use this function to check the protocol of the transport layer and
     * should use the transport accordingly.
     *
     * @brief Gets the protocol type of the transport library.
     * @return The type of the transport. See AXIS_PROTOCOL_TYPE in Packet.h
     */
    AXIS_PROTOCOL_TYPE getProtocol ();
    /**
     * Gets the sub protocol. The usefulness of this method and the return
     * values depend on the particular implementation. For example HTTP
     * transports should return one of the values defined in enumeration
     * AXIS_HTTP_METHOD. See Packet.h
     *
     * @brief Gets the sub protocol. 
     * @return Type of the sub protocol (Ex: GET, POST, UNSUPPORTED for HTTP).
     */
    int getSubProtocol ();
    /**
     * @brief Forces transport to send any remaining data of the outgoing message.
     * @return Transport status. Two return status are possible. They are,
     *         TRANSPORT_FAILED   - Sending data has failed.
     *         TRANSPORT_FINISHED - Sending finished and successful.
     */
    AXIS_TRANSPORT_STATUS flushOutput ();
  /**
    * Set proxy server and port for transport.
    *
    * Setting the proxy is useful for users who are behind proxies.
    *
    * For some trasports this method may not make sense.
    * Hence this method is not pure .
    * Those trasports that implement this interface, that wish to use proxy, must provide an implementation.
    * Also, the hadling of the proxy is the responsibility of the deriving classes
    *
    * @param pcProxyHost Host name of proxy server
    * @param uiProxyPort Port of proxy server
    */
    void setProxy (const char *pcProxyHost, unsigned int uiProxyPort);

  /**
    * Set transport timeout.
    *
    * @param lSeconds Timeout in seconds
    */
    void setTimeout (const long lSeconds);

  protected:
    //Handler that terminate the event loop and clean up
    //int terminate_handler (HTRequest * request, HTResponse * response,
    //                           void * param, int status);


    //Request object
    HTRequest * m_pRequest;
    //Chunk to hold the result
    HTChunk *m_pResult;
    //data to be posted
    char *m_pcData;
    //proxy
    char *m_pcProxy;
    //getting bytes
    int m_iBytesLeft;
    char *m_pcReceived;

  public:
    // The object that acquires the lock to start event loop
    static LibWWWTransport *m_spLockingObject;

};

#endif

#endif // !defined(AXIS_LIB_WWW_TRANSPORT_H__OF_AXIS_INCLUDED_)
