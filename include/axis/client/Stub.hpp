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
 */

 /**
 * @file Stub.h
 *
 * Contains the Stub base class that all C++ web service stubs inherit
 * from. The functions in this Stub base class provides the client
 * application some added functionality to manipulate the SOAP messages. 
 */
 
/*
 * Revision 1.1  2004/05/31 samisa
 * Added setProxy
 */

/*
 * Revision 1.2  2004/05/31 roshan
 * Added calling conventions
 */

/*
 * Revision 1.3  2004/06/01 roshan
 * Added setSOAPMethodAttribute
 */

/*
 * Revision 1.4  2004/06/08 samisa
 * Added setTransportTimeout
 */

/*
 * Revision 1.5  2004/06/10 samisa
 * Added doxygen comments to help autobuild API docs
 */

/*
 * Revision 1.6  2004/06/13 roshan
 * Added doxygen comments to help autobuild API docs
 */

/*
 * Revision 1.13  2004/06/13 susantha
 * Added support for writing C web services and handlers
 */

#if !defined(_STUB_H____OF_AXIS_INCLUDED_)
#define _STUB_H____OF_AXIS_INCLUDED_

#include <axis/client/Call.hpp>
#include <axis/IAttribute.hpp>
#include <vector>

using namespace std;

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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */

AXIS_CPP_NAMESPACE_START

class STORAGE_CLASS_INFO Stub
{
  public:
  /**
    * Constructor.
    * 
    * @param pcEndPointURI End point URI of the service to connect to. 
    *                       e.g. http://localhost:8080/axis/services/echo
    * @param eProtocol The protocol that this stub should use to communicate
    *        with the endpoint. See AXIS_PROTOCOL_TYPE in GDefine.h for
    *        possible values for eProtocol.
    */
    Stub(const char *pcEndPointURI, AXIS_PROTOCOL_TYPE eProtocol);

  /**
   * Default Constructor.
   */
   
  /**
    * Destructor.
    */
    virtual ~Stub();

  /**
    * Set end point of service to connect to.
    * 
    * @param pcEndPointURI End point URI of the service to connect to. 
    *                       e.g. http://localhost:8080/axis/services/echo
    */

    void AXISCALL setEndPoint(const char *pcEndPointURI);

  /**
    * Set transport property.
    *
    * Handling the semantics of the headers is up to the user.
    * The user has to make sure that the key:value paires passed to this method 
    * would make sense at trasport level.
    * The Stub class does not validate the key value paires to see if the properties
    * make sense to the undelying trasport.
    * 
    * Some example trasport properties:
    * <BR>  For HTTP: "Accept-Language: da, en-gb;q=0.8, en;q=0.7"
    * <BR>  For SMTP: "Reply-To: user@apache.org" 
    * 
    * @param pcKey Header name e.g. "Accept-Language". 
    *              Note that the key is not tested for uniqueness.
    *              One can set several values to the same key and they all will
    *              appear in the outgoing trasport header.
    *              e.g. If the method is called twise with (k,v1) and (k,v2) 
    *              both k:v1 and k:v2 will appear in trasport header as 
    *              seperate properties.
    * @param pcValue Header value e.g. "da, en-gb;q=0.8, en;q=0.7"
    */
    void AXISCALL setTransportProperty(const char *pcKey, const char *pcValue);

  /**
    * Iterator initiatior for trasport property keys
    *
    * This method must be called first to initiate access to the list of 
    * transport property keys.
    *
    * @return First transport property key. If there are no trasport 
    * properties set, returns NULL.
    */
    char* getFirstTrasportPropertyKey();

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
    char* getNextTrasportPropertyKey();

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
    char* getCurrentTrasportPropertyKey();
    
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
    char* getCurrentTrasportPropertyValue();

  /**
    * Deletes the trasport property key:value pair currently pointed to by 
    * the iterator.
    */
    void deleteCurrentTrasportProperty();

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
    void deleteTrasportProperty(char* pcKey, unsigned int uiOccurance = 1);

  /**
    * Sets a property that can be accessed from a handler.
	*
	* @param name The name of the property
	* @param value The value of the property
	* @param len The length of the value
	*/
    void setHandlerProperty(AxisChar* name, void* value, int len);

