/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
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

package org.apache.axis.j2me.rpc.wsdl.tojava;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import javax.wsdl.Binding;
import javax.wsdl.BindingOperation;
import javax.wsdl.Fault;
import javax.wsdl.Message;
import javax.wsdl.Operation;
import javax.wsdl.OperationType;
import javax.wsdl.Part;
import javax.wsdl.Port;
import javax.wsdl.PortType;
import javax.wsdl.Service;
import javax.wsdl.extensions.UnknownExtensibilityElement;
import javax.wsdl.extensions.soap.SOAPOperation;
import javax.xml.namespace.QName;
import javax.xml.rpc.holders.BooleanHolder;

import org.apache.axis.Constants;
import org.apache.axis.enum.Use;
import org.apache.axis.utils.JavaUtils;
import org.apache.axis.utils.WSDLUtils;
import org.apache.axis.wsdl.symbolTable.BaseType;
import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.ElementDecl;
import org.apache.axis.wsdl.symbolTable.FaultInfo;
import org.apache.axis.wsdl.symbolTable.Parameter;
import org.apache.axis.wsdl.symbolTable.Parameters;
import org.apache.axis.wsdl.symbolTable.SchemaUtils;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.toJava.Emitter;
import org.apache.axis.wsdl.toJava.JavaBindingWriter;
import org.apache.axis.wsdl.toJava.JavaClassWriter;
import org.apache.axis.wsdl.toJava.Utils;
import org.w3c.dom.Node;

/**
 * 
 * This class is customized for J2ME from Axis' JavaStubWriter
 * 
 * @author Ias (iasandcb@tmax.co.kr)
 *  
 */
public class J2meStubWriter extends JavaClassWriter {

    /** Field bEntry */
    private BindingEntry bEntry;

    /** Field binding */
    private Binding binding;

    /** Field symbolTable */
    private SymbolTable symbolTable;
    
    private ArrayList faults;
    
    /** A simple map of the primitive types and their holder objects */
    private static HashMap TYPES = new HashMap(7);

    static {
        TYPES.put("int", "java.lang.Integer");
        TYPES.put("float", "java.lang.Float");
        TYPES.put("boolean", "java.lang.Boolean");
        TYPES.put("double", "java.lang.Double");
        TYPES.put("byte", "java.lang.Byte");
        TYPES.put("short", "java.lang.Short");
        TYPES.put("long", "java.lang.Long");
    }

    /**
	 * Constructor.
	 * 
	 * @param emitter
	 * @param bEntry
	 * @param symbolTable
	 */
    protected J2meStubWriter(Emitter emitter, BindingEntry bEntry, SymbolTable symbolTable) {

        super(emitter, bEntry.getName() + "_Stub", "stub");

        this.bEntry = bEntry;
        this.binding = bEntry.getBinding();
        this.symbolTable = symbolTable;
        
        Map faultMap = bEntry.getFaults();
        Iterator it = faultMap.values().iterator();
        faults = new ArrayList();

        while (it.hasNext()) {
        	ArrayList list = (ArrayList) it.next();

        	// Accumulate total list of faults
        	faults.addAll(list);
        }
        
    } // ctor

    /**
	 * Returns "implements <SEI>".
	 * 
	 * @return
	 */
    protected String getImplementsText() {
    	String implementingTarget = "implements javax.xml.rpc.Stub, ";
    	if (!faults.isEmpty()) {
    		implementingTarget += "javax.microedition.xml.rpc.FaultDetailHandler, ";
    	}
        return  implementingTarget + bEntry.getDynamicVar(JavaBindingWriter.INTERFACE_NAME) + " ";
    } // getImplementsText

