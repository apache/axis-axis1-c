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
package org.apache.axis.wsdl;

import com.ibm.wsdl.extensions.soap.SOAPAddress;
import com.ibm.wsdl.extensions.soap.SOAPBody;
import com.ibm.wsdl.extensions.soap.SOAPOperation;
import com.ibm.wsdl.xml.WSDLReader;
import org.apache.axis.utils.XMLUtils;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

import javax.wsdl.Binding;
import javax.wsdl.BindingOperation;
import javax.wsdl.Definition;
import javax.wsdl.Fault;
import javax.wsdl.Import;
import javax.wsdl.Input;
import javax.wsdl.Message;
import javax.wsdl.Operation;
import javax.wsdl.Output;
import javax.wsdl.Part;
import javax.wsdl.Port;
import javax.wsdl.PortType;
import javax.wsdl.QName;
import javax.wsdl.Service;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;
import java.util.Vector;

/**
 * This class produces java files for stubs, skeletons, and types from a
 * WSDL document.
 *
 * @author Russell Butek (butek@us.ibm.com)
 * @author Tom Jordahl (tjordahl@macromedia.com)
 * @author Steve Graham (sggraham@us.ibm.com)
 */
public class Emitter {

    // Scope constants
    public static final byte NO_EXPLICIT_SCOPE = 0x00;
    public static final byte APPLICATION_SCOPE = 0x01;
    public static final byte REQUEST_SCOPE     = 0x10;
    public static final byte SESSION_SCOPE     = 0x11;

    private boolean firstSer = true ;

    private Document doc = null;
    private Definition def = null;
    private WsdlAttributes wsdlAttr = null;
    private boolean bEmitSkeleton = false;
    private boolean bMessageContext = false;
    private boolean bEmitTestCase = false;
    private boolean bVerbose = false;
    private boolean bGenerateImports = true;
    private String outputDir = null;
    private byte scope = NO_EXPLICIT_SCOPE;
    private ArrayList classList = new ArrayList();
    private ArrayList fileList = new ArrayList();
    private Namespaces namespaces = null;
    private HashMap delaySetMap = null;
    private TypeFactory emitFactory = null;

    private HashMap portTypesInfo = null;

    /**
     * Default constructor.
     */
    public Emitter() {
        portTypesInfo = new HashMap();
    } // ctor

    /**
     * Construct an Emitter that initially looks like the given Emitter.
     */
    public Emitter(Emitter that) {
        this.bEmitSkeleton        = that.bEmitSkeleton;
        this.bMessageContext      = that.bMessageContext;
        this.bEmitTestCase        = that.bEmitTestCase;
        this.bVerbose             = that.bVerbose;
        this.bGenerateImports     = that.bGenerateImports;
        this.outputDir            = that.outputDir;
        this.scope                = that.scope;
        this.namespaces           = that.namespaces;
        this.emitFactory          = that.emitFactory;
        this.portTypesInfo        = that.portTypesInfo;
    } // ctor

    /**
     * Call this method if you have a uri for the WSDL document
     */
    public void emit(String uri) throws IOException {
        if (bVerbose)
            System.out.println("Parsing XML File: " + uri);

        try {
            emit(XMLUtils.newDocument(uri));
        }
        catch (Throwable t) {
            t.printStackTrace();
            System.out.println("Error in parsing: " + t.getMessage());
        }
    } // emit

    /**
     * Call this method if your WSDL document has already been parsed as an XML DOM document.
     */
    public void emit(Document doc) throws IOException {
        try {
            WSDLReader reader = new WSDLReader();
            reader.setVerbose(bVerbose);
            def = reader.readWSDL(null, doc);
            namespaces = new Namespaces(outputDir);
            if (delaySetMap != null) {
                namespaces.putAll(delaySetMap);
            }
            emitFactory = new TypeFactory(namespaces);
            emit(def, doc);

            // Output deploy.xml and undeploy.xml outside of the recursive emit method.
            if (bEmitSkeleton) {
                writeDeploymentXML(def.getTargetNamespace());
            }
        }
        catch (Throwable t) {
            t.printStackTrace();
            System.out.println("Error in parsing: " + t.getMessage());
        }
    } // emit

    private void emit(Definition def, Document doc) throws IOException {
        this.def = def;
        this.doc = doc;

        // Generate types from doc
        if (doc != null) {
            emitFactory.buildTypes(doc);
            if (bVerbose) {
                System.out.println("Types:");
                emitFactory.dump();
            }
            // Output Java classes for types
            writeTypes();
        }


        if (def != null) {
            // Generated all the imported XML
            if (bGenerateImports) {

                // Generate the imported WSDL documents
                Map imports = def.getImports();
                Object[] importKeys = imports.keySet().toArray();
                for (int i = 0; i < importKeys.length; ++i) {
                    Vector v = (Vector) imports.get(importKeys[i]);
                    for (int j = 0; j < v.size(); ++j) {
                        Import imp = (Import) v.get(j);
                        Emitter emitter = new Emitter(this);
                        emitter.emit(imp.getDefinition(),
                                     XMLUtils.newDocument(imp.getLocationURI()));
                    }
                }
            }

            // Collect information about ports and operations
            wsdlAttr = new WsdlAttributes(def, new HashMap());

            // PortTypes and Services can share the same name.  If they do in this Definition,
            // force their names to be suffixed with _PortType and _Service, respectively.
            resolvePortTypeServiceNameClashes();

            // Output interfaces for portTypes - fill in the portTypesInfo HashMap
            writePortTypes(portTypesInfo);

            // Output Stub classes for bindings
            writeBindings(portTypesInfo);

            // Output factory classes for services
            writeServices();
        }
    } // emit

    ///////////////////////////////////////////////////
    //
    // Command line switches
    //

    /**
     * Turn on/off server skeleton creation
     * @param boolean value
     */
    public void generateSkeleton(boolean value) {
        this.bEmitSkeleton = value;
    }

    /**
     * Turn on/off test case creation
     * @param boolean value
     */
    public void generateTestCase(boolean value) {
        this.bEmitTestCase = value;
    }

    /**
     * Turn on/off server Message Context parm creation in skel
     * @param boolean value
     */
    public void generateMessageContext(boolean value) {
        this.bMessageContext = value;
    }

    /**
     * Turn on/off generation of elements from imported files.
     * @param boolean generateImports
     */
    public void generateImports(boolean generateImports) {
        this.bGenerateImports = generateImports;
    } // generateImports

    /**
     * Turn on/off verbose messages
     * @param boolean value
     */
    public void verbose(boolean value) {
        this.bVerbose = value;
    }

    public void setNamespaceMap(HashMap map) {
        delaySetMap = map;
    }


    /**
     * Set the output directory to use in emitted source files
     */
    public void setOutputDir(String outputDir) {
        this.outputDir = outputDir;
    }

    /**
     * Set the scope for the deploy.xml file.
     * @param scope One of Emitter.NO_EXPLICIT_SCOPE, Emitter.APPLICATION_SCOPE, Emitter.REQUEST_SCOPE, Emitter.SESSION_SCOPE.  Anything else is equivalent to NO_EXPLICIT_SCOPE and no explicit scope tag will appear in deploy.xml.
     */
    public void setScope(byte scope) {
        this.scope = scope;
    } // setScope

    ///////////////////////////////////////////////////
    //
    // Implementation
    //

    /**
     * This method returns a list of all generated class names.
     */
    public List getGeneratedClassNames() {
        return this.classList;
    }

    /**
     * This method returns a list of all generated file names.
     */
    public List getGeneratedFileNames() {
        return this.fileList;
    }

    /**
     * This method returns a set of all the Types in a given PortType.
     * The elements of the returned HashSet are Types.
     */
    private HashSet getTypesInPortType(PortType portType) {
        HashSet types = new HashSet();
        HashSet firstPassTypes = new HashSet();

        // Get all the types from all the operations
        List operations = portType.getOperations();

        for (int i = 0; i < operations.size(); ++i) {
            firstPassTypes.addAll(getTypesInOperation((Operation) operations.get(i)));
        }

        // Extract those types which are complex types.
        Iterator i = firstPassTypes.iterator();
        while (i.hasNext()) {
            Type type = (Type) i.next();
            if (!types.contains(type)) {
                types.add(type);
                if (type.isDefined() && type.getBaseType() == null) {
                    types.addAll(getNestedTypes(type.getNode()));
                }
            }
        }
        return types;
    } // getTypesInPortType

