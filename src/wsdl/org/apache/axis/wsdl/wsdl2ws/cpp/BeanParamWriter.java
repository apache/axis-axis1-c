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

package org.apache.axis.wsdl.wsdl2ws.cpp;

import java.io.IOException;
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.ElementInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

/**
 * Genarate a webservice for the complex types likes structs.
 * 
 * @author hemapani
 */

public class BeanParamWriter extends ParamCPPFileWriter 
{
	public BeanParamWriter(WebServiceContext wscontext, Type type) throws WrapperFault 
    {
		super(wscontext, type);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.ParamCPPFileWriter#writeGlobalCodes()
	 */
	protected void writeGlobalCodes() throws WrapperFault 
    {
		try 
        {
			HashSet typeSet = new HashSet();
			String typeName;
			for (int i = 0; i < attribs.length; i++) 
            {
				if (!attribs[i].isSimpleType()) 
                {
					typeSet.add(attribs[i].getTypeName());
				}
			}
			Iterator itr = typeSet.iterator();
			while (itr.hasNext()) 
            {
				/*
				 * Needed for self referenced array. <xsd:complexType
				 * name="Type1"> <xsd:sequence> <xsd:element name="followings"
				 * maxOccurs="unbounded" minOccurs="0" type="tns:Type1" />
				 * <xsd:element name="kind" type="xsd:string" /> <xsd:element
				 * name="index" type="xsd:int" /> </xsd:sequence> <xsd:attribute
				 * name="att_kind" type="tns:Kind" /> </xsd:complexType>
				 */
				typeName = itr.next().toString();
				if (!typeName.equals(type.getName().getLocalPart())) 
                {
					writer.write("extern int Axis_DeSerialize_" + typeName
							+ "(" + typeName
							+ "* param, IWrapperSoapDeSerializer* pDZ);\n");
					writer.write("extern void* Axis_Create_" + typeName + "("
							+ typeName
							+ "* pObj, bool bArray = false, int nSize=0);\n");
					writer.write("extern void Axis_Delete_" + typeName + "("
							+ typeName
							+ "* param, bool bArray = false, int nSize=0);\n");
					writer
							.write("extern int Axis_Serialize_"
									+ typeName
									+ "("
									+ typeName
									+ "* param, IWrapperSoapSerializer* pSZ, bool bArray = false);\n");
					writer.write("extern int Axis_GetSize_" + typeName
							+ "();\n\n");
				} 
                else 
                {
					writer.write("int Axis_DeSerialize_" + typeName + "("
							+ typeName
							+ "* param, IWrapperSoapDeSerializer* pDZ);\n");
					writer.write("void* Axis_Create_" + typeName + "("
							+ typeName + "* pObj, bool bArray, int nSize);\n");
					writer.write("void Axis_Delete_" + typeName + "("
							+ typeName + "* param, bool bArray, int nSize);\n");
					writer
							.write("int Axis_Serialize_"
									+ typeName
									+ "("
									+ typeName
									+ "* param, IWrapperSoapSerializer* pSZ, bool bArray);\n");
					writer.write("int Axis_GetSize_" + typeName + "();\n\n");
				}
			}

			writeGetSetMethods();
			writeSerializeGlobalMethod();
			writeDeSerializeGlobalMethod();
			writeCreateGlobalMethod();
			writeDeleteGlobalMethod();
			writeGetSizeGlobalMethod();
		} 
        catch (IOException e) 
        {
			throw new WrapperFault(e);
		}
	}

	/**
	 * Dushshantha: following method writes getters and setters for the
	 * attributes
	 */

	private void writeGetSetMethods() throws WrapperFault 
    {
		/**
		 * Dushshantha: writing getter
		 */

		int anyCounter = 0;
		
		if (type.isArray())
        {
            return;
        }
        try
        {
			for (int i = 0; i < attribs.length; i++)
            {
			    String parameterName = attribs[i]
			       							.getParamNameWithoutSymbols();
				String properParamName = getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]);
				
				if (attribs[i].isArray())
				{
                    writer.write("\n" + properParamName + " * " + classname
                            + "::get" + parameterName + "()\n{\n");

                    writer.write("\t" + "return " + parameterName + " ; \n}\n");

                    writer.write("\n" + "void " + classname + "::set"
                            + parameterName + "(" + properParamName
                            + " * pInValue)\n{\n");

                    writer.write("\tif(" + parameterName + " == NULL)\n");
                    writer.write("\t{\n");
                    writer.write("\t\t" + parameterName + " = new " + properParamName + "();\n");
                    writer.write("\t}\n");
                    writer.write("\t" + parameterName + "->clone(*pInValue); \n");
                    writer.write("}\n");
                }
				else
				{
	                // FJP Nillable vv
	                if (isElementNillable(i))
	                {
						
	
						if (attribs[i].isAnyType())
	                    {
	                        anyCounter += 1;
	                    	parameterName = parameterName + Integer.toString(anyCounter);
	                    }
						
						writer.write("\n" + properParamName + " * " + classname
								+ "::get" + parameterName + "()\n{\n");
	
						writer.write("\t" + "return " + parameterName + " ; \n}\n");
	
						writer.write("\n" + "void " + classname + "::set"
								+ parameterName + "(" + properParamName
								+ " * pInValue)\n{\n");
	
						writer.write("\t" + parameterName + " = pInValue ; \n");
	
						if (attribs[i].getChoiceElement())
	                    {
	                        for (int j = 0; j < attribs.length; j++)
	                        {
	                            if ((attribs[j].getChoiceElement()) && (j != i))
	                            {
									writer.write("\t"
											+ attribs[j]
													.getParamNameWithoutSymbols()
											+ " = NULL ; \n");
								}
							}
						}
	
						writer.write("}\n");
					} 
	                else 
	                {
						// FJP Nillable ^^
						/**
						 * Dushshantha: Write getter
						 */
	                    
	                    if (attribs[i].isAnyType())
	                    {
	                        anyCounter += 1;
	                    	parameterName = parameterName + Integer.toString(anyCounter);
	                    }
	
	                    writer.write("\n"
	                                    + properParamName
	                                    + " " + classname + "::get"
	                                    + parameterName
	                                    + "()\n{\n");
	
	                    writer.write("\t" + "return "
	                            + parameterName
	                            + " ; \n}\n");
	
						/**
						 * Dushshantha: Write setter
						 */
	
	                    writer.write("\n"
	                            + "void "
	                            + classname
	                            + "::set"
	                            + parameterName
	                            + "("
	                            + properParamName
	                            + " InValue)\n{\n");
	
	                    writer.write("\t" + parameterName
	                            + " = InValue ; \n");
	
						if (attribs[i].getChoiceElement())
	                    {
	                        for (int j = 0; j < attribs.length; j++)
	                        {
	                            if ((attribs[j].getChoiceElement()) && (j != i))
	                            {
									writer.write("\t"
											+ attribs[j].getParamNameWithoutSymbols()
											+ " = NULL ; \n");
								}
							}
						}
	
						writer.write("}\n");
					}
				}
			}
		} 
        catch (IOException e) 
        {
			throw new WrapperFault(e);
		}
	}

	private void writeGetSizeGlobalMethod() throws IOException 
    {
		writer.write("/*\n");
		writer.write(" * This static method gives the size of " + classname
				+ " type of object\n");
		writer.write(" */\n");
		writer.write("int Axis_GetSize_" + classname
				+ "()\n{\n\treturn sizeof(" + classname + ");\n}\n");
	}

	private void writeSerializeGlobalMethod() throws IOException, WrapperFault 
    {
		writer.write("/*\n");
		writer.write(" * This static method serialize a " + classname
				+ " type of object\n");
		writer.write(" */\n");
		writer.write("int Axis_Serialize_"
						+ classname
						+ "("
						+ classname
						+ "* param, IWrapperSoapSerializer* pSZ, bool bArray = false)\n{\n");

		if (attribs.length == 0) 
        {
			System.out.println("Possible error in class " + classname
					+ ": class with no attributes....................");
			writer.write("\t}\n\n");
			return;
		}
		writer.write("\tif (bArray)\n");
		writer.write("\t{\n");
		writer.write("\t\tpSZ->serialize(\"<\", Axis_TypeName_" + classname
				+ ", \">\", NULL);\n");
		writer.write("\t}\n");
		writer.write("\telse\n");
		writer.write("\t{\n");
		writer.write("\t\tbool blnIsNewPrefix = false;\n");
		writer
				.write("\t\tconst AxisChar* sPrefix = pSZ->getNamespacePrefix(Axis_URI_"
						+ classname + ", blnIsNewPrefix);\n");
		writer.write("\t\tif (!blnIsNewPrefix)\n");
		writer.write("\t\t{\n");
		writer.write("\t\t\tpSZ->serialize(\"<\", Axis_TypeName_" + classname
				+ ", \" xsi:type=\\\"\", sPrefix, \":\",\n");
		writer.write("\t\t\t\tAxis_TypeName_" + classname
				+ ", \"\\\">\", NULL);\n");
		writer.write("\t\t}\n");
		writer.write("\t\telse\n");
		writer.write("\t\t{\n");
		writer.write("\t\t\tpSZ->serialize(\"<\", Axis_TypeName_" + classname
				+ ", \" xsi:type=\\\"\", sPrefix, \":\",\n");
		writer.write("\t\t\t\tAxis_TypeName_" + classname
				+ ", \"\\\" xmlns:\", sPrefix, \"=\\\"\",\n");
		writer.write("\t\t\t\tAxis_URI_" + classname + ", \"\\\">\", NULL);\n");
		writer.write("\t\t}\n");
		writer.write("\t}\n\n");

		String arrayType;
		boolean firstIfWritten = false;
		int anyCounter = 0;
		
		for (int i = 0; i < attribs.length; i++) 
        {
			//Dushshantha:
			//if the attribute is a choice following should do

			if (attribs[i].getChoiceElement())
            {
                if (!firstIfWritten)
                {
                    writer.write("\tif");
                    firstIfWritten = true;
                }
                else
                {
                    writer.write("\telse if");
                }

				writer.write("(param->" + attribs[i].getParamNameAsMember()
						+ ")\n\t{\n\t");
			}

			//Chinthana:
			//if the attribute is a 'all' following should do

			if (attribs[i].getAllElement())
            {
                if (attribs[i].getMinOccurs() == 0)
                {
                    writer.write("\tif(param->"
                            + attribs[i].getParamNameAsMember() + ")\n\t{\n\t");
                }
            }

			if (attribs[i].isAnyType()) 
            {
				anyCounter += 1;
            	writer.write("\tpSZ->serializeAnyObject(param->any" + Integer.toString(anyCounter) +");\n");
			} 
            else if (attribs[i].isArray()) 
            {
				//if Array
				if (attribs[i].isSimpleType()) 
                {
					writer.write("\tpSZ->serializeBasicArray(param->"
									+ attribs[i].getParamNameAsMember()
									+ ","
									+ CUtils.getXSDTypeForBasicType(attribs[i]
											.getTypeName())
									+ ", \""
									+ attribs[i].getParamName() + "\");\n");
				}
                else
                {
                    String elm = attribs[i].getParamName();
                    if (attribs[i].isReference())
                    {
                        elm = attribs[i].getTypeName();
                    }
					arrayType = attribs[i].getTypeName();
					writer.write("\tpSZ->serializeCmplxArray(param->"
									+ attribs[i].getParamNameAsMember()
									+ ",\n");
					writer.write("\t\t(void*) Axis_Serialize_" + arrayType
							+ ", (void*) Axis_Delete_" + arrayType
							+ ", (void*) Axis_GetSize_" + arrayType + ",\n");
					writer.write("\t\t\"" + elm + "\", Axis_URI_" + arrayType
							+ ");\n");
				}
			}
            else if (attribs[i].isSimpleType())
            {
                if (attribs[i].isAttribute())
                {
                    if (attribs[i].isOptional())
                    {
						writer.write("\tif (0 != param->"
								+ attribs[i].getParamNameAsMember() + ")\n");
						if (attribs[i].getTypeName().equals("xsd__string")
								|| attribs[i].getTypeName().equals("xsd__anyURI")
								|| attribs[i].getTypeName().equals("xsd__QName")
								|| attribs[i].getTypeName().equals("xsd__NOTATION")) 
                        {
							writer.write("\t\tpSZ->serializeAsAttribute(\""
									+ attribs[i].getParamName()
									+ "\", 0, (void*)(param->"
									+ attribs[i].getParamNameAsMember()
									+ "), "
									+ CUtils.getXSDTypeForBasicType(attribs[i]
											.getTypeName()) + ");\n");
						} 
                        else 
                        {
							writer.write("\t\tpSZ->serializeAsAttribute(\""
									+ attribs[i].getParamName()
									+ "\", 0, (void*)&(param->"
									+ attribs[i].getParamNameAsMember()
									+ "), "
									+ CUtils.getXSDTypeForBasicType(attribs[i]
											.getTypeName()) + ");\n");
						}
					} 
                    else 
                    {
						writer.write("\tpSZ->serializeAsAttribute(\""
								+ attribs[i].getParamName()
								+ "\", 0, (void*)&(param->"
								+ attribs[i].getParamNameAsMember()
								+ "), "
								+ CUtils.getXSDTypeForBasicType(attribs[i]
										.getTypeName()) + ");\n");
					}
				} 
                else 
                {
					if (attribs[i].getTypeName().equals("xsd__string")
							|| attribs[i].getTypeName().equals("xsd__anyURI")
							|| attribs[i].getTypeName().equals("xsd__QName")
							|| attribs[i].getTypeName().equals("xsd__NOTATION")
							|| isElementNillable(i)) 
                    {
						writer.write("\tpSZ->serializeAsElement(\""
								+ attribs[i].getParamName()
								+ "\", (void*)(param->"
								+ attribs[i].getParamNameAsMember()
								+ "), "
								+ CUtils.getXSDTypeForBasicType(attribs[i]
										.getTypeName()) + ");\n");
					} 
                    else 
                    {
						/**
						 * Dushshantha: if the element is a choice element, it
						 * should be treated as a pointer
						 */
						if (attribs[i].getChoiceElement()
								|| attribs[i].getAllElement())
                        {
							writer.write("\tpSZ->serializeAsElement(\""
									+ attribs[i].getParamName()
									+ "\", (void*)(param->"
									+ attribs[i].getParamNameAsMember()
									+ "), "
									+ CUtils.getXSDTypeForBasicType(attribs[i]
											.getTypeName()) + ");\n");
                        }
						else
                        {
							writer.write("\tpSZ->serializeAsElement(\""
									+ attribs[i].getParamName()
									+ "\", (void*)&(param->"
									+ attribs[i].getParamNameAsMember()
									+ "), "
									+ CUtils.getXSDTypeForBasicType(attribs[i]
											.getTypeName()) + ");\n");
                        }
					}
				}
			} 
            else 
            {
				//if complex type
				writer.write("\tAxis_Serialize_" + attribs[i].getTypeName()
						+ "(param->" + attribs[i].getParamNameAsMember()
						+ ", pSZ);\n");
			}
			//Dushshantha:
			//end if choice element

			if (attribs[i].getChoiceElement())
				writer.write("\t}\n");

			//Chinthana: end if
			if (attribs[i].getAllElement())
            {
                if (attribs[i].getMinOccurs() == 0)
                    writer.write("\t}\n");
            }
		}
		writer.write("\n\tpSZ->serialize(\"</\", Axis_TypeName_" + classname
				+ ", \">\", NULL);\n");
		writer.write("\treturn AXIS_SUCCESS;\n");
		writer.write("}\n\n");

	}

	private void writeDeSerializeGlobalMethod() throws IOException, WrapperFault 
    {
		int arrayCount = 0;
		
		writer.write("/*\n");
		writer.write(" * This static method deserialize a " + classname
				+ " type of object\n");
		writer.write(" */\n");
		writer.write("int Axis_DeSerialize_" + classname + "(" + classname
				+ "* param, IWrapperSoapDeSerializer* pIWSDZ)\n{\n");

		if (attribs.length == 0) 
        {
			System.out.println("Possible error in class " + classname
					+ ": class with no attributes....................");
			writer.write("\t}\n\n");
			return;
		}
		String arrayType = null;

		//Dushshantha:
		//peekCalled boolean variable checks whether the Line
		//const char* choiceName=pIWSDZ->peekNextElementName(); has been
		// wriiten in the generated cade.
		boolean peekCalled = false;
		boolean firstIfWritten = false;
		boolean foundAll = false;
		int anyCounter = 0; //counter for any types.
		
		for (int i = 0; i < attribs.length; i++) 
        {
			//Dushshantha:
			//if the attribute is a choice following should do :-)

			if (attribs[i].getChoiceElement()) 
            {
				if (!peekCalled) 
                {
					writer.write("\tconst char* choiceName=pIWSDZ->peekNextElementName();\n");
					peekCalled = true;
				}

				if (!firstIfWritten) 
                {
					writer.write("\tif");
					firstIfWritten = true;
				} 
                else 
                {
					writer.write("\telse if");
				}

				writer.write("(strcmp(choiceName,\""
						+ attribs[i].getParamNameAsMember()
						+ "\")==0)\n\t{\n\t");

			}

			//Chinthana:
			//if the attribute is a 'all' construct we have to check Min
			// occures
			if (attribs[i].getAllElement()) 
            {
				if (attribs[i].getMinOccurs() == 0) 
                {
					if (!foundAll) 
                    {
						writer.write("\tconst char* allName = NULL;\n");
						writer.write("\tbool peekCalled = false;\n");
						foundAll = true;
					}

					writer.write("\n\tif(!peekCalled)\n\t{\n\t");
					writer.write("\tallName=pIWSDZ->peekNextElementName();\n");
					writer.write("\t\tpeekCalled = true;\n");
					writer.write("\t}\n");
					writer.write("\tif(strcmp(allName,\""
							+ attribs[i].getParamNameAsMember()
							+ "\")==0)\n\t{\n\t");
					writer.write("\tpeekCalled = false;\n\t");
				}
			}

			if (attribs[i].isAnyType()) 
            {
				anyCounter +=1;
            	writer.write("\tparam->any" + Integer.toString(anyCounter)+ " = pIWSDZ->getAnyObject();\n");
			} 
            else if (attribs[i].isArray()) 
            {
				//if Array
				if (attribs[i].isSimpleType()) 
                {
					//new array memory model.					
					 writer.write("\tAxis_Array * array" + arrayCount + " = pIWSDZ->getBasicArray("
	                            + CUtils.getXSDTypeForBasicType(attribs[i].getTypeName()) + ", \""
	                            + attribs[i].getParamNameAsSOAPElement()
	                            + "\",0);\n");
	                    writer.write("\tif(param->" + attribs[i].getParamNameAsMember() + " == NULL)\n");
	                    writer.write("\t{\n");
	                    writer.write("\t\tparam->" + attribs[i].getParamNameAsMember() + " = new " + attribs[i].getTypeName() + "_Array();\n");
	                    writer.write("\t}\n");
	                    writer.write("\tparam->" + attribs[i].getParamNameAsMember() + "->clone( *array" + arrayCount + ");\n");
	                    writer.write("\tAxis::AxisDelete((void*) array" + arrayCount + ", XSD_ARRAY);\n\n");
	                    //end of new array memory model.
				} 
                else 
                {
					String elm = attribs[i].getParamName();
					if (attribs[i].isReference()) 
                    {
						elm = attribs[i].getTypeName();
					}
					arrayType = attribs[i].getTypeName();
					
					//new array memory model.
					writer.write("\t" + arrayType + "_Array * array" + arrayCount + " = new " + arrayType + "_Array();\n");
                    writer.write("\tarray" + arrayCount + " = (" + arrayType + "_Array *) pIWSDZ->getCmplxArray(array" + arrayCount + ", (void*)Axis_DeSerialize_"
                                    + arrayType
                                    + ",\n"
                                    + "\t\t\t\t\t\t\t\t  (void*)Axis_Create_"
                                    + arrayType
                                    + ",\n"
                                    + "\t\t\t\t\t\t\t\t  (void*)Axis_Delete_"
                                    + arrayType
                                    + ",\n"
                                    + "\t\t\t\t\t\t\t\t  (void*)Axis_GetSize_"
                                    + arrayType
                                    + ",\n"
                                    + "\t\t\t\t\t\t\t\t  \""
                                    + attribs[i].getElementNameAsString()
                                    + "\", Axis_URI_" + arrayType + ");\n\n");
                    
                	writer.write("\tparam->" + attribs[i].getParamNameAsMember() + " = array" + arrayCount + ";\n\n");
                	//end of new array memory model.
				}
			} 
            else if (attribs[i].isSimpleType()) 
            {
				if (attribs[i].isNillable()
						|| attribs[i].getTypeName().equals("xsd__anyURI")
						|| attribs[i].getTypeName().equals("xsd__QName")
						|| attribs[i].getTypeName().equals("xsd__NOTATION")) 
                {
					//TODO handle optional attributes
					writer.write("\t"
							+ attribs[i].getTypeName()
							+ "* p_"
							+ attribs[i].getParamNameAsMember()
							+ " = (pIWSDZ->"
							+ CUtils.getParameterGetValueMethodName(attribs[i]
									.getTypeName(), attribs[i].isAttribute())
							+ "(\"" + attribs[i].getParamName() + "\",0));\n");
					writer.write("\tparam->"
							+ attribs[i].getParamNameAsMember() + " = *p_"
							+ attribs[i].getParamNameAsMember() + ";\n");

					writer.write("\tdelete p_"
							+ attribs[i].getParamNameAsMember() + ";\n");
				} 
                else if (attribs[i].getTypeName().equals("xsd__string")
						|| isElementNillable(i)) 
                {
					writer.write("\tparam->"
							+ attribs[i].getParamNameAsMember()
							+ " = pIWSDZ->"
							+ CUtils.getParameterGetValueMethodName(attribs[i]
									.getTypeName(), attribs[i].isAttribute())
							+ "(\"" + attribs[i].getParamName() + "\",0);\n");
				} 
                else 
                {
					//TODO handle optional attributes
					/**
					 * Dushshantha: if the element is a choice element, it
					 * should be treated as a pointer.
					 */

					if (attribs[i].getChoiceElement()
							|| attribs[i].getAllElement())
                    {
						writer.write("\tparam->"
								+ attribs[i].getParamNameAsMember()
								+ " = (pIWSDZ->"
								+ CUtils.getParameterGetValueMethodName(
										attribs[i].getTypeName(), attribs[i]
												.isAttribute()) + "(\""
								+ attribs[i].getParamName() + "\",0));\n");
                    }
					else 
                    {
						writer.write("\t"
								+ attribs[i].getTypeName()
								+ "* p_"
								+ attribs[i].getParamNameAsMember()
								+ " = (pIWSDZ->"
								+ CUtils.getParameterGetValueMethodName(
										attribs[i].getTypeName(), attribs[i]
												.isAttribute()) + "(\""
								+ attribs[i].getParamName() + "\",0));\n");
						writer.write("\tparam->"
								+ attribs[i].getParamNameAsMember() + " = *p_"
								+ attribs[i].getParamNameAsMember() + ";\n");
						if (attribs[i].getTypeName().equals("xsd__hexBinary")
									|| attribs[i].getTypeName().equals("xsd__base64Binary"))
							writer.write("\n");
						else
							writer.write("\tdelete p_" + attribs[i].getParamNameAsMember() + ";\n");
					}

				}
			} 
            else 
            {
				writer.write("\tparam->" + attribs[i].getParamNameAsMember()
						+ " = (" + attribs[i].getTypeName()
						+ "*)pIWSDZ->getCmplxObject((void*)Axis_DeSerialize_"
						+ attribs[i].getTypeName()
						+ "\n\t\t, (void*)Axis_Create_"
						+ attribs[i].getTypeName() + ", (void*)Axis_Delete_"
						+ attribs[i].getTypeName() + "\n\t\t, \""
						+ attribs[i].getParamNameAsSOAPElement()
						+ "\", Axis_URI_" + attribs[i].getTypeName() + ");\n");
			}

			//Dushshantha:
			//end if

			if (attribs[i].getChoiceElement())
				writer.write("\t}\n");

			//Chinthana: end if
			if (attribs[i].getAllElement()) 
            {
				if (attribs[i].getMinOccurs() == 0)
					writer.write("\t}\n");
			}
		}
		writer.write("\treturn pIWSDZ->getStatus();\n");
		writer.write("}\n");
	}

	private void writeCreateGlobalMethod() throws IOException 
    {
		writer.write("void* Axis_Create_" + classname + "(" + classname
				+ "* pObj, bool bArray = false, int nSize=0)\n{\n");
		writer.write("\tif (bArray && (nSize > 0))\n\t{\n\t\tif (pObj)\n\t\t{\n");
		writer.write("\t\t\t" + classname + "* pNew = new " + classname
				+ "[nSize];\n");
		
        writer.write("\t\t\tsize_t i = nSize/2;\n");
        writer.write("\t\t\tfor (int ii=0; ii<i; ++ii)\n");
        writer.write("\t\t\t{\n");
        writer.write("\t\t\t\tpNew[ii] = pObj[ii];\n");
        writer.write("\t\t\t\tpObj[ii].reset();\n");
        writer.write("\t\t\t}\n");

        writer.write("\t\t\tdelete [] pObj;\n");
        
		writer.write("\t\t\treturn pNew;\n\t\t}\n\t\telse\n\t\t{\n");
		writer.write("\t\t\treturn new " + classname
						+ "[nSize];\n\t\t}\n\t}\n");
		writer.write("\telse\n\t\treturn new " + classname + ";\n}\n\n");
	}

	private void writeDeleteGlobalMethod() throws IOException 
    {
		writer.write("/*\n");
		writer.write(" * This static method delete a " + classname
				+ " type of object\n");
		writer.write(" */\n");
		writer.write("void Axis_Delete_" + classname + "(" + classname
				+ "* param, bool bArray = false, int nSize=0)\n");
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

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeConstructors()
	 */
	protected void writeConstructors() throws WrapperFault 
    {
		try 
        {
			writer.write("\n" + classname + "::" + classname + "()\n{\n");
			for (int i = 0 ; i < attribs.length ; i++)
			{
			    if (attribs[i].isArray())
			    {
			        writer.write("\t" + attribs[i].getParamNameAsMember() + " = NULL;\n");
			    }
			}
            writer.write("\t reset();\n");
            writer.write("}\n");

            writeReset(); 
		} 
        catch (IOException e) 
        {
			throw new WrapperFault(e);
		}
	}
    
	/*
	 * (non-Javadoc)
	 * 
	 * @see 
	 */
	protected void writeReset() throws WrapperFault 
    {
		try 
        {
			writer.write("\nvoid " + classname + "::reset()\n{\n");
			writer.write("\t/*do not allocate memory to any pointer members here\n\t because deserializer will allocate memory anyway. */\n");
			
			int anyCounter = 0;
			
			for (int i = 0; i < attribs.length; i++) 
            {
				if (attribs[i].isArray()) 
                {
                    writer.write("\tif ( " + attribs[i].getParamNameAsMember() + " != NULL)\n");
                    writer.write("\t{\n");
                    writer.write("\t\t" + attribs[i].getParamNameAsMember() + "->clear();\n");
                    writer.write("\t}\n");
				} 
                else if (!attribs[i].isSimpleType()) 
                {
					if (attribs[i].isAnyType())
                    {
                    	anyCounter += 1;
                    	writer.write("\t" + attribs[i].getParamNameAsMember() + Integer.toString(anyCounter)
                                + "= 0;\n");
                    }
                	else
                    {				
                		writer.write("\t" + attribs[i].getParamNameAsMember()
							+ " = 0;\n");
                	}
				}
				// FJP Nillable vv
				else if (isElementNillable(i)) 
                {
					writer.write("\t" + attribs[i].getParamNameAsMember()
							+ " = NULL;\n");
				}
				// FJP Nillable ^^
				else 
                {
					/* Needed for shared libraries */
				    if(CUtils.isPointerType(attribs[i].getTypeName()))
				    {
					writer.write("\t"+attribs[i].getParamNameAsMember()+"=0;\n");
				    }
				}
			}
			writer.write("}\n");
		} 
        catch (IOException e) 
        {
			throw new WrapperFault(e);
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
	 */
	protected void writeDestructors() throws WrapperFault 
    {
		try 
        {
			if (type.isFault())
            {
                writer.write("\n" + classname + "::~" + classname
                        + "() throw ()\n{\n");
            }
            else
            {
                writer.write("\n" + classname + "::~" + classname + "()\n{\n");
            }
			writer.write("\t/*delete any pointer and array members here*/\n");
			
			int anyCounter = 0;
			
			for (int i = 0; i < attribs.length; i++) 
            {
				if (attribs[i].isArray()) 
                {
					writer.write("\tdelete " + attribs[i].getParamNameAsMember()
						+ ";\n");
				}
				
				else if (attribs[i].isAnyType())
                {
            		anyCounter += 1;
            		writer.write("\tdelete "
							+ attribs[i].getParamNameAsMember() + Integer.toString(anyCounter) + ";\n");
				}
                else if (!attribs[i].isSimpleType()) 
                {
					writer.write("\tdelete "
							+ attribs[i].getParamNameAsMember() + ";\n");
				}
			}
			writer.write("}\n");
		} 
        catch (IOException e) 
        {
			throw new WrapperFault(e);
		}
	}
}