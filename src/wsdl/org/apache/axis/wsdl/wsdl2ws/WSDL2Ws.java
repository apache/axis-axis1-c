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

package org.apache.axis.wsdl.wsdl2ws;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;

import javax.wsdl.Binding;
import javax.wsdl.Fault;
import javax.wsdl.Operation;
import javax.wsdl.Part;
import javax.wsdl.Port;
import javax.wsdl.PortType;
import javax.wsdl.Service;
import javax.xml.namespace.QName;
import javax.xml.rpc.holders.IntHolder;

// hold off until we use 1.4 or newer axis.jar.
//import org.apache.axis.constants.Style;

import org.apache.axis.wsdl.symbolTable.BaseType;
import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.CElementDecl;
import org.apache.axis.wsdl.symbolTable.CSchemaUtils;
import org.apache.axis.wsdl.symbolTable.CContainedAttribute;
import org.apache.axis.wsdl.symbolTable.CollectionElement;
import org.apache.axis.wsdl.symbolTable.CollectionType;
import org.apache.axis.wsdl.symbolTable.DefinedElement;
import org.apache.axis.wsdl.symbolTable.DefinedType;
import org.apache.axis.wsdl.symbolTable.Element;
import org.apache.axis.wsdl.symbolTable.Parameters;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.wsdl2ws.info.FaultInfo;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ServiceInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.TypeMap;
import org.apache.axis.wsdl.wsdl2ws.info.WSDLInfo;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
import org.apache.axis.wsdl.wsdl2ws.info.WrapperInfo;
import org.w3c.dom.Node;

/**
 * This is the main class for the WSDL2Ws Tool. This class reuses the code in the 
 * Axis java implementations to parse the WSDL file. Here is what is done: 
 * 
 *  1) create a Symbol table by parsing WSDL file.
 *  2) create TypeMap object by iterating through types in the Symbol Table.
 *  3) create WrapperInfo object using command line arguments and SymbolTable information.
 *  4) create ServiceInfo object parsing the Symbol table.
 *  5) create WebServiceContext using above three classes and start execution 
 * 
 * @author hemapani@opensource.lk
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 * @author hawkeye (hawkinsj@uk.ibm.com)
 * @author nadir amra (amra@us.ibm.com)
 */
public class WSDL2Ws
{
    public static boolean c_verbose = false;

    private String  c_language;
    private boolean c_wsdlWrappingStyle;
    private boolean c_userRequestedWSDLWrappingStyle = false;
    private String  c_targetoutputLocation = null;
    private String  c_targetEngine = null;
        
    // WSDL parser symbol table
    private SymbolTable c_symbolTable;
    
    // The types
    private TypeMap c_typeMap;
    
    // WSDL info.
    private WSDLInfo c_wsdlInfo;

    /**
     * Prints out usage.
     */
    public static void usage()
    {
        System.out.println(
            "java WSDL2Ws -<options> <wsdlfile>\n"
                + "-h, -help              print this message\n"
                + "-o<folder>             target output folder - default is current folder.\n"
                + "-l<c++|c>              target language (c++|c) - default is c++.\n"
                + "-s<server|client>      target side (server|client) - default is server.\n"
                + "-v, -verbose           be verbose.\n"
                + "-t<timeout>            uri resolution timeout in seconds - default is 0 (no timeout).\n"
                + "-w<wrapped|unwrapped>  generate wrapper style or not - default is wrapped.\n"
                );
    }
    