    /**
     * This method returns a set of all the Types in a given Operation.
     * The elements of the returned HashSet are Types.
     */
    private HashSet getTypesInOperation(Operation operation) {
        HashSet types = new HashSet();
        Vector v = new Vector();

        // Collect all the input types
        Input input = operation.getInput();

        if (input != null) {
            partTypes(v,
                    input.getMessage().getOrderedParts(null),
                    (wsdlAttr.getInputBodyType(operation) == WsdlAttributes.USE_LITERAL));
        }

        // Collect all the output types
        Output output = operation.getOutput();

        if (output != null) {
            partTypes(v,
                    output.getMessage().getOrderedParts(null),
                    (wsdlAttr.getOutputBodyType(operation) == WsdlAttributes.USE_LITERAL));
        }

        // Collect all the types in faults
        Map faults = operation.getFaults();

        if (faults != null) {
            Iterator i = faults.values().iterator();

            while (i.hasNext()) {
                Fault f = (Fault) i.next();
                partTypes(v,
                        f.getMessage().getOrderedParts(null),
                        (wsdlAttr.getFaultBodyType(operation, f.getName()) == WsdlAttributes.USE_LITERAL));
            }
        }

        // Put all these types into a set.  This operation eliminates all duplicates.
        for (int i = 0; i < v.size(); i++)
            types.add(v.get(i));
        return types;
    } // getTypesInOperation

    /**
     * This method returns a set of all the nested Types.
     * The elements of the returned HashSet are Types.
     */
    private HashSet getNestedTypes(Node type) {
        HashSet types = new HashSet();
        if (type == null) {
            return types;
        }

        Vector v = emitFactory.getComplexElementTypesAndNames(type);
        if (v != null) {
            for (int i = 0; i < v.size(); i+=2) {
                if (!types.contains(v.get(i))) {
                    types.add(v.get(i));
                    types.addAll(getNestedTypes(((Type) v.get(i)).getNode()));
                }
            }
        }
        return types;
    } // getNestedTypes

    /**
     * PortTypes and Services can share the same name.  If they do in this Definition,
     * force their names to be suffixed with _PortType and _Service, respectively.  These names
     * are placed back in the QName of the PortType and Service objects themselves.
     */
    private void resolvePortTypeServiceNameClashes() {
        Map portTypes = def.getPortTypes();
        Map services  = def.getServices();
        Iterator pti = portTypes.keySet().iterator();
        while (pti.hasNext()) {
            QName ptName = (QName) pti.next();
            Iterator si = services.keySet().iterator();
            while (si.hasNext()) {
                QName sName = (QName) si.next();
                if (ptName.equals(sName)) {
                    ptName.setLocalPart(ptName.getLocalPart() + "_Port");
                    sName.setLocalPart(sName.getLocalPart() + "_Service");
                }
            }
        }
    } // resolvePortTypeServiceNameClashes

    /**
     * Generate the bindings for all port types, and fill in the portTypesInfo HashMap.
     */
    private void writePortTypes(HashMap portTypesInfo) throws IOException {
        Map portTypes = def.getPortTypes();
        Iterator i = portTypes.values().iterator();

        while (i.hasNext()) {
            PortType portType = (PortType) i.next();

            HashMap portTypeInfo = writePortType(portType);
            if (bEmitSkeleton && bMessageContext) {
                writeAxisPortType(portType);
            }

            portTypesInfo.put(portType, portTypeInfo);
        }
    } // writePortTypes

    /**
     * Generate the interface for the given port type.
     */
    private HashMap writePortType(PortType portType) throws IOException {
        QName portTypeQName = portType.getQName();
        PrintWriter interfacePW = printWriter(portTypeQName, null, "java", "Generating portType interface:  ");
        String nameValue = xmlNameToJava(portTypeQName.getLocalPart());

        writeFileHeader(nameValue + ".java", namespaces.getCreate(portTypeQName.getNamespaceURI()), interfacePW);
        interfacePW.println("public interface " + nameValue + " extends java.rmi.Remote {");

        HashMap portTypeInfo = new HashMap();
        // Remove Duplicates - happens with only a few WSDL's. No idea why!!! 
        // (like http://www.xmethods.net/tmodels/InteropTest.wsdl) 
        // TODO: Remove this patch...
        Iterator operations = (new HashSet(portType.getOperations())).iterator();
        while(operations.hasNext()) {
            Operation operation = (Operation) operations.next();
            Parameters operationInfo = writeOperation(operation, portType.getQName().getNamespaceURI(), interfacePW);

            portTypeInfo.put(operation, operationInfo);
        }

        interfacePW.println("}");
        interfacePW.close();

        return portTypeInfo;
    } // writePortType

    /**
     * Generate the server-side (Axis) interface for the given port type.
     */
    private void writeAxisPortType(PortType portType) throws IOException {
        QName portTypeQName = portType.getQName();
        PrintWriter interfacePW = printWriter(portTypeQName, "Axis", "java", "Generating server-side PortType interface:  ");
        String nameValue = xmlNameToJava(portTypeQName.getLocalPart()) + "Axis";

        writeFileHeader(nameValue + ".java", namespaces.getCreate(portTypeQName.getNamespaceURI()), interfacePW);
        interfacePW.println("public interface " + nameValue + " extends java.rmi.Remote {");

        List operations = portType.getOperations();

        for (int i = 0; i < operations.size(); ++i) {
            Operation operation = (Operation) operations.get(i);
            Parameters operationInfo = writeOperationAxisSkelSignatures(operation, portType.getQName().getNamespaceURI(), interfacePW);
        }

        interfacePW.println("}");
        interfacePW.close();

        return;
    } // writeAxisPortType

    /**
     * This class simply collects
     */
    protected static class Parameter {

        // constant values for the parameter mode.
        public static final byte IN = 1;
        public static final byte OUT = 2;
        public static final byte INOUT = 3;

        public String name;
        public String type;
        public byte mode = IN;

        public String toString() {
            return "(" + type + ", " + name + ", "
                    + (mode == IN ? "IN)" : mode == INOUT ? "INOUT)" : "OUT)");
        } // toString
    } // class Parameter


    /**
     * This class simply collects all the parameter or message data for an operation into one place.
     */
    protected static class Parameters {

        // This vector contains instances of the Parameter class
        public Vector list = new Vector();

        // The type of the first output part, used as the method's return value
        public String returnType = null;

        // The name of the return type (from the part name of the output message.
        // Used to create the RPCParam for the return value.
        public String returnName = null;

        // A comma-separated list of all of the faults
        public String faultString = null;

        // The signature that the interface and the stub will use
        public String signature = null;

        // The signature that the skeleton will use
        public String skelSignature = null;

        // The signature that the skeleton impl
        public String axisSignature = null;

        // The numbers of the respective parameters
        public int inputs = 0;
        public int inouts = 0;
        public int outputs = 0;

        public String toString() {
            return "\nreturnType = " + returnType
                    + "\nreturnTypeName = " + returnName
                    + "\nfaultString = " + faultString
                    + "\nsignature = " + signature
                    + "\nskelSignature = " + skelSignature
                    + "\naxisSignature = " + axisSignature
                    + "\n(inputs, inouts, outputs) = (" + inputs + ", " + inouts + ", " + outputs + ")"
                    + "\nlist = " + list;
        } // toString
    } // class Parameters

