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
import java.util.Iterator;

import javax.xml.namespace.QName;

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
                    // We use a counter appended to parameter name.
                    anyCounter += 1;
                    parameterName = parameterName + Integer.toString(anyCounter);
                    methodName = methodName + Integer.toString(anyCounter);
                }
                
                //=============================================================================
                // Write getter method
                //=============================================================================      

                CUtils.printMethodComment(c_writer, "Getter method for class member field " 
                        + parameterName + ".");
                
                c_writer.write(properParamType + asterisk + c_classname
                        + "::\nget" + methodName + "()\n{\n");

                c_writer.write("\t" + "return " + parameterName + "; \n}\n");

                //=============================================================================
                // Write setter method
                //=============================================================================  
                
                CUtils.printMethodComment(c_writer, "Setter method for class member field " 
                        + parameterName + ".");
                
                if (attribs[i].isArray())
                {   
                    c_writer.write("void " + c_classname + "::\nset"
                            + methodName + "(" + properParamType + asterisk + "pInValue)\n{\n");
                    
                    if (attribs[i].getChoiceElement())
                    {
                        c_writer.write("\t// For 'choice' you need to ensure that any\n");
                        c_writer.write("\t// other objects belonging to this union of elements are empty.\n");
                    }
                    
                    c_writer.write("\tif(" + parameterName + " == NULL)\n");
                    c_writer.write("\t\t" + parameterName + " = new " + properParamType + "();\n");                   
                    
                    c_writer.write("\t" + parameterName + "->clone( *pInValue);\n");
                    c_writer.write("}\n");
                }
                else if (isElementNillable(i)  || isElementOptional(i))
                {
                    // Setter method
                    c_writer.write("void " + c_classname + "::\nset"
                            + methodName + "(" + properParamType  
                            + " pInValue, bool deep, bool makeCopy)\n{\n");
                    
                    if (attribs[i].getChoiceElement())
                    {
                        c_writer.write("\t// For 'choice' you need to ensure that any\n");
                        c_writer.write("\t// other objects belonging to this union of elements are NULL.\n");
                    }

                    c_writer.write("\tif (__axis_deepcopy_" + parameterName + ")\n");
                    c_writer.write("\t\tdelete " + parameterName + ";\n");
                    c_writer.write("\t" + parameterName + " = NULL;\n");

                    c_writer.write("\tif (pInValue != NULL)\n");
                    c_writer.write("\t{\n");
                    c_writer.write("\t\tif (deep && makeCopy)\n");
                    c_writer.write("\t\t{\n");
                    
                    c_writer.write("\t\t\t" + parameterName + " = new " + type + "();\n");

                    c_writer.write("\t\t\t*" + parameterName + " = *pInValue;\n");
                    c_writer.write("\t\t}\n");
                    c_writer.write("\t\telse\n");
                    c_writer.write("\t\t\t" + parameterName + " = pInValue;\n");
                    c_writer.write("\t}\n");

                    c_writer.write("\t__axis_deepcopy_" + parameterName + " = deep;\n");

                    c_writer.write("}\n");
                } 
                else
                {
                    c_writer.write("void " + c_classname + "::\nset"
                            + methodName + "(" + properParamType + " InValue");
                                        
                    Type attributeType = attribs[i].getType();
                    
                    boolean isPointerType = false;
                    if (attributeType.isSimpleType())
                        isPointerType = CUtils.isPointerType(CUtils.getSimpleType(attributeType.getBaseType())); 
                    else
                        isPointerType = CUtils.isPointerType(getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]));
                    
                    if((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()) 
                            && (isPointerType || attribs[i].getAllElement() || attribs[i].getChoiceElement()))
                        c_writer.write(", bool deep, bool makeCopy");
                    
                    c_writer.write(")\n{\n");
                    
                    if (attribs[i].getChoiceElement())
                    {
                        c_writer.write("\t// For 'choice' you need to ensure that any\n");
                        c_writer.write("\t// other objects belonging to this union of elements are NULL.\n");
                    }
                    
                    if(isPointerType)
                    {
                        c_writer.write("\tif (__axis_deepcopy_" + parameterName + ")\n");
                        c_writer.write("\t\tdelete [] " + parameterName + ";\n");
                        c_writer.write("\t" + parameterName + " = NULL;\n");
                        
                        c_writer.write("\tif(InValue != NULL)\n");
                        c_writer.write("\t{\n");
                        c_writer.write("\t\tif (deep && makeCopy)\n");
                        c_writer.write("\t\t{\n");
                        c_writer.write("\t\t\t" + parameterName + " = new char[strlen(InValue) + 1];\n");
                        c_writer.write("\t\t\tstrcpy(" + parameterName + ", InValue);\n");
                        c_writer.write("\t\t}\n");
                        c_writer.write("\t\telse\n");
                        c_writer.write("\t\t\t" + parameterName + " = InValue;\n");
                        c_writer.write("\t}\n");

                        c_writer.write("\t__axis_deepcopy_" + parameterName + " = deep;\n");
                    }
                    else if ((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()) 
                                && (attribs[i].getAllElement() || attribs[i].getChoiceElement()))
                    {
                        c_writer.write("\tif (__axis_deepcopy_" + parameterName + ")\n");
                        c_writer.write("\t\tdelete " + parameterName + ";\n");
                        c_writer.write("\t" + parameterName + " = NULL;\n");

                        c_writer.write("\tif (InValue != NULL)\n");
                        c_writer.write("\t{\n");
                        c_writer.write("\t\tif (deep && makeCopy)\n");
                        c_writer.write("\t\t{\n");
                        c_writer.write("\t\t\t" + parameterName + " = new " + type + "();\n");
                        c_writer.write("\t\t\t*" + parameterName + " = *InValue;\n");
                        c_writer.write("\t\t}\n");
                        c_writer.write("\t\telse\n");
                        c_writer.write("\t\t\t" + parameterName + " = InValue;\n");
                        c_writer.write("\t}\n");

                        c_writer.write("\t__axis_deepcopy_" + parameterName + " = deep;\n");
                    }
                    else
                        c_writer.write("\t" + parameterName + " = InValue ; \n");

                    c_writer.write("}\n");
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
            CUtils.printBlockComment(c_writer, "Serialize extension.");
            
            String typeName = extensionBaseAttrib.getTypeName(); 

            if (extensionBaseAttrib.isSimpleType())
            {
                c_writer.write("\tpSZ->serializeAsChardata((void*)");
                if (!CUtils.isPointerType(typeName))
                    c_writer.write("&");    
                c_writer.write("(param->" + extensionBaseAttrib.getParamNameAsMember() + "), "
                        + CUtils.getXSDEnumeratorForType(typeName) + ");\n");
            }
            else
            {
                // TODO
            }
        }        
        else if (attribs.length == 0)
        {
            System.out.println("Possible error in class " + c_classname
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

        CUtils.printMethodComment(c_writer, "Function to serialize an object of type "  
                + c_classname + ".");        
        
        c_writer.write( "int Axis_Serialize_" + c_classname 
                     + "( " + c_classname + "* param, IWrapperSoapSerializer* pSZ, bool bArray)\n");
        c_writer.write( "{\n");
       
        //=============================================================================
        // No attributes or elements to serialize? Then serialize extension and return.
        //=============================================================================        

        if (attribs.length == 0) 
        {
            CUtils.printBlockComment(c_writer, "No attributes or elements to serialize.");
            
            c_writer.write("\tpSZ->serialize(\">\", NULL);\n");

            writeSerializeExtensionCode();
            
            c_writer.write("\treturn AXIS_SUCCESS;\n");
            c_writer.write("}\n");
            return;
        }
        
        //=============================================================================
        // NULL param passed in? Assume nillable although type does not know whether
        // it is used as a nillable parameter so this may not be the appropriate place
        // to put this, or we need to find a way to determine if nillable.
        //=============================================================================        

        CUtils.printBlockComment(c_writer, "If null input, serialize as nil element.");
        
        c_writer.write("\tif ( param == NULL )\n\t{\n");
        c_writer.write("\t\tpSZ->serializeAsAttribute( \"xsi:nil\", 0, (void*)&(xsd_boolean_true), XSD_BOOLEAN);\n");
        
        c_writer.write("\t\tpSZ->serialize( \">\", NULL);\n");
        c_writer.write("\t\treturn AXIS_SUCCESS;\n");
        c_writer.write("\t}\n");
        
        //=============================================================================
        // This is the only real difference for the serializer between rpc/encoded and 
        // doc/literal objects
        //=============================================================================        
        
        if (wscontext.getWrapperInfo().getBindingStyle().equals("rpc"))
            writeRPCArrayPortionOfSerializeGlobalMethod();
        else
            writeDOCArrayPortionOfSerializeGlobalMethod();
        
        //=============================================================================
        // Serialize attributes, if any
        //=============================================================================        

        if (attributeParamCount > 0)
            CUtils.printBlockComment(c_writer, "Serialize attributes.");
        
        for (int i = 0; i < attributeParamCount; i++)
        {
            if (attribs[i].isArray() || !(attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()))
                throw new WrapperFault("Error : an attribute is not basic type");
            
            String soapTagName = attribs[i].getParamNameAsSOAPString();

            Type attrType = attribs[i].getType();
            String basicType = null;
            
            if (!attribs[i].isSimpleType() && attrType.isSimpleType())
                basicType = CUtils.getSimpleType(attrType.getBaseType());
            else
                basicType = attribs[i].getTypeName();

            if (CUtils.isPointerType(basicType) || attribs[i].isOptional())
            {
                // TODO: Add check if ptr type and not optional and is null, throw exception.
                c_writer.write("\tif (0 != param->" + attribs[i].getParamNameAsMember() + ")\n\t");                
                c_writer.write("\tpSZ->serializeAsAttribute(\""
                        + soapTagName + "\", 0, (void*)(param->"
                        + attribs[i].getParamNameAsMember() + "), "
                        + CUtils.getXSDEnumeratorForType(basicType) + ");\n");
            }
            else
            {
                c_writer.write("\tpSZ->serializeAsAttribute(\""
                        + soapTagName + "\", 0, (void*)&(param->"
                        + attribs[i].getParamNameAsMember() + "), "
                        + CUtils.getXSDEnumeratorForType(attribs[i].getTypeName()) + ");\n");
            }
        }

        //=============================================================================
        // Serialization relating to faults
        //=============================================================================                           
                
        if (type.isFault())
        {
            c_writer.write("\tif(Axis_URI_" + c_classname + ")\n\t{\n");
            c_writer.write("\t\tbool blnIsNewPrefix = false;\n");
            c_writer.write("\t\tconst AxisChar* sPrefix = pSZ->getNamespacePrefix(Axis_URI_"
                        + c_classname + ", blnIsNewPrefix);\n");
            c_writer.write("\t\tpSZ->serialize(\" xmlns:\", sPrefix, \"=\\\"\",");
            c_writer.write("Axis_URI_" + c_classname + ", \" " + " \\\"\"");
            c_writer.write(", NULL);\n\t}\n");
        }               
        
        if (wscontext.getWrapperInfo().getBindingStyle().equals("document"))
            c_writer.write("\tpSZ->serialize( \">\", 0);\n");
        
        //=============================================================================
        // Serialize extension, if any
        //=============================================================================                           
        
        writeSerializeExtensionCode();

        //=============================================================================
        // Serialize elements, if any
        //=============================================================================                
        
        if (attributeParamCount < attribs.length)
            CUtils.printBlockComment(c_writer, "Serialize sub-elements.");

        boolean firstIfWritten = false;
        int anyCounter = 0; //counter for any types.
        String arrayType;
        
        for (int i = attributeParamCount; i < attribs.length; i++)
        {
            String namespace = "NULL";
            if (attribs[i].getNsQualified())
                namespace = "Axis_URI_" + c_classname;
            
            // if the attribute is a choice following should do
            boolean ifCheckPrinted = false;
            if (attribs[i].getChoiceElement())
            {
                if (!firstIfWritten)
                {
                    c_writer.write("\tif");
                    firstIfWritten = true;
                } 
                else
                    c_writer.write("\telse if");

                ifCheckPrinted = true;
                c_writer.write("(param->" + attribs[i].getParamNameAsMember() + ")\n\t{\n\t");
            }
            else
                firstIfWritten = false;
 
            //if the attribute is a 'all' following should do
            if (attribs[i].getAllElement())
                if (attribs[i].getMinOccurs() == 0)
                {
                    ifCheckPrinted = true;
                    c_writer.write("\tif(param->" + attribs[i].getParamNameAsMember() + ")\n\t{\n\t");
                }
             
            if (attribs[i].isAnyType())
            {
                anyCounter += 1;
                
                if (attribs[i].isOptional())
                    c_writer.write("\tif (param->any" + Integer.toString(anyCounter) + " != NULL)\n");
                                
                c_writer.write("\t\tpSZ->serializeAnyObject(param->any" + Integer.toString(anyCounter) +");\n");
            }
            else if (attribs[i].isArray())
            {
                if (attribs[i].isSimpleType() || attribs[i].getType().isSimpleType())
                {
                    String baseTypeName = null;
                    if (!attribs[i].isSimpleType() && attribs[i].getType().isSimpleType())
                        baseTypeName = CUtils.getSimpleType(attribs[i].getType().getBaseType());
                    else
                        baseTypeName = attribs[i].getTypeName();
                    
                    c_writer.write("\tpSZ->serializeBasicArray(param->" + attribs[i].getParamNameAsMember()
                        + ", " + namespace + ","
                        + CUtils.getXSDEnumeratorForType(baseTypeName) + ", \""
                        + attribs[i].getParamNameAsSOAPString() + "\");\n");
                }
                else
                {
                    arrayType = attribs[i].getTypeName();
                    
                    if (attribs[i].getNsQualified())
                        namespace = "Axis_URI_" + arrayType;
                    else
                        namespace = "NULL";
                    
                    c_writer.write("\tpSZ->serializeCmplxArray(param->" + attribs[i].getParamNameAsMember() 
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
                    baseTypeName = CUtils.getSimpleType (attribs[i].getType().getBaseType ());
                else
                    baseTypeName = typeName;
                
                if (!ifCheckPrinted && attribs[i].isOptional())
                    c_writer.write("\tif (param->" + attribs[i].getParamNameAsMember() + " != NULL)\n\t");
                
                // If the simple type is a choice it is handled
                // as a pointer variable.  This is the same in 'all' element and nillable elements.
                String ampersand = "&";
                if (CUtils.isPointerType(baseTypeName)
                            || attribs[i].getChoiceElement()
                            || attribs[i].getAllElement()
                            || isElementNillable(i) || isElementOptional(i))
                    ampersand = "";

                c_writer.write("\tpSZ->serializeAsElement(\""
                        + attribs[i].getElementNameAsSOAPString() + "\", " + namespace
                        + ", (void*)" + ampersand + "(param->" + attribs[i].getParamNameAsMember() + "), " 
                        + CUtils.getXSDEnumeratorForType(baseTypeName) + ");\n");
            }
            else
            {
                //if complex type
                String elm = attribs[i].getParamNameAsSOAPString();
                if (attribs[i].isReference())
                    elm = attribs[i].getTypeName();
                
                String tab = "";
                if (ifCheckPrinted)
                    tab = "\t";
                else if (attribs[i].isOptional())
                {
                    tab = "\t";
                    c_writer.write("\tif (param->" + attribs[i].getParamNameAsMember() + " != NULL)\n\t{\n\t");
                }
                
                if (attribs[i].getNsQualified())
                {
                    c_writer.write("\tpSZ->serialize(\"<\", pSZ->getNamespacePrefix(\""
                                    + type.getName().getNamespaceURI()
                                    + "\"), \":\", \"" + elm + "\", 0);\n");
                    c_writer.write(tab + "\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamNameAsMember() + ", pSZ);\n");
                    c_writer.write(tab + "\tpSZ->serialize(\"</\", pSZ->getNamespacePrefix(\""
                                    + type.getName().getNamespaceURI()
                                    + "\"), \":\", \"" + elm + "\", \">\", 0);\n");
                }
                else
                {
                    c_writer.write("\tpSZ->serialize(\"<" + elm + "\", 0);\n");
                    c_writer.write(tab + "\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamNameAsMember() + ", pSZ);\n");
                    c_writer.write(tab + "\tpSZ->serialize(\"</" + elm + "\", \">\", 0);\n");
                }
                
                if (!ifCheckPrinted && attribs[i].isOptional())
                    c_writer.write("\t}\n");
            }

            //end if choice element

            if (ifCheckPrinted)
                c_writer.write("\t}\n");
        }

        //=============================================================================
        // End of attribute and element serialization
        //=============================================================================                
                
        if (wscontext.getWrapperInfo().getBindingStyle().equals("rpc"))
        {
            c_writer.write("\n\tpSZ->serialize(\"</\", Axis_TypeName_" + c_classname
                    + ", \">\", NULL);\n");
        }

        CUtils.printBlockComment(c_writer, "Remove namespace, if new.");        
        
        c_writer.write("\tif (!bArray && blnIsNewPrefix)\n");
        c_writer.write("\t\tpSZ->removeNamespacePrefix(Axis_URI_" + c_classname + ");\n");
        c_writer.write("\n");
        
        c_writer.write("\treturn AXIS_SUCCESS;\n");
        c_writer.write("}\n");
    }

    /**
     * @throws IOException
     */
    private void writeDOCArrayPortionOfSerializeGlobalMethod() throws IOException
    {
        CUtils.printBlockComment(c_writer, "Serialize top-most element, possibly defining new namespace.");        
        
        // For doc/literal objects
        c_writer.write("\tbool blnIsNewPrefix = false;\n");
        c_writer.write("\tif (!bArray)\n\t{\n");
        c_writer.write("\t\tconst AxisChar* sPrefix = pSZ->getNamespacePrefix(Axis_URI_" + c_classname + ", blnIsNewPrefix);\n");
        c_writer.write("\t\tif (blnIsNewPrefix)\n");
        c_writer.write("\t\t\tpSZ->serialize(\" xmlns:\", sPrefix, \"=\\\"\", "
                        + "Axis_URI_" + c_classname + ", \"\\\"\", NULL);\n");
        c_writer.write( "\t}\n");
    }

    /**
     * @throws IOException
     */
    private void writeRPCArrayPortionOfSerializeGlobalMethod() throws IOException
    {
        // For rpc/encoded objects
        c_writer.write("\tbool blnIsNewPrefix = false;\n");
        c_writer.write( "\tif( bArray)\n");
        c_writer.write( "\t\tpSZ->serialize( \"<\", Axis_TypeName_" + c_classname + ", \">\", NULL);\n");
        c_writer.write( "\telse\n");
        c_writer.write( "\t{\n");
        c_writer.write( "\t\tconst AxisChar * sPrefix = pSZ->getNamespacePrefix( Axis_URI_" 
                + c_classname + ", blnIsNewPrefix);\n\n");
        c_writer.write( "\t\t// If there are objects that require a local namespace, then define it here.\n");
        c_writer.write( "\t\t// NB: This namespace will go out of scope when the closing tag is reached.\n");
        c_writer.write( "\t\tif( !blnIsNewPrefix)\n");
        c_writer.write( "\t\t\tpSZ->serialize( \"<\", Axis_TypeName_" + c_classname + ", " 
                    + "\" xsi:type=\\\"\", sPrefix, \":\", " 
                    + "Axis_TypeName_" + c_classname + ", \"\\\">\", NULL);\n");
        c_writer.write( "\t\telse\n");
        c_writer.write( "\t\t\tpSZ->serialize( \"<\", Axis_TypeName_" + c_classname + ", " 
                    + "\" xsi:type=\\\"\", sPrefix, \":\", " 
                    + "Axis_TypeName_" + c_classname + ", \"\\\" xmlns:\", " 
                    + "sPrefix, \"=\\\"\", Axis_URI_" + c_classname + ", \"\\\">\", NULL);\n");
        c_writer.write( "\t}\n");
    }

    private void writeDeSerializeExtensionCode() throws IOException, WrapperFault
    {  
        if (extensionBaseAttrib != null
                && extensionBaseAttrib.getTypeName() != null)
        {
            CUtils.printBlockComment(c_writer, "Deserialize extension.");
            
            if (extensionBaseAttrib.isSimpleType())
            {
                c_writer.write("\tvoid* pCharDataAs;\n");
                String typeName = extensionBaseAttrib.getTypeName();
                String xsdType = CUtils.getXSDEnumeratorForType(typeName);
                c_writer.write("\tpIWSDZ->getChardataAs(&pCharDataAs, " + xsdType + ");\n");
                c_writer.write("\tparam->" + extensionBaseAttrib.getParamNameAsMember() + " = ");
                
                if (CUtils.isPointerType(typeName))
                    c_writer.write("(" + typeName + ") pCharDataAs;\n");
                else
                {
                    c_writer.write(" *(" + typeName + "*) pCharDataAs;\n");
                    c_writer.write("\tAxis::AxisDelete( pCharDataAs, " + xsdType + ");\n");
                }    
            }
            else
            {
                // TODO
            }
        }
        else if (attribs.length == 0)
        {
            System.out.println("Possible error in class " + c_classname
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
        
        CUtils.printMethodComment(c_writer, "Function to deserialize an object of type "  
                + c_classname + ".");   
        
        c_writer.write("int Axis_DeSerialize_" + c_classname + "(" + c_classname
                + "* param, IWrapperSoapDeSerializer* pIWSDZ)\n{\n");

        //=============================================================================
        // No attributes or elements to deserialize? Then deserialize extension and return.
        //=============================================================================        

        if (attribs.length == 0)
        {
            writeDeSerializeExtensionCode();
            
            c_writer.write("\treturn AXIS_SUCCESS;\n");
            c_writer.write("}\n");
            return;
        }

        
        // Declare variables we use
        c_writer.write("\tconst char* peekedElementName;\n");
        
        //=============================================================================
        // Deserialize attributes.
        // Actually, attribute deserialization takes place in same loop as elements
        // in order to avoid duplication. But here, we put out a comment block.
        //=============================================================================        
        
        if (attributeParamCount > 0)
            CUtils.printBlockComment(c_writer, "Deserialize attributes.");
            
        //=============================================================================
        // Deserialize attributes and elements.
        //=============================================================================        
        
        String arrayType = null;
        boolean firstIfWritten = false;
        int anyCounter = 0; //counter for any types.
        int arrayCount = 0;
        
        boolean handleAll = false;
        boolean handleChoice = false;
     
        // Tabs to ensure code alignment
        String tab1  = "\t";
        String tab2  = "\t";
        
        int startingGroup=0;
        int endingGroup=0;
       
        for (int i = 0; i < attribs.length; i++)
        {
            if (i == attributeParamCount)
                CUtils.printBlockComment(c_writer, "Deserialize elements.");
            
            // If All, then the element order is arbitrary, so we need a loop.  For both
            // 'choice' and 'all', we need to do a peek. 
            if (attribs[i].getChoiceElement() || attribs[i].getAllElement())
            {
                endingGroup   = i;

                if (!firstIfWritten)
                {
                    startingGroup = i;

                    handleChoice = attribs[i].getChoiceElement();
                    handleAll    = attribs[i].getAllElement();

                    // Flag for us to know when we found element for 'choice'.
                    if (handleChoice)
                        CUtils.printComment(c_writer, "Deserialize \"choice\" group of elements."); 
                    else if (handleAll)
                    {
                        CUtils.printComment(c_writer, "Deserialize \"all\" group of elements."); 
                        
                        c_writer.write("\twhile (true)\n\t{\n");
                        
                        // Need to adjust tabs since we will be in a loop
                        tab1 = "\t\t";
                        tab2 = "\t\t";
                    }
                    
                    // for choice and all, we need to do a peek.
                    c_writer.write(tab1 + "peekedElementName=pIWSDZ->peekNextElementName();\n");

                    if (handleAll)
                    {
                        c_writer.write(tab1 + "if (0x00 == *peekedElementName)\n");
                        c_writer.write(tab1 + "\tbreak;\n");
                    }

                    c_writer.write("\n");
                   
                    c_writer.write(tab1 + "if ");
                    firstIfWritten = true;
                } 
                else
                {
                    c_writer.write(tab1 + "else if ");
                    if (handleAll)
                       tab2 = "\t\t";
                    else if (handleChoice)
                       tab2  = "\t";
                }

                c_writer.write("(strcmp(peekedElementName,\""
                        + attribs[i].getElementNameAsSOAPString() + "\")==0)\n");
                c_writer.write(tab1 + "{\n");

                if (handleAll)
                {
                    c_writer.write(tab1 + "\tif (param->" + attribs[i].getParamNameAsMember() + ")\n");
                    c_writer.write(tab1 + "\t\tthrow RedundantElementException(peekedElementName);\n\n");
                }
            }
            else
            {       
                if (firstIfWritten)
                    endChoiceOrAll(handleAll, handleChoice, tab1, startingGroup, endingGroup);
                
                tab1  = "\t";
                tab2  = "\t";
                
                firstIfWritten = false;
                handleAll = false;
                handleChoice = false;
            }
            
            if (handleAll || handleChoice)
                tab2 += "\t";
            
            if (attribs[i].isAnyType())
            {
                anyCounter +=1;
                c_writer.write(tab2 + "param->any" + Integer.toString(anyCounter)+ " = pIWSDZ->getAnyObject();\n");
            }
            else if (attribs[i].isArray())
            {
                arrayCount++;
                
                if (attribs[i].isSimpleType() || attribs[i].getType().isSimpleType())
                {
                    String baseTypeName = null;
                    if (!attribs[i].isSimpleType() && attribs[i].getType().isSimpleType())
                        baseTypeName = CUtils.getSimpleType(attribs[i].getType().getBaseType());
                    else
                        baseTypeName = attribs[i].getTypeName();
                    
                    c_writer.write(tab2 + "Axis_Array * array" + arrayCount + " = pIWSDZ->getBasicArray("
                            + CUtils.getXSDEnumeratorForType(baseTypeName) + ", \""
                            + attribs[i].getParamNameAsSOAPString()
                            + "\",0);\n");
                    c_writer.write(tab2 + "if(param->" + attribs[i].getParamNameAsMember() + " == NULL)\n");
                    c_writer.write(tab2 + "\tparam->" + attribs[i].getParamNameAsMember() + " = new " + attribs[i].getTypeName() + "_Array();\n");
                    c_writer.write(tab2 + "param->" + attribs[i].getParamNameAsMember() + "->clone( *array" + arrayCount + ");\n");
                    c_writer.write(tab2 + "Axis::AxisDelete((void*) array" + arrayCount + ", XSD_ARRAY);\n\n");
                }
                else
                {
                    arrayType = attribs[i].getTypeName();
                    c_writer.write(tab2 + "if(param->" + attribs[i].getParamNameAsMember() + " == NULL)\n");
                    c_writer.write(tab2 + "\tparam->" + attribs[i].getParamNameAsMember() + " = new " + arrayType + "_Array();\n");
                    c_writer.write(tab2 + "pIWSDZ->getCmplxArray(param->" + attribs[i].getParamNameAsMember() 
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
                if (attribs[i].isOptional() && !attribs[i].isAttribute() && !handleAll && !handleChoice)
                {
                    c_writer.write(tab1 + "peekedElementName = pIWSDZ->peekNextElementName();\n");
                    c_writer.write(tab1 + "if (strcmp(peekedElementName, \"" + soapTagName + "\") == 0)\n");
                    c_writer.write(tab1 + "{\n");
                    
                    tab2 += "\t";
                }
                
                Type type = attribs[i].getType();
                boolean isPointerType = false;
                if (type.isSimpleType())
                    isPointerType = CUtils.isPointerType(CUtils.getSimpleType(type.getBaseType())); 
                else
                    isPointerType = CUtils.isPointerType(attribs[i].getTypeName());

                String typeName = attribs[i].getTypeName();
                String baseTypeName = null;
                if (type.isSimpleType())
                    baseTypeName = CUtils.getSimpleType (type.getBaseType ());
                else
                    baseTypeName = typeName;
                
                if( isPointerType)
                {
                    c_writer.write(tab2 + typeName + " pValue" + i + " = pIWSDZ->" +
                            CUtils.getDeserializerMethodName(baseTypeName, attribs[i].isAttribute()) +
                            "(\"" + soapTagName + "\", 0);\n");
                }
                else
                {
                    c_writer.write(tab2 + typeName + " * pValue" + i + " = pIWSDZ->" +
                            CUtils.getDeserializerMethodName(baseTypeName, attribs[i].isAttribute()) +
                            "(\"" + soapTagName + "\", 0);\n");
                }
                
                // All these fields are pointers, so we should be able to pass ownership of 
                // deserialized object to object instance.
                if (attribs[i].isNillable() ||
                        isElementNillable(i) ||
                        isElementOptional(i) ||
                        attribs[i].getChoiceElement() ||
                        attribs[i].getAllElement() ||
                        attribs[i].isOptional() ||
                        isPointerType)
                {
                    c_writer.write(tab2 + "param->set" + attribs[i].getMethodName() 
                            + "(pValue" + i + ", true, false);\n");
                } 
                else
                {   
                    c_writer.write(tab2 + "if (pValue" + i + ")\n");
                    c_writer.write(tab2 + "{\n");
                    c_writer.write(tab2 + "\tparam->set" + attribs[i].getMethodName() + "(*pValue" + i + ");\n");
                    c_writer.write(tab2 + "\tAxis::AxisDelete((void *)pValue" + i 
                            + ", " + CUtils.getXSDEnumeratorForType( attribs[i].getTypeName()) + ");\n");
                    c_writer.write(tab2 + "}\n");                        
                }
                
                // TODO - remove this chunk of code...?
                if (attribs[i].isOptional() && !attribs[i].isAttribute() && !handleAll && !handleChoice)
                {
                    c_writer.write(tab1 + "}\n");
                    c_writer.write(tab1 + "else\n");
                    c_writer.write(tab1 + "\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                }
            }
            else
            {
                //if complex type
                String soapTagName = attribs[i].getParamNameAsSOAPString();
                
                if (attribs[i].isOptional() && !handleAll && !handleChoice)
                {
                    c_writer.write(tab1 + "peekedElementName = pIWSDZ->peekNextElementName();\n");
                    c_writer.write(tab1 + "if (strcmp(peekedElementName, \"" + soapTagName + "\") == 0)\n");
                    
                    tab2 += "\t";
                }

                c_writer.write(tab2 + "param->" + attribs[i].getParamNameAsMember()
                        + " = (" + attribs[i].getTypeName()
                        + "*)pIWSDZ->getCmplxObject((void*)Axis_DeSerialize_" + attribs[i].getTypeName()
                        + ", (void*)Axis_Create_" + attribs[i].getTypeName() 
                        + ", (void*)Axis_Delete_" + attribs[i].getTypeName() 
                        + ", \"" + soapTagName + "\", Axis_URI_" + attribs[i].getTypeName() + ");\n");
                
                // TODO remove following chunk of code...?
                if (attribs[i].isOptional() && !handleAll && !handleChoice)
                {
                    c_writer.write(tab1 + "else\n");
                    c_writer.write(tab1 + "\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                }
            }

            if (attribs[i].getChoiceElement() || attribs[i].getAllElement())
                c_writer.write(tab1 + "}\n");
            else
                c_writer.write("\n");
        } // end for-loop
        
        if (firstIfWritten)
            endChoiceOrAll(handleAll, handleChoice, tab1, startingGroup, endingGroup);
        
        //=============================================================================
        // Deserialize extension, if any, and return status
        //=============================================================================                           
        
        writeDeSerializeExtensionCode();
        
        //=============================================================================
        // Ensure there are no more elements - there should not be!
        //=============================================================================                           
        c_writer.write("\n");
        
        CUtils.printBlockComment(c_writer, "Ensure no extraneous elements.");            
        c_writer.write("\tpeekedElementName = pIWSDZ->peekNextElementName();\n");
        c_writer.write("\tif (0x00 != *peekedElementName)\n");
        c_writer.write("\t\tthrow UnknownElementException(peekedElementName);\n");
        
        c_writer.write("\n");
        c_writer.write("\treturn pIWSDZ->getStatus();\n");
        c_writer.write("}\n");
    }
    
    private void endChoiceOrAll(boolean handleAll, 
            boolean handleChoice, 
            String tab1,
            int startGroup, int endGroup)  throws IOException    
    {
        // If xsd:all xsd:choice - an unknown element check - throw exception.

        if (handleAll)
        {
            c_writer.write(tab1 + "else\n");
            c_writer.write(tab1 + "\tthrow UnknownElementException(peekedElementName);\n");
            
            // Closes for loop
            c_writer.write("\t}\n");
            
            // Verify all fields set if possible.
            boolean commentPrinted = false;
            for (int j = startGroup; j <= endGroup; j++) 
                if (attribs[j].getAllElement() && !attribs[j].isArray()
                        && !attribs[j].isOptional() && !attribs[j].isNillable()
                        && attribs[j].getMinOccurs() != 0)
                {
                    if (!commentPrinted)
                    {
                        CUtils.printComment(c_writer, "Ensure no missing elements in \"all\" group."); 
                        commentPrinted = true;
                    }

                    c_writer.write("\tif (param->" + attribs[j].getParamNameAsMember() + " == NULL)");
                    c_writer.write(" throw ElementMissingException(\"" + attribs[j].getParamNameAsMember() + "\");\n");
                }
        }
        
        c_writer.write("\n");
    }

    private void writeCreateGlobalMethod() throws IOException
    {
        CUtils.printMethodComment(c_writer, "Function used to create objects of type " 
                + c_classname + ".");
        
        c_writer.write("void* Axis_Create_" + c_classname + "(int nSize)\n");
        c_writer.write("{\n");
        c_writer.write("\tif (nSize > 0)\n");
        c_writer.write("\t{\n");
        c_writer.write("\t\t" + c_classname + "** pNew = new " + c_classname + "* [nSize];\n");
        c_writer.write("\t\tfor (int i=0; i < nSize; ++i)\n");
        c_writer.write("\t\t\tpNew[i] = new " + c_classname + ";\n");
        c_writer.write("\t\treturn pNew;\n");
        c_writer.write("\t}\n");
        c_writer.write("\telse\n");
        c_writer.write("\t\treturn new " + c_classname + ";\n");
        c_writer.write("}\n");
        c_writer.write("\n");
    }

    private void writeDeleteGlobalMethod() throws IOException
    {
        CUtils.printMethodComment(c_writer, "Function used to delete objects of type " 
                + c_classname + ".");
        
        c_writer.write("void Axis_Delete_" + c_classname + "(" + c_classname + "* param, int nSize)\n");
        c_writer.write("{\n");
        
        c_writer.write("\t// If null just return.\n");
        c_writer.write("\tif (!param)\n");
        c_writer.write("\t\treturn;\n\n");
        
        c_writer.write("\t// Reclaim array objects if array.\n");
        c_writer.write("\tif (nSize > 0)\n");
        c_writer.write("\t{\n");
        c_writer.write("\t\tfor (int count = 0 ; count < nSize ; count++ )\n");
        c_writer.write("\t\t{\n");
        c_writer.write("\t\t\tif ( (( " + c_classname + " ** ) param)[count])\n");
        c_writer.write("\t\t\t{\n");
        c_writer.write("\t\t\t\tdelete (( " + c_classname + " ** ) param)[count];\n");
        c_writer.write("\t\t\t\t(( " + c_classname + " ** ) param)[count] = NULL;\n");
        c_writer.write("\t\t\t}\n");
        c_writer.write("\t\t}\n");
        c_writer.write("\t\tdelete [] ( " + c_classname + " ** ) param;\n");
        c_writer.write("\t}\n");
        c_writer.write("\telse\n");
        c_writer.write("\t\tdelete param;\n");
        c_writer.write("}\n");
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
            CUtils.printMethodComment(c_writer, "Constructor for class " + c_classname + ".");
            
            c_writer.write(c_classname + "::\n" + c_classname + "()\n{\n");
            writeReset(true);
            c_writer.write("}\n");

            // Write copy constructor
            writeCopyConstructor();
            
            // Write reset method
            writeReset(false);
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
            CUtils.printMethodComment(c_writer, "Copy constructor for class " + c_classname + ".");            
            c_writer.write(c_classname + "::\n" + c_classname + "(const " + c_classname + " & original)\n{\n");

            writeReset(true);
            c_writer.write("\n");

            
            // AXISCPP-918 patch provided by Franz Fehringer
            if (extensionBaseAttrib != null && extensionBaseAttrib.getTypeName() != null)
            {
                if (extensionBaseAttrib.isSimpleType())
                    c_writer.write("\t" + extensionBaseAttrib.getParamNameAsMember() + " = " + "original." + extensionBaseAttrib.getParamNameAsMember() + ";\n");
                else
                {
                    // TODO
                }
            }
            // End of AXISCPP-918

            // Set fields in SoapFaultException parent class if fault
            if (type.isFault())
            {
                c_writer.write("\tsetFaultCode(original.getFaultCode());\n");
                c_writer.write("\tsetFaultString(original.getFaultString());\n");
                c_writer.write("\tsetFaultActor(original.getFaultActor());\n");
            }
            
            int anyCounter = 0;
            for (int i = 0 ; i < attribs.length ; i++)
            {
                if (i != 0)
                    c_writer.write("\n");

                if (attribs[i].isArray())
                {    
                    c_writer.write("\tif (original." + attribs[i].getParamNameAsMember() + " != NULL)\n");
                    c_writer.write("\t\t" + attribs[i].getParamNameAsMember() + " = new " 
                            + attribs[i].getTypeName() + "_Array(*original." 
                            + attribs[i].getParamNameAsMember() + ");\n");
                }
                else if (attribs[i].isAnyType())
                {
                    anyCounter++;
                    c_writer.write("\tif (original." + attribs[i].getParamNameAsMember() + anyCounter + " != NULL)\n");
                    c_writer.write("\t\t" + attribs[i].getParamNameAsMember() + anyCounter + " = new " + attribs[i].getTypeName() + "(*(original." + attribs[i].getParamNameAsMember() + anyCounter + "));\n");
                }
                else
                {
                    Type type = attribs[i].getType();
                    boolean isPointerType = false;
                    if (type.isSimpleType())
                        isPointerType = CUtils.isPointerType(CUtils.getSimpleType(type.getBaseType())); 
                    else
                        isPointerType = CUtils.isPointerType(attribs[i].getTypeName());
    
                    if ((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()) && (isPointerType || attribs[i].isOptional() || attribs[i].isNillable() || attribs[i].getChoiceElement() || attribs[i].getAllElement()))
                        c_writer.write("\tset" + attribs[i].getMethodName() + "(original." + attribs[i].getParamNameAsMember() + ", original.__axis_deepcopy_" + attribs[i].getParamNameAsMember() + ");\n");
                    else if (attribs[i].isSimpleType())
                    {
                        c_writer.write("\t" + attribs[i].getParamNameAsMember() + " = original." 
                                + attribs[i].getParamNameAsMember() + ";\n");
                    }
                    else
                    {
                        c_writer.write("\tif (original." + attribs[i].getParamNameAsMember() + " != NULL)\n");
                        c_writer.write("\t\t" + attribs[i].getParamNameAsMember() + " = new " 
                                + attribs[i].getTypeName() + "(*(original." 
                                + attribs[i].getParamNameAsMember() + "));\n");
                    }
                }
            }
            c_writer.write("}\n");
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
    protected void writeReset(boolean forConstructor) throws WrapperFault
    {
        try
        {
            if (!forConstructor)
            {
                CUtils.printMethodComment(c_writer, "Method to initialize objects of class " + c_classname + ".");
            
                c_writer.write("void " + c_classname + "::\nreset()\n{\n");
            }

            int anyCounter = 0;
            
            for(int i = 0; i< attribs.length;i++)
            {
                String name = attribs[i].getParamNameAsMember();
                String typename = attribs[i].getTypeName();
                
                Type type = attribs[i].getType();
                boolean isPointerType = false;
                if (type.isSimpleType())
                    isPointerType = CUtils.isPointerType(CUtils.getSimpleType(type.getBaseType())); 
                else
                    isPointerType = CUtils.isPointerType(typename);
                
                if(attribs[i].isArray())
                {
                    if (!forConstructor)
                        c_writer.write("\tdelete " + name + ";\n");
                    c_writer.write("\t"+ name + " = NULL;\n\n");
                }
                else if (attribs[i].isAnyType())
                {
                    anyCounter += 1;
                    name = name + Integer.toString(anyCounter);
                    
                    if (!forConstructor)
                    {
                        c_writer.write("\tif ("+name+") \n\t{\n");
                        c_writer.write("\t\tfor (int i=0; i<"+name+"->_size; i++)\n");
                        c_writer.write("\t\t\tdelete [] "+name+"->_array[i];\n");
                        c_writer.write("\t\tdelete "+name+";\n");
                        c_writer.write("\t}\n");
                    }
                    c_writer.write("\t" + name + "= NULL;\n\n");
                }
                else if (!(attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()))
                {
                    if (!forConstructor)
                        c_writer.write("\tdelete " + name + ";\n");
                    c_writer.write("\t" + name + "= NULL;\n\n");
                }
                else if (isPointerType || isElementNillable(i) || isElementOptional(i) 
                        || attribs[i].getChoiceElement() || attribs[i].getAllElement())
                {
                    if (!forConstructor)
                    {
                        c_writer.write("\tif(__axis_deepcopy_" + name + ")\n");
                        c_writer.write("\t\tdelete ");
                        if (isPointerType)
                            c_writer.write("[] ");
                        c_writer.write(name + ";\n");
                    }
                    
                    c_writer.write("\t" + name + " = NULL;\n");
                    c_writer.write("\t__axis_deepcopy_" + name + " = false;\n\n");
                }
            }
            
            if (!forConstructor)
                c_writer.write("}\n");
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
            CUtils.printMethodComment(c_writer, "Destructor for class " + c_classname + ".");
            
            if (type.isFault())
                c_writer.write(c_classname + "::\n~" + c_classname + "() throw ()\n{\n");
            else
                c_writer.write(c_classname + "::\n~" + c_classname + "()\n{\n");

            c_writer.write("\treset();\n");

            c_writer.write("}\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    protected void writeRestrictionCheckerFunction() throws WrapperFault
    {
        //TODO write code to check the restrictions.
        try
        {
            CUtils.printMethodComment(c_writer, "Function used to check whether object has allowed values. Not implemented yet.");
            
            boolean isPtrType = CUtils.isPointerType( CUtils.getSimpleType( type.getBaseType()));
            
            c_writer.write("int Check_Restrictions_" + c_classname + "(" + c_classname + " value)\n"); 
            c_writer.write("{\n");

            Iterator i = type.getEnumerationdata().iterator();
            if (i.hasNext())
            {
                // The first entry is the base type...consume it.
                i.next();
                int iIndex=0;
                
                while( i.hasNext())
                {
                    if( iIndex == 0)
                    {
                        c_writer.write( "//\tif (");
                        iIndex++;
                    }
                    else
                        c_writer.write( " ||\n//\t    ");
                    
                    QName qnElement = (QName) i.next();
                    
                    if (isPtrType)
                        c_writer.write( "!strcmp( value, " + c_classname+ "_" + qnElement.getNamespaceURI() + ")");
                    else
                        c_writer.write( "value == ENUM" + c_classname.toUpperCase()+ "_" + qnElement.getNamespaceURI());
                }
                
                if (iIndex != 0)
                {
                    c_writer.write( "//)\n//\t{\n");
                    c_writer.write( "//\t\treturn 1;\n");
                    c_writer.write( "//\t}\n");
                }
            }
            
            c_writer.write( "\n\treturn 0;\n");
            c_writer.write("}\n");
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