    /**
     * Main entry point. 
     * 
     * @param args
     * @throws Exception
     */
    public static void main(String[] args) throws Exception
    {
        // Get parameters and validate
        CLArgParser data = new CLArgParser(args);
        
        if (!data.areOptionsValid() || data.isSet("h") || data.getArgumentCount() != 1)
        {
            usage();
            return;
        }

        // Kick off code generation
        try
        {
            WSDL2Ws gen = new WSDL2Ws(data);
            gen.generateWrappers();

            System.out.println("\nCode generation completed. Generated files in directory '" + gen.getTargetOutputLocation() + "'.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.out.println("\nCode generation failed. Please see errors above.\n");
        }
    }    
    
    /**
     * Gathers the parameters passed in and parses the WSDL file, generating the symbol table. 
     * 
     * @param cmdLineArgs
     * @throws WrapperFault
     */
    public WSDL2Ws(CLArgParser cmdLineArgs) throws WrapperFault
    {
        try
        {
            // ==================================================
            // Process the parameters
            // ==================================================            
            
            // Verbose mode?
            if (cmdLineArgs.isSet("v"))
                c_verbose = true;
            
            // Target location - we resolve to canonical path and use path in completion message later on.
            c_targetoutputLocation = cmdLineArgs.getOptionBykey("o");
            if (c_targetoutputLocation == null)
                c_targetoutputLocation = "." + File.separator;
            c_targetoutputLocation = (new File(c_targetoutputLocation)).getCanonicalPath();
            
            // language c or c++ - CUtils.setLanguage MUST be invoked at the very beginning!
            c_language = cmdLineArgs.getOptionBykey("l");
            if (c_language == null)
                c_language = "c++";
            CUtils.setLanguage(c_language);
            
            // generate artifacts for server, client or both?
            c_targetEngine = cmdLineArgs.getOptionBykey("s");
            if (c_targetEngine == null)
                c_targetEngine = "server";
            
            // Wrapped or unwrapped? The default will be wrapped. 
            String wsdlWrapStyle = cmdLineArgs.getOptionBykey("w");
            if (wsdlWrapStyle == null)
                c_wsdlWrappingStyle = true;
            else if (wsdlWrapStyle.equalsIgnoreCase("wrapped"))
            {
                c_wsdlWrappingStyle = true;
                c_userRequestedWSDLWrappingStyle = true;
            }
            else
                c_wsdlWrappingStyle = false;            
            
            // ==================================================
            // Parse the WSDL file
            // ==================================================
            
            c_wsdlInfo = new WSDLInfo(cmdLineArgs.getArgument(0));
            c_wsdlInfo.setVerbose(c_verbose);
            c_wsdlInfo.setTimeout(cmdLineArgs.getOptionBykey("t")); 
            c_wsdlInfo.setNoWrapperStyle(c_wsdlWrappingStyle == false);

            c_symbolTable = c_wsdlInfo.parse();
            
            // ==================================================
            // Let us do some validation on the WSDL passed in.
            // ==================================================
            
            // Maximum of one <service> tag is supported in WSDL for the time being.
            if (c_wsdlInfo.getServices().size() > 1)
                throw new WrapperFault("Multiple service definitions not supported.");
            
            // TODO
            // At this time we require a service definition to be defined, but in 
            // future if not found that caller needs to specify a binding to use in 
            // order for us to generate the stubs.  Not having service definition will
            // only result in not knowing the Web service end point, so it is really not necessary.
            if (c_wsdlInfo.getServices().size() == 0)
                throw new WrapperFault("Service definition not found. A service definition must be specified.");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    /**
     * Kicks of the generation of the stub code.
     * 
     * @throws WrapperFault
     */
    public void generateWrappers() throws Exception
    {        
        // ==================================================
        // Generate types, populating the type map
        // ==================================================            
        
        c_typeMap = new TypeMap();
        
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
                                
                createTypeInfo(type);
            }
        }
        
        // ==================================================
        // Get service, ports, binding, and port type
        // ==================================================           
   
        //TODO  resolve this
        //  this code will generate one stub corresponding to a port.  Other ports
        //  are ignored. Should really generate one service stub per port.

        // Get service definition, binding entry, port type.  We first ask for SOAP 1.1 ports
        // that have a binding style of document....if there is none, then we ask for 
        // SOAP 1.1 ports that have a binding style of rpc.
        Service service = (Service)c_wsdlInfo.getServices().get(0);
        ArrayList servicePorts = c_wsdlInfo.getPortsSOAP11Document(service);
        if (servicePorts.isEmpty())
            servicePorts = c_wsdlInfo.getPortsSOAP11RPC(service);
        if (servicePorts.isEmpty())
            throw new WrapperFault("A port with a supported binding was not found.");

        Port port                 = (Port)servicePorts.get(0);
        Binding binding           = port.getBinding();
        BindingEntry bindingEntry = c_symbolTable.getBindingEntry(binding.getQName());
        
        PortType portType         = bindingEntry.getBinding().getPortType();
        if (portType == null)
            throw new WrapperFault("Port type specified in binding '" + binding.getQName().getLocalPart() + "' not found");
        
        // ==================================================
        // Build the context that is needed by the code generators.
        // ==================================================            
                       
        // Wrapper info
        WrapperInfo wrapperInfo = 
            new WrapperInfo(bindingEntry.getBindingStyle().getName(), 
                            c_language, c_targetoutputLocation, c_targetEngine,
                            c_wsdlInfo.getTargetNameSpaceOfWSDL());
        
        // Service info
        String serviceName = CUtils.getClassNameFromFullyQualifiedName(portType.getQName().getLocalPart());
        ArrayList serviceMethods = processServiceMethods(portType, bindingEntry);
        ServiceInfo serviceInfo = new ServiceInfo(serviceName, serviceMethods, WSDLInfo.getTargetEndPointURI(port));
        
        // Context
        WebServiceContext wsContext = new WebServiceContext(wrapperInfo, serviceInfo, c_typeMap); 
        
        // Generator
        WebServiceGenerator wsg = WebServiceGeneratorFactory.createWebServiceGenerator(wsContext);
        if (wsg == null)
            throw new WrapperFault("WSDL2Ws does not support the option combination");
        
        // There must be a better way to do this
        exposeReferenceTypes(wsContext);
        exposeMessagePartsThatAreAnonymousTypes(wsContext);
        // This call must be last one called of the exposexxx methods!
        exposeNestedTypesThatAreAnonymousTypes(wsContext);
        
        if (c_verbose)
        {
            System.out.println( "Dumping typeMap....");
            
            it = c_typeMap.getTypes().iterator();
            while (it.hasNext())
            {
                System.out.println(it.next());
            }
        }
        
        // ==================================================
        // Generate the artifacts
        // ================================================== 
        
        wsg.generate();
    }    
    
    /**
     * Returns absolute path to where the generated code will be located. 
     * 
     * @return the absolute path to the target location
     */
    public String getTargetOutputLocation()
    {
        return c_targetoutputLocation;
    }
    
    /**
     * Process service operations, generating information about each operation.
     *
     * @param porttype
     * @param bindingEntry
     * @return               array of MethodInfo objects.
     * @throws WrapperFault
     */
    private ArrayList processServiceMethods(PortType porttype, BindingEntry bindingEntry) throws WrapperFault
    {
        ArrayList serviceMethods = new ArrayList();
        
        //get operation list
        Iterator oplist = porttype.getOperations().iterator();
        while (oplist.hasNext())
        {
            Operation op     = (Operation) oplist.next();
            MethodInfo minfo = new MethodInfo(op.getName());
            
            // This chunk of code is new and we hope to use it more in the future to replace some of the 
            // things we do to process parameters.
            // When getOperationParameters() is called, the code, assuming user did not request unwrapped,
            // will determine whether the operation is eligible for wrapped-style.   The bad thing is that
            // isWrapped() is a method on the SymbolTable class.  So before processing an operation, 
            // we call setWrapped(false) before calling getOperationParameters() so that we can determine 
            // on a per-operation basis whether the operation is eligible for wrapped-style processing.
            c_symbolTable.setWrapped(false);
            Parameters opParams=null;
            try
            {
                opParams = c_symbolTable.getOperationParameters(op, "", bindingEntry);
                minfo.setOperationParameters(opParams);
                minfo.setEligibleForWrapped(c_symbolTable.isWrapped());
                
                // mark the method as wrapped or unwrapped.
                if (!c_wsdlWrappingStyle || !minfo.isEligibleForWrapped())
                {
                    minfo.setIsUnwrapped(true);
                    minfo.setConsumeBodyOnMessageValidation(false);
                }
            }
            catch (IOException e)
            {
                throw new WrapperFault(e);
            }

            if (c_verbose)
            {
                System.out.println("\n\n-----------------------------------------------");
                System.out.println("Parameters for operation: " + op.getName()); 
                System.out.println("-----------------------------------------------");
                System.out.println(opParams);
                System.out.println("-----------------------------------------------");
            }
            
            //setting the faults
            addFaultInfo(op.getFaults(), minfo);
            
            //add each parameter to parameter list
            if ("document".equals(bindingEntry.getBindingStyle().getName()))
            {
                if (c_userRequestedWSDLWrappingStyle && !minfo.isEligibleForWrapped())
                    System.out.println("INFORMATIONAL: Operation '" + op.getName() + "' is not eligible for wrapper-style, using non-wrapper style.");
                addDocumentStyleInputMessageToMethodInfo(op, minfo);
            }
            else
                addRPCStyleInputMessageToMethodInfo(op, minfo);

            //get the return type
            if (op.getOutput() != null)
            {
                Iterator returnlist = op.getOutput().getMessage().getParts().values().iterator();
                if (returnlist.hasNext() && "document".equals(bindingEntry.getBindingStyle().getName()))
                    addDocumentStyleOutputMessageToMethodInfo(minfo, (Part) returnlist.next());
                else
                    addRPCStyleOutputMessageToMethodInfo(op, minfo);
            }
            
            //add operation to operation List
            serviceMethods.add(minfo); 
        }
        
        // Need to get some stuff from binding element such as SOAPAction and namespace for 
        // each operation - we store the information in the method. 
        List operations = bindingEntry.getBinding().getBindingOperations();
        if (operations != null)
        {
            for (int i = 0; i < operations.size(); i++)
            {
                //for the each binding operation found
                if (operations.get(i) instanceof javax.wsdl.BindingOperation)
                {
                    javax.wsdl.BindingOperation bindinop = (javax.wsdl.BindingOperation) operations.get(i);
                    
                    String name = bindinop.getName();
                    MethodInfo method = null;
                    
                    for (int ii = 0; ii < serviceMethods.size(); ii++)
                        if (((MethodInfo) serviceMethods.get(ii)).getMethodname().equals(name))
                            method = (MethodInfo) serviceMethods.get(ii);
                    
                    if (method == null)
                        throw new WrapperFault("The binding and portType elements do not match.");                    
                    
                    // Get binding operation information and store in method for later use.
                    WSDLInfo.updateMethodInfoFromBinding(bindinop, method);
                }
            }
        }
        
        return serviceMethods;
    }

    /**
     * @param op
     * @param minfo MethodInfo object into which output message and it's elements are to be added
     * @throws WrapperFault
     */
    private void addRPCStyleOutputMessageToMethodInfo(Operation op, MethodInfo minfo)
        throws WrapperFault
    {
        ParameterInfo pinfo;
        Iterator returnlist;

        minfo.setInputMessage(op.getInput().getMessage().getQName());
        minfo.setOutputMessage(op.getOutput().getMessage().getQName());
        // minfo.setFaultMessage();
        if (op.getParameterOrdering() != null)
        {
            for (int ix = 0; ix < op.getParameterOrdering().size(); ix++)
            {
                Part p = (Part) (op.getOutput()
                                   .getMessage()
                                   .getParts()
                                   .get((String) op.getParameterOrdering().get(ix)));
                if (p == null)
                    continue;
                pinfo = createParameterInfo(p);
                if (null != pinfo)
                    minfo.addOutputParameter(pinfo);
            }
            
            /* there can be more output parameters than in parameterOrder list (partial parameter ordering) */
            returnlist = op.getOutput().getMessage().getParts().values().iterator();
            while (returnlist.hasNext())
            { 
                //RPC style messages can have multiple parts
                Part p = (Part) returnlist.next();
                if (op.getParameterOrdering().contains(p.getName()))
                    continue;
                pinfo = createParameterInfo(p);
                if (null != pinfo)
                    minfo.addOutputParameter(pinfo);
            }
        }
        else
        {
            returnlist = op.getOutput().getMessage().getParts().values().iterator();
            while (returnlist.hasNext())
            { 
                //RPC style messages can have multiple parts
                Part p = ((Part) returnlist.next());
                pinfo = createParameterInfo(p);
                if (null != pinfo)
                    minfo.addOutputParameter(pinfo);
            }
        }
    }

    /**
     * @param minfo MethodInfo object into which output message and it's elements are to be added
     * @param part
     * @throws WrapperFault
     */
    private void addDocumentStyleOutputMessageToMethodInfo(MethodInfo minfo, Part part)
        throws WrapperFault
    {
        QName qname;
        QName minfoqname;
        TypeEntry elementTypeEntry;
        
        Element element = c_symbolTable.getElement(part.getElementName());

        if (element == null)
        {
            elementTypeEntry = c_symbolTable.getType(part.getTypeName());
            qname            = elementTypeEntry.getQName();
            minfoqname       = elementTypeEntry.getQName();
        }
        else
        {
            elementTypeEntry = element.getRefType();
            qname            = elementTypeEntry.getQName();
            minfoqname       = element.getQName();
        }
        
        minfo.setOutputMessage(minfoqname);

        if (qname == null)
            return;
        
        Type type = c_typeMap.getType(qname);
        if (type == null)
            throw new WrapperFault("Unregistered type " + qname + " referenced!");

        // TODO - need to look into this more.
        // For wrapped style, inner attributes and elements are added as parameters.
        // For unwrapped style, objects are used for the parameters (i.e. classes or structures).
        
        Iterator names = type.getElementnames();
        if (!minfo.isUnwrapped())
        {
            if (!names.hasNext())
            {
                // TODO what if not simple?
                if (type.isSimpleType())
                {
                    String elementName = (String) element.getQName().getLocalPart();
                    ParameterInfo pinfo = new ParameterInfo();
                    pinfo.setType(type);
                    pinfo.setParamName(elementName, c_typeMap);
                    pinfo.setElementName(element.getQName());
                    if (type.getName().equals(CUtils.anyTypeQname))
                        pinfo.setAnyType(true);
                    minfo.addOutputParameter(pinfo);                    
                    minfo.setConsumeBodyOnMessageValidation(false);
                }
            }
            else
            {
                while (names.hasNext())
                {
                    String elementname  = (String) names.next();
                    CElementDecl eleinfo = type.getElementForElementName(elementname);
                    Type innerType      = eleinfo.getType();
                    
                    ParameterInfo pinfo = new ParameterInfo();
                    pinfo.setType(innerType);
                    pinfo.setParamName(elementname, c_typeMap);
                    
                    if (eleinfo.getMaxOccurs() > 1)
                        pinfo.setArray(true);
                    
                    pinfo.setNillable(eleinfo.isNillable());
                    
                    if (eleinfo.getMinOccurs() == 0)
                        pinfo.setOptional(true);
                    else
                        pinfo.setOptional(false);
    
                    pinfo.setElementName(type.getElementForElementName(elementname).getName());
                    
                    if (innerType.getName().equals(CUtils.anyTypeQname))
                        pinfo.setAnyType(true);
    
                    minfo.addOutputParameter(pinfo);
                }
            }
        }
        else
        { 
            String elementName = (String) element.getQName().getLocalPart();
            ParameterInfo pinfo = new ParameterInfo();
            pinfo.setType(type);
            type.setIsUnwrappedOutputType(true);
            pinfo.setParamName(elementName, c_typeMap);
            
            if (!names.hasNext() && type.isSimpleType())
                pinfo.setElementName(element.getQName());
            else
                pinfo.setElementName(type.getName());
            
            if (type.getName().equals(CUtils.anyTypeQname))
                pinfo.setAnyType(true);
            
            // Let us be nice and uppercase the first character in type name, 
            // in addition to resolving method name/type conflicts.
            type.setLanguageSpecificName(generateNewTypeName(type, minfo));
            
            minfo.addOutputParameter(pinfo);
        }
    }

    /**
     * @param op
     * @param minfo
     * @throws WrapperFault
     */
    private void addRPCStyleInputMessageToMethodInfo(Operation op, MethodInfo minfo)
        throws WrapperFault
    {
        ParameterInfo pinfo;
        Iterator paramlist;

        minfo.setInputMessage(op.getInput().getMessage().getQName());
        if (op.getParameterOrdering() != null)
        {
            for (int ix = 0; ix < op.getParameterOrdering().size(); ix++)
            {
                Part p = (Part) (op.getInput()
                                   .getMessage()
                                   .getParts()
                                   .get((String) op.getParameterOrdering().get(ix)));
                if (p == null)
                    continue;

                pinfo = createParameterInfo(p);
                if (null != pinfo)
                    minfo.addInputParameter(pinfo);
            }
        }
        else
        {
            paramlist = op.getInput().getMessage().getParts().values().iterator();
            while (paramlist.hasNext())
            { 
                //RPC style messages can have multiple parts
                Part p = (Part) paramlist.next();
                pinfo = createParameterInfo(p);
                if (null != pinfo)
                    minfo.addInputParameter(pinfo);
            }
        }
    }

    /**
     * @param op
     * @param minfo
     * @throws WrapperFault
     */
    private void addDocumentStyleInputMessageToMethodInfo(Operation op, MethodInfo minfo)
        throws WrapperFault
    {   
        // If no input parameters, simply return.
        Iterator paramlist = op.getInput().getMessage().getParts().values().iterator();
        if(!paramlist.hasNext())
            return;
        
        Part part = (Part) paramlist.next();
        
        QName minfoqname;
        QName qname;
        
        Element element = c_symbolTable.getElement(part.getElementName());
        
        if (element == null)
        {
            // the part reference a type.
            qname = c_symbolTable.getType(part.getTypeName()).getQName();
            minfoqname = c_symbolTable.getType(part.getTypeName()).getQName();
        }
        else
        {
            qname = element.getRefType().getQName();
            minfoqname = element.getQName();
        }
        
        minfo.setInputMessage(minfoqname);

        if (qname == null)
            return;
        
        Type type = c_typeMap.getType(qname);
        if (type == null)
            throw new WrapperFault("unregistered type " + qname + " referenced");

        // For wrapped style, inner attributes and elements are added as parameters.
        // For unwrapped style, objects are used for the parameters (i.e. classes or structures).
        if (!minfo.isUnwrapped())
        {
            // Add input elements to method info
            Iterator elementNames = type.getElementnames();
            while (elementNames.hasNext())
            {
                String elementname = (String) elementNames.next();
                CElementDecl eleinfo = type.getElementForElementName(elementname);
                Type innerType = eleinfo.getType();
                
                ParameterInfo pinfo = new ParameterInfo();
                pinfo.setType(innerType);
                pinfo.setParamName(elementname, c_typeMap);            
                
                if (eleinfo.getMaxOccurs() > 1)
                    pinfo.setArray(true);

                pinfo.setElementName(type.getElementForElementName(elementname).getName());
                
                if (innerType.getName().equals(CUtils.anyTypeQname))
                    pinfo.setAnyType(true);
                
                pinfo.setNillable(eleinfo.isNillable());
                
                if (eleinfo.getMinOccurs() == 0)
                    pinfo.setOptional(true);
                else
                    pinfo.setOptional(false);

                minfo.addInputParameter(pinfo);
            }
            
            // add input attributes to method info
            Iterator attributes = type.getAttributes();
            if (attributes != null)
            {
                while (attributes.hasNext())
                {
                    CContainedAttribute attr = (CContainedAttribute)attributes.next();
    
                    ParameterInfo pinfo = new ParameterInfo();
    
                    pinfo.setType(attr.getType());
                    pinfo.setParamName(attr.getName(), c_typeMap);
                    pinfo.setElementName(attr.getType().getName());
                    pinfo.setAttribute(true);
                    
                    minfo.addInputParameter(pinfo);
                }
            }
        }
        else
        { 
            String elementName;
            
            if (element != null)
                elementName = element.getQName().getLocalPart();
            else
                elementName = type.getName().getLocalPart();
            
            ParameterInfo pinfo = new ParameterInfo();
            
            pinfo.setType(type);
            type.setIsUnwrappedInputType(true);
            pinfo.setParamName(elementName, c_typeMap);
            pinfo.setElementName(type.getName());
            if (type.getName().equals(CUtils.anyTypeQname))
                pinfo.setAnyType(true);

            // Let us be nice and uppercase the first character in type name, 
            // in addition to resolving method name/type conflicts.
            type.setLanguageSpecificName(generateNewTypeName(type, minfo));
            
            minfo.addInputParameter(pinfo);
        }
    }


    /**
     * Iterates through symbol table, creating types in the typemap.
     * 
     * @param typename
     * @return
     * @throws WrapperFault
     */
    private Type createTypeInfo(QName typename)  throws WrapperFault
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
        return createTypeInfo(type);
    }
    