    /**
     * For the given operation, this method returns the parameter info conveniently collated.
     * There is a bit of processing that is needed to write the interface, stub, and skeleton.
     * Rather than do that processing 3 times, it is done once, here, and stored in the
     * Parameters object.
     */
    protected Parameters parameters(Operation operation, String namespace) throws IOException {
        Parameters parameters = new Parameters();

        // The input and output Vectors, when filled in, will be of the form:
        // {<parmType0>, <parmName0>, <parmType1>, <parmName1>, ..., <parmTypeN>, <parmNameN>}
        Vector inputs = new Vector();
        Vector outputs = new Vector();

        List parameterOrder = operation.getParameterOrdering();

        // Handle parameterOrder="", which is techinically illegal
        if (parameterOrder != null && parameterOrder.isEmpty()) {
            parameterOrder = null;
        }

        // All input parts MUST be in the parameterOrder list.  It is an error otherwise.
        if (parameterOrder != null) {
            Input input = operation.getInput();
            if (input != null) {
                Message inputMsg = input.getMessage();
                Map allInputs = inputMsg.getParts();
                Collection orderedInputs = inputMsg.getOrderedParts(parameterOrder);
                if (allInputs.size() != orderedInputs.size()) {
                    throw new IOException("Emitter failure.  All input parts must be listed in the parameterOrder attribute of " + operation.getName());
                }
            }
        }

        // Collect all the input parameters
        Input input = operation.getInput();
        if (input != null) {
            partStrings(inputs,
                    input.getMessage().getOrderedParts(null),
                    (wsdlAttr.getInputBodyType(operation) == WsdlAttributes.USE_LITERAL));
        }

        // Collect all the output parameters
        Output output = operation.getOutput();
        if (output != null) {
            partStrings(outputs,
                    output.getMessage().getOrderedParts(null),
                    (wsdlAttr.getOutputBodyType(operation) == WsdlAttributes.USE_LITERAL));
        }

        if (parameterOrder != null) {
            // Construct a list of the parameters in the parameterOrder list, determining the
            // mode of each parameter and preserving the parameterOrder list.
            for (int i = 0; i < parameterOrder.size(); ++i) {
                String name = (String) parameterOrder.get(i);

                // index in the inputs Vector of the given name, -1 if it doesn't exist.
                int index = getPartIndex(name, inputs);

                // index in the outputs Vector of the given name, -1 if it doesn't exist.
                int outdex = getPartIndex(name, outputs);

                if (index > 0) {
                    // The mode of this parameter is either in or inout
                    addInishParm(inputs, outputs, index, outdex, parameters, true);
                }
                else if (outdex > 0) {
                    addOutParm(outputs, outdex, parameters, true);
                }
                else {
                    System.err.println("!!! " + name + " not found as an input OR an output part!");
                }
            }
        }

        // Get the mode info about those parts that aren't in the parameterOrder list.
        // Since they're not in the parameterOrder list, the order doesn't matter.
        // Add the input and inout parts first, then add the output parts.
        for (int i = 1; i < inputs.size(); i += 2) {
            int outdex = getPartIndex((String) inputs.get(i), outputs);
            addInishParm(inputs, outputs, i, outdex, parameters, false);
        }

        // Now that the remaining in and inout parameters are collected, the first entry in the
        // outputs Vector is the return value.  The rest are out parameters.
        if (outputs.size() > 0) {
            parameters.returnType = (String) outputs.get(0);
            parameters.returnName = (String) outputs.get(1);
            ++parameters.outputs;
            for (int i = 3; i < outputs.size(); i += 2) {
                addOutParm(outputs, i, parameters, false);
            }
        }

        // Collect the list of faults into a single string, separated by commas.
        Map faults = operation.getFaults();
        Iterator i = faults.values().iterator();
        while (i.hasNext()) {
            if (parameters.faultString == null)
                parameters.faultString = fault((Fault) i.next(), namespace);
            else
                parameters.faultString = parameters.faultString + ", " + fault((Fault) i.next(), namespace);
        }

        if (parameters.returnType == null)
            parameters.returnType = "void";
        constructSignatures(parameters, operation.getName());
        return parameters;
    } // parameters

    /**
     * Return the index of the given name in the given Vector, -1 if it doesn't exist.
     */
    private int getPartIndex(String name, Vector v) {
        for (int i = 1; i < v.size(); i += 2) {
            if (name.equals(v.get(i))) {
                return i;
            }
        }
        return -1;
    } // getPartIndex

    /**
     * Add an in or inout parameter to the parameters object.
     */
    private void addInishParm(Vector inputs, Vector outputs, int index, int outdex, Parameters parameters, boolean trimInput) {
        Parameter p = new Parameter();
        p.name = (String) inputs.get(index);
        p.type = (String) inputs.get(index - 1);

        // Should we remove the given parameter type/name entries from the Vector?
        if (trimInput) {
            inputs.remove(index);
            inputs.remove(index - 1);
        }

        // At this point we know the name and type of the parameter, and that it's at least an
        // in parameter.  Now check to see whether it's also in the outputs Vector.  If it is,
        // then it's an inout parameter.
        if (outdex > 0 && p.type.equals(outputs.get(outdex - 1))) {
            outputs.remove(outdex);
            outputs.remove(outdex - 1);
            p.mode = Parameter.INOUT;
            ++parameters.inouts;
        }
        else {
            ++parameters.inputs;
        }
        parameters.list.add(p);
    } // addInishParm

    /**
     * Add an output parameter to the parameters object.
     */
    private void addOutParm(Vector outputs, int outdex, Parameters parameters, boolean trim) {
        Parameter p = new Parameter();
        p.name = (String) outputs.get(outdex);
        p.type = (String) outputs.get(outdex - 1);
        if (trim) {
            outputs.remove(outdex);
            outputs.remove(outdex - 1);
        }
        p.mode = Parameter.OUT;
        ++parameters.outputs;
        parameters.list.add(p);
    } // addOutParm

    /**
     * Construct the signatures.  signature is used by both the interface and the stub.
     * skelSig is used by the skeleton.
     */
    private void constructSignatures(Parameters parms, String name) {
        int allOuts = parms.outputs + parms.inouts;
        String signature = "    public " + parms.returnType + " " + name + "(";
        String axisSig = "    public " + parms.returnType + " " + name + "(";
        String skelSig = null;

        if (allOuts == 0)
            skelSig = "    public void " + name + "(";
        else
            skelSig = "    public Object " + name + "(";

        if (bMessageContext) {
            skelSig = skelSig + "org.apache.axis.MessageContext ctx";
            axisSig = axisSig + "org.apache.axis.MessageContext ctx";
            if ((parms.inputs + parms.inouts) > 0) {
                skelSig = skelSig + ", ";
            }
            if (parms.list.size() > 0) {
                axisSig = axisSig + ", ";
            }
        }
        boolean needComma = false;

        for (int i = 0; i < parms.list.size(); ++i) {
            Parameter p = (Parameter) parms.list.get(i);

            if (needComma) {
                signature = signature + ", ";
                axisSig = axisSig + ", ";
                if (p.mode != Parameter.OUT)
                    skelSig = skelSig + ", ";
            }
            else
                needComma = true;
            if (p.mode == Parameter.IN) {
                signature = signature + p.type + " " + p.name;
                axisSig = axisSig + p.type + " " + p.name;
                skelSig = skelSig + p.type + " " + p.name;
            }
            else if (p.mode == Parameter.INOUT) {
                signature = signature + holder(p.type) + " " + p.name;
                axisSig = axisSig + holder(p.type) + " " + p.name;
                skelSig = skelSig + p.type + " " + p.name;
            }
            else// (p.mode == Parameter.OUT)
            {
                signature = signature + holder(p.type) + " " + p.name;
                axisSig = axisSig + holder(p.type) + " " + p.name;
            }
        }
        signature = signature + ") throws java.rmi.RemoteException";
        axisSig = axisSig + ") throws java.rmi.RemoteException";
        skelSig = skelSig + ") throws java.rmi.RemoteException";
        if (parms.faultString != null) {
            signature = signature + ", " + parms.faultString;
            axisSig = axisSig + ", " + parms.faultString;
            skelSig = skelSig + ", " + parms.faultString;
        }
        parms.signature = signature;
        parms.axisSignature = axisSig;
        parms.skelSignature = skelSig;
    } // constructSignatures

    /**
     * This method returns a vector containing the Java types (even indices) and
     * names (odd indices) of the parts.
     */
    private void partStrings(Vector v, Collection parts, boolean literal) {
        Iterator i = parts.iterator();

        while (i.hasNext()) {
            Part part = (Part) i.next();

            if (literal) {
                QName elementName = part.getElementName();
                if (elementName != null) {
                    v.add(Utils.capitalize(elementName.getLocalPart()));
                    v.add(part.getName());
                }
            } else {
                QName typeName = part.getTypeName();
                if (typeName != null) {
                    // Handle the special "java" namespace for types
                    if (typeName.getNamespaceURI().equalsIgnoreCase("java")) {
                        v.add(typeName.getLocalPart());
                    } else {
                        v.add(emitFactory.getType(typeName).getJavaName());
                    }
                    v.add(part.getName());
                }
            }
        }
    } // partStrings

    /**
     * This method returns a vector of Types for the parts.
     */
    private void partTypes(Vector v, Collection parts, boolean literal) {
        Iterator i = parts.iterator();

        while (i.hasNext()) {
            Part part = (Part) i.next();

            QName qType;
            if (literal) {
                qType = part.getElementName();
            } else {
                qType = part.getTypeName();
            }
            if (qType != null) {
                v.add(emitFactory.getType(qType));
            }
        }
    } // partTypes