    /**
	 * Write the body of the binding's stub file.
	 * 
	 * @param pw
	 * @throws IOException
	 */
    protected void writeFileBody(PrintWriter pw) throws IOException {

        PortType portType = binding.getPortType();
        HashSet types = getTypesInPortType(portType);
        ServiceEntry serviceEntry = getFirstServiceEntry();
        Service service = serviceEntry.getService();
        // get ports
        Map portMap = service.getPorts();
        Iterator portIterator = portMap.values().iterator();

        String address = "";
        // write a get method for each of the ports with a SOAP binding
        while (portIterator.hasNext()) {
            Port p = (Port) portIterator.next();
            Binding binding = p.getBinding();
            String portName = p.getName();

            if (binding == null) {
                throw new IOException("no binding for port " + portName);
            }

            BindingEntry bEntry = symbolTable.getBindingEntry(binding.getQName());

            if (bEntry == null) {
                throw new IOException("no binding entry for port " + portName);
            }

            // If this isn't an SOAP binding, skip it
            if (bEntry.getBindingType() != BindingEntry.TYPE_SOAP) {
                continue;
            }

            if (binding.getQName().equals(this.binding.getQName())) {
                address = WSDLUtils.getAddressFromPort(p);
            }

            // Get endpoint address and validate it
        }

        writeStubImplementation(pw);
        if (!faults.isEmpty()) {
        	writeFaultHandler(pw);
        }
        pw.println();
        pw.println("    public " + className + "() {");
        pw.println("         _setProperty(javax.xml.rpc.Stub.ENDPOINT_ADDRESS_PROPERTY, \"" + address + "\");");
        pw.println("    }");
        pw.println();
        List operations = binding.getBindingOperations();

        for (int i = 0; i < operations.size(); ++i) {
            BindingOperation operation = (BindingOperation) operations.get(i);
            Parameters parameters = bEntry.getParameters(operation.getOperation());

            // Get the soapAction from the <soap:operation>
            String soapAction = "";
            String opStyle = null;
            Iterator operationExtensibilityIterator = operation.getExtensibilityElements().iterator();

            for (; operationExtensibilityIterator.hasNext();) {
                Object obj = operationExtensibilityIterator.next();

                if (obj instanceof SOAPOperation) {
                    soapAction = ((SOAPOperation) obj).getSoapActionURI();
                    opStyle = ((SOAPOperation) obj).getStyle();

                    break;
                }
                else if (obj instanceof UnknownExtensibilityElement) {

                    // TODO: After WSDL4J supports soap12, change this code
                    UnknownExtensibilityElement unkElement = (UnknownExtensibilityElement) obj;
                    QName name = unkElement.getElementType();

                    if (name.getNamespaceURI().equals(Constants.URI_WSDL12_SOAP) && name.getLocalPart().equals("operation")) {
                        if (unkElement.getElement().getAttribute("soapAction") != null) {
                            soapAction = unkElement.getElement().getAttribute("soapAction");
                        }

                        opStyle = unkElement.getElement().getAttribute("style");
                    }
                }
            }

            Operation ptOperation = operation.getOperation();
            OperationType type = ptOperation.getStyle();

            // These operation types are not supported. The signature
            // will be a string stating that fact.
            if ((type == OperationType.NOTIFICATION) || (type == OperationType.SOLICIT_RESPONSE)) {
                pw.println(parameters.signature);
                pw.println();
            }
            else {
                writeOperation(pw, operation, parameters, soapAction, opStyle, type == OperationType.ONE_WAY, i);
            }
        }
    } // writeFileBody

