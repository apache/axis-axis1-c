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
        if (type.isArray())
            return;
        
        try
        {
            int anyCounter = 0;
            
            for (int i = 0; i < attribs.length; i++)
            {
                // Set method name
                String methodName = attribs[i].getMethodName();
                
                // Set parameter name
                String parameterName = attribs[i].getParamNameAsMember();
                
                // Set the type to use
                String properParamType = getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]);
                
                String type = attribs[i].getTypeName();
                
                // arrays require '*' in prototype for type if one not specified.
                String asterisk = " ";
                
                // Details
                if (attribs[i].isArray())
                {
                    // Ensure that type on prototype is a pointer to an array
                    if (!properParamType.endsWith("*"))
                        asterisk += "* ";
                }
                else if (attribs[i].isAnyType())
                {
                    // We use a counter appeneded to parameter name.
                    anyCounter += 1;
                    parameterName = parameterName + Integer.toString(anyCounter);
                    methodName = methodName + Integer.toString(anyCounter);
                }
                
                //=============================================================================
                // Write getter method
                //=============================================================================      

                CUtils.printMethodComment(writer, "Getter method for class member field " 
                        + parameterName + ".");
                
                writer.write(properParamType + asterisk + classname
                        + "::get" + methodName + "()\n{\n");

                writer.write("\t" + "return " + parameterName + "; \n}\n");

                //=============================================================================
                // Write setter method
                //=============================================================================  
                
                CUtils.printMethodComment(writer, "Setter method for class member field " 
                        + parameterName + ".");
                
                if (attribs[i].isArray())
                {   
                    writer.write("void " + classname + "::set"
                            + methodName + "(" + properParamType + asterisk + "pInValue)\n{\n");

                    writer.write("\tif(" + parameterName + " == NULL)\n");
                    
                    if (attribs[i].getChoiceElement() || attribs[i].getAllElement())
                    {
                        // TODO: for choice, we need to ensure any other set element is deleted.
                        writer.write("\t{\n");
                        writer.write("\t\t// For 'choice' need to ensure that any\n");
                        writer.write("\t\t// other objects belonging to this union of elements are empty.\n");
                        writer.write("\t\t// NB: Hasn't been implemented yet!\n");
                        writer.write("\t\t" + parameterName + " = new " + type + "_Array();\n");
                        writer.write("\t}\n");
                    }
                    else
                        writer.write("\t\t" + parameterName + " = new " + properParamType + "();\n");                   
                    
                    writer.write("\t" + parameterName + "->clone( *pInValue);\n");
                    writer.write("}\n");
                }
                else if (isElementNillable(i)  || isElementOptional(i))
                {
                    // Setter method
                    writer.write("void " + classname + "::set"
                            + methodName + "(" + properParamType  
                            + " pInValue, bool deep)\n{\n");

                    writer.write("\tif (__axis_deepcopy_" + parameterName + ")\n");
                    writer.write("\t\tdelete " + parameterName + ";\n");
                    writer.write("\t" + parameterName + " = NULL;\n");

                    writer.write("\tif (pInValue != NULL)\n");
                    writer.write("\t{\n");
                    writer.write("\t\tif (deep)\n");
                    writer.write("\t\t{\n");
                    
                    writer.write("\t\t\t" + parameterName + " = new " + type + "();\n");

                    writer.write("\t\t\t*" + parameterName + " = *pInValue;\n");
                    writer.write("\t\t}\n");
                    writer.write("\t\telse\n");
                    writer.write("\t\t\t" + parameterName + " = pInValue;\n");
                    writer.write("\t}\n");

                    writer.write("\t__axis_deepcopy_" + parameterName + " = deep;\n");

                    // TODO: wrong! We need to delete the object if deep copy, otherwise NULL it out.
                    if (attribs[i].getChoiceElement())
                        for (int j = 0; j < attribs.length; j++)
                            if ((attribs[j].getChoiceElement()) && (j != i))
                                writer.write("\t" + attribs[j].getParamNameAsMember() + " = NULL; \n");

                    writer.write("}\n");
                } 
                else
                {
                    writer.write("void " + classname + "::set"
                            + methodName + "(" + properParamType + " InValue");
                    
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
                        writer.write("\tif (__axis_deepcopy_" + parameterName + ")\n");
                        writer.write("\t\tdelete [] " + parameterName + ";\n");
                        writer.write("\t" + parameterName + " = NULL;\n");
                        
                        writer.write("\tif(InValue != NULL)\n");
                        writer.write("\t{\n");
                        writer.write("\t\tif (deep)\n");
                        writer.write("\t\t{\n");
                        writer.write("\t\t\t" + parameterName + " = new char[strlen(InValue) + 1];\n");
                        writer.write("\t\t\tstrcpy(" + parameterName + ", InValue);\n");
                        writer.write("\t\t}\n");
                        writer.write("\t\telse\n");
                        writer.write("\t\t\t" + parameterName + " = InValue;\n");
                        writer.write("\t}\n");

                        writer.write("\t__axis_deepcopy_" + parameterName + " = deep;\n");
                    }
                    else if ((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()) 
                                && (attribs[i].getAllElement() || attribs[i].getChoiceElement()))
                    {
                        writer.write("\tif (__axis_deepcopy_" + parameterName + ")\n");
                        writer.write("\t\tdelete " + parameterName + ";\n");
                        writer.write("\t" + parameterName + " = NULL;\n");

                        writer.write("\tif (InValue != NULL)\n");
                        writer.write("\t{\n");
                        writer.write("\t\tif (deep)\n");
                        writer.write("\t\t{\n");
                        writer.write("\t\t\t" + parameterName + " = new " + type + "();\n");
                        writer.write("\t\t\t*" + parameterName + " = *InValue;\n");
                        writer.write("\t\t}\n");
                        writer.write("\t\telse\n");
                        writer.write("\t\t\t" + parameterName + " = InValue;\n");
                        writer.write("\t}\n");

                        writer.write("\t__axis_deepcopy_" + parameterName + " = deep;\n");
                    }
                    else
                        writer.write("\t" + parameterName + " = InValue ; \n");

                    // TODO: wrong! We need to delete the object if deep copy, otherwise NULL it out.
                    if (attribs[i].getChoiceElement())
                        for (int j = 0; j < attribs.length; j++)
                            if ((attribs[j].getChoiceElement()) && (j != i))
                                writer.write("\t" + attribs[j].getParamNameAsMember() + " = NULL ; \n");

                    writer.write("}\n");
                }
            } // for loop
        } 
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }

    }

    private void writeSerializeExtensionCode()  throws IOException, WrapperFault
    {
        // TODO: xsd:extension not fully or correctly supported.
        if (extensionBaseAttrib != null)
        {
            CUtils.printBlockComment(writer, "Serialize extension.");
            
            String typeName = extensionBaseAttrib.getTypeName(); 

            if (extensionBaseAttrib.isSimpleType())
            {
                writer.write("\tpSZ->serializeAsChardata((void*)");
                if (!CUtils.isPointerType(typeName))
                    writer.write("&");    
                writer.write("(param->" + extensionBaseAttrib.getParamNameAsMember() + "), "
                        + CUtils.getXSDTypeForBasicType(typeName) + ");\n");
            }
            else
            {
                // TODO
            }
        }        
        else if (attribs.length == 0)
        {
            System.out.println("Possible error in class " + classname
                    + ": class with no attributes or elements...........");
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

        CUtils.printMethodComment(writer, "Function to serialize an object of type "  
                + classname + ".");        
        
        writer.write( "int Axis_Serialize_" + classname 
                     + "( " + classname + "* param, IWrapperSoapSerializer* pSZ, bool bArray)\n");
        writer.write( "{\n");
       
        //=============================================================================
        // No attributes or elements to serialize? Then serialize extension and return.
        //=============================================================================        

        if (attribs.length == 0) 
        {
            CUtils.printBlockComment(writer, "No attributes or elements to serialize.");
            
            writer.write("\tpSZ->serialize(\">\", NULL);\n");

            writeSerializeExtensionCode();
            
            writer.write("\treturn AXIS_SUCCESS;\n");
            writer.write("}\n\n");
            return;
        }
        
        //=============================================================================
        // NULL param passed in? Assume nillable although type does not know whether
        // it is used as a nillable parameter so this may not be the appropriate place
        // to put this, or we need to find a way to determine if nillable.
        //=============================================================================        

        CUtils.printBlockComment(writer, "If null input, serialize as nil element.");
        
        writer.write("\tif ( param == NULL )\n\t{\n");
        writer.write("\t\tpSZ->serializeAsAttribute( \"xsi:nil\", 0, (void*)&(xsd_boolean_true), XSD_BOOLEAN);\n");
        writer.write("\t\tpSZ->serialize( \">\", NULL);\n");
        writer.write("\t\treturn AXIS_SUCCESS;\n");
        writer.write("\t}\n");
        
        //=============================================================================
        // Serialize 
        // This is the only real difference for the serializer between rpc/encoded and 
        // doc/literal objects
        //=============================================================================        
        
        if (wscontext.getWrapInfo().getWrapperStyle().equals("rpc"))
            writeRPCArrayPortionOfSerializeGlobalMethod();
        else
            writeDOCArrayPortionOfSerializeGlobalMethod();
        
        //=============================================================================
        // Serialize attributes, if any
        //=============================================================================        

        if (attributeParamCount > 0)
            CUtils.printBlockComment(writer, "Serialize attributes.");
        
        for (int i = 0; i < attributeParamCount; i++)
        {
            if (attribs[i].isArray() || !(attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()))
                throw new WrapperFault("Error : an attribute is not basic type");
            
            String soapTagName = attribs[i].getParamNameAsSOAPString();

            Type type = attribs[i].getType();
            String basicType = null;
            
            if (!attribs[i].isSimpleType() && type.isSimpleType())
                basicType = CUtils.getclass4qname(type.getBaseType());
            else
                basicType = attribs[i].getTypeName();

            if (CUtils.isPointerType(basicType) || attribs[i].isOptional())
            {
                // TODO: Add check if ptr type and not optional and is null, throw exception.
                writer.write("\tif (0 != param->" + attribs[i].getParamNameAsMember() + ")\n\t");                
                writer.write("\tpSZ->serializeAsAttribute(\""
                        + soapTagName + "\", 0, (void*)(param->"
                        + attribs[i].getParamNameAsMember() + "), "
                        + CUtils.getXSDTypeForBasicType(basicType) + ");\n");
            }
            else
            {
                writer.write("\tpSZ->serializeAsAttribute(\""
                        + soapTagName + "\", 0, (void*)&(param->"
                        + attribs[i].getParamNameAsMember() + "), "
                        + CUtils.getXSDTypeForBasicType(attribs[i].getTypeName()) + ");\n");
            }
        }

        //=============================================================================
        // Serialization relating to faults
        //=============================================================================                           
                
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
        
        //=============================================================================
        // Serialize extension, if any
        //=============================================================================                           
        
        writeSerializeExtensionCode();

        //=============================================================================
        // Serialize elements, if any
        //=============================================================================                
        
        if (attributeParamCount < attribs.length)
            CUtils.printBlockComment(writer, "Serialize sub-elements.");

        boolean firstIfWritten = false;
        int anyCounter = 0; //counter for any types.
        String arrayType;
        
        for (int i = attributeParamCount; i < attribs.length; i++)
        {
            String namespace = "NULL";
            if (attribs[i].getNsQualified())
                namespace = "Axis_URI_" + classname;
            
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
                
                if (attribs[i].isOptional())
                    writer.write("\tif (param->any" + Integer.toString(anyCounter) + " != NULL)\n");
                                
                writer.write("\t\tpSZ->serializeAnyObject(param->any" + Integer.toString(anyCounter) +");\n");
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
                    
                    writer.write("\tpSZ->serializeBasicArray(param->" + attribs[i].getParamNameAsMember()
                        + ", " + namespace + ","
                        + CUtils.getXSDTypeForBasicType(baseTypeName) + ", \""
                        + attribs[i].getParamNameAsSOAPString() + "\");\n");
                }
                else
                {
                    arrayType = attribs[i].getTypeName();
                    
                    if (attribs[i].getNsQualified())
                        namespace = "Axis_URI_" + arrayType;
                    else
                        namespace = "NULL";
                    
                    writer.write("\tpSZ->serializeCmplxArray(param->" + attribs[i].getParamNameAsMember() 
                            + ", (void*)Axis_Serialize_" + arrayType 
                            + ", (void*)Axis_Delete_" + arrayType 
                            + ", \"" + attribs[i].getElementNameAsSOAPString() + "\", " + namespace + ");\n");
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
                    writer.write("\tif (param->" + attribs[i].getParamNameAsMember() + " != NULL)\n\t");
                
                if (CUtils.isPointerType(baseTypeName))
                {
                    writer.write("\tpSZ->serializeAsElement(\""
                            + attribs[i].getElementNameAsSOAPString()
                            + "\", " + namespace
                            + ", (void*)(param->" + attribs[i].getParamNameAsMember() + "), "
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
                                + attribs[i].getElementNameAsSOAPString() + "\", " + namespace
                                + ", (void*)(*(param->" + attribs[i].getParamNameAsMember()
                                + ")), " + CUtils.getXSDTypeForBasicType(baseTypeName) + ");\n");
                    }
                    else
                    {
                        writer.write("\tpSZ->serializeAsElement(\""
                                + attribs[i].getElementNameAsSOAPString() + "\", " + namespace
                                + ", (void*)(param->" + attribs[i].getParamNameAsMember()
                                + "), " + CUtils.getXSDTypeForBasicType(baseTypeName) + ");\n");
                    }    
                }                           
                else
                {
                    writer.write("\tpSZ->serializeAsElement(\""
                            + attribs[i].getElementNameAsSOAPString() + "\", " + namespace
                            + ", (void*)&(param->" + attribs[i].getParamNameAsMember()
                            + "), " + CUtils.getXSDTypeForBasicType(baseTypeName) + ");\n");
                }
            }
            else
            {
                //if complex type
                String elm = attribs[i].getParamNameAsSOAPString();
                if (attribs[i].isReference())
                    elm = attribs[i].getTypeName();
                
                if (attribs[i].isOptional())
                    writer.write("\tif (param->" + attribs[i].getParamNameAsMember() + " != NULL)\n\t{\n");
                
                if (attribs[i].getNsQualified())
                {
                    writer.write("\tpSZ->serialize(\"<\", pSZ->getNamespacePrefix(\""
                                    + type.getName().getNamespaceURI()
                                    + "\"), \":\", \"" + elm + "\", 0);\n");
                    writer.write("\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamNameAsMember() + ", pSZ);\n");
                    writer.write("\tpSZ->serialize(\"</\", pSZ->getNamespacePrefix(\""
                                    + type.getName().getNamespaceURI()
                                    + "\"), \":\", \"" + elm + "\", \">\", 0);\n");
                }
                else
                {
                    writer.write("\tpSZ->serialize(\"<" + elm + "\", 0);\n");
                    writer.write("\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamNameAsMember() + ", pSZ);\n");
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

        //=============================================================================
        // End of attribute and element serialization
        //=============================================================================                
                
        if (wscontext.getWrapInfo().getWrapperStyle().equals("rpc"))
        {
            writer.write("\n\tpSZ->serialize(\"</\", Axis_TypeName_" + classname
                    + ", \">\", NULL);\n");
        }

        CUtils.printBlockComment(writer, "Remove namespace, if new.");        
        
        writer.write("\tif (!bArray && blnIsNewPrefix)\n");
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
        CUtils.printBlockComment(writer, "Serialize top-most element, possibly defining new namespace.");        
        
        // For doc/literal objects
        writer.write("\tbool blnIsNewPrefix = false;\n");
        writer.write("\tif (!bArray)\n\t{\n");
        writer.write("\t\tconst AxisChar* sPrefix = pSZ->getNamespacePrefix(Axis_URI_" + classname + ", blnIsNewPrefix);\n");
        writer.write("\t\tif (blnIsNewPrefix)\n");
        writer.write("\t\t\tpSZ->serialize(\" xmlns:\", sPrefix, \"=\\\"\", "
                        + "Axis_URI_" + classname + ", \"\\\"\", NULL);\n");
        writer.write( "\t}\n");
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
        writer.write( "\t\tconst AxisChar * sPrefix = pSZ->getNamespacePrefix( Axis_URI_" 
                + classname + ", blnIsNewPrefix);\n\n");
        writer.write( "\t\t// If there are objects that require a local namespace, then define it here.\n");
        writer.write( "\t\t// NB: This namespace will go out of scope when the closing tag is reached.\n");
        writer.write( "\t\tif( !blnIsNewPrefix)\n");
        writer.write( "\t\t\tpSZ->serialize( \"<\", Axis_TypeName_" + classname + ", " 
                    + "\" xsi:type=\\\"\", sPrefix, \":\", " 
                    + "Axis_TypeName_" + classname + ", \"\\\">\", NULL);\n");
        writer.write( "\t\telse\n");
        writer.write( "\t\t\tpSZ->serialize( \"<\", Axis_TypeName_" + classname + ", " 
                    + "\" xsi:type=\\\"\", sPrefix, \":\", " 
                    + "Axis_TypeName_" + classname + ", \"\\\" xmlns:\", " 
                    + "sPrefix, \"=\\\"\", Axis_URI_" + classname + ", \"\\\">\", NULL);\n");
        writer.write( "\t}\n");
    }

    private void writeDeSerializeExtensionCode() throws IOException, WrapperFault
    {  
        if (extensionBaseAttrib != null
                && extensionBaseAttrib.getTypeName() != null)
        {
            CUtils.printBlockComment(writer, "Deserialize extension.");
            
            if (extensionBaseAttrib.isSimpleType())
            {
                writer.write("\tvoid* pCharDataAs;\n");
                String typeName = extensionBaseAttrib.getTypeName();
                String xsdType = CUtils.getXSDTypeForBasicType(typeName);
                writer.write("\tpIWSDZ->getChardataAs(&pCharDataAs, " + xsdType + ");\n");
                writer.write("\tparam->" + extensionBaseAttrib.getParamNameAsMember() + " = ");
                
                if (CUtils.isPointerType(typeName))
                    writer.write("(" + typeName + ") pCharDataAs;\n");
                else
                {
                    writer.write(" *(" + typeName + "*) pCharDataAs;\n");
                    writer.write("\tAxis::AxisDelete( pCharDataAs, " + xsdType + ");\n");
                }    
            }
            else
            {
                // TODO
            }
        }
        else if (attribs.length == 0)
        {
            System.out.println("Possible error in class " + classname
                    + ": class with no attributes or elements............");
            
        }
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
        
        CUtils.printMethodComment(writer, "Function to deserialize an object of type "  
                + classname + ".");   
        
        writer.write("int Axis_DeSerialize_" + classname + "(" + classname
                + "* param, IWrapperSoapDeSerializer* pIWSDZ)\n{\n");

        //=============================================================================
        // No attributes or elements to deserialize? Then deserialize extension and return.
        //=============================================================================        

        if (attribs.length == 0)
        {
            writeDeSerializeExtensionCode();
            
            writer.write("\treturn AXIS_SUCCESS;\n");
            writer.write("}\n\n");
            return;
        }

        
        // We always use this...
        writer.write("\tconst char* peekedElementName;\n");

        //=============================================================================
        // Deserialize attributes.
        // Makes logic simpler to follow with slight duplication. TODO
        //=============================================================================        
        
        if (attributeParamCount > 0)
            CUtils.printBlockComment(writer, "Deserialize attributes.");
        
        for (int i = 0; i < attributeParamCount; i++) 
        {
            
        }
        
        //=============================================================================
        // Deserialize attributes and elements.
        //=============================================================================        
        
        String arrayType = null;
        boolean peekCalled = false;
        boolean firstIfWritten = false;
        boolean foundAll = false;
        int anyCounter = 0; //counter for any types.
        int arrayCount = 0;
        
        boolean handleAll = false;
        boolean handleChoice = false;
     
        // Tabs to ensure code alignment
        String tab1  = "\t";
        String tab2Default = "";
        String tab2;
       
        for (int i = 0; i < attribs.length; i++)
        {
            // Reset tabs
            tab2  = tab2Default + "\t";
            
            if (i == attributeParamCount)
                CUtils.printBlockComment(writer, "Deserialize elements.");
            
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
                        + attribs[i].getElementNameAsSOAPString() + "\")==0)\n\t{\n\t");
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
                writer.write(tab1 + "param->any" + Integer.toString(anyCounter)+ " = pIWSDZ->getAnyObject();\n");
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

                    writer.write(tab1 + "Axis_Array * array" + arrayCount + " = pIWSDZ->getBasicArray("
                            + CUtils.getXSDTypeForBasicType(baseTypeName) + ", \""
                            + attribs[i].getParamNameAsSOAPString()
                            + "\",0);\n");
                    writer.write(tab1 + "if(param->" + attribs[i].getParamNameAsMember() + " == NULL)\n");
                    writer.write(tab1 + "\tparam->" + attribs[i].getParamNameAsMember() + " = new " + attribs[i].getTypeName() + "_Array();\n");
                    writer.write(tab1 + "param->" + attribs[i].getParamNameAsMember() + "->clone( *array" + arrayCount + ");\n");
                    writer.write(tab1 + "Axis::AxisDelete((void*) array" + arrayCount + ", XSD_ARRAY);\n\n");
                }
                else
                {
                    arrayType = attribs[i].getTypeName();
                    writer.write(tab1 + "pIWSDZ->getCmplxArray(param->" + attribs[i].getParamNameAsMember() 
                            + ", (void*)Axis_DeSerialize_" + arrayType
                            + ", (void*)Axis_Create_" + arrayType 
                            + ", (void*)Axis_Delete_" + arrayType
                            + ", \"" + attribs[i].getElementNameAsSOAPString() + "\", Axis_URI_" + arrayType + ");\n");
                }
            }
            else if ((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()))
            {
                String soapTagName = (attribs[i].isAttribute() ? attribs[i].getParamNameAsSOAPString() : attribs[i].getElementNameAsSOAPString());
                
                // We only peek for elements, not element attributes!
                if (attribs[i].isOptional() && !attribs[i].isAttribute())
                {
                    writer.write(tab1 + "peekedElementName = pIWSDZ->peekNextElementName();\n");
                    writer.write(tab1 + "if (strcmp(peekedElementName, \"" + soapTagName + "\") == 0)\n");
                    writer.write(tab1 + "{\n");
                    tab2 += "\t";
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
                        writer.write(tab2 + "param->"
                                + attribs[i].getParamNameAsMember()
                                + " = (" + attribs[i].getTypeName()
                                + "**)(" + attribs[i].getTypeName()
                                +"*)new " +attribs[i].getTypeName() + ";\n");
                        
                        writer.write(tab2 + "*(param->"
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
                            writer.write(tab2 + typeName + " pValue" + i + " = pIWSDZ->" +
                                    CUtils.getParameterGetValueMethodName(baseTypeName, attribs[i].isAttribute()) +
                                    "( \"" + soapTagName + "\", 0);\n");
                        }
                        else
                        {
                            writer.write(tab2 + typeName + " *    pValue" + i + " = pIWSDZ->" +
                                    CUtils.getParameterGetValueMethodName(baseTypeName, attribs[i].isAttribute()) +
                                    "( \"" + soapTagName + "\", 0);\n");
                        }
                        
                        writer.write(tab2 + "if( pValue" + i + " == NULL)\n");
                        writer.write(tab2 + "\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                        writer.write(tab2 + "else\n");
                        writer.write(tab2 + "{\n");
                        
                        writer.write(tab2 + "\tparam->set" + attribs[i].getMethodName() + " (pValue" + i + ");\n");
                        writer.write(tab2 + "\tAxis::AxisDelete( (void *) pValue" + i + ", " 
                                + CUtils.getXSDTypeForBasicType( baseTypeName) + ");\n");
                        writer.write(tab2 + "}\n");
                    }
                } 
                else if (attribs[i].getChoiceElement() || attribs[i].getAllElement())
                {
                    writer.write(tab2 + "param->"
                            + attribs[i].getParamNameAsMember() + " = pIWSDZ->"
                            + CUtils.getParameterGetValueMethodName(
                                    attribs[i].getTypeName(), attribs[i].isAttribute()) + "( \""
                            + soapTagName + "\",0);\n");
//                    writer.write(tab2 + "param->__axis_deepcopy_"  + attribs[i].getParamNameAsMember()
//                            + " = true;\n");
                }
                else
                {
                    String elementNameToSearchFor = attribs[i].isAttribute()? attribs[i].getParamNameAsSOAPString():attribs[i].getElementNameAsSOAPString();
                    
                    writer.write(tab2 + attribs[i].getTypeName() + " * "
                            + attribs[i].getParamNameAsMember() + " = NULL;\n");
                    writer.write(tab2 + "if ((" + attribs[i].getParamNameAsMember() + " = pIWSDZ->"
                            + CUtils.getParameterGetValueMethodName(
                                    attribs[i].getTypeName(), attribs[i].isAttribute()) + "( \""
                            + elementNameToSearchFor + "\",0)) != NULL)\n");
                    writer.write(tab2 + "{\n");
                    writer.write(tab2 + "\tparam->set"
                            + attribs[i].getMethodName() + "(* " + attribs[i].getParamNameAsMember() + " );\n");
                    writer.write(tab2 + "\tAxis::AxisDelete( (void *) " + attribs[i].getParamNameAsMember() + ", " + CUtils.getXSDTypeForBasicType( attribs[i].getTypeName()) + ");\n");
                    writer.write(tab2 + "}\n");                        
                }
                
                if (attribs[i].isOptional() && !attribs[i].isAttribute())
                {
                    writer.write(tab1 + "}\n");
                    writer.write(tab1 + "else\n");
                    writer.write(tab1 + "\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                }
            }
            else
            {
                //if complex type
                String soapTagName = attribs[i].getParamNameAsSOAPString();
                
                if (attribs[i].isOptional())
                {
                    writer.write(tab1 + "peekedElementName = pIWSDZ->peekNextElementName();\n");
                    writer.write(tab1 + "if (strcmp(peekedElementName, \"" + soapTagName + "\") == 0)\n");
                    tab2 += "\t";
                }

                writer.write(tab2 + "param->" + attribs[i].getParamNameAsMember()
                        + " = (" + attribs[i].getTypeName()
                        + "*)pIWSDZ->getCmplxObject((void*)Axis_DeSerialize_" + attribs[i].getTypeName()
                        + ", (void*)Axis_Create_" + attribs[i].getTypeName() 
                        + ", (void*)Axis_Delete_" + attribs[i].getTypeName() 
                        + ", \"" + soapTagName + "\", Axis_URI_" + attribs[i].getTypeName() + ");\n");
                
                if (attribs[i].isOptional())
                {
                    writer.write(tab1 + "else\n");
                    writer.write(tab1 + "\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                }
            }

            if (attribs[i].getChoiceElement())
                writer.write(tab1 + "}\n");
            
            if (attribs[i].getAllElement())
                if (attribs[i].getMinOccurs() == 0)
                    writer.write("\t}\n");
            
            writer.write("\n");                        
        }
        
        //=============================================================================
        // Deserialize extension, if any, and return status
        //=============================================================================                           
        
        writeDeSerializeExtensionCode();

        writer.write("\treturn pIWSDZ->getStatus();\n");
        writer.write("}\n");
    }

    private void writeCreateGlobalMethod() throws IOException
    {
        CUtils.printMethodComment(writer, "Function used to create objects of type " 
                + classname + ".");
        
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
        CUtils.printMethodComment(writer, "Function used to delete objects of type " 
                + classname + ".");
        
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
            CUtils.printMethodComment(writer, "Constructor for class " + classname + ".");
            
            writer.write(classname + "::" + classname + "()\n{\n");
            for (int i = 0 ; i < attribs.length ; i++)
            {
                if (attribs[i].isArray())
                {
                    if (attribs[i].getChoiceElement()||attribs[i].getAllElement())
                    {
                        // This is the 'choice' or 'all' route in the code
                        writer.write("\t\t// This a 'choice' so need to ensure that any\n");
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
            CUtils.printMethodComment(writer, "Copy constructor for class " + classname + ".");            
            writer.write(classname + "::" + classname + "(const " + classname + " & original)\n{\n");

            // AXISCPP-918 patch provided by Franz Fehringer
            if (extensionBaseAttrib != null && extensionBaseAttrib.getTypeName() != null)
            {
                if (extensionBaseAttrib.isSimpleType())
                    writer.write("\t" + extensionBaseAttrib.getParamNameAsMember() + " = " + "original." + extensionBaseAttrib.getParamNameAsMember() + ";\n");
                else
                {
                    // TODO
                }
            }
            // End of AXISCPP-918

            // Set fields in SoapFaultException parent class if fault
            if (type.isFault())
            {
                writer.write("\tsetFaultCode(original.getFaultCode());\n");
                writer.write("\tsetFaultString(original.getFaultString());\n");
                writer.write("\tsetFaultActor(original.getFaultActor());\n");
            }
            
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
                        writer.write("\t" + attribs[i].getParamNameAsMember() + " = new " 
                                + attribs[i].getTypeName() + "_Array( *original." 
                                + attribs[i].getParamNameAsMember() + ");\n");
                    }
                    else
                    {
                        writer.write("\t" + attribs[i].getParamNameAsMember() + " = new " 
                                + attribs[i].getTypeName() + "_Array(*original." 
                                + attribs[i].getParamNameAsMember() + ");\n");
                    }
                }
                else if (attribs[i].isAnyType())
                {
                    anyCounter++;
                    writer.write("\tif (original." + attribs[i].getParamNameAsMember() + anyCounter + " != NULL)\n");
                    writer.write("\t\t" + attribs[i].getParamNameAsMember() + anyCounter + " = new " + attribs[i].getTypeName() + "(*(original." + attribs[i].getParamNameAsMember() + anyCounter + "));\n");
                    writer.write("\telse\n");
                    writer.write("\t\t" + attribs[i].getParamNameAsMember() + anyCounter + " = NULL;\n");
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
                        writer.write("\t" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                        writer.write("\t__axis_deepcopy_" + attribs[i].getParamNameAsMember() + " = false;\n");
                        writer.write("\tset" + attribs[i].getMethodName() + "(original." + attribs[i].getParamNameAsMember() + ", original.__axis_deepcopy_" + attribs[i].getParamNameAsMember() + ");\n\n");
                    }
                    else if (attribs[i].isSimpleType())
                    {
                        writer.write("\t" + attribs[i].getParamNameAsMember() + " = original." 
                                + attribs[i].getParamNameAsMember() + ";\n");
                    }
                    else
                    {
                        writer.write("\tif (original." + attribs[i].getParamNameAsMember() + " != NULL)\n");
                        writer.write("\t\t" + attribs[i].getParamNameAsMember() + " = new " 
                                + attribs[i].getTypeName() + "(*(original." 
                                + attribs[i].getParamNameAsMember() + "));\n");
                        writer.write("\telse\n");
                        writer.write("\t\t" + attribs[i].getParamNameAsMember() + " = NULL;\n");
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
            CUtils.printMethodComment(writer, "Method to initialize objects of class " + classname + ".");
            
            writer.write("void " + classname + "::reset()\n{\n");
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
                    writer.write("\t__axis_deepcopy_" + attribs[i].getParamNameAsMember() + " = false;\n");
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
                        writer.write("\t__axis_deepcopy_" + attribs[i].getParamNameAsMember() + " = false;\n");
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
            CUtils.printMethodComment(writer, "Destructor for class " + classname + ".");
            
            if (type.isFault())
                writer.write(classname + "::~" + classname + "() throw ()\n{\n");
            else
                writer.write(classname + "::~" + classname + "()\n{\n");
            
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
                    writer.write("\tdelete " + name + ";\n");
                else if (attribs[i].isAnyType())
                {
                    anyCounter += 1;
                    name = name + Integer.toString(anyCounter);
                    writer.write("\tif ("+name+") \n\t{\n");
                    writer.write("\t\tfor (int i=0; i<"+name+"->_size; i++)\n");
                    writer.write("\t\t\tdelete [] "+name+"->_array[i];\n");
                    writer.write("\t\tdelete "+name+";\n");
                    writer.write("\t}\n");
                }
                else if (!(attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()))
                    writer.write("\tdelete " + name + ";\n");
                else if (isPointerType || isElementNillable(i) || isElementOptional(i) || attribs[i].getChoiceElement() || attribs[i].getAllElement())
                {
                    // found pointer type
                    writer.write("\tif(__axis_deepcopy_" + name + ")\n");
                    writer.write("\t\tdelete ");
                    if (isPointerType)
                        writer.write("[] ");
                    writer.write(name + ";\n");
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
            CUtils.printMethodComment(writer, "Function used to check whether object has allowed values. Not implemented yet.");
            
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