    /**
     * This method generates the interface signatures for the given operation.
     */
    private Parameters writeOperation(Operation operation, String namespace, PrintWriter interfacePW) throws IOException {
        String name = operation.getName();
        Parameters parms = parameters(operation, namespace);

        writeComment(interfacePW, operation.getDocumentationElement());
        interfacePW.println(parms.signature + ";");

        return parms;
    } // writeOperation

    /**
     * This method generates the axis server side impl interface signatures operation.
     */
    private Parameters writeOperationAxisSkelSignatures(Operation operation, String namespace, PrintWriter interfacePW) throws IOException {
        String name = operation.getName();
        Parameters parms = parameters(operation, namespace);

        interfacePW.println(parms.axisSignature + ";");

        return parms;
    } // writeOperation

    /**
     * This generates an exception class for the given fault and returns the capitalized name of
     * the fault.
     */
    private String fault(Fault operation, String namespace) throws IOException {
        String exceptionName = Utils.capitalize(xmlNameToJava(operation.getName()));
        QName qname = new QName(namespace, exceptionName);
        PrintWriter pw = printWriter(qname, null, "java", "Generating Fault class:  ");

        writeFileHeader(exceptionName + ".java", namespaces.getCreate(namespace), pw);
        pw.println("public class " + exceptionName + " extends Exception {");

        Vector params = new Vector();

        partStrings(params, operation.getMessage().getOrderedParts(null), false);

        for (int i = 0; i < params.size(); i += 2)
            pw.println("    public " + params.get(i) + " " + params.get(i + 1) + ";");

        pw.println();
        pw.println("    public " + exceptionName + "() {");
        pw.println("    }");
        pw.println();
        if (params.size() > 0) {
            pw.print("      public " + exceptionName + "(");
            for (int i = 0; i < params.size(); i += 2) {
                if (i != 0) pw.print(", ");
                pw.print(params.get(i) + " " + params.get(i + 1));
            }
            pw.println(") {");
            for (int i = 1; i < params.size(); i += 2) {
                String variable = (String) params.get(i);

                pw.println("        this." + variable + " = " + variable + ";");
            }
            pw.println("    }");
        }
        pw.println("}");
        pw.close();
        return exceptionName;
    } // fault

    /**
     * Generate the stubs and skeletons for all binding tags.
     */
    private void writeBindings(HashMap portTypesInfo) throws IOException {
        Map bindings = def.getBindings();
        Iterator i = bindings.values().iterator();

        while (i.hasNext()) {
            Binding binding = (Binding) i.next();

            // If this isn't a SOAP binding, skip it
            if (wsdlAttr.getBindingType(binding) != WsdlAttributes.TYPE_SOAP) {
                continue;
            }

            HashMap portTypeInfo = (HashMap) portTypesInfo.get(binding.getPortType());

            writeBinding(binding, portTypeInfo);
        }
    } // writeBindings

    /**
     * Generate a stub and a skeleton for the given binding tag.
     */
    private void writeBinding(Binding binding, HashMap portTypeInfo) throws IOException {
        QName bindingQName = binding.getQName();
        if (portTypeInfo == null)
            throw new IOException("Emitter failure.  Can't find interal classes for portType for binding " + bindingQName);

        PortType portType = binding.getPortType();
        String name = xmlNameToJava(bindingQName.getLocalPart());
        String portTypeName = emitFactory.getJavaName(portType.getQName());
        boolean isRPC = true;
        if (wsdlAttr.getBindingStyle(binding) == WsdlAttributes.STYLE_DOCUMENT) {
            isRPC = false;
        }

        String stubName = name + "Stub";
        PrintWriter stubPW = printWriter(bindingQName, "Stub", "java", "Generating client-side stub:  ");

        writeFileHeader(stubName + ".java", namespaces.getCreate(bindingQName.getNamespaceURI()), stubPW);
        stubPW.println("public class " + stubName + " extends javax.xml.rpc.Stub implements " + portTypeName + " {");
        stubPW.println("    private org.apache.axis.client.Service service = null ;");
        stubPW.println("    private org.apache.axis.client.Call call = null ;");
        stubPW.println("    private java.util.Hashtable properties = new java.util.Hashtable();");
        stubPW.println();
        stubPW.println("    public " + stubName + "(java.net.URL endpointURL) throws org.apache.axis.AxisFault {");
        stubPW.println("         this();");
        stubPW.println("         call.setTargetEndpointAddress( endpointURL );");
        stubPW.println("         call.setProperty(org.apache.axis.transport.http.HTTPTransport.URL, endpointURL.toString());");
        stubPW.println("    }");

        stubPW.println("    public " + stubName + "() throws org.apache.axis.AxisFault {");

        HashSet types = getTypesInPortType(portType);
        Iterator it = types.iterator();

        stubPW.println("        try {" );
        stubPW.println("            service = new org.apache.axis.client.Service();");
        stubPW.println("            call = (org.apache.axis.client.Call) service.createCall();");

        while (it.hasNext()) {
            writeSerializationInit(stubPW, (Type) it.next());
        }

        stubPW.println("        }");
        stubPW.println("        catch(Exception t) {");
        stubPW.println("            throw new org.apache.axis.AxisFault(t);");
        stubPW.println("        }");

        stubPW.println("    }");
        stubPW.println();
        stubPW.println("    public void _setProperty(String name, Object value) {");
        stubPW.println("        properties.put(name, value);");
        stubPW.println("    }");
        stubPW.println();
        stubPW.println("    // From javax.xml.rpc.Stub");
        stubPW.println("    public Object _getProperty(String name) {");
        stubPW.println("        return properties.get(name);");
        stubPW.println("    }");
        stubPW.println();
        stubPW.println("    // From javax.xml.rpc.Stub");
        stubPW.println("    public void _setTargetEndpoint(java.net.URL address) {");
        stubPW.println("        call.setProperty(org.apache.axis.transport.http.HTTPTransport.URL, address.toString());");
        stubPW.println("    }");
        stubPW.println();
        stubPW.println("    // From javax.xml.rpc.Stub");
        stubPW.println("    public java.net.URL _getTargetEndpoint() {");
        stubPW.println("        try {");
        stubPW.println("            return new java.net.URL((String) call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL));");
        stubPW.println("        }");
        stubPW.println("        catch (java.net.MalformedURLException mue) {");
        stubPW.println("            return null; // ???");
        stubPW.println("        }");
        stubPW.println("    }");
        stubPW.println();
        stubPW.println("    // From javax.xml.rpc.Stub");
        stubPW.println("    public synchronized void setMaintainSession(boolean session) {");
        stubPW.println("        call.setMaintainSession(session);");
        stubPW.println("    }");
        stubPW.println();
        stubPW.println("    // From javax.naming.Referenceable");
        stubPW.println("    public javax.naming.Reference getReference() {");
        stubPW.println("        return null; // ???");
        stubPW.println("    }");
        stubPW.println();

        PrintWriter skelPW =
                null;
        PrintWriter implPW = null;

        if (bEmitSkeleton) {
            String skelName = name + "Skeleton";

            skelPW = printWriter(bindingQName, "Skeleton", "java", "Generating server-side skeleton:  ");
            String implType = portTypeName + " impl";
            String implName = name + "Impl";

            if (bMessageContext) {
                implType = portTypeName + "Axis impl";
            }
            writeFileHeader(skelName + ".java", namespaces.getCreate(bindingQName.getNamespaceURI()), skelPW);
            skelPW.println("public class " + skelName + " {");
            skelPW.println("    private " + implType + ";");
            skelPW.println();
            // RJB WARNING! - is this OK?
            skelPW.println("    public " + skelName + "() {");
            skelPW.println("        this.impl = new " + implName + "();");
            skelPW.println("    }");
            skelPW.println();
            skelPW.println("    public " + skelName + "(" + implType + ") {");
            skelPW.println("        this.impl = impl;");
            skelPW.println("    }");
            skelPW.println();

            String implFileName = implName + ".java";

            if (!fileExists (implFileName, bindingQName.getNamespaceURI())) {
                implPW = printWriter(bindingQName, "Impl", "java", "Generating server-side impl template:  ");
                writeFileHeader(implFileName, namespaces.getCreate(bindingQName.getNamespaceURI()), implPW);
                implPW.print("public class " + implName + " implements " + portTypeName);
                if (bMessageContext) {
                    implPW.print("Axis");
                }
                implPW.println(" {");
            }
        }

        List operations = binding.getBindingOperations();
        for (int i = 0; i < operations.size(); ++i) {
            BindingOperation operation = (BindingOperation) operations.get(i);
            Parameters parameters = (Parameters) portTypeInfo.get(operation.getOperation());

            // Get the soapAction from the <soap:operation>
            String soapAction = "";
            Iterator operationExtensibilityIterator = operation.getExtensibilityElements().iterator();
            for (; operationExtensibilityIterator.hasNext();) {
                Object obj = operationExtensibilityIterator.next();
                if (obj instanceof SOAPOperation) {
                    soapAction = ((SOAPOperation) obj).getSoapActionURI();
                    break;
                }
            }
            // Get the namespace for the operation from the <soap:body>
            String namespace = "";
            Iterator bindingInputIterator
                    = operation.getBindingInput().getExtensibilityElements().iterator();
            for (; bindingInputIterator.hasNext();) {
                Object obj = bindingInputIterator.next();
                if (obj instanceof SOAPBody) {
                    namespace = ((SOAPBody) obj).getNamespaceURI();
                    if (namespace == null)
                        namespace = "";
                    break;
                }
            }

            writeBindingOperation(operation, parameters, soapAction, namespace, isRPC, stubPW, skelPW, implPW);
        }

        stubPW.println("}");
        stubPW.close();

        if (bEmitSkeleton) {
            skelPW.println("}");
            skelPW.close();
        }
        if (implPW != null) {
            implPW.println("}");
            implPW.close();
        }

    } // writeBinding

