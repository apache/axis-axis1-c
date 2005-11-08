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
    public BeanParamWriter(WebServiceContext wscontext, Type type)
            throws WrapperFault
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
                if (!(attribs[i].isSimpleType() || attribs[i].isAnyType()))
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
                    writer.write("extern int Axis_Serialize_"
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
                    writer.write("int Axis_Serialize_"
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
                attribs[i].setParamName( CUtils.sanitiseAttributeName( classname, attribs[i].getParamName()));

                // FJP Nillable vv
                if (isElementNillable(i))
                {
                    String parameterName = attribs[i].getParamNameWithoutSymbols();
                    String properParamName = getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]);
                    
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
                                        + attribs[j].getParamNameWithoutSymbols()
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
                	String methodName = attribs[i].getParamNameWithoutSymbols();
                    String parameterName = methodName;
                    String properParamName = getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]);

                    if( methodName.endsWith( "_"))
                    {
                        String localMethodName = methodName.substring( 0, methodName.length() - 1);
                        
                        if( localMethodName.equals( classname))
                        {
                            methodName = localMethodName; 
                        }
                    }
                    
                    if (attribs[i].isAnyType())
                    {                    	
                    	anyCounter += 1;
                    	parameterName = parameterName + Integer.toString(anyCounter);
                    	methodName = methodName + Integer.toString(anyCounter);
                    }

                    writer.write("\n"
                            + properParamName
                            + " " + classname + "::get"
                            + methodName
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
                            + methodName
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
            writer.write("\tpSZ->serialize(\">\", NULL);\n");

            if (extensionBaseAttrib != null)
            {
                writer.write("\tpSZ->serializeAsChardata((void*)&(param->"
                        + extensionBaseAttrib.getParamNameAsMember()
                        + "), "
                        + CUtils.getXSDTypeForBasicType(extensionBaseAttrib
                                .getTypeName()) + ");\n");
            } 
            else
            {
                System.out.println("Possible error in class " + classname
                        + ": class with no attributes....................");
            }
            writer.write("\treturn AXIS_SUCCESS;\n");
            writer.write("}\n\n");
            return;
        }

        String arrayType;
        /*
         * A type does not know whether it is used as a nillable parameter So
         * this may not be the appropriate place to do this
         */
        writer.write("\tif ( param == NULL )\n\t{\n");
        writer.write("\t /* TODO : may need to check nillable value - Now done*/\n");
        writer.write("\t\tpSZ->serializeAsAttribute( \"xsi:nil\", 0, (void*)&(xsd_boolean_true), XSD_BOOLEAN);\n");
        writer.write("\t\tpSZ->serialize( \">\", NULL);\n");
        writer.write("\t\treturn AXIS_SUCCESS;\n");
        writer.write("\t}\n\n");

        writer.write("\t/* first serialize attributes if any*/\n");
        for (int i = 0; i < attributeParamCount; i++)
        {
            if (attribs[i].isArray() || !(attribs[i].isSimpleType()))
            {
                throw new WrapperFault("Error : an attribute is not basic type");
            }
            else
            {
                //Samisa
                //remove _Ref sufix and _ prefix in SOAP tag name
                String soapTagName = attribs[i].getParamName();
                if (soapTagName.lastIndexOf("_Ref") > -1)
                {
                    soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref"));
                }
                
                if (soapTagName.charAt(0) == '_')
                {
                    soapTagName = soapTagName.substring(1, soapTagName.length());
                }
                //end remove _Ref sufix and _ prefix in SOAP tag name
                if (CUtils.isPointerType(attribs[i].getTypeName()))
                {
                    writer.write("\tif (0 != param->"
                            + attribs[i].getParamNameAsMember() + ")\n");
                    writer.write("\t\tpSZ->serializeAsAttribute(\""
                            + soapTagName
                            + "\", 0, (void*)(param->"
                            + attribs[i].getParamNameAsMember()
                            + "), "
                            + CUtils.getXSDTypeForBasicType(attribs[i]
                                    .getTypeName()) + ");\n");
                }
                else
                {
                    writer.write("\t\tpSZ->serializeAsAttribute(\""
                            + soapTagName
                            + "\", 0, (void*)&(param->"
                            + attribs[i].getParamNameAsMember()
                            + "), "
                            + CUtils.getXSDTypeForBasicType(attribs[i].getTypeName()) + ");\n");
                }
                if (!attribs[i].isOptional())
                {
                    /* This avoid segmentation fault at runtime */
                    /*
                     * writer.write("\telse\n");
                     * writer.write("\t\tAXISTRACE1(\"The mandatory attribute
                     * "+attribs[i].getParamName()+" is not set\",
                     * CRITICAL);\n");
                     */
                }
            }
        }
        if (type.isFault())
        {
        	writer.write("\tif(Axis_URI_" + classname + ")\n\t{\n");
        	writer.write("\t\tbool blnIsNewPrefix = false;\n");
        	writer.write("\t\tconst AxisChar* sPrefix = pSZ->getNamespacePrefix(Axis_URI_"
						+ classname + ", blnIsNewPrefix);\n");
        	writer.write("\t\tpSZ->serialize(\" xmlns:\", sPrefix, \"=\\\"\",");
        	writer.write("Axis_URI_" + classname + ", \" " + " \\\"\"");
        	writer.write(", NULL);\n\t}\n");
        }               
        
        writer.write("\tpSZ->serialize( \">\", 0);\n");
        if (extensionBaseAttrib != null
                && extensionBaseAttrib.getTypeName() != null)
        {
            writer.write("\tpSZ->serializeAsChardata((void*)&(param->"
                    + extensionBaseAttrib.getParamNameAsMember()
                    + "), "
                    + CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName()) + ");\n");
        }

        writer.write("\n\t/* then serialize elements if any*/\n");

        boolean firstIfWritten = false;
        int anyCounter = 0; //counter for any types.
        
        
        for (int i = attributeParamCount; i < attribs.length; i++)
        {
            // Dushshantha:
		    // if the attribute is a choice following should do

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
                	/**
                     * Dushshantha: If the element is a Choice, It should be
                     * treated as a pointer to an array. Chinthana: This is the
                     * same in 'all' element
                     */

                    if(attribs[i].getChoiceElement()||attribs[i].getAllElement())
                    {
                    	writer.write("\tpSZ->serializeBasicArray((Axis_Array*)(param->"
                                + attribs[i].getParamName()
                                + "), Axis_URI_"
                                + classname
                                + ","
                                + CUtils.getXSDTypeForBasicType(attribs[i]
                                                .getTypeName())
                                + ", \""
                                + attribs[i].getParamNameAsSOAPElement()
                                + "\");\n");
                    }
                    else
                    {
                        writer.write("\tpSZ->serializeBasicArray((Axis_Array*)(&param->"
                                + attribs[i].getParamName()
                                + "), Axis_URI_"
                                + classname
                                + ","
                                + CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())
                                + ", \""
                                + attribs[i].getParamNameAsSOAPElement()
                                + "\");\n");
                    }
                }
                else
                {
                    Iterator itForTypes = wscontext.getTypemap().getTypes().iterator();
                    boolean nillable = isNillable();
                    boolean moreThanOne = isMoreThanOne();

                    arrayType = attribs[i].getTypeName();
                    writer.write("\t// Additional code to find is reference is pointer or pointer to a pointer\n");

                    if (nillable)
                    {
                        writer.write("\tAxis_Array\tsAA" + i + ";\n\n");
                        writer.write("\tsAA" + i + ".m_Size = 1;\n\n");

                        if (moreThanOne)
                        {
                            writer.write("\tfor( int iCount" + i
                                    + " = 0; iCount" + i
                                    + " < param->count; iCount" + i + "++)\n");
                        }
                        else
                        {
                            writer.write("\tfor( int iCount" + i
                                    + " = 0; iCount" + i + " < param->"
                                    + attribs[i].getParamName()
                                    + ".m_Size; iCount" + i + "++)\n");
                        }

                        writer.write("\t{\n");

                        if (moreThanOne)
                        {
                            writer.write("\t\tif( param->infos.m_Array[iCount"
                                    + i + "] == NULL)\n");
                        }
                        else
                        {
                            writer.write("\t\tif( param->"
                                    + attribs[i].getParamName()
                                    + ".m_Array[iCount" + i + "] == NULL)\n");
                        }

                        writer.write("\t\t{\n");
                        writer.write("\t\t\tpSZ->serializeAsAttribute( \"<"
                                        + attribs[i].getParamName()
                                        + " xsi:nil\", 0, (void*)&(xsd_boolean_true), XSD_BOOLEAN);\n");
                        writer.write("\t\t\tpSZ->serialize( \"/>\", NULL);\n");
                        writer.write("\t\t}\n");
                        writer.write("\t\telse\n");
                        writer.write("\t\t{\n");

                        if (moreThanOne)
                        {
                            writer.write("\t\t\tsAA"
                                    + i
                                    + ".m_Array = (void **)param->infos.m_Array[iCount"
                                    + i + "];\n");
                        }
                        else
                        {
                            writer.write("\t\t\tsAA" + i + ".m_Array = param->"
                                    + attribs[i].getParamName()
                                    + ".m_Array[iCount" + i + "];\n\n");
                        }

                        writer.write("\t\t\tpSZ->serializeCmplxArray( &sAA" + i
                                + ",\n");
                        writer.write("\t\t\t\t\t\t\t\t\t (void*) Axis_Serialize_"
                                        + arrayType + ",\n");
                        writer.write("\t\t\t\t\t\t\t\t\t (void*) Axis_Delete_"
                                + arrayType + ",\n");
                        writer.write("\t\t\t\t\t\t\t\t\t (void*) Axis_GetSize_"
                                + arrayType + ",\n");
                        writer.write("\t\t\t\t\t\t\t\t\t \""
                                + attribs[i].getParamName() + "\", Axis_URI_"
                                + arrayType + ");\n");
                        writer.write("\t\t}\n");
                        writer.write("\t}\n");
                    }
                    else
                    {
                        writer.write("\tpSZ->serializeCmplxArray((Axis_Array*)(&param->"
                                        + attribs[i].getParamNameAsMember()
                                        + "),\n");
                        writer.write("\t\t\t\t\t\t (void*) Axis_Serialize_"
                                + arrayType + ",\n");
                        writer.write("\t\t\t\t\t\t (void*) Axis_Delete_"
                                + arrayType + ",\n");
                        writer.write("\t\t\t\t\t\t (void*) Axis_GetSize_"
                                + arrayType + ",\n");
                        writer.write("\t\t\t\t\t\t \""
                                + attribs[i].getParamName() + "\", Axis_URI_"
                                + arrayType + ");\n");
                    }

                    writer.write("\t// End\n");
                }
            }
            else if (attribs[i].isSimpleType())
            {
                if (CUtils.isPointerType(attribs[i].getTypeName()))
                {
                    writer.write("\tpSZ->serializeAsElement(\""
                            + CUtils.sanitiseAttributeName( classname, attribs[i].getSOAPElementNameAsString())
                            + "\", Axis_URI_"
                            + classname
                            + ", (void*)(param->"
                            + attribs[i].getParamNameWithoutSymbols()
                            + "), "
                            + CUtils.getXSDTypeForBasicType(attribs[i].getTypeName()) + ");\n");
                }
                else
                {
                    /**
                     * Dushshantha: If the simple type is a choice it is handled
                     * as a pointer variable. These variables should be defined
                     * as pointers in the header file. Chinthana: This is the
                     * same in 'all' element
                     */
                	if (attribs[i].getChoiceElement()
                            || attribs[i].getAllElement()
                            || isElementNillable(i))
                	{
                		
                		if (((attribs[i].getChoiceElement())&&(isElementNillable(i)))&& !(attribs[i].getTypeName().equals("xsd__string")) )
                		{
                			writer.write("\tpSZ->serializeAsElement(\""
                                    + CUtils.sanitiseAttributeName( classname, attribs[i].getSOAPElementNameAsString())
                                    + "\", Axis_URI_"
                                    + classname
                                    + ", (void*)(*(param->"
                                    + attribs[i].getParamNameWithoutSymbols()
                                    + ")), "
                                    + CUtils.getXSDTypeForBasicType(attribs[i].getTypeName()) + ");\n");
                		}
                		else
                		{
                    		writer.write("\tpSZ->serializeAsElement(\""
                                    + CUtils.sanitiseAttributeName( classname, attribs[i].getSOAPElementNameAsString())
                                    + "\", Axis_URI_"
                                    + classname
                                    + ", (void*)(param->"
                                    + attribs[i].getParamNameWithoutSymbols()
                                    + "), "
                                    + CUtils.getXSDTypeForBasicType(attribs[i].getTypeName()) + ");\n");
                		}	
                    }                   		
                    else
                    {
                        writer.write("\tpSZ->serializeAsElement(\""
                                + CUtils.sanitiseAttributeName( classname, attribs[i].getSOAPElementNameAsString())
                                + "\", Axis_URI_"
                                + classname
                                + ", (void*)&(param->"
                                + attribs[i].getParamNameWithoutSymbols()
                                + "), "
                                + CUtils.getXSDTypeForBasicType(attribs[i].getTypeName()) + ");\n");
                    }
                }
            }
            else
            {
                //if complex type
                String elm = attribs[i].getParamName();
                if (elm.lastIndexOf("_Ref") > -1)
                {
                    elm = elm.substring(0, elm.lastIndexOf("_Ref"));
                }

                if (elm.charAt(0) == '_')
                {
                    elm = elm.substring(1, elm.length());
                }
                
                if (attribs[i].isReference())
                {
                    elm = attribs[i].getTypeName();
                }
 
                writer.write("\tpSZ->serialize(\"<\", pSZ->getNamespacePrefix(\""
                                + type.getName().getNamespaceURI()
                                + "\"), \":\", \"" + elm + "\", 0);\n");
                writer.write("\tAxis_Serialize_" + attribs[i].getTypeName()
                        + "(param->" + attribs[i].getParamName() + ", pSZ);\n");
                writer.write("\tpSZ->serialize(\"</\", pSZ->getNamespacePrefix(\""
                                + type.getName().getNamespaceURI()
                                + "\"), \":\", \"" + elm + "\", \">\", 0);\n");

            }
            //Dushshantha:
            //end if choice element

            if (attribs[i].getChoiceElement())
            {
                writer.write("\t}\n");
            }
            
            //Chinthana: end if
            if (attribs[i].getAllElement())
            {
                if (attribs[i].getMinOccurs() == 0)
                {
                    writer.write("\t}\n");
                }
            }
        }
        
        writer.write("\treturn AXIS_SUCCESS;\n");
        writer.write("}\n\n");
    }

    private void writeDeSerializeGlobalMethod() throws IOException, WrapperFault
    {
        writer.write("/*\n");
        writer.write(" * This static method deserialize a " + classname
                + " type of object\n");
        writer.write(" */\n");
        writer.write("int Axis_DeSerialize_" + classname + "(" + classname
                + "* param, IWrapperSoapDeSerializer* pIWSDZ)\n{\n");

        if (attribs.length == 0)
        {
            if (extensionBaseAttrib != null)
            {
                writer.write("\tpIWSDZ->getChardataAs((void*)&(param->"
                        + extensionBaseAttrib.getParamNameAsMember()
                        + "), "
                        + CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName()) + ");\n");
            }
            else
            {
                System.out.println("Possible error in class " + classname
                        + ": class with no attributes....................");
            }
            writer.write("\treturn AXIS_SUCCESS;\n");
            writer.write("}\n\n");
            return;
        }
        String arrayType = null;

        /* Needed for Aix xlc */

        for (int i = 0; i < attribs.length; i++)
        {
            if (attribs[i].isArray())
            {
                writer.write("\tAxis_Array array;\n\n");
                break;
            }
        }

        boolean peekCalled = false;
        boolean firstIfWritten = false;
        boolean foundAll = false;
        int anyCounter = 0; //counter for any types.
        
        for (int i = 0; i < attribs.length; i++)
        {
            //Dushshantha:
            //if the attribute is a 'choice' construct we have to peek and make
            // the choice

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
                    writer.write("\tarray = pIWSDZ->getBasicArray("
                            + CUtils.getXSDTypeForBasicType(attribs[i].getTypeName()) + ", \""
                            + attribs[i].getParamNameAsSOAPElement()
                            + "\",0);\n");

                    String typename = attribs[i].getTypeName();
                    
                    if (CUtils.isPointerType(typename))
                    {
                        if (attribs[i].getChoiceElement())
                        {
                            writer.write("\tparam->"
                                    + attribs[i].getParamNameAsMember()
                                    + "->m_Array = ("
                                    + attribs[i].getTypeName() + "*)new "
                                    + attribs[i].getTypeName()
                                    + "[array.m_Size];\n");
                        }
                        else
                        {
                            writer.write("\tparam->"
                                    + attribs[i].getParamNameAsMember()
                                    + ".m_Array = (" + attribs[i].getTypeName()
                                    + "*)new " + attribs[i].getTypeName()
                                    + "[array.m_Size];\n");
                        }
                    }
                    else
                    {
                        /**
                         * Dushshantha: If the element is a Choice, It should be
                         * treated as a pointer to an array. Chinthana: This is
                         * the same in 'all' element
                         */

                        if (attribs[i].getChoiceElement()
                                || attribs[i].getAllElement())
                        {
                            writer.write("\tparam->"
                                    + attribs[i].getParamNameAsMember()
                                    + "->m_Array = ("
                                    + attribs[i].getTypeName() + "**)new "
                                    + attribs[i].getTypeName()
                                    + "*[array.m_Size];\n");
                        }
                        else
                        {
                            writer.write("\tparam->"
                                    + attribs[i].getParamNameAsMember()
                                    + ".m_Array = (" + attribs[i].getTypeName()
                                    + "**)new " + attribs[i].getTypeName()
                                    + "*[array.m_Size];\n");
                        }
                    }

                    /**
                     * Dushshantha: If the element is a Choice, It should be
                     * treated as a pointer to an array. Chinthana: This is the
                     * same in 'all' element
                     */

                    if (attribs[i].getChoiceElement()
                            || attribs[i].getAllElement())
                    {
                        writer.write("\tparam->"
                                + attribs[i].getParamNameAsMember()
                                + "->m_Size = array.m_Size;\n\n");
                        writer.write("\tmemcpy( param->"
                                + attribs[i].getParamNameAsMember()
                                + "->m_Array, array.m_Array, sizeof( "
                                + attribs[i].getTypeName()
                                + " *) * array.m_Size);\n");
                    }
                    else
                    {
                        writer.write("\tparam->"
                                + attribs[i].getParamNameAsMember()
                                + ".m_Size = array.m_Size;\n\n");
                        writer.write("\tmemcpy( param->"
                                + attribs[i].getParamNameAsMember()
                                + ".m_Array, array.m_Array, sizeof( "
                                + attribs[i].getTypeName()
                                + " *) * array.m_Size);\n");
                    }
                }
                else
                {
                    Iterator itForTypes = wscontext.getTypemap().getTypes().iterator();
                    boolean nillable = isNillable();
                    boolean moreThanOne = isMoreThanOne();

                    arrayType = attribs[i].getTypeName();
                    writer.write("\tarray = pIWSDZ->getCmplxArray((void*)Axis_DeSerialize_"
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
                    writer.write("\t// Additional code to find if reference is pointer or pointer to a pointer\n");

                    if (nillable)
                    {
                        String attributeParamName = attribs[i].getParamName();
                        String attributeTypeName = attribs[i].getTypeName();
                        writer.write("\t" + attributeTypeName + " **	pp" + i
                                + " = param->" + attributeParamName
                                + ".m_Array;\n\n");
                        writer.write("\tparam->" + attributeParamName
                                + ".m_Size = array.m_Size;\n\n");
                        writer.write("\tif( param->" + attributeParamName
                                + ".m_Array == NULL)\n");
                        writer.write("\t{\n");
                        writer.write("\t\tpp" + i + " = new "
                                + attributeTypeName + "*[array.m_Size];\n");
                        writer.write("\t\tparam->" + attributeParamName
                                + ".m_Array = pp" + i + ";\n");
                        writer.write("\t}\n\n");
                        writer.write("\t" + attributeTypeName + " *p" + i
                                + " = (" + attributeTypeName
                                + " *) array.m_Array;\n");
                        writer.write("\t" + attributeTypeName + " default" + i + ";\n");
                        writer.write("\tfor( int iCount" + i + " = 0; iCount"
                                + i + " < array.m_Size; iCount" + i + "++)\n");
                        writer.write("\t{\n");
                        writer.write("\t\tpp" + i + "[iCount" + i + "] = new "
                                + attributeTypeName + "();\n");
                        writer.write("\t\t*(pp" + i + "[iCount" + i + "]) = p"
                                + i + "[iCount" + i + "];\n");
                        writer.write("\t\t// Set the array to default values so that the delete does not delete subfields\n");
                        writer.write("\t\tp" + i + "[iCount" + i + "] = default" + i + ";\n");
                        writer.write("\t}\n");
                        writer.write("\tdelete [] p" + i + ";\n");
                    }
                    else
                    {
                        writer.write("\tparam->"
                                        + attribs[i].getParamNameAsMember()
                                        + " = (" + attribs[i].getTypeName()
                                        + "_Array&)array;\n");
                    }

                    writer.write("\t// End\n");
                }
            }
            else if (attribs[i].isSimpleType())
            {
                //TODO handle optional attributes
                //Samisa
                //remove _Ref sufix and _ prefix in SOAP tag name
                String soapTagName = (attribs[i].isAttribute() ? attribs[i].getParamName() : attribs[i].getElementNameAsString());
                
                if (soapTagName.lastIndexOf("_Ref") > -1)
                {
                    soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref"));
                }

                if (soapTagName.charAt(0) == '_')
                {
                    soapTagName = soapTagName.substring(1, soapTagName.length());
                }
                
                //end remove _Ref sufix and _ prefix in SOAP tag name
                if (attribs[i].isNillable() ||
                        isElementNillable(i) ||
                        CUtils.isPointerType(attribs[i].getTypeName()))
                {
                	if (attribs[i].getChoiceElement() && !attribs[i].getTypeName().equals("xsd__string"))
                	{
                		writer.write("\tparam->"
                				+ attribs[i].getParamNameAsMember()
                				+ " = ("
                				+ attribs[i].getTypeName()
                				+ "**)("
                				+ attribs[i].getTypeName()
                				+"*)new "
                				+attribs[i].getTypeName()
                				+ ";\n");
                		
                		writer.write("\t\t*(param->"
                                + attribs[i].getParamNameAsMember()
                                + ") = pIWSDZ->"
                                + CUtils.getParameterGetValueMethodName(
                                        attribs[i].getTypeName(), attribs[i].isAttribute()) + "( \""
                                + soapTagName + "\",0);\n");
                    }
                	else
                	{
                		String typeName = attribs[i].getTypeName();
                		String elementName = attribs[i].getParamNameAsMember();
                		
                		writer.write("\t" + typeName + " *	pValue = pIWSDZ->" +
                		        	 CUtils.getParameterGetValueMethodName(typeName, attribs[i].isAttribute()) +
                		        	 "( \"" + soapTagName + "\", 0);\n\n");
                		writer.write("\tparam->" + elementName + " = new " + typeName + "();\n");
                		writer.write("\t*param->" + elementName + " = *pValue;\n\n");
                		writer.write("\tAxis::AxisDelete( (void *) pValue, " + CUtils.getXSDTypeForBasicType( typeName) + ");\n\n");

                	}
                } 
                else
                {
                    /**
                     * Dushshantha: If the simple type is a choice it is handled
                     * as a pointer variable. These variables should be defined
                     * as pointers in the header file. Chinthana: This is the
                     * same in 'all' element
                     */
                    if (attribs[i].getChoiceElement()
                            || attribs[i].getAllElement())
                    {
                        writer.write("\tparam->"
                                + attribs[i].getParamNameAsMember()
                                + " = pIWSDZ->"
                                + CUtils.getParameterGetValueMethodName(
                                        attribs[i].getTypeName(), attribs[i].isAttribute()) + "( \""
                                + soapTagName + "\",0);\n");
                    }
                    else
                    {
                        writer.write("\t" + attribs[i].getTypeName() + " * "
                                + attribs[i].getParamNameAsMember()
                                + " = NULL;\n\n");
                        writer.write("\tif (("
                                + attribs[i].getParamNameAsMember()
                                + " = pIWSDZ->"
                                + CUtils.getParameterGetValueMethodName(
                                        attribs[i].getTypeName(), attribs[i].isAttribute()) + "( \""
                                + CUtils.sanitiseAttributeName( classname, soapTagName) + "\",0)) != NULL)\n\t{\n");
                        writer.write("\t\tparam->"
                                + attribs[i].getParamNameAsMember() + " = *( "
                                + attribs[i].getParamNameAsMember() + " );\n");

                        if (attribs[i].getTypeName().equals("xsd__hexBinary")
    								|| attribs[i].getTypeName().equals("xsd__base64Binary"))
                        {
                        	writer.write("\t}\n");
                        }
                        else
                        {
            				writer.write("\t\tAxis::AxisDelete( (void *) " + attribs[i].getParamNameAsMember() + ", " + CUtils.getXSDTypeForBasicType( attribs[i].getTypeName()) + ");\n");
                        	writer.write("\t}\n");
                        }                        	
                    }
                }
            }
            else
            {
                //if complex type
                //Samisa
                //remove _Ref sufix and _ prefix in SOAP tag name
                String soapTagName = attribs[i].getParamName();

                if (soapTagName.lastIndexOf("_Ref") > -1)
                {
                    soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref"));
                }

                if (soapTagName.charAt(0) == '_')
                {
                    soapTagName = soapTagName.substring(1, soapTagName.length());
                }

                //end remove _Ref sufix and _ prefix in SOAP tag name
                writer.write("\tparam->" + attribs[i].getParamNameAsMember()
                        + " = (" + attribs[i].getTypeName()
                        + "*)pIWSDZ->getCmplxObject((void*)Axis_DeSerialize_"
                        + attribs[i].getTypeName()
                        + "\n\t\t, (void*)Axis_Create_"
                        + attribs[i].getTypeName() + ", (void*)Axis_Delete_"
                        + attribs[i].getTypeName() + "\n\t\t, \"" + soapTagName
                        + "\", Axis_URI_" + attribs[i].getTypeName() + ");\n");
            }

            //Dushshantha:
            //end if

            if (attribs[i].getChoiceElement())
            {
                writer.write("\t}\n");
            }
            
            //Chinthana: end if
            if (attribs[i].getAllElement())
            {
                if (attribs[i].getMinOccurs() == 0)
                {
                    writer.write("\t}\n");
                }
            }
        }

        if (extensionBaseAttrib != null
                && extensionBaseAttrib.getTypeName() != null)
        {
            writer.write("\tpIWSDZ->getChardataAs((void*)&(param->"
                    + extensionBaseAttrib.getParamNameAsMember()
                    + "), "
                    + CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName()) + ");\n");
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
                    /**
                     * Dushshantha: If the element is a Choice, it sould be
                     * treated as a pointer to an array. Memory should be
                     * allocated for that. Chinthana: This is the same in 'all'
                     * element
                     */

                    if (attribs[i].getChoiceElement()
                            || attribs[i].getAllElement())
                    {
                        writer.write("\t"
                                + attribs[i].getParamNameAsMember()
                                + " = new "
                                + CUtils.getBasicArrayNameforType(attribs[i]
                                        .getTypeName()) + "();\n");
                        writer.write("\t" + attribs[i].getParamNameAsMember()
                                + "->m_Array = 0;\n");
                        writer.write("\t" + attribs[i].getParamNameAsMember()
                                + "->m_Size = 0;\n");
                    }
                    else
                    {
                        writer.write("\t" + attribs[i].getParamNameAsMember()
                                + ".m_Array = 0;\n");
                        writer.write("\t" + attribs[i].getParamNameAsMember()
                                + ".m_Size = 0;\n");
                    }
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
                	            + "= 0;\n");
                	}
                }
                else if (isElementNillable(i))
                {
                    writer.write("\t" + attribs[i].getParamNameAsMember()
                            + " = NULL;\n");
                }
                else
                {
                    writer.write("\tmemset( &"
                            + attribs[i].getParamNameAsMember()
                            + ", 0, sizeof( " + attribs[i].getTypeName()
                            + "));\n");
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
                writer.write("\n" + classname + "::~" + classname + "() throw ()\n{\n");
            }
            else
            {
                writer.write("\n" + classname + "::~" + classname + "()\n{\n");
            }
            
            writer.write("\t/*delete any pointer and array members here*/\n");
            int anyCounter = 0;
            
            for(int i = 0; i< attribs.length;i++)
            {
                String name = attribs[i].getParamNameAsMember();
                String typename = attribs[i].getTypeName();
            	if(attribs[i].isArray())
                {
            		if (attribs[i].isSimpleType())
                    {
                        if (attribs[i].getChoiceElement())
                        {
                            writer.write("\tif (" + name
                                    + "->m_Array != NULL)\n");
                            writer.write("\t\tdelete [] ((" + typename + "*)"
                                    + name + "->m_Array);\n");
                        }
                        else
                        {
                            writer.write("\tif (" + name
                                    + ".m_Array != NULL)\n");
                            writer.write("\t\tdelete [] ((" + typename + "*)"
                                    + name + ".m_Array);\n");
                        }
                    }
            		else
            		{
            			if (isNillable())
                        {
                            writer.write("\tif (" + name
                                    + ".m_Array != NULL)\n");
                            writer.write("\t\tdelete " + name + ".m_Array;\n");
                        }
                        else
                        {
                            writer.write("\tif (" + name
                                    + ".m_Array != NULL)\n");
                            writer.write("\t\tdelete [] ((" + typename + "*)"
                                    + name + ".m_Array);\n");
                        }
            		}
            	}
            	else if (attribs[i].isAnyType())
                {
            		anyCounter += 1;
            		name = name + Integer.toString(anyCounter);
            		writer.write("\tif ("+name+") \n\t{\n");
            		writer.write("\t\tfor (int i=0; i<"+name+"->_size; i++)\n\t\t{\n");
            		writer.write("\t\t\tif ("+name+"->_array[i]) delete [] "+name+"->_array[i];\n");
            		writer.write("\t\t}\n");
            		writer.write("\t\tdelete "+name+";\n");
            		writer.write("\t}\n");
            		
            	}
            	else if (!attribs[i].isSimpleType())
                {
                    writer.write("\tif (" + name + " != NULL)\n");
                    writer.write("\t\tdelete " + name + ";\n");
                }
                else if (CUtils.isPointerType(typename))
                {
                    // found pointer type
                    writer.write("\tif (" + name + " != NULL)\n");
                    writer.write("\t\tdelete [] " + name + ";\n");
                }
            }
            writer.write("}\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    protected void writeRestrictionCheckerFunction() throws WrapperFault
    {
        try
        {
            writer.write("int Check_Restrictions_" + classname + "("
                    + classname + " value)\n");
            writer.write("{\n");
            writer.write("\treturn 0;\n");
            //TODO write code to check the restrictions
            writer.write("}\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    protected File getFilePath(boolean useServiceName) throws WrapperFault
    {
        return null;
    }

    private boolean isNillable()
    {
        Iterator itForTypes = wscontext.getTypemap().getTypes().iterator();
        boolean nillable = false;

        while (itForTypes.hasNext() && !nillable)
        {
            Type aType = (Type) itForTypes.next();

            if (aType.getLanguageSpecificName().indexOf(">") > -1)
            {
                Iterator itForElemName = aType.getElementnames();

                while (itForElemName.hasNext() && !nillable)
                {
                    String key = (String) itForElemName.next();

                    if (aType.getElementForElementName(key).getNillable())
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
        Iterator itForTypes = wscontext.getTypemap().getTypes().iterator();
        boolean moreThanOne = false;

        while (itForTypes.hasNext() && !moreThanOne)
        {
            Type aType = (Type) itForTypes.next();

            if (aType.getLanguageSpecificName().indexOf(">") > -1)
            {
                Iterator itForElemName = aType.getElementnames();

                while (itForElemName.hasNext() && !moreThanOne)
                {
                    String key = (String) itForElemName.next();

                    if (aType.getElementForElementName(key).getNillable())
                    {
                        Iterator itForElementType = aType.getElementForElementName(key).getType().getElementnames();

                        while (itForElementType.hasNext())
                        {
                            String name = (String) itForElementType.next();

                            if ("count".equals(name))
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

    //	 FJP Nillable vv
    protected boolean isElementNillable(int index)
    {
        ElementInfo ei = type.getElementForElementName(attribs[index].getParamName());
        boolean bNillable = false;

        if (ei != null
        		&& attribs[index].isSimpleType()
        		&& !attribs[index].isArray()
                && !CUtils.isPointerType(attribs[index].getTypeName()) )
        {
            bNillable = ei.getNillable();
        }

        return bNillable;
    }
    //	 FJP Nillable ^^
}