    /**
     * Creates a type map entry from a symbol table typeentry. 
     * 
     * @param type
     * @return
     * @throws WrapperFault
     */
    private Type createTypeInfo(TypeEntry type) throws WrapperFault
    {
        Type typedata = null;
        Type newSecondaryType = null;
        
        // Do not add types which are not used in the WSDL
        if (!type.isReferenced())
            return null;
        
        if (c_verbose && !CUtils.isPrimitiveBasicType(type.getQName()))
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
                
                return createTypeInfo(type.getRefType());
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
            
            if (CUtils.isBasicType(qn))
                return null;
            
            QName newqn = new QName(type.getQName().getNamespaceURI(), qn.getLocalPart() + "_Array");
            // type is a inbuilt type or a already created type?
            typedata = c_typeMap.getType(newqn);
            if (typedata != null)
            {
                if (c_verbose && !CUtils.isPrimitiveBasicType(type.getQName()))
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
            typedata = c_typeMap.getType(type.getQName());
            if (typedata != null)
            {
                if (c_verbose && !CUtils.isPrimitiveBasicType(type.getQName()))
                    System.out.println("Type not created, already exists: " + type.getQName());
                
                return typedata;
            }
            
            typedata = new Type(type.getQName(), type.getQName().getLocalPart());
        }
        
        // Add type to type map
        if (c_verbose)
            System.out.println("Created new type: " + typedata.getName());
        
        c_typeMap.addType(typedata.getName(), typedata);
        
        // work out whether this type will be generated or not 
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
                newSecondaryType = createTypeInfo(base.getQName());
                typedata.addRelatedType(newSecondaryType);
                typedata.setExtensionBaseType(new CElementDecl(newSecondaryType, typeName));
                if (c_verbose)
                    System.out.print(
                        "=====complexType with simpleContent is found : "
                            + type.getQName().getLocalPart() + "=====\n");
            }
            else
                c_wsdlInfo.setRestrictionBaseAndValues(typedata, node);
            