    /**
     * In the stub constructor, write the serializer code for the complex types.
     */
    private void writeSerializationInit(PrintWriter pw, Type type) throws IOException {
        if (type.getBaseType() != null) {
            return;
        }
        if ( firstSer ) {
            pw.println("            javax.xml.rpc.namespace.QName qn;" );
            pw.println("            Class cls;" );
        }
        firstSer = false ;

        QName qname = type.getQName();
        //pw.println("            qn = new javax.xml.rpc.namespace.QName(\"" + qname.getNamespaceURI() + "\", \"" + type.getJavaLocalName() + "\");");
        pw.println("            qn = new javax.xml.rpc.namespace.QName(\"" + qname.getNamespaceURI() + "\", \"" + qname.getLocalPart() + "\");");
        pw.println("            cls = " + type.getJavaName() + ".class;");
        pw.println("            call.addSerializer(cls, qn, new org.apache.axis.encoding.BeanSerializer(cls));");
        pw.println("            call.addDeserializerFactory(qn, cls, org.apache.axis.encoding.BeanSerializer.getFactory());");
        pw.println();
    } // writeSerializationInit

    /**
     * Write the stub and skeleton code for the given BindingOperation.
     */
    private void writeBindingOperation(BindingOperation operation, Parameters parms,
                                        String soapAction, String namespace,
                                       boolean isRPC,
                                       PrintWriter stubPW, PrintWriter skelPW,
                                       PrintWriter implPW)
            throws IOException {

        String name = operation.getName();

        writeComment(stubPW, operation.getDocumentationElement());
        writeStubOperation(name, parms, soapAction, namespace, isRPC, stubPW);
        if (bEmitSkeleton) {
            writeSkeletonOperation(name, parms, skelPW);
            writeImplOperation(name, parms, implPW);
        }
    } // writeBindingOperation

    /**
     * Write the stub code for the given operation.
     */
    private void writeStubOperation(String name, Parameters parms, String soapAction,
                                    String namespace, boolean isRPC, PrintWriter pw) {
        pw.println(parms.signature + "{");
        pw.println("        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {");
        pw.println("            throw new org.apache.axis.NoEndPointException();");
        pw.println("        }");
        pw.println("        call.removeAllParameters();");

        // DUG: need to set the isRPC flag in the Call object

        // loop over paramters and set up in/out params
        for (int i = 0; i < parms.list.size(); ++i) {
            Parameter p = (Parameter) parms.list.get(i);


            Type type = emitFactory.getType(p.type);
            if (type == null) {
                // XXX yikes, something is wrong
            }
            QName qn = type.getQName();
            String typeString = "new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName(\"" + qn.getNamespaceURI() + "\", \"" +
                    qn.getLocalPart() + "\"))";
            if (p.mode == Parameter.IN) {
                pw.println("        call.addParameter(\"" + p.name + "\", " + typeString + ", org.apache.axis.client.Call.PARAM_MODE_IN);");
            }
            else if (p.mode == Parameter.INOUT) {
                pw.println("        call.addParameter(\"" + p.name + "\", " + typeString + ", call.PARAM_MODE_INOUT);");
            }
            else { // p.mode == Parameter.OUT
                pw.println("        call.addParameter(\"" + p.name + "\", " + typeString + ", call.PARAM_MODE_OUT);");
            }
        }
        // set output type
        if (!"void".equals(parms.returnType)) {
            QName qn = emitFactory.getType(parms.returnType).getQName();
            String outputType = "new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName(\"" + qn.getNamespaceURI() + "\", \"" +
              qn.getLocalPart() + "\"))";
            pw.println("        call.setReturnType(" + outputType + ");");

            pw.println();
        }

        pw.println("        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, \"" + soapAction + "\");");
        pw.println("        call.setProperty(call.NAMESPACE, \"" + namespace
                                                 + "\");" );
        pw.println("        call.setOperationName( \"" + name + "\");" );
        pw.print("        Object resp = call.invoke(");
        pw.print("new Object[] {");

        // Write the input and inout parameter list
        boolean needComma = false;
        for (int i = 0; i < parms.list.size(); ++i) {
            Parameter p = (Parameter) parms.list.get(i);

            if (needComma) {
                if (p.mode != Parameter.OUT)
                    pw.print(", ");
            }
            else
                needComma = true;
            if (p.mode == Parameter.IN)
                pw.print(wrapPrimitiveType(p.type, p.name));
            else if (p.mode == Parameter.INOUT)
                pw.print(wrapPrimitiveType(p.type, p.name + "._value"));
        }
        pw.println("});");
        pw.println();
        pw.println("        if (resp instanceof java.rmi.RemoteException) {");
        pw.println("            throw (java.rmi.RemoteException)resp;");
        pw.println("        }");

        int allOuts = parms.outputs + parms.inouts;
        if (allOuts > 0) {
            pw.println("        else {");
            if (allOuts == 1) {
                if (parms.inouts == 1) {
                    // There is only one output and it is an inout, so the resp object
                    // must go into the inout holder.
                    int i = 0;
                    Parameter p = (Parameter) parms.list.get(i);

                    while (p.mode != Parameter.INOUT)
                        p = (Parameter) parms.list.get(++i);
                    pw.println ("            " + p.name + "._value = " + getResponseString(p.type, "resp"));
                }
                else {
                    // (parms.outputs == 1)
                    // There is only one output and it is the return value.
                    pw.println("             return " + getResponseString(parms.returnType, "resp"));
                }
            }
            else {
                // There is more than 1 output.  resp is the first one.  The rest are from
                // call.getOutputParams ().  Pull the Objects from the appropriate place -
                // resp or call.getOutputParms - and put them in the appropriate place,
                // either in a holder or as the return value.
                pw.println("            java.util.Vector output = call.getOutputParams();");
                int outdex = 0;
                boolean firstInoutIsResp = (parms.outputs == 0);
                for (int i = 0; i < parms.list.size (); ++i) {
                    Parameter p = (Parameter) parms.list.get (i);
                    if (p.mode != Parameter.IN) {
                        if (firstInoutIsResp) {
                            firstInoutIsResp = false;
                            pw.println ("            " + p.name + "._value = " + getResponseString(p.type,  "resp"));
                        }
                        else {
                            pw.println ("            " + p.name + "._value = " + getResponseString(p.type, "((org.apache.axis.message.RPCParam) output.get(" + outdex++ + ")).getValue()"));
                        }
                    }

                }
                if (parms.outputs > 0)
                    pw.println ("            return " + getResponseString(parms.returnType, "resp"));

            }
            pw.println("        }");
        }
        pw.println("    }");
        pw.println();
    } // writeStubOperation

