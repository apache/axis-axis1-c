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

 
/**
 * @author Srinath Perera(hemapani@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws.cpp.literal;

import java.io.File;
import java.io.IOException;
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

/**
 * Genarate a webservice for the complex types likes structs.
 * @author hemapani
 */

public class BeanParamWriter extends ParamCPPFileWriter{
	public BeanParamWriter(WebServiceContext wscontext,Type type)throws WrapperFault{
		super(wscontext,type);
	}
	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.ParamCPPFileWriter#writeGlobalCodes()
	 */
	protected void writeGlobalCodes()throws WrapperFault{
		try{
		HashSet typeSet = new HashSet();
		String typeName;
		for(int i = 0; i< attribs.length;i++){
			if(!(attribs[i].isSimpleType() || attribs[i].isAnyType())){
				typeSet.add(attribs[i].getTypeName());
			}
		}
		Iterator itr = typeSet.iterator();
		while(itr.hasNext())
		{
			/*
			 * Needed for self referenced  array.
			* <xsd:complexType name="Type1">
			*	<xsd:sequence>
			*		<xsd:element name="followings" maxOccurs="unbounded" minOccurs="0" type="tns:Type1" />
			*		<xsd:element name="kind" type="xsd:string" />
			*		<xsd:element name="index" type="xsd:int" />
			*	</xsd:sequence>
			*	<xsd:attribute name="att_kind" type="tns:Kind" />
			* </xsd:complexType>
			*/
			typeName = itr.next().toString();
			if ( ! typeName.equals(type.getName().getLocalPart())) {
				writer.write("extern int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer* pDZ);\n");
				writer.write("extern void* Axis_Create_"+typeName+"("+typeName+"* pObj, bool bArray = false, int nSize=0);\n");
				writer.write("extern void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray = false, int nSize=0);\n");
				writer.write("extern int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer* pSZ, bool bArray = false);\n");
				writer.write("extern int Axis_GetSize_"+typeName+"();\n\n");
			} else {
				writer.write("int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer* pDZ);\n");
				writer.write("void* Axis_Create_"+typeName+"("+typeName+"* pObj, bool bArray, int nSize);\n");
				writer.write("void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray, int nSize);\n");
				writer.write("int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer* pSZ, bool bArray);\n");
				writer.write("int Axis_GetSize_"+typeName+"();\n\n");
			}	
		}
		writeSerializeGlobalMethod();
		writeDeSerializeGlobalMethod();
		writeCreateGlobalMethod();
		writeDeleteGlobalMethod();
		writeGetSizeGlobalMethod();
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}
	private void writeGetSizeGlobalMethod() throws IOException{
		writer.write("/*\n");
		writer.write(" * This static method gives the size of "+classname+" type of object\n");
		writer.write(" */\n");
		writer.write("int Axis_GetSize_"+classname+"()\n{\n\treturn sizeof("+classname+");\n}\n");
	}
	private void writeSerializeGlobalMethod()throws IOException,WrapperFault{
		writer.write("/*\n");
		writer.write(" * This static method serialize a "+classname+" type of object\n");
		writer.write(" */\n");
		writer.write("int Axis_Serialize_"+classname+"("+classname+"* param, IWrapperSoapSerializer* pSZ, bool bArray = false)\n{\n");
		if (attribs.length == 0) {
			writer.write("\tpSZ->serialize(\">\", NULL);\n");
			if (extensionBaseAttrib != null){
				writer.write("\tpSZ->serializeAsChardata((void*)&(param->"+extensionBaseAttrib.getParamName()+"), "+CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName())+");\n");
			}else{
				System.out.println("Possible error in class "  + classname + ": class with no attributes....................");
			}
			writer.write("\treturn AXIS_SUCCESS;\n");
			writer.write("}\n\n");				 
			return;
		}
		String arrayType;
		/* A type does not know whether it is used as a nillable parameter 
		 * So this may not be the appropriate place to do this
		 */
		writer.write("\tif ( param == NULL ) {\n");
		writer.write("\t /* TODO : may need to check nillable value*/\n"); 
		//writer.write("\t pSZ->serializeAsAttribute(\"nil\", \"http://www.w3.org/2001/XMLSchema-instance\", (void*)&(xsd_boolean_true), XSD_BOOLEAN);\n");
		writer.write("\tpSZ->serializeAsAttribute(\"xsi:nil\", 0, (void*)&(xsd_boolean_true), XSD_BOOLEAN);\n");
		writer.write("\t pSZ->serialize(\">\", NULL);\n");
		writer.write("\treturn AXIS_SUCCESS;\n");
		writer.write("\t}\n");
		writer.write("\t/* first serialize attributes if any*/\n");
		for(int i = 0; i< attributeParamCount;i++){
			if(attribs[i].isArray() || !(attribs[i].isSimpleType())){
				throw new WrapperFault("Error : an attribute is not basic type");
			}
			else{
				//Samisa
				//remove _Ref sufix and _ prefix in SOAP tag name
				String soapTagName = attribs[i].getParamName();
				if( soapTagName.lastIndexOf("_Ref") > -1 )
					soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref") );
				if( soapTagName.charAt(0) == '_' )
					soapTagName = soapTagName.substring(1, soapTagName.length() );
				//end remove _Ref sufix and _ prefix in SOAP tag name
				writer.write("\tif (0 != param->"+attribs[i].getParamName()+")\n");
				//writer.write("\t\tpSZ->serializeAsAttribute(\""+attribs[i].getParamName()+"\", 0, (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");				
				writer.write("\t\tpSZ->serializeAsAttribute(\""+ soapTagName +"\", 0, (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");				
				if (!attribs[i].isOptional()){
					/* This avoid segmentation fault at runtime */
					/*writer.write("\telse\n");
					writer.write("\t\tAXISTRACE1(\"The mandatory attribute "+attribs[i].getParamName()+" is not set\", CRITICAL);\n");*/
				}
			}
		}
		writer.write("\tpSZ->serialize(\">\", 0);\n");
		if (extensionBaseAttrib != null && extensionBaseAttrib.getTypeName() != null){
			writer.write("\tpSZ->serializeAsChardata((void*)&(param->"+extensionBaseAttrib.getParamName()+"), "+CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName())+");\n");
		}
		writer.write("\t/* then serialize elements if any*/\n");
		for(int i = attributeParamCount; i< attribs.length;i++){
			if(attribs[i].isAnyType()){
				writer.write("\tpSZ->serializeAnyObject(param->any);\n");
			}
			else if(attribs[i].isArray()){
				//if Array
				if (attribs[i].isSimpleType()){
					writer.write("\tpSZ->serializeBasicArray((Axis_Array*)(&param->"+attribs[i].getParamName()+"),"+CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+", \""+attribs[i].getParamName()+"\");\n"); 
				}
				else{
					arrayType = attribs[i].getTypeName();
					writer.write("\tpSZ->serializeCmplxArray((Axis_Array*)(&param->"+attribs[i].getParamName()+"),\n"); 
					writer.write("\t\t(void*) Axis_Serialize_"+arrayType+", (void*) Axis_Delete_"+arrayType+", (void*) Axis_GetSize_"+arrayType+",\n");
					//writer.write("\t\t\""+attribs[i].getElementName().getLocalPart()+"\", Axis_URI_"+arrayType+");\n");
					writer.write("\t\t\""+attribs[i].getElementNameAsString()+"\", Axis_URI_"+arrayType+");\n");
				}
			}
			else if (attribs[i].isSimpleType()){
				//writer.write("\tpSZ->serializeAsElement(\""+attribs[i].getElementName().getLocalPart()+"\", (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
				//Samisa 22/08/2004
				writer.write("\tpSZ->serializeAsElement(\""+attribs[i].getElementNameAsString()+"\", (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
				//Samisa
			}else{
				//if complex type
				String elm = attribs[i].getParamName();
				if ( attribs[i].isReference() )
					elm = attribs[i].getTypeName();
				writer.write("\tpSZ->serialize(\"<"+elm+"\", 0);\n");
				writer.write("\tAxis_Serialize_"+attribs[i].getTypeName()+"(param->"+attribs[i].getParamName()+", pSZ);\n");
				writer.write("\tpSZ->serialize(\"</"+elm+">\", 0);\n");
			}
		}
		writer.write("\treturn AXIS_SUCCESS;\n");
		writer.write("}\n\n");
	}
	private void writeDeSerializeGlobalMethod()throws IOException,WrapperFault{	
		writer.write("/*\n");
		writer.write(" * This static method deserialize a "+classname+" type of object\n");
		writer.write(" */\n");		
		writer.write("int Axis_DeSerialize_"+classname+"("+classname+"* param, IWrapperSoapDeSerializer* pIWSDZ)\n{\n");
		if (attribs.length == 0) {
			if (extensionBaseAttrib != null){
				writer.write("\tpIWSDZ->getChardataAs((void*)&(param->"+extensionBaseAttrib.getParamName()+"), "+CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName())+");\n");
			}else{
				System.out.println("Possible error in class "  + classname + ": class with no attributes....................");
			}
			writer.write("\treturn AXIS_SUCCESS;\n");
			writer.write("}\n\n");
			return;
		 }
		 String arrayType = null;
		/* Needed for Aix xlc */
		for(int i = 0; i< attribs.length;i++){
			if(attribs[i].isArray()) {
				writer.write("\tAxis_Array array;\n");
				break;
			}
		}			
		for(int i = 0; i< attribs.length;i++){
			if(attribs[i].isAnyType()){
				writer.write("\tparam->any = pIWSDZ->getAnyObject();\n");
			}
			else if(attribs[i].isArray()){
				//if Array
				if (attribs[i].isSimpleType()){
					writer.write("\tarray = pIWSDZ->getBasicArray("+CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+ ", \""+attribs[i].getParamName()+"\",0);\n");
					writer.write("\tparam->"+attribs[i].getParamName()+" = ("+CUtils.getBasicArrayNameforType(attribs[i].getTypeName())+"&)array;\n");					
				}
				else{
					arrayType = attribs[i].getTypeName();
					writer.write("\tarray = pIWSDZ->getCmplxArray((void*)Axis_DeSerialize_"+arrayType+ 
						"\n\t\t, (void*)Axis_Create_"+arrayType+", (void*)Axis_Delete_"+arrayType+
					//	"\n\t\t, (void*)Axis_GetSize_"+arrayType+", \""+attribs[i].getElementName().getLocalPart()+"\", Axis_URI_"+arrayType+");\n");
						"\n\t\t, (void*)Axis_GetSize_"+arrayType+", \""+attribs[i].getElementNameAsString()+"\", Axis_URI_"+arrayType+");\n");
					writer.write("\tparam->"+attribs[i].getParamName()+" = ("+attribs[i].getTypeName()+"_Array&)array;\n");	
				}
			}else if(attribs[i].isSimpleType()){
				//TODO handle optional attributes
				//Samisa
				//remove _Ref sufix and _ prefix in SOAP tag name
				String soapTagName = (attribs[i].isAttribute() ? attribs[i].getParamName():attribs[i].getElementNameAsString());
				if( soapTagName.lastIndexOf("_Ref") > -1 )
					soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref") );
				if( soapTagName.charAt(0) == '_' )
					soapTagName = soapTagName.substring(1, soapTagName.length() );
				//end remove _Ref sufix and _ prefix in SOAP tag name
				writer.write("\tparam->"+attribs[i].getParamName()+" = pIWSDZ->"+CUtils.getParameterGetValueMethodName(attribs[i].getTypeName(), attribs[i].isAttribute())+"(\""+ soapTagName +"\",0);\n");
				//Samisa
			} else{
				//if complex type
				//Samisa
				//remove _Ref sufix and _ prefix in SOAP tag name
				String soapTagName = attribs[i].getParamName();
				if( soapTagName.lastIndexOf("_Ref") > -1 )
					soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref") );
				if( soapTagName.charAt(0) == '_' )
					soapTagName = soapTagName.substring(1, soapTagName.length() );
				//end remove _Ref sufix and _ prefix in SOAP tag name
				writer.write("\tparam->"+attribs[i].getParamName()+" = ("+attribs[i].getTypeName()+"*)pIWSDZ->getCmplxObject((void*)Axis_DeSerialize_"+attribs[i].getTypeName()+
					"\n\t\t, (void*)Axis_Create_"+attribs[i].getTypeName()+", (void*)Axis_Delete_"+attribs[i].getTypeName()+
					"\n\t\t, \""+ soapTagName +"\", Axis_URI_"+attribs[i].getTypeName()+");\n");				
			}		
		}
		if (extensionBaseAttrib != null && extensionBaseAttrib.getTypeName() != null){
			writer.write("\tpIWSDZ->getChardataAs((void*)&(param->"+extensionBaseAttrib.getParamName()+"), "+CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName())+");\n");
		}
		writer.write("\treturn pIWSDZ->getStatus();\n");
		writer.write("}\n");
	}
	
	private void writeCreateGlobalMethod()throws IOException{
		writer.write("void* Axis_Create_"+classname+"("+classname+"* pObj, bool bArray = false, int nSize=0)\n{\n");
		writer.write("\tif (bArray && (nSize > 0))\n\t{\n\t\tif (pObj)\n\t\t{\n");
		writer.write("\t\t\t"+classname+"* pNew = new "+classname+"[nSize];\n");
		writer.write("\t\t\tmemcpy(pNew, pObj, sizeof("+classname+")*nSize/2);\n");
		writer.write("\t\t\tmemset(pObj, 0, sizeof("+classname+")*nSize/2);\n");
		writer.write("\t\t\tdelete [] pObj;\n");
		writer.write("\t\t\treturn pNew;\n\t\t}\n\t\telse\n\t\t{\n");
		writer.write("\t\t\treturn new "+classname+"[nSize];\n\t\t}\n\t}\n");
		writer.write("\telse\n\t\treturn new "+classname+";\n}\n\n");
	}
	private void writeDeleteGlobalMethod()throws IOException{
		writer.write("/*\n");
		writer.write(" * This static method delete a "+classname+" type of object\n");
		writer.write(" */\n");		
		writer.write("void Axis_Delete_"+classname+"("+classname+"* param, bool bArray = false, int nSize=0)\n");
		writer.write("{\n");
		writer.write("\tif (bArray)\n");
		writer.write("\t{\n");
		writer.write("\t\tdelete [] param;\n");
		writer.write("\t}\n");
		writer.write("\telse\n");
		writer.write("\t{\n");
		writer.write("\t\tdelete param;\n");
		writer.write("\t}\n");
		writer.write("}\n");
	}
	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeConstructors()
	 */
	protected void writeConstructors() throws WrapperFault {
		try{
		writer.write("\n"+classname+"::"+classname+"()\n{\n");
		writer.write("\t/*do not allocate memory to any pointer members here\n\t because deserializer will allocate memory anyway. */\n");
		for(int i = 0; i< attribs.length;i++){
			if (attribs[i].isArray()){
				writer.write("\t"+attribs[i].getParamName()+".m_Array = 0;\n");
				writer.write("\t"+attribs[i].getParamName()+".m_Size = 0;\n");
			}
			else if (!attribs[i].isSimpleType()){
				writer.write("\t"+attribs[i].getParamName()+"=0;\n");
			} else {
				/* Needed for shared libraries */
				   writer.write("\tmemset( &" + attribs[i].getParamName() + ", 0, sizeof( " + attribs[i].getTypeName() + "));\n");
//FJP				if ("xsd__string".equals(attribs[i].getTypeName()))
//FJP				   writer.write("\t"+attribs[i].getParamName()+" = 0;\n");
			}
		}			
		writer.write("}\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
	 */
	protected void writeDistructors() throws WrapperFault {
		try{
		writer.write("\n"+classname+"::~"+classname+"()\n{\n");
		writer.write("\t/*delete any pointer and array members here*/\n");
		for(int i = 0; i< attribs.length;i++){
			if(attribs[i].isArray()){
				writer.write("\tdelete [] (("+attribs[i].getTypeName()+"*)"+attribs[i].getParamName()+".m_Array);\n");
			}
			else if (attribs[i].isAnyType()){
				writer.write("\tif ("+attribs[i].getParamName()+") \n\t{ \n");
				writer.write("\t\tfor (int i=0; i<"+attribs[i].getParamName()+"->_size; i++)\n\t\t{\n");
				writer.write("\t\t\tif ("+attribs[i].getParamName()+"->_array[i]) free("+attribs[i].getParamName()+"->_array[i]);\n");
				writer.write("\t\t}\n");
				writer.write("\t\tfree("+attribs[i].getParamName()+");\n");
				writer.write("\t}\n");
				
			}
			else if (!attribs[i].isSimpleType()){
				writer.write("\tdelete "+attribs[i].getParamName()+";\n");				
			}
		}			
		writer.write("}\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}	
	protected void writeRestrictionCheckerFunction() throws WrapperFault {
		try{
			writer.write("int Check_Restrictions_"+classname+"("+classname+" value)\n");
			writer.write("{\n");
			writer.write("\treturn 0;\n");			
			//TODO write code to check the restrictions
			writer.write("}\n");					
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}	
	protected File getFilePath(boolean useServiceName) throws WrapperFault {
		
		return null;
	}
}