    /**
	 * 
	 */
	private void writeStubImplementation(PrintWriter pw) {
		pw.println("        protected boolean maintainSessionSet = false;");
		pw.println("		protected boolean maintainSession = false;");
		pw.println("		protected String cachedUsername = null;");
		pw.println("		protected String cachedPassword = null;");
		pw.println("		protected String cachedEndpoint = null;");
		pw.println("		protected java.util.Hashtable cachedProperties = new java.util.Hashtable();");

		pw.println("		public void _setProperty(String name, Object value) {");
		pw.println("			if (name == null || value == null) {");
		pw.println("				throw new javax.xml.rpc.JAXRPCException(\"Illegal name or value\");");
		pw.println("			} else if (name.equals(USERNAME_PROPERTY)) {");
		pw.println("				if (!(value instanceof String)) {");
		pw.println("					throw new javax.xml.rpc.JAXRPCException(\"Illegal value type: String required\");");
		pw.println("				}");
		pw.println("				cachedUsername = (String) value;");
		pw.println("			} else if (name.equals(PASSWORD_PROPERTY)) {");
		pw.println("				if (!(value instanceof String)) {");
		pw.println("					throw new javax.xml.rpc.JAXRPCException(\"Illegal value type: String required\");");
		pw.println("				}");
		pw.println("				cachedPassword = (String) value;");
		pw.println("			} else if (name.equals(javax.xml.rpc.Stub.ENDPOINT_ADDRESS_PROPERTY)) {");
		pw.println("				if (!(value instanceof String)) {");
		pw.println("					throw new javax.xml.rpc.JAXRPCException(\"Illegal value type: String required\");");
		pw.println("				}");
		pw.println("				cachedEndpoint = (String) value;");
		pw.println("			} else if (name.equals(SESSION_MAINTAIN_PROPERTY)) {");
		pw.println("				if (!(value instanceof Boolean)) {");
		pw.println("					throw new javax.xml.rpc.JAXRPCException(\"Illegal value type: Boolean required\");");
		pw.println("				}");
		pw.println("				maintainSessionSet = true;");
		pw.println("				maintainSession = ((Boolean) value).booleanValue();");
		pw.println("			} else {");
		pw.println("				cachedProperties.put(name, value);");
		pw.println("			}");
		pw.println("		}");

		pw.println("		public Object _getProperty(String name) {");
		pw.println("			if (name != null) {");
		pw.println("				if (name.equals(USERNAME_PROPERTY)) {");
		pw.println("					return cachedUsername;");
		pw.println("				} else if (name.equals(PASSWORD_PROPERTY)) {");
		pw.println("					return cachedPassword;");
		pw.println("				} else if (name.equals(ENDPOINT_ADDRESS_PROPERTY)) {");
		pw.println("					return cachedEndpoint.toString();");
		pw.println("				} else if (name.equals(SESSION_MAINTAIN_PROPERTY)) {");
		pw.println("					return maintainSessionSet ? (maintainSession ? new Boolean(true) : new Boolean(false)) : null;");
		pw.println("				} else if (name.startsWith(\"java.\") || name.startsWith(\"javax.\")) {");
		pw.println("					throw new javax.xml.rpc.JAXRPCException(\"java or javax prefix are prohibited.\");");
		pw.println("				} else {");
		pw.println("					return cachedProperties.get(name);");
		pw.println("				}");
		pw.println("			} else {");
		pw.println("				return null;");
		pw.println("			}");
		pw.println("		}");
	}

	protected void writeFaultHandler(PrintWriter pw) throws IOException {
		String className = getClassName();
		pw.println("  public javax.microedition.xml.rpc.Element handleFault(javax.xml.namespace.QName faultDetailName) {");
		for (int i = 0; i <faults.size(); i++) {
			FaultInfo faultInfo = (FaultInfo) faults.get(i);
			QName faultQName = faultInfo.getQName();
			pw.println("    if (\"" + faultQName.getNamespaceURI() + "\".equals(faultDetailName.getNamespaceURI()) && ");
			pw.println("    \"" + faultQName.getLocalPart() + "\".equals(faultDetailName.getLocalPart())) {");
			String faultElement = faultInfo.getName() + i;
			writeElement(pw, faultQName, faultElement, null);
			pw.println("      return " + faultElement + ";");
			pw.println("    }");
		}
		pw.println("    return null;");
		pw.println("  }");
	}