    /**
     * Write the skeleton code for the given operation.
     */
    private void writeSkeletonOperation(String name, Parameters parms, PrintWriter pw) {
        pw.println(parms.skelSignature);
        pw.println("    {");

        // Instantiate the holders
        for (int i = 0; i < parms.list.size(); ++i) {
            Parameter p = (Parameter) parms.list.get(i);

            String holder = holder(p.type);
            if (p.mode == Parameter.INOUT) {
                pw.println("        " + holder + " " + p.name + "Holder = new " + holder + "(" + p.name + ");");
            }
            else if (p.mode == Parameter.OUT) {
                pw.println("        " + holder + " " + p.name + "Holder = new " + holder + "();");
            }
        }

        // Call the real implementation
        if ( "void".equals(parms.returnType) )
            pw.print("        ");
        else
            pw.print("        Object ret = ");
        String call = "impl." + name + "(";
        if (bMessageContext) {
            call = call + "ctx";
            if (parms.list.size() > 0)
                call = call + ", ";
        }

        boolean needComma = false;
        for (int i = 0; i < parms.list.size(); ++i) {
            if (needComma)
                call = call + ", ";
            else
                needComma = true;
            Parameter p = (Parameter) parms.list.get(i);

            if (p.mode == Parameter.IN)
                call = call + p.name;
            else
                call = call + p.name + "Holder";
        }
        call = call + ")";
        if (parms.outputs == 0)
            pw.println(call + ";");
        else
            pw.println(wrapPrimitiveType(parms.returnType, call) + ";");

        // Handle the outputs, if there are any.
        if (parms.inouts + parms.outputs > 0) {
            if (parms.inouts == 0 && parms.outputs == 1)
            // The only output is a single return value; simply pass it through.
                pw.println("        return ret;");
            else if (parms.outputs == 0 && parms.inouts == 1) {
                // There is only one inout parameter.  Find it in the parms list and write
                // its return
                int i = 0;
                Parameter p = (Parameter) parms.list.get(i);
                while (p.mode != Parameter.INOUT)
                    p = (Parameter) parms.list.get(++i);
                pw.println("        return " + wrapPrimitiveType(p.type, p.name + "Holder._value") + ";");
            }
            else {
                // There are more than 1 output parts, so create a Vector to put them into.
                pw.println("        org.apache.axis.server.ParamList list = new org.apache.axis.server.ParamList();");
                if (!"void".equals(parms.returnType))
                    pw.println("        list.add(new org.apache.axis.message.RPCParam(\"" + parms.returnName + "\", ret));");
                for (int i = 0; i < parms.list.size(); ++i) {
                    Parameter p = (Parameter) parms.list.get(i);

                    if (p.mode != Parameter.IN)
                        pw.println("        list.add(new org.apache.axis.message.RPCParam(\"" + p.name + "\", " + wrapPrimitiveType(p.type, p.name + "Holder._value") +"));");
                }
                pw.println("        return list;");
            }
        }

        pw.println("    }");
        pw.println();
    } // writeSkeletonOperation

    /**
     * This method generates the axis server side dummy impl
     */
    private void writeImplOperation(String name, Parameters parms, PrintWriter pw) {
        if (pw != null) {
            if (bMessageContext) {
                pw.println(parms.axisSignature + " {");
            }
            else {
                pw.println(parms.signature + " {");
            }
            if (!"void".equals(parms.returnType)) {
                pw.print("        return ");

                if (isPrimitiveType(parms.returnType)) {
                    if ("boolean".equals(parms.returnType)) {
                        pw.println("false;");
                    } else {
                        pw.println("-3;");
                    }
                } else {
                    pw.println("null;");
                }
            }
            pw.println("    }");
        }
    } // writeImplOperation

    /**
     * Create the service class or classes
     */
    private void writeServices() throws IOException {
        Map services = def.getServices();
        Iterator i = services.values().iterator();

        while (i.hasNext()) {
            Service s = (Service) i.next();
            writeService(s);
        }
    }

    /**
     * Write out a single service class
     */
    private void writeService(Service service) throws IOException {
        QName serviceQName = service.getQName();
        String serviceName = Utils.capitalize(xmlNameToJava(serviceQName.getLocalPart()));
        String servicePackage = namespaces.getCreate(serviceQName.getNamespaceURI());
        PrintWriter servicePW = printWriter(serviceQName, null, "java", "Generating service class:  ");

        TestCaseEmitter testFactory = null;
        if (this.bEmitTestCase) {
            String className = serviceName + "TestCase";
            testFactory = new TestCaseEmitter(printWriter(serviceQName, "TestCase", "java", "Generating service test class:  "), className, this);

            testFactory.writeHeader(className, servicePackage);
            testFactory.writeInitCode();
        }

        writeFileHeader(serviceName + ".java", servicePackage, servicePW);

        // declare class
        servicePW.println("public class " + serviceName + " {");

        // output comments
        writeComment(servicePW, service.getDocumentationElement());
        if (this.bEmitTestCase) {
            this.writeComment(testFactory.getWriter(), service.getDocumentationElement());
        }

        // get ports
        Map portMap = service.getPorts();
        Iterator portIterator = portMap.values().iterator();

        // write a get method for each of the ports with a SOAP binding
        while (portIterator.hasNext()) {
            Port p = (Port) portIterator.next();
            Binding binding = p.getBinding();

            // If this isn't an SOAP binding, skip it
            if (wsdlAttr.getBindingType(binding) != WsdlAttributes.TYPE_SOAP) {
                continue;
            }

            String portName = p.getName();
            String stubClass = emitFactory.getJavaName(binding.getQName()) + "Stub";
            String bindingType = emitFactory.getJavaName(binding.getPortType().getQName());

            // Get endpoint address and validate it
            String address = getAddressFromPort(p);
            if (address == null) {
                // now what?
                throw new IOException("Emitter failure.  Can't find endpoint address in port " + portName + " in service " + serviceName);
            }
            try {
                URL ep = new URL(address);
            }
            catch (MalformedURLException e) {
                throw new IOException("Emitter failure.  Invalid endpoint address in port " + portName + " in service " + serviceName + ": " + address);
            }

            // Write out the get<PortName> methods
            servicePW.println();
            servicePW.println("    // Use to get a proxy class for " + portName);
            writeComment(servicePW, p.getDocumentationElement());
            servicePW.println("    private final java.lang.String " + portName + "_address = \"" + address + "\";");


            servicePW.println("" );
            servicePW.println("    public String get" + portName + "Address() {" );
            servicePW.println("        return " + portName + "_address;" );
            servicePW.println("    }" );
            servicePW.println("" );

            servicePW.println("    public " + bindingType + " get" + portName + "() {");
            servicePW.println("       java.net.URL endpoint;");
            servicePW.println("        try {");
            servicePW.println("            endpoint = new java.net.URL(" + portName + "_address);");
            servicePW.println("        }");
            servicePW.println("        catch (java.net.MalformedURLException e) {");
            servicePW.println("            return null; // unlikely as URL was validated in wsdl2java");
            servicePW.println("        }");
            servicePW.println("        return get" + portName + "(endpoint);");
            servicePW.println("    }");
            servicePW.println();
            servicePW.println("    public " + bindingType + " get" + portName + "(java.net.URL portAddress) {");
            servicePW.println("        try {");
            servicePW.println("            return new " + stubClass + "(portAddress);");
            servicePW.println("        }");
            servicePW.println("        catch (org.apache.axis.AxisFault e) {");
            servicePW.println("            return null; // ???");
            servicePW.println("        }");
            servicePW.println("    }");

            if (this.bEmitTestCase) {
                this.writeComment(testFactory.getWriter(), p.getDocumentationElement());
                testFactory.writeServiceTestCode(portName, binding);
        }
        }

        // write out standard service methods (available in all services)
        if (this.bEmitTestCase) {
            testFactory.finish();
        }

        // all done
        servicePW.println("}");
        servicePW.close();
    }


    /**
     * Return the endpoint address from a <soap:address location="..."> tag
     */
    private String getAddressFromPort(Port p) {
        // Get the endpoint for a port
        List extensibilityList = p.getExtensibilityElements();
        for (ListIterator li = extensibilityList.listIterator(); li.hasNext();) {
            Object obj = li.next();
            if (obj instanceof SOAPAddress) {
                return ((SOAPAddress) obj).getLocationURI();
            }
        }
        // didn't find it
        return null;
    }

    /**
     * Generate the deployment descriptor and undeployment descriptor
     * for the current WSDL file
     */
    private void writeDeploymentXML(String namespace) {
        try {
            QName dummyQName = new QName(namespace, "deploy");
            PrintWriter deployPW = printWriter(dummyQName, null, "xml", "Generating deployment document:  ");
            initializeDeploymentDoc(deployPW, "deploy");

            dummyQName = new QName(namespace, "undeploy");
            PrintWriter undeployPW = printWriter(dummyQName, null, "xml", "Generating deployment document:  ");
            initializeDeploymentDoc(undeployPW, "undeploy");
            writeDeployServices(deployPW, undeployPW);
            writeDeployTypes(deployPW);
            deployPW.println("</m:deploy>");
            deployPW.close();
            undeployPW.println("</m:undeploy>");
            undeployPW.close();
        }
        catch (IOException e) {
            System.err.println("Failed to write deployment documents");
            e.printStackTrace();
        }

    } // writeDeploymentXML

