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
 */

package org.apache.axis.wsdl.wsdl2ws.info;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;

import javax.wsdl.Binding;
import javax.wsdl.BindingInput;
import javax.wsdl.BindingOperation;
import javax.wsdl.Port;
import javax.wsdl.Service;
import javax.wsdl.WSDLElement;
import javax.wsdl.extensions.soap.SOAPBinding;
import javax.wsdl.extensions.soap.SOAPBody;
import javax.wsdl.extensions.soap.SOAPOperation;
import javax.wsdl.extensions.soap.SOAPAddress;
import javax.xml.namespace.QName;
import javax.xml.rpc.holders.BooleanHolder;
import javax.xml.rpc.holders.IntHolder;

import org.apache.axis.Constants;
import org.apache.axis.wsdl.gen.Parser;
import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.CContainedAttribute;
import org.apache.axis.wsdl.symbolTable.CElementDecl;
import org.apache.axis.wsdl.symbolTable.CSchemaUtils;
import org.apache.axis.wsdl.symbolTable.CollectionElement;
import org.apache.axis.wsdl.symbolTable.CollectionType;
import org.apache.axis.wsdl.symbolTable.DefinedElement;
import org.apache.axis.wsdl.symbolTable.SchemaUtils;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.axis.wsdl.symbolTable.SymTabEntry;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.toJava.Utils;
import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;


/**
 * This class initiates the collection of various bits of information needed by the 
 * wsdl2ws tool by parsing the WSDL file.
 * 
 * @author nadir amra
 *
 */
public class WSDLInfo
{
    // Private constants for retrieving extensibility elements.
    private static final int INSTANCEOF_SOAPBINDING   = 1;
    private static final int INSTANCEOF_SOAPADDRESS   = 2;
    private static final int INSTANCEOF_SOAPBODY      = 3;
    private static final int INSTANCEOF_SOAPOPERATION = 4;



    // verbose flag 
    private boolean c_verbose = false;
    
    // parser timeout value, in seconds. 0=no timeout. 
    private long c_timeout = 0;
    
    // URI to WSDL document. 
    private String c_URIToWSDLDocument = null;
    
    // Whether wrapper-style is not requested. 
    private boolean c_noWrapperStyle = false;
    
    // WSDL parser from the last time parse() was invoked. 
    private Parser c_wsdlParser = null;
    
    // Symbol table associated with the parser.
    private SymbolTable c_symbolTable = null;
    
    // Target name space of WSDL 
    private String c_targetNameSpaceOfWSDL = null;
    
    // Service definitions in WSDL 
    ArrayList c_services = new ArrayList();
    
    // Maps service definition to set of ports that use RPC binding style 
    ArrayList c_bindings = new ArrayList();
    
    
    /**
     * Constructor.
     */
    public WSDLInfo(String uri)
    {
        c_URIToWSDLDocument = uri;
    }
    
    /**
     * Initiates the parsing of the WSDL document. Returns the symbol table that is generated
     * by the parser. After parsing the WSDL document, various artifacts that the wsdl2ws tool needs
     * is collected for easy access.  
     * 
     * @throws Exception 
     */
    public SymbolTable parse() throws Exception
    {
        c_wsdlParser = new Parser();
        
        // Set verbose in WSDL parser
        c_wsdlParser.setVerbose(c_verbose);
        
        // Set timeout for parser, setTimeout method expects the time in milliseconds.
        c_wsdlParser.setTimeout(c_timeout*1000); 
        
        // Set unwrapped if requested
        c_wsdlParser.setNowrap(c_noWrapperStyle);

        // Parse the WSDL document.
        c_wsdlParser.run(c_URIToWSDLDocument);
        c_symbolTable =  c_wsdlParser.getSymbolTable();
        
        // Dump symbol table if in verbose mode.
        if (c_verbose)
            c_symbolTable.dump(System.out);
        
        // Collect various bits of information from the document.
        processWSDLDocument();

        // Return the symbol table
        return c_symbolTable;
    }

    /**
     * Sets the WSDL parser timeout value. 
     * 
     * @param t  timeout value in seconds. Null implies 0 timeout (no timeout).
     */
    public void setTimeout(String t)
    {
        if (t == null)
            t = "0"; 
        
        c_timeout = Long.parseLong(t);
    }
    
