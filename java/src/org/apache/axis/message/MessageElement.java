/*
 * Copyright 2001-2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.axis.message;

import org.apache.axis.AxisFault;
import org.apache.axis.Constants;
import org.apache.axis.MessageContext;
import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.encoding.DeserializationContext;
import org.apache.axis.encoding.DeserializationContextImpl;
import org.apache.axis.encoding.Deserializer;
import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.encoding.SerializationContextImpl;
import org.apache.axis.enum.Style;
import org.apache.axis.soap.SOAPConstants;
import org.apache.axis.utils.Mapping;
import org.apache.axis.utils.Messages;
import org.apache.axis.utils.XMLUtils;
import org.apache.commons.logging.Log;
import org.w3c.dom.Attr;
import org.w3c.dom.CDATASection;
import org.w3c.dom.CharacterData;
import org.w3c.dom.Comment;
import org.w3c.dom.DOMException;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.w3c.dom.Text;
import org.xml.sax.Attributes;
import org.xml.sax.ContentHandler;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.AttributesImpl;

import javax.xml.namespace.QName;
import javax.xml.rpc.encoding.TypeMapping;
import javax.xml.soap.Name;
import javax.xml.soap.SOAPElement;
import javax.xml.soap.SOAPException;
import java.io.Reader;
import java.io.Serializable;
import java.io.StringReader;
import java.io.StringWriter;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;

/*
 * MessageElement is the base type of nodes of the SOAP message parse tree.
 *
 * Note: it was made Serializable to help users of Apache SOAP who had
 * exploited the serializability of the DOM tree to migrate to Axis.
 */
