/*
* The Apache Software License, Version 1.1
*
*
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
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
* 4. The names "Axis" and "Apache Software Foundation" must
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
*/

package org.apache.axis.client ;

import org.apache.axis.AxisFault;
import org.apache.axis.Constants;
import org.apache.axis.Message;
import org.apache.axis.MessageContext;
import org.apache.axis.SOAPPart;
import org.apache.axis.configuration.FileProvider;
import org.apache.axis.encoding.DeserializerFactory;
import org.apache.axis.encoding.SerializerFactory;
import org.apache.axis.encoding.ser.BaseSerializerFactory;
import org.apache.axis.encoding.ser.BaseDeserializerFactory;
import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.encoding.SerializationContextImpl;
import org.apache.axis.encoding.Serializer;
import org.apache.axis.encoding.TypeMappingRegistry;
import org.apache.axis.encoding.TypeMapping;
import org.apache.axis.message.RPCElement;
import org.apache.axis.message.RPCParam;
import org.apache.axis.message.SOAPBodyElement;
import org.apache.axis.message.SOAPEnvelope;
import org.apache.axis.message.SOAPFaultElement;
import org.apache.axis.message.SOAPHeader;
import org.apache.axis.transport.http.HTTPTransport;
import org.apache.axis.utils.JavaUtils;
import org.apache.axis.attachments.AttachmentPart; 
import org.apache.axis.InternalException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import javax.wsdl.Binding;
import javax.wsdl.BindingInput;
import javax.wsdl.BindingOperation;
import javax.wsdl.Definition;
import javax.wsdl.Input;
import javax.wsdl.Operation;
import javax.wsdl.Output;
import javax.wsdl.Part;
import javax.wsdl.Port;
import javax.wsdl.PortType;
import javax.wsdl.extensions.soap.SOAPAddress;
import javax.wsdl.extensions.soap.SOAPBody;
import javax.wsdl.extensions.soap.SOAPOperation;

import javax.xml.rpc.namespace.QName;
import javax.xml.rpc.JAXRPCException;
import javax.xml.rpc.ParameterMode;

import java.beans.IntrospectionException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;

/**
 * Axis' JAXRPC Dynamic Invocation Interface implementation of the Call
 * interface.  This class should be used to actually invoke the Web Service.
 * It can be prefilled by a WSDL document (on the constructor to the Service
 * object) or you can fill in the data yourself.
 * <pre>
 * Properties:
 *     NAMESPACE        - Namespace URI of RPC Body
 *     SEND_TYPE_ATTR   - Should we send the XSI type attributes (true/false)
 *     TIMEOUT          - Timeout used by transport sender in seconds
 *     TRANSPORT_NAME   - Name of transport handler to use
 * </pre>
 *
 * @author Doug Davis (dug@us.ibm.com)
 */

public class Call implements javax.xml.rpc.Call {
    protected static Log log =
        LogFactory.getLog(Call.class.getName());

    private boolean            parmAndRetReq   = true ;
    private Service            service         = null ;
    private QName              portTypeName    = null ;
    private QName              operationName   = null ;
    private Vector             paramNames      = null ;
    private Vector             paramTypes      = null ;
    private Vector             paramModes      = null ;
    private QName              returnType      = null ;

    private MessageContext     msgContext      = null ;

    // Collection of properties to store and put in MessageContext at
    // invoke() time.  Known ones are stored in actual variables for
    // efficiency/type-consistency.  Unknown ones are in myProperties.
    private Hashtable          myProperties    = new Hashtable();
    private String             username        = null;
    private String             password        = null;
    private boolean            maintainSession = false;
    private String             operationStyle  = null;
    private boolean            useSOAPAction   = false;
    private String             SOAPActionURI   = null;
    private String             encodingStyle   = Constants.URI_CURRENT_SOAP_ENC;
    private Integer            timeout         = null;


    // Our Transport, if any
    private Transport          transport       = null ;
    private String             transportName   = null ;

    // A place to store output parameters
    private HashMap            outParams       = null;

    // A place to store any client-specified headers
    private Vector             myHeaders       = null;

    public static final String SEND_TYPE_ATTR    = "send_type_attr" ;
    public static final String TRANSPORT_NAME    = "transport_name" ;
    public static final String TRANSPORT_PROPERTY= "java.protocol.handler.pkgs";

    // Constants for the standard properties
    public static final String USERNAME_PROPERTY =
            "javax.xml.rpc.security.auth.username";
    public static final String PASSWORD_PROPERTY =
            "javax.xml.rpc.security.auth.password";
    public static final String SESSION_PROPERTY =
            "javax.xml.rpc.http.session.maintain";
    public static final String OPERATION_STYLE_PROPERTY =
            "javax.xml.rpc.soap.operation.style";
    public static final String SOAPACTION_USE_PROPERTY =
            "javax.xml.rpc.soap.http.soapaction.use";
    public static final String SOAPACTION_URI_PROPERTY =
            "javax.xml.rpc.soap.http.soapaction.uri";
    public static final String ENCODING_STYLE_PROPERTY =
            "javax.xml.rpc.encodingstyle.namespace.uri";

    /**
     * A Hashtable mapping protocols (Strings) to Transports (classes)
     */
    private static Hashtable transports  = new Hashtable();

    /**
     * A Hashtable mapping addresses (URLs) to Transports (objects)
     */
    private static Hashtable transportImpls = new Hashtable();

    /************************************************************************/
    /* Start of core JAX-RPC stuff                                          */
    /************************************************************************/

    /**
     * Default constructor - not much else to say.
     */
    public Call(Service service) {
        this.service = service ;
        msgContext = new MessageContext( service.getEngine() );
        maintainSession = service.getMaintainSession();
        initialize();
    }

    /**
     * Build a call from a URL string
     *
     * @param url the target endpoint URL
     * @exception MalformedURLException
     */
    public Call(String url) throws MalformedURLException {
        this(new Service());
        setTargetEndpointAddress(new URL(url));
    }

    /**
     * Build a call from a URL
     *
     * @param url the target endpoint URL
     */
    public Call(URL url) {
        this(new Service());
        setTargetEndpointAddress(url);
    }

    ////////////////////////////
    //
    // Properties and the shortcuts for common ones.
    //

