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
 * @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/31 samisa
 * Added setProxy
 */

/*
 * Revision 1.2  2004/06/08 samisa
 * Added setTimeout
 */

#if !defined(AXIS_SOAPTRANSPORT_H__OF_AXIS_INCLUDED_)
#define AXIS_SOAPTRANSPORT_H__OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>

/**
 * @file SOAPTransport.h
 *
 * Contains the interfaces that any transport layer should implemnt in order
 * for using in Axis. The implementation should be at lease thread safe. The
 * Axis Engine creates a separate transport object for each thread.
 */

#ifdef __cplusplus

/**
 * @interface AxisIOStream
 *
 * Interface of the input/output stream of Axis transport. The use of this
 * interface is to avoid the parser being provided the full functionalies
 * of SOAPTransport interface
 *
 * @brief Interface of the input/output stream of Axis transport. ISOAPTransport is
 *        derived from this interface
 */

AXIS_CPP_NAMESPACE_START

typedef enum
{
    TRANSPORT_FINISHED=0,
    TRANSPORT_IN_PROGRESS,
    TRANSPORT_FAILED
} AXIS_TRANSPORT_STATUS;

typedef enum
{
    AXIS_HTTP_GET,
    AXIS_HTTP_POST,
    AXIS_HTTP_UNSUPPORTED
} AXIS_HTTP_METHOD;

// Samisa: This was in the removed include/axis/server/Packet.hpp
// This is required by Apache transports in src/server/apache*
// I added this here as I felt this is the most suitable place for it.
typedef struct
{
    const void* pBufferId;
    const char* pcBuffer;
} BufferInfo;

// Samisa : This too was defined in include/axis/server/Packet.hpp
// and used by Apache transports in src/server/apache*
typedef struct
{
    char* headername;
    char* headervalue;
} Ax_header;


// Samisa: NO_OF_SERIALIZE_BUFFERS too was defined in include/axis/server/Packet.hpp
// As that header has been removed I put it here.
// This is used by Apache transport classes in ser/srver/apache*
#define NO_OF_SERIALIZE_BUFFERS 20

/*
 * This function is provided by the Axis Engine. 
 * Called by transport module when it needs to say that
 * a message buffer passed to it is no longer being used by the transport 
 * and can be re-used by the 
 * Axis engine.This function should be called for each buffer 
 * if AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES
 * returned TRANSPORT_IN_PROGRESS.
 * @param 
 *        1st - buffer that Axis gave to the transport layer
 *        2nd - buffer id    which uniquely identifies the buffer
 *        3rd - Ax_soapstream object which act like a thread id
 */
typedef void (AXISCALL * AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER)
(const char*, const void*);
 
class AxisIOStream
{
public:
    /**
     * Sends a buffer to the transport layer. A Caller may call this method
     * multiple times to send several buffers. Its upto the transport to
     * decide how they are sent (chunked/unchunked etc). But should return the
     * appropriate status code.
     *
     * @brief Sends a buffer to the transport layer.
     * @pre   1. Transport connection should have been established by calling
     *           Openconnection of the SOAPTransport's implementaion.
     *        2. If the implementaion of SOAPTransport intends to accumulate
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
    virtual AXIS_TRANSPORT_STATUS sendBytes(const char* pcSendBuffer, 
		const void* pBufferid)=0;
    /**
     * Gets a part of or full SOAP message. A Caller may call this method
     * multiple times to get parts of the SOAP message until the function
     * return status says that no more data available.
     *
     * @brief Gets a part of or full SOAP message.
     * @pre   Transport connection should have been established by calling
     *        Openconnection of the SOAPTransport's implementaion.
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
    virtual AXIS_TRANSPORT_STATUS getBytes(char* pcBuffer, int* piRetSize)=0;
};

/**
 * @interface SOAPTransport
 *
 * Interface of any Axis transport. Every transpor layer should implement this
 * interface in order to be used with Axis Engine. This interface contain the
 * functionalities independent of the type of transport (whether HTTP, SMTP,
 * etc).
 *
 * @brief Interface of any Axis transport layer.
 *
 */
AXIS_CPP_NAMESPACE_END
AXIS_CPP_NAMESPACE_START
class SOAPTransport : public AxisIOStream
{
public:
    virtual ~SOAPTransport(){};
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
    virtual int openConnection()=0;
    /**
     * @brief Closes the connection established with OpenConnection.
     * @example AxisTransport.h
     */
    virtual void closeConnection()=0;
    
