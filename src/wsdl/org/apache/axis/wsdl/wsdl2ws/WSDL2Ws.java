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

import org.apache.axis.wsdl.wsdl2ws.info.ElementInfo;
import org.apache.axis.wsdl.wsdl2ws.info.FaultInfo;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ServiceInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.TypeMap;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
import org.apache.axis.wsdl.wsdl2ws.info.WrapperInfo;
import org.apache.axis.wsdl.symbolTable.DefinedElement;
import org.apache.axis.wsdl.symbolTable.CollectionElement;
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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */
public class WSDL2Ws {
    public static boolean verbose = false;
    public static String makeSystem = null;

    private String language;
	private boolean wsdlWrappingStyle;

    private String qualifiedServiceName;
    private SymbolTable symbolTable;
    private boolean hasOrder = false;
    private String typeval;

    private String serviceStyle = null;

    //private boolean verbose = true;
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
		ElementInfo eleinfo;
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
            Iterator paramlist = null;
            //add each parameter to parameter list
            if ("document".equals(bindingEntry.getBindingStyle().getName())){
				paramlist = op.getInput().getMessage().getParts().values().iterator();
				Part part = (Part) paramlist.next();
				QName minfoqname;
				element = symbolTable.getElement(part.getElementName());
				if ( element == null ) {
					// the part reference a type.
					qname =  symbolTable.getType(part.getTypeName()).getQName();
					minfoqname = symbolTable.getType(part.getTypeName()).getQName();
				}
				else {
					qname = element.getRefType().getQName();
					minfoqname = element.getQName();
				}
				if (qname != null){
					minfo.setInputMessage(minfoqname);
					
					type = this.typeMap.getType(qname);
					//boolean wrapped = true; //TODO take this from a commandline argument
					//boolean wrapped = false; //just for testing the non-wrapped style wsdl
					boolean wrapped = wsdlWrappingStyle;

					if (wrapped){
						if(type == null)
							 throw new WrapperFault("unregisterd type "+qname+" refered");
						else{
							/* if(type.getLanguageSpecificName().startsWith(">")){*/ //anyway skip the wrapping element type even if it is a named type.
							//get inner attributes and elements and add them as parameters
							ArrayList elementlist = new ArrayList();
							Iterator names = type.getElementnames();
							while (names.hasNext()){
								elementlist.add(names.next());
							}

							Type innerType;
							for (int i = 0 ; i < elementlist.size(); i++) {
								String elementname = (String)elementlist.get(i);
								eleinfo = type.getElementForElementName(elementname);
								innerType = eleinfo.getType();
								pinfo = new ParameterInfo(innerType,elementname);
								if (eleinfo.getMaxOccurs() > 1){
									pinfo.setArray(true);									
								}
								pinfo.setElementName(type.getElementForElementName(elementname).getName());
								if (innerType.getName().equals(CUtils.anyTypeQname))
									pinfo.setAnyType(true);
								minfo.addInputParameter(pinfo);		
							}

							ArrayList attributeList = new ArrayList();
							names = type.getAttributeNames();
							while (names.hasNext()){
								attributeList.add(names.next());
							}
							for (int i = 0; i < attributeList.size();i++){
								String attributeName = (String) attributeList.get(i);
								innerType = type.getTypForAttribName(attributeName);
								pinfo= new ParameterInfo(innerType, attributeName);
								pinfo.setElementName(type.getTypForAttribName(attributeName).getName());
								pinfo.setAttribute(true);
								minfo.addInputParameter(pinfo);
							}
							//remove the type that represents the wrapping element so that such type is not created.
							//following is commented for the moment because the same element can be refered by more
							//than one message. Also this complex type may be used as a type while it is the wrapping 
							//element here 
							//this.typeMap.removeType(qname);
						}
					}
					else{ // for non-wrapped style wsdl's
						if(type == null)
							 throw new WrapperFault("unregisterd type "+qname+" refered");
						else{
							// String elementName = (String)type.getName().toString();
							String elementName = (String)element.getQName().getLocalPart();
							pinfo = new ParameterInfo(type,elementName);
							pinfo.setElementName(type.getName());
							if (type.getName().equals(CUtils.anyTypeQname))
								pinfo.setAnyType(true);
							minfo.addInputParameter(pinfo);
						}
					}
				}
	    	}
    	  	else{
				minfo.setInputMessage(op.getInput().getMessage().getQName());
    	   		if (op.getParameterOrdering() != null){
	    	   		for (int ix=0; ix < op.getParameterOrdering().size(); ix++){
						Part p = (Part)(op.getInput().getMessage().getParts().get((String)op.getParameterOrdering().get(ix)));
						if (p == null) continue;
						pinfo = createParameterInfo(p);
						if (null != pinfo) minfo.addInputParameter(pinfo);
	    	   		}
    	   		}
    	   		else {
					paramlist = op.getInput().getMessage().getParts().values().iterator();
					while (paramlist.hasNext()) { //RPC style messages can have multiple parts
						Part p = (Part) paramlist.next();
						pinfo = createParameterInfo(p);
						if (null != pinfo) minfo.addInputParameter(pinfo);
					}    	   			
    	   		}
           }
            //get the return type
			if(op.getOutput()!=null){
	            Iterator returnlist = op.getOutput().getMessage().getParts().values().iterator();
				if (returnlist.hasNext() && "document".equals(bindingEntry.getBindingStyle().getName())){
					Part part = (Part) returnlist.next();
					QName minfoqname;
					element = symbolTable.getElement(part.getElementName());
					if ( element == null ) {
						// the part reference a type.
						qname =  symbolTable.getType(part.getTypeName()).getQName();
						minfoqname = symbolTable.getType(part.getTypeName()).getQName();
					}
					else {
						qname = element.getRefType().getQName();
						minfoqname = element.getQName();
					}
					if (qname != null){
						minfo.setOutputMessage(minfoqname);
						type = this.typeMap.getType(qname);				
						//boolean wrapped = true; //TODO take this from a commandline argument
						boolean wrapped = wsdlWrappingStyle;
						if (wrapped){
							if(type == null)
								 throw new WrapperFault("unregisterd type "+qname+" refered");
							else{
								/*if(type.getLanguageSpecificName().startsWith(">")){*///anyway skip the wrapping element type even if it is a named type.
								//get inner attributes and elements and add them as parameters 
								ArrayList elementlist = new ArrayList();
								Iterator names = type.getElementnames();
								while (names.hasNext()){
									elementlist.add(names.next());
								}
								Type innerType;
								for (int i = 0 ; i < elementlist.size(); i++) {
									String elementname = (String)elementlist.get(i);
									eleinfo = type.getElementForElementName(elementname);
									innerType = eleinfo.getType();
									pinfo = new ParameterInfo(innerType,elementname);
									if (eleinfo.getMaxOccurs() > 1){
										pinfo.setArray(true);									
									}
									pinfo.setElementName(type.getElementForElementName(elementname).getName());
									if (innerType.getName().equals(CUtils.anyTypeQname))
										pinfo.setAnyType(true);
									minfo.addOutputParameter(pinfo);		
								}							
								//remove the type that represents the wrapping element so that such type is not created.							
								//following is commented for the moment because the same element can be refered by more
								//than one message. Also this complex type may be used as a type while it is the wrapping 
								//element here 
								//this.typeMap.removeType(qname);
							}
						}
						else{ // for non-wrapped style wsdl's
							if(type == null)
								 throw new WrapperFault("unregisterd type "+qname+" refered");
							else{
								// String elementName = (String)type.getName().toString();
								String elementName = (String)element.getQName().getLocalPart();
								symbolTable.dump ( System.out);
								pinfo = new ParameterInfo(type,elementName);
								pinfo.setElementName(type.getName());
								if (type.getName().equals(CUtils.anyTypeQname))
									pinfo.setAnyType(true);
								minfo.addOutputParameter(pinfo);
							}
						}
					}
				}
				else{
			//added on 1-jun-2004
				    minfo.setInputMessage(op.getInput().getMessage().getQName()); 
				    minfo.setOutputMessage(op.getOutput().getMessage().getQName());
				   // minfo.setFaultMessage();
					if (op.getParameterOrdering() != null){
						 
						for (int ix=0; ix < op.getParameterOrdering().size(); ix++){
							Part p = (Part)(op.getOutput().getMessage().getParts().get((String)op.getParameterOrdering().get(ix)));
							if (p == null) continue;
							pinfo = createParameterInfo(p);
							if (null != pinfo) minfo.addOutputParameter(pinfo);
						}
						/* there can be more output parameters than in parameterOrder list (partial parameter ordering) */
						returnlist = op.getOutput().getMessage().getParts().values().iterator();
						while (returnlist.hasNext()) { //RPC style messages can have multiple parts
							Part p = (Part) returnlist.next();
							if (op.getParameterOrdering().contains(p.getName())) continue;
							pinfo = createParameterInfo(p);
							if (null != pinfo) minfo.addOutputParameter(pinfo);
						}    	   				    	   			
					}
					else {
						returnlist = op.getOutput().getMessage().getParts().values().iterator();
						while (returnlist.hasNext()) { //RPC style messages can have multiple parts
							Part p = ((Part) returnlist.next());
							pinfo = createParameterInfo(p);
							if (null != pinfo) minfo.addOutputParameter(pinfo);
						}
					}
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
        String targetEngine,
        String security,
	    String wsdlWrapStyle)
        throws WrapperFault {
        	
		if (targetLanguage == null) targetLanguage = "c++";
		if (targetEngine == null) targetEngine = "server";
		if (targetoutputLocation == null) targetoutputLocation = "./";
		if (wsdlWrapStyle == null) wsdlWrapStyle = "wrapped";
		
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
                        targetNameSpaceOfWSDL,
                        security),
                    new ServiceInfo(servicename, qualifiedServiceName, methods),
                    typeMap));
        if (wsg == null)
            throw new WrapperFault("does not support the option combination");
        if (WSDL2Ws.verbose){
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
		if (!type.isReferenced()) return null; //do not add types which are not used in the wsdl
		if (type instanceof CollectionElement){ //an array
		}
		else if (type instanceof DefinedElement){ //skip any wrapping elements where ref=....
			if (type.getRefType() != null){
				return createTypeInfo(type.getRefType(), targetLanguage);
			}
			return null;
		}
		Type typedata = typeMap.getType(type.getQName());		
		if(typedata!= null){
			//type is a inbild type or a already created type
			return typedata;  
		}

		if (-1 != type.getQName().getLocalPart().indexOf('[')) {/* it seems that this is an array */
			if (null == type.getRefType())throw new WrapperFault("Array type found without a Ref type");
			QName qn = type.getRefType().getQName();
			if (null == qn)throw new WrapperFault("Array type found without a Ref type");
			if (CUtils.isBasicType(qn)) return null;
			QName newqn = new QName(type.getQName().getNamespaceURI(), qn.getLocalPart()+"_Array");
			typedata = new Type(newqn, newqn.getLocalPart(), true, targetLanguage);
                        if( type.getRefType().getRefType() != null )
				typedata.setElementType(type.getRefType().getRefType().getQName().getLocalPart());
			else
				typedata.setElementType(type.getRefType().getQName().getLocalPart());
			typeMap.addType(newqn, typedata);
		}else {
			typedata = new Type(type.getQName(), type.getQName().getLocalPart(), true, targetLanguage);
			typeMap.addType(type.getQName(), typedata);
		}
			
		Node node = type.getNode();

		Vector restrictdata = null;
		if(type.isSimpleType()){
			//check for extended types
			TypeEntry base = SchemaUtils.getComplexElementExtensionBase(type.getNode(),symbolTable);
			if (base != null){
				String localpart = type.getQName().getLocalPart()+ "_value";
				QName typeName = new QName(type.getQName().getNamespaceURI(),localpart);
				ElementInfo eleinfo = new ElementInfo(typeName,createTypeInfo(base.getQName(),targetLanguage));
				typedata.setExtensionBaseType(eleinfo);
				if ( WSDL2Ws.verbose)
				    System.out.print("=====complexType with simpleContent is found : "+ type.getQName().getLocalPart()+"=====\n");
			}
			else{
			//types declared as simpleType
				restrictdata = CUtils.getRestrictionBaseAndValues(node,symbolTable);
				if(restrictdata != null)
					typedata.setRestrictiondata(restrictdata);
			}
			// There can be attributes in this extended basic type
			// Process the attributes
			Vector attributes = SchemaUtils.getContainedAttributeTypes(
				type.getNode(), symbolTable);
			if (attributes != null) {
				for (int j=0; j<attributes.size(); j+=2) {
					typedata.setTypeForAttributeName(
						((QName)attributes.get(j + 1)).getLocalPart(),
					createTypeInfo(((TypeEntry) attributes.get(j)).getQName(),targetLanguage));
				}
			}			
		}else if(type instanceof CollectionType){
			typedata.setTypeNameForElementName(new ElementInfo(type.getQName(),
					createTypeInfo(type.getRefType().getQName(),targetLanguage)));
			typedata.setArray(true);
		}else{
			//is this a SOAPEnc array type	
			QName arrayType =
				SchemaUtils.getArrayComponentQName(node, new IntHolder(0),symbolTable);
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
							ElementInfo eleinfo = null;
							ElementDecl elem = (ElementDecl)elements.get(j);
							if (elem.getAnyElement()){
							
								Type anyType = new Type(CUtils.anyTypeQname, CUtils.anyTypeQname.getLocalPart(), true, targetLanguage);
								eleinfo = new ElementInfo(elem.getName(),anyType);							
							}
							else{
								QName typeName = elem.getType().getQName();
								if(typeName.getLocalPart().indexOf('[')>0){
									String localpart = typeName.getLocalPart().substring(0,typeName.getLocalPart().indexOf('['));
									typeName = new QName(typeName.getNamespaceURI(),localpart);
									if (CUtils.isBasicType(typeName)){
										eleinfo = new ElementInfo(elem.getName(),createTypeInfo(typeName,targetLanguage));
									}
									else{
										eleinfo = new ElementInfo(elem.getName(),createTypeInfo(elem.getType(),targetLanguage)); 
									}
								}
								else{
									eleinfo = new ElementInfo(elem.getName(),createTypeInfo(typeName,targetLanguage));								
								}
							}
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
			//add by nithya
			methodinfo.addFaultType(faultinfo) ;
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

    public static void usage() {
        System.out.println(
                "java WSDL2Ws -<options> <wsdlfile>\n"
                    + "-help, -h              print this message\n"
                    + "-o<folder>             target output folder - default is current folder\n"
                    + "-l<c++|c>              target language (c++|c) - default is c++\n"
                    + "-s<server|client>      target side (serve|client) - default is server\n"
                    + "-c<none|ssl>           channel security (ssl|none) - default is none\n"
                    + "-w<wrapped|nonwrapped> wrapping style of the WSDL (wrapped|nonwrapped) - default is wrapped\n"
                    + "-verbose, -v           be verbose\n"
                    + "-m<none|gnu>           generate make files (none|gnu) - default is none\n");

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
     * -w wrapping style of the WSDL (wrapped|nonwrapped) - default is wrapped
     * 
     * Note:  PP - pull parser
     * @param args
     * @throws Exception
     */

    public static void main(String[] args) throws Exception {
        CLArgParser data = new CLArgParser(args);

        if (data.getArgumentCount() != 1) {
            usage();
        }
        else {

            if (data.isSet("v"))
                WSDL2Ws.verbose = true;

            if (data.isSet("h")) {
                usage();
                return; 
            }

            WSDL2Ws.makeSystem = data.getOptionBykey("m");

            try {
            
                WSDL2Ws gen = new WSDL2Ws(data);
                gen.genarateWrappers(
                    null,
                    data.getOptionBykey("o"),
                    data.getOptionBykey("l"),
                    data.getOptionBykey("i"),
                    data.getOptionBykey("s"),
                    data.getOptionBykey("c"),
		    	    data.getOptionBykey("w"));
		    	    
				System.out.println( "\nCode generation completed.\n");
            } 
		catch(NoSuchMethodError noSuchMethodError)
            {
            	// catch the no such method error that occurs when they have put this class after axis java 1.2
            	if(noSuchMethodError.getMessage().indexOf("org.apache.axis.wsdl.symbolTable.ElementDecl.getMinOccrs")>-1)
            	{
            		System.out.println("We have caught the following error - "+noSuchMethodError);
					System.out.println("");
					System.out.println("This usually occurs when axis java jar file comes before WSDL2ws.jar in your classpath.");
					System.out.println("Please verify that WSDL2ws.jar comes first in your classpath and correct if necessary");
					System.out.println("If it does and you still get this error then please raise an issue with the supplier of your code");
            	}

            }catch (Exception e) {            	
            	e.printStackTrace();
				System.out.println( "\nCode generation failed. Please see errors above.\n");
            }
        }
    }
}