    /**
     * Allows you to set a named property to the passed in value.
     * There are a few known properties (like username, password, etc)
     * that are variables in Call.  The rest of the properties are
     * stored in a Hashtable.  These common properties should be
     * accessed via the accessors for speed/type safety, but they may
     * still be obtained via this method.  It's up to one of the
     * Handlers (or the Axis engine itself) to go looking for
     * one of them.
     *
     * @param name  Name of the property
     * @param value Value of the property
     */
    public void setProperty(String name, Object value) {
        if (name == null || value == null) {
            return;
            // Is this right?  Shouldn't we throw an exception like: throw new IllegalArgumentException();
        }
        else if (name.equals(USERNAME_PROPERTY)) {
            if (!(value instanceof String)) {
                throw new IllegalArgumentException(
                        JavaUtils.getMessage("badProp00", new String[] {
                        name, "java.lang.String", value.getClass().getName()}));
            }
            setUsername((String) value);
        }
        else if (name.equals(PASSWORD_PROPERTY)) {
            if (!(value instanceof String)) {
                throw new IllegalArgumentException(
                        JavaUtils.getMessage("badProp00", new String[] {
                        name, "java.lang.String", value.getClass().getName()}));
            }
            setPassword((String) value);
        }
        else if (name.equals(SESSION_PROPERTY)) {
            if (!(value instanceof Boolean)) {
                throw new IllegalArgumentException(
                        JavaUtils.getMessage("badProp00", new String[]
                        {name,
                        "java.lang.Boolean",
                        value.getClass().getName()}));
            }
            setMaintainSession(((Boolean) value).booleanValue());
        }
        else if (name.equals(OPERATION_STYLE_PROPERTY)) {
            if (!(value instanceof String)) {
                throw new IllegalArgumentException(
                        JavaUtils.getMessage("badProp00", new String[] {
                        name, "java.lang.String", value.getClass().getName()}));
            }
            setOperationStyle((String) value);
        }
        else if (name.equals(SOAPACTION_USE_PROPERTY)) {
            if (!(value instanceof Boolean)) {
                throw new IllegalArgumentException(
                        JavaUtils.getMessage("badProp00", new String[]
                        {name,
                        "java.lang.Boolean",
                        value.getClass().getName()}));
            }
            setUseSOAPAction(((Boolean) value).booleanValue());
        }
        else if (name.equals(SOAPACTION_URI_PROPERTY)) {
            if (!(value instanceof String)) {
                throw new IllegalArgumentException(
                        JavaUtils.getMessage("badProp00", new String[]
                        {name,
                        "java.lang.String",
                        value.getClass().getName()}));
            }
            setSOAPActionURI((String) value);
        }
        else if (name.equals(ENCODING_STYLE_PROPERTY)) {
            if (!(value instanceof String)) {
                throw new IllegalArgumentException(
                        JavaUtils.getMessage("badProp00", new String[]
                        {name,
                        "java.lang.String",
                        value.getClass().getName()}));
            }
            setEncodingStyle((String) value);
        }
        else if ( name.equals(TRANSPORT_NAME) ) {
            if (!(value instanceof String)) {
                throw new IllegalArgumentException(
                        JavaUtils.getMessage("badProp00", new String[] {
                        name, "java.lang.String", value.getClass().getName()}));
            }
            transportName = (String) value ;
            if (transport != null)
                transport.setTransportName((String) value);
        }
        else {
            myProperties.put(name, value);
        }
    } // setProperty

    /**
     * Returns the value associated with the named property - or null if not
     * defined/set.
     *
     * @return Object value of the property - or null
     */
    public Object getProperty(String name) {
        if (name != null) {
            if (name.equals(USERNAME_PROPERTY)) {
                return getUsername();
            }
            else if (name.equals(PASSWORD_PROPERTY)) {
                return getPassword();
            }
            else if (name.equals(SESSION_PROPERTY)) {
                return new Boolean(getMaintainSession());
            }
            else if (name.equals(OPERATION_STYLE_PROPERTY)) {
                return getOperationStyle();
            }
            else if (name.equals(SOAPACTION_USE_PROPERTY)) {
                return new Boolean(useSOAPAction());
            }
            else if (name.equals(SOAPACTION_URI_PROPERTY)) {
                return getSOAPActionURI();
            }
            else if (name.equals(ENCODING_STYLE_PROPERTY)) {
                return getEncodingStyle();
            }
            else if (name.equals(TRANSPORT_NAME)) {
                return transportName;
            }
            else {
                return myProperties.get(name);
            }
        }
        else {
            return null;
        }
    }

    /**
     * Set the username.
     */
    public void setUsername(String username) {
        this.username = username;
    } // setUsername

    /**
     * Get the user name
     */
    public String getUsername() {
        return username;
    } // getUsername

    /**
     * Set the password.
     */
    public void setPassword(String password) {
        this.password = password;
    } // setPassword

    /**
     * Get the password
     */
    public String getPassword() {
        return password;
    } // getPassword

    /**
     * Determine whether we'd like to track sessions or not.  This
     * overrides the default setting from the service.
     * This just passes through the value into the MessageContext.
     * Note: Not part of JAX-RPC specification.
     *
     * @param yesno true if session state is desired, false if not.
     */
    public void setMaintainSession(boolean yesno) {
        maintainSession = yesno;
    }

    /**
     * Get the value of maintainSession flag.
     */
    public boolean getMaintainSession() {
        return maintainSession;
    }

    /**
     * Set the operation style.  IllegalArgumentException is thrown if operationStyle
     * is not "rpc" or "document".
     *
     * @exception IllegalArgumentException if operationStyle is not "rpc" or "document".
     */
    public void setOperationStyle(String operationStyle) {
        if ("rpc".equalsIgnoreCase(operationStyle)
                || "document".equalsIgnoreCase(operationStyle)) {
            this.operationStyle = operationStyle;
        }
        else {
            throw new IllegalArgumentException(JavaUtils.getMessage(
                    "badProp01",
                    new String[] {OPERATION_STYLE_PROPERTY,
                    "\"rpc\", \"document\"", operationStyle}));
        }
    } // setOperationStyle

    /**
     * Get the operation style.
     */
    public String getOperationStyle() {
        return operationStyle;
    } // getOperationStyle

    /**
     * Should soapAction be used?
     */
    public void setUseSOAPAction(boolean useSOAPAction) {
        this.useSOAPAction = useSOAPAction;
    } // setUseSOAPAction