    /**
     * Sets a predefined transport property to be included in the outgoing
     * message. This transport property is not persistent in the transport
     * layer. These transport properties should be set for each outgoing
     * message.
     *
     * @brief Sets a predefined transport property for outgoing message.
     * @param eType Predefined transport property to be set.
     *        for predefined transport property types.
     * @param pcValue Transport property value to be set.
     */
    virtual void setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE eType,
    const char* pcValue)=0;
    /**
     * @brief Gets a predefined transport property in the arrived message
     *
     * @param eType Predefined transport property to get.
     *        for predefined transport property types.
     * @return Value of the transport property if available. Returns null
     *         if unavailable.
     */
    virtual const char* getTransportProperty(
    AXIS_TRANSPORT_INFORMATION_TYPE eType)=0;
    /**
     * Sets any transport property to be included in the outgoing message.
     * This transport property is not persistent in the transport layer.
     * These transport properties should be set for each outgoing message.
     *
     * @brief Sets any transport property.
     * @param pcKey Key for the transport property to be set.
     * @param pcValue Value for transport property to be set.
     */
    virtual void setTransportProperty(const char* pcKey, const char* pcValue)=0;
    /**
     * @brief Gets any transport property in the arrived message
     *
     * @param pcKey The key of the transport property to get.
     * @return Value of the transport property if available. Returns null
     *         if unavailable.
     */
    virtual const char* getTransportProperty(const char* pcKey)=0;
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
    virtual void setAttachment(const char* pcAttachmentid, const char* pcAttachment)=0;
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
    virtual const char* getAttachment(const char* pcAttachmentid)=0;
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
    virtual void setEndpointUri(const char* pcEndpointUri)=0;
    /**
     * Sets the session id for the transport session. Actual usage of this
     * session id is depend on the implementation of the transport.
     *
     * @brief Sets the session id for the transport session.
     * @param pcSessionId The session id.
     */
    virtual void setSessionId(const char* pcSessionId)=0;
    /**
     * Gets the session id of the transport session sent by the remote end if
     * any. 
     *
     * @brief  Sets the session id for the transport session.
     * @return Session id if available. Returns null otherwise.
     */
    virtual const char* getSessionId()=0;
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
    virtual const char* getServiceName()=0;
    /**
     * Gets the protocol type of the transport library. The caller should
     * use this function to check the protocol of the transport layer and
     * should use the transport accordingly.
     *
     * @brief Gets the protocol type of the transport library.
     * @return The type of the transport. See AXIS_PROTOCOL_TYPE
     */
    virtual AXIS_PROTOCOL_TYPE getProtocol()=0;

    /**
     * Sets the protocol to be used by the transport library. 
     *
     * @param eProtocol - protocol to be used by transport.
     *                    See AXIS_PROTOCOL_TYPE in GDefine.hpp
     * @return AXIS_SUCCESS if protocol is supported. Else AXIS_FAIL.
     */
    virtual int setProtocol(AXIS_PROTOCOL_TYPE eProtocol)=0;

    /**
     * Gets the sub protocol. The usefulness of this method and the return
     * values depend on the particular implementation. For example HTTP
     * transports should return one of the values defined in enumeration
     * AXIS_HTTP_METHOD.
     *
     * @brief Gets the sub protocol. 
     * @return Type of the sub protocol (Ex: GET, POST, UNSUPPORTED for HTTP).
     */
    virtual int getSubProtocol()=0;
    /**
     * @brief Forces transport to send any remaining data of the outgoing message.
     * @return Transport status. Two return status are possible. They are,
     *         TRANSPORT_FAILED   - Sending data has failed.
     *         TRANSPORT_FINISHED - Sending finished and successful.
     */
    virtual AXIS_TRANSPORT_STATUS flushOutput()=0;
  /**
    * Set proxy server and port for transport.
    *
    * Setting the proxy is useful for users who are behind proxies.
    *
    * For some trasports this method may not make sense.
    * Hence this method is not pure virtual.
    * Those trasports that implement this interface, that wish to use proxy, must provide an implementation.
    * Also, the hadling of the proxy is the responsibility of the deriving classes
    *
    * @param pcProxyHost Host name of proxy server
    * @param uiProxyPort Port of proxy server
    */
    virtual void setProxy(const char* pcProxyHost, unsigned int uiProxyPort) {}

  /**
    * Set transport timeout.
    *
    * @param lSeconds Timeout in seconds
    */
    virtual void setTimeout(const long lSeconds) = 0;
    
    /**
    * Iterator initiatior for trasport property keys
    *
    * This method must be called first to initiate access to the list of 
    * transport property keys.
    *
    * @return First transport property key. If there are no trasport 
    * properties set, returns NULL.
    */
    virtual const char* getFirstTrasportPropertyKey() { return 0; };

  /**
    * Iterator for trasport property keys
    *
    * getFirstTrasportPropertyKey() method must have been called at least once
    * before this method is called. If not behaviour is undefined.
    *
    * This method advances the iterator by one position.
    * Repeated calls always retuen the next value.
    *
    * @return Next transport property key. If there are no trasport 
    * properties set or if iterator is at the end of the list, returns NULL.
    */
    virtual const char* getNextTrasportPropertyKey() { return 0; };

  /**
    * Accessor for trasport property keys.
    *
    * This method gives access to the key corresponding to the trasport key
    * currently being pointed by trasport property key iterator.
    *
    * getFirstTrasportPropertyKey() method must have been called at least once
    * before this method is called. If not behaviour is undefined.
    *
    * This method does not advance the iterator.
    * Repeated calls always retuen the same key unless 
    * getNextTrasportPropertyKey() is called in between.
    *
    * @return Current transport property key. If there are no trasport 
    * properties set or if iterator is at the end of the list, returns NULL.
    */
    virtual const char* getCurrentTrasportPropertyKey() { return 0; };
    
  /**
    * Accessor for trasport property values.
    *
    * This method gives access to the value corresponding to the trasport key
    * currently being pointed by trasport property key iterator.
    * As keys and values are treated as paires, access to the value field is 
    * based on the access to the key field.
    *
    * getFirstTrasportPropertyKey() method must have been called at least once
    * before this method is called. If not behaviour is undefined.
    *
    * This method does not advance the iterator.
    * Repeated calls always retuen the same value unless 
    * getNextTrasportPropertyKey() is called in between.
    *
    * @return Current transport property value. If there are no trasport 
    * properties set or if iterator is at the end of the list, returns NULL.
    */
    virtual const char* getCurrentTrasportPropertyValue() { return 0; };

  /**
    * Deletes the trasport property key:value pair currently pointed to by 
    * the iterator.
    */
    virtual void deleteCurrentTrasportProperty() {};

  /**
    * Deletes the given occerance of the trasport property key:value pair
    * corresponding to the given key.
    *
    * This method does not advance the iterator in line with the deletes done.
    * In case you want to access the trasport properties after using this
    * method, it is advisable to reinitialize the iterator using
    * getFirstTrasportPropertyKey();
    * However you can use this method despite where the iterator is 
    * pointing currently.
    *
    * @param pcKey Key of the trasport property key:value pair to be deleted
    *              If the given key is not set currently, nothing will happen.
    * @param uiOccurance Which occerance of the key to be deleted, because 
    *                    there can be multiple values for the same key. 
    *                    Default is to delete the first occurance.
    *                    Count starts from 1.
    */
    virtual void deleteTrasportProperty(char* pcKey, unsigned int uiOccurance = 1) {};
    
  /**
    * Set whether to Maitain session with service ot not.
    * @param bSession - true is session should be maintained. False otherwise.
    */
    virtual void setMaintainSession(bool bSession) {};

protected:
    /**
     * Outgoing endpoint URI
     */
    char* m_pcEndpointUri;
    /**
     * Release buffer callback function registered. Usefull if the transport
     * is accumulating buffers to be sent later. Ex: non-chunked behavior
     * of http transports
     */ 
    AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER m_pReleaseBufferCallback;
 
    AXIS_PROTOCOL_TYPE m_eProtocolType;  

};

AXIS_CPP_NAMESPACE_END

#endif

#endif // !defined(AXIS_SOAPTRANSPORT_H__OF_AXIS_INCLUDED_)