	/**
	 * This method returns a set of all the TypeEntry in a given PortType. The elements of the returned HashSet are Types.
	 * 
	 * @param portType
	 * @return
	 */
    private HashSet getTypesInPortType(PortType portType) {

        HashSet types = new HashSet();
        HashSet firstPassTypes = new HashSet();

        // Get all the types from all the operations
        List operations = portType.getOperations();

        for (int i = 0; i < operations.size(); ++i) {
            Operation op = (Operation) operations.get(i);

            firstPassTypes.addAll(getTypesInOperation(op));
        }

        // Add all the types nested and derived from the types
        // in the first pass.
        Iterator i = firstPassTypes.iterator();

        while (i.hasNext()) {
            TypeEntry type = (TypeEntry) i.next();

            if (!types.contains(type)) {
                types.add(type);
                types.addAll(type.getNestedTypes(symbolTable, true));
            }
        }

        return types;
    } // getTypesInPortType

    /**
	 * This method returns a set of all the TypeEntry in a given Operation. The elements of the returned HashSet are TypeEntry.
	 * 
	 * @param operation
	 * @return
	 */
    private HashSet getTypesInOperation(Operation operation) {

        HashSet types = new HashSet();
        Vector v = new Vector();
        Parameters params = bEntry.getParameters(operation);

        // Loop over parameter types for this operation
        for (int i = 0; i < params.list.size(); i++) {
            Parameter p = (Parameter) params.list.get(i);

            v.add(p.getType());
        }

        // Add the return type
        if (params.returnParam != null) {
            v.add(params.returnParam.getType());
        }

        // Collect all the types in faults
        Map faults = operation.getFaults();

        if (faults != null) {
            Iterator i = faults.values().iterator();

            while (i.hasNext()) {
                Fault f = (Fault) i.next();

                partTypes(v, f.getMessage().getOrderedParts(null));
            }
        }

        // Put all these types into a set. This operation eliminates all duplicates.
        for (int i = 0; i < v.size(); i++) {
            types.add(v.get(i));
        }

        return types;
    } // getTypesInOperation

    /**
	 * This method returns a vector of TypeEntry for the parts.
	 * 
	 * @param v
	 * @param parts
	 */
    private void partTypes(Vector v, Collection parts) {

        Iterator i = parts.iterator();

        while (i.hasNext()) {
            Part part = (Part) i.next();
            QName qType = part.getTypeName();

            if (qType != null) {
                v.add(symbolTable.getType(qType));
            }
            else {
                qType = part.getElementName();

                if (qType != null) {
                    v.add(symbolTable.getElement(qType));
                }
            }
        } // while
    } // partTypes

    private Vector isSimpleElement(QName qName) {
    	TypeEntry typeEntry = symbolTable.getTypeEntry(qName, true);
    	Node node = typeEntry.getNode();

    	// Check if this element is of the form:
    	// <element name="foo" type="tns:foo_type"/>
    	BooleanHolder forElement = new BooleanHolder();
    	QName type = Utils.getTypeQName(node, forElement, false);

    	if ((type != null) && !forElement.value) {

    		// If in fact we have such a type, go get the node that
    		// corresponds to THAT definition.
    		node = symbolTable.getTypeEntry(type, false).getNode();
    	}

    	Vector vTypes = SchemaUtils.getContainedElementDeclarations(node, symbolTable);
    	return vTypes;
    }
    