    /**
     * Are we using soapAction?
     */
    public boolean useSOAPAction() {
        return useSOAPAction;
    } // useSOAPAction

    /**
     * Set the soapAction URI.
     */
    public void setSOAPActionURI(String SOAPActionURI)
            throws IllegalArgumentException {
        this.SOAPActionURI = SOAPActionURI;
    } // setSOAPActionURI

    /**
     * Get the soapAction URI.
     */
    public String getSOAPActionURI() {
        return SOAPActionURI;
    } // getSOAPActionURI

    /**
     * Sets the encoding style to the URL passed in.
     *
     * @param namespaceURI URI of the encoding to use.
     */
    public void setEncodingStyle(String namespaceURI) {
        if (namespaceURI == null)
            namespaceURI = "";

        encodingStyle = namespaceURI;
    }

    /**
     * Returns the encoding style as a URI that should be used for the SOAP
     * message.
     *
     * @return String URI of the encoding style to use
     */
    public String getEncodingStyle() {
        return encodingStyle;
    }

   /**
     * Removes (if set) the named property.
     *
     * @param name name of the property to remove
     */
    public void removeProperty(String name) {
        if ( name == null || myProperties == null ) return ;
        myProperties.remove( name );
    }

    /**
     * Sets the URL of the target Web Service.
     *
     * @param address URL of the target Web Service
     */
    public void setTargetEndpointAddress(java.net.URL address) {
        try {
            if ( address == null ) {
                setTransport(null);
                return ;
            }

            String protocol = address.getProtocol();

            // Handle the case where the protocol is the same but we
            // just want to change the URL - if so just set the URL,
            // creating a new Transport object will drop all session
            // data - and we want that stuff to persist between invoke()s.
            // Technically the session data should be in the message
            // context so that it can be persistent across transports
            // as well, but for now the data is in the Transport object.
            ////////////////////////////////////////////////////////////////
            if ( this.transport != null ) {
                String oldAddr = this.transport.getUrl();
                if ( oldAddr != null && !oldAddr.equals("") ) {
                    URL     tmpURL   = new URL( oldAddr );
                    String  oldProto = tmpURL.getProtocol();
                    if ( protocol.equals(oldProto) ) {
                        this.transport.setUrl( address.toString() );
                        return ;
                    }
                }
            }

            // Do we already have a transport for this address?
            Transport transport = (Transport) transportImpls.get(address);
            if (transport != null) {
                setTransport(transport);
            }
            else {
            // We don't already have a transport for this address.  Create one.
                transport = getTransportForProtocol(protocol);
                if (transport == null)
                    throw new AxisFault("Call.setTargetEndpointAddress",
                                 JavaUtils.getMessage("noTransport01",
                                 protocol), null, null);
                transport.setUrl(address.toString());
                setTransport(transport);
                transportImpls.put(address, transport);
            }
        }
        catch( Exception exp ) {
            log.error(JavaUtils.getMessage("exception00"), exp);
            // do what?
            // throw new AxisFault("Call.setTargetEndpointAddress",
            //"Malformed URL Exception: " + e.getMessage(), null, null);
        }
    }

    /**
     * Returns the URL of the target Web Service.
     *
     * @return URL URL of the target Web Service
     */
    public java.net.URL getTargetEndpointAddress() {
        try {
            if ( transport == null ) return( null );
            return( new java.net.URL( transport.getUrl() ) );
        }
        catch( Exception exp ) {
            return( null );
        }
    }

    public Integer getTimeout() {
        return timeout;
    }

    public void setTimeout(Integer timeout) {
        this.timeout = timeout;
    }
    //
    // end properties code.
    //
    ////////////////////////////

    /**
     * Is the caller required to provide the parameter and return type specification?  If true, then
     * addParameter and setReturnType MUST be called to provide the meta data.  If false, then
     * addParameter and setReturnType CANNOT be called because the Call object already has the meta
     * data and the user is not allowed to mess with it.  These methods throw JAXRPCException if
     * this method returns false.
     */
    public boolean isParameterAndReturnSpecRequired() {
        return parmAndRetReq;
    } // isParameterAndReturnSpecRequired

    /**
     * Adds the specified parameter to the list of parameters for the
     * operation associated with this Call object.
     *
     * @param paramName      Name that will be used for the parameter in the XML
     * @param paramType      XMLType of the parameter
     * @param parameterMode  one of PARAM_MODE_IN, PARAM_MODE_OUT
     *                       or PARAM_MODE_INOUT
     */
    public void addParameter(String paramName, QName paramType,
            ParameterMode parameterMode) {
        if (parmAndRetReq) {

            if ( paramNames == null ) {
                paramNames = new Vector();
                paramTypes = new Vector();
                paramModes = new Vector();
            }

            paramNames.add( new QName("", paramName) );
            paramTypes.add( paramType );
            paramModes.add( parameterMode );

        }
        else {
            throw new JAXRPCException();
        }
    }
    /**
     * Adds the specified parameter to the list of parameters for the
     * operation associated with this Call object.
     *
     * @param paramName      Name that will be used for the parameter in the XML
     * @param paramType      XMLType of the parameter
     * @param parameterMode  one of PARAM_MODE_IN, PARAM_MODE_OUT
     *                       or PARAM_MODE_INOUT
     */
    public void addParameter(QName paramName, QName paramType,
            ParameterMode parameterMode) {
        if (parmAndRetReq) {

            if ( paramNames == null ) {
                paramNames = new Vector();
                paramTypes = new Vector();
                paramModes = new Vector();
            }

            paramNames.add( paramName );
            paramTypes.add( paramType );
            paramModes.add( parameterMode );

        }
        else {
            throw new JAXRPCException();
        }
    }

    /**
     * Return the QName of the type of the parameters with the given name.
     *
     * @param  paramName  name of the parameter to return
     * @return XMLType    XMLType of paramName, or null if not found.
     */
    public QName getParameterTypeByName(String paramName) {
        int  i ;
        QName paramQName = new QName("", paramName);

        return getParameterTypeByQName(paramQName);
    }

    /**
     * Return the QName of the type of the parameters with the given name.
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @param  paramQName  QName of the parameter to return
     * @return XMLType    XMLType of paramQName, or null if not found.
     */    
    public QName getParameterTypeByQName(QName paramQName) {
        int i;
        if ( paramNames == null ) return( null );

        for (i = 0 ; i< paramNames.size() ; i++ ) 
            if ( ((QName)paramNames.get(i)).equals(paramQName) ) {
                return (QName) paramTypes.get(i);
            }
        return( null );
    }