            // There can be attributes in this extended basic type
            Vector attributes = CSchemaUtils.getContainedAttributeTypes(type.getNode(), c_symbolTable);
            if (attributes != null)
            {
                for (int j = 0; j < attributes.size(); j++)
                {
                    CContainedAttribute attr = (CContainedAttribute)attributes.get(j);
                    newSecondaryType = createTypeInfo(attr.getTypeEntry().getQName());
                    attr.setType(newSecondaryType);
                    typedata.addRelatedType(newSecondaryType);
                }
                typedata.addAttributes(attributes);
            }
        }
        else if (type instanceof CollectionType)
        {
            newSecondaryType = createTypeInfo(type.getRefType().getQName());
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
                newSecondaryType = createTypeInfo(arrayType);
                typedata.addRelatedType(newSecondaryType);
                typedata.setTypeNameForElementName(new CElementDecl(newSecondaryType, new QName("item")));
                typedata.setArray(true);
            }
            else if ((arrayType = CSchemaUtils.getCollectionComponentQName(node)) != null)
            {
                newSecondaryType = createTypeInfo(arrayType);
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
                            newSecondaryType = createTypeInfo(attr.getTypeEntry().getQName());
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
                                    
                                    if (CUtils.isBasicType(typeName))
                                        newSecondaryType = createTypeInfo(typeName);
                                    else
                                        newSecondaryType = createTypeInfo(elem.getTypeEntry());
                                }
                                else
                                    newSecondaryType = createTypeInfo(typeName);
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
     * Adds faults.
     * 
     * @param faults
     * @param methodinfo
     * @throws WrapperFault
     */
    private void addFaultInfo(Map faults, MethodInfo methodinfo)
        throws WrapperFault
    {
        if (faults == null)
            return;
        
        Iterator faultIt = faults.values().iterator();
        while (faultIt.hasNext())
        {
            Fault fault = (Fault) faultIt.next();
            FaultInfo faultinfo = new FaultInfo(fault.getName());

            Map parts = fault.getMessage().getParts();
            Iterator partIt = parts.values().iterator();
            while (partIt.hasNext())
            {
                ParameterInfo pinfo = createParameterInfo((Part) partIt.next());
                pinfo.getType().setAsFault(true);
                faultinfo.addParam(pinfo);
            }
            
            methodinfo.addFaultType(faultinfo);
        }
    }

    /**
     * 
     * @param part
     * @return
     * @throws WrapperFault
     */
    private ParameterInfo createParameterInfo(Part part) throws WrapperFault
    {
        QName qname = part.getTypeName();
        if (qname == null)
        {
            Element element = c_symbolTable.getElement(part.getElementName());
            qname = element.getRefType().getQName();
        }

        Type type = c_typeMap.getType(qname);
        if (type == null)
            throw new WrapperFault("unregistered type " + qname + " referred");
        
        ParameterInfo pinfo = new ParameterInfo();
        pinfo.setType(type);
        pinfo.setParamName(part.getName(), c_typeMap);
        pinfo.setElementName(part.getElementName());
        return pinfo;
    }
    
    // The following 3 exposeXXX methods attempts to expose anonymous types so that 
    // the types are externalized to the user.  
    
    /**
     * This method goes through the types and for any types that are referenced works out whether
     * they need to be exposed as a seperate class.
     * If they do require to be a seperate class then the name of the type will be changed from 
     * ">nameoftype" to "nameoftype". This will then get picked up later on in the process and the
     * type will be exposed as a seperate class. 
     * 
     * @param wsContext the webservice context.
     */
    private void exposeReferenceTypes(WebServiceContext wsContext)
    {
        // get the main types
        Collection types = c_symbolTable.getTypeIndex().values();
        Iterator typeIterator = types.iterator();   
        while(typeIterator.hasNext())
        {
            Object highLevelType = typeIterator.next();
            if(!(highLevelType instanceof BaseType))
            {
                DefinedType type = (DefinedType)highLevelType;
                
                if(!type.getQName().getLocalPart().toString().startsWith(">"))
                {
                    // It's not an "inner" type so look for the refs (this might not be valid 
                    // logic and refs might be acceptable for these types too !)
                    HashSet nestedTypes = type.getNestedTypes(c_symbolTable, true);
                    Iterator nestTypeIter = nestedTypes.iterator();
                    while(nestTypeIter.hasNext())
                    {
                        Object nestedType =nestTypeIter.next();
                        if(!(nestedType instanceof BaseType))
                        {
                            TypeEntry defType = (TypeEntry)nestedType;

                            TypeEntry referencedType =defType.getRefType(); 
                            if (referencedType==null)
                                continue;
                            
                            if(c_verbose)
                                System.out.println( "EXPOSE1: Checking whether to expose ref-types for "+defType.getQName().getLocalPart());

                            // If ref type is anonymous and thus currently not exposed because 
                            // it's an "inner" type, expose it and any nested types (latter is TODO).                            
                            
                            if(referencedType.getQName().getLocalPart().startsWith(">") 
                                    && referencedType.getQName().getLocalPart().lastIndexOf(">") == 0)
                            {
                                if(c_verbose)
                                    System.out.println( "EXPOSE1: Exposing ref-type "+referencedType.getQName());

                                Type innerClassType = wsContext.getTypemap().getType(referencedType.getQName());
                                
                                String newLocalPart =  new QName(defType.getQName().getLocalPart()).toString();
                                innerClassType.externalize(new QName(innerClassType.getName().getNamespaceURI(), newLocalPart));
                            }
                        }
                    }
                }
                
            }
        }
    }
    
    /**
     * This method attempts to find anonymous types in the parameter list of 
     * web-service methods to determine if the type should be exposed.
     * @param wsContext
     */
    private void exposeMessagePartsThatAreAnonymousTypes(WebServiceContext wsContext)
    {
        // get the main types
        Collection types = c_symbolTable.getTypeIndex().values();
        Iterator typeIterator = types.iterator();   
        while(typeIterator.hasNext())
        {
            Object highLevelType = typeIterator.next();
            if(!(highLevelType instanceof BaseType))
            {
                DefinedType type = (DefinedType)highLevelType;
                if(type.getQName().getLocalPart().toString().startsWith(">"))
                {
                    if(c_verbose)
                        System.out.println( "EXPOSE2: Checking whether to expose anon type "+type.getQName().getLocalPart());
                    
                    // this is an "inner" type that will not be exposed
                    // however, it needs to be if it is referenced in a message part.
                    // check all the messages
                    ArrayList methods = wsContext.getServiceInfo().getMethods();
                    for(int i=0; i<methods.size(); i++)
                    {
                          MethodInfo method = (MethodInfo)methods.get(i);
                          
                          // Check for faults that need to be externalized
                          Collection faultTypes = method.getFaultType();
                          Iterator faultIterator = faultTypes.iterator();
                          while(faultIterator.hasNext())
                          {
                              FaultInfo faultType = (FaultInfo)faultIterator.next();
                              Collection parameterTypes = faultType.getParams();
                              Iterator paramIterator = parameterTypes.iterator();
                              while(paramIterator.hasNext())
                              {
                                  ParameterInfo parameterInfo =(ParameterInfo)paramIterator.next();
                                  Type parameterType = parameterInfo.getType();

                                  if(c_verbose)
                                      System.out.println( "EXPOSE2: Exposing fault type "+parameterType.getName());
                                  externalizeTypeAndUpdateTypeMap(wsContext, parameterType);
                              }                              
                          }

                          // Check input parameters
                          Collection inputParameterTypes = method.getInputParameterTypes();
                          Iterator paramIterator = inputParameterTypes.iterator();
                          while(paramIterator.hasNext())
                          {
                              ParameterInfo parameterInfo =(ParameterInfo)paramIterator.next();
                              Type parameterType = parameterInfo.getType();
                              if(parameterType.getName().equals(type.getQName()))
                              {
                                  if(c_verbose)
                                      System.out.println( "EXPOSE2: Matches input parm, exposing anon type "+parameterType.getName());
                                  externalizeTypeAndUpdateTypeMap(wsContext, parameterType);
                              }
                          }
                          
                          // Check output parameters
                          Collection outputParameterTypes = method.getOutputParameterTypes();
                          paramIterator = outputParameterTypes.iterator();
                          while(paramIterator.hasNext())
                          {
                              ParameterInfo parameterInfo =(ParameterInfo)paramIterator.next();
                              Type parameterType = parameterInfo.getType();
                              if(parameterType.getName().equals(type.getQName()))
                              {
                                  if(c_verbose)
                                      System.out.println( "EXPOSE2: Matches output parm, exposing anon type "+parameterType.getName());                             
                                  externalizeTypeAndUpdateTypeMap(wsContext, parameterType);
                              }
                          }
                    }
                }
            }
        }
    }
    
    /**
     * 
     * @param theOrigMap
     * @param theType
     * @param nameMapper
     */
    private void exposeRelatedTypes(TypeMap theOrigMap, Type theType, Hashtable nameMapper)
    {
        QName oldName = theType.getName();                              
        Type classType =  theOrigMap.getType(oldName);
        if (classType != null && !classType.isExternalized())
        {
            if(c_verbose)
                System.out.println("\nEXPOSE4: Externalizing type " + oldName);
            
            // Externalize the type - if anonymous we have to change to name
            if (classType.isAnonymous())
            {
                QName newName   =  new QName(oldName.getNamespaceURI(), 
                                             classType.getLanguageSpecificName());
    
                classType.externalize(newName);
                
                // add old name to new name mapping to name mapper hash table
                nameMapper.put(oldName, newName);
            }
            else
                classType.externalize(true);

            // Now check to see related types of this type - recursively.
            Iterator relatedTypesIt = theType.getRelatedTypes();
            Type relatedType;
            while (relatedTypesIt.hasNext())
            {
                relatedType = (Type) relatedTypesIt.next();
                if (!relatedType.isExternalized())
                    exposeRelatedTypes(theOrigMap, relatedType, nameMapper);
            }            
        }
    }
    
    /**
     * 
     * @param wsContext
     */
    private void exposeNestedTypesThatAreAnonymousTypes(WebServiceContext wsContext)
    {
        // Go through the externalized types in the typemap and externalize the 
        // related types used by each externalized type. In order to complete the externalization,
        // we need to remove the entry from the typemap and replace it with a new name.  
        // However, this will have to be done after we have iterated through the typemap since
        // updating the typemap as we iterate through it will result in an exception.
        // So we have a hash table to map old names to new names for those types that have been 
        // externalized.
        Hashtable nameMapper = new Hashtable();
        Iterator typesIt = wsContext.getTypemap().getTypes().iterator();
        Type type;
        while (typesIt.hasNext())
        {
            type = (Type) typesIt.next();
            if (type.isExternalized())
            {
                if(c_verbose)
                    System.out.println("\nEXPOSE3: Checking related types for type " + type.getName());
                
                Iterator relatedTypesIt = type.getRelatedTypes();
                Type relatedType;
                while (relatedTypesIt.hasNext())
                {
                    relatedType = (Type) relatedTypesIt.next();
                    if (!relatedType.isExternalized())
                        exposeRelatedTypes(wsContext.getTypemap(), relatedType, nameMapper);
                }
            }              
        }
        
        // Now update the typemap, replacing old names with new names, using the hash table that
        // maps old names to new names.
        QName oldName;
        QName newName;
        
        for (Enumeration e = nameMapper.keys(); e.hasMoreElements() ;)
        {
            oldName = (QName) e.nextElement();
            newName = (QName) nameMapper.get(oldName);
            type    = wsContext.getTypemap().getType(oldName);
            if (type != null)
            {
                wsContext.getTypemap().removeType(oldName);
                wsContext.getTypemap().addType(newName, type);                
            }
        }
    }

    /**
     * 
     * @param wsContext
     * @param parameterType
     */
    private void externalizeTypeAndUpdateTypeMap(WebServiceContext wsContext, Type parameterType)
    {
        QName oldName = parameterType.getName();
        Type innerClassType =  wsContext.getTypemap().getType(oldName);
        if (innerClassType != null && !innerClassType.isExternalized())
        {
            QName newTypeName   =  new QName(parameterType.getName().getNamespaceURI(), 
                                             parameterType.getLanguageSpecificName());

            innerClassType.externalize(newTypeName);
            
            // Update the typemap with new info
            wsContext.getTypemap().removeType(oldName);
            wsContext.getTypemap().addType(newTypeName, innerClassType);
        }
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
    
    /**
     * Resolves name conflict between a method name and a type name. 
     * When doing document-literal, usually the name of the wrapper element is same as the 
     * operation name. 
     * 
     * @param type
     * @param minfo
     * @return the new type name that does not conflict with the operation name.
     */
    private String generateNewTypeName(Type type, MethodInfo minfo)
    {
        String minfo_nm = minfo.getMethodname();
        String type_nm  = type.getLanguageSpecificName();
        
        String newName = CUtils.capitalizeFirstCharacter(type_nm);

        if (!minfo_nm.equals(newName))
            return newName;

        return newName + "_t";
    }
}