    private void writeElement(PrintWriter pw, QName qName, String id, TypeEntry idType) {
        // Get the node which corresponds to the type entry for this
        // element. i.e.:
        // <part name="part" element="foo:bar"/>
        // ...
        // <schema targetNamespace="foo">
        // <element name="bar"...> <--- This one
        TypeEntry typeEntry = symbolTable.getTypeEntry(qName, true);
        String typeId = id + "Type";
        if (typeEntry == null) {
            typeEntry = idType;
        }

        Node node = typeEntry.getNode();

        // Check if this element is of the form:
        // <element name="foo" type="tns:foo_type"/>
        BooleanHolder forElement = new BooleanHolder();
        QName type = Utils.getTypeQName(node, forElement, false);

        if ((type != null) && !forElement.value) {

            // If in fact we have such a type, go get the node that
            // corresponds to THAT definition.
            node = symbolTable.getTypeEntry(type, false).getNode();
        }

        Vector vTypes = SchemaUtils.getContainedElementDeclarations(node, symbolTable);

        if (vTypes == null) {
            String javaType = typeEntry.getName();
            if (J2meUtils.isSimpleType(javaType)) {
                pw.println("        javax.microedition.xml.rpc.Type " + typeId + ";");
                String simpleType = J2meUtils.getSimpleType(javaType);
                pw.println("       " + typeId + " = javax.microedition.xml.rpc.Type." + simpleType + ";");
                pw.println("        javax.microedition.xml.rpc.Element " + id);
                pw.println("          = new javax.microedition.xml.rpc.Element(");
                pw.println("          new javax.xml.namespace.QName(\"" + qName.getNamespaceURI() + "\",");
                pw.println("          \"" + Utils.getLastLocalPart(qName.getLocalPart()) + "\")");
                pw.println("          , " + typeId + ");");
            }
            else {
                String dims = typeEntry.getDimensions();
                if (!dims.equals("")) {
                    QName componentQName = typeEntry.getRefType().getQName();
                    String componentType = javaType.substring(0, javaType.lastIndexOf(dims));
                    writeElement(pw, qName, id, typeEntry.getRefType());
                    pw.println("        " + id);
                    pw.println("          = new javax.microedition.xml.rpc.Element(");
                    pw.println("          new javax.xml.namespace.QName(\"" + qName.getNamespaceURI() + "\",");
                    pw.println("          \"" + Utils.getLastLocalPart(qName.getLocalPart()) + "\")");
                    pw.println("          , " + typeId);
                    pw.println(" , " + J2meUtils.getMinOccurs(node));
                    pw.println(" , " + J2meUtils.getMaxOccurs(node));
                    pw.println(" , " + JavaUtils.isTrueExplicitly(
                            Utils.getAttribute(node, "nillable")));
                    pw.println("          );");
                }
            }
        }
        else {
            int typeSizes = vTypes.size();
            pw.println("        javax.microedition.xml.rpc.ComplexType " + typeId + ";");
            pw.println("       " + typeId + " = new javax.microedition.xml.rpc.ComplexType();");
            pw.println("       " + typeId + ".elements = new javax.microedition.xml.rpc.Element[" + typeSizes + "];");
            for (int j = 0; j < typeSizes; j++) {
                ElementDecl elem = (ElementDecl) vTypes.elementAt(j);
                String componentId = typeId + j;
                writeElement(pw, elem.getName(), componentId, elem.getType());
                pw.println("       " + typeId + ".elements[" + j + "] = " + componentId + ";");
            }
            pw.println("        javax.microedition.xml.rpc.Element " + id);
            pw.println("          = new javax.microedition.xml.rpc.Element(");
            pw.println("          new javax.xml.namespace.QName(\"" + qName.getNamespaceURI() + "\",");
            pw.println("          \"" + Utils.getLastLocalPart(qName.getLocalPart()) + "\")");
            pw.println("          , " + typeId + ");");
        }

    }