    /**
     * Sets the return type of the operation associated with this Call object.
     *
     * @param type QName of the return value type.
     */
    public void setReturnType(QName type) {
        if (parmAndRetReq) {
            returnType = type ;
        }
        else {
            throw new JAXRPCException();
        }
    }

    /**
     * Returns the QName of the type of the return value of this Call - or null if
     * not set.
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @return the XMLType specified for this Call (or null).
     */
    public QName getReturnType() {
        return( returnType );
    }

    /**
     * Clears the list of parameters.
     * @exception JAXRPCException - if isParameterAndReturnSpecRequired returns false, then
     * removeAllParameters will throw JAXRPCException.
     */
    public void removeAllParameters() {
        if (parmAndRetReq) {
            paramNames = null ;
            paramTypes = null ;
            paramModes = null ;
        }
        else {
            throw new JAXRPCException();
        }
    }

    /**
     * Returns the operation name associated with this Call object.
     *
     * @return String Name of the operation or null if not set.
     */
    public QName getOperationName() {
        return( operationName );
    }

    /**
     * Sets the operation name associated with this Call object.  This will
     * not check the WSDL (if there is WSDL) to make sure that it's a valid
     * operation name.
     *
     * @param opName Name of the operation.
     */
    public void setOperationName(QName opName) {
        operationName = opName ;
    }

    /**
     * This is a convenience method.  If the user doesn't care about the QName of the operation, the
     * user can call this method, which converts a String operation name to a QName.
     */
    public void setOperationName(String opName) {
        operationName = new QName(opName);
    }

    public void setOperation(QName portName, String opName) {
        if ( service == null ) 
            throw new JAXRPCException( JavaUtils.getMessage("noService04") );

        Definition wsdlDefinition = service.getWSDLDefinition();
        javax.wsdl.Service wsdlService = service.getWSDLService();

        javax.wsdl.QName qn = new javax.wsdl.QName( portName.getNamespaceURI(),
                                                    portName.getLocalPart() );
        if ( wsdlDefinition == null )
            throw new JAXRPCException( JavaUtils.getMessage("wsdlMissing00") );

        Port port = wsdlService.getPort( portName.getLocalPart() );
        if ( port == null )
            throw new JAXRPCException( JavaUtils.getMessage("noPort00", "" + portName) );

        Binding   binding  = port.getBinding();
        PortType  portType = binding.getPortType();
        if ( portType == null )
            throw new JAXRPCException( JavaUtils.getMessage("noPortType00", "" + portName) );

        List operations = portType.getOperations();
        if ( operations == null )
            throw new JAXRPCException( JavaUtils.getMessage("noOperation01", opName) );
        Operation op = null ;
        for ( int i = 0 ; i < operations.size() ; i++, op=null ) {
            op = (Operation) operations.get( i );
            if ( opName.equals( op.getName() ) ) break ;
        }
        if ( op == null )
            throw new JAXRPCException( JavaUtils.getMessage("noOperation01", opName) );

        this.setPortTypeName( portName );
        this.setOperationName( opName );

        // Get the URL
        ////////////////////////////////////////////////////////////////////
        this.setTargetEndpointAddress( null );
        List list = port.getExtensibilityElements();
        for ( int i = 0 ; list != null && i < list.size() ; i++ ) {
            Object obj = list.get(i);
            if ( obj instanceof SOAPAddress ) { 
                try {
                    SOAPAddress addr = (SOAPAddress) obj ;
                    URL         url  = new URL(addr.getLocationURI());
                    this.setTargetEndpointAddress(url);
                }
                catch(Exception exp) {
                    throw new JAXRPCException(
                            JavaUtils.getMessage("cantSetURI00", "" + exp) );
                }
            }
        }

        // Get the SOAPAction
        ////////////////////////////////////////////////////////////////////
        BindingOperation bop = binding.getBindingOperation(opName,
                                                           null, null);
        if ( bop == null )
            throw new JAXRPCException( JavaUtils.getMessage("noOperation02",
                                                            opName ));
        list = bop.getExtensibilityElements();
        for ( int i = 0 ; list != null && i < list.size() ; i++ ) {
            Object obj = list.get(i);
            if ( obj instanceof SOAPOperation ) { 
                SOAPOperation sop    = (SOAPOperation) obj ;
                String        action = sop.getSoapActionURI();
                if ( action != null ) {
                    setUseSOAPAction(true);
                    setSOAPActionURI(action);
                }
                else {
                    setUseSOAPAction(false);
                    setSOAPActionURI(null);
                }
                break ;
            }
        }

        // Get the body's namespace URI and encoding style
        ////////////////////////////////////////////////////////////////////
        this.setEncodingStyle( null );
        BindingInput bIn = bop.getBindingInput();
        if ( bIn != null ) {
            list = bIn.getExtensibilityElements();
            for ( int i = 0 ; list != null && i < list.size() ; i++ ) {
                Object obj = list.get(i);
                if ( obj instanceof SOAPBody ) { 
                    SOAPBody sBody  = (SOAPBody) obj ;
                    list = sBody.getEncodingStyles();
                    if ( list != null && list.size() > 0 )
                        this.setEncodingStyle( (String) list.get(0) );
                    String ns = sBody.getNamespaceURI();
                    if (ns != null && !ns.equals(""))
                      setOperationName( new QName( ns, opName ) );
                    break ;
                }
            }
        }

        // Get the parameters
        ////////////////////////////////////////////////////////////////////
        List    paramOrder = op.getParameterOrdering();
        Input   input      = op.getInput();
        javax.wsdl.Message message    = null ;
        List    parts      = null ;

        this.removeAllParameters();
        if ( input   != null ) message = input.getMessage();
        if ( message != null ) parts   = message.getOrderedParts( paramOrder );
        if ( parts != null ) {
            for ( int i = 0 ; i < parts.size() ; i++ ) {
                Part    part = (Part) parts.get(i);
                if ( part == null ) continue ;

                String           name  = part.getName();
                javax.wsdl.QName type  = part.getTypeName();

                if ( type == null ) {
                    type = part.getElementName();
                    if ( type != null ) 
                      type = new javax.wsdl.QName("java","org.w3c.dom.Element");
                    else
                      throw new JAXRPCException(
                                  JavaUtils.getMessage("typeNotSet00", name) );
                }

                QName qname = new QName(type.getNamespaceURI(),
                        type.getLocalPart());
                ParameterMode mode = ParameterMode.PARAM_MODE_IN;
                this.addParameter( name, qname, mode );
            }
        }


        // Get the return type
        ////////////////////////////////////////////////////////////////////
        Output   output  = op.getOutput();
        message = null ;

        if ( output  != null ) message = output.getMessage();
        if ( message != null ) parts   = message.getOrderedParts(null);

        this.setReturnType( null );
        if ( parts != null ) {
            for( int i = 0 ;i < parts.size() ; i++ ) {
                Part part  = (Part) parts.get( i );

                if (paramOrder != null && paramOrder.contains(part.getName()))
                        continue ;

                javax.wsdl.QName type  = part.getTypeName();
                if ( type == null ) {
                    type = part.getElementName();
                    if ( type != null ) 
                      type = new javax.wsdl.QName("java","org.w3c.dom.Element");
                    else
                      throw new JAXRPCException(
                            JavaUtils.getMessage("typeNotSet00", "<return>") );
                }
                QName qname = new QName(type.getNamespaceURI(),
                        type.getLocalPart());
                this.setReturnType( qname );
                break ;
            }
        }

    }

