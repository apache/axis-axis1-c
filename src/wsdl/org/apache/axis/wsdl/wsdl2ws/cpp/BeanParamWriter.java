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

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* CHANGES TO FILE MAY NEED TO BE PROPAGATED TO THE                   */
/* C-EQUIVALENT FILE IN SUPPORT OF THE C-BINDING INTERFACES.          */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

package org.apache.axis.wsdl.wsdl2ws.cpp;

import java.io.File;
import java.io.IOException;
import java.util.HashSet;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
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
            // Ensure writeGetSetMethods() is first since it ensure attribute name does not conflict with
            // existing classes
            writeGetSetMethods();
            writeSerializeGlobalMethod();
            writeDeSerializeGlobalMethod();
            writeCreateGlobalMethod();
            writeDeleteGlobalMethod();
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
            return;
        
        try
        {
            for (int i = 0; i < attribs.length; i++)
            {
                // Ensure field name is valid and does not cause conflict with class names
                String sanitizedAttrName = CUtils.sanitiseAttributeName(attribs[i].getParamName());
                attribs[i].setMethodName(sanitizedAttrName);
                if (CUtils.classExists(wscontext, sanitizedAttrName))
                    sanitizedAttrName += "_Ref";
                attribs[i].setParamName(sanitizedAttrName);

                String methodName = attribs[i].getMethodName();
                String parameterName = sanitizedAttrName;
                String properParamName = getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]);
                String type = attribs[i].getTypeName();
                
                if (attribs[i].isArray())
                {
                    String parameterTypeName = properParamName;
                    if (!parameterTypeName.endsWith("*"))
                        parameterTypeName += " *";
                    
                    writer.write("\n" + parameterTypeName + " " + classname
                            + "::get" + methodName + "()\n{\n");

                    writer.write("\t" + "return " + parameterName + " ; \n}\n");

                    writer.write("\n" + "void " + classname + "::set"
                            + methodName + "(" + parameterTypeName + " pInValue)\n{\n");

                    writer.write("\tif(" + parameterName + " == NULL)\n");
                    writer.write("\t{\n");
                    
                    if (attribs[i].getChoiceElement() || attribs[i].getAllElement())
                    {
                        writer.write("\t\t// This object is a 'choice' or 'all', so need to ensure that any\n");
                        writer.write("\t\t// other objects belonging to this union of elements are empty.\n");
                        writer.write("\t\t// NB: Hasn't been implemented yet!\n");
                        writer.write("\t\t" + parameterName + " = new " + type + "_Array();\n");
                    }
                    else
                        writer.write("\t\t" + parameterName + " = new " + properParamName + "();\n");
                    
                    writer.write("\t}\n");
                    
                    if (attribs[i].getChoiceElement() || attribs[i].getAllElement())
                        writer.write("\t" + parameterName + "->clone( *pInValue);\n");
                    else
                        writer.write("\t" + parameterName + "->clone( *pInValue);\n");

                    writer.write("}\n");
                }
                else if (isElementNillable(i)  || isElementOptional(i))
                {
                    if (attribs[i].isAnyType())
                    {                        
                        anyCounter += 1;
                        parameterName = parameterName + Integer.toString(anyCounter);
                    }
                    
                    if(attribs[i].getAllElement() || attribs[i].getChoiceElement() )
                    {
                        if (isElementNillable(i))
                            writer.write("\n" + properParamName + " * " + classname
                                + "::get" + methodName + "()\n{\n");
                        else 
                            writer.write("\n" + properParamName + " " + classname
                                    + "::get" + methodName + "()\n{\n");
                    }
                    else
                    {
                        writer.write("\n" + properParamName + " * " + classname
                                + "::get" + methodName + "()\n{\n");
                    }
                    
                    writer.write("\t" + "return " + parameterName + " ; \n}\n");

                    if(attribs[i].getAllElement() || attribs[i].getChoiceElement())
                    {
                        if (isElementNillable(i))
                            writer.write("\n" + "void " + classname + "::set"
                                    + methodName + "(" + properParamName
                                    + " * pInValue, bool deep)\n{\n");
                        else
                            writer.write("\n" + "void " + classname + "::set"
                                + methodName + "(" + properParamName
                                + " pInValue, bool deep)\n{\n");
                    }
                    else
                    {
                        writer.write("\n" + "void " + classname + "::set"
                                + methodName + "(" + properParamName
                                + " * pInValue, bool deep)\n{\n");
                    }
                    
                    writer.write("\tif (" + parameterName + " != NULL)\n");
                    writer.write("\t{\n");
                    writer.write("\t\tif (__axis_deepcopy_" + parameterName + ")\n");
                    writer.write("\t\t{\n");
                    writer.write("\t\t\tdelete " + parameterName + ";\n");
                    writer.write("\t\t}\n");
                    writer.write("\t\t" + parameterName + " = NULL;\n");
                    writer.write("\t}\n");
                    writer.write("\tif (pInValue != NULL)\n");
                    writer.write("\t{\n");
                    writer.write("\t\tif (deep)\n");
                    writer.write("\t\t{\n");
                    
                    if(attribs[i].getAllElement() || attribs[i].getChoiceElement())
                    {
                        if (isElementNillable(i))
                            writer.write("\t\t\t" + parameterName + " = new " + type + "*();\n");
                        else
                            writer.write("\t\t\t" + parameterName + " = new " + type + "();\n");
                    }
                    else
                        writer.write("\t\t\t" + parameterName + " = new " + properParamName + "();\n");
                    
                    writer.write("\t\t\t*" + parameterName + " = *pInValue;\n");
                    writer.write("\t\t}\n");
                    writer.write("\t\telse\n");
                    writer.write("\t\t{\n");
                    writer.write("\t\t\t" + parameterName + " = pInValue;\n");
                    writer.write("\t\t}\n");
                    writer.write("\t}\n");
                    writer.write("\telse\n");
                    writer.write("\t{\n");
                    writer.write("\t\t" + parameterName + " = NULL;\n");
                    writer.write("\t}\n");
                    writer.write("\t__axis_deepcopy_" + parameterName + " = deep;\n");

                    if (attribs[i].getChoiceElement())
                        for (int j = 0; j < attribs.length; j++)
                            if ((attribs[j].getChoiceElement()) && (j != i))
                            {
                                // TODO simplify by doing all attributes before we get into code gen
                                String realName = attribs[j].getParamNameWithoutSymbols();
                                if (CUtils.classExists(wscontext, realName))
                                    realName += "_Ref";
                                writer.write("\t" + realName + " = NULL ; \n");
                            }
                    
                    if (attribs[i].getAllElement())
                        for (int j = 0; j < attribs.length; j++)
                            if ((attribs[j].getAllElement()) && (j != i))
                            {
                                String realName = attribs[j].getParamNameWithoutSymbols();
                                if (CUtils.classExists(wscontext, realName))
                                    realName += "_Ref";
                                writer.write("\t" + realName + " = NULL ; \n");
                            }

                    writer.write("}\n");
                } 
                else
                {
                    /**
                     * Dushshantha: Write getter
                     */
                
                    if (attribs[i].isAnyType())
                    {                        
                        anyCounter += 1;
                        parameterName = parameterName + Integer.toString(anyCounter);
                        methodName = methodName + Integer.toString(anyCounter);
                    }

                    writer.write("\n"
                            + properParamName + " " + classname + "::get" + methodName
                            + "()\n{\n");

                    writer.write("\t" + "return " + parameterName + " ; \n}\n");

                    /**
                     * Dushshantha: Write setter
                     */

                    writer.write("\n"
                            + "void " + classname + "::set"
                            + methodName + "(" + properParamName + " InValue");
                    
                    Type attributeType = attribs[i].getType();
                    
                    boolean isPointerType = false;
                    if (attributeType.isSimpleType())
                        isPointerType = CUtils.isPointerType(CUtils.getclass4qname(attributeType.getBaseType())); 
                    else
                        isPointerType = CUtils.isPointerType(getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]));
                    
                    if((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()) 
                            && (isPointerType || attribs[i].getAllElement() || attribs[i].getChoiceElement()))
                        writer.write(", bool deep");
                    
                    writer.write(")\n{\n");
                    
                    if(isPointerType)
                    {
                        writer.write("\tif (" + parameterName + " != NULL)\n");
                        writer.write("\t{\n");
                        writer.write("\t\tif (__axis_deepcopy_" + parameterName + ")\n");
                        writer.write("\t\t{\n");
                        writer.write("\t\t\tdelete [] " + parameterName + ";\n");
                        writer.write("\t\t}\n");
                        writer.write("\t\t" + parameterName + " = NULL;\n");
                        writer.write("\t}\n\n");
                        writer.write("\tif(InValue != NULL)\n");
                        writer.write("\t{\n");
                        writer.write("\t\tif (deep)\n");
                        writer.write("\t\t{\n");
                        writer.write("\t\t\t" + parameterName + " = new char[strlen(InValue) + 1];\n");
                        writer.write("\t\t\tstrcpy(" + parameterName + ", InValue);\n");
                        writer.write("\t\t}\n");
                        writer.write("\t\telse\n");
                        writer.write("\t\t{\n");
                        writer.write("\t\t\t" + parameterName + " = InValue;\n");
                        writer.write("\t\t}\n");
                        writer.write("\t}\n");
                        writer.write("\telse\n");
                        writer.write("\t{\n");
                        writer.write("\t\t" + parameterName + " = NULL;\n");
                        writer.write("\t}\n");
                        writer.write("\t__axis_deepcopy_" + parameterName + " = deep;\n");
                    }
                    else if ((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()) 
                                && (attribs[i].getAllElement() || attribs[i].getChoiceElement()))
                    {
                        writer.write("\tif (" + parameterName + " != NULL)\n");
                        writer.write("\t{\n");
                        writer.write("\t\tif (__axis_deepcopy_" + parameterName + ")\n");
                        writer.write("\t\t{\n");
                        writer.write("\t\t\tdelete " + parameterName + ";\n");
                        writer.write("\t\t}\n");
                        writer.write("\t\t" + parameterName + " = NULL;\n");
                        writer.write("\t}\n");
                        writer.write("\tif (InValue != NULL)\n");
                        writer.write("\t{\n");
                        writer.write("\t\tif (deep)\n");
                        writer.write("\t\t{\n");
                        writer.write("\t\t\t" + parameterName + " = new " + type + "();\n");
                        writer.write("\t\t\t*" + parameterName + " = *InValue;\n");
                        writer.write("\t\t}\n");
                        writer.write("\t\telse\n");
                        writer.write("\t\t{\n");
                        writer.write("\t\t\t" + parameterName + " = InValue;\n");
                        writer.write("\t\t}\n");
                        writer.write("\t}\n");
                        writer.write("\telse\n");
                        writer.write("\t{\n");
                        writer.write("\t\t" + parameterName + " = NULL;\n");
                        writer.write("\t}\n");
                        writer.write("\t__axis_deepcopy_" + parameterName + " = deep;\n");
                    }
                    else
                        writer.write("\t" + parameterName + " = InValue ; \n");

                    if (attribs[i].getChoiceElement())
                        for (int j = 0; j < attribs.length; j++)
                            if ((attribs[j].getChoiceElement()) && (j != i))
                            {
                                String realName = attribs[j].getParamNameWithoutSymbols();
                                if (CUtils.classExists(wscontext, realName))
                                    realName += "_Ref";

                                writer.write("\t" + realName + " = NULL ; \n");
                            }

                    writer.write("}\n");
                }
            } // for loop
        } 
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }

    }

    private void writeSerializeGlobalMethod() throws IOException, WrapperFault 
    {
        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
        /* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
        /* ----------------------------------------------------------------   */
        /* CHANGES TO FILE MAY NEED TO BE PROPAGATED TO THE                   */
        /* C-EQUIVALENT FILE IN SUPPORT OF THE C-BINDING INTERFACES.          */
        /* ----------------------------------------------------------------   */
        /* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
        
        writer.write( "/*\n");
        writer.write( " * This static method serialize a " + classname + " type of object\n");
        writer.write( " */\n");
        writer.write( "int Axis_Serialize_" + classname 
                     + "( " + classname + "* param, IWrapperSoapSerializer* pSZ, bool bArray)\n");
        writer.write( "{\n");

        if (attribs.length == 0) 
        {
            writer.write("\tpSZ->serialize(\">\", NULL);\n");

            if (extensionBaseAttrib != null)
            {
                String typeName = extensionBaseAttrib.getTypeName();
                writer.write("\tpSZ->serializeAsChardata((void*)");
                
                if (!CUtils.isPointerType(typeName))
                    writer.write("&");
                
                writer.write("(param->" + extensionBaseAttrib.getParamNameAsMember()
                        + "), " + CUtils.getXSDTypeForBasicType(typeName) + ");\n");
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
        writer.write("\t\tpSZ->serializeAsAttribute( \"xsi:nil\", 0, (void*)&(xsd_boolean_true), XSD_BOOLEAN);\n");
        writer.write("\t\tpSZ->serialize( \">\", NULL);\n");
        writer.write("\t\treturn AXIS_SUCCESS;\n");
        writer.write("\t}\n\n");
        /*
         * This is the only real difference for the serializer between rpc/encoded and doc/literal objects
         */
        if (wscontext.getWrapInfo().getWrapperStyle().equals("rpc"))
            writeRPCArrayPortionOfSerializeGlobalMethod();
        else
            writeDOCArrayPortionOfSerializeGlobalMethod();
        
        writer.write("\t/* If there are any attributes serialize them. If there aren't then close the tag */\n");
        for (int i = 0; i < attributeParamCount; i++)
        {
            if (attribs[i].isArray() || !(attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()))
            {
                throw new WrapperFault("Error : an attribute is not basic type");
            }
            else
            {
                //remove _Ref sufix and _ prefix in SOAP tag name
                String soapTagName = attribs[i].getParamName();
                if (soapTagName.lastIndexOf("_Ref") > -1)
                    soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref"));
                
                if (soapTagName.charAt(0) == '_')
                    soapTagName = soapTagName.substring(1, soapTagName.length());

                Type type = attribs[i].getType();
                String basicType = null;
                
                if (!attribs[i].isSimpleType() && type.isSimpleType())
                    basicType = CUtils.getclass4qname(type.getBaseType());
                else
                    basicType = attribs[i].getTypeName();

                if (CUtils.isPointerType(basicType))
                {
                    writer.write("\tif (0 != param->" + attribs[i].getParamNameAsMember() + ")\n");
                    writer.write("\t\tpSZ->serializeAsAttribute(\""
                            + soapTagName + "\", 0, (void*)(param->"
                            + attribs[i].getParamNameAsMember() + "), "
                            + CUtils.getXSDTypeForBasicType(basicType) + ");\n");
                }
                else
                {
                    writer.write("\tpSZ->serializeAsAttribute(\""
                            + soapTagName
                            + "\", 0, (void*)&(param->"
                            + attribs[i].getParamNameAsMember()
                            + "), "
                            + CUtils.getXSDTypeForBasicType(attribs[i].getTypeName()) + ");\n");
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
        
        if(wscontext.getWrapInfo().getWrapperStyle().equals("document"))
            writer.write("\tpSZ->serialize( \">\", 0);\n");
        
        if (extensionBaseAttrib != null)
        {
            String typeName = extensionBaseAttrib.getTypeName(); 
            if( typeName != null)
            {
                writer.write("\tpSZ->serializeAsChardata((void*)");
                if (!CUtils.isPointerType(typeName))
                    writer.write("&");

                writer.write("(param->" + extensionBaseAttrib.getParamNameAsMember() + "), "
                        + CUtils.getXSDTypeForBasicType(typeName) + ");\n");
            }
        }

        writer.write("\n\t/* then serialize elements if any*/\n");

        boolean firstIfWritten = false;
        int anyCounter = 0; //counter for any types.
        
        for (int i = attributeParamCount; i < attribs.length; i++)
        {
            String namespace = "";
            if (attribs[i].getNsQualified())
                namespace = "Axis_URI_" + classname;
            else
                namespace = "NULL";
            
            // if the attribute is a choice following should do
            if (attribs[i].getChoiceElement())
            {
                if (!firstIfWritten)
                {
                    writer.write("\tif");
                    firstIfWritten = true;
                } 
                else
                    writer.write("\telse if");

                writer.write("(param->" + attribs[i].getParamNameAsMember() + ")\n\t{\n\t");
            }
 
            //if the attribute is a 'all' following should do
            if (attribs[i].getAllElement())
                if (attribs[i].getMinOccurs() == 0)
                    writer.write("\tif(param->" + attribs[i].getParamNameAsMember() + ")\n\t{\n\t");
             
            if (attribs[i].isAnyType())
            {
                anyCounter += 1;
                writer.write("\tpSZ->serializeAnyObject(param->any" + Integer.toString(anyCounter) +");\n");
            }
            else if (attribs[i].isArray())
            {
                if (attribs[i].isSimpleType() || attribs[i].getType().isSimpleType())
                {
                    String baseTypeName = null;
                    if (!attribs[i].isSimpleType() && attribs[i].getType().isSimpleType())
                        baseTypeName = CUtils.getclass4qname(attribs[i].getType().getBaseType());
                    else
                        baseTypeName = attribs[i].getTypeName();
                    
                    writer.write("\tpSZ->serializeBasicArray(param->" + attribs[i].getParamName()
                        + ", " + namespace + ","
                        + CUtils.getXSDTypeForBasicType(baseTypeName) + ", \""
                        + attribs[i].getParamNameAsSOAPElement() + "\");\n");
                }
                else
                {
                    arrayType = attribs[i].getTypeName();
                    
                    if (attribs[i].getNsQualified())
                        namespace = "Axis_URI_" + arrayType;
                    else
                        namespace = "NULL";
                    
                    writer.write("\tpSZ->serializeCmplxArray(param->"
                                    + attribs[i].getParamNameAsMember() + ",\n");
                    writer.write("\t\t\t\t\t\t (void*) Axis_Serialize_" + arrayType + ",\n");
                    writer.write("\t\t\t\t\t\t (void*) Axis_Delete_" + arrayType + ",\n");
                    writer.write("\t\t\t\t\t\t \""
                            + attribs[i].getElementNameAsString() + "\", " + namespace + ");\n");
                }
            }
            else if (attribs[i].isSimpleType() || attribs[i].getType().isSimpleType())
            {
                String typeName = attribs[i].getTypeName();
                String baseTypeName = null;
                if (attribs[i].getType().isSimpleType())
                    baseTypeName = CUtils.getclass4qname (attribs[i].getType().getBaseType ());
                else
                    baseTypeName = typeName;
                
                if (attribs[i].isOptional())
                    writer.write("\tif (param->" + attribs[i].getParamNameWithoutSymbols() + " != NULL)\n\t{\n\t");
                
                if (CUtils.isPointerType(baseTypeName))
                {
                    writer.write("\tpSZ->serializeAsElement(\""
                            + attribs[i].getSOAPElementNameAsString()
                            + "\", " + namespace
                            + ", (void*)(param->" + attribs[i].getParamNameWithoutSymbols() + "), "
                            + CUtils.getXSDTypeForBasicType(baseTypeName) + ");\n");
                }
                else if (attribs[i].getChoiceElement()
                            || attribs[i].getAllElement()
                            || isElementNillable(i) || isElementOptional(i))
                {
                    // If the simple type is a choice it is handled
                    // as a pointer variable. These variables should be defined
                    // as pointers in the header file. This is the same in 'all' element
                    
                    if (((attribs[i].getChoiceElement())
                            && (isElementNillable(i)))
                            && !(CUtils.isPointerType(attribs[i].getTypeName())) )
                    {
                        writer.write("\tpSZ->serializeAsElement(\""
                                + attribs[i].getSOAPElementNameAsString() + "\", " + namespace
                                + ", (void*)(*(param->" + attribs[i].getParamNameWithoutSymbols()
                                + ")), " + CUtils.getXSDTypeForBasicType(baseTypeName) + ");\n");
                    }
                    else
                    {
                        writer.write("\tpSZ->serializeAsElement(\""
                                + attribs[i].getSOAPElementNameAsString() + "\", " + namespace
                                + ", (void*)(param->" + attribs[i].getParamNameWithoutSymbols()
                                + "), " + CUtils.getXSDTypeForBasicType(baseTypeName) + ");\n");
                    }    
                }                           
                else
                {
                    writer.write("\tpSZ->serializeAsElement(\""
                            + attribs[i].getSOAPElementNameAsString() + "\", " + namespace
                            + ", (void*)&(param->" + attribs[i].getParamNameWithoutSymbols()
                            + "), " + CUtils.getXSDTypeForBasicType(baseTypeName) + ");\n");
                }
                
                if (attribs[i].isOptional())
                    writer.write("\t}\n");
            }
            else
            {
                //if complex type
                String elm = attribs[i].getParamName();
                if (elm.lastIndexOf("_Ref") > -1)
                    elm = elm.substring(0, elm.lastIndexOf("_Ref"));

                if (elm.charAt(0) == '_')
                    elm = elm.substring(1, elm.length());
                
                if (attribs[i].isReference())
                    elm = attribs[i].getTypeName();
                
                if (attribs[i].isOptional())
                    writer.write("\tif (param->" + attribs[i].getParamName() + " != NULL)\n\t{\n");
                
                if (attribs[i].getNsQualified())
                {
                    writer.write("\tpSZ->serialize(\"<\", pSZ->getNamespacePrefix(\""
                                    + type.getName().getNamespaceURI()
                                    + "\"), \":\", \"" + elm + "\", 0);\n");
                    writer.write("\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamName() + ", pSZ);\n");
                    writer.write("\tpSZ->serialize(\"</\", pSZ->getNamespacePrefix(\""
                                    + type.getName().getNamespaceURI()
                                    + "\"), \":\", \"" + elm + "\", \">\", 0);\n");
                }
                else
                {
                    writer.write("\tpSZ->serialize(\"<" + elm + "\", 0);\n");
                    writer.write("\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamName() + ", pSZ);\n");
                    writer.write("\tpSZ->serialize(\"</" + elm + "\", \">\", 0);\n");
                }
                
                if (attribs[i].isOptional())
                    writer.write("\t}\n");
            }

            //end if choice element

            if (attribs[i].getChoiceElement())
                writer.write("\t}\n");
            
            if (attribs[i].getAllElement())
                if (attribs[i].getMinOccurs() == 0)
                    writer.write("\t}\n");
        }

        if (wscontext.getWrapInfo().getWrapperStyle().equals("rpc"))
        {
            writer.write("\n\tpSZ->serialize(\"</\", Axis_TypeName_" + classname
                    + ", \">\", NULL);\n");
        }

        
        writer.write("\n\tif (!bArray && blnIsNewPrefix)\n");
        writer.write("\t\tpSZ->removeNamespacePrefix(Axis_URI_" + classname + ");\n");
        writer.write("\n");
        
        writer.write("\treturn AXIS_SUCCESS;\n");
        writer.write("}\n\n");
    }

    /**
     * @throws IOException
     */
    private void writeDOCArrayPortionOfSerializeGlobalMethod() throws IOException
    {
        // For doc/literal objects
        writer.write("\tbool blnIsNewPrefix = false;\n");
        writer.write("\tif (!bArray)\n\t{\n");
        writer.write("\t\tconst AxisChar* sPrefix = pSZ->getNamespacePrefix(Axis_URI_" + classname + ", blnIsNewPrefix);\n");
        writer.write("\t\tif (blnIsNewPrefix)\n\t\t{\n");
        writer.write("\t\t\tpSZ->serialize(\" xmlns:\", sPrefix, \"=\\\"\",\n");
        writer.write("\t\t\t\tAxis_URI_" + classname + ", \"\\\"\", NULL );\n");
        writer.write( "\t\t}\n");
        writer.write( "\t}\n\n");
    }

    /**
     * @throws IOException
     */
    private void writeRPCArrayPortionOfSerializeGlobalMethod() throws IOException
    {
        // For rpc/encoded objects
        writer.write("\tbool blnIsNewPrefix = false;\n");
        writer.write( "\tif( bArray)\n");
        writer.write( "\t\tpSZ->serialize( \"<\", Axis_TypeName_" + classname + ", \">\", NULL);\n");
        writer.write( "\telse\n");
        writer.write( "\t{\n");
        writer.write( "\t\tconst AxisChar *\tsPrefix = pSZ->getNamespacePrefix( Axis_URI_" + classname + ",\n" +
                      "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tblnIsNewPrefix);\n\n");
        writer.write( "// If there are objects that require a local namespace, then define it here.\n");
        writer.write( "// NB: This namespace will go out of scope when the closing tag is reached.\n");
        writer.write( "\t\tif( !blnIsNewPrefix)\n");
        writer.write( "\t\t{\n");
        writer.write( "\t\t\tpSZ->serialize( \"<\",\n\t\t\t\t\t\t\tAxis_TypeName_" + classname + ",\n" +
                      "\t\t\t\t\t\t\t\" xsi:type=\\\"\",\n" +
                      "\t\t\t\t\t\t\tsPrefix,\n" +
                      "\t\t\t\t\t\t\t\":\",\n" +
                      "\t\t\t\t\t\t\t");
        writer.write( "Axis_TypeName_" + classname + ",\n" +
                      "\t\t\t\t\t\t\t\"\\\">\",\n" +
                      "\t\t\t\t\t\t\tNULL);\n");
        writer.write( "\t\t}\n");
        writer.write( "\t\telse\n");
        writer.write( "\t\t{\n");
        writer.write( "\t\t\tpSZ->serialize( \"<\",\n" +
                      "\t\t\t\t\t\t\tAxis_TypeName_" + classname + ",\n" +
                      "\t\t\t\t\t\t\t\" xsi:type=\\\"\",\n" +
                      "\t\t\t\t\t\t\tsPrefix,\n" +
                      "\t\t\t\t\t\t\t\":\",\n" +
                      "\t\t\t\t\t\t\tAxis_TypeName_" + classname + ",\n" +
                      "\t\t\t\t\t\t\t\"\\\" xmlns:\",\n" +
                      "\t\t\t\t\t\t\tsPrefix,\n" +
                      "\t\t\t\t\t\t\t\"=\\\"\",\n" +
                      "\t\t\t\t\t\t\tAxis_URI_" + classname + ",\n" +
                      "\t\t\t\t\t\t\t\"\\\">\",\n" +
                      "\t\t\t\t\t\t\tNULL);\n");

        writer.write( "\t\t}\n");
        writer.write( "\t}\n\n");
    }

    private void writeDeSerializeGlobalMethod() throws IOException, WrapperFault
    {
        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
        /* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
        /* ----------------------------------------------------------------   */
        /* CHANGES TO FILE MAY NEED TO BE PROPAGATED TO THE                   */
        /* C-EQUIVALENT FILE IN SUPPORT OF THE C-BINDING INTERFACES.          */
        /* ----------------------------------------------------------------   */
        /* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
        
        writer.write("/*\n");
        writer.write(" * This static method deserialize a " + classname + " type of object\n");
        writer.write(" */\n");
        writer.write("int Axis_DeSerialize_" + classname + "(" + classname
                + "* param, IWrapperSoapDeSerializer* pIWSDZ)\n{\n");

        if (attribs.length == 0)
        {
            if (extensionBaseAttrib != null)
            {
                writer.write("\tpIWSDZ->getChardataAs((void **)&(param->"
                        + extensionBaseAttrib.getParamNameAsMember() + "), "
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
        boolean peekCalled = false;
        boolean firstIfWritten = false;
        boolean foundAll = false;
        int anyCounter = 0; //counter for any types.
        int arrayCount = 0;
        
        for (int i = 0; i < attribs.length; i++)
        {
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
                    writer.write("\telse if");

                writer.write("(strcmp(choiceName,\""
                        + attribs[i].getElementNameAsString() + "\")==0)\n\t{\n\t");
            }

            //if the attribute is a 'all' construct we have to check Min
            // occures
            if (attribs[i].getAllElement())
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
                            + attribs[i].getParamNameAsMember() + "\")==0)\n\t{\n\t");
                    writer.write("\tpeekCalled = false;\n\t");
                }
            
            if (attribs[i].isAnyType())
            {
                anyCounter +=1;
                writer.write("\tparam->any" + Integer.toString(anyCounter)+ " = pIWSDZ->getAnyObject();\n");
            }
            else if (attribs[i].isArray())
            {
                arrayCount++;
                
                if (attribs[i].isSimpleType() || attribs[i].getType().isSimpleType())
                {
                    String baseTypeName = null;
                    if (!attribs[i].isSimpleType() && attribs[i].getType().isSimpleType())
                        baseTypeName = CUtils.getclass4qname(attribs[i].getType().getBaseType());
                    else
                        baseTypeName = attribs[i].getTypeName();

                    writer.write("\tAxis_Array * array" + arrayCount + " = pIWSDZ->getBasicArray("
                            + CUtils.getXSDTypeForBasicType(baseTypeName) + ", \""
                            + attribs[i].getParamNameAsSOAPElement()
                            + "\",0);\n");
                    writer.write("\tif(param->" + attribs[i].getParamNameAsMember() + " == NULL)\n");
                    writer.write("\t{\n");
                    writer.write("\t\tparam->" + attribs[i].getParamNameAsMember() + " = new " + attribs[i].getTypeName() + "_Array();\n");
                    writer.write("\t}\n");
                    writer.write("\tparam->" + attribs[i].getParamNameAsMember() + "->clone( *array" + arrayCount + ");\n");
                    writer.write("\tAxis::AxisDelete((void*) array" + arrayCount + ", XSD_ARRAY);\n\n");
                }
                else
                {
                    arrayType = attribs[i].getTypeName();
                    writer.write("\tpIWSDZ->getCmplxArray(param->" + attribs[i].getParamNameAsMember() + ", (void*)Axis_DeSerialize_"
                                    + arrayType + ",\n"
                                    + "\t\t\t\t\t\t\t\t  (void*)Axis_Create_" + arrayType + ",\n"
                                    + "\t\t\t\t\t\t\t\t  (void*)Axis_Delete_" + arrayType + ",\n"
                                    + "\t\t\t\t\t\t\t\t  \""
                                    + attribs[i].getElementNameAsString()
                                    + "\", Axis_URI_" + arrayType + ");\n\n");
                    
                }
            }
            else if ((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()))
            {
                //TODO handle optional attributes
                //remove _Ref sufix and _ prefix in SOAP tag name
                String soapTagName = (attribs[i].isAttribute() ? attribs[i].getParamName() : attribs[i].getElementNameAsString());
                if (soapTagName.lastIndexOf("_Ref") > -1)
                    soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref"));

                if (soapTagName.charAt(0) == '_')
                    soapTagName = soapTagName.substring(1, soapTagName.length());
                
                if (attribs[i].isOptional())
                {
                    writer.write("\tconst char* elementName" + i + " = pIWSDZ->peekNextElementName();\n");
                    writer.write("\t\tif(strcmp(elementName" + i + ", \"" + soapTagName + "\") == 0)\n");
                    writer.write("\t\t{\n");
                }
                
                Type type = attribs[i].getType();
                boolean isPointerType = false;
                if (type.isSimpleType())
                    isPointerType = CUtils.isPointerType(CUtils.getclass4qname(type.getBaseType())); 
                else
                    isPointerType = CUtils.isPointerType(attribs[i].getTypeName());

                if (attribs[i].isNillable() ||
                        isElementNillable(i) ||
                        isElementOptional(i) ||
                        isPointerType)
                {
                    if (attribs[i].getChoiceElement() && isElementNillable(i) && !isPointerType)
                    {
                        writer.write("\tparam->"
                                + attribs[i].getParamNameAsMember()
                                + " = (" + attribs[i].getTypeName()
                                + "**)(" + attribs[i].getTypeName()
                                +"*)new " +attribs[i].getTypeName() + ";\n");
                        
                        writer.write("\t\t*(param->"
                                + attribs[i].getParamNameAsMember() + ") = pIWSDZ->"
                                + CUtils.getParameterGetValueMethodName(
                                        attribs[i].getTypeName(), attribs[i].isAttribute()) + "( \""
                                + soapTagName + "\",0);\n");
                    }
                    else
                    {
                        String typeName = attribs[i].getTypeName();
                        String baseTypeName = null;
                        if (type.isSimpleType())
                            baseTypeName = CUtils.getclass4qname (type.getBaseType ());
                        else
                            baseTypeName = typeName;
                        
                        if( isPointerType)
                        {
                            writer.write("\t" + typeName + "    pValue" + i + " = pIWSDZ->" +
                                    CUtils.getParameterGetValueMethodName(baseTypeName, attribs[i].isAttribute()) +
                                    "( \"" + soapTagName + "\", 0);\n");
                        }
                        else
                        {
                            writer.write("\t\t\t" + typeName + " *    pValue" + i + " = pIWSDZ->" +
                                    CUtils.getParameterGetValueMethodName(baseTypeName, attribs[i].isAttribute()) +
                                    "( \"" + soapTagName + "\", 0);\n");
                        }
                        
                        writer.write( "\t\t\tif( pValue" + i + " == NULL)\n");
                        writer.write("\t\t\t\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                        writer.write( "\t\t\telse\n");
                        writer.write( "\t\t\t{\n");
                        
                        writer.write("\t\t\t\tparam->set" + attribs[i].getMethodName() + " (pValue" + i + ");\n");
                        writer.write("\t\t\t\tAxis::AxisDelete( (void *) pValue" + i + ", " 
                                + CUtils.getXSDTypeForBasicType( baseTypeName) + ");\n\n");
                        writer.write( "\t\t\t}\n\n");
                    }
                } 
                else if (attribs[i].getChoiceElement() || attribs[i].getAllElement())
                {
                    writer.write("\tparam->"
                            + attribs[i].getParamNameAsMember() + " = pIWSDZ->"
                            + CUtils.getParameterGetValueMethodName(
                                    attribs[i].getTypeName(), attribs[i].isAttribute()) + "( \""
                            + soapTagName + "\",0);\n");
                }
                else
                {
                    String elementNameToSearchFor = attribs[i].isAttribute()? attribs[i].getParamNameAsMember():attribs[i].getSOAPElementNameAsString();
                    
                    writer.write("\t" + attribs[i].getTypeName() + " * "
                            + attribs[i].getParamNameAsMember() + " = NULL;\n\n");
                    writer.write("\tif ((" + attribs[i].getParamNameAsMember() + " = pIWSDZ->"
                            + CUtils.getParameterGetValueMethodName(
                                    attribs[i].getTypeName(), attribs[i].isAttribute()) + "( \""
                            + elementNameToSearchFor + "\",0)) != NULL)\n\t{\n");

                    writer.write("\t\tparam->set"
                            + attribs[i].getMethodName() + "(* " + attribs[i].getParamNameAsMember() + " );\n");
                    writer.write("\t\tAxis::AxisDelete( (void *) " + attribs[i].getParamNameAsMember() + ", " + CUtils.getXSDTypeForBasicType( attribs[i].getTypeName()) + ");\n");
                    writer.write("\t}\n");                        
                }
                
                if (attribs[i].isOptional())
                {
                    writer.write("\t\t\t}\n");
                    writer.write("\t\telse\n");
                    writer.write("\t\t\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                    writer.write("\n");
                }
            }
            else
            {
                //if complex type
                //remove _Ref sufix and _ prefix in SOAP tag name
                String soapTagName = attribs[i].getParamName();

                if (soapTagName.lastIndexOf("_Ref") > -1)
                    soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref"));

                if (soapTagName.charAt(0) == '_')
                    soapTagName = soapTagName.substring(1, soapTagName.length());
                
                if (attribs[i].isOptional())
                {
                    writer.write("\tconst char* elementName" + i + " = pIWSDZ->peekNextElementName();\n");
                    writer.write("\tif(strcmp(elementName" + i + ", \"" + soapTagName + "\") == 0)\n");
                    writer.write("\t{\n");
                }

                writer.write("\tparam->" + attribs[i].getParamNameAsMember()
                        + " = (" + attribs[i].getTypeName()
                        + "*)pIWSDZ->getCmplxObject((void*)Axis_DeSerialize_"
                        + attribs[i].getTypeName()
                        + "\n\t\t, (void*)Axis_Create_"
                        + attribs[i].getTypeName() + ", (void*)Axis_Delete_"
                        + attribs[i].getTypeName() + "\n\t\t, \"" + soapTagName
                        + "\", Axis_URI_" + attribs[i].getTypeName() + ");\n");
                
                if (attribs[i].isOptional())
                {
                    writer.write("\t}\n");
                    writer.write("\telse\n");
                    writer.write("\t\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                    writer.write("\n");
                }
            }

            if (attribs[i].getChoiceElement())
                writer.write("\t}\n");
            
            if (attribs[i].getAllElement())
                if (attribs[i].getMinOccurs() == 0)
                    writer.write("\t}\n");
        }

        if (extensionBaseAttrib != null
                && extensionBaseAttrib.getTypeName() != null)
        {
            writer.write("\tpIWSDZ->getChardataAs((void **)&(param->"
                    + extensionBaseAttrib.getParamNameAsMember() + "), "
                    + CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName()) + ");\n");
        }

        writer.write("\treturn pIWSDZ->getStatus();\n");
        writer.write("}\n");
    }

    private void writeCreateGlobalMethod() throws IOException
    {
        writer.write("void* Axis_Create_" + classname + "(int nSize)\n");
        writer.write("{\n");
        writer.write("\tif (nSize > 0)\n");
        writer.write("\t{\n");
        writer.write("\t\t" + classname + "** pNew = new " + classname + "* [nSize];\n");
        writer.write("\t\tfor (int i=0; i < nSize; ++i)\n");
        writer.write("\t\t\tpNew[i] = new " + classname + ";\n");
        writer.write("\t\treturn pNew;\n");
        writer.write("\t}\n");
        writer.write("\telse\n");
        writer.write("\t\treturn new " + classname + ";\n");
        writer.write("}\n");
        writer.write("\n");
    }

    private void writeDeleteGlobalMethod() throws IOException
    {
        writer.write("/*\n");
        writer.write(" * This static method delete a " + classname + " type of object\n");
        writer.write(" */\n");
        writer.write("void Axis_Delete_" + classname + "(" + classname + "* param, int nSize)\n");
        writer.write("{\n");
        
        writer.write("\t/* If null just return */\n");
        writer.write("\tif (!param)\n");
        writer.write("\t\treturn;\n\n");
        
        writer.write("\t/* Reclaim array objects if array */\n");
        writer.write("\tif (nSize > 0)\n");
        writer.write("\t{\n");
        writer.write("\t\tfor (int count = 0 ; count < nSize ; count++ )\n");
        writer.write("\t\t{\n");
        writer.write("\t\t\tif ( (( " + classname + " ** ) param)[count])\n");
        writer.write("\t\t\t{\n");
        writer.write("\t\t\t\tdelete (( " + classname + " ** ) param)[count];\n");
        writer.write("\t\t\t\t(( " + classname + " ** ) param)[count] = NULL;\n");
        writer.write("\t\t\t}\n");
        writer.write("\t\t}\n");
        writer.write("\t\tdelete [] ( " + classname + " ** ) param;\n");
        writer.write("\t}\n");
        writer.write("\telse\n");
        writer.write("\t\tdelete param;\n");
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
            // Write default constructor
            writer.write("\n" + classname + "::" + classname + "()\n{\n");
            for (int i = 0 ; i < attribs.length ; i++)
            {
                if (attribs[i].isArray())
                {
                    if (attribs[i].getChoiceElement()||attribs[i].getAllElement())
                    {
                        // This is the 'choice' or 'all' route in the code
                        writer.write("\t\t// This object is a 'choice' or 'all', so need to ensure that any\n");
                        writer.write("\t\t// other objects belonging to this union of elements are empty.\n");
                        writer.write("\t\t// NB: Hasn't been implemented yet!\n");
                        writer.write("\t" + attribs[i].getParamNameAsMember() + " = new " 
                                + attribs[i].getTypeName() +"_Array();\n");
                    }
                    else
                    {
                        writer.write("\t" + attribs[i].getParamNameAsMember() + " = new " 
                                + attribs[i].getTypeName() +"_Array();\n");
                    }
                }
            }
            writer.write("\treset();\n");
            writer.write("}\n");

            writeCopyConstructor();
            writeReset();
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
    
    /**
     * @throws IOException
     */
    private void writeCopyConstructor() throws WrapperFault
    {
        try
        {
            //write copy constructor
            writer.write("\n" + classname + "::" + classname + "(const " + classname + " & original)\n{\n");

            // AXISCPP-918 patch provided by Franz Fehringer
            if (extensionBaseAttrib != null && extensionBaseAttrib.getTypeName() != null)
            {
                writer.write("\t" + extensionBaseAttrib.getParamNameAsMember() + " = " + "original." + extensionBaseAttrib.getParamNameAsMember() + ";\n");
            }
            // End of AXISCPP-918

            int anyCounter = 0;
            for (int i = 0 ; i < attribs.length ; i++)
            {
                if (attribs[i].isArray())
                {    
                    if (attribs[i].getChoiceElement()||attribs[i].getAllElement())
                    {
                        // This is the 'choice' or 'all' route in the code
                        writer.write("\t\t// This object is a 'choice' or 'all', so need to ensure that any\n");
                        writer.write("\t\t// other objects belonging to this union of elements are empty.\n");
                        writer.write("\t\t// NB: Hasn't been implemented yet!\n");
                        writer.write("\t" + attribs[i].getParamName() + " = new " 
                                + attribs[i].getTypeName() + "_Array( *original." 
                                + attribs[i].getParamName() + ");\n");
                    }
                    else
                    {
                        writer.write("\t" + attribs[i].getParamName() + " = new " 
                                + attribs[i].getTypeName() + "_Array(*original." 
                                + attribs[i].getParamName() + ");\n");
                    }
                }
                else if (attribs[i].isAnyType())
                {
                    anyCounter++;
                    writer.write("\tif (original." + attribs[i].getParamName() + anyCounter + " != NULL)\n");
                    writer.write("\t{\n");
                    writer.write("\t\t" + attribs[i].getParamName() + anyCounter + " = new " + attribs[i].getTypeName() + "(*(original." + attribs[i].getParamName() + anyCounter + "));\n");
                    writer.write("\t}\n");
                    writer.write("\telse\n");
                    writer.write("\t{\n");
                    writer.write("\t\t" + attribs[i].getParamName() + anyCounter + " = NULL;\n");
                    writer.write("\t}\n");
                }
                else
                {
                    Type type = attribs[i].getType();
                    boolean isPointerType = false;
                    if (type.isSimpleType())
                        isPointerType = CUtils.isPointerType(CUtils.getclass4qname(type.getBaseType())); 
                    else
                        isPointerType = CUtils.isPointerType(attribs[i].getTypeName());
    
                    if ((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()) && (isPointerType || attribs[i].isOptional() || attribs[i].isNillable() || attribs[i].getChoiceElement() || attribs[i].getAllElement()))
                    {
                        writer.write("\t" + attribs[i].getParamName() + " = NULL;\n");
                        writer.write("\t__axis_deepcopy_" + attribs[i].getParamName() + " = false;\n");
                        writer.write("\tset" + attribs[i].getMethodName() + "(original." + attribs[i].getParamName() + ", original.__axis_deepcopy_" + attribs[i].getParamName() + ");\n\n");
                    }
                    else if (attribs[i].isSimpleType())
                    {
                        writer.write("\t" + attribs[i].getParamName() + " = original." 
                                + attribs[i].getParamName() + ";\n");
                    }
                    else
                    {
                        writer.write("\tif (original." + attribs[i].getParamName() + " != NULL)\n");
                        writer.write("\t{\n");
                        writer.write("\t\t" + attribs[i].getParamName() + " = new " 
                                + attribs[i].getTypeName() + "(*(original." 
                                + attribs[i].getParamName() + "));\n");
                        writer.write("\t}\n");
                        writer.write("\telse\n");
                        writer.write("\t{\n");
                        writer.write("\t\t" + attribs[i].getParamName() + " = NULL;\n");
                        writer.write("\t}\n");
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
                    if (attribs[i].getChoiceElement()||attribs[i].getAllElement())
                    {
                        writer.write( "\t// This object is a 'choice' or 'all', so need to ensure that any\n");
                        writer.write( "\t// other objects belonging to this union of elements are empty.\n");
                        writer.write( "\t// NB: Hasn't been implemented yet!\n");

                        writer.write("\t" + attribs[i].getParamNameAsMember() + "->clear();\n");
                    }
                    else
                        writer.write("\t" + attribs[i].getParamNameAsMember() + "->clear();\n");
                }
                else if (!(attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()))
                {
                    if (attribs[i].isAnyType())
                    {
                        anyCounter += 1;
                        writer.write("\t" + attribs[i].getParamNameAsMember() + Integer.toString(anyCounter)
                                + "= NULL;\n");
                    }
                    else
                        writer.write("\t" + attribs[i].getParamNameAsMember() + "= NULL;\n");
                }
                else if (isElementNillable(i) || isElementOptional(i) || attribs[i].getChoiceElement() || attribs[i].getAllElement())
                {
                    writer.write("\t" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                    writer.write("\t__axis_deepcopy_" + attribs[i].getParamName() + " = false;\n");
                }
                else
                {
                    Type type = attribs[i].getType();
                    boolean isPointerType = false;
                    if (type.isSimpleType())
                        isPointerType = CUtils.isPointerType(CUtils.getclass4qname(type.getBaseType())); 
                    else
                        isPointerType = CUtils.isPointerType(attribs[i].getTypeName());

                    if(isPointerType)
                    {
                        writer.write("\t"+ attribs[i].getParamNameAsMember() + " = NULL;\n");
                        writer.write("\t__axis_deepcopy_" + attribs[i].getParamName() + " = false;\n");
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
                writer.write("\n" + classname + "::~" + classname + "() throw ()\n{\n");
            else
                writer.write("\n" + classname + "::~" + classname + "()\n{\n");
            
            writer.write("\t/*delete any pointer and array members here*/\n");
            int anyCounter = 0;
            
            for(int i = 0; i< attribs.length;i++)
            {
                String name = attribs[i].getParamNameAsMember();
                String typename = attribs[i].getTypeName();
                
                Type type = attribs[i].getType();
                boolean isPointerType = false;
                if (type.isSimpleType())
                    isPointerType = CUtils.isPointerType(CUtils.getclass4qname(type.getBaseType())); 
                else
                    isPointerType = CUtils.isPointerType(typename);
                
                if(attribs[i].isArray())
                {
                    writer.write("\tif (" + name + "!= NULL)\n");
                    writer.write("\t{\n");
                    writer.write("\t\tdelete " + name + ";\n");
                    writer.write("\t\t" + name + " = NULL;\n");
                    writer.write("\t}\n");
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
                else if (!(attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()))
                {
                    writer.write("\tif (" + name + "!= NULL)\n");
                    writer.write("\t{\n");
                    writer.write("\t\tdelete " + name + ";\n");
                    writer.write("\t\t" + name + " = NULL;\n");
                    writer.write("\t}\n");
                }
                else if (isPointerType || isElementNillable(i) || isElementOptional(i) || attribs[i].getChoiceElement() || attribs[i].getAllElement())
                {
                    // found pointer type
                    writer.write("\tif (" + name + " != NULL)\n");
                    writer.write("\t{\n");
                    writer.write("\t\tif(__axis_deepcopy_" + name + ")\n");
                    writer.write("\t\t{\n");
                    writer.write("\t\t\tdelete ");
                    if (isPointerType)
                        writer.write("[] ");
                    writer.write(name + ";\n");
                    writer.write("\t\t}\n");
                    writer.write("\t\t" + name + " = NULL;\n");
                    writer.write("\t}\n");
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
            writer.write("int Check_Restrictions_" + classname + "(" + classname + " value)\n");
            
            //TODO write code to check the restrictions. 
            
            writer.write("{\n");
            
            if( CUtils.isPointerType( CUtils.getclass4qname( type.getBaseType())))
            {
                writer.write( "// String type\n");
                writer.write( "// Number of " + classname + " elements = " + (type.getEnumerationdata().size() - 1) + "\n");
                
                Iterator i = type.getEnumerationdata().iterator();
                int iIndex = 0;
                TypeEntry baseTypeForArray = (TypeEntry) i.next();
                
                while( i.hasNext())
                {
                    if( iIndex == 0)
                        writer.write( "//\tif( ");
                    else
                        writer.write( " ||\n//\t    ");
                    
                    QName qnElement = (QName) i.next();
                    writer.write( "!strcmp( value, " + classname+ "_" + qnElement.getNamespaceURI() + ")");
                    iIndex++;
                }
                
                writer.write( "//)\n//\t{\n");
                writer.write( "//\t\treturn 1;\n");
                writer.write( "//\t}\n");
            }
            else
            {
                writer.write( "// Non-string type\n");
                writer.write( "// Number of " + classname + " enums = " + (type.getEnumerationdata().size() - 1) + "\n");
                
                Iterator i = type.getEnumerationdata().iterator();
                int iIndex = 0;
                TypeEntry baseTypeForArray = (TypeEntry) i.next();
                
                while( i.hasNext())
                {
                    if( iIndex == 0)
                        writer.write( "//\tif( ");
                    else
                        writer.write( " ||\n//\t    ");
                    
                    QName qnElement = (QName) i.next();
                    writer.write( "value == ENUM" + classname.toUpperCase()+ "_" 
                            + qnElement.getNamespaceURI());
                    iIndex++;
                }
                
                writer.write( "//)\n//\t{\n");
                writer.write( "//\t\treturn 1;\n");
                writer.write( "//\t}\n");
            }
            
            writer.write( "\n\treturn 0;\n");
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
}