    /**
     * Sets the WSDL parser verbose mode. 
     * 
     * @param b  true=verbose; false=no verbose.
     */
    public void setVerbose(boolean b)
    {
        c_verbose = b;
    }
    
    /**
     * Indicates whether wrapper-style interfaces is allowed. 
     * 
     * @param b  true=no wrapper style; false=allow wrapper style.
     */
    public void setNoWrapperStyle(boolean b)
    {
        c_noWrapperStyle = b;
    }

    /**
     * Returns target name space of WSDL.
     * 
     * @return String representing the target name space of WSDL.
     */
    public String getTargetNameSpaceOfWSDL()
    {
        return c_targetNameSpaceOfWSDL;
    }

    /**
     * Returns array of services defined in WSDL.  The array
     * may be empty if service was not defined in WSDL.
     * 
     * @return array of java.wsdl.Service objects.
     */
    public ArrayList getServices()
    {
        return c_services;
    }
    
    /**
     * Returns end point URI for a Port by looking for the soap:address extensibility element.
     * 
     * @param port
     * @return
     */
    public static String getTargetEndPointURI(Port port)
    {
        SOAPAddress e = (SOAPAddress)getExtensibilityElement(port, INSTANCEOF_SOAPADDRESS);
        if (e != null)
            return e.getLocationURI();
        return null;
    }

    /**
     * Returns the transport URI in a soap:binding element.
     * 
     * @param binding
     * @return
     */
    public static String getTransportType(Binding binding)
    {
        SOAPBinding e = (SOAPBinding)getExtensibilityElement(binding, INSTANCEOF_SOAPBINDING);
        if (e != null)
            return e.getTransportURI();
        return null;
    }

    /**
     * Updates MethodInfo with information from the binding operation element.
     * 
     * @param bindingOp
     * @param method
     */
    public static void updateMethodInfoFromBinding(BindingOperation bindingOp, MethodInfo method)
    {
        // Get SOAPAction
        SOAPOperation e = (SOAPOperation)getExtensibilityElement(bindingOp, INSTANCEOF_SOAPOPERATION);
        if (e != null)
            method.setSoapAction(e.getSoapActionURI());
        
        // Get information about input operation
        BindingInput  bi = bindingOp.getBindingInput();
        SOAPBody body = (SOAPBody)getExtensibilityElement(bi, INSTANCEOF_SOAPBODY);
        if (body != null)
        {
            method.setInputNamespaceURI(body.getNamespaceURI());            
        }
    }
    
    /**
     * Returns list of Port objects in the specified service.  All ports in the list 
     * will have a binding style of document and uses the SOAP 1.1 binding. 
     * 
     * @param s service definition
     * @return list of ports that match the criteria described above.
     * @throws Exception
     */
    public ArrayList getPortsSOAP11Document(Service s) throws Exception
    {
        return getServicePorts(s, true, true, false, false);
    }
    
    /**
     * Returns list of Port objects in the specified service.  All ports in the list 
     * will have a binding style of rpc and uses the SOAP 1.1 binding. 
     * 
     * @param s service definition
     * @return list of ports that match the criteria described above.
     * @throws Exception
     */
    public ArrayList getPortsSOAP11RPC(Service s) throws Exception
    {
        return getServicePorts(s, false, true, false, false);
    }
    
    /**
     * Returns list of Port objects in the specified service.  All ports in the list 
     * will have a binding style of document and uses the SOAP 1.2 binding. 
     * 
     * @param s service definition
     * @return list of ports that match the criteria described above.
     * @throws Exception
     */
    public ArrayList getPortsSOAP12Document(Service s) throws Exception
    {
        return getServicePorts(s, true, false, true, false);
    }
    
    /**
     * Returns list of Port objects in the specified service.  All ports in the list 
     * will have a binding style of rpc and uses the SOAP 1.2 binding. 
     * 
     * @param s service definition
     * @return list of ports that match the criteria described above.
     * @throws Exception
     */
    public ArrayList getPortsSOAP12RPC(Service s) throws Exception
    {
        return getServicePorts(s, false, false, true, false);
    }
    