  /**
    * Create and add a SOAP header block to the Stub.
    * 
    * This will create a header block that would look like the following when 
    * serialized:
    * <PRE>
    *   <th:TestHeader xmlns:th="http://ws.apache.org/axisCppTest/">
    *   </th:TestHeader>
    * </PRE>
    *
    * User must use the IHeaderBlock pointer returned and fill in the header structure.
    * e.g. To make the SOAP header look like
    * <PRE>
    * <SOAP-ENV:Header>
    *   <th:TestHeader xmlns:th="http://ws.apache.org/axisCppTest/">
    *       <Credentials>
    *            <username>Test User</username>
    *            <password>Test Password</password>
    *       </Credentials>
    *   </th:TestHeader>
    * </SOAP-ENV:Header>
    * </PRE>
    * the following code segment coule be used
    * <PRE>
    *  IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader", "th",
    *                                   "http://ws.apache.org/axisCppTest/");
    *  //create parent node
    *  BasicNode *parentNode = phb->createChild(ELEMENT_NODE);
    *  parentNode->setLocalName("Credentials");
    *  //create child node
    *  BasicNode *childNode = phb->createChild(ELEMENT_NODE);
    *  childNode->setLocalName("username");
    *  //create char node for value
    *  BasicNode *valueNode = phb->createChild(CHARACTER_NODE);
    *  valueNode->setValue("Test User");
    *  //buld node tree
    *  childNode->addChild(valueNode);
    *  parentNode->addChild(childNode);
    *
    *  //add another node set
    *  childNode = phb->createChild(ELEMENT_NODE);
    *  childNode->setLocalName("password");
    *
    *  valueNode = phb->createChild(CHARACTER_NODE);
    *  valueNode->setValue("Test Password");
    *
    *  childNode->addChild(valueNode);
    *  parentNode->addChild(childNode);
    *
    *  phb->addChild(parentNode);
    * </PRE>
    *
    * @param pachLocalName Local tag name of the SOAP header. e.g. TestHeader
    * @param pachPrefix Prefix to be used in XML represenation of SOAP header
    *                   e.g. th
    * @param pachUri Namespace URI to be used in SOAP header.
                     e.g http://ws.apache.org/axisCppTestHeader/
    *
    * @return Pointer to the creater SOAP header block.
    */
    IHeaderBlock * AXISCALL createSOAPHeaderBlock(AxisChar * pachLocalName,
                     AxisChar * pachUri);

  /**
    * Iterator initiatior for SOAP header blocks
    *
    * This method must be called first to initiate access to the list of 
    * SOAP header blocks.
    *
    * @return First SOAP header block pointer. If there are no SOAP header
    * blocks set, returns NULL.
    */
    IHeaderBlock* getFirstSOAPHeaderBlock();

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
    IHeaderBlock* getNextSOAPHeaderBlock();

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
    IHeaderBlock* getCurrentSOAPHeaderBlock();
    
  /**
    * Deletes the SOAP header block currently pointed to by 
    * the iterator.
    */
    void deleteCurrentSOAPHeaderBlock();

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
    void deleteSOAPHeaderBlock(IHeaderBlock* pHeaderBlock);

  /**
    * Set proxy server and port for transport.
    *
    * @param pcProxyHost Host name of proxy server
    * @param uiProxyPort Port of proxy server
    */
    void setProxy(const char* pcProxyHost, unsigned int uiProxyPort);

  /**
    * Sets a Attribute to the SOAPMethod, using the given Attribute data.
    *
    * @param pLocalname The local name of the Attribute.
    * @param pPrefix The prefix of the Attribute.
    * @param pValue The value of the Attribute.
    */
    void setSOAPMethodAttribute(const AxisChar *pLocalname, const AxisChar *pPrefix, const AxisChar *pValue);

  /**
    * Sets a Attribute to the SOAPMethod, using the given Attribute data.
    *
    * @param pLocalname The local name of the Attribute.
    * @param pPrefix The prefix of the Attribute.
    * @param pUri The namespace uri of the Attribute.
    * @param pValue The value of the Attribute.
    */
    void setSOAPMethodAttribute(const AxisChar *pLocalname, const AxisChar *pPrefix, const AxisChar* pUri, const AxisChar *pValue);
  
  /**
    * Iterator initiatior for SOAP method attributes
    *
    * This method must be called first to initiate access to the list of 
    * SOAP method attributes.
    *
    * @return First SOAP method attribute pointer. If there are no SOAP method 
    * attributes set, returns NULL.
    */
    IAttribute* getFirstSOAPMethodAttribute();

  /**
    * Iterator for SOAP method attributes
    *
    * getFirstSOAPMethodAttribute() method must have been called at least once
    * before this method is called. If not behaviour is undefined.
    *
    * This method advances the iterator by one position.
    * Repeated calls always retuen the next value.
    *
    * @return Next SOAP method attribute pointer. If there are no SOAP method 
    * attributes set or if iterator is at the end of the list, returns NULL.
    */
    IAttribute* getNextSOAPMethodAttribute();

  /**
    * Accessor for SOAP method attributes
    *
    * This method gives access to the SOAP method attribute pointer corresponding
    * to the SOAP method attribute currently being pointed by SOAP method 
    * attributes iterator.
    *
    * getFirstSOAPMethodAttribute() method must have been called at least once
    * before this method is called. If not behaviour is undefined.
    *
    * This method does not advance the iterator.
    * Repeated calls always retuen the same key unless 
    * getNextSOAPMethodAttribute() is called in between.
    *
    * @return Current SOAP method attribute pointer. If there are no SOAP method 
    * attribute set or if iterator is at the end of the list, returns NULL.
    */
    IAttribute* getCurrentSOAPMethodAttribute();
    