    /**
	 * Write the stub code for the given operation.
	 * 
	 * @param pw
	 * @param operation
	 * @param parms
	 * @param soapAction
	 * @param opStyle
	 * @param oneway
	 * @param opIndex
	 */
    private void writeOperation(
        PrintWriter pw,
        BindingOperation operation,
        Parameters parms,
        String soapAction,
        String opStyle,
        boolean oneway,
        int opIndex) {

        writeComment(pw, operation.getDocumentationElement());
        pw.println(parms.signature + " {");
        Message inputMessage = operation.getOperation().getInput().getMessage();
        Map parts = inputMessage.getParts();
        Iterator i = parts.values().iterator();
        Part operationPart = (Part) i.next();
        QName operationQName = operationPart.getElementName();

        QName inputQName = operationQName;
        inputQName = operationQName;
        writeElement(pw, inputQName, "_inputElement", null);

        Message outputMessage = operation.getOperation().getOutput().getMessage();
        parts = outputMessage.getParts();
        i = parts.values().iterator();
        Part responsePart = (Part) i.next();
        QName outputQName = responsePart.getElementName();
        writeElement(pw, outputQName, "_outputElement", null);
        TypeEntry returnType = parms.returnParam.getType();
        pw.println("        javax.microedition.xml.rpc.Operation _operation ");
        pw.println("          = javax.microedition.xml.rpc.Operation.newInstance(");
        pw.println("          new javax.xml.namespace.QName(\"" + operationQName.getNamespaceURI() + "\",");
        pw.println("          \"" + operationQName.getLocalPart() + "\")");
        pw.println("          , _inputElement, _outputElement");
        ArrayList faults = (ArrayList) bEntry.getFaults().get(operation);
        // check for no faults
        if (!faults.isEmpty()) {
            pw.println("        , this");
        }   

        pw.println("        );");
        pw.println("        _operation.setProperty(javax.xml.rpc.Stub.ENDPOINT_ADDRESS_PROPERTY, (String) _getProperty(javax.xml.rpc.Stub.ENDPOINT_ADDRESS_PROPERTY));");
        pw.println("        String username = (String) _getProperty(javax.xml.rpc.Stub.USERNAME_PROPERTY);");
        pw.println("        if (username != null) {");
        pw.println("            _operation.setProperty(javax.xml.rpc.Stub.USERNAME_PROPERTY, username);");
        pw.println("             String password = (String) _getProperty(javax.xml.rpc.Stub.PASSWORD_PROPERTY);");
        pw.println("             if (password != null) {");
        pw.println("                 _operation.setProperty(javax.xml.rpc.Stub.PASSWORD_PROPERTY, password);");
        pw.println("             }");
        pw.println("        }");
        // SoapAction
        if (soapAction != null) {
            pw.println(
                "        _operation.setProperty(javax.microedition.xml.rpc.Operation.SOAPACTION_URI_PROPERTY, \""
                    + soapAction
                    + "\");");
        }

        if ((parms.list.size() == 1) && isSimpleElement(inputQName) == null) {
       		Parameter p = (Parameter) parms.list.get(0);
       		TypeEntry paramType = p.getType();
       		String javifiedName = Utils.xmlNameToJava(p.getName());
       		writeEncoding(pw, javifiedName, "_args", paramType);
        }
        else {
        	pw.println("        Object[] _args = new Object[" + parms.list.size() + "];");
        	for (int j = 0; j < parms.list.size(); j++) {
        		Parameter p = (Parameter) parms.list.get(j);
        		TypeEntry paramType = p.getType();
        		String javifiedName = Utils.xmlNameToJava(p.getName());
        		writeEncoding(pw, javifiedName, "_args" + j, paramType);
        		pw.println("        _args[" + j + "] = _args" + j + ";");
        	}
        	
        }
        pw.println("        Object _res;");
        
        pw.println("        try {");
        pw.println("            _res = _operation.invoke(_args);");
        pw.println("        }");
        pw.println("        catch (javax.xml.rpc.JAXRPCException jre) {");
        pw.println("            Throwable linkedCause = jre.getLinkedCause();");
        pw.println("   			if (linkedCause instanceof java.rmi.RemoteException) {");
        pw.println("   				throw (java.rmi.RemoteException) linkedCause;");
        pw.println("      		}");
        if (!faults.isEmpty()) {
        	pw.println("   			else if (linkedCause instanceof javax.microedition.xml.rpc.FaultDetailException) {");
        	pw.println("   				javax.microedition.xml.rpc.FaultDetailException detailException = (javax.microedition.xml.rpc.FaultDetailException) linkedCause;");
        	pw.println("   				javax.xml.namespace.QName detailQName = detailException.getFaultDetailName();");
        	for (Iterator j = faults.iterator(); j.hasNext(); ) {
        		FaultInfo faultInfo = (FaultInfo) j.next();
        		QName faultQName = faultInfo.getQName();
        		pw.println("    if (\"" + faultQName.getNamespaceURI() + "\".equals(detailQName.getNamespaceURI()) && ");
        		pw.println("    \"" + faultQName.getLocalPart() + "\".equals(detailQName.getLocalPart())) {");
        		Vector params = new Vector();
        		Message faultMessage = faultInfo.getMessage();
        		Part part = (Part) faultMessage.getParts().values().iterator().next();
        		QName faultElementQName = part.getElementName();
        		boolean literal = faultInfo.getUse().equals(Use.LITERAL);
        		
        		try {
					symbolTable.getParametersFromParts(params,
							faultMessage.getOrderedParts(null),
							literal, null, null);
				} catch (IOException e) {
					e.printStackTrace();
				}

        		// Write data members of the exception and getter methods for them
				String faultParamList = "";
				Vector components =isSimpleElement(faultElementQName); 
				if (components == null) {
					Parameter param = (Parameter) params.get(0);
					String variable = Utils.xmlNameToJava(param.getName());
					writeDecoding(pw, variable, "detailException.getFaultDetail()", param.getType());
					faultParamList = variable;
				}
				else {
					String compositeName = "_fault";
					pw.println("        Object[] " +  compositeName + " = (Object[]) detailException.getFaultDetail();");
					for (int k = 0; k < components.size(); k++) {
						ElementDecl elem = (ElementDecl) components.elementAt(k);
						String componentName = compositeName + k;
						String fieldName = Utils.xmlNameToJava(Utils.getLastLocalPart(elem.getName().getLocalPart()));
						writeDecoding(pw, componentName, compositeName + "[" + k + "]", elem.getType());
						faultParamList += componentName;
						if (k < components.size() - 1) {
							faultParamList += ", ";
						}
					}
				}
        		pw.println("    	throw new " + Utils.getFullExceptionName(faultInfo.getMessage(), symbolTable) + "(");
        		pw.println("    	" + faultParamList);
        		pw.println(");");
        		pw.println("    }");
        	}
        	pw.println("      		}");
        }   
        pw.println("      		throw jre;");
        pw.println("        }");
        String returnName = "_returnValue";
        if (isSimpleElement(outputQName) == null) {
        	writeDecoding(pw, returnName, "_res", returnType);
        }
        else {
        	writeDecoding(pw, returnName, "((Object[])_res)[0]", returnType);
        }
        pw.print("        return " + returnName + ";");
        pw.println();
        pw.println("    }");
        pw.println();
    } // writeOperation