    /**
     * Returns the fully qualified name of the port for this Call object
     * (if there is one).
     *
     * @return QName Fully qualified name of the port (or null if not set)
     */
    public QName getPortTypeName() {
        return( portTypeName );
    }

    /**
     * Sets the port type of this Call object.  This call will not set
     * any additional fields, nor will it do any checking to verify that
     * this port type is actually defined in the WSDL - for now anyway.
     *
     * @param portType Fully qualified name of the portType
     */
    public void setPortTypeName(QName portType) {
        portTypeName = portType ;
    }

    /**
     * Invokes a specific operation using a synchronous request-response interaction mode. The invoke method takes 
     * as parameters the object values corresponding to these defined parameter types. Implementation of the invoke 
     * method must check whether the passed parameter values correspond to the number, order and types of parameters 
     * specified in the corresponding operation specification.
     *
     * @param operationName - Name of the operation to invoke
     * @param params  - Parameters for this invocation
     *
     * @return the value returned from the other end. 
     *
     * @throws java.rmi.RemoteException - if there is any error in the remote method invocation or if the Call 
     * object is not configured properly.
     */
    public Object invoke(QName operationName, Object[] params)
      throws java.rmi.RemoteException {
        QName origOpName = this.operationName;
        this.operationName = operationName;
        try {
            return this.invoke(params);
        }
        catch (java.rmi.RemoteException re) {
            this.operationName = origOpName;
            throw re;
        }
        catch (RuntimeException re) {
            this.operationName = origOpName;
            throw re;
        }
        catch (Error e) {
            this.operationName = origOpName;
            throw e;
        }
    } // invoke

    /**
     * Invokes the operation associated with this Call object using the
     * passed in parameters as the arguments to the method.
     *
     * For Messaging (ie. non-RPC) the params argument should be an array
     * of SOAPBodyElements.  <b>All</b> of them need to be SOAPBodyElements,
     * if any of them are not this method will default back to RPC.  In the
     * Messaging case the return value will be a vector of SOAPBodyElements.
     *
     * @param  params Array of parameters to invoke the Web Service with
     * @return Object Return value of the operation/method - or null
     * @throws RemoteException if there's an error
     */
    public Object invoke(Object[] params) throws java.rmi.RemoteException {
        /* First see if we're dealing with Messaging instead of RPC.        */
        /* If ALL of the params are SOAPBodyElements then we're doing       */
        /* Messaging, otherwise just fall through to normal RPC processing. */
        /********************************************************************/
        SOAPEnvelope  env = null ;
        int i ;

        for ( i = 0 ; params != null && i < params.length ; i++ )
            if ( !(params[i] instanceof SOAPBodyElement) ) break ;

        if ( params != null && params.length > 0 && i == params.length ) {
            /* ok, we're doing Messaging, so build up the message */
            /******************************************************/
            env = new SOAPEnvelope();

            for ( i = 0 ; myHeaders != null && i < myHeaders.size() ; i++ )
                env.addHeader((SOAPHeader)myHeaders.get(i));

            if ( !(params[0] instanceof SOAPEnvelope) )
                for ( i = 0 ; i < params.length ; i++ )
                    env.addBodyElement( (SOAPBodyElement) params[i] );

            Message msg = new Message( env );
            setRequestMessage(msg);

            invoke();

            msg = msgContext.getResponseMessage();
            if (msg == null)
                throw new AxisFault(JavaUtils.getMessage("nullResponse00"));

            env = msg.getSOAPEnvelope();
            return( env.getBodyElements() );
        }


        if ( operationName == null )
            throw new AxisFault( JavaUtils.getMessage("noOperation00") );
        try {
            return this.invoke(operationName.getNamespaceURI(),
                    operationName.getLocalPart(), getParamList(params));
        }
        catch( AxisFault af) {
            throw af;
        }
        catch( Exception exp ) {
            //if ( exp instanceof AxisFault ) throw (AxisFault) exp ;

            throw new AxisFault( JavaUtils.getMessage("errorInvoking00", "\n" + exp) );
        }
    }

    /**
     * Invokes the operation associated with this Call object using the passed
     * in parameters as the arguments to the method.  This will return
     * immediately rather than waiting for the server to complete its
     * processing.
     *
     * NOTE: the return immediately part isn't implemented yet
     *
     * @param  params Array of parameters to invoke the Web Service with
     * @throws JAXRPCException is there's an error
     */
    public void invokeOneWay(Object[] params) {
        try {
            invoke( getParamList(params) );
        }
        catch( Exception exp ) {
            throw new JAXRPCException( exp.toString() );
        }
    }

    /************************************************************************/
    /* End of core JAX-RPC stuff                                            */
    /************************************************************************/

