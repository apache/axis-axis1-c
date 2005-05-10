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
	private void writeSerializeGlobalMethod()throws IOException, WrapperFault
	{
		writer.write("/*\n");
		writer.write(" * This static method serialize a "+classname+" type of object\n");
		writer.write(" */\n");
		writer.write("int Axis_Serialize_"+classname+"("+classname+"* param, IWrapperSoapSerializer* pSZ, bool bArray = false)\n{\n");
		
		if (attribs.length == 0)
		{
			writer.write("\tpSZ->serialize(\">\", NULL);\n");
			
			if (extensionBaseAttrib != null)
			{
				writer.write("\tpSZ->serializeAsChardata((void*)&(param->"+extensionBaseAttrib.getParamNameAsMember()+"), "+CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName())+");\n");
			}
			else
			{
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
		writer.write("\tif ( param == NULL )\n\t{\n");
		writer.write("\t /* TODO : may need to check nillable value - Now done*/\n"); 
		writer.write("\t\tpSZ->serializeAsAttribute( \"xsi:nil\", 0, (void*)&(xsd_boolean_true), XSD_BOOLEAN);\n");
		writer.write("\t\tpSZ->serialize( \">\", NULL);\n");
		writer.write("\t\treturn AXIS_SUCCESS;\n");
		writer.write("\t}\n\n");
		
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
				if (attribs[i].getTypeName().equals("xsd__string")
 						|| attribs[i].getTypeName().equals("xsd__anyURI")
						|| attribs[i].getTypeName().equals("xsd__QName")
						|| attribs[i].getTypeName().equals("xsd__notation"))
				{
					writer.write("\tif (0 != param->"+attribs[i].getParamNameAsMember()+")\n");
					writer.write("\t\tpSZ->serializeAsAttribute(\""+ soapTagName +"\", 0, (void*)(param->"+attribs[i].getParamNameAsMember()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
				}
				else
				{
					writer.write("\t\tpSZ->serializeAsAttribute(\""+ soapTagName +"\", 0, (void*)&(param->"+attribs[i].getParamNameAsMember()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
				}
				if (!attribs[i].isOptional()){
					/* This avoid segmentation fault at runtime */
					/*writer.write("\telse\n");
					writer.write("\t\tAXISTRACE1(\"The mandatory attribute "+attribs[i].getParamName()+" is not set\", CRITICAL);\n");*/
				}
			}
		}
		writer.write("\tpSZ->serialize( \">\", 0);\n");
		if (extensionBaseAttrib != null && extensionBaseAttrib.getTypeName() != null){
			writer.write("\tpSZ->serializeAsChardata((void*)&(param->"+extensionBaseAttrib.getParamNameAsMember()+"), "+CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName())+");\n");
		}
		
		writer.write("\n\t/* then serialize elements if any*/\n");
		for(int i = attributeParamCount; i< attribs.length;i++){
	
			//Dushshantha:
			//if the attribute is a choice 
			//following should do
			
			if(attribs[i].getChoiceElement())
			{
				writer.write("\tif(param->" + attribs[i].getParamNameAsMember()+ ")\n\t{\n\t");
			}
			//..............................................................................



			if(attribs[i].isAnyType())
			{
				writer.write("\tpSZ->serializeAnyObject(param->any);\n");
			}
			else if(attribs[i].isArray()){
				//if Array
				if (attribs[i].isSimpleType()){
 					//writer.write("\tpSZ->serializeBasicArray((Axis_Array*)(&param->"+attribs[i].getParamNameAsMember()+"),"+CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+", \""+attribs[i].getParamName()+"\");\n");
 					// cblecken 17/01/2005
									
					
					/**
					 *Dushshantha:
					 *If the element is a Choice,
					 *It should be treated as a pointer to an array. 
					 */
					
					if(attribs[i].getChoiceElement())
						writer.write("\tpSZ->serializeBasicArray((Axis_Array*)(param->"+attribs[i].getParamName()+"), Axis_URI_" + classname + ","+CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+", \""+attribs[i].getParamNameAsSOAPElement()+"\");\n"); 
					else
						writer.write("\tpSZ->serializeBasicArray((Axis_Array*)(&param->"+attribs[i].getParamName()+"), Axis_URI_" + classname + ","+CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+", \""+attribs[i].getParamNameAsSOAPElement()+"\");\n"); 
				}
				else
				{
					Iterator	itForTypes = wscontext.getTypemap().getTypes().iterator();
					boolean		nillable = isNillable();
					boolean		moreThanOne = isMoreThanOne();

					arrayType = attribs[i].getTypeName();
					writer.write("\t// Additional code to find is reference is pointer or pointer to a pointer\n");
					
					if( nillable)
					{
						writer.write("\tAxis_Array\tsAA"+i+";\n\n");
						writer.write("\tsAA"+i+".m_Size = 1;\n\n");
						
						if( moreThanOne)
						{
							writer.write("\tfor( int iCount"+i+" = 0; iCount"+i+" < param->count; iCount"+i+"++)\n");
						}
						else
						{
							writer.write("\tfor( int iCount"+i+" = 0; iCount"+i+" < param->" + attribs[i].getParamName() + ".m_Size; iCount"+i+"++)\n");
						}

						writer.write("\t{\n");
						
						if( moreThanOne)
						{
							writer.write("\t\tif( param->infos.m_Array[iCount"+i+"] == NULL)\n");
						}
						else
						{
							writer.write("\t\tif( param->" + attribs[i].getParamName() + ".m_Array[iCount"+i+"] == NULL)\n");
						}
						
						writer.write("\t\t{\n");
						writer.write("\t\t\tpSZ->serializeAsAttribute( \"<" + attribs[i].getParamName() +" xsi:nil\", 0, (void*)&(xsd_boolean_true), XSD_BOOLEAN);\n");
						writer.write("\t\t\tpSZ->serialize( \"/>\", NULL);\n");
						writer.write("\t\t}\n");
						writer.write("\t\telse\n");
						writer.write("\t\t{\n");

						if( moreThanOne)
						{
							writer.write("\t\t\tsAA"+i+".m_Array = (void **)param->infos.m_Array[iCount"+i+"];\n");
						}
						else
						{
							writer.write("\t\t\tsAA"+i+".m_Array = param->" + attribs[i].getParamName() + ".m_Array[iCount"+i+"];\n\n");
						}

						writer.write("\t\t\tpSZ->serializeCmplxArray( &sAA"+i+",\n");
						writer.write("\t\t\t\t\t\t\t\t\t (void*) Axis_Serialize_"+arrayType+",\n");
						writer.write("\t\t\t\t\t\t\t\t\t (void*) Axis_Delete_"+arrayType+",\n");
						writer.write("\t\t\t\t\t\t\t\t\t (void*) Axis_GetSize_"+arrayType+",\n");
						writer.write("\t\t\t\t\t\t\t\t\t \""+attribs[i].getParamName()+"\", Axis_URI_"+arrayType+");\n");
						writer.write("\t\t}\n");
						writer.write("\t}\n");
					}
					else
					{
						writer.write("\tpSZ->serializeCmplxArray((Axis_Array*)(&param->"+attribs[i].getParamNameAsMember()+"),\n"); 
						writer.write("\t\t\t\t\t\t (void*) Axis_Serialize_"+arrayType+",\n");
						writer.write("\t\t\t\t\t\t (void*) Axis_Delete_"+arrayType+",\n");
						writer.write("\t\t\t\t\t\t (void*) Axis_GetSize_"+arrayType+",\n");
						writer.write("\t\t\t\t\t\t \""+attribs[i].getParamName()+"\", Axis_URI_"+arrayType+");\n");
					}
					
					writer.write("\t// End\n");
				}
			}
			else if (attribs[i].isSimpleType()){
				//writer.write("\tpSZ->serializeAsElement(\""+attribs[i].getElementName().getLocalPart()+"\", (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
				//Samisa 22/08/2004
 				// writer.write("\tpSZ->serializeAsElement( \""+attribs[i].getElementNameAsString()+"\", (void*)&(param->"+attribs[i].getParamNameAsMember()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
 				// cblecken 17/01/2005
 				if (attribs[i].getTypeName().equals("xsd__string")
 						|| attribs[i].getTypeName().equals("xsd__anyURI")
						|| attribs[i].getTypeName().equals("xsd__QName")
						|| attribs[i].getTypeName().equals("xsd__notation"))
 				{
 					writer.write("\tpSZ->serializeAsElement(\""+attribs[i].getSOAPElementNameAsString()+"\", Axis_URI_" + classname + ", (void*)(param->"+attribs[i].getParamNameWithoutSymbols()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");	
 				}
 				else
 				{
 				/**
 				  * Dushshantha:
 				  * If the simple type is a choice 
 				  * it is handled as a pointer variable.
 				  * These variables should be defined as pointers in the header file.
 				  */
 				 					
 					if(attribs[i].getChoiceElement())
 						writer.write("\tpSZ->serializeAsElement(\""+attribs[i].getSOAPElementNameAsString()+"\", Axis_URI_" + classname + ", (void*)(param->"+attribs[i].getParamNameWithoutSymbols()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
 					else
 						writer.write("\tpSZ->serializeAsElement(\""+attribs[i].getSOAPElementNameAsString()+"\", Axis_URI_" + classname + ", (void*)&(param->"+attribs[i].getParamNameWithoutSymbols()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");	
 				}
 
			}else{
				//if complex type
				String elm = attribs[i].getParamName();
				if ( attribs[i].isReference() )
					elm = attribs[i].getTypeName();
 				//writer.write("\tpSZ->serialize(\"<"+elm+"\", 0);\n");
 				//writer.write("\tAxis_Serialize_"+attribs[i].getTypeName()+"(param->"+attribs[i].getParamNameAsMember()+", pSZ);\n");
 				//writer.write("\tpSZ->serialize(\"</"+elm+">\", 0);\n");
                 writer.write("\tpSZ->serialize(\"<\", pSZ->getNamespacePrefix(\"" + type.getName().getNamespaceURI() + "\"), \":\", \""+elm+"\", 0);\n");
                 writer.write("\tAxis_Serialize_"+attribs[i].getTypeName()+"(param->"+attribs[i].getParamName()+", pSZ);\n");
                 writer.write("\tpSZ->serialize(\"</\", pSZ->getNamespacePrefix(\"" + type.getName().getNamespaceURI() + "\"), \":\", \""+elm+"\", \">\", 0);\n");

		
			}
			//Dushshantha:
			//end if choice element
			
			if(attribs[i].getChoiceElement())
				writer.write("\t}\n");
		
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
				writer.write("\tpIWSDZ->getChardataAs((void*)&(param->"+extensionBaseAttrib.getParamNameAsMember()+"), "+CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName())+");\n");
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
				writer.write("\tAxis_Array array;\n\n");
				break;
			}
		}			
		
		
		boolean peekCalled=false;
        
		for (int i = 0; i < attribs.length; i++)
		{
			//Dushshantha:
			//if the attribute is a 'choice' construct we have to peek and make the choice
        	        	
			if(attribs[i].getChoiceElement())
			{
				if(!peekCalled)
				{
					writer.write("\tconst char* choiceName=pIWSDZ->peekNextElementName();\n");
					peekCalled=true;
				}
				
				writer.write("\tif(strcmp(choiceName,\"" + attribs[i].getParamNameAsMember()+ "\")==0)\n\t{\n\t");
								           	           	
			}
			//.............................................
			if( attribs[i].isAnyType())
			{
				writer.write("\tparam->any = pIWSDZ->getAnyObject();\n");
			}
			else if( attribs[i].isArray())
			{
				//if Array
				if ( attribs[i].isSimpleType())
				{
					writer.write("\tarray = pIWSDZ->getBasicArray("+CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+ ", \""+attribs[i].getParamNameAsSOAPElement()+"\",0);\n");
//					writer.write("\tparam->"+attribs[i].getParamNameAsMember()+" = ("+CUtils.getBasicArrayNameforType(attribs[i].getTypeName())+"&)array;\n");
					String typename = attribs[i].getTypeName();
					if (typename.equals("xsd__string")
							|| typename.equals("xsd__anyURI")
							|| typename.equals("xsd__QName")
							|| typename.equals("xsd__notation")
							|| typename.equals("xsd__NMTOKEN"))
					{
						writer.write("\tparam->"+attribs[i].getParamNameAsMember()+".m_Array = ("+attribs[i].getTypeName()+"*)new "+attribs[i].getTypeName()+"[array.m_Size];\n");
					}
					else
					{
						
						/**
						 *Dushshantha:
						 *If the element is a Choice,
						 *It should be treated as a pointer to an array. 
						 */
						
						if(attribs[i].getChoiceElement())
							writer.write("\tparam->"+attribs[i].getParamNameAsMember()+"->m_Array = ("+attribs[i].getTypeName()+"**)new "+attribs[i].getTypeName()+"*[array.m_Size];\n");
						else
							writer.write("\tparam->"+attribs[i].getParamNameAsMember()+".m_Array = ("+attribs[i].getTypeName()+"**)new "+attribs[i].getTypeName()+"*[array.m_Size];\n");
					}
					
					/**
					 *Dushshantha:
					 *If the element is a Choice,
					 *It should be treated as a pointer to an array. 
					 */
					
					if(attribs[i].getChoiceElement()){
						writer.write("\tparam->"+attribs[i].getParamNameAsMember()+"->m_Size = array.m_Size;\n\n");
						writer.write("\tmemcpy( param->"+attribs[i].getParamNameAsMember()+"->m_Array, array.m_Array, sizeof( "+attribs[i].getTypeName()+") * array.m_Size);\n");
					}
					else{
						writer.write("\tparam->"+attribs[i].getParamNameAsMember()+".m_Size = array.m_Size;\n\n");
						writer.write("\tmemcpy( param->"+attribs[i].getParamNameAsMember()+".m_Array, array.m_Array, sizeof( "+attribs[i].getTypeName()+") * array.m_Size);\n");
					}
									
				}
				else
				{
					Iterator	itForTypes = wscontext.getTypemap().getTypes().iterator();
					boolean		nillable = isNillable();
					boolean		moreThanOne = isMoreThanOne();

					arrayType = attribs[i].getTypeName();
					writer.write("\tarray = pIWSDZ->getCmplxArray((void*)Axis_DeSerialize_"+arrayType+",\n"+ 
								 "\t\t\t\t\t\t\t\t  (void*)Axis_Create_"+arrayType+",\n"+
								 "\t\t\t\t\t\t\t\t  (void*)Axis_Delete_"+arrayType+",\n"+
								 "\t\t\t\t\t\t\t\t  (void*)Axis_GetSize_"+arrayType+",\n"+
								 "\t\t\t\t\t\t\t\t  \""+attribs[i].getElementNameAsString()+"\", Axis_URI_"+arrayType+");\n\n");
					writer.write("\t// Additional code to find is reference is pointer or pointer to a pointer\n");

					if( nillable)
					{
						String attributeParamName = attribs[i].getParamName();
						String attributeTypeName = attribs[i].getTypeName();
						writer.write("\t"+attributeTypeName+" **	pp"+i+" = param->"+attributeParamName+".m_Array;\n\n");
						writer.write("\tparam->"+attributeParamName+".m_Size = array.m_Size;\n\n");
						writer.write("\tif( param->"+attributeParamName+".m_Array == NULL)\n");
						writer.write("\t{\n");
						writer.write("\t\tpp"+i+" = new "+attributeTypeName+"*[array.m_Size];\n");
						writer.write("\t\tparam->"+attributeParamName+".m_Array = pp"+i+";\n");
						writer.write("\t}\n\n");
						writer.write("\t"+attributeTypeName+" *	p"+i+" = ("+attributeTypeName+" *) array.m_Array;\n\n");
						writer.write("\tfor( int iCount"+i+" = 0; iCount"+i+" < array.m_Size; iCount"+i+"++)\n");
						writer.write("\t{\n");
						writer.write("\t\tpp"+i+"[iCount"+i+"] = new "+attributeTypeName+"();\n");
						writer.write("\t\t*(pp"+i+"[iCount"+i+"]) = p"+i+"[iCount"+i+"];\n");
						writer.write("\t}\n");
						writer.write("\tdelete [] p"+i+";\n");
					}
					else
					{
						writer.write("\tparam->"+attribs[i].getParamNameAsMember()+" = ("+attribs[i].getTypeName()+"_Array&)array;\n");	
					}
					
					writer.write("\t// End\n");
				}
			}
			else if(attribs[i].isSimpleType())
			{
				//TODO handle optional attributes
				//Samisa
				//remove _Ref sufix and _ prefix in SOAP tag name
				String soapTagName = (attribs[i].isAttribute() ? attribs[i].getParamName():attribs[i].getElementNameAsString());
				if( soapTagName.lastIndexOf("_Ref") > -1 )
				{
					soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref") );
				}
				
				if( soapTagName.charAt(0) == '_' )
				{
					soapTagName = soapTagName.substring(1, soapTagName.length() );
				}
				//end remove _Ref sufix and _ prefix in SOAP tag name
				if (attribs[i].isNillable()
						|| attribs[i].getTypeName().equals("xsd__string")
						|| attribs[i].getTypeName().equals("xsd__anyURI")
						|| attribs[i].getTypeName().equals("xsd__QName")
						|| attribs[i].getTypeName().equals("xsd__NMTOKEN")
						|| attribs[i].getTypeName().equals("xsd__notation"))				{
					writer.write("\tparam->"+attribs[i].getParamNameAsMember()+" = pIWSDZ->"+CUtils.getParameterGetValueMethodName(attribs[i].getTypeName(), attribs[i].isAttribute())+"( \""+ soapTagName +"\",0);\n");
					//Samisa
				}
				else
				{
			    /**
			      * Dushshantha:
			      * If the simple type is a choice 
			      * it is handled as a pointer variable.
			      * These variables should be defined as pointers in the header file.
			      */
					if(attribs[i].getChoiceElement())
						writer.write("\tparam->"+attribs[i].getParamNameAsMember()+" = pIWSDZ->"+CUtils.getParameterGetValueMethodName(attribs[i].getTypeName(), attribs[i].isAttribute())+"( \""+ soapTagName +"\",0);\n");
					else{	
						writer.write("\t" + attribs[i].getTypeName() + " * " + attribs[i].getParamNameAsMember()+ " = NULL;\n");
						writer.write("\tif ((" + attribs[i].getParamNameAsMember()+ " = pIWSDZ->"+CUtils.getParameterGetValueMethodName(attribs[i].getTypeName(), attribs[i].isAttribute())+"( \""+ soapTagName +"\",0)) != NULL)\n");
						writer.write("\t\tparam->"+attribs[i].getParamNameAsMember()+" = *( " + attribs[i].getParamNameAsMember()+" );\n");
//                                        writer.write("\t\tdelete " + attribs[i].getParamNameAsMember()+";\n");
					}
				}
			}
			else
			{
				//if complex type
				//Samisa
				//remove _Ref sufix and _ prefix in SOAP tag name
				String soapTagName = attribs[i].getParamName();
				
				if( soapTagName.lastIndexOf("_Ref") > -1 )
				{
					soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref") );
				}
				
				if( soapTagName.charAt(0) == '_' )
				{
					soapTagName = soapTagName.substring(1, soapTagName.length() );
				}
				
				//end remove _Ref sufix and _ prefix in SOAP tag name
				writer.write("\tparam->"+attribs[i].getParamNameAsMember()+" = ("+attribs[i].getTypeName()+"*)pIWSDZ->getCmplxObject((void*)Axis_DeSerialize_"+attribs[i].getTypeName()+
					"\n\t\t, (void*)Axis_Create_"+attribs[i].getTypeName()+", (void*)Axis_Delete_"+attribs[i].getTypeName()+
					"\n\t\t, \""+ soapTagName +"\", Axis_URI_"+attribs[i].getTypeName()+");\n");				
			}		
			
			//Dushshantha:
			//end if
			
			if(attribs[i].getChoiceElement())
				writer.write("\t}\n");
		
		
		}
		if (extensionBaseAttrib != null && extensionBaseAttrib.getTypeName() != null)
		{
			writer.write("\tpIWSDZ->getChardataAs((void*)&(param->"+extensionBaseAttrib.getParamNameAsMember()+"), "+CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName())+");\n");
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
			if (attribs[i].isArray())
			{
				
				/**
				 * Dushshantha:
				 * If the element is a Choice,
				 * it sould be treated as a pointer to an array.
				 * Memory should be allocated for that.
				 */
				
				if(attribs[i].getChoiceElement())
				{
					writer.write("\t"+attribs[i].getParamNameAsMember()+" = new "+CUtils.getBasicArrayNameforType(attribs[i].getTypeName())+"();\n");
					writer.write("\t"+attribs[i].getParamNameAsMember()+"->m_Array = 0;\n");
					writer.write("\t"+attribs[i].getParamNameAsMember()+"->m_Size = 0;\n");
				}
				
				else
				{
					writer.write("\t"+attribs[i].getParamNameAsMember()+".m_Array = 0;\n");
					writer.write("\t"+attribs[i].getParamNameAsMember()+".m_Size = 0;\n");
				}
			}
			else if (!attribs[i].isSimpleType())
			{
				writer.write("\t"+attribs[i].getParamNameAsMember()+"=0;\n");
			} 
						
			else{
				writer.write("\tmemset( &" + attribs[i].getParamNameAsMember() + ", 0, sizeof( " + attribs[i].getTypeName() + "));\n");
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
	protected void writeDestructors() throws WrapperFault {
		try{
			if (type.isFault())
			{
				writer.write("\n"+classname+"::~"+classname+"() throw ()\n{\n");
			}
			else
			{
				writer.write("\n"+classname+"::~"+classname+"()\n{\n");
			}
		writer.write("\t/*delete any pointer and array members here*/\n");
		// Adrian - seeing problems of losing data when clearing up,
		// so temporarily remove this section, until such time as a better solution is found
//		for(int i = 0; i< attribs.length;i++){
//			if(attribs[i].isArray()){
//				if ( attribs[i].isSimpleType())
//				{
//					writer.write("\tdelete [] (("+attribs[i].getTypeName()+"*)"+attribs[i].getParamNameAsMember()+".m_Array);\n");
//				}
//				else
//				{
//					if( isNillable())
//					{
//						writer.write("\tdelete "+attribs[i].getParamNameAsMember()+".m_Array;\n");
//					}
//					else
//					{
//						writer.write("\tdelete [] (("+attribs[i].getTypeName()+"*)"+attribs[i].getParamNameAsMember()+".m_Array);\n");
//					}
//				}
//			}
//			else if (attribs[i].isAnyType()){
//				writer.write("\tif ("+attribs[i].getParamNameAsMember()+") \n\t{ \n");
//				writer.write("\t\tfor (int i=0; i<"+attribs[i].getParamNameAsMember()+"->_size; i++)\n\t\t{\n");
//				writer.write("\t\t\tif ("+attribs[i].getParamNameAsMember()+"->_array[i]) delete [] "+attribs[i].getParamNameAsMember()+"->_array[i];\n");
//				writer.write("\t\t}\n");
//				writer.write("\t\tdelete "+attribs[i].getParamNameAsMember()+";\n");
//				writer.write("\t}\n");
//				
//			}
//			else if (!attribs[i].isSimpleType()){
//				writer.write("\tdelete "+attribs[i].getParamNameAsMember()+";\n");				
//			}
//		}			
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
	
	private boolean isNillable()
	{
		Iterator	itForTypes = wscontext.getTypemap().getTypes().iterator();
		boolean		nillable = false;

		while( itForTypes.hasNext() && !nillable)
		{
			Type aType = (Type) itForTypes.next();
        		
			if( aType.getLanguageSpecificName().indexOf( ">") > -1)
			{
				Iterator	itForElemName = aType.getElementnames();
					
				while( itForElemName.hasNext() && !nillable)
				{
					String key = (String) itForElemName.next();
        				
					if( aType.getElementForElementName( key).getNillable())
					{
						nillable = true;
					}
				}
			}
		}
		
		return nillable;
	}
	private boolean isMoreThanOne()
	{
		Iterator	itForTypes = wscontext.getTypemap().getTypes().iterator();
		boolean 	moreThanOne = false;
        	
		while( itForTypes.hasNext() && !moreThanOne)
		{
			Type aType = (Type) itForTypes.next();
        		
			if( aType.getLanguageSpecificName().indexOf( ">") > -1)
			{
				Iterator	itForElemName = aType.getElementnames();
					
				while( itForElemName.hasNext() && !moreThanOne)
				{
					String key = (String) itForElemName.next();
        				
					if( aType.getElementForElementName( key).getNillable())
					{
						Iterator itForElementType = aType.getElementForElementName( key).getType().getElementnames();
									
						while( itForElementType.hasNext())
						{
							String name = (String) itForElementType.next();
										
							if( "count".equals( name))
							{
								moreThanOne = true;
							}
						}
					}
				}
			}
		}
		
		return moreThanOne;
	}
}