    /**
     * Initialize the deployment document, spit out preamble comments
     * and opening tag
     */
    private void initializeDeploymentDoc(PrintWriter pw, String deploymentOpName) throws IOException {
        pw.println("<!--                                         " +
                "                    -->");
        pw.println("<!--Use this file to " + deploymentOpName +
                " some handlers/chains and services  -->");
        pw.println("<!--Two ways to do this:                     " +
                "                    -->");
        pw.println("<!--  java org.apache.axis.utils.Admin " +
                deploymentOpName + ".xml              -->");
        pw.println("<!--     from the same dir that the Axis " +
                "engine runs             -->");
        pw.println("<!--or                                     " +
                "                      -->");
        pw.println("<!--  java org.apache.axis.client.AdminClient " +
                deploymentOpName + ".xml       -->");
        pw.println("<!--     after the axis server is running    " +
                "                    -->");
        pw.println("<!--This file will be replaced by WSDD once " +
                "it's ready           -->");
        pw.println();
        pw.println("<m:" + deploymentOpName + " xmlns:m=\"AdminService\">");
    } // initializeDeploymentDoc

    /**
     * Write out bean mappings for each type
     */
    private void writeDeployTypes(PrintWriter pw) throws IOException {
        HashMap types = emitFactory.getTypes();

        if (types.isEmpty()) return;

        pw.println();

        pw.print("   <beanMappings ");
        HashMap nsMap = new HashMap();
        int i = 1;
        String nsPrefix = null;
        Iterator it = types.values().iterator();
        while (it.hasNext()) {
            Type type = (Type) it.next();
            if (type.getBaseType() == null) {
                if (!nsMap.containsKey(type.getQName().getNamespaceURI())) {
                  pw.println("");
                  nsPrefix = "ns" + i++;
                  nsMap.put(type.getQName().getNamespaceURI(), nsPrefix);
                  pw.print("     xmlns:" + nsPrefix  + "=\"" + type.getQName().getNamespaceURI() + "\"");
                }
            }
        }
        pw.println(">");
        it = types.values().iterator();
        while (it.hasNext()) {
            Type type = (Type) it.next();
            if (type.getBaseType() == null) {
                nsPrefix = (String)nsMap.get(type.getQName().getNamespaceURI());
                pw.println("     <" + nsPrefix + ":" + type.getQName().getLocalPart()
                       + " classname=\"" + type.getJavaName() +"\"/>");
            }
        }
        pw.println("   </beanMappings>");

    } //writeDeployTypes

    /**
     * Write out deployment and undeployment instructions for each WSDL service
     */
    private void writeDeployServices(PrintWriter deployPW, PrintWriter undeployPW) throws IOException {
        //deploy the ports on each service
        Map serviceMap = def.getServices();
        for (Iterator mapIterator = serviceMap.values().iterator(); mapIterator.hasNext();) {
            Service myService = (Service) mapIterator.next();

            deployPW.println();
            deployPW.println("   <!-- Services from " + myService.getQName().getLocalPart() + " WSDL service -->");
            deployPW.println();

            undeployPW.println();
            undeployPW.println("   <!-- Services from " + myService.getQName().getLocalPart() + " WSDL service -->");
            undeployPW.println();

            for (Iterator portIterator = myService.getPorts().values().iterator(); portIterator.hasNext();) {
                Port myPort = (Port) portIterator.next();
                writeDeployPort(deployPW, undeployPW, myPort);
            }
        }
    } //writeDeployServices

    /**
     * Write out deployment and undeployment instructions for given WSDL port
     */
    private void writeDeployPort(PrintWriter deployPW, PrintWriter undeployPW, Port port) throws IOException {
        Binding binding = port.getBinding();
        String serviceName = port.getName();

        boolean isRPC = (wsdlAttr.getBindingStyle(binding) == WsdlAttributes.STYLE_RPC);

        deployPW.println("   <service name=\"" + serviceName
                + "\" pivot=\"" + (isRPC ? "RPCDispatcher" : "MsgDispatcher") + "\">");
        undeployPW.println("   <service name=\"" + serviceName
                + "\" pivot=\"" + (isRPC ? "RPCDispatcher" : "MsgDispatcher") + "\">");

        writeDeployBinding(deployPW, binding);

        deployPW.println("   </service>");
        undeployPW.println("   </service>");
    } //writeDeployPort

    /**
     * Write out deployment instructions for given WSDL binding
     */
    private void writeDeployBinding(PrintWriter deployPW, Binding binding) throws IOException {
        QName bindingQName = binding.getQName();
        String packageName = namespaces.getCreate(bindingQName.getNamespaceURI());
        deployPW.println("      <option name=\"className\" value=\""
                         + packageName + "."
                         + bindingQName.getLocalPart() + "Skeleton" + "\"/>");

        String methodList = "";
        Iterator operationsIterator = binding.getBindingOperations().iterator();
        for (; operationsIterator.hasNext();) {
            BindingOperation op = (BindingOperation) operationsIterator.next();
            methodList = methodList + " " + op.getName();
        }

        deployPW.println("      <option name=\"methodName\" value=\"" + methodList + "\"/>");

        if (scope == APPLICATION_SCOPE) {
            deployPW.println("      <option name=\"scope\" value=\"Application\"/>");
        }
        else if (scope == REQUEST_SCOPE) {
            deployPW.println("      <option name=\"scope\" value=\"Request\"/>");
        }
        else if (scope == SESSION_SCOPE) {
            deployPW.println("      <option name=\"scope\" value=\"Session\"/>");
        }
    } //writeDeployBinding

    //////////////////////////////
    //
    // Methods using types (non WSDL)
    //

    /**
     * Generate bindings (classes and class holders) for the complex types.
     * If generating serverside (skeleton) spit out beanmappings
     */
    private void writeTypes() throws IOException {
        HashMap types = emitFactory.getTypes();
        Iterator i = types.values().iterator();
        while (i.hasNext()) {
            Type type = (Type) i.next();
            if (type.isDefined() && type.getBaseType() == null) {
                writeType(type);
                writeHolder(type);
            }
        }
    } // writeTypes

    /**
     * Generate the binding for the given type.
     */
    private void writeType(Type type) throws IOException {

        Node node = type.getNode();

        // Generate the proper class for either "complex" or "enumeration" types
        Vector v = emitFactory.getComplexElementTypesAndNames(node);
        if (v != null)
            writeComplexType(type, v);
        else {
            v = emitFactory.getEnumerationBaseAndValues(node);
            if (v != null) {
                writeEnumType(type, v);
            }
        }
    } // writeType

   /**
     * Generate the binding for the given complex type.
     * The elements vector contains the Types (even indices) and
     * element names (odd indices) of the contained elements
     */
    private void writeComplexType(Type type, Vector elements) throws IOException {
        Node node = type.getNode();

        // We are only interested in the java names of the types, so replace the
        // Types in the list with their java names.
        for (int i=0; i < elements.size(); i+=2) {
            elements.setElementAt(((Type) elements.get(i)).getJavaName(), i);
        }

        String javaName = type.getJavaLocalName();

        PrintWriter typePW = printWriter(type.getQName(), null, "java", "Generating type implementation:  ");

        writeFileHeader(javaName + ".java", type.getJavaPackageName(), typePW);
        typePW.println("public class " + javaName + " implements java.io.Serializable {");

        for (int i = 0; i < elements.size(); i += 2) {
            String variable = (String) elements.get(i + 1);
            if (Utils.isJavaKeyword(variable)) {
                variable = Utils.makeNonJavaKeyword(variable);
            }
            typePW.println("    private " + elements.get(i) + " " + variable + ";");
        }

        typePW.println();
        typePW.println("    public " + javaName + "() {");
        typePW.println("    }");
        typePW.println();
        if (elements.size() > 0) {
            typePW.print("    public " + javaName + "(");
            for (int i = 0; i < elements.size(); i += 2) {
                if (i != 0) typePW.print(", ");
                String variable = (String) elements.get(i + 1);
                if (Utils.isJavaKeyword(variable)) {
                    variable = Utils.makeNonJavaKeyword(variable);
                }
                typePW.print((String) elements.get(i) + " " + variable);
            }
            typePW.println(") {");
            for (int i = 1; i < elements.size(); i += 2) {
                String variable = (String) elements.get(i);
                if (Utils.isJavaKeyword(variable)) {
                    variable = Utils.makeNonJavaKeyword(variable);
                }
                typePW.println("        this." + variable + " = " + variable + ";");
            }
            typePW.println("    }");
        }
        typePW.println();
        for (int i = 0; i < elements.size(); i += 2) {
            String typeName = (String) elements.get(i);
            String name = (String) elements.get(i + 1);
            String capName = Utils.capitalize(name);

            if (Utils.isJavaKeyword(name)) {
                name = Utils.makeNonJavaKeyword(name);
            }
            typePW.println("    public " + typeName + " get" + capName + "() {");
            typePW.println("        return " + name + ";");
            typePW.println("    }");
            typePW.println();
            typePW.println("    public void set" + capName + "(" + typeName + " " + name + ") {");
            typePW.println("        this." + name + " = " + name + ";");
            typePW.println("    }");
            typePW.println();
        }
        typePW.println("}");
        typePW.close();
    } // writeComplexType