    /** Invoke the service with a custom SOAPEnvelope.
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @param env a SOAPEnvelope to send.
     * @exception AxisFault
     */
    public SOAPEnvelope invoke(SOAPEnvelope env)
                                  throws java.rmi.RemoteException {
        try {
            Message msg = null ;
            int     i ;

            for ( i = 0 ; myHeaders != null && i < myHeaders.size() ; i++ )
                env.addHeader((SOAPHeader)myHeaders.get(i));

            msg = new Message( env );
            setRequestMessage( msg );
            invoke();
            msg = msgContext.getResponseMessage();
            if (msg == null)
                throw new AxisFault(JavaUtils.getMessage("nullResponse00"));
            return( msg.getSOAPEnvelope() );
        }
        catch( Exception exp ) {
            if ( exp instanceof AxisFault ) throw (AxisFault) exp ;

            throw new AxisFault( JavaUtils.getMessage("errorInvoking00", "\n" + exp) );
        }
    }


    /** Register a Transport that should be used for URLs of the specified
     * protocol.
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @param protocol the URL protocol (i.e. "tcp" for "tcp://" urls)
     * @param transportClass the class of a Transport type which will be used
     *                       for matching URLs.
     */
    public static void setTransportForProtocol(String protocol,
                                               Class transportClass) {
        if (Transport.class.isAssignableFrom(transportClass))
            transports.put(protocol, transportClass);
        else
            throw new InternalException(transportClass.toString());
    }

    /**
     * Set up the default transport URL mappings.
     *
     * This must be called BEFORE doing non-standard URL parsing (i.e. if you
     * want the system to accept a "local:" URL).  This is why the Options class
     * calls it before parsing the command-line URL argument.
     *
     * Note: Not part of JAX-RPC specification.
     */
    public static synchronized void initialize() {
        addTransportPackage("org.apache.axis.transport");

        setTransportForProtocol("local",
                org.apache.axis.transport.local.LocalTransport.class);
        setTransportForProtocol("http", HTTPTransport.class);
        setTransportForProtocol("https", HTTPTransport.class);
    }

    /** Add a package to the system protocol handler search path.  This
     * enables users to create their own URLStreamHandler classes, and thus
     * allow custom protocols to be used in Axis (typically on the client
     * command line).
     *
     * For instance, if you add "samples.transport" to the packages property,
     * and have a class samples.transport.tcp.Handler, the system will be able
     * to parse URLs of the form "tcp://host:port..."
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @param packageName the package in which to search for protocol names.
     */
    public static synchronized void addTransportPackage(String packageName) {
        String currentPackages = System.getProperty(TRANSPORT_PROPERTY);
        if (currentPackages == null) {
            currentPackages = "";
        } else {
            currentPackages += "|";
        }
        currentPackages += packageName;

        System.setProperty(TRANSPORT_PROPERTY, currentPackages);
    }

    /**
     * Convert the list of objects into RPCParam's based on the paramNames,
     * paramTypes and paramModes variables.  If those aren't set then just
     * return what was passed in.
     *
     * @param  params   Array of parameters to pass into the operation/method
     * @return Object[] Array of parameters to pass to invoke()
     */
    private Object[] getParamList(Object[] params) {
        int  numParams = 0 ;
        int  i ;

        // If we never set-up any names... then just return what was passed in
        //////////////////////////////////////////////////////////////////////
        if ( paramNames == null ) return( params );

        // Count the number of IN and INOUT params, this needs to match the
        // number of params passed in - if not throw an error
        /////////////////////////////////////////////////////////////////////
        for ( i = 0 ; i < paramNames.size() ; i++ ) {
            if (paramModes.get(i) == ParameterMode.PARAM_MODE_OUT)
                continue ;
            numParams++ ;
        }

        if ( numParams != params.length )
            throw new JAXRPCException(
                    JavaUtils.getMessage("parmMismatch00",
                    "" + params.length, "" + numParams) );

        // All ok - so now produce an array of RPCParams
        //////////////////////////////////////////////////
        Vector result = new Vector();
        int    j = 0 ;
        for ( i = 0 ; i < paramNames.size() ; i++ ) {
            if (paramModes.get(i) == ParameterMode.PARAM_MODE_OUT)
                continue ;
            QName paramQName = (QName)paramNames.get(i);
            RPCParam p = new RPCParam(paramQName.getNamespaceURI(),
                                      paramQName.getLocalPart(),
                                      params[j++] );
            result.add( p );
        }

        return( result.toArray() );
    }

    /**
     * Set the Transport
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @param transport the Transport object we'll use to set up
     *                  MessageContext properties.
     */
    public void setTransport(Transport trans) {
        transport = trans;
        if (log.isDebugEnabled())
            log.debug(JavaUtils.getMessage("transport00", "" + transport));
    }

    /** Get the Transport registered for the given protocol.
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @param protocol a protocol such as "http" or "local" which may
     *                 have a Transport object associated with it.
     * @return the Transport registered for this protocol, or null if none.
     */
    public Transport getTransportForProtocol(String protocol)
    {
        Class transportClass = (Class)transports.get(protocol);
        Transport ret = null;
        if (transportClass != null) {
            try {
                ret = (Transport)transportClass.newInstance();
            } catch (InstantiationException e) {
            } catch (IllegalAccessException e) {
            }
        }
        return ret;
    }

    /**
     * Directly set the request message in our MessageContext.
     *
     * This allows custom message creation.
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @param msg the new request message.
     */
    public void setRequestMessage(Message msg) {

        if(null != attachmentParts && !attachmentParts.isEmpty()){ 
            try{
            org.apache.axis.attachments.Attachments attachments= msg.getAttachments();
            if(null == attachments)
              throw new RuntimeException("No support for attachments");

            attachments.setAttachmentParts(attachmentParts);
            }catch(org.apache.axis.AxisFault ex){
              log.debug(JavaUtils.getMessage("axisFault00"), ex);
              throw  new RuntimeException(ex.getMessage());
            }
        }
    
        msgContext.setRequestMessage(msg);
        attachmentParts.clear();
    }

    /**
     * Directly get the response message in our MessageContext.
     *
     * Shortcut for having to go thru the msgContext
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @return the response Message object in the msgContext
     */
    public Message getResponseMessage() {
        return msgContext.getResponseMessage();
    }

    /**
     * Obtain a reference to our MessageContext.
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @return the MessageContext.
     */
    public MessageContext getMessageContext () {
        return msgContext;
    }

    /**
     * Add a header which should be inserted into each outgoing message
     * we generate.
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @param header a SOAPHeader to be inserted into messages
     */
    public void addHeader(SOAPHeader header)
    {
        if (myHeaders == null) {
            myHeaders = new Vector();
        }
        myHeaders.add(header);
    }