    private void writeEncoding(PrintWriter pw, String name, String id, TypeEntry paramType) {
        Node node = paramType.getNode();

        // Check if this element is of the form:
        // <element name="foo" type="tns:foo_type"/>
        BooleanHolder forElement = new BooleanHolder();
        QName type = Utils.getTypeQName(node, forElement, false);

        if ((type != null) && !forElement.value) {

            // If in fact we have such a type, go get the node that
            // corresponds to THAT definition.
            node = symbolTable.getTypeEntry(type, false).getNode();
        }

        Vector vTypes = SchemaUtils.getContainedElementDeclarations(node, symbolTable);

        if (vTypes == null) {
            if (paramType instanceof BaseType || paramType.getRefType() instanceof BaseType) 
            {
                String javifiedName = Utils.wrapPrimitiveType(paramType, name);
                pw.println("   Object " + id + " = " + javifiedName + ";");
            }
            else  {
                String arraySize = name + ".length";
                pw.println("        Object[] " + id + " = new Object["+ arraySize + "];");
                String loopId = id + "Index";
                pw.println("       for (int " + loopId + " = 0; " + loopId + " < " + arraySize + "; " + loopId + "++ ) {");
                String arrayComponentId = id + "Component";
                writeEncoding(pw, name + "[" + loopId + "]", arrayComponentId, paramType.getRefType());
                pw.println("       " + id + "[" + loopId + "] = " + arrayComponentId + ";");
                pw.println("       }");
            }
        }
        else {
            int typeSizes = vTypes.size();
            pw.println("        Object[] " + id + " = new Object[" + typeSizes + "];");
            for (int j = 0; j < typeSizes; j++) {
                ElementDecl elem = (ElementDecl) vTypes.elementAt(j);
                String componentId = id + j;
                String fieldName = Utils.xmlNameToJava(Utils.getLastLocalPart(elem.getName().getLocalPart()));
                String getterName = "get" +Utils.capitalizeFirstChar(fieldName) + "()";
                writeEncoding(pw, name + "." + getterName, componentId, elem.getType());
                pw.println("       " + id + "[" + j + "] = " + componentId + ";");
            }
        }

    }

