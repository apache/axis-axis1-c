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
 *    Apache Software Foundation (http://www.apache.org/)."
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

package org.apache.axis.wsdl.wsdl2ws;
import java.util.ArrayList;
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
import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.CollectionType;
import org.apache.axis.wsdl.symbolTable.Element;
import org.apache.axis.wsdl.symbolTable.ElementDecl;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.SchemaUtils;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.axis.wsdl.symbolTable.SymTabEntry;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.toJava.Utils;
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
 */
public class WSDL2Ws {

    private String language;

    private String qualifiedServiceName;
    private SymbolTable symbolTable;
    private boolean hasOrder = false;
    private String typeval;

    private String serviceStyle = null;

    private boolean verbose = true;
    private String targetEndpointURI = null;
    private String transportURI = null;
    private String targetNameSpaceOfWSDL = null;
    private TypeMap typeMap;
    
    private ServiceEntry serviceentry;
    private BindingEntry bindingEntry;
    private PortTypeEntry portTypeEntry;
	private ArrayList methods;	

    public WSDL2Ws(CLArgParser cmdLineArgs) throws WrapperFault {
        try {
            Parser wsdlParser = new Parser();
            //get the commandline arguments
            String wsdlfile = cmdLineArgs.getArgument(0);
            wsdlParser.run(wsdlfile);

            symbolTable = wsdlParser.getSymbolTable();
            
            //get the target namespace
			targetNameSpaceOfWSDL = symbolTable.getDefinition().getTargetNamespace();
        } catch (Exception e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }
    
    /** 
     * this method initailize the serviceEntry portEntry and bindingEntry   
     * @throws WrapperFault
     */
    
    public void perprocess()throws WrapperFault{
		typeMap = new TypeMap(language);
		this.serviceentry = getServiceEntry();
		Iterator ports = this.serviceentry.getService().getPorts().values().iterator();
		
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
		
		this.portTypeEntry = symbolTable.getPortTypeEntry(binding.getPortType().getQName());
		if (portTypeEntry == null)
			throw new WrapperFault("Service not found");
		ports = this.serviceentry.getService().getPorts().values().iterator();
		this.targetEndpointURI = SymbolTableParsingUtils.getTargetEndPointURI(ports);			
    }
    
    

    /**
     * This method exteact the service,binding,encoding information and return a PortType of the
     * webservice to publish.
     * @return port type the webservice based on
     */
    private void getWebServiceInfo()
        throws WrapperFault {
		this.qualifiedServiceName = portTypeEntry.getName();
		if (this.qualifiedServiceName == null) {
			qualifiedServiceName = portTypeEntry.getQName().getNamespaceURI();
			qualifiedServiceName =
				WrapperUtils.firstCharacterToLowercase(
					WrapperUtils.nsURI2packageName(qualifiedServiceName))
					+ "."
					+ portTypeEntry.getQName().getLocalPart();
		}
		
		//the service style (rpc|doc|msg)
		this.serviceStyle = bindingEntry.getBindingStyle().getName();
		//extract the trasport type as a uri
		this.transportURI = SymbolTableParsingUtils.getTransportType(bindingEntry.getBinding());
        List operations = bindingEntry.getBinding().getBindingOperations();
        if (operations != null) {

            for (int i = 0; i < operations.size(); i++) {
                //for the each binding operation found
                if (operations.get(i) instanceof javax.wsdl.BindingOperation) {
                	
					javax.wsdl.BindingOperation bindinop = (javax.wsdl.BindingOperation) operations.get(i);
					MethodInfo method = getMethodInfoByName(bindinop.getName());
					method.setSoapAction(SymbolTableParsingUtils.getSoapAction(bindinop));
					SymbolTableParsingUtils.getInputInfo(bindinop.getBindingInput(),method);
                    SymbolTableParsingUtils.getOutputInfo(bindinop.getBindingOutput(),method);
                }
            }
        }
    }

    /**
     * get Service data .. service data is given as the fully qualified names
     * When possible the user can have the schema QName if he like
     */

    private ArrayList getServiceInfo(PortType porttype)throws WrapperFault {
        //get opeation list
        Iterator oplist = porttype.getOperations().iterator();
        ArrayList methods = new ArrayList();
        MethodInfo minfo;
		Element element;
		QName qname;
        ParameterInfo pinfo;
		Type type;
        org.apache.axis.wsdl.symbolTable.Type ptype;
        //for each operation
        while (oplist.hasNext()) {
            minfo = new MethodInfo();
            methods.add(minfo);

            //add operation to operation List
            Operation op = (Operation) oplist.next();
            minfo.setMethodname(op.getName());
            
            //setting the faults
            Map faults = op.getFaults();
			addFaultInfo(faults,minfo);
            
            Iterator paramlist = op.getInput().getMessage().getParts().values().iterator();
            //add each parameter to parameter list
            if ("document".equals(bindingEntry.getBindingStyle().getName())){
				Part part = (Part) paramlist.next();
				if ("parameters".equals(part.getName())){
					element = symbolTable.getElement(part.getElementName());
					qname = element.getRefType().getQName();
					if (qname != null){
						minfo.setInputMessage(element.getQName());
						type = this.typeMap.getType(qname);				
						if(type == null)
							 throw new WrapperFault("unregisterd type "+qname+" refered");
						if(type.getLanguageSpecificName().startsWith(">")){ //anonymous type - the message element
							//get inner attributes and elements and add them as parameters
							ArrayList elementlist = new ArrayList();
							Iterator names = type.getElementnames();
							while (names.hasNext()){
								elementlist.add(names.next());
							}
							Type innerType;
							for (int i = 0 ; i < elementlist.size(); i++) {
								String elementname = (String)elementlist.get(i);
								innerType = type.getElementForElementName(elementname).getType();
								pinfo = new ParameterInfo(innerType,elementname);
								pinfo.setElementName(type.getElementForElementName(elementname).getName());
								minfo.addInputParameter(pinfo);		
							}
						}
						else{
							pinfo = new ParameterInfo(type,element.getQName().getLocalPart());
							pinfo.setElementName(element.getQName());
							minfo.addInputParameter(pinfo);
						}
					}
				}
				else{
					throw new WrapperFault("A message name of document literal style WSDL is not \"parameters\"");
				}
	    	}
    	   	else{
	    	  	while (paramlist.hasNext()) {
	        	 	Part p = (Part) paramlist.next();
	            	pinfo = createParameterInfo(p);
	               	minfo.addInputParameter(pinfo);
	           	}
            }
            //get the return type
            Iterator returnlist = op.getOutput().getMessage().getParts().values().iterator();
			if ("document".equals(bindingEntry.getBindingStyle().getName())){
				Part part = (Part) returnlist.next();
				if ("parameters".equals(part.getName())){
					element = symbolTable.getElement(part.getElementName());
					qname = element.getRefType().getQName();
					if (qname != null){
						minfo.setOutputMessage(element.getQName());
						type = this.typeMap.getType(qname);				
						if(type == null)
							 throw new WrapperFault("unregisterd type "+qname+" refered");
						if(type.getLanguageSpecificName().startsWith(">")){
							//get inner attributes and elements and add them as parameters 
							ArrayList elementlist = new ArrayList();
							Iterator names = type.getElementnames();
							while (names.hasNext()){
								elementlist.add(names.next());
							}
							Type innerType;
							for (int i = 0 ; i < elementlist.size(); i++) {
								String elementname = (String)elementlist.get(i);
								innerType = type.getElementForElementName(elementname).getType();
								pinfo = new ParameterInfo(innerType,elementname);
								pinfo.setElementName(type.getElementForElementName(elementname).getName());
								minfo.addOutputParameter(pinfo);		
							}							
						}
						else{
							pinfo = new ParameterInfo(type,element.getQName().getLocalPart());
							pinfo.setElementName(element.getQName());
							minfo.addOutputParameter(pinfo);							
						}
						pinfo = new ParameterInfo(type,part.getName());
						pinfo.setElementName(part.getElementName());					}
				}
				else{
					throw new WrapperFault("A message name of document literal style WSDL is not \"parameters\"");
				}
			}
			else{
	            if (returnlist.hasNext()) {
	                Part p = ((Part) returnlist.next());
	   		        minfo.addOutputParameter(createParameterInfo(p));
	            }
			}
        }
        return methods;
    }

    /**
     * This method extract the custom complex type info fom the symbol table
     * @return the type map with type info
     */
    private TypeMap getTypeInfo(String targetLanguage)throws WrapperFault {
        Iterator it = symbolTable.getTypeIndex().values().iterator();
        TypeEntry type;
        Iterator elements;
        Type typedata;

        boolean hasElements;
        while (it.hasNext()) {
            type = (TypeEntry) it.next();
            Node node = type.getNode();
            if (node != null) {
					createTypeInfo(type,targetLanguage);

            }
        } //end of type while
        return typeMap;
    } //end of method

    public void genarateWrappers(
        String servicename,
        String targetoutputLocation,
        String targetLanguage,
        String targetImplementationStyle,
        String targetEngine)
        throws WrapperFault {
        	
		this.language = targetLanguage;
		if (targetLanguage == null) targetLanguage = "c++";
		if (targetEngine == null) targetEngine = "server";
		if (targetoutputLocation == null) targetoutputLocation = "./";
		
		perprocess();
		
		QName serviceqname = serviceentry.getService().getQName();
		servicename = serviceqname.getLocalPart();
		typeMap = this.getTypeInfo(targetLanguage);
        methods = this.getServiceInfo(this.portTypeEntry.getPortType());
        this.getWebServiceInfo();
        
        //TODO	chaeck weather the name at the WrapperConstant Doclit is right "doc"

        WebServiceGenarator wsg =
            WebServiceGenaratorFactory.createWebServiceGenarator(
                new WebServiceContext(
                    new WrapperInfo(
                        serviceStyle,
                        targetLanguage,
                        targetoutputLocation,
                        targetImplementationStyle,
                        targetEngine,
                        transportURI,
                        targetEndpointURI,
                        targetNameSpaceOfWSDL),
                    new ServiceInfo(servicename, qualifiedServiceName, methods),
                    typeMap));
        if (wsg == null)
            throw new WrapperFault("does not support the option combination");
        if(verbose){
        	Iterator it = typeMap.getTypes().iterator();
        	while(it.hasNext()){
        		System.out.println(it.next());
        	}
        }    
 		wsg.genarate();
    }
    
    /**
     * This code is taken from the org.apache.axis.wsdl.gen.Parser Class.
     * WSDL file should have only one service, The first service 
     * find is utilized.
     * @return
     * @throws WrapperFault
     */
    public ServiceEntry getServiceEntry()throws WrapperFault{
		Iterator it = symbolTable.getHashMap().values().iterator();
		 while (it.hasNext()) {
			Vector v = (Vector) it.next();
			  for (int i = 0; i < v.size(); ++i) {
				  SymTabEntry entry = (SymTabEntry) v.elementAt(i);
   
			 if (entry instanceof ServiceEntry) {
					return (ServiceEntry)entry;
				 }
			}
		 }
		 throw new WrapperFault("the service does not exists");
    }
    
	public Type createTypeInfo(QName typename,String targetLanguage)throws WrapperFault{
		TypeEntry type = symbolTable.getType(typename);	
		if(type == null){
			type = symbolTable.getElement(typename);
			if(type == null){
				throw new WrapperFault("["+typename+"]unexpected condition occured " +
					".. please inform the axis-dev@apache.org mailing list ASAP");
				
			}
			type.getRefType();
		}
	
		return createTypeInfo(type,targetLanguage);
	}
    
    /**
     * This code is borrowd from the JavaBeanWriter#writeFullConstructor().
     * @param type
     * @param targetLanguage
     * @return
     */

	public Type createTypeInfo(TypeEntry type,String targetLanguage)throws WrapperFault{
		Type typedata = typeMap.getType(type.getQName());
		
		if(typedata!= null){
			//type is a inbild type or a already created type
			return typedata;  
		}
		System.out.println(
			"############## the type found =" + type.getQName());
		typedata =
			new Type(type.getQName(), type.getName(), true, targetLanguage);
		typeMap.addType(type.getQName(), typedata);
			
		Node node = type.getNode();

		Vector enumdata = null;
		if(type.isSimpleType())
			enumdata = Utils.getEnumerationBaseAndValues(node,symbolTable);
		if(enumdata != null){
			typedata.setEnumerationdata(enumdata);
		}else if(type instanceof CollectionType){
			typedata.setTypeNameForElementName(new ElementInfo(type.getQName(),
					createTypeInfo(type.getRefType().getQName(),targetLanguage)));
			typedata.setArray(true);
			typedata.setCanThisOccuredmoreThanOnceAllTheTime(true);		
		}else{
			//is this a SOAPEnc array type	
			QName arrayType =
				SchemaUtils.getArrayComponentQName(node, new IntHolder(0));
			if (arrayType != null) {
				typedata.setTypeNameForElementName(new ElementInfo(new QName("item"),
						createTypeInfo(arrayType,targetLanguage)));
				typedata.setArray(true);
			} else if (
				(arrayType = SchemaUtils.getCollectionComponentQName(node))
					!= null) {
				typedata.setTypeNameForElementName(new ElementInfo(new QName("item"),
						createTypeInfo(arrayType,targetLanguage)));
				typedata.setArray(true);
			} 
			//Note in a array the parameter type is stored as under the name item all the time  
			else {
				// get all extended types
				Vector extendList = new Vector();
				extendList.add(type);
				TypeEntry parent = SchemaUtils.getComplexElementExtensionBase(
														type.getNode(),symbolTable);
				while(parent != null) {
					extendList.add(parent);
					parent = SchemaUtils.getComplexElementExtensionBase(
												parent.getNode(),symbolTable);
				}
		
				// Now generate a list of names and types starting with
				// the oldest parent.  (Attrs are considered before elements).
				for (int i=extendList.size()-1; i >= 0; i--) {
					TypeEntry te = (TypeEntry) extendList.elementAt(i);
		
					
					//TODO the code require the attributes name at extension base types
					//different, the WSDL2Ws do not support it having same name at up and below.
					
					// The names of the inherited parms are mangled
					// in case they interfere with local parms.
					String mangle = "";
					//if (i > 0) {
					//	mangle = "_" +
					//		Utils.xmlNameToJava(te.getQName().getLocalPart()) +
					//		"_";
					//}
					
					// Process the attributes
					Vector attributes = SchemaUtils.getContainedAttributeTypes(
						te.getNode(), symbolTable);
					if (attributes != null) {
						for (int j=0; j<attributes.size(); j+=2) {
							typedata.setTypeForAttributeName(
								((QName)attributes.get(j + 1)).getLocalPart(),
							createTypeInfo(((TypeEntry) attributes.get(j)).getQName(),targetLanguage));
						}
					}
					// Process the elements
					Vector elements = SchemaUtils.getContainedElementDeclarations(
											te.getNode(), symbolTable);
					if (elements != null) {
						for (int j=0; j<elements.size(); j++) {
							ElementDecl elem = (ElementDecl)elements.get(j);
							QName typeName = elem.getType().getQName();
							if(typeName.getLocalPart().indexOf('[')>0){
								String localpart = typeName.getLocalPart().substring(0,typeName.getLocalPart().indexOf('['));
								typeName = new QName(typeName.getNamespaceURI(),localpart);
							}
								
							ElementInfo eleinfo = new ElementInfo(elem.getName(),createTypeInfo(typeName,targetLanguage));
							eleinfo.setMinOccurs(elem.getMinOccrs());
							eleinfo.setMaxOccurs(elem.getMaxOccurs());
							typedata.setTypeNameForElementName(eleinfo);
						}			
					}
				}
			}
		}	
		return typedata;
	}

	private void addFaultInfo(Map faults,MethodInfo methodinfo)throws WrapperFault{
		if(faults == null)
			return;
		Iterator faultIt = faults.values().iterator();
		while(faultIt.hasNext()){
			Fault fault = (Fault)faultIt.next();
			FaultInfo faultinfo = new FaultInfo(fault.getName());
			Map parts = fault.getMessage().getParts();
			Iterator partIt = parts.values().iterator();
			while(partIt.hasNext()){
				faultinfo.addParam(createParameterInfo((Part)partIt.next()));
			}			  
		}	 
	
	}
	
	private ParameterInfo createParameterInfo(Part part)throws WrapperFault{
		QName qname = part.getTypeName();
		if(qname == null){
			Element element = symbolTable.getElement(part.getElementName());
			qname = element.getRefType().getQName();
		}
		TypeEntry tentry = symbolTable.getType(qname);
		
		Type type = this.typeMap.getType(qname);
		if(type == null)
			throw new WrapperFault("unregisterd type "+qname+" refered");
			
		ParameterInfo parainfo = 
			new ParameterInfo(type,part.getName());
		parainfo.setElementName(part.getElementName());
		return parainfo;
	}

	private MethodInfo getMethodInfoByName(String name)throws WrapperFault{
		for(int i = 0; i < methods.size();i++){
			if(((MethodInfo)methods.get(i)).getMethodname().equals(name))
				return (MethodInfo)methods.get(i);
		}
		throw new WrapperFault("binding and the port type do not match");
	}

    /**
     * Usage
     * =====
     * java WSDL2ws <wsdlfile> -<optionChar><value>
     * 
     * Options and Values 
     * ======= === ======
     * -o target output folder
     * -l target language(c|java|c++) default is java
     * --help (later ???? not emplemented)
     * -i implementation style (struct|order|simple) default is struct--- (usergetvalue() with PP or use getTag() ect ....)
     * -s (client|server|both)  
     * 
     * Note:  PP - pull parser
     * @param args
     * @throws Exception
     */

    public static void main(String[] args) throws Exception {
        CLArgParser data = new CLArgParser(args);
        System.out.println(data.getArgumentCount());
        if (data.getArgumentCount() != 1)
            System.out.println(
                "java WSDL2ws <wsdlfile> -<optionChar><value>\n"
                    + "-o target output folder - default is current folder\n"
                    + "-l target language(c|c++) - default is c++\n"
                    + "-s (client|server) - default is server\n");
        else {
            WSDL2Ws gen = new WSDL2Ws(data);
            gen.genarateWrappers(
                null,
                data.getOptionBykey("o"),
                data.getOptionBykey("l"),
                data.getOptionBykey("i"),
                data.getOptionBykey("s"));
        }
    }
}