    /**
     * Returns list of Port objects in the specified service.  All ports in the list 
     * uses the HTTP binding. 
     * 
     * @param s
     * @param styleDocument
     * @return
     * @throws Exception
     */
    public ArrayList getPortsREST(Service s) throws Exception
    {
        return getServicePorts(s, true, false, false, true);
    }

    /**
     * Iterates through the symbol table, generating user-defined types and
     * storing the types in a hash table.
     * 
     * @return
     * @throws WrapperFault
     */
    public TypeMap generateTypeMap() throws WrapperFault
    {
        TypeMap typeMap = new TypeMap();
        if (c_symbolTable ==  null)
            return typeMap;
        
        Iterator it = c_symbolTable.getTypeIndex().values().iterator();
        while (it.hasNext())
        {
            TypeEntry type = (TypeEntry) it.next();
            Node node = type.getNode();
            if (node != null)
            {
                if (c_verbose)
                {
                    System.out.println( "==>getTypeInfo: Processing type...." + type.getQName());                    
                }
                                
                createTypeInfo(type, typeMap);
            }
        }
        
        return typeMap;
    }
  
    
    /**
     * Returns list of Port objects in a service definition based on selection criteria.
     * 
     * @param s              service definition.
     * @param styleDocument  true=return document style; false=return "rpc" style. 
     *                       This parameter is ignored for REST (HTTP) bindings.
     * @param soap11         true=return SOAP 1.1 bindings; false=SOAP 1.1 bindings are ignored.
     * @param soap12         true=return SOAP 1.2 bindings; false=SOAP 1.2 bindings are ignored.
     * @param rest           true=return HTTP bindings; false=ignore HTTP bindings.
     * @return               List of ports that match selection criteria.
     * @throws Exception
     */
    private ArrayList getServicePorts(Service s, 
                                      boolean styleDocument, 
                                      boolean soap11, 
                                      boolean soap12, 
                                      boolean rest) throws Exception
    {        
        ArrayList a = new ArrayList();
        
        if (s == null)
            return a;

        Iterator ports = s.getPorts().values().iterator();
        while (ports.hasNext())
        {
            Port p = (Port) ports.next();
            Binding b = p.getBinding();
            BindingEntry be = c_symbolTable.getBindingEntry(b.getQName());
            if (b == null || be == null)
                throw new WrapperFault("No binding exists for port '" + p.getName() + "'.");
            
            if ((be.getBindingType() == BindingEntry.TYPE_SOAP) && (soap11 || soap12))
            {
                String style = be.getBindingStyle().getName();
                if (style == null)
                    style = "rpc"; // TODO need to revisit.
                
                if ((styleDocument && style.equalsIgnoreCase("document"))
                        || (!styleDocument && style.equalsIgnoreCase("rpc")))
                {
                    String ns = Constants.URI_WSDL11_SOAP;
                    SOAPBinding soapbinding = (SOAPBinding)getExtensibilityElement(b, INSTANCEOF_SOAPBINDING);
                    if (soapbinding != null && null != soapbinding.getElementType().getNamespaceURI())
                        ns = soapbinding.getElementType().getNamespaceURI();
                        
                    if ((soap11 && ns.equals(Constants.URI_WSDL11_SOAP))
                            || (soap12 && ns.equals(Constants.URI_WSDL12_SOAP)))
                            a.add(p);
                }
            }
            else if (rest && (be.getBindingType() == BindingEntry.TYPE_HTTP_GET 
                                || be.getBindingType() == BindingEntry.TYPE_HTTP_POST))
            {
                a.add(p);
            }
        }
        
        return a;
    }
    
    /**
     * Collects all the information by the wsdl2ws tool.
     */
    private void processWSDLDocument() throws Exception
    {        
        // Get target name space of WSDL
        c_targetNameSpaceOfWSDL = c_symbolTable.getDefinition().getTargetNamespace();

        // Collect services and bindings.           
        Iterator it = c_symbolTable.getHashMap().values().iterator();
        while (it.hasNext())
        {
            Vector v = (Vector) it.next();
            for (int i = 0; i < v.size(); ++i)
            {
                SymTabEntry entry = (SymTabEntry) v.elementAt(i);

                if (entry instanceof org.apache.axis.wsdl.symbolTable.ServiceEntry)
                    c_services.add(((ServiceEntry) entry).getService());
                else if (entry instanceof org.apache.axis.wsdl.symbolTable.BindingEntry)
                    c_bindings.add(entry);
            }
        }
    }
    