    /**
     * Clear the list of headers which we insert into each message
     *
     * Note: Not part of JAX-RPC specification.
     */
    public void clearHeaders()
    {
        myHeaders = null;
    }

    /**
     * Register type mapping information for serialization/deserialization
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @param javaType is  the Java class of the data type.
     * @param xmlType the xsi:type QName of the associated XML type.
     * @param sf/df are the factories (or the Class objects of the factory).
     * @param force Indicates whether to add the information if already registered.
     */
    public void registerTypeMapping(Class javaType, QName xmlType,
                                    SerializerFactory sf,
                                    DeserializerFactory df) {
        registerTypeMapping(javaType, xmlType, sf, df, true);
    }
    public void registerTypeMapping(Class javaType, QName xmlType,
                                    SerializerFactory sf,
                                    DeserializerFactory df,
                                    boolean force) {
        // Get the TypeMappingRegistry
        TypeMappingRegistry tmr = msgContext.getTypeMappingRegistry();

        // If a TypeMapping is not available, add one.
        TypeMapping tm = (TypeMapping) tmr.getTypeMapping(encodingStyle); 
        TypeMapping defaultTM = (TypeMapping) tmr.getDefaultTypeMapping(); 
        try {
            if (tm == null || tm == defaultTM ) {
                tm = (TypeMapping) tmr.createTypeMapping();
                tm.setSupportedNamespaces(new String[] {encodingStyle});
                tmr.register(msgContext.getEncodingStyle(), tm);
            }
            if (!force && tm.isRegistered(javaType, xmlType)) 
                return;

            // Register the information
            tm.register(javaType, xmlType, sf, df);
        } catch (Exception e) {}
    }
    public void registerTypeMapping(Class javaType, QName xmlType,
                                    Class sfClass, Class dfClass) {
        registerTypeMapping(javaType, xmlType, sfClass, dfClass, true);
    }
    public void registerTypeMapping(Class javaType, QName xmlType,
                                    Class sfClass, Class dfClass, boolean force){
        // Instantiate the factory using introspection.
        SerializerFactory   sf = BaseSerializerFactory.createFactory  (sfClass, javaType, xmlType);
        DeserializerFactory df = BaseDeserializerFactory.createFactory(dfClass, javaType, xmlType);
        if (sf != null || df != null) {
            registerTypeMapping(javaType, xmlType, sf, df, force);
        }
    }

    /**
     * Map a type for deserialization.
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @param qName the xsi:type QName of an XML Schema type.
     * @param _class the class of the associated Java data type.
     * @param deserializerFactory a factory which can create deserializer
     *                            instances for this type.
     * @throws IntrospectionException _class is not compatible with the
     *                            specified deserializer.
     */

    /************************************************
     * Invocation
     */

    /** Invoke an RPC service with a method name and arguments.
     *
     * This will call the service, serializing all the arguments, and
     * then deserialize the return value.
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @param namespace the desired namespace URI of the method element
     * @param method the method name
     * @param args an array of Objects representing the arguments to the
     *             invoked method.  If any of these objects are RPCParams,
     *             Axis will use the embedded name of the RPCParam as the
     *             name of the parameter.  Otherwise, we will serialize
     *             each argument as an XML element called "arg<n>".
     * @return a deserialized Java Object containing the return value
     * @exception AxisFault
     */
    public Object invoke(String namespace, String method, Object[] args)
                    throws AxisFault {

        if (log.isDebugEnabled()) {
            log.debug(JavaUtils.getMessage("enter00", 
                                           "Call::invoke(ns, meth, args)") );
        }

        RPCElement  body = new RPCElement(namespace, method, args);
        
        Object ret = invoke( body );

        if (log.isDebugEnabled()) {
            log.debug(JavaUtils.getMessage("exit00", 
                                           "Call::invoke(ns, meth, args)") );
        }

        return ret;
    }

    /** Convenience method to invoke a method with a default (empty)
     * namespace.  Calls invoke() above.
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @param method the method name
     * @param args an array of Objects representing the arguments to the
     *             invoked method.  If any of these objects are RPCParams,
     *             Axis will use the embedded name of the RPCParam as the
     *             name of the parameter.  Otherwise, we will serialize
     *             each argument as an XML element called "arg<n>".
     * @return a deserialized Java Object containing the return value
     * @exception AxisFault
     */
    public Object invoke( String method, Object [] args ) throws AxisFault
    {
        return invoke("", method, args);
    }

    /** Invoke an RPC service with a pre-constructed RPCElement.
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @param body an RPCElement containing all the information about
     *             this call.
     * @return a deserialized Java Object containing the return value
     * @exception AxisFault
     */
    public Object invoke( RPCElement body ) throws AxisFault {
        if (log.isDebugEnabled()) {
            log.debug(JavaUtils.getMessage("enter00", 
                                           "Call::invoke(RPCElement)") );
        }

        SOAPEnvelope         reqEnv = new SOAPEnvelope();
        SOAPEnvelope         resEnv = null ;
        Message              reqMsg = new Message( reqEnv );
        Message              resMsg = null ;
        Vector               resArgs = null ;
        Object               result = null ;

        // Clear the output params
        outParams = new HashMap();

        // If we have headers to insert, do so now.
        if (myHeaders != null) {
            for (int i = 0; i < myHeaders.size(); i++) {
                reqEnv.addHeader((SOAPHeader)myHeaders.get(i));
            }
        }

        // Set both the envelope and the RPCElement encoding styles
        body.setEncodingStyle(encodingStyle);
        reqEnv.setEncodingStyle(encodingStyle);

        setRequestMessage(reqMsg);

        reqEnv.addBodyElement(body);
        body.setParent(reqEnv);
        reqEnv.setMessageType(Message.REQUEST);

        try {
            invoke();
        }
        catch( Exception e ) {
            log.error( JavaUtils.getMessage("exception00"), e );
            throw AxisFault.makeFault(e);
        }

        resMsg = msgContext.getResponseMessage();
        resEnv = (SOAPEnvelope)resMsg.getSOAPEnvelope();
        try {
            body = (RPCElement)resEnv.getFirstBody();
            resArgs = body.getParams();
        } catch (Exception e) {
            log.error(JavaUtils.getMessage("exception00"), e);
            throw AxisFault.makeFault(e);
        }

        if (resArgs != null && resArgs.size() > 0) {

            // If there is no return, then we start at index 0 to create the outParams Map.
            // If there IS a return, then we start with 1.
            int outParamStart = 0;

            // If we have resArgs and the returnType is specified, then the first
            // resArgs is the return.  If we have resArgs and neither returnType
            // nor paramTypes are specified, then we assume that the caller is
            // following the non-JAX-RPC AXIS shortcut of not having to specify
            // the return, in which case we again assume the first resArgs is
            // the return.
            // NOTE 1:  the non-JAX-RPC AXIS shortcut allows a potential error
            // to escape notice.  If the caller IS NOT following the non-JAX-RPC
            // shortcut but instead intentionally leaves returnType and params
            // null (ie., a method that takes no parameters and returns nothing)
            // then, if we DO receive something it should be an error, but this
            // code passes it through.  The ideal solution here is to require
            // this caller to set the returnType to void, but there's no void
            // type in XML.
            // NOTE 2:  we should probably verify that the resArgs element
            // types match the expected returnType and paramTypes, but I'm not
            // sure how to do that since the resArgs value is a Java Object
            // and the returnType and paramTypes are QNames.
            if (returnType != null || paramTypes == null) {
                RPCParam param = (RPCParam)resArgs.get(0);
                result = param.getValue();
                outParamStart = 1;
            }

            for (int i = outParamStart; i < resArgs.size(); i++) {
                RPCParam param = (RPCParam) resArgs.get(i);
                outParams.put(param.getName(), param.getValue());
            }
        }

        if (log.isDebugEnabled()) {
            log.debug(JavaUtils.getMessage("exit00",
                                           "Call::invoke(RPCElement)") );
        }

        return( result );
    }

