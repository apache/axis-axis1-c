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
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import javax.wsdl.Binding;
import javax.wsdl.Fault;
import javax.wsdl.Operation;
import javax.wsdl.Part;
import javax.wsdl.Port;
import javax.wsdl.PortType;
import javax.xml.namespace.QName;
import javax.xml.rpc.holders.IntHolder;

import org.apache.axis.wsdl.gen.Parser;
import org.apache.axis.wsdl.symbolTable.BaseType;
import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.CElementDecl;
import org.apache.axis.wsdl.symbolTable.CSchemaUtils;
import org.apache.axis.wsdl.symbolTable.CollectionElement;
import org.apache.axis.wsdl.symbolTable.CollectionType;
import org.apache.axis.wsdl.symbolTable.DefinedElement;
import org.apache.axis.wsdl.symbolTable.DefinedType;
import org.apache.axis.wsdl.symbolTable.Element;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.axis.wsdl.symbolTable.SymTabEntry;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.wsdl2ws.info.ElementInfo;
import org.apache.axis.wsdl.wsdl2ws.info.FaultInfo;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ServiceInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.TypeMap;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
import org.apache.axis.wsdl.wsdl2ws.info.WrapperInfo;
import org.w3c.dom.Node;

import sun.security.action.GetLongAction;

/**
 * This this the main class for the WSDL2Ws Tool. This class reuses the code in the 
 * Axis java implementations to parse the WSDL file.
 * the functinality of the class can be discribed as follows 
 * 	1) create a Symbol table
 *  2) create WrapperInfo class parsing the commandline arguments and the SymbolTable
 *  3) create TypeMap parsing the  Symbol Table
 *  4) create Service Info parsing the Symbol table
 *  5) create WebServiceContext using above three classes and start execution 
 * 
 * @author hemapani@opensource.lk
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 * @author hawkeye (hawkinsj@uk.ibm.com)
 */
public class WSDL2Ws
{
    public static boolean verbose = false;
    // we don't write out the make files anymore - 9th Nov 2005
//    public static String makeSystem = null;

    private String language;
    private boolean wsdlWrappingStyle;

    private String qualifiedServiceName;
    private SymbolTable symbolTable;

    private String serviceStyle = null;

    private String targetEndpointURI = null;
    private String transportURI = null;
    private String targetNameSpaceOfWSDL = null;
    private TypeMap typeMap;

    private ServiceEntry serviceentry;
    private BindingEntry bindingEntry;
    private PortTypeEntry portTypeEntry;
    private ArrayList methods;