    /**
     * Helper function that returns requested extensibility element.
     * 
     * @param e element to retrieve extensibility elements from.
     * @param clazz instance of class
     * @return extensibility element.
     */
    private static Object getExtensibilityElement(WSDLElement e, int clazz)
    {
        if (e != null)
        {
            List extElems = e.getExtensibilityElements();
            if (extElems != null)
            {
                Iterator it = extElems.iterator();
                
                while (it.hasNext())
                {
                    Object o = it.next();
                    if ((clazz == INSTANCEOF_SOAPBINDING && (o instanceof javax.wsdl.extensions.soap.SOAPBinding))
                       || (clazz == INSTANCEOF_SOAPADDRESS && (o instanceof javax.wsdl.extensions.soap.SOAPAddress))
                       || (clazz == INSTANCEOF_SOAPOPERATION && (o instanceof javax.wsdl.extensions.soap.SOAPOperation))
                       || (clazz == INSTANCEOF_SOAPBODY && (o instanceof javax.wsdl.extensions.soap.SOAPBody)))
                        return o;
                }
            }
        }
        
        return null;
    }
    

    /**
     * Generate a type for the specified QName.
     * 
     * @param typename
     * @return
     * @throws WrapperFault
     */
    private Type createTypeInfo(QName typename, TypeMap typeMap)  throws WrapperFault
    {
        TypeEntry type = c_symbolTable.getType(typename);
        if (type == null)
        {
            type = c_symbolTable.getElement(typename);
            if (type == null)
            {
                throw new WrapperFault(
                    "["
                        + typename
                        + "]unexpected condition occurred "
                        + ".. please inform the axis-dev@apache.org mailing list ASAP");
            }
        }
        return createTypeInfo(type, typeMap);
    }
    