   /**
     * Generate the binding for the given enumeration type.
     * The values vector contains the base type (first index) and
     * the values (subsequent Strings)
     */
    private void writeEnumType(Type eType, Vector values) throws IOException {

        Node node = eType.getNode();

        // The first index is the base type.  Get its java name.
        String baseType = ((Type) values.get(0)).getJavaName();

        String javaName = eType.getJavaLocalName();

        PrintWriter typePW = printWriter(eType.getQName(), null, "java", "Generating enum type implementation:  ");

        writeFileHeader(javaName + ".java", eType.getJavaPackageName(), typePW);
        typePW.println("public class " + javaName + " implements java.io.Serializable {");
        for (int i=1; i < values.size(); i++) {
            typePW.println("    public static final " + baseType + " _" + values.get(i)
                           + " = \"" + values.get(i) + "\";");
        }

        typePW.println("}");
        typePW.close();
    } // writeEnumType

    /**
     * Generate the holder for the given complex type.
     */
    private void writeHolder(Type type) throws IOException {
        Node node = type.getNode();
        String javaName = type.getJavaLocalName();

        PrintWriter pw = printWriter(type.getQName(), "Holder", "java", "Generating type implementation holder:  ");

        writeFileHeader(javaName + "Holder.java", type.getJavaPackageName(), pw);
        pw.println("public final class " + javaName + "Holder implements java.io.Serializable {");
        pw.println("    public " + javaName + " _value;");
        pw.println();
        pw.println("    public " + javaName + "Holder() {");
        pw.println("    }");
        pw.println();
        pw.println("    public " + javaName + "Holder(" + javaName + " value) {");
        pw.println("        this._value = value;");
        pw.println("    }");
        pw.println();
        pw.println("    // ??? what else?");
        pw.println("}");
        pw.close();
    } // writeHolder


    //
    // Methods using types (non WSDL)
    //
    //////////////////////////////

    ///////////////////////////////////////////////////
    //
    // Utility methods
    //

    public Namespaces getNamespaces() {
        return namespaces;
    } // getNamespaces

    public TypeFactory getTypeFactory() {
        return emitFactory;
    } // getTypeFactory

    /**
     * Does the given file already exist?
     */
    private boolean fileExists (String name, String namespace) throws IOException
    {
        String packageName = namespaces.getAsDir(namespace);
        String fullName = packageName + name;
        return new File (fullName).exists();
    } // fileExists

    /**
     * Get a PrintWriter attached to a file with the given name.
     */
    private PrintWriter printWriter(QName qname, String suffix, String extension, String message) throws IOException
    {
        String name = qname.getLocalPart();
        // Don't capitalize for deploy.xml and undeploy.xml
        if(name.indexOf("deploy")==-1)
            name = Utils.capitalize(xmlNameToJava(name));
        String fileName = name + (suffix == null ? "" : suffix) + '.' + extension;
        String packageName = namespaces.getCreate(qname.getNamespaceURI());
        String packageDirName = namespaces.toDir(packageName);
        fileList.add(packageDirName + fileName);
        classList.add(packageName + "." + name);
        File file = new File(packageDirName, fileName);
        if (bVerbose) {
            System.out.println(message + file.getPath());
        }
        return new PrintWriter(new FileWriter(file));
    } // printWriter

    /**
     * output documentation element as a Java comment
     */
    private void writeComment(PrintWriter pw, Element element) {
        // This controls how many characters per line
        final int LINE_LENGTH = 65;

        if (element == null)
            return;

        String comment = element.getFirstChild().getNodeValue();

        // Strip out stuff that will really mess up our comments
        comment = comment.replace('\r', ' ');
        comment = comment.replace('\n', ' ');

        if (comment != null) {
            int start = 0;

            pw.println();  // blank line

            // make the comment look pretty
            while (start < comment.length()) {
                int end = start + LINE_LENGTH;
                if (end > comment.length())
                    end = comment.length();
                // look for next whitespace
                while (end < comment.length() &&
                        !Character.isWhitespace(comment.charAt(end))) {
                    end++;
                }
                pw.println("    // " + comment.substring(start, end).trim());
                start = end + 1;
            }
        }
    }

    /**
     * Given a type name, return the Java mapping of that type's holder.
     */
    protected String holder(String typeValue) {
        if (typeValue.equals("java.lang.String")) {
            return "javax.xml.rpc.holders.StringHolder";
        }
        else if (typeValue.equals("java.math.BigDecimal")) {
            return "javax.xml.rpc.holders.BigDecimalHolder";
        }
        else if (typeValue.equals("java.util.Date")) {
            return "javax.xml.rpc.holders.DateHolder";
        }
        else if (typeValue.equals("javax.xml.rpc.namespace.QName")) {
            return "javax.xml.rpc.holders.QNameHolder";
        }
        else if (typeValue.equals("int")
                || typeValue.equals("long")
                || typeValue.equals("short")
                || typeValue.equals("float")
                || typeValue.equals("double")
                || typeValue.equals("boolean")
                || typeValue.equals("byte"))
            return "javax.xml.rpc.holders." + Utils.capitalize(typeValue) + "Holder";
        else
            return typeValue + "Holder";
    } // holder

    /**
     * Map an XML name to a valid Java identifier
     */
    private String xmlNameToJava(String name)
    {
        char[] nameArray = name.toCharArray();
        for(int j = 0, len = name.length(); j < len; ++j) {
            char c = nameArray[j];
            if( !Character.isLetterOrDigit(c) && c != '_' )
                nameArray[j] = '_';
        }
        return new String(nameArray);
    }

    /**
     * A simple map of the primitive types and their holder objects
     */
    private static HashMap TYPES = new HashMap(7);

    static {
        TYPES.put("int", "Integer");
        TYPES.put("float", "Float");
        TYPES.put("boolean", "Boolean");
        TYPES.put("double", "Double");
        TYPES.put("byte", "Byte");
        TYPES.put("short", "Short");
        TYPES.put("long", "Long");

    }

    /**
     * Return the Object variable 'var' cast to the appropriate type
     * doing the right thing for the primitive types.
     */
    private String getResponseString(String type, String var) {
        String objType = (String) TYPES.get(type);
        if (objType != null) {
            return "((" + objType + ") " + var + ")." + type + "Value();";
        }
        else if (type.equals("void")) {
            return ";";
        }
        else {
            return "(" + type + ") " + var + ";";
        }
    }

    /**
     * Return a string with "var" wrapped as an Object type if needed
     */
    private String wrapPrimitiveType(String type, String var) {
        String objType = (String) TYPES.get(type);
        if (objType != null) {
            return "new " + objType + "(" + var + ")";
        }
        else {
            return var;
        }
    }

    /**
     * Write a common header, including the package name to the
     * provided stream
     */
    protected void writeFileHeader(String filename, String pkgName, PrintWriter pw) {
        pw.println("/**");
        pw.println(" * " + filename);
        pw.println(" *");
        pw.println(" * This file was auto-generated from WSDL");
        pw.println(" * by the Apache Axis Wsdl2java emitter.");
        pw.println(" */");
        pw.println();

        // print package declaration
        pw.println("package " + pkgName + ";");
        pw.println();
    }

    protected boolean isPrimitiveType(String type) {
        return TYPES.get(type) != null;
    }
}