public class MessageElement extends NodeImpl implements SOAPElement,
        Serializable,
        org.w3c.dom.NodeList,  // ADD Nodelist Interfaces for SAAJ 1.2
        Cloneable
{
    protected static Log log =
        LogFactory.getLog(MessageElement.class.getName());

    private static final Mapping enc11Mapping =
            new Mapping(Constants.URI_SOAP11_ENC,
                        "SOAP-ENC");

    private static final Mapping enc12Mapping =
            new Mapping(Constants.URI_SOAP12_ENC,
                        "SOAP-ENC");

    protected String    id;
    protected String    href;
    protected boolean   _isRoot = true;
    protected SOAPEnvelope message = null;

    protected transient DeserializationContext context;

    protected transient QName typeQName = null;

    protected Vector qNameAttrs = null;

    // Some message representations - as recorded SAX events...
    protected transient SAX2EventRecorder recorder = null;
    protected int startEventIndex = 0;
    protected int startContentsIndex = 0;
    protected int endEventIndex = -1;

    public ArrayList namespaces = null;

    /** Our encoding style, if any */
    protected String encodingStyle = null;

    /** Object value, possibly supplied by subclass */
    private Object objectValue = null;

    /** No-arg constructor for building messages?
     */
    public MessageElement() 
    {
    }

    public MessageElement(String namespace, String localPart)
    {
        namespaceURI = namespace;
        name = localPart;
    }

    public MessageElement(String localPart, String prefix, String namespace)
    {
        this.namespaceURI = namespace;
        this.name = localPart;
        this.prefix = prefix;
        addMapping(new Mapping(namespace, prefix));
    }

    public MessageElement(Name eltName) 
    {
        this(eltName.getLocalName(),eltName.getPrefix(), eltName.getURI());
    }

    public MessageElement(String namespace, String localPart, Object value)
    {
        this(namespace, localPart);
        objectValue = value;
    }

    public MessageElement(QName name) 
    {
        this(name.getNamespaceURI(), name.getLocalPart());
    }

    public MessageElement(QName name, Object value)
    {
        this(name.getNamespaceURI(), name.getLocalPart());
        objectValue = value;
    }

    public MessageElement(Element elem)
    {
        namespaceURI = elem.getNamespaceURI();
        name = elem.getLocalName();
        copyNode(elem);
    }

    public MessageElement(CharacterData text)
    {
        textRep = text;
        namespaceURI = text.getNamespaceURI();
        name = text.getLocalName();
    }

    public MessageElement(String namespace, String localPart, String prefix,
                   Attributes attributes, DeserializationContext context)
        throws AxisFault
    {
        if (log.isDebugEnabled()) {
            log.debug(Messages.getMessage("newElem00", super.toString(),
                                            "{" + prefix + "}" + localPart));
            for (int i = 0; attributes != null && i < attributes.getLength(); i++) {
                log.debug("  " + attributes.getQName(i) + " = '" + attributes.getValue(i) + "'");
            }
        }
        this.namespaceURI = namespace;
        this.name = localPart;
        this.prefix = prefix;

        this.context = context;
        this.startEventIndex = context.getStartOfMappingsPos();

        setNSMappings(context.getCurrentNSMappings());

        this.recorder = context.getRecorder();

        if (attributes != null && attributes.getLength() > 0) {
            this.attributes = attributes;

            typeQName = context.getTypeFromAttributes(namespace,
                                                      localPart,
                                                      attributes);

            String rootVal = attributes.getValue(Constants.URI_DEFAULT_SOAP_ENC, Constants.ATTR_ROOT);
            if (rootVal != null)
                _isRoot = rootVal.equals("1");

            id = attributes.getValue(Constants.ATTR_ID);
            // Register this ID with the context.....
            if (id != null) {
                context.registerElementByID(id, this);
                if (recorder == null) {
                    recorder = new SAX2EventRecorder();
                    context.setRecorder(recorder);
                }
            }

            // Set the encoding style to the attribute value.  If null,
            // we just automatically use our parent's (see getEncodingStyle)
            MessageContext mc = context.getMessageContext();
            SOAPConstants sc = (mc != null) ?
                                            mc.getSOAPConstants() :
                                            SOAPConstants.SOAP11_CONSTANTS;

            href = attributes.getValue(sc.getAttrHref());

            // If there's an arrayType attribute, we can pretty well guess that we're an Array???
            if (attributes.getValue(Constants.URI_DEFAULT_SOAP_ENC, Constants.ATTR_ARRAY_TYPE) != null)
                typeQName = Constants.SOAP_ARRAY;


            encodingStyle =
                    attributes.getValue(sc.getEncodingURI(),
                                        Constants.ATTR_ENCODING_STYLE);

            // if no-encoding style was defined, we don't define as well
            if (Constants.URI_SOAP12_NOENC.equals(encodingStyle))
                encodingStyle = null;

            // If we have an encoding style, and are not a MESSAGE style
            // operation (in other words - we're going to do some data 
            // binding), AND we're SOAP 1.2, check the encoding style against
            // the ones we've got type mappings registered for.  If it isn't
            // registered, throw a DataEncodingUnknown fault as per the
            // SOAP 1.2 spec.
            if (encodingStyle != null &&
                    sc.equals(SOAPConstants.SOAP12_CONSTANTS) &&
                    (mc.getOperationStyle() != Style.MESSAGE)) {
                TypeMapping tm = mc.getTypeMappingRegistry().
                        getTypeMapping(encodingStyle);
                if (tm == null ||
                        (tm.equals(mc.getTypeMappingRegistry().
                                                getDefaultTypeMapping()))) {
                    AxisFault badEncodingFault = new AxisFault(
                            Constants.FAULT_SOAP12_DATAENCODINGUNKNOWN,
                            "bad encoding style", null, null);
                    throw badEncodingFault;
                }
            }

        }
    }

    /** !!! TODO : Make sure this handles multiple targets
     */
    Deserializer fixupDeserializer;

    public void setFixupDeserializer(Deserializer dser)
    {
        // !!! Merge targets here if already set?
        fixupDeserializer = dser;
    }

    public Deserializer getFixupDeserializer()
    {
        return fixupDeserializer;
    }
 
    public void setEndIndex(int endIndex)
    {
        endEventIndex = endIndex;
        //context.setRecorder(null);
    }

    public boolean isRoot() { return _isRoot; }
    public String getID() { return id; }

    public String getHref() { return href; }

    public Attributes getAttributesEx() { return attributes; }


    /**
     * Returns a duplicate of this node, i.e., serves as a generic copy
     * constructor for nodes. The duplicate node has no parent; (
     * <code>parentNode</code> is <code>null</code>.).
     * <br>Cloning an <code>Element</code> copies all attributes and their
     * values, including those generated by the XML processor to represent
     * defaulted attributes, but this method does not copy any text it
     * contains unless it is a deep clone, since the text is contained in a
     * child <code>Text</code> node. Cloning an <code>Attribute</code>
     * directly, as opposed to be cloned as part of an <code>Element</code>
     * cloning operation, returns a specified attribute (
     * <code>specified</code> is <code>true</code>). Cloning any other type
     * of node simply returns a copy of this node.
     * <br>Note that cloning an immutable subtree results in a mutable copy,
     * but the children of an <code>EntityReference</code> clone are readonly
     * . In addition, clones of unspecified <code>Attr</code> nodes are
     * specified. And, cloning <code>Document</code>,
     * <code>DocumentType</code>, <code>Entity</code>, and
     * <code>Notation</code> nodes is implementation dependent.
     * 
     * @param deep If <code>true</code>, recursively clone the subtree under
     *             the specified node; if <code>false</code>, clone only the node
     *             itself (and its attributes, if it is an <code>Element</code>).
     * @return The duplicate node.
     */
    public Node cloneNode(boolean deep) {
        try{
            MessageElement clonedSelf = (MessageElement) clonning();

            if(deep == true){
                if(children != null){
                    for(int i =0; i < children.size(); i++){
                        NodeImpl child = (NodeImpl)children.get(i);
                        if(child != null) {  // why child can be null?
                            NodeImpl clonedChild = (NodeImpl)child.cloneNode(deep); // deep == true
                            clonedChild.setParent(clonedSelf);
                            clonedChild.setOwnerDocument(soapPart);
                        }
                    }
                }
            }
            return clonedSelf;
        }
        catch(Exception e){
            return null;
        }
    }
    /**
     *  protected clone method (not public)
     *
     *  copied status
     *  -------------------
     *  protected String    name ;             Y
     *  protected String    prefix ;           Y
     *  protected String    namespaceURI ;     Y
     *  protected transient Attributes attributes  Y
     *  protected String    id;               Y?
     *  protected String    href;             Y?
     *  protected boolean   _isRoot = true;   Y?
     *  protected SOAPEnvelope message = null; N?
     *  protected transient DeserializationContext context;  Y?
     *  protected transient QName typeQName = null;          Y?
     *  protected Vector qNameAttrs = null;                  Y?
     *  protected transient SAX2EventRecorder recorder = null; N?
     *  protected int startEventIndex = 0;                   N?
     *  protected int startContentsIndex = 0;                N?
     *  protected int endEventIndex = -1;                    N?
     *  protected CharacterData textRep = null;             Y?
     *  protected MessageElement parent = null;             N
     *  public ArrayList namespaces = null;                 Y
     *  protected String encodingStyle = null;              N?
     *   private Object objectValue = null;                 N?
     *
     * @return
     * @throws CloneNotSupportedException
     */
    protected Object clonning() throws CloneNotSupportedException
    {
        try{
            MessageElement clonedME = null;
            clonedME = (MessageElement)this.clone();

            clonedME.setName(name);
            clonedME.setNamespaceURI(namespaceURI);
            clonedME.setPrefix(prefix);

            // new AttributesImpl will copy all data not set referencing only
            clonedME.setAllAttributes(new AttributesImpl(attributes));
            //       clonedME.addNamespaceDeclaration((namespaces.clone()); // cannot do this. since we cannot access the namepace arraylist

            clonedME.namespaces = new ArrayList();
            if(namespaces != null){
                for(int i = 0; i < namespaces.size(); i++){
                    //     jeus.util.Logger.directLog( " Debug :  namspace.size() = " + namespaces.size());
                    Mapping namespace = (Mapping)namespaces.get(i);
                    clonedME.addNamespaceDeclaration(namespace.getPrefix(), namespace.getNamespaceURI()); // why exception here!!
                }
            }
            // clear reference to old children
            clonedME.detachAllChildren();

            // clear parents relationship to old parent
            clonedME.setParent(null);
            // clonedME.setObjectValue(objectValue); // how to copy this???
            clonedME.setDirty(this._isDirty);
            if(encodingStyle != null){
                clonedME.setEncodingStyle(new String(encodingStyle));
            }
            clonedME.setRecorder(recorder);
            return clonedME;
        }catch(Exception ex){
            return null;
        }
    }

    // called in MESerialaizationContext
    public void setAllAttributes(Attributes attrs){
        attributes = attrs;
    }

    public void detachAllChildren()
    {
        removeContents();
    }
    
    /**
     * Obtain an Attributes collection consisting of all attributes
     * for this MessageElement, including namespace declarations.
     *
     * @return Attributes collection
     */
    public Attributes getCompleteAttributes() {
        if (namespaces == null)
            return attributes;
        
        AttributesImpl attrs = null;
        if (attributes == NullAttributes.singleton)
            attrs = new AttributesImpl();
        else
            attrs = new AttributesImpl(attributes);
        
        for (Iterator iterator = namespaces.iterator(); iterator.hasNext();) {
            Mapping mapping = (Mapping) iterator.next();
            String prefix = mapping.getPrefix();
            String nsURI = mapping.getNamespaceURI();
            attrs.addAttribute(Constants.NS_URI_XMLNS, prefix,
                               "xmlns:" + prefix, nsURI, "CDATA");
        }
        return attrs;
    }

    public String getName() { return( name ); }
    public void setName(String name) { this.name = name; }
    
    public QName getQName() { return new QName(namespaceURI, name); }
    public void setQName(QName qName) {
        this.name = qName.getLocalPart();
        this.namespaceURI = qName.getNamespaceURI();
    }

    public void setNamespaceURI(String nsURI) { namespaceURI = nsURI; }

    public QName getType() {
        // Try to get the type from our target if we're a reference...
        if (typeQName == null && href != null && context != null) {
            MessageElement referent = context.getElementByID(href);
            if (referent != null) {
                typeQName = referent.getType();
            }
        }
        return typeQName;
    }

    public void setType(QName qname) {
        typeQName = qname;
    }

    public SAX2EventRecorder getRecorder() { return recorder; }
    public void setRecorder(SAX2EventRecorder rec) { recorder = rec; }

    /**
     * Get the encoding style.  If ours is null, walk up the hierarchy
     * and use our parent's.  Default if we're the root is "".
     *
     * @return the currently in-scope encoding style
     */
    public String getEncodingStyle() {
        if (encodingStyle == null) {
            if (parent == null)
                return "";
            return ((MessageElement)parent).getEncodingStyle();
        }
        return encodingStyle;
    }

    public void removeContents() {
        // unlink
        if(children != null) {
            for(int i = 0; i < children.size(); i++){
                try{
                    ((NodeImpl)children.get(i)).setParent(null);
                }catch(Exception e){
                }
            }
            // empty the collection
            children.clear();
            setDirty(true);
        }
    }

    public Iterator getVisibleNamespacePrefixes() {
        Vector prefixes = new Vector();

        // Add all parents namespace definitions
        if(parent !=null){
            Iterator parentsPrefixes = ((MessageElement)parent).getVisibleNamespacePrefixes();
            if(parentsPrefixes != null){
                while(parentsPrefixes.hasNext()){
                    prefixes.add(parentsPrefixes.next());
                }
            }
        }
        Iterator mine = getNamespacePrefixes();
        if(mine != null){
            while(mine.hasNext()){
                prefixes.add(mine.next());
            }
        }
        return prefixes.iterator();
    }

    /**
     * Sets the encoding style for this <CODE>SOAPElement</CODE>
     * object to one specified. The semantics of a null value,
     * as above in getEncodingStyle() are to just use the parent's value,
     * but null here means set to "".
     *
     * @param   encodingStyle a <CODE>String</CODE>
     *     giving the encoding style
     * @throws  java.lang.IllegalArgumentException  if
     *     there was a problem in the encoding style being set.
     * @see #getEncodingStyle() getEncodingStyle()
     */
    public void setEncodingStyle(String encodingStyle) throws SOAPException { 
        if (encodingStyle == null) {
            encodingStyle = "";
        }

        this.encodingStyle = encodingStyle;

        // Wherever we set the encoding style, map the SOAP-ENC prefix
        // just for fun (if it's a known style)
        if (encodingStyle.equals(Constants.URI_SOAP11_ENC)) {
            addMapping(enc11Mapping);
        } else if (encodingStyle.equals(Constants.URI_SOAP12_ENC)) {
            addMapping(enc12Mapping);
        }
    }

    /**
     * Note that this method will log a error and no-op if there is
     * a value (set using setObjectValue) in the MessageElement.
     */
    public void addChild(MessageElement el) throws SOAPException
    {
        if (objectValue != null) {
            SOAPException exc = 
                new SOAPException(Messages.getMessage("valuePresent"));
            log.error(Messages.getMessage("valuePresent"), exc);
            throw exc;
        }
        initializeChildren();
        children.add(el);
        el.parent = this;
    }

    public List getChildren()
    {
        return children;
    }

    public void setContentsIndex(int index) 
    {
        startContentsIndex = index;
    }
 
    public void setNSMappings(ArrayList namespaces)
    {
        this.namespaces = namespaces;
    }

    public String getPrefix(String namespaceURI) {
        if ((namespaceURI == null) || (namespaceURI.equals("")))
            return null;

        if (href != null && getRealElement() != null) {
            return getRealElement().getPrefix(namespaceURI);
        }

        for (int i = 0; namespaces != null && i < namespaces.size(); i++) {
            Mapping map = (Mapping)namespaces.get(i);
            if (map.getNamespaceURI().equals(namespaceURI))
                return map.getPrefix();
        }

        if (parent != null)
            return ((MessageElement)parent).getPrefix(namespaceURI);

        return null;
    }

    public String getNamespaceURI(String prefix) {
        if (prefix == null)
            prefix = "";

        if (href != null && getRealElement() != null) {
            return getRealElement().getNamespaceURI(prefix);
        }

        for (int i = 0; namespaces != null && i < namespaces.size(); i++) {
            Mapping map = (Mapping)namespaces.get(i);
            if (map.getPrefix().equals(prefix)) {
                return map.getNamespaceURI();
            }
        }

        if (parent != null)
            return ((MessageElement)parent).getNamespaceURI(prefix);

        if (log.isDebugEnabled()) {
            log.debug(Messages.getMessage("noPrefix00", "" + this, prefix));
        }

        return null;
    }

    /**
     * Returns value of the node as an object of registered type.
     * @return Object of proper type, or null if no mapping could be found.
     */
    public Object getObjectValue() {
        Object obj = null;
        try {
            obj = getObjectValue(null);
        } catch (Exception e) {
            log.debug("getValue()", e);
        }
        return obj;
    }

    /**
     * Returns value of the node as an object of registered type.
     * @param cls Class that contains top level deserializer metadata
     * @return Object of proper type, or null if no mapping could be found.
     */
    public Object getObjectValue(Class cls) throws Exception {
        if (objectValue == null) {
            objectValue = getValueAsType(getType(), cls);
        }
        return objectValue;
    }

    /**
     * Sets value of this node to an Object.
     * A serializer needs to be registered for this object class for proper
     * operation.
     * <p>
     * Note that this method will log an error and no-op if there are
     * any children in the MessageElement or if the MessageElement was
     * constructed from XML.
     * @param newValue node's value or null.
     */
    public void setObjectValue(Object newValue) throws SOAPException {
        if (children != null && !children.isEmpty()) {
            SOAPException exc = new SOAPException(Messages.getMessage("childPresent"));
            log.error(Messages.getMessage("childPresent"), exc);
            throw exc;
        }
        if (textRep != null) {
            SOAPException exc = new SOAPException(Messages.getMessage("xmlPresent"));
            log.error(Messages.getMessage("xmlPresent"), exc);
            throw exc;
        }
        this.objectValue = newValue;
    }

    public Object getValueAsType(QName type) throws Exception 
    {
        return getValueAsType(type, null);
    }

    public Object getValueAsType(QName type, Class cls) throws Exception 
    {
        if (context == null)
            throw new Exception(Messages.getMessage("noContext00"));

        Deserializer dser = null;
        if (cls == null) {
            dser = context.getDeserializerForType(type);
        } else {
            dser = context.getDeserializerForClass(cls);
        }
        if (dser == null)
            throw new Exception(Messages.getMessage("noDeser00", "" + type));

        boolean oldVal = context.isDoneParsing();
        ((DeserializationContextImpl)context).deserializing(true);
        context.pushElementHandler(new EnvelopeHandler((SOAPHandler)dser));

        publishToHandler((org.xml.sax.ContentHandler) context);

        ((DeserializationContextImpl)context).deserializing(oldVal);

        return dser.getValue();
    }

    protected static class QNameAttr {
        QName name;
        QName value;
    }

    public void addAttribute(String namespace, String localName,
                             QName value)
    {
        if (qNameAttrs == null)
            qNameAttrs = new Vector();

        QNameAttr attr = new QNameAttr();
        attr.name = new QName(namespace, localName);
        attr.value = value;

        qNameAttrs.addElement(attr);
        // !!! Add attribute to attributes!
    }

    public void addAttribute(String namespace, String localName,
                             String value)
    {
        AttributesImpl attributes = makeAttributesEditable();
        attributes.addAttribute(namespace, localName, "", "CDATA",
                                value);
    }

    public void addAttribute(String prefix, String namespace, String localName,
                             String value)
    {
        AttributesImpl attributes = makeAttributesEditable();
        String attrName = localName;
        if (prefix != null && prefix.length() > 0) {
            attrName = prefix + ":" + localName;
        }
        attributes.addAttribute(namespace, localName, attrName, "CDATA",
                                value);
    }

    /**
     * Set an attribute, adding the attribute if it isn't already present
     * in this element, and changing the value if it is.  Passing null as the
     * value will cause any pre-existing attribute by this name to go away.
     */
    public void setAttribute(String namespace, String localName,
                             String value)
    {
        AttributesImpl attributes = makeAttributesEditable();

        int idx = attributes.getIndex(namespace, localName);
        if (idx > -1) {
            // Got it, so replace it's value.
            if (value != null) {
                attributes.setValue(idx, value);
            } else {
                attributes.removeAttribute(idx);
            }
            return;
        }

        addAttribute(namespace, localName, value);
    }

    public String getAttributeValue(String localName)
    {
        if (attributes == null) {
           return null;
        }
        return attributes.getValue(localName);
    }

    public void setEnvelope(SOAPEnvelope env)
    {
        env.setDirty(true);
        message = env;
    }

    public SOAPEnvelope getEnvelope() 
    {
        return message;
    }

    public MessageElement getRealElement()
    {
        if (href == null)
            return this;

        Object obj = context.getObjectByRef(href);
        if (obj == null)
            return null;

        if (!(obj instanceof MessageElement))
            return null;

        return (MessageElement)obj;
    }

    public Document getAsDocument() throws Exception 
    {
        String elementString = getAsString();

        Reader reader = new StringReader(elementString);
        Document doc = XMLUtils.newDocument(new InputSource(reader));
        if (doc == null)
            throw new Exception(
                    Messages.getMessage("noDoc00", elementString));
        return doc;
    }

    public String getAsString() throws Exception {
        SerializationContext serializeContext = null;
        StringWriter writer = new StringWriter();
        MessageContext msgContext;
        if (context != null) {
            msgContext = context.getMessageContext();
        } else {
            msgContext = MessageContext.getCurrentContext();
        }
        serializeContext = new SerializationContextImpl(writer, msgContext);
        serializeContext.setSendDecl(false);
        output(serializeContext);
        writer.close();

        return writer.getBuffer().toString();
    }

    public Element getAsDOM() throws Exception 
    {
        return getAsDocument().getDocumentElement();
    }

    public void publishToHandler(ContentHandler handler) throws SAXException
    {
        if (recorder == null)
            throw new SAXException(Messages.getMessage("noRecorder00"));

        recorder.replay(startEventIndex, endEventIndex, handler);
    }

    public void publishContents(ContentHandler handler) throws SAXException 
    {
        if (recorder == null)
            throw new SAXException(Messages.getMessage("noRecorder00"));

        recorder.replay(startContentsIndex, endEventIndex-1, handler);
    }

    /** This is the public output() method, which will always simply use
     * the recorded SAX stream for this element if it is available.  If
     * not, this method calls outputImpl() to allow subclasses and
     * programmatically created messages to serialize themselves.
     *
     * @param context the SerializationContext we will write to.
     */
    public final void output(SerializationContext context) throws Exception
    {
        if ((recorder != null) && (!_isDirty)) {
            recorder.replay(startEventIndex,
                            endEventIndex,
                            new SAXOutputter(context));
            return;
        }

        // Turn QName attributes into strings
        if (qNameAttrs != null) {
            for (int i = 0; i < qNameAttrs.size(); i++) {
                QNameAttr attr = (QNameAttr)qNameAttrs.get(i);
                QName attrName = attr.name;
                setAttribute(attrName.getNamespaceURI(),
                             attrName.getLocalPart(),
                             context.qName2String(attr.value));
            }
        }

        /**
         * Write the encoding style attribute IF it's different from
         * whatever encoding style is in scope....
         */
        if (encodingStyle != null) {
            MessageContext mc = context.getMessageContext();
            SOAPConstants soapConstants = (mc != null) ?
                                            mc.getSOAPConstants() :
                                            SOAPConstants.SOAP11_CONSTANTS;
            if (parent == null) {
                // don't emit an encoding style if its "" (literal)
                if (!encodingStyle.equals("")) {
                    setAttribute(soapConstants.getEnvelopeURI(),
                                 Constants.ATTR_ENCODING_STYLE,
                                 encodingStyle);
                }
            } else if (!encodingStyle.equals(((MessageElement)parent).getEncodingStyle())) {
                setAttribute(soapConstants.getEnvelopeURI(),
                             Constants.ATTR_ENCODING_STYLE,
                             encodingStyle);
            }
        }

        outputImpl(context);
    }

    /** Subclasses can override
     */
    protected void outputImpl(SerializationContext context) throws Exception 
    {
        if (textRep != null) {
            boolean oldPretty = context.getPretty();
            context.setPretty(false);
            if (textRep instanceof CDATASection) {
                context.writeString("<![CDATA[");
                context.writeString(((Text)textRep).getData());
                context.writeString("]]>");
            } else if (textRep instanceof Comment) {
                context.writeString("<!--");
                context.writeString(((CharacterData)textRep).getData());
                context.writeString("-->");
            } else if (textRep instanceof Text) {
                context.writeSafeString(((Text)textRep).getData());
            }
            context.setPretty(oldPretty);
            return;
        }

        if (prefix != null)
            context.registerPrefixForURI(prefix, namespaceURI);

        if (namespaces != null) {
            for (Iterator i = namespaces.iterator(); i.hasNext();) {
                Mapping mapping = (Mapping) i.next();
                context.registerPrefixForURI(mapping.getPrefix(), mapping.getNamespaceURI());
            }
        }            

        if (objectValue != null) {
            context.serialize(new QName(namespaceURI, name),
                              attributes,
                              objectValue, null, false, null);
            return;
        }

        context.startElement(new QName(namespaceURI, name), attributes);
        if (children != null) {
            for (Iterator it = children.iterator(); it.hasNext();) {
                ((NodeImpl)it.next()).output(context);
            }
        }
        context.endElement();
    }

    public String toString() {
        try {
            return getAsString();
        }
        catch( Exception exp ) {
            log.error(Messages.getMessage("exception00"), exp);
            return null;
        }
    }

    public void addMapping(Mapping map) {
        if (namespaces == null) 
            namespaces = new ArrayList();
        namespaces.add(map);
    }

    // JAXM SOAPElement methods...

    public SOAPElement addChildElement(Name name) throws SOAPException {
        MessageElement child = new MessageElement(name.getLocalName(), 
                                                  name.getPrefix(),
                                                  name.getURI());
        addChild(child);
        return child;
    }

    public SOAPElement addChildElement(String localName) throws SOAPException {
        // Inherit parent's namespace
        MessageElement child = new MessageElement(getNamespaceURI(),
                                                  localName);
        addChild(child);
        return child;
    }

    public SOAPElement addChildElement(String localName,
                                       String prefix) throws SOAPException {
        MessageElement child = new MessageElement(getNamespaceURI(prefix),
                                                  localName);
        child.setPrefix(prefix);
        addChild(child);
        return child;
    }

    public SOAPElement addChildElement(String localName,
                                       String prefix,
                                       String uri) throws SOAPException {
        MessageElement child = new MessageElement(uri, localName);
        child.setPrefix(prefix);
        child.addNamespaceDeclaration(prefix, uri);
        addChild(child);
        return child;
    }

    /**
     * The added child must be an instance of MessageElement rather than
     * an abitrary SOAPElement otherwise a (wrapped) ClassCastException
     * will be thrown.
     */
    public SOAPElement addChildElement(SOAPElement element)
        throws SOAPException {
        try {
            addChild((MessageElement)element);
            setDirty(true);
            return element;
        } catch (ClassCastException e) {
            throw new SOAPException(e);
        }
    }

    /**
     * Text nodes are not supported.
     */
    public SOAPElement addTextNode(String s) throws SOAPException {
        org.apache.axis.message.Text text = new org.apache.axis.message.Text(s);
        try {
            appendChild(text);
            return this;
        } catch (ClassCastException e) {
            throw new SOAPException(e);
        }
    }

    public SOAPElement addAttribute(Name name, String value)
        throws SOAPException {
        try {
            addAttribute(name.getPrefix(), name.getURI(), name.getLocalName(), value);
        } catch (RuntimeException t) {
            throw new SOAPException(t);
        }
        return this;
    }

    public SOAPElement addNamespaceDeclaration(String prefix,
                                               String uri)
        throws SOAPException {
        try {
            Mapping map = new Mapping(uri, prefix);
            addMapping(map);
        } catch (RuntimeException t) {
            throw new SOAPException(t);
        }
        return this;
    }

    public String getAttributeValue(Name name) {
        return attributes.getValue(name.getURI(), name.getLocalName());
    }

    public Iterator getAllAttributes() {
        int num = attributes.getLength();
        Vector attrs = new Vector(num);
        for (int i = 0; i < num; i++) {
            String q = attributes.getQName(i);
            String prefix = "";
            if (q != null) {
                int idx = q.indexOf(":");
                if (idx > 0) {
                    prefix = q.substring(0, idx);
                } else {
                    prefix= "";
                }
            }

            attrs.add(new PrefixedQName(attributes.getURI(i),
                                        attributes.getLocalName(i),
                                        prefix));
        }
        return attrs.iterator();
    }

    // getNamespaceURI implemented above

    public Iterator getNamespacePrefixes() {
        Vector prefixes = new Vector();
        for (int i = 0; namespaces != null && i < namespaces.size(); i++) {
            prefixes.add(((Mapping)namespaces.get(i)).getPrefix());
        }
        return prefixes.iterator();
    }

    public Name getElementName() {
        return new PrefixedQName(getNamespaceURI(), getName(), getPrefix());
    }

    public boolean removeAttribute(Name name) {
        AttributesImpl attributes = makeAttributesEditable();
        boolean removed = false;

        for (int i = 0; i < attributes.getLength() && !removed; i++) {
            if (attributes.getURI(i).equals(name.getURI()) &&
                attributes.getLocalName(i).equals(name.getLocalName())) {
                attributes.removeAttribute(i);
                removed = true;
            }
        }
        return removed;
    }

    public boolean removeNamespaceDeclaration(String prefix) {
        makeAttributesEditable();
        boolean removed = false;

        for (int i = 0; namespaces != null && i < namespaces.size() && !removed; i++) {
            if (((Mapping)namespaces.get(i)).getPrefix().equals(prefix)) {
                namespaces.remove(i);
                removed = true;
            }
        }
        return removed;
    }

    public Iterator getChildElements() {
        initializeChildren();
        return children.iterator();
    }

    /**
     * Convenience method to get the first matching child for a given QName.
     * 
     * @param qname
     * @return
     */
    public MessageElement getChildElement(QName qname) {
        if (children != null) {
            for (Iterator i = children.iterator(); i.hasNext();) {
                MessageElement child = (MessageElement) i.next();
                if (child.getQName().equals(qname))
                    return child;
            }
        }
        return null;
    }

    public Iterator getChildElements(QName qname) {
        initializeChildren();
        int num = children.size();
        Vector c = new Vector(num);
        for (int i = 0; i < num; i++) {
            MessageElement child = (MessageElement)children.get(i);
            Name cname = child.getElementName();
            if (cname.getURI().equals(qname.getNamespaceURI()) &&
                cname.getLocalName().equals(qname.getLocalPart())) {
                c.add(child);
            }
        }
        return c.iterator();
    }

    public Iterator getChildElements(Name name) {
        return getChildElements(new QName(name.getURI(), name.getLocalName()));
    }

    public String getTagName() {
        return prefix == null ? name : prefix + ":" + name;
    }

    public void removeAttribute(String name) throws DOMException {
        AttributesImpl impl =  (AttributesImpl)attributes;
        int index = impl.getIndex(name);
        if(index >= 0){
            AttributesImpl newAttrs = new AttributesImpl();
            // copy except the removed attribute
            for(int i = 0; i < impl.getLength(); i++){ // shift after removal
                if(i != index){
                    String uri = impl.getURI(i);
                    String local = impl.getLocalName(i);
                    String qname = impl.getQName(i);
                    String type = impl.getType(i);
                    String value = impl.getValue(i);
                    newAttrs.addAttribute(uri,local,qname,type,value);
                }
            }
            // replace it
            attributes = newAttrs;
        }
    }

    public boolean hasAttribute(String name) {
        if(name == null)  // Do I have to send an exception?
            name = "";

        for(int i = 0; i < attributes.getLength(); i++){
            if(name.equals(attributes.getQName(i)))
                return true;
        }
        return false;
    }

    public String getAttribute(String name) {
        return attributes.getValue(name);
    }

    public void removeAttributeNS(String namespaceURI, String localName) throws DOMException {
        makeAttributesEditable();
        Name name =  new PrefixedQName(namespaceURI, localName, null);
        removeAttribute(name);
    }

    public void setAttribute(String name, String value) throws DOMException {
        AttributesImpl impl =  makeAttributesEditable();
        int index = impl.getIndex(name);
        if(index < 0){ // not found
            String uri = "";
            String localname  = name;
            String qname = name;     
            String type = "CDDATA";  
            impl.addAttribute(uri,localname,qname,type,value);
        }else{         // found
            impl.setLocalName(index, value);
        }
    }

    public boolean hasAttributeNS(String namespaceURI, String localName) {
        if(namespaceURI == null)
            namespaceURI ="";
        if(localName == null)  // Do I have to send an exception? or just return false
            localName = "";

        for(int i = 0; i < attributes.getLength(); i++){
            if( namespaceURI.equals(attributes.getURI(i))
                    && localName.equals(attributes.getLocalName(i)))
                return true;
        }
        return false;
    }

    public Attr getAttributeNode(String name) {
        return null;  //TODO: Fix this for SAAJ 1.2 Implementation
    }

    public Attr removeAttributeNode(Attr oldAttr) throws DOMException {
        makeAttributesEditable();
        Name name =  new PrefixedQName(oldAttr.getNamespaceURI(), oldAttr.getLocalName(), oldAttr.getPrefix());
        removeAttribute(name);
        return oldAttr;
    }

    public Attr setAttributeNode(Attr newAttr) throws DOMException {
        return newAttr;
    }

    public Attr setAttributeNodeNS(Attr newAttr) throws DOMException {
        //attributes.
        AttributesImpl attributes = makeAttributesEditable();
        // how to convert to DOM ATTR
        attributes.addAttribute(newAttr.getNamespaceURI(),
                newAttr.getLocalName(),
                newAttr.getLocalName(),
                "CDATA",
                newAttr.getValue());
        return null;
    }

    public NodeList getElementsByTagName(String name) {
        //use this MessageElement class for Nodelist store
        MessageElement nodelist = new MessageElement();

        try{
            if(children != null){
                // add 2nd Generation
                for(int i =0; i < children.size(); i++){
                    nodelist.addChild((MessageElement)children.get(i));
                }
                // add 3rd Generation
                for(int i =0; i < children.size(); i++){
                    MessageElement child = (MessageElement)children.get(i);
                    NodeList grandsons = child.getElementsByTagName(name);
                    for(int j =0; j < children.size(); j++){
                        nodelist.addChild((MessageElement)grandsons.item(j));
                    }
                }
            }
        }catch(SOAPException se){
            // Shame on me
        }
        return nodelist;
    }

    public String getAttributeNS(String namespaceURI, String localName) {
        for (int i = 0; i < attributes.getLength(); i++) {
            if (attributes.getURI(i).equals(namespaceURI) &&
                    attributes.getLocalName(i).equals(localName)) {
                return  attributes.getValue(i);
            }
        }
        return null;
    }

    public void setAttributeNS(String namespaceURI, String qualifiedName, 
                               String value) 
        throws DOMException 
    {
        AttributesImpl attributes = makeAttributesEditable();
        String localName =  qualifiedName.substring(qualifiedName.indexOf(":")+1, qualifiedName.length());

        if(namespaceURI == null){
            namespaceURI = "intentionalNullURI";
        }
        attributes.addAttribute(namespaceURI,
                localName,
                qualifiedName,
                "CDATA",
                value);
    }

    public Attr getAttributeNodeNS(String namespaceURI, String localName) {
        return null;  //TODO: Fix this for SAAJ 1.2 Implementation
    }

    public NodeList getElementsByTagNameNS(String namespaceURI, 
                                           String localName) 
    {
        return getElementsNS(this,namespaceURI,localName);
    }

    /**
     * helper method for recusively getting the element that has namespace URI and localname
     */
    protected NodeList getElementsNS(org.w3c.dom.Element parent,
                                     String namespaceURI, String localName)
    {
        NodeList children = parent.getChildNodes();
        NodeListImpl matches = new NodeListImpl();

        for(int i =0; i < children.getLength();  i++){
            if(children.item(i) instanceof Text)
                continue;
            Element child = (Element) children.item(i);
            if (namespaceURI.equals(child.getNamespaceURI()) &&
                    localName.equals(child.getLocalName())) {
                matches.addNode(child);
            }
            // search the grand-children.
            matches.addNodeList(child.getElementsByTagNameNS(namespaceURI,
                    localName));
        }
        return matches;
    }
    
    public Node item(int index) {
        if(children !=null && children.size() > index){
            return (Node)children.get(index);
        }else{
            return null;
        }
    }
    
    /**
     * The number of nodes in the list. The range of valid child node indices
     * is 0 to <code>length-1</code> inclusive.
     *
     * @since SAAJ 1.2 : Nodelist Interface
     */
    public int getLength() 
    {
        return (children == null) ? 0 : children.size();
    }

    // setEncodingStyle implemented above

    // getEncodingStyle() implemented above
    
    MessageElement findElement(Vector vec, String namespace,
                               String localPart) 
    {
        if (vec.isEmpty())
            return null;
     
        QName qname = new QName(namespace, localPart);
        Enumeration e = vec.elements();
        MessageElement element;
        while (e.hasMoreElements()) {
            element = (MessageElement)e.nextElement();
            if (element.getQName().equals(qname))
                return element;
        }
        
        return null;
    }
    
    public boolean equals(Object obj) 
    {
        if (obj == null || !(obj instanceof MessageElement))
            return false;
        return toString().equals(obj.toString());
    }

    private void copyNode(org.w3c.dom.Node element) {
        copyNode(this, element);
    }

    private void copyNode(MessageElement parent, org.w3c.dom.Node element)
    {
        parent.setPrefix(element.getPrefix());
        if(element.getLocalName() != null) {
            parent.setQName(new QName(element.getNamespaceURI(), element.getLocalName()));
        }

        org.w3c.dom.NamedNodeMap attrs = element.getAttributes();
        for(int i = 0; i < attrs.getLength(); i++){
            org.w3c.dom.Node att = attrs.item(i);
        if (att.getNamespaceURI() != null &&
                att.getPrefix() != null &&
                att.getNamespaceURI().equals(Constants.NS_URI_XMLNS) &&
                att.getPrefix().equals("xmlns")) {
                Mapping map = new Mapping(att.getNodeValue(), att.getLocalName());
                addMapping(map);
            }
            if(att.getLocalName() != null) {
                parent.addAttribute(att.getPrefix(),
                        att.getNamespaceURI(),
                        att.getLocalName(),
                        att.getNodeValue());
            } else if (att.getNodeName() != null) {
                parent.addAttribute(att.getPrefix(),
                        att.getNamespaceURI(),
                        att.getNodeName(),
                        att.getNodeValue());
            }
        }

        org.w3c.dom.NodeList children = element.getChildNodes();
        for(int i = 0; i < children.getLength(); i++){
            org.w3c.dom.Node child = children.item(i);
            if(child.getNodeType()==TEXT_NODE || 
               child.getNodeType()==CDATA_SECTION_NODE || 
               child.getNodeType()==COMMENT_NODE ) {
                MessageElement childElement = new MessageElement((CharacterData)child);
                parent.appendChild(childElement);
            } else {
                PrefixedQName qname = new PrefixedQName(child.getNamespaceURI(),
                        child.getLocalName(),
                        child.getPrefix());
                MessageElement childElement = new MessageElement(qname);
                parent.appendChild(childElement);
                copyNode(childElement, child);
            }
        }
    }

    public String getValue() {
        try {
            Element element = getAsDOM();
            if(element.hasChildNodes()){
                org.w3c.dom.Node node = element.getFirstChild();
                if(node.getNodeType()==org.w3c.dom.Node.TEXT_NODE){
                    return node.getNodeValue();
                }
            }
        } catch (Exception t){
            log.debug("getValue()", t);
        }
        return null;
    }
}