    private void writeDecoding(PrintWriter pw, String name, String id, TypeEntry paramType) {
        Node node = paramType.getNode();

        // Check if this element is of the form:
        // <element name="foo" type="tns:foo_type"/>
        BooleanHolder forElement = new BooleanHolder();
        QName type = Utils.getTypeQName(node, forElement, false);

        if ((type != null) && !forElement.value) {

            // If in fact we have such a type, go get the node that
            // corresponds to THAT definition.
            node = symbolTable.getTypeEntry(type, false).getNode();
        }

        Vector vTypes = SchemaUtils.getContainedElementDeclarations(node, symbolTable);
        String javaTypeName = paramType.getName();

        if (vTypes == null) {
            if (paramType instanceof BaseType || paramType.getRefType() instanceof BaseType)
            {
                String objType = (String) TYPES.get(javaTypeName);
                if (objType != null) {
                    pw.println("       " + javaTypeName + " " + name + " = ((" + objType + ") " + id + ")." + javaTypeName + "Value();");
                } else {
                    pw.println("       " + javaTypeName + " " + name + " = (" + javaTypeName + ") " + id + ";");
                }
            }
            else  {
                String arrayId = name + "Array";
                pw.println("        Object[] " + arrayId + " = (Object[]) " + id + ";");
                pw.println("       " + javaTypeName + " " + name + " = new " + paramType.getRefType().getName() + "[" + arrayId + ".length];");
                String loopId = name + "Index";
                pw.println("       for (int " + loopId + " = 0; " + loopId + " < " + name + ".length ; " + loopId + "++ ) {");
                String arrayName = name + "Component";
                writeDecoding(pw, arrayName, arrayId + "[" + loopId + "]", paramType.getRefType());
                pw.println("       " + name + "[" + loopId + "] = " + arrayName + ";");
                pw.println("       }");
            }
        }
        else {
            int typeSizes = vTypes.size();
            pw.println("        " + javaTypeName + " " + name + " = new " + javaTypeName + "();");
            String compositeName = name + "Composite";
            pw.println("        Object[] " +  compositeName + " = (Object[]) " + id + ";");
            for (int j = 0; j < typeSizes; j++) {
                ElementDecl elem = (ElementDecl) vTypes.elementAt(j);
                String componentName = compositeName + j;
                String fieldName = Utils.xmlNameToJava(Utils.getLastLocalPart(elem.getName().getLocalPart()));
                String setterName = "set" +Utils.capitalizeFirstChar(fieldName);
                writeDecoding(pw, componentName, compositeName + "[" + j + "]", elem.getType());
                pw.println("       " + name + "." + setterName + "(" + componentName + ");");
            }
        }

    }

    public ServiceEntry getFirstServiceEntry() {
        java.util.Set entryKeys = symbolTable.getHashMap().keySet();
        if (entryKeys == null) {
            return null;
        }
        else {
            for (Iterator iter = entryKeys.iterator(); iter.hasNext();) {
                Vector vec = (Vector) symbolTable.getHashMap().get(iter.next());
                for (int i = 0; i < vec.size(); i++) {
                    Object candidate = vec.get(i);
                    if (candidate instanceof ServiceEntry) {
                        ServiceEntry entry = (ServiceEntry) candidate;
                        return entry;
                    }
                } // loop in vecor
            } // loop in hashMap
            return null;
        }
    }
}