    /**
     * Creates a type map entry from a symbol table typeentry. 
     * 
     * @param type
     * @return
     * @throws WrapperFault
     */
    private Type createTypeInfo(TypeEntry type, TypeMap typeMap) throws WrapperFault
    {
        Type typedata = null;
        Type newSecondaryType = null;
        
        // Do not add types which are not used in the WSDL
        if (!type.isReferenced())
            return null;
        
        if (c_verbose && !CUtils.isPrimitiveType(type.getQName()))
            System.out.println("Attempting to create type: " + type.getQName());
        
        if (type instanceof CollectionElement)
        { //an array
        }
        else if (type instanceof DefinedElement)
        { 
            // if element references another type, process the referenced type
            if (type.getRefType() != null)
            {
                if (c_verbose)
                    System.out.println("Attempting to create new type from element-ref: " + type.getRefType().getQName());
                
                return createTypeInfo(type.getRefType(), typeMap);
            }

            return null;
        }
        
        if (-1 != type.getQName().getLocalPart().indexOf('['))
        { 
            /* it seems that this is an array */
            if (null == type.getRefType())
                throw new WrapperFault("Array type found without a Ref type");
            
            QName qn = type.getRefType().getQName();
            if (null == qn)
                throw new WrapperFault("Array type found without a Ref type");
            
            if (CUtils.isPrimitiveType(qn))
                return null;
            
            QName newqn = new QName(type.getQName().getNamespaceURI(), qn.getLocalPart() + "_Array");
            // type is a inbuilt type or a already created type?
            typedata = typeMap.getType(newqn);
            if (typedata != null)
            {
                if (c_verbose && !CUtils.isPrimitiveType(type.getQName()))
                    System.out.println("Type not created, already exists: " + type.getQName());
                
                return typedata;
            }            
            
            typedata = new Type(newqn, newqn.getLocalPart());
            
            if (type.getRefType().getRefType() != null)
                typedata.setElementType(type.getRefType().getRefType().getQName().getLocalPart());
            else
                typedata.setElementType(type.getRefType().getQName().getLocalPart());     
        }
        else
        {
            // type is a inbuilt type or a already created type?
            typedata = typeMap.getType(type.getQName());
            if (typedata != null)
            {
                if (c_verbose && !CUtils.isPrimitiveType(type.getQName()))
                    System.out.println("Type not created, already exists: " + type.getQName());
                
                return typedata;
            }
            
            typedata = new Type(type.getQName(), type.getQName().getLocalPart());
        }
        
        // Add type to type map
        if (c_verbose)
            System.out.println("Created new type: " + typedata.getName());
        
        typeMap.addType(typedata.getName(), typedata);
        
        // TODO revisit...work out whether this type will be generated or not 
        typedata.externalize(isTypeGenerated(type, typedata));

        Node node = type.getNode();

        if (type.isSimpleType())
        {
            //check for extended types
            TypeEntry base = CSchemaUtils.getComplexElementExtensionBase(type.getNode(), c_symbolTable);
            if (base != null)
            {
                String localpart = type.getQName().getLocalPart() + "_value";
                QName typeName =  new QName(type.getQName().getNamespaceURI(), localpart);
                newSecondaryType = createTypeInfo(base.getQName(), typeMap);
                typedata.addRelatedType(newSecondaryType);
                typedata.setExtensionBaseType(new CElementDecl(newSecondaryType, typeName));
                if (c_verbose)
                    System.out.print(
                        "=====complexType with simpleContent is found : "
                            + type.getQName().getLocalPart() + "=====\n");
            }
            else
                setRestrictionBaseAndValues(typedata, node);
            
            // There can be attributes in this extended basic type
            Vector attributes = CSchemaUtils.getContainedAttributeTypes(type.getNode(), c_symbolTable);
            if (attributes != null)
            {
                for (int j = 0; j < attributes.size(); j++)
                {
                    CContainedAttribute attr = (CContainedAttribute)attributes.get(j);
                    newSecondaryType = createTypeInfo(attr.getTypeEntry().getQName(), typeMap);
                    attr.setType(newSecondaryType);
                    typedata.addRelatedType(newSecondaryType);
                }
                typedata.addAttributes(attributes);
            }
        }
        else if (type instanceof CollectionType)
        {
            newSecondaryType = createTypeInfo(type.getRefType().getQName(), typeMap);
            typedata.addRelatedType(newSecondaryType);
            typedata.setTypeNameForElementName(new CElementDecl(newSecondaryType, type.getQName()));
            typedata.setArray(true);
        }
        else
        {
            //is this a SOAPEnc array type    
            QName arrayType = CSchemaUtils.getArrayComponentQName(node,new IntHolder(0),c_symbolTable);
            if (arrayType != null)
            {
                newSecondaryType = createTypeInfo(arrayType, typeMap);
                typedata.addRelatedType(newSecondaryType);
                typedata.setTypeNameForElementName(new CElementDecl(newSecondaryType, new QName("item")));
                typedata.setArray(true);
            }
            else if ((arrayType = CSchemaUtils.getCollectionComponentQName(node)) != null)
            {
                newSecondaryType = createTypeInfo(arrayType, typeMap);
                typedata.addRelatedType(newSecondaryType);
                typedata.setTypeNameForElementName(new CElementDecl(newSecondaryType, new QName("item")));
                typedata.setArray(true);
            }
            //Note in a array the parameter type is stored as under the name item all the time  
            else
            {
                // get all extended types
                Vector extendList = new Vector();
                extendList.add(type);
                
                TypeEntry parent = CSchemaUtils.getComplexElementExtensionBase(type.getNode(), c_symbolTable);
                while (parent != null)
                {
                    extendList.add(parent);
                    parent = CSchemaUtils.getComplexElementExtensionBase(parent.getNode(), c_symbolTable);
                }

                // Now generate a list of names and types starting with
                // the oldest parent.  (Attrs are considered before elements).
                for (int i = extendList.size() - 1; i >= 0; i--)
                {
                    TypeEntry te = (TypeEntry) extendList.elementAt(i);

                    //TODO the code require the attributes name at extension base types
                    //different, the WSDL2Ws do not support it having same name at up and below.

                    // Process the attributes
                    if (c_verbose)
                        System.out.println("Processing attributes for type: " + type.getQName());

                    // TODO Need to handle whether attributes are qualified?
                    Vector attributes = CSchemaUtils.getContainedAttributeTypes(te.getNode(), c_symbolTable);
                    if (attributes != null)
                    {
                        for (int j = 0; j < attributes.size(); j++)
                        {
                            CContainedAttribute attr = (CContainedAttribute)attributes.get(j);
                            newSecondaryType = createTypeInfo(attr.getTypeEntry().getQName(), typeMap);
                            attr.setType(newSecondaryType);
                            typedata.addRelatedType(newSecondaryType);
                        }
                        typedata.addAttributes(attributes);
                    }                        
                    
                    // Process the elements
                    if (c_verbose)
                        System.out.println("Processing elements for type: " + type.getQName());
                    
                    Vector elements =  CSchemaUtils.getContainedElementDeclarations(te.getNode(), c_symbolTable);
                    if (elements != null)
                    {
                        // The following will get elementFormDefault for the schema the element is in.
                        boolean nsQualifyElementDefault = CSchemaUtils.isElementFormDefaultQualified(te.getNode());
                        
                        // Now process the elements.
                        for (int j = 0; j < elements.size(); j++)
                        {   
                            CElementDecl elem = (CElementDecl) elements.get(j);
                            
                            // Set whether to namespace qualify or not. We only process if not set.
                            if (!elem.getNsQualified())
                            {
                                boolean nsQualifyElement = 
                                    CSchemaUtils.shouldWeNamespaceQualifyNode(elem.getTypeEntry().getNode(), 
                                                                              nsQualifyElementDefault);
                                elem.setNsQualified(nsQualifyElement);
                            }
                            
                            if (elem.getAnyElement())
                            {
                                newSecondaryType =  new Type(CUtils.anyTypeQname, CUtils.anyTypeQname.getLocalPart());
                            }
                            else
                            {
                                QName typeName = elem.getTypeEntry().getQName();
                                if (typeName.getLocalPart().indexOf('[') > 0)
                                {
                                    String localpart =
                                        typeName.getLocalPart().substring(0, typeName.getLocalPart().indexOf('['));
                                    
                                    typeName = new QName(typeName.getNamespaceURI(), localpart);
                                    
                                    if (CUtils.isPrimitiveType(typeName))
                                        newSecondaryType = createTypeInfo(typeName, typeMap);
                                    else
                                        newSecondaryType = createTypeInfo(elem.getTypeEntry(), typeMap);
                                }
                                else
                                    newSecondaryType = createTypeInfo(typeName, typeMap);
                            }
                            
                            typedata.addRelatedType(newSecondaryType);
                            elem.setType(newSecondaryType);
                                                       
                            typedata.setTypeNameForElementName(elem);
                        }
                    }
                } // for-loop
            }
        }
        return typedata;
    }    
    