  /**
    * Deletes the SOAP method attribute currently pointed to by 
    * the iterator.
    */
    void deleteCurrentSOAPMethodAttribute();

  /**
    * Deletes the given occerance of the SOAP method attribute from
    * the current list of SOAP method attributes
    *
    * This method does a pointer comparison. It does not compare the contents
    * within objects.
    * Hence it is expected that either the pointer returned by the 
    * create method or by one of the iterator methods would be used with 
    * this method.
    *
    * This method does not advance the iterator in line with the deletes done.
    * In case you want to access the SOAP method attributes after using this
    * method, it is advisable to reinitialize the iterator using
    * getFirstSOAPMethodAttribute();
    * However you can use this method despite where the iterator is 
    * pointing currently.
    *
    * @param pAttribute Pointer of Attribute to be deleted
    */
    void deleteSOAPMethodAttribute(IAttribute* pAttribute);

  /**
    * Set transport timeout.
    *
    * @param lSeconds Timeout in seconds. 
    *                 If lSeconds is 0, then the transport will assume no 
    *                 timeout. Hence you want to reset a timeout already set
    *                 use 0.
    */
    void setTransportTimeout(const long lSeconds);
  /**
    * Get the status of the stub to see any error situation
    */
       int getStatus();
  /**
    * Get a namespace prefix for a given namespace URI
    */
    const AxisChar* AXISCALL getNamespacePrefix(const AxisChar* pNamespace);

  /**
    * Set whether to Maitain session with service ot not.
    * @param bSession - true is session should be maintained. False otherwise.
    */
    void setMaintainSession(bool bSession);

  /**
    * Set transport protocol to be used by the transport.
    * @param eProtocol - protocol to use
    */
    void setTransportProtocol(AXIS_PROTOCOL_TYPE eProtocol);

  /**
    * Get transport protocol being used by the transport.
    * @return Protocol used by transport
    */
    AXIS_PROTOCOL_TYPE getTransportProtocol();

  protected:
  /**
    * Apply user set preferences to each call made on the Stub object.
    * This method is required because Axis engine holds only part of the state
    * with refereance to subsequent calls on the same Stub object. 
    * Foxing this approach would make the engine much more efficient.
    */
    void applyUserPreferences();

  /**
    * After the response is received and the results gathered update the Stub  
    * object's state with whatever information left over (e.g. get Set-Cookie 
    * value from trasport to be used for subsequent calls) 
    */
    void updateStateAfterResponse();
    
  /**
    * Set transport properties stored in m_vKeys and m_vValues vectors.
    * Called by applyUserPreferences for each and every method invocation. 
    */
    void setTransportProperties();
  
  /**
    * Set SOAP Headers stored in m_vSOAPHeaderBlock vector.
    * Called by applyUserPreferences for each and every method invocation. 
    */
    void setSOAPHeaders();
    
  /**
    * Set SOAP method attributes stored in m_vSOAPMethodAttributes vector.
    * Called by applyUserPreferences for each and every method invocation. 
    */
    void setSOAPMethodAttributes();

  /**
    * Set transport timeout stored in mm_lTimeoutSeconds
    * Called by applyUserPreferences for each and every method invocation. 
    */
    void setTransportTimeout();
  
  /**
    * Get Set-Cookie header value from transport.
    */
    void getCookieValue();

  /**
    * Call object of the Stub. This is the point of access to the internals
    * of the Axis engine.
    */
    Call *m_pCall;

  /**
    * Trasport property keys
    */
    vector < char *>m_vKeys;

  /**
    * Trasport keys iterator
    */
    vector <char*>::iterator m_viCurrentKey;

  /**
    * Trasport property values 
    */
    vector < char *>m_vValues;
  
  /**
    * Trasport keys iterator
    */
    vector <char*>::iterator m_viCurrentValue;

  /**
    * Vector of Header Blok pointers
    */
    vector < IHeaderBlock * >m_vSOAPHeaderBlocks;

  /**
    * Trasport keys iterator
    */
    vector <IHeaderBlock *>::iterator m_viCurrentSOAPHeaderBlock;

  /**
    * List of SOAPMethod Attributes
    */
    vector <IAttribute*> m_vSOAPMethodAttributes;

  /**
    * Trasport keys iterator
    */
    vector <IAttribute*>::iterator m_viCurrentSOAPMethodAttribute;

  /**
    * Timeout in seconds
    */
    long m_lTimeoutSeconds;

  /**
    * Should the Stub maintain session with service?
    */
    bool m_bMaintainSession;

  /**
    * Session key sent by service 
    */
    std::string m_strSessionKey;

};

AXIS_CPP_NAMESPACE_END

#endif /* !defined(_STUB_H____OF_AXIS_INCLUDED_) */