    public WSDL2Ws(CLArgParser cmdLineArgs) throws WrapperFault
    {
        try
        {
            Parser wsdlParser = new Parser();
            // set timeout
            String timeout = cmdLineArgs.getOptionBykey("t"); 
            if (timeout != null) 
                wsdlParser.setTimeout(Long.parseLong(timeout)); 

            //get the commandline arguments
            String wsdlfile = cmdLineArgs.getArgument(0);
            wsdlParser.run(wsdlfile);

            symbolTable = wsdlParser.getSymbolTable();

            //get the target namespace
            targetNameSpaceOfWSDL =
                symbolTable.getDefinition().getTargetNamespace();
        }
        catch (Exception e)
        {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    /** 
     * this method initailize the serviceEntry portEntry and bindingEntry   
     * @throws WrapperFault
     */

    public void perprocess() throws WrapperFault
    {
        typeMap = new TypeMap(language);
        this.serviceentry = getServiceEntry();
        Iterator ports =
            this.serviceentry.getService().getPorts().values().iterator();

        //TODO  resolve this
        //		this code support only the service with onebindings it will not care about the
        //		second binding if exists.. if the NO binding specified it will failed
        //		this should be resolved by let user specify which binding to use.

        Binding binding = null;
        if (ports.hasNext())
            binding = ((Port) ports.next()).getBinding();
        if (binding == null)
            throw new WrapperFault("No binding specified");
        this.bindingEntry = symbolTable.getBindingEntry(binding.getQName());

        this.portTypeEntry =
            symbolTable.getPortTypeEntry(binding.getPortType().getQName());
        if (portTypeEntry == null)
            throw new WrapperFault("Service not found");
        ports = this.serviceentry.getService().getPorts().values().iterator();
        this.targetEndpointURI =
            SymbolTableParsingUtils.getTargetEndPointURI(ports);
    }

    /**
     * This method exteact the service,binding,encoding information and return a PortType of the
     * webservice to publish.
     * @return port type the webservice based on
     */
    private void getWebServiceInfo() throws WrapperFault
    {
        this.qualifiedServiceName = portTypeEntry.getName();
        if (this.qualifiedServiceName == null)
        {
            qualifiedServiceName = portTypeEntry.getQName().getNamespaceURI();
            qualifiedServiceName =
                WrapperUtils.firstCharacterToLowercase(
                    WrapperUtils.nsURI2packageName(qualifiedServiceName))
                    + "."
                    + portTypeEntry.getQName().getLocalPart();
        }

        //the service style (rpc|doc|msg)
        this.serviceStyle = bindingEntry.getBindingStyle().getName();
        //extract the transport type as a uri
        this.transportURI =
            SymbolTableParsingUtils.getTransportType(bindingEntry.getBinding());
        List operations = bindingEntry.getBinding().getBindingOperations();
        if (operations != null)
        {

            for (int i = 0; i < operations.size(); i++)
            {
                //for the each binding operation found
                if (operations.get(i) instanceof javax.wsdl.BindingOperation)
                {

                    javax.wsdl.BindingOperation bindinop =
                        (javax.wsdl.BindingOperation) operations.get(i);
                    MethodInfo method = getMethodInfoByName(bindinop.getName());
                    method.setSoapAction(
                        SymbolTableParsingUtils.getSoapAction(bindinop));
                    SymbolTableParsingUtils.getInputInfo(
                        bindinop.getBindingInput(),
                        method);
                    SymbolTableParsingUtils.getOutputInfo(
                        bindinop.getBindingOutput(),
                        method);
                }
            }
        }
    }

    /**
     * get Service data .. service data is given as the fully qualified names
     * When possible the user can have the schema QName if he like
     */

    private ArrayList getServiceInfo(PortType porttype) throws WrapperFault
    {
        //get opeation list
        Iterator oplist = porttype.getOperations().iterator();
        ArrayList methods = new ArrayList();

        //for each operation
        while (oplist.hasNext())
        {
            Operation op = (Operation) oplist.next();
            methods.add(setMethodInfo(op)); //add operation to operation List
        }
        return methods;
    }

    /**
     * @param op Operation from which to set MethodInfo
     * @return MethodInfo
     * @throws WrapperFault
     */
    private MethodInfo setMethodInfo(Operation op) throws WrapperFault
    {
        MethodInfo minfo = new MethodInfo(op.getName());

        //setting the faults
        this.addFaultInfo(op.getFaults(), minfo);
        //add each parameter to parameter list
        if ("document".equals(bindingEntry.getBindingStyle().getName()))
        {
            this.addDocumentStyleInputMessageToMethodInfo(op, minfo);
        }
        else
        {
            this.addRPCStyleInputMessageToMethodInfo(op, minfo);
        }
        //get the return type
        if (op.getOutput() != null)
        {
            Iterator returnlist =
                op.getOutput().getMessage().getParts().values().iterator();
            if (returnlist.hasNext()
                && "document".equals(bindingEntry.getBindingStyle().getName()))
            {
                this.addDocumentStyleOutputMessageToMethodInfo(
                    minfo,
                    (Part) returnlist.next());
            }
            else
            {
                this.addRPCStyleOutputMessageToMethodInfo(op, minfo);
            }
        }
        return minfo;
    }

    /**
     * @param op
     * @param minfo MethodInfo object into which output message and it's elements are to be added
     * @throws WrapperFault
     */
    private void addRPCStyleOutputMessageToMethodInfo(
        Operation op,
        MethodInfo minfo)
        throws WrapperFault
    {
        ParameterInfo pinfo;
        Iterator returnlist;

        //added on 1-jun-2004
        minfo.setInputMessage(op.getInput().getMessage().getQName());
        minfo.setOutputMessage(op.getOutput().getMessage().getQName());
        // minfo.setFaultMessage();
        if (op.getParameterOrdering() != null)
        {

            for (int ix = 0; ix < op.getParameterOrdering().size(); ix++)
            {
                Part p =
                    (Part) (op
                        .getOutput()
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
            returnlist =
                op.getOutput().getMessage().getParts().values().iterator();
            while (returnlist.hasNext())
            { //RPC style messages can have multiple parts
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
            returnlist =
                op.getOutput().getMessage().getParts().values().iterator();
            while (returnlist.hasNext())
            { //RPC style messages can have multiple parts
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
    private void addDocumentStyleOutputMessageToMethodInfo(
        MethodInfo minfo,
        Part part)
        throws WrapperFault
    {
        Element element;
        QName qname;
        ParameterInfo pinfo;
        Type type;
        QName minfoqname;
        element = symbolTable.getElement(part.getElementName());
        if (element == null)
        {
            // the part reference a type.
            qname = symbolTable.getType(part.getTypeName()).getQName();
            minfoqname = symbolTable.getType(part.getTypeName()).getQName();
        }
        else
        {
            qname = element.getRefType().getQName();
            minfoqname = element.getQName();
        }
        minfo.setOutputMessage(minfoqname);

        if (qname != null)
        {
            type = this.typeMap.getType(qname);
            //boolean wrapped = true; //TODO take this from a commandline argument
            boolean wrapped = wsdlWrappingStyle;

            if (type == null)
            {
                throw new WrapperFault(
                    "Unregistered type " + qname + " referred");
            }

            if (wrapped)
            {
                //get inner attributes and elements and add them as parameters 
                addOutputElementsToMethodInfo(minfo, type);
            }
            else
            { // for non-wrapped style wsdl's
                // String elementName = (String)type.getName().toString();
                String elementName = (String) element.getQName().getLocalPart();
                symbolTable.dump(System.out);
                pinfo = new ParameterInfo(type, elementName);
                pinfo.setElementName(type.getName());
                if (type.getName().equals(CUtils.anyTypeQname))
                    pinfo.setAnyType(true);
                minfo.addOutputParameter(pinfo);

            }
        }

    }

    /**
     * @param minfo
     * @param type
     */
    private void addOutputElementsToMethodInfo(MethodInfo minfo, Type type)
    {
        ParameterInfo pinfo;
        ElementInfo eleinfo;
        ArrayList elementlist = new ArrayList();
        Iterator names = type.getElementnames();
        while (names.hasNext())
        {
            elementlist.add(names.next());
        }
        Type innerType;
        for (int i = 0; i < elementlist.size(); i++)
        {
            String elementname = (String) elementlist.get(i);
            eleinfo = type.getElementForElementName(elementname);
            innerType = eleinfo.getType();
            pinfo = new ParameterInfo(innerType, elementname);
            if (eleinfo.getMaxOccurs() > 1)
            {
                pinfo.setArray(true);
            }
            pinfo.setNillable(eleinfo.getNillable());
            if (eleinfo.getMinOccurs() == 0)
            {
                pinfo.setOptional(true);
            }
            else
            {
                pinfo.setOptional(false);
            }
            pinfo.setElementName(
                type.getElementForElementName(elementname).getName());
            if (innerType.getName().equals(CUtils.anyTypeQname))
            {
                pinfo.setAnyType(true);
            }
            minfo.addOutputParameter(pinfo);
        }
    }

    /**
     * @param op
     * @param minfo
     * @throws WrapperFault
     */
    private void addRPCStyleInputMessageToMethodInfo(
        Operation op,
        MethodInfo minfo)
        throws WrapperFault
    {
        ParameterInfo pinfo;
        Iterator paramlist;

        minfo.setInputMessage(op.getInput().getMessage().getQName());
        if (op.getParameterOrdering() != null)
        {
            for (int ix = 0; ix < op.getParameterOrdering().size(); ix++)
            {
                Part p =
                    (Part) (op
                        .getInput()
                        .getMessage()
                        .getParts()
                        .get((String) op.getParameterOrdering().get(ix)));
                if (p == null)
                {
                    continue;
                }
                pinfo = createParameterInfo(p);
                if (null != pinfo)
                {
                    minfo.addInputParameter(pinfo);
                }
            }
        }
        else
        {
            paramlist =
                op.getInput().getMessage().getParts().values().iterator();
            while (paramlist.hasNext())
            { //RPC style messages can have multiple parts
                Part p = (Part) paramlist.next();
                pinfo = createParameterInfo(p);
                if (null != pinfo)
                {
                    minfo.addInputParameter(pinfo);
                }
            }
        }

    }

    /**
     * @param op
     * @param minfo
     * @throws WrapperFault
     */
    private void addDocumentStyleInputMessageToMethodInfo(
        Operation op,
        MethodInfo minfo)
        throws WrapperFault
    {
        Element element;
        QName qname;
        ParameterInfo pinfo;
        Type type;
        Iterator paramlist;

        paramlist = op.getInput().getMessage().getParts().values().iterator();
        Part part = (Part) paramlist.next();
        QName minfoqname;
        element = symbolTable.getElement(part.getElementName());
        if (element == null)
        {
            // the part reference a type.
            qname = symbolTable.getType(part.getTypeName()).getQName();
            minfoqname = symbolTable.getType(part.getTypeName()).getQName();
        }
        else
        {
            qname = element.getRefType().getQName();
            minfoqname = element.getQName();
        }
        minfo.setInputMessage(minfoqname);

        if (qname != null)
        {
            type = this.typeMap.getType(qname);
            boolean wrapped = wsdlWrappingStyle;

            if (type == null)
            {
                throw new WrapperFault(
                    "unregistered type " + qname + " referred");
            }

            if (wrapped)
            {
                //get inner attributes and elements and add them as parameters
                addInputElementsToMethodInfo(minfo, type);
                addInputAttributesToMethodInfo(minfo, type);
            }
            else
            { // for non-wrapped style wsdl's
                String elementName = (String) element.getQName().getLocalPart();
                pinfo = new ParameterInfo(type, elementName);
                pinfo.setElementName(type.getName());
                if (type.getName().equals(CUtils.anyTypeQname))
                {
                    pinfo.setAnyType(true);
                }
                minfo.addInputParameter(pinfo);
            }
        }

    }

    /**
     * @param minfo
     * @param type
     */
    private void addInputAttributesToMethodInfo(MethodInfo minfo, Type type)
    {
        ParameterInfo pinfo;
        ArrayList attributeList = new ArrayList();
        Iterator attributeNames = type.getAttributeNames();
        while (attributeNames.hasNext())
        {
            attributeList.add(attributeNames.next());
        }

        for (int i = 0; i < attributeList.size(); i++)
        {
            String attributeName = (String) attributeList.get(i);
            Type innerType = type.getTypForAttribName(attributeName);
            pinfo = new ParameterInfo(innerType, attributeName);
            pinfo.setElementName(
                type.getTypForAttribName(attributeName).getName());
            pinfo.setAttribute(true);
            minfo.addInputParameter(pinfo);
        }
    }

    /**
     * @param minfo
     * @param type
     */
    private void addInputElementsToMethodInfo(MethodInfo minfo, Type type)
    {
        ParameterInfo pinfo;
        ElementInfo eleinfo;
        Iterator elementNames = type.getElementnames();
        ArrayList elementlist = new ArrayList();
        while (elementNames.hasNext())
        {
            elementlist.add(elementNames.next());
        }

        for (int i = 0; i < elementlist.size(); i++)
        {
            String elementname = (String) elementlist.get(i);
            eleinfo = type.getElementForElementName(elementname);
            Type innerType = eleinfo.getType();
            pinfo = new ParameterInfo(innerType, elementname);
            if (eleinfo.getMaxOccurs() > 1)
            {
                pinfo.setArray(true);
            }
            pinfo.setElementName(
                type.getElementForElementName(elementname).getName());
            if (innerType.getName().equals(CUtils.anyTypeQname))
                pinfo.setAnyType(true);
            pinfo.setNillable(eleinfo.getNillable());
            if (eleinfo.getMinOccurs() == 0)
            {
                pinfo.setOptional(true);
            }
            else
            {
                pinfo.setOptional(false);
            }
            minfo.addInputParameter(pinfo);
        }
    }

    /**
     * This method extract the custom complex type info fom the symbol table
     * @return the type map with type info
     */
    private TypeMap getTypeInfo(String targetLanguage) throws WrapperFault
    {
        Iterator it = symbolTable.getTypeIndex().values().iterator();
        TypeEntry type;

        while (it.hasNext())
        {
            type = (TypeEntry) it.next();
            Node node = type.getNode();
            if (node != null)
            {
                createTypeInfo(type, targetLanguage);

            }
        } //end of type while
        return typeMap;
    } //end of method

    public void generateWrappers(
        String servicename,
        String targetoutputLocation,
        String targetLanguage,
        String targetEngine,
        String wsdlWrapStyle)
        throws WrapperFault
    {

        if (targetLanguage == null)
            targetLanguage = "c++";
        if (targetEngine == null)
            targetEngine = "server";
        if (targetoutputLocation == null)
            targetoutputLocation = "./";
        if (wsdlWrapStyle == null)
            wsdlWrapStyle = "wrapped";

        this.language = targetLanguage;

        if (wsdlWrapStyle.equalsIgnoreCase("wrapped"))
        {
            this.wsdlWrappingStyle = true;
        }
        else
        {
            this.wsdlWrappingStyle = false;
        }

        perprocess();

        CUtils.setLanguage(language);
        QName serviceqname = serviceentry.getService().getQName();
        servicename = serviceqname.getLocalPart();
        typeMap = this.getTypeInfo(targetLanguage);
        methods = this.getServiceInfo(this.portTypeEntry.getPortType());
        this.getWebServiceInfo();

        //TODO	check whether the name at the WrapperConstant Doclit is right "doc"
        WebServiceContext wsContext =new WebServiceContext(
                new WrapperInfo(
                        serviceStyle,
                        targetLanguage,
                        targetoutputLocation,
                        targetEngine,
                        transportURI,
                        targetEndpointURI,
                        targetNameSpaceOfWSDL),
                    new ServiceInfo(servicename, qualifiedServiceName, methods),
                    typeMap);  
        WebServiceGenerator wsg =
            WebServiceGeneratorFactory.createWebServiceGenerator(wsContext);
        
        if (wsg == null)
            throw new WrapperFault("WSDL2Ws does not support the option combination");
        exposeReferenceTypes(wsContext);
        exposeMessagePartsThatAreAnonymousTypes(wsContext);
        exposeNestedTypesThatAreAnonymousTypes(wsContext);
        
        if (WSDL2Ws.verbose)
        {
            Iterator it = typeMap.getTypes().iterator();
            while (it.hasNext())
            {
                System.out.println(it.next());
            }
        }
        wsg.generate();
    }

    
    /**
     * @param wsContext
     */
    private void exposeMessagePartsThatAreAnonymousTypes(WebServiceContext wsContext)
    {
        // get the main types
        Collection types = symbolTable.getTypeIndex().values();
        Iterator typeIterator = types.iterator();   
        while(typeIterator.hasNext())
        {
            Object highLevelType = typeIterator.next();
            if(!(highLevelType instanceof BaseType))
            {
                DefinedType type = (DefinedType)highLevelType;
                if(type.getQName().getLocalPart().toString().startsWith(">")&& !(type.getQName().getLocalPart().toString().lastIndexOf(">")>1))
                {
                    // this is an "inner" type that will not be exposed
                    // however, it needs to be if it is referenced in a message part.
                    // check all the messages
                  ArrayList methods = wsContext.getSerInfo().getMethods();
                  for(int i=0; i<methods.size(); i++)
                  {
                      MethodInfo method = (MethodInfo)methods.get(i);
                      Collection inputParameterTypes = method.getInputParameterTypes();
                      Iterator paramIterator = inputParameterTypes.iterator();
                      while(paramIterator.hasNext())
                      {
                          ParameterInfo parameterInfo =(ParameterInfo)paramIterator.next();
                          Type parameterType = parameterInfo.getType();
                          if(parameterType.getName().equals(type.getQName()))
                          {
                              QName oldName = parameterType.getName();
                              QName newTypeName = new QName(parameterType.getName().getNamespaceURI(), parameterType.getName().getLocalPart().substring(1));
                              
                              Type innerClassType =  wsContext.getTypemap().getType(parameterType.getName());
                              // innerClassType.setLanguageSpecificName(newTypeName);
                              
                              // First thing to do is to expose the type so it gets created.
                              innerClassType.setLanguageSpecificName(newTypeName.getLocalPart().toString());
                              
                              // also have to set the QName becuase this is used in generating the header info.
                              innerClassType.setName(newTypeName);
                              
                              // The typemap we get back is a copy of the actual typemap so we have to set the new value explicitly
                              // firstly remove the old version
                              wsContext.getTypemap().removeType(oldName);
                              wsContext.getTypemap().addType(newTypeName, innerClassType);
                              
                              Iterator AllTypes = symbolTable.getTypeIndex().values().iterator();
                          }
                      }
                  }
                    
                }
            }
        }
 
                    
//                    ArrayList methods = wsContext.getSerInfo().getMethods();
//        for(int i=0; i<methods.size(); i++)
//        {
//            MethodInfo method = (MethodInfo)methods.get(i);
//            Collection inputParameterTypes = method.getInputParameterTypes();
//            Iterator paramIterator = inputParameterTypes.iterator();
//            while(paramIterator.hasNext())
//            {
//                ParameterInfo parameterInfo =(ParameterInfo)paramIterator.next();
//                Type parameterType = parameterInfo.getType();
//                if(parameterType.getLanguageSpecificName().startsWith(">"))
//                {
//                    // Then this type has not been exposed as a seperate class and it needs to be
//                    System.out.println( "got to expose "+parameterType.getName().getLocalPart());
//                    QName exposedName = new QName(parameterType.getName().getNamespaceURI(), parameterType.getName().getLocalPart().substring(1));
//                    // There'#s no point in doing this unless the type map is changed
//                    Type type = wsContext.getTypemap().getType(parameterType.getName());
//                    type.setName(exposedName);
//                    wsContext.getTypemap().removeType(parameterType.getName());
//                    wsContext.getTypemap().addType(exposedName, type);
//                    //parameterType.setLanguageSpecificName(new QName(parameterType.getLanguageSpecificName().substring(1)).toString() );
//                    
//                    // also have to set the QName becuase this is used in generating the header info.
//                    //parameterType.setName(new QName(parameterType.getName().getNamespaceURI(), parameterType.getLanguageSpecificName()));
//                    
//                    
//                }
        
    }

    /**
         * @param wsContext
         */
        private void exposeNestedTypesThatAreAnonymousTypes(WebServiceContext wsContext)
        {
            // get the main types
            Collection types = symbolTable.getTypeIndex().values();
            Iterator typeIterator = types.iterator();   
            while(typeIterator.hasNext())
            {
                Object highLevelType = typeIterator.next();
                if(!(highLevelType instanceof BaseType))
                {
                    DefinedType type = (DefinedType)highLevelType;
                    if(!type.getQName().getLocalPart().toString().startsWith(">"))
                    {
//                        System.out.println( "HERE "+type.getQName().getLocalPart());
                        HashSet nestedTypes = type.getNestedTypes(symbolTable, true);
                        Iterator iterator = nestedTypes.iterator();
                        while(iterator.hasNext())
                        {
                            Object nestedObjectType = iterator.next();
                            if(nestedObjectType instanceof DefinedType)
                            {
                                //System.out.println( "nestedname"+nestedObjectType);
                                DefinedType nestedType =(DefinedType) nestedObjectType; 
                                // If the nested parts are complex inner/anonymous types then they need to be exposed as seperate classes
                                String name =nestedType.getQName().getLocalPart().toString(); 
                               // System.out.println( "iterator next = "+name);
                                if(name.startsWith(">") && name.lastIndexOf(">")>0)
                                {
                                  // then this type needs to be exposed !
                                  QName oldName = nestedType.getQName();
//                                  System.out.println( "Exposing nestedType "+oldName);
//                                  System.out.println( "nestobjecttype = "+nestedObjectType.getClass());
//                                  QName newTypeName = new QName(oldName.getNamespaceURI(), oldName.getLocalPart().substring(1));
                                  QName newTypeName =new QName(oldName.getNamespaceURI(), CUtils.sanitiseClassName(oldName.getLocalPart().toString()));
                                  
                                  Type innerClassType =  wsContext.getTypemap().getType(oldName);
                                  if(innerClassType!=null)
                                  {
                                      // 	First thing to do is to expose the type so it gets created.
                                      innerClassType.setLanguageSpecificName(newTypeName.getLocalPart().toString());
                                  
                                      // 	also have to set the QName because this is used in generating the header info.
                                      innerClassType.setName(newTypeName);
                                      // 	The typemap we get back is a copy of the actual typemap so we have to set the new value explicitly
                                      // firstly remove the old version
                                      wsContext.getTypemap().removeType(oldName);
                                      wsContext.getTypemap().addType(newTypeName, innerClassType);
                                  }
                                  
                                  // Iterator AllTypes = symbolTable.getTypeIndex().values().iterator();
                                }
                            }
                        }
                    }
                }
            }
        }

                            
                            
//                        }
//                    }
//                    if(type.getQName().getLocalPart().toString().startsWith(">")&& !(type.getQName().getLocalPart().toString().lastIndexOf(">")>1))
//                    {
//                        // this is an "inner" type that will not be exposed
//                        // however, it needs to be if it is referenced in a message part.
//                        // check all the messages
//                      ArrayList methods = wsContext.getSerInfo().getMethods();
//                      for(int i=0; i<methods.size(); i++)
//                      {
//                          MethodInfo method = (MethodInfo)methods.get(i);
//                          Collection inputParameterTypes = method.getInputParameterTypes();
//                          Iterator paramIterator = inputParameterTypes.iterator();
//                          while(paramIterator.hasNext())
//                          {
//                              ParameterInfo parameterInfo =(ParameterInfo)paramIterator.next();
//                              Type parameterType = parameterInfo.getType();
//                              if(parameterType.getName().equals(type.getQName()))
//                              {
//                                  QName oldName = parameterType.getName();
//                                  QName newTypeName = new QName(parameterType.getName().getNamespaceURI(), parameterType.getName().getLocalPart().substring(1));
//                                  
//                                  Type innerClassType =  wsContext.getTypemap().getType(parameterType.getName());
//                                  // innerClassType.setLanguageSpecificName(newTypeName);
//                                  
//                                  // First thing to do is to expose the type so it gets created.
//                                  innerClassType.setLanguageSpecificName(newTypeName.getLocalPart().toString());
//                                  
//                                  // also have to set the QName becuase this is used in generating the header info.
//                                  innerClassType.setName(newTypeName);
//                                  
//                                  // The typemap we get back is a copy of the actual typemap so we have to set the new value explicitly
//                                  // firstly remove the old version
//                                  wsContext.getTypemap().removeType(oldName);
//                                  wsContext.getTypemap().addType(newTypeName, innerClassType);
//                                  
//                                  Iterator AllTypes = symbolTable.getTypeIndex().values().iterator();
//                              }
//                          }
//                      }
//                        
//                    }
//                }
//            }
     
                        
    //                    ArrayList methods = wsContext.getSerInfo().getMethods();
    //        for(int i=0; i<methods.size(); i++)
    //        {
    //            MethodInfo method = (MethodInfo)methods.get(i);
    //            Collection inputParameterTypes = method.getInputParameterTypes();
    //            Iterator paramIterator = inputParameterTypes.iterator();
    //            while(paramIterator.hasNext())
    //            {
    //                ParameterInfo parameterInfo =(ParameterInfo)paramIterator.next();
    //                Type parameterType = parameterInfo.getType();
    //                if(parameterType.getLanguageSpecificName().startsWith(">"))
    //                {
    //                    // Then this type has not been exposed as a seperate class and it needs to be
    //                    System.out.println( "got to expose "+parameterType.getName().getLocalPart());
    //                    QName exposedName = new QName(parameterType.getName().getNamespaceURI(), parameterType.getName().getLocalPart().substring(1));
    //                    // There'#s no point in doing this unless the type map is changed
    //                    Type type = wsContext.getTypemap().getType(parameterType.getName());
    //                    type.setName(exposedName);
    //                    wsContext.getTypemap().removeType(parameterType.getName());
    //                    wsContext.getTypemap().addType(exposedName, type);
    //                    //parameterType.setLanguageSpecificName(new QName(parameterType.getLanguageSpecificName().substring(1)).toString() );
    //                    
    //                    // also have to set the QName becuase this is used in generating the header info.
    //                    //parameterType.setName(new QName(parameterType.getName().getNamespaceURI(), parameterType.getLanguageSpecificName()));
    //                    
    //                    
    //                }
            
//        }

    /**
     * This code is taken from the org.apache.axis.wsdl.gen.Parser Class.
     * WSDL file should have only one service, The first service 
     * find is utilized.
     * @return
     * @throws WrapperFault
     */
    public ServiceEntry getServiceEntry() throws WrapperFault
    {
        Iterator it = symbolTable.getHashMap().values().iterator();
        while (it.hasNext())
        {
            Vector v = (Vector) it.next();
            for (int i = 0; i < v.size(); ++i)
            {
                SymTabEntry entry = (SymTabEntry) v.elementAt(i);

                if (entry instanceof ServiceEntry)
                {
                    return (ServiceEntry) entry;
                }
            }
        }
        throw new WrapperFault("the service does not exists");
    }

    public Type createTypeInfo(QName typename, String targetLanguage)
        throws WrapperFault
    {
        TypeEntry type = symbolTable.getType(typename);
        if (type == null)
        {
            type = symbolTable.getElement(typename);
            if (type == null)
            {
                throw new WrapperFault(
                    "["
                        + typename
                        + "]unexpected condition occurred "
                        + ".. please inform the axis-dev@apache.org mailing list ASAP");
            }
            type.getRefType();
        }
        return createTypeInfo(type, targetLanguage);
    }

    /**
     * This code is borrowd from the JavaBeanWriter#writeFullConstructor().
     * @param type
     * @param targetLanguage
     * @return
     */

    public Type createTypeInfo(TypeEntry type, String targetLanguage)
        throws WrapperFault
    {
        if (!type.isReferenced())
            return null; //do not add types which are not used in the wsdl
        if (type instanceof CollectionElement)
        { //an array
        }
        else
            if (type instanceof DefinedElement)
            { //skip any wrapping elements where ref=....
                if (type.getRefType() != null)
                {
                    return createTypeInfo(type.getRefType(), targetLanguage);
                }
                return null;
            }
        Type typedata = typeMap.getType(type.getQName());
        if (typedata != null)
        {
            //type is a inbild type or a already created type
            return typedata;
        }

        if (-1 != type.getQName().getLocalPart().indexOf('['))
        { /* it seems that this is an array */
            if (null == type.getRefType())
                throw new WrapperFault("Array type found without a Ref type");
            QName qn = type.getRefType().getQName();
            if (null == qn)
                throw new WrapperFault("Array type found without a Ref type");
            if (CUtils.isBasicType(qn))
                return null;
            
            QName newqn =
                new QName(
                    type.getQName().getNamespaceURI(),
                    qn.getLocalPart() + "_Array");
            typedata =
                new Type(newqn, newqn.getLocalPart(), true, targetLanguage);
            
            if (type.getRefType().getRefType() != null)
                typedata.setElementType(
                    type.getRefType().getRefType().getQName().getLocalPart());
            else
                typedata.setElementType(
                    type.getRefType().getQName().getLocalPart());
            
            

            typeMap.addType(newqn, typedata);
        }
        else
        {
            typedata =
                new Type(
                    type.getQName(),
                    type.getQName().getLocalPart(),
                    true,
                    targetLanguage);
            typeMap.addType(type.getQName(), typedata);
        }
        
        // work out whether this type will be generated or not 
        typedata.setGenerated(isTypeGenerated(type));

        Node node = type.getNode();

        Vector restrictdata = null;
        if (type.isSimpleType())
        {
            //check for extended types
            TypeEntry base =
                CSchemaUtils.getComplexElementExtensionBase(
                    type.getNode(),
                    symbolTable);
            if (base != null)
            {
                String localpart = type.getQName().getLocalPart() + "_value";
                QName typeName =
                    new QName(type.getQName().getNamespaceURI(), localpart);
                ElementInfo eleinfo =
                    new ElementInfo(
                        typeName,
                        createTypeInfo(base.getQName(), targetLanguage));
                typedata.setExtensionBaseType(eleinfo);
                if (WSDL2Ws.verbose)
                    System.out.print(
                        "=====complexType with simpleContent is found : "
                            + type.getQName().getLocalPart()
                            + "=====\n");
            }
            else
            {
                //types declared as simpleType
                restrictdata =
                    CUtils.getRestrictionBaseAndValues(node, symbolTable);
                if (restrictdata != null)
                    typedata.setRestrictiondata(restrictdata);
            }
            // There can be attributes in this extended basic type
            // Process the attributes
            Vector attributes =
                CSchemaUtils.getContainedAttributeTypes(
                    type.getNode(),
                    symbolTable);
            if (attributes != null)
            {
                for (int j = 0; j < attributes.size(); j += 2)
                {
                    typedata.setTypeForAttributeName(
                        ((QName) attributes.get(j + 1)).getLocalPart(),
                        createTypeInfo(
                            ((TypeEntry) attributes.get(j)).getQName(),
                            targetLanguage));
                }
            }
        }
        else
            if (type instanceof CollectionType)
            {
                typedata.setTypeNameForElementName(
                    new ElementInfo(
                        type.getQName(),
                        createTypeInfo(
                            type.getRefType().getQName(),
                            targetLanguage)));
                typedata.setArray(true);
            }
            else
            {
                //is this a SOAPEnc array type	
                QName arrayType =
                    CSchemaUtils.getArrayComponentQName(
                        node,
                        new IntHolder(0),
                        symbolTable);
                if (arrayType != null)
                {
                    typedata.setTypeNameForElementName(
                        new ElementInfo(
                            new QName("item"),
                            createTypeInfo(arrayType, targetLanguage)));
                    typedata.setArray(true);
                }
                else
                    if ((arrayType =
                        CSchemaUtils.getCollectionComponentQName(node))
                        != null)
                    {
                        typedata.setTypeNameForElementName(
                            new ElementInfo(
                                new QName("item"),
                                createTypeInfo(arrayType, targetLanguage)));
                        typedata.setArray(true);
                    }
                //Note in a array the parameter type is stored as under the name item all the time  
                else
                {
                    // get all extended types
                    Vector extendList = new Vector();
                    extendList.add(type);
                    TypeEntry parent =
                        CSchemaUtils.getComplexElementExtensionBase(
                            type.getNode(),
                            symbolTable);
                    while (parent != null)
                    {
                        extendList.add(parent);
                        parent =
                            CSchemaUtils.getComplexElementExtensionBase(
                                parent.getNode(),
                                symbolTable);
                    }

                    // Now generate a list of names and types starting with
                    // the oldest parent.  (Attrs are considered before elements).
                    for (int i = extendList.size() - 1; i >= 0; i--)
                    {
                        TypeEntry te = (TypeEntry) extendList.elementAt(i);

                        //TODO the code require the attributes name at extension base types
                        //different, the WSDL2Ws do not support it having same name at up and below.

                        // The names of the inherited parms are mangled
                        // in case they interfere with local parms.
                        // String mangle = "";
                        //if (i > 0) {
                        //	mangle = "_" +
                        //		Utils.xmlNameToJava(te.getQName().getLocalPart()) +
                        //		"_";
                        //}

                        // Process the attributes
                        Vector attributes =
                            CSchemaUtils.getContainedAttributeTypes(
                                te.getNode(),
                                symbolTable);
                        if (attributes != null)
                        {
                            for (int j = 0; j < attributes.size(); j += 2)
                            {
                                typedata.setTypeForAttributeName(
                                    ((QName) attributes.get(j + 1))
                                        .getLocalPart(),
                                    createTypeInfo(
                                        ((TypeEntry) attributes.get(j))
                                            .getQName(),
                                        targetLanguage));
                            }
                        }
                        // Process the elements
                        Vector elements =
                            CSchemaUtils.getContainedElementDeclarations(
                                te.getNode(),
                                symbolTable);
                        if (elements != null)
                        {
                            for (int j = 0; j < elements.size(); j++)
                            {
                                ElementInfo eleinfo = null;
                                CElementDecl elem =
                                    (CElementDecl) elements.get(j);
                                if (elem.getAnyElement())
                                {

                                    Type anyType =
                                        new Type(
                                            CUtils.anyTypeQname,
                                            CUtils.anyTypeQname.getLocalPart(),
                                            true,
                                            targetLanguage);
                                    eleinfo =
                                        new ElementInfo(
                                            elem.getName(),
                                            anyType);
                                }
                                else
                                {
                                    QName typeName = elem.getType().getQName();
                                    if (typeName.getLocalPart().indexOf('[')
                                        > 0)
                                    {
                                        String localpart =
                                            typeName.getLocalPart().substring(
                                                0,
                                                typeName
                                                    .getLocalPart()
                                                    .indexOf(
                                                    '['));
                                        typeName =
                                            new QName(
                                                typeName.getNamespaceURI(),
                                                localpart);
                                        if (CUtils.isBasicType(typeName))
                                        {
                                            eleinfo =
                                                new ElementInfo(
                                                    elem.getName(),
                                                    createTypeInfo(
                                                        typeName,
                                                        targetLanguage));
                                        }
                                        else
                                        {
                                            eleinfo =
                                                new ElementInfo(
                                                    elem.getName(),
                                                    createTypeInfo(
                                                        elem.getType(),
                                                        targetLanguage));
                                        }
                                    }
                                    else
                                    {
                                        eleinfo =
                                            new ElementInfo(
                                                elem.getName(),
                                                createTypeInfo(
                                                    typeName,
                                                    targetLanguage));
                                    }
                                }
                                eleinfo.setMinOccurs(elem.getMinOccurs());
                                eleinfo.setMaxOccurs(elem.getMaxOccurs());
                                eleinfo.setNillable( elem.isNillable());
                                
                                // Dushshantha:
                                // states whether this element is a xsd:choice
                                eleinfo.setChoiceElement(elem.getChoiceElement());
                                //.................................................
                                
                                // Chinthana:
                                // states whether this element is a xsd:all
                                eleinfo.setAllElement(elem.getAllElement());
                                //04/05/2005.................................................
                                
                                //Dushshantha:
                                //states whether the element must be namespace qualified.
                                eleinfo.setNsQualified(elem.getNsQualified());
                                
                                
                                typedata.setTypeNameForElementName(eleinfo);
                            }
                        }
                    }
                }
            }
        return typedata;
    }

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
            //add by nithya
            methodinfo.addFaultType(faultinfo);
        }
    }

    private ParameterInfo createParameterInfo(Part part) throws WrapperFault
    {
        QName qname = part.getTypeName();
        if (qname == null)
        {
            Element element = symbolTable.getElement(part.getElementName());
            qname = element.getRefType().getQName();
        }

        Type type = this.typeMap.getType(qname);
        if (type == null)
            throw new WrapperFault("unregistered type " + qname + " referred");
        ParameterInfo parainfo = new ParameterInfo(type, part.getName());
        parainfo.setElementName(part.getElementName());
        return parainfo;
    }

    private MethodInfo getMethodInfoByName(String name) throws WrapperFault
    {
        for (int i = 0; i < methods.size(); i++)
        {
            if (((MethodInfo) methods.get(i)).getMethodname().equals(name))
                return (MethodInfo) methods.get(i);
        }
        throw new WrapperFault("binding and the port type do not match");
    }
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
        Collection types = symbolTable.getTypeIndex().values();
        Iterator typeIterator = types.iterator();   
        while(typeIterator.hasNext())
        {
            Object highLevelType = typeIterator.next();
            if(!(highLevelType instanceof BaseType))
            {
                DefinedType type = (DefinedType)highLevelType;
                
                if(!type.getQName().getLocalPart().toString().startsWith(">"))
                {
                    // It's not an "inner" type so look for the refs (this might not be valid logic and refs might be acceptable for these types too !)
                    HashSet nestedTypes = type.getNestedTypes(symbolTable, true);
                    Iterator nestTypeIter = nestedTypes.iterator();
                    while(nestTypeIter.hasNext())
                    {
                        Object nestedType =nestTypeIter.next();
                        if(!(nestedType instanceof BaseType))
                        {
                            TypeEntry defType = (TypeEntry)nestedType;
                            // If there is a ref type and the ref type is not currently exposed because it's an "inner" type (marked by ">")then make sure the ref type is exposed to the user as a class
                            // in order to expose it we simply change the name !                            
                            TypeEntry referencedType =defType.getRefType(); 
                            if(referencedType!=null && referencedType.getQName().getLocalPart().startsWith(">") && referencedType.getQName().getLocalPart().lastIndexOf(">") == 0)
                            {
                                if(WSDL2Ws.verbose)
                                {
                                    System.out.println( "got to expose "+defType.getQName().getLocalPart());
                                }
                                Type innerClassType = wsContext.getTypemap().getType(defType.getRefType().getQName());
                                innerClassType.setLanguageSpecificName(new QName(defType.getQName().getLocalPart()).toString());
                                
                                // also have to set the QName becuase this is used in generating the header info.
                                innerClassType.setName(new QName(innerClassType.getName().getNamespaceURI(), innerClassType.getLanguageSpecificName()));
                            }
                        }
                    }
                }
                
            }
        }
    }

    public static void usage()
    {
        System.out.println(
            "java WSDL2Ws -<options> <wsdlfile>\n"
                + "-help, -h              print this message\n"
                + "-o<folder>             target output folder - default is current folder\n"
                + "-l<c++|c>              target language (c++|c) - default is c++\n"
                + "-s<server|client>      target side (server|client) - default is server\n"
//                + "-w<wrapped|nonwrapped> wrapping style of the WSDL (wrapped|nonwrapped) - default is wrapped - nonwrapped is currently not implemented\n"
                + "-verbose, -v           be verbose\n"
                + "-t timeout			  timeout wehen trying to get resolve uri's"
                );
//                + "-m<none|gnu>           generate make files (none|gnu) - default is none\n");

    }
    /**
     * Usage
     * =====
     * java WSDL2ws <wsdlfile> -<optionChar><value>
     * 
     * Options and Values 
     * ======= === ======
     * -o target output folder
     * -l target language(c|c++) default is c++
     * -help (later ???? not implemented)
     * -h print usage()
     * -s (client|server|both)  
     * -t timeout
     * ****** removed *******-w wrapping style of the WSDL (wrapped|nonwrapped) - default is wrapped - nonwrapped is currently not implemented so removed option for -wnonwrapped
     * ****** removed *******-m create GNU make files - this was failing and not supported so removed.
     * 
     * Note:  PP - pull parser
     * @param args
     * @throws Exception
     */

    public static void main(String[] args) throws Exception
    {
        CLArgParser data = new CLArgParser(args);
        if (data.getArgumentCount() != 1 || !checkArguments(data))
        {
            usage();
        }
        else
        {
            

            if (data.isSet("v"))
                WSDL2Ws.verbose = true;

            if (data.isSet("h"))
            {
                usage();
                return;
            }
            

            

            // WSDL2Ws.makeSystem = data.getOptionBykey("m");
            try
            {

                WSDL2Ws gen = new WSDL2Ws(data);
                gen.generateWrappers(
                    null,
                    data.getOptionBykey("o"),
                    data.getOptionBykey("l"),
                    data.getOptionBykey("s"),
                    data.getOptionBykey("w"));

                System.out.println("\nCode generation completed.\n");
            }
            catch (Exception e)
            {
                e.printStackTrace();
                System.out.println(
                    "\nCode generation failed. Please see errors above.\n");
            }
        }
    }

    /**
     * This method checks that we do not have extraneous inputs to the tool that we do not support
     * @param data the args coming in
     * @return tre if the args are all supported false otherwise.
     */
    private static boolean checkArguments(CLArgParser data)
    {
        for(int i=0; i<data.getArgumentCount(); i++)
        {
            // Check that those supported args have only the acceptable options.
            // target language
            String language = data.getOptionBykey("l");
            if(language!=null)
            {
                if(!language.equals("c++") && !language.equals("c"))
                {
                    return false;
                }
            }
            
            // target side
            String targetSide = data.getOptionBykey("s");
            if(targetSide!=null)
            {
                if(!targetSide.equals("server") && !targetSide.equals("client") && !targetSide.equals("both"))
                {
                    return false;
                }
            }

            // ensure that only wrapped style is used. 
            if(data.isSet("w") && !"wrapped".equalsIgnoreCase(data.getOptionBykey("w")))
            {
                usage();
                return false;
            }
            
            // make file generation
            String makeFiles = data.getOptionBykey("m");
            if(makeFiles!=null)
            {
                // hawkeye - makefiles are not supported as of Nov 2005.
                return false;
//                if(!makeFiles.equals("none") && !makeFiles.equals("gnu"))
//                {
//                    return false;
//                }
            }
            
        }
        return true;
    }
    
    /**
     * Work out the various conditions that dictate whether this type will be generated into a new
     * file or not.
     * This method is only very partically implemented and will usually default to true. This is becuase we have 
     * this kind of logic already dispersed around the code (it usually just looks for a ">" in the name).
     * But it's much better to encapsulate here.
     *   
     * @param type
     * @return true if the type will not be generated. False otherwise
     * 
     */
    private boolean isTypeGenerated(TypeEntry type)
    {
        // If the referenced type is actually a type that will not get generated because it's
        // 	a base type array then tell other people of this case. Do this to two levels of indirection
        
        if(type.getRefType()!=null)
        {
            if(type.getRefType().getRefType()!=null && type.getRefType().getRefType().isBaseType())
            {
                return false;
            }
        }
            
        return true;
    }
}