    /**
     * Set engine option.
     *
     * Note: Not part of JAX-RPC specification.
     */
    public void setOption(String name, Object value) {
        service.getEngine().setOption(name, value);
    }
    
    /**
     * Old version of above
     * 
     * @deprecated replaced with setOption()
     */
    public void addOption(String name, Object value) {
        setOption(name, value);
    }

    /**
     * Invoke this Call with its established MessageContext
     * (perhaps because you called this.setRequestMessage())
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @exception AxisFault
     */
    public void invoke() throws AxisFault {
        if (log.isDebugEnabled()) {
            log.debug(JavaUtils.getMessage("enter00", "Call::invoke()") );
        }

        Message      reqMsg  = null ;
        SOAPEnvelope reqEnv  = null ;

        msgContext.reset();
        msgContext.setResponseMessage(null);
        msgContext.setProperty( MessageContext.CALL, this );
        if (username != null) {
            msgContext.setUsername(username);
        }
        if (password != null) {
            msgContext.setPassword(password);
        }
        msgContext.setMaintainSession(maintainSession);
        if (operationStyle != null) {
            msgContext.setOperationStyle(MessageContext.getStyleFromString(operationStyle));
        }
        if (useSOAPAction) {
            msgContext.setUseSOAPAction(true);
        }
        if (SOAPActionURI != null) {
            msgContext.setSOAPActionURI(SOAPActionURI);
        }
        msgContext.setEncodingStyle(encodingStyle);

        /**
         * Go thru the properties and ones that are Axis specific, and
         * need to be moved to the msgContext - do so.
         * TBD:
         *   security.auth.subject
         */
        if (myProperties != null) {
            msgContext.setPropertyParent(myProperties);
        }

        // Determine client target service
        reqMsg = msgContext.getRequestMessage();
        reqEnv = reqMsg.getSOAPEnvelope();
        SOAPBodyElement body = reqEnv.getFirstBody();

        if ( body.getPrefix() == null )       body.setPrefix( "m" );
        if ( body.getNamespaceURI() == null ) {
            throw new AxisFault("Call.invoke", 
                   JavaUtils.getMessage("cantInvoke00", body.getName()),
                                        null, null);
        } else if (msgContext.getService() == null) {
            msgContext.setTargetService(body.getNamespaceURI());
        }

        if (log.isDebugEnabled()) {
            log.debug("TargetService:" + msgContext.getTargetService());
        }

        // set up transport if there is one
        if (transport != null) {
            transport.setupMessageContext(msgContext, this, service.getEngine());
        }
        else
            msgContext.setTransportName( transportName );

        // For debugging - print request message
        if (log.isDebugEnabled()) {
            StringWriter writer = new StringWriter();
            try {
                SerializationContext ctx = new SerializationContextImpl(writer,
                                                                   msgContext);
                reqEnv.output(ctx);
                writer.close();
            } catch (Exception e) {
                log.debug("Exception caught while printing request message", e);
            } finally {
                log.debug(writer.getBuffer().toString());
            }
        }

        service.getEngine().invoke( msgContext );
        
        if (transport != null)
            transport.processReturnedMessageContext(msgContext);
        
        Message resMsg = msgContext.getResponseMessage();
        
        if (resMsg == null)
            throw new AxisFault(JavaUtils.getMessage("nullResponse00"));
        
        /** This must happen before deserialization...
         */
        resMsg.setMessageType(Message.RESPONSE);
        
        SOAPEnvelope resEnv = (SOAPEnvelope)resMsg.getSOAPPart().
                getAsSOAPEnvelope();
        
        SOAPBodyElement respBody = resEnv.getFirstBody();
        if (respBody instanceof SOAPFaultElement) {
            throw ((SOAPFaultElement)respBody).getFault();
        }

        if (log.isDebugEnabled()) {
            log.debug(JavaUtils.getMessage("exit00", "Call::invoke()") );
        }
    }

    /**
     * Get the output parameters (if any) from the last invocation.
     *
     * NOTE that the params returned are all RPCParams, containing
     * name and value - if you want the value, you'll need to call
     * param.getValue().
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @return Vector of RPCParams
     */
    public Map getOutputParams()
    {
        return this.outParams;
    }

    /**
     * Get the Service object associated with this Call object.
     *
     * Note: Not part of JAX-RPC specification.
     *
     * @return Service the Service object this Call object is associated with
     */
    public Service getService()
    {
        return this.service;
    }


    protected java.util.Vector attachmentParts= new java.util.Vector();

    /**
     * This method adds an attachment.
     *
     * Note: Not part of JAX-RPC specification.
     * @exception RuntimeException if there is no support for attachments.
     *
     */
     public void addAttachmentPart( Object attachment){
         attachmentParts.add(attachment);
     }
}