    /**
     * If the specified node represents a supported JAX-RPC restriction,
     * a Vector is returned which contains the base type and the values (enumerations etc).
     * The first element in the vector is the base type (an TypeEntry).
     * Subsequent elements are QNames.
     * NEEDS WORK - CURRENTLY THE ONLY THING WE DO IS GENERATE ENUMERATOR CONSTANTS AND CREATE
     * AN EMPTY RESTRICTOR FUNCTION WHEN DOING CODE GENERATION STEP.
     */
    private void setRestrictionBaseAndValues(Type typedata, Node node) 
    {
        if (node == null)
            return;

        // If the node kind is an element, dive into it.
        QName nodeKind = Utils.getNodeQName(node);
        if (nodeKind != null &&
            nodeKind.getLocalPart().equals("element") &&
            Constants.isSchemaXSD(nodeKind.getNamespaceURI())) 
        {
            NodeList children = node.getChildNodes();
            Node simpleNode = null;
            for (int j = 0; j < children.getLength() && simpleNode == null; j++) 
            {
                QName simpleKind = Utils.getNodeQName(children.item(j));
                if (simpleKind != null &&
                    simpleKind.getLocalPart().equals("simpleType") &&
                    Constants.isSchemaXSD(simpleKind.getNamespaceURI())) 
                {
                    simpleNode = children.item(j);
                    node = simpleNode;
                }
            }
        }
        
        // Get the node kind, expecting a schema simpleType
        nodeKind = Utils.getNodeQName(node);
        if (nodeKind != null &&
            nodeKind.getLocalPart().equals("simpleType") &&
            Constants.isSchemaXSD(nodeKind.getNamespaceURI())) 
        {
            // Under the simpleType there should be a restriction.
            // (There may be other #text nodes, which we will ignore).
            NodeList children = node.getChildNodes();
            Node restrictionNode = null;
            for (int j = 0; j < children.getLength() && restrictionNode == null; j++) 
            {
                QName restrictionKind = Utils.getNodeQName(children.item(j));
                if (restrictionKind != null &&
                    restrictionKind.getLocalPart().equals("restriction") &&
                    Constants.isSchemaXSD(restrictionKind.getNamespaceURI()))
                    restrictionNode = children.item(j);
            }
            
            // If no restriction node, just return
            if (restrictionNode == null)
                return;

            // The restriction node indicates the type being restricted
            // (the base attribute contains this type).
            QName baseType = Utils.getTypeQName(restrictionNode, new BooleanHolder(), false);
            TypeEntry baseEType = c_symbolTable.getType(baseType);
            
            if (baseEType != null) 
            {
                QName  typedataQName     = typedata.getName();
                String typedataLocalpart = typedataQName.getLocalPart();
                String baseTypeLocalpart = baseEType.getQName().getLocalPart();
                
                QName  typedataQNameSanitized     = null;
                String typedataLocalpartSanitized = null;
                String baseTypeLocalpartSanitized = null;
                
                String methodSuffix = null;
                
                String primitiveXSDType          = null;
                String initValueForType          = null;
                String classForPrimitiveType     = null;
                
                if (TypeMap.isAnonymousType(typedataLocalpart))
                {
                    typedataQNameSanitized     = new QName(typedataQName.getNamespaceURI(), CUtils.sanitizeString(typedataLocalpart));
                    typedataLocalpartSanitized =  CUtils.sanitizeString(typedataLocalpart);
                }
                
                if (TypeMap.isAnonymousType(baseTypeLocalpart))
                    baseTypeLocalpartSanitized =  CUtils.sanitizeString(baseTypeLocalpart);
                
                String class4qname          = null;
                String class4qnameSanitized = null;
                
                String javaName = CUtils.getPrimitiveType(baseEType.getQName());
                boolean isBaseTypePrimitive = javaName != null;
                
                QName primitiveBaseTypeQName = null;
                
                if (javaName == null)
                {
                    // No mapping - ensure that the base type is simple - if it is, then this 
                    // must be a user-defined simple type that is based on another user-defined
                    // simple type.
                    if (!baseEType.isSimpleType()
                            && !SchemaUtils.isSimpleSchemaType(baseEType.getQName())) 
                        return;

                    // Get the primitive base type
                    TypeEntry primitiveBaseType = CSchemaUtils.getBaseType(baseEType, c_symbolTable);
                    primitiveBaseTypeQName      = primitiveBaseType.getQName();
                }
                else if (javaName.equals("boolean"))
                    return;
                else
                    primitiveBaseTypeQName = baseEType.getQName();
                
                classForPrimitiveType =  CUtils.getSimpleType(primitiveBaseTypeQName);
                initValueForType      =  CUtils.getInitValue(classForPrimitiveType);
                
                // Set the base type for Type
                typedata.setBaseType(primitiveBaseTypeQName);
                
                // We will map the user-defined type to the user-defined type, so set
                // mapping for the type.
                class4qname          = typedataLocalpart;
                class4qnameSanitized = typedataLocalpartSanitized;
                
                // Update some commonly-used mapping tables to reflect the user-defined
                // simple type. If anonymous type, we need to update mapping tables twice: once
                // with the anonymous names, and once with the sanitized names. 
                
                boolean isPointerType = CUtils.isPointerType(primitiveBaseTypeQName);
                primitiveXSDType = CUtils.getXSDEnumerator(classForPrimitiveType);

                if (!isBaseTypePrimitive)
                {
                    typedata.setRestrictionBaseType(baseTypeLocalpart);
                    if (isPointerType)
                        CUtils.c_pointerBasedTypes.add(baseTypeLocalpart);
                }
                if (isPointerType)
                    CUtils.c_pointerBasedTypes.add(typedataLocalpart);                    

                methodSuffix = (String)CUtils.c_simpleTypeToMethodSuffixMapper.get(classForPrimitiveType);
                CUtils.c_qnameToSimpleTypeMapper.put(typedataQName, class4qname);
                CUtils.c_simpleTypeToQNameMapper.put(class4qname, typedataQName);
                CUtils.c_simpleTypeToEnumMapper.put(typedataLocalpart, primitiveXSDType);

                if (initValueForType != null)
                    CUtils.c_initValueForSimpleType.put(typedataLocalpart, initValueForType);
                CUtils.c_simpleTypeToMethodSuffixMapper.put(typedataLocalpart, methodSuffix);
                
                if (!isBaseTypePrimitive)
                {
                    CUtils.c_simpleTypeToEnumMapper.put(baseTypeLocalpart, primitiveXSDType);
                    if (initValueForType != null)
                        CUtils.c_initValueForSimpleType.put(baseTypeLocalpart, initValueForType);
                    CUtils.c_simpleTypeToMethodSuffixMapper.put(baseTypeLocalpart, methodSuffix);
                }

                if (typedataQNameSanitized != null)
                {
                    if (isPointerType)
                        CUtils.c_pointerBasedTypes.add(typedataLocalpartSanitized); 
                    CUtils.c_qnameToSimpleTypeMapper.put(typedataQNameSanitized, class4qnameSanitized);
                    CUtils.c_simpleTypeToQNameMapper.put(class4qnameSanitized, typedataQNameSanitized);
                    CUtils.c_simpleTypeToEnumMapper.put(typedataLocalpartSanitized, primitiveXSDType);
                    if (initValueForType != null)
                        CUtils.c_initValueForSimpleType.put(typedataLocalpartSanitized, initValueForType);
                    CUtils.c_simpleTypeToMethodSuffixMapper.put(typedataLocalpartSanitized, methodSuffix);
                }
                
                if (baseTypeLocalpartSanitized != null)
                {
                    if (isPointerType)
                        CUtils.c_pointerBasedTypes.add(baseTypeLocalpartSanitized);
                    CUtils.c_simpleTypeToEnumMapper.put(baseTypeLocalpartSanitized, primitiveXSDType);
                    if (initValueForType != null)
                        CUtils.c_initValueForSimpleType.put(baseTypeLocalpartSanitized, initValueForType);
                    CUtils.c_simpleTypeToMethodSuffixMapper.put(baseTypeLocalpartSanitized, methodSuffix);
                }         
                
                // Process the enumeration elements underneath the restriction node
                Vector v = new Vector();                
                NodeList enums = restrictionNode.getChildNodes();
                for (int i=0; i < enums.getLength(); i++) 
                {
                    QName enumKind = Utils.getNodeQName(enums.item(i));
                    if (enumKind != null && Constants.isSchemaXSD(enumKind.getNamespaceURI())) 
                    {
                        Node enumNode = enums.item(i);
                        String value = Utils.getAttribute(enumNode, "value");
    
                        if (value.indexOf(':')>0)                                                        
                                value=value.substring(value.indexOf(':')+1,value.length());
                        v.add(new QName(value, enumKind.getLocalPart()));
                    }
                }
                
                // The first element in the vector is a TypeEntry.
                v.add(0,baseEType);
                typedata.setRestrictiondata(v);
                typedata.setRestriction(true);
                
                // Add schema-defined simple type to mapping table - TODO: not sure we need this anymore.
                CUtils.addSchemaDefinedSimpleType(typedataQName, class4qname);
                if (typedataQNameSanitized != null)
                    CUtils.addSchemaDefinedSimpleType(typedataQNameSanitized, class4qnameSanitized);
            }
        }
        return;
    }      
    
    /**
     * Work out the various conditions that dictate whether this type will be generated into a new
     * file or not.
     * This method is only very partially implemented. 
     *   
     * @param type
     * @param typedata
     * @return true if the type will not be generated. False otherwise
     */
    private boolean isTypeGenerated(TypeEntry type, Type typedata)
    {
        // If the referenced type is actually a type that will not get generated because it's
        //     a base type array then tell other people of this case. Do this to two levels of indirection
        
        if(type.getRefType()!=null)
            if(type.getRefType().getRefType()!=null && type.getRefType().getRefType().isBaseType())
                return false;
            
        if (typedata.isAnonymous())
            return false;
        else
            return true;
    }
}
