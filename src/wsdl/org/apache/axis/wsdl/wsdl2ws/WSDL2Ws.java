/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
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
 
/**
 * @author Srinath Perera(hemapani@openource.lk)
 */
package org.apache.axis.wsdl.wsdl2ws;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;

import javax.wsdl.Binding;
import javax.wsdl.BindingInput;
import javax.wsdl.Operation;
import javax.wsdl.Part;
import javax.wsdl.Port;
import javax.wsdl.PortType;
import javax.xml.namespace.QName;
import javax.xml.rpc.holders.IntHolder;

import org.apache.axis.wsdl.wsdl2ws.CLArgParser;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ServiceInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.TypeMap;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
import org.apache.axis.wsdl.wsdl2ws.info.WrapperInfo;

import org.apache.axis.wsdl.gen.Parser;
import org.apache.axis.wsdl.symbolTable.ElementDecl;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.SchemaUtils;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.w3c.dom.Node;

public class WSDL2Ws {
	private PortType porttype ;

	private String qualifiedServiceName;
    private SymbolTable tb;
	private boolean hasOrder = false;
	private String typeval;

	private String serviceStyle = null;
	private String encodingStyle = null;
	private String targetEndpointURI = null;
	private String transportURI = null;
    private TypeMap typeMap;
    
    
	public WSDL2Ws(CLArgParser cmdLineArgs) throws WrapperFault {
		try {
            typeMap = new TypeMap();
			Parser wsdlParser = new Parser();
			String wsdlfile =  cmdLineArgs.getArgument(0);
            String serviceuri = cmdLineArgs.getArgument(1);
            String servicelocalpart = cmdLineArgs.getArgument(2);

            if(wsdlfile == null || servicelocalpart == null)
              throw new WrapperFault("not enough arguments ");
            wsdlParser.run(wsdlfile);

			tb = wsdlParser.getSymbolTable();
            // tb.dump(System.out);
		   porttype = this.getWebServiceInfo(serviceuri,servicelocalpart);
		} catch (Exception e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}

    /**
     * This method exteact the service,binding,encoding information and return a PortType of the
     * webservice to publish.
     * @return port type the webservice based on
     */
    private PortType getWebServiceInfo(String serviceuri,String servicelocalpart)throws WrapperFault{
        //get the service
           ServiceEntry sentry = tb.getServiceEntry(new QName(serviceuri,servicelocalpart));
		   Iterator ports = sentry.getService().getPorts().values().iterator();
		   
		   //if the targetEndPointURI not specifed we continue having it null
		   //The WrapperInfo will set a default value for the targetEndPointURI
		   if(ports.hasNext()){
		   		Port port = (Port)ports.next();
				List adresslist = port.getExtensibilityElements();
				if(adresslist != null && adresslist.size() != 0 && (adresslist.get(0) instanceof com.ibm.wsdl.extensions.soap.SOAPAddressImpl) )
					this.targetEndpointURI = ((com.ibm.wsdl.extensions.soap.SOAPAddressImpl)adresslist.get(0)).getLocationURI();
		   }
           
           //get the binding
           Iterator portmap = sentry.getService().getPorts().values().iterator();
           //TODO resolve this
           /*
               this code support only the service with onebindings it will not care about the
               second binding if exists.. if the NO binding specified it will failed
            */
           Binding binding = null;
           if(portmap.hasNext())
               binding = ((Port)portmap.next()).getBinding();

          if(binding == null)
           	throw new WrapperFault("No binding specified");
           	
            //the service style (rpc|doc|msg)
			this.serviceStyle = tb.getBindingEntry(binding.getQName()).getBindingStyle().getName();
			
			//extract the trasport type as a uri
			List soapbinding = binding.getExtensibilityElements();
		    if(soapbinding!= null && soapbinding.size() > 0 && (soapbinding.get(0) instanceof com.ibm.wsdl.extensions.soap.SOAPBindingImpl))
				this.transportURI = ((com.ibm.wsdl.extensions.soap.SOAPBindingImpl)soapbinding.get(0)).getTransportURI();
               
			/**
			 * --- Get the encoding style ---
			 * The WSDL file specified the encoding for the each operation in the binding.
			 * but tool can not genarate the stub/skeltons/types which each has different 
			 * encoding styles. So the encoding style given in the FIRST OPERATION will be used 
			 * as THE ENCODED style for all the operations.
			 * # if the more than one encoding style define for the first operation the 
			 * # first among them will be used.   
			 */
			
			List operations = binding.getBindingOperations();
			if(operations!= null){
			
			for(int i =0; i <operations.size(); i++){
				//for the first binding operation found
			 	 if(operations.get(i) instanceof com.ibm.wsdl.BindingOperationImpl){
					BindingInput input;
					
					if((input = ((com.ibm.wsdl.BindingOperationImpl)operations.get(i)).getBindingInput()) == null)
						break;
					List soapbodies = input.getExtensibilityElements();
					
					if(soapbodies!= null){
				 		for(int j =0; j <operations.size(); j++){
					 		if(soapbodies.get(i) instanceof com.ibm.wsdl.extensions.soap.SOAPBodyImpl){
								List encodings  = ((com.ibm.wsdl.extensions.soap.SOAPBodyImpl)soapbodies.get(j)).getEncodingStyles();
					 			if(encodings == null && encodings.size() > 0)
					 				this.encodingStyle = (String)encodings.get(0);
					 			break;
					 		}
				 		}
					}		
					break;	
			 	 }
				}
			 }		
				
           PortTypeEntry classinfo = tb.getPortTypeEntry(binding.getPortType().getQName());
         if (classinfo == null)
				throw new WrapperFault("Service not found");
			this.qualifiedServiceName = classinfo.getName();
        if(this.qualifiedServiceName == null){
            qualifiedServiceName = classinfo.getQName().getNamespaceURI();
            qualifiedServiceName = WrapperUtils.firstCharacterToLowercase(WrapperUtils.nsURI2packageName(qualifiedServiceName)) +"."+ classinfo.getQName().getLocalPart();
        	}
		return classinfo.getPortType();

    }

    /**
     * get Service data .. service data is given as the fully qualified names
     * When possible the user can have the schema QName if he like
     */

    private  ArrayList getServiceInfo(PortType porttype,String language){
        //get opeation list
        Iterator oplist = porttype.getOperations().iterator();
        ArrayList methods = new ArrayList();
        MethodInfo minfo;
        ParameterInfo pinfo;
        org.apache.axis.wsdl.symbolTable.Type ptype;
        //for each operation
        while (oplist.hasNext()) {

            minfo = new MethodInfo();
            methods.add(minfo);

            //add operation to operation List
            Operation op = (Operation) oplist.next();
            minfo.setMethodname(op.getName());

            Iterator paramlist =
                op.getInput().getMessage().getParts().values().iterator();
            //add each parameter to parameter list
            while (paramlist.hasNext()) {
                Part p = (Part) paramlist.next();
                ptype = tb.getType(p.getTypeName());
                pinfo = new ParameterInfo(ptype.getName(),ptype.getQName(),null,language);
                minfo.addParameter(p.getName(),pinfo);
            }

            //get the return type
            Iterator returnlist =
                op.getOutput().getMessage().getParts().values().iterator();
            if (returnlist.hasNext()){
                ptype = tb.getType(((Part) returnlist.next()).getTypeName());
                        minfo.setReturnType(new ParameterInfo(ptype.getName(),ptype.getQName(),null,language));
                }
        }
        return methods;
    }

	

    /**
     * This method extract the custom complex type info fom the symbol table
     * @return the type map with type info
     */
	private TypeMap getTypeInfo(String targetLanguage){
		Iterator it = tb.getTypeIndex().values().iterator();	
		TypeEntry type;
		Iterator elements;
		Type typedata;
		
		boolean hasElements; 
		while(it.hasNext()){
			type = (TypeEntry)it.next();
			Node node = type.getNode();
			if(node!= null){
				//get information about all the element declaration
				Vector elementsV = SchemaUtils.getContainedElementDeclarations(node,tb);

				if(elementsV!= null){
					elements = elementsV.iterator();
					typedata = new Type(type.getQName(),type.getName(),true,targetLanguage);
					hasElements = false;	
					
					//is this a SOAPEnc array type	
					QName arrayType = SchemaUtils.getArrayComponentQName(node,new IntHolder(0));
					if(arrayType !=  null){
						typedata.setTypeNameForAttribName("item",arrayType);
						System.out.println("ArrayType =" + arrayType);
						typedata.setArray(true);
					}else if((arrayType = SchemaUtils.getCollectionComponentQName(node)) !=  null){
							typedata.setTypeNameForAttribName("item",arrayType);
							typedata.setArray(true);
							System.out.println("ArrayType =" + arrayType);
					}else{
						while(elements.hasNext()){
							ElementDecl ed =(ElementDecl)elements.next();
							typedata.setTypeNameForAttribName(ed.getName().getLocalPart(),ed.getType().getQName());
				
							//see weather the type extend from SOAPEnc ArrayType
						/*	
						 //TODO this code fragement might not needed .... the unbound case of the arrray is
						 //not controlled by the SchemaUtils   top twoif conditions 
						    
						  
						 if(ed.getMaxoccurs()!= null){
								try{
									if(ed.getMaxoccurs().equals("unbound") || Integer.parseInt(ed.getMaxoccurs()) >1){
										if(hasElements)
											throw new WrapperFault("maxOccurs can not be with other element in complex type");
											//if maxOccurs is threre no way other element exit in the complextype (we are not support 
											// that type of combinations) 
											typedata.setArray(true);			
									}
								}catch(Exception e){
									// do nothing value is not unbound nor integer 
								}
							}*/
							
							//say now the type has elements
							if(!hasElements) hasElements = false;				
						}//end of elements it while
					}		
					//add the type to type map.
					System.out.println("############## the type found ="+type.getQName());
					typeMap.addType(type.getQName(),typedata);
					
				}
			}
		}//end of type while
		return typeMap;
	}//end of method
    
    
    
    
 /*   private TypeMap getTypeInfoR(){
      //get the type information
      Vector v = tb.getTypes();  //TODO remove the depricated method
      NodeList nl;
      Node t;
      Node node;
      NodeList params;
      TypeEntry entry;
      String name;
      //for each type in the WSDL file do ..
      for (int i = 0; i < v.size(); i++) {
         entry = (TypeEntry) v.get(i);
          //get the node element
            t = entry.getNode();

          //ignore the entries not relevent .. e.g.<element>
            if (t == null) continue;
                if(!t.getLocalName().equalsIgnoreCase(WrapperConstants.ELEMENT_COMPLEX_TYPE)){
                if(t.getLocalName().equalsIgnoreCase(WrapperConstants.ELEMENT_ELEMENT)){
                    TypeMap.setQnameTras(Utils.getTypeQName(t,new BooleanHolder(false),false),Utils.getNodeNameQName(t));
                }
                continue;
            }
            
			nl = ((Element) t).getElementsByTagName(WrapperConstants.ELEMENT_ELEMENT);
            if(nl != null && nl.getLength() != 0){
				//get child elements inside the complex type
				params = ((Element)t).getChildNodes();
            }else{
            	nl = ((Element) t).getElementsByTagName(WrapperConstants.ELEMENT_SEQUENCE);
            	if (nl == null || nl.getLength() != 0) {
               		nl = ((Element) t).getElementsByTagName(WrapperConstants.ELEMENT_ALL);
               		hasOrder = true;
               		if (nl == null || nl.getLength() != 0) {
               	    	//what todo?? ;
               		}
            	}
				params = nl.item(0).getChildNodes();
            } 	
         //create type ...
         org.apache.axis.wsdl.wsdl2ws.info.Type type =
               new org.apache.axis.wsdl.wsdl2ws.info.Type(entry.getQName(),entry.getName(),hasOrder);
         
         for (int j = 0; j < params.getLength(); j++) {
			//get child elements inside the complex type
         	node = params.item(j);
            if (!WrapperConstants.ELEMENT_ELEMENT.equals(node.getLocalName()))
               continue;
            name = node.getAttributes().getNamedItem(WrapperConstants.ATTRIBUTE_NAME).getNodeValue();

            QName typeqnameG = Utils.getTypeQName(node,new BooleanHolder(false),false);
            QName typeqname = TypeMap.getNameTrans(typeqnameG);
            if(typeqname == null)
              typeqname =typeqnameG;
              type.setTypeNameForAttribName(name, typeqname);
            }
            typeMap.addType(entry.getQName(),type);
       }
      return typeMap;
    }*/


	public void genarateWrappers(
		String servicename,
		String targetoutputLocation,
		String targetLanguage,
		String targetImplementationStyle,
        String targetEngine,
        String targetNameSpaceOfWSDL)
		throws WrapperFault {


        ArrayList methods = this.getServiceInfo(this.porttype,targetLanguage);
        TypeMap typeMap = this.getTypeInfo(targetLanguage);
		//TODO	chaeck weather the name at the WrapperConstant Doclit is right "doc"

		WebServiceGenarator wsg =
			WebServiceGenaratorFactory.createWebServiceGenarator(
				new WebServiceContext(
					new WrapperInfo(serviceStyle,targetLanguage,encodingStyle,
                                        targetoutputLocation,targetImplementationStyle,targetEngine,transportURI,targetEndpointURI,targetNameSpaceOfWSDL),
					new ServiceInfo(servicename,qualifiedServiceName,methods),
					typeMap));
		if (wsg == null)
			throw new WrapperFault("does not support the option combination");
		wsg.genarate();

	}

	/**
	 * Usage
	 * =====
	 * java WSDL2ws <wsdlfile> <serviceuri> <serviceLocalpart> -<optionChar><value>
	 * 
	 * Options and Values 
	 * ======= === ======
	 * -o target output folder
	 * -l target language(c|java|c++) default is java
	 * -h help (later ???? not emplemented)
	 * -i implementation style (struct|order|simple) default is struct--- (usergetvalue() with PP or use getTag() ect ....)
     * -s (client|server)  default is server
     * 
     * Note:  PP - pull parser
	 * @param args
	 * @throws Exception
	 */

	public static void main(String[] args) throws Exception {
		CLArgParser data = new CLArgParser(args);
		System.out.println(data.getArgumentCount());
		if (data.getArgumentCount() != 3)
			System.out.println(
				"usage WSDL2Wrapper <wsdlfile> <uri> <localpart> -o <target output folder> -p <target output package>");
		else {
			WSDL2Ws gen = new WSDL2Ws(data);
			gen.genarateWrappers(
				args[2],
				data.getOptionBykey("o"),
				data.getOptionBykey("l"),
				data.getOptionBykey("i"),
                data.getOptionBykey("s"),
                args[1]);
		}
	}
}
