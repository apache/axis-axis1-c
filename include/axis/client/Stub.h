/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 */
/**
 * @file Stub.hpp
 *
 * Contains the Stub base class that all C++ web service stubs inherit
 * from. The functions in this Stub base class provides the client
 * application some added functionality to manipulate the SOAP messages.
 */
#ifndef STUB_INCLUDED
#define STUB_INCLUDED

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE C APIS.                                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifdef __cplusplus
 extern "C" {
#endif


#include <stdarg.h>
#include <axis/client/Call.h>

/**
 * @class Stub
 *
 * @brief This is the client Stub base class to be inherited by all stub
 *        classes genarated by WSDL2WS tool. This class acts as the interface
 *        between the users and the Axis C++ engine (client side). Programmer
 *        can use the API defined here to enrich the client application
 *        functionality. Setting transport properties, setting SOAP headers,
 *        setting connection timeout and specifying a proxy on the client stub
 *        is facilitated with this interface.
 *
 */
/**
 * Constructor.
 *
 * @param pcEndPointURI End point URI of the service to connect to.
 *                       e.g. http://localhost:8080/axis/services/echo
 * @param eProtocol The protocol that this stub should use to communicate
 *        with the endpoint. See AXIS_PROTOCOL_TYPE in GDefine.h for
 *        possible values for eProtocol.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscStubCreate(const char * pcEndPointURI, 
	AXISC_PROTOCOL_TYPE eProtocol);

/**
 * Destructor.
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubDestroy(AXISCHANDLE stub);

/**
 * Set end point of service to connect to.
 *
 * @param pcEndPointURI End point URI of the service to connect to.
 *                       e.g. http://localhost:8080/axis/services/echo
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetEndPoint(AXISCHANDLE stub, const char * pcEndPointURI);

/**
 * Set transport property.
 *
 * Handling the semantics of the headers is up to the user.
 * The user has to make sure that the key:value paires passed to this method
 * would make sense at transport level.
 * The Stub class does not validate the key value paires to see if the properties
 * make sense to the undelying transport.
 *
 * Some example transport properties:
 * <BR>  For HTTP: "Accept-Language: da, en-gb;q=0.8, en;q=0.7"
 * <BR>  For HTTP: "Cookie: sessiontoken=123345456;"
 * <BR>  For SMTP: "Reply-To: user@apache.org"
 *
 * @param pcKey Header name e.g. "Accept-Language".
 *              Note that the key is not tested for uniqueness.
 *              One can set several values to the same key and they all will
 *              appear in the outgoing transport header.
 *              e.g. If the method is called twise with (k,v1) and (k,v2)
 *              both k:v1 and k:v2 will appear in transport header as
 *              seperate properties.
 *              The exception to this is "Cookie" where multiple cookie values will only result in one "Cookie:" header being sent as is correct for HTTP.
 * @param pcValue Header value e.g. "da, en-gb;q=0.8, en;q=0.7"
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetTransportProperty(AXISCHANDLE stub, const char * pcKey, 
	const char * pcValue);

/**
 * Get a transport property.
 *
 * Returns the value of a transport property based on a key.
 *
 * @param key the property's name to search for
 * @param response set to true searches the response message for the property
 *                 set to false searches the send message for the property
 * @return the value of the property or NULL if it was not found.
 */
AXISC_STORAGE_CLASS_INFO
const char * axiscStubGetTransportProperty(AXISCHANDLE stub, const char * key, 
	AxiscBool response);

/**
 * Iterator initiatior for transport property keys
 *
 * This method must be called first to initiate access to the list of
 * transport property keys. If you initialise e.g. response then ensure
 * that you call this method for outgoing message too if you want the
 * outgoing message in future calls.
 *
 *
 * @param response  whether the response or outgoing message is being used.
 * @return First transport property key. If there are no transport
 * properties set, returns NULL.
 */
AXISC_STORAGE_CLASS_INFO
const char * axiscStubGetFirstTransportPropertyKey(AXISCHANDLE stub, AxiscBool response);

/**
 * Iterator for transport property keys
 *
 * getFirstTransportPropertyKey() method must have been called at least once
 * before this method is called. If not behaviour is undefined.
 *
 * This method advances the iterator by one position.
 * Repeated calls always retuen the next value.
 *
 * @param response whether the response or outgoing message should be used
 * @return Next transport property key. If there are no transport
 * properties set or if iterator is at the end of the list, returns NULL.
 */
AXISC_STORAGE_CLASS_INFO
const char * axiscStubGetNextTransportPropertyKey(AXISCHANDLE stub, AxiscBool response);

/**
 * Accessor for transport property keys.
 *
 * This method gives access to the key corresponding to the transport key
 * currently being pointed by transport property key iterator.
 *
 * getFirstTransportPropertyKey() method must have been called at least once
 * before this method is called. If not behaviour is undefined.
 *
 * This method does not advance the iterator.
 * Repeated calls always retuen the same key unless
 * getNextTransportPropertyKey() is called in between.
 *
 * @param response  whether the response or outgoing message is being used.
 * @return Current transport property key. If there are no transport
 * properties set or if iterator is at the end of the list, returns NULL.
 */
AXISC_STORAGE_CLASS_INFO
const char * axiscStubGetCurrentTransportPropertyKey(AXISCHANDLE stub, AxiscBool response);

/**
 * Accessor for transport property values.
 *
 * This method gives access to the value corresponding to the transport key
 * currently being pointed by transport property key iterator.
 * As keys and values are treated as pairs, access to the value field is
 * based on the access to the key field.
 *
 * getFirstTransportPropertyKey() method must have been called at least once
 * before this method is called. It must be called with the same "response"
 * value as used here. If not behaviour is undefined.
 *
 * This method does not advance the iterator.
 * Repeated calls always retuen the same value unless
 * getNextTransportPropertyKey() is called in between.
 *
 * @param response whether the response or outgoing message should be used
 * @return Current transport property value. If there are no transport
 * properties set or if iterator is at the end of the list, returns NULL.
 */
AXISC_STORAGE_CLASS_INFO
const char * axiscStubGetCurrentTransportPropertyValue(AXISCHANDLE stub, AxiscBool response);

/**
 * Deletes the transport property key:value pair currently pointed to by
 * the iterator.
 * @param response true if it's the response property or false for the request
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubDeleteCurrentTransportProperty(AXISCHANDLE stub, AxiscBool response);

/**
 * Deletes the given occurance of the transport property key:value pair
 * corresponding to the given key.
 *
 * This method does not advance the iterator in line with the deletes done.
 * In case you want to access the transport properties after using this
 * method, it is advisable to reinitialize the iterator using
 * getFirstTransportPropertyKey();
 * However you can use this method despite where the iterator is
 * pointing currently.
 *
 * NOTE: This method is used to delete individual cookies e.g. deleteTransportProperty("myCookie") will delete the cookie "myCookie" only.
 * This method can also be used to delete all Cookies by doing deleteTransportProperty("Cookie").
 *
 * @param pcKey Key of the transport property key:value pair to be deleted
 *              If the given key is not set currently, nothing will happen.
 * @param uiOccurance Which occerance of the key to be deleted, because
 *                    there can be multiple values for the same key.
 *                    Default is to delete the first occurance.
 *                    Count starts from 1.
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubDeleteTransportProperty(AXISCHANDLE stub, char * pcKey, 
	unsigned int uiOccurance);

/**
 * Sets a property that can be accessed from a handler.
 *
 * @param name The name of the property
 * @param value The value of the property
 * @param len The length of the value
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetHandlerProperty(AXISCHANDLE stub, AxiscChar * name, 
	void * value, 
	int len);

/**
 * Create and add a SOAP header block to the Stub.
 *
 * This will create a header block that would look like the following when
 * serialized:
 * \verbatim
<th:TestHeader xmlns:th="http://ws.apache.org/axisCppTest/">
</th:TestHeader>
\endverbatim
 *
 * User must use the IHeaderBlock pointer returned and fill in the header structure.
 * e.g. To make the SOAP header look like
 * \verbatim
<SOAP-ENV:Header>
<th:TestHeader xmlns:th="http://ws.apache.org/axisCppTest/">
<Credentials>
<username>Test User</username>
<password>Test Password</password>
</Credentials>
</th:TestHeader>
</SOAP-ENV:Header>
\endverbatim
 * the following code segment could be used
 * <code>
 *
 * IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader",
 *                                   "http://ws.apache.org/axisCppTest/",
 *                                   "th");
 *
 *
 *  //create parent node
 *
 *  BasicNode *parentNode = phb->createChild(ELEMENT_NODE);
 *
 *  parentNode->setLocalName("Credentials");
 *
 *
 *  //create child node
 *
 *  BasicNode *childNode = phb->createChild(ELEMENT_NODE);
 *
 *  childNode->setLocalName("username");
 *
 *
 *  //create char node for value
 *
 *  BasicNode *valueNode = phb->createChild(CHARACTER_NODE);
 *
 *  valueNode->setValue("Test User");
 *
 *
 *  //buld node tree
 *
 *  childNode->addChild(valueNode);
 *
 *  parentNode->addChild(childNode);
 *
 *
 *  //add another node set
 *
 *  childNode = phb->createChild(ELEMENT_NODE);
 *
 *  childNode->setLocalName("password");
 *
 *
 *  valueNode = phb->createChild(CHARACTER_NODE);
 *
 *  valueNode->setValue("Test Password");
 *
 *
 *  childNode->addChild(valueNode);
 *
 *  parentNode->addChild(childNode);
 *
 *
 *  phb->addChild(parentNode);
 * </code>
 *
 * @param pachLocalName Local tag name of the SOAP header. e.g. TestHeader
 * @param pachPrefix Prefix to be used in XML represenation of SOAP header
 *                   e.g. th
 * @param pachUri Namespace URI to be used in SOAP header.
e.g http://ws.apache.org/axisCppTestHeader/
 *
 * @return Pointer to the creater SOAP header block.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscStubCreateSOAPHeaderBlock(AXISCHANDLE stub, AxiscChar * pachLocalName, 
	AxiscChar * pachUri, 
	AxiscChar * pachPrefix);

/**
 * Iterator initiatior for SOAP header blocks
 *
 * This method must be called first to initiate access to the list of
 * SOAP header blocks.
 *
 * @return First SOAP header block pointer. If there are no SOAP header
 * blocks set, returns NULL.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscStubGetFirstSOAPHeaderBlock(AXISCHANDLE stub);

/**
 * Iterator for SOAP header blocks
 *
 * getFirstSOAPHeaderBlock() method must have been called at least once
 * before this method is called. If not behaviour is undefined.
 *
 * This method advances the iterator by one position.
 * Repeated calls always retuen the next value.
 *
 * @return Next SOAP header block pointer. If there are no SOAP header
 * blocks set or if iterator is at the end of the list, returns NULL.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscStubGetNextSOAPHeaderBlock(AXISCHANDLE stub);

/**
 * Accessor for SOAP header blocks
 *
 * This method gives access to the SOAP header block pointer corresponding
 * to the SOAP header block currently being pointed by SOAP header blocks
 * iterator.
 *
 * getFirstSOAPHeaderBlock() method must have been called at least once
 * before this method is called. If not behaviour is undefined.
 *
 * This method does not advance the iterator.
 * Repeated calls always retuen the same key unless
 * getNextSOAPHeaderBlock() is called in between.
 *
 * @return Current SOAP header block pointer. If there are no SOAP header
 * block set or if iterator is at the end of the list, returns NULL.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscStubGetCurrentSOAPHeaderBlock(AXISCHANDLE stub);

/**
 * Deletes the SOAP header block currently pointed to by
 * the iterator.
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubDeleteCurrentSOAPHeaderBlock(AXISCHANDLE stub);

/**
 * Deletes the given SOAP header block pointer from the current list of
 * SOAP header blocks.
 *
 * This method does a pointer comparison. It does not compare the contents
 * within objects.
 * Hence it is expected that either the pointer returned by the
 * create method or by one of the iterator methods would be used with
 * this method.
 *
 * This method does not advance the iterator in line with the deletes done.
 * In case you want to access the SOAP header  blocks after using this
 * method, it is advisable to reinitialize the iterator using
 * getFirstSOAPHeaderBlock();
 * However you can use this method despite where the iterator is
 * pointing currently.
 *
 * @param pHeaderBlock Pointer of the header block to be deleted.
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubDeleteSOAPHeaderBlock(AXISCHANDLE stub, AXISCHANDLE pHeaderBlock);

/**
 * Set proxy server and port for transport.
 *
 * @param pcProxyHost Host name of proxy server
 * @param uiProxyPort Port of proxy server
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetProxy(AXISCHANDLE stub, const char * pcProxyHost, 
	unsigned int uiProxyPort);

/**
 * Set transport timeout.
 *
 * @param lSeconds Timeout in seconds.
 *                 If lSeconds is 0, then the transport will assume no
 *                 timeout. Hence you want to reset a timeout already set
 *                 use 0.
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetTransportTimeout(AXISCHANDLE stub, long lSeconds);

/**
 * Get the status of the stub to see any error situation
 */
AXISC_STORAGE_CLASS_INFO
int axiscStubGetStatus(AXISCHANDLE stub);

/**
 * Set whether to Maintain session with service ot not.
 * @param bSession - true if session should be maintained. False otherwise.
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetMaintainSession(AXISCHANDLE stub, AxiscBool bSession);

/**
 * Set transport protocol to be used by the transport.
 * @param eProtocol - protocol to use
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetTransportProtocol(AXISCHANDLE stub, AXISC_PROTOCOL_TYPE eProtocol);

/**
 * Get transport protocol being used by the transport.
 * @return Protocol used by transport
 */
AXISC_STORAGE_CLASS_INFO
AXISC_PROTOCOL_TYPE axiscStubGetTransportProtocol(AXISCHANDLE stub);

/**
 * Sets the username to be used for basic authentication
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetUsername(AXISCHANDLE stub, const char * pcUsername);

/**
 * Sets the password to be used for basic authentication
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetPassword(AXISCHANDLE stub, const char * pcPassword);

/**
 * Sets the username to be used for Proxy authentication
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetProxyUsername(AXISCHANDLE stub, const char * pcProxyUsername);

/**
 * Sets the password to be used for Proxy authentication
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetProxyPassword(AXISCHANDLE stub, const char * pcProxyPassword);

/**
 * Gets the username used for Proxy authentication
 */
AXISC_STORAGE_CLASS_INFO
const char * axiscStubGetProxyUsername(AXISCHANDLE stub);

/**
 * Gets the password used for Proxy authentication
 */
AXISC_STORAGE_CLASS_INFO
const char * axiscStubGetProxyPassword(AXISCHANDLE stub);

/**
 * Call object of the Stub. This is the point of access to the internals
 * of the Axis engine.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscStubGetCall(AXISCHANDLE stub);

/**
 * Creates an ISoapAttachment which represents an attachment. The ISoapAttachment should be passed as
 * an attachmment parameter to a web service. The storage associated with the ISoapAttachment will be
 * automatically deleted by Axis C++ if it is passed as a parameter to a web service.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscStubCreateSoapAttachment(AXISCHANDLE stub);

/**
 * Set SSL configuration properties.
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetSecure(AXISCHANDLE stub, char * pszArguments, 
	... );

/**
 * Set pointer to exception handler function for stub object.
 * This function was added in support of the c-Binding implementation.
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetCExceptionHandler(AXISCHANDLE stub, void * pExceptionHandler);

/**
 * Get pointer to exception handling function for call object.
 * This function was added in support of the c-Binding implementation.
 */
AXISC_STORAGE_CLASS_INFO
void * axiscStubGetCExceptionHandler(AXISCHANDLE stub);

/**
 * Apply user set preferences to each call made on the Stub object.
 * This method is required because Axis engine holds only part of the state
 * with refereance to subsequent calls on the same Stub object.
 * Foxing this approach would make the engine much more efficient.
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubApplyUserPreferences(AXISCHANDLE stub);

/**
 * Apply SSL configuration properties.
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubIncludeSecure(AXISCHANDLE stub);

/**
 * Set SOAP Headers stored in m_vSOAPHeaderBlock vector.
 * Called by applyUserPreferences for each and every method invocation.
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetSOAPHeaders(AXISCHANDLE stub);

/**
 * Set Authorization header for Proxy authentication
 */
AXISC_STORAGE_CLASS_INFO
void axiscStubSetProxyAuthorizationHeader(AXISCHANDLE stub);


#ifdef __cplusplus
 }
#endif

#endif /* STUB_INCLUDED */
