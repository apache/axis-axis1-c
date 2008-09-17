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

package org.apache.axis.wsdl.wsdl2ws.c;

import java.io.IOException;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

/**
 * Genarate a webservice for the complex types likes structs.
 * 
 * @author hemapani
 */

public class BeanParamWriter extends ParamCFileWriter
{
    public BeanParamWriter(WebServiceContext wscontext, Type type)
        throws WrapperFault
    {
        super(wscontext, type);
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.c.ParamCFileWriter#writeGlobalCodes()
     */
    protected void writeGlobalCodes() throws WrapperFault
    {
        try
        {
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
    
    private void writeSerializeExtensionCode()  throws IOException, WrapperFault
    {
        // TODO: xsd:extension not fully or correctly supported.
        if (extensionBaseAttrib != null)
        {
            CUtils.printBlockComment(c_writer, "Serialize extension.");
            
            String typeName = extensionBaseAttrib.getTypeName(); 

            if (extensionBaseAttrib.isSimpleType())
            {
                c_writer.write("\taxiscSoapSerializerSerializeAsChardata(pSZ,(void*)");                
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
        CUtils.printMethodComment(c_writer, "Function to serialize an object of type "  
                + c_classname + ".");  
        
        c_writer.write("int Axis_Serialize_" + c_classname
                + "(" + c_classname + "* param, AXISCHANDLE pSZ, AxiscBool bArray)\n");
        c_writer.write( "{\n");
        
        //=============================================================================
        // No attributes or elements to serialize? Then serialize extension and return.
        //=============================================================================        

        if (attribs.length == 0)
        {
            CUtils.printBlockComment(c_writer, "No attributes or elements to serialize.");
        
            c_writer.write("\taxiscSoapSerializerSerialize(pSZ,\">\", NULL);\n");

            writeSerializeExtensionCode();
            
            c_writer.write("\treturn AXISC_SUCCESS;\n");
            c_writer.write("}\n");
            return;
        }
        
        //=============================================================================
        // NULL param passed in? Assume nillable although type does not know whether
        // it is used as a nillable parameter so this may not be the appropriate place
        // to put this, or we need to find a way to determine if nillable.
        //=============================================================================        
        
        c_writer.write("\tAxiscBool blnIsNewPrefix = xsdc_boolean_false;\n\n");

        CUtils.printBlockComment(c_writer, "If null input, serialize as nil element.");
        
        c_writer.write("\tif ( param == NULL )\n\t{\n");
        c_writer.write("\t\taxiscSoapSerializerSerializeAsAttribute(pSZ, \"xsi:nil\", 0, (void*)&(xsdc_boolean_true), XSDC_BOOLEAN);\n");

        c_writer.write("\t\taxiscSoapSerializerSerialize(pSZ, \">\", NULL);\n");
        c_writer.write("\t\treturn AXISC_SUCCESS;\n");
        c_writer.write("\t}\n");
        
        //=============================================================================
        // Serialize 
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
            
            Type type = attribs[i].getType();
            String basicType = null;
            
            if (!attribs[i].isSimpleType() && type.isSimpleType())
                basicType = CUtils.getSimpleType(type.getBaseType());
            else
                basicType = attribs[i].getTypeName();

            if (CUtils.isPointerType(basicType) || attribs[i].isOptional())
            {
                // TODO: Add check if ptr type and not optional and is null, throw exception.
                c_writer.write("\tif (0 != param->" + attribs[i].getParamNameAsMember() + ")\n\t");
                c_writer.write("\taxiscSoapSerializerSerializeAsAttribute(pSZ,\""
                        + attribs[i].getParamNameAsSOAPString() + "\", 0, (void*)(param->"
                        + attribs[i].getParamNameAsMember() + "), "
                        + CUtils.getXSDEnumeratorForType(basicType) + ");\n");
            }
            else
            {
                c_writer.write("\taxiscSoapSerializerSerializeAsAttribute(pSZ,\""
                        + attribs[i].getParamNameAsSOAPString() + "\", 0, (void*)&(param->"
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
            c_writer.write("\t\tAxiscBool blnIsNewPrefix = xsdc_boolean_false;\n");
            c_writer.write("\t\tconst AxiscChar* sPrefix = axiscSoapSerializerGetNamespacePrefix(pSZ,Axis_URI_"
                        + c_classname + ", &blnIsNewPrefix);\n");
            c_writer.write("\t\taxiscSoapSerializerSerialize(pSZ, \" xmlns:\", sPrefix, \"=\\\"\",");
            c_writer.write("Axis_URI_" + c_classname + ", \" " + " \\\"\"");
            c_writer.write(", NULL);\n\t}\n");
        }               
        
        if (wscontext.getWrapperInfo().getBindingStyle().equals("document"))
            c_writer.write("\taxiscSoapSerializerSerialize(pSZ, \">\", 0);\n");
        
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
             
            if (attribs[i].isAnyTypeOrAnyElement())
            {
                String fieldName = attribs[i].getParamNameAsMember();
            
                if (attribs[i].getType().isAnyElement())
                {
                    anyCounter += 1;
                    fieldName  = "any" + Integer.toString(anyCounter);
                }
                    
                if (!ifCheckPrinted && attribs[i].isOptional())
                    c_writer.write("\tif (param->" + fieldName + " != NULL)\n");
                                          
                c_writer.write("\t\taxiscSoapSerializerSerializeAnyObject(pSZ, param->" + fieldName +");\n");
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
                    
                    c_writer.write("\taxiscSoapSerializerSerializeBasicArray(pSZ, (const Axisc_Array *)param->" + attribs[i].getParamNameAsMember()
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
                    
                    c_writer.write("\taxiscSoapSerializerSerializeCmplxArray(pSZ, (const Axisc_Array *)param->"
                            + attribs[i].getParamNameAsMember() 
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
                
                c_writer.write("\taxiscSoapSerializerSerializeAsElement(pSZ, \""
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
                    c_writer.write("\taxiscSoapSerializerSerialize(pSZ, \"<\", axiscSoapSerializerGetNamespacePrefix(pSZ, \""
                                    + type.getName().getNamespaceURI()
                                    + "\", NULL), \":\", \"" + elm + "\", 0);\n");
                    c_writer.write(tab + "\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamNameAsMember() + ", pSZ, 0);\n");
                    c_writer.write(tab + "\taxiscSoapSerializerSerialize(pSZ, \"</\", axiscSoapSerializerGetNamespacePrefix(pSZ, \""
                                    + type.getName().getNamespaceURI()
                                    + "\", NULL), \":\", \"" + elm + "\", \">\", 0);\n");
                }
                else
                {
                    c_writer.write("\taxiscSoapSerializerSerialize(pSZ, \"<" + elm + "\", 0);\n");
                    c_writer.write(tab + "\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamNameAsMember() + ", pSZ, 0);\n");
                    c_writer.write(tab + "\taxiscSoapSerializerSerialize(pSZ, \"</" + elm + "\", \">\", 0);\n");
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
            c_writer.write("\n\taxiscSoapSerializerSerialize(pSZ, \"</\", Axis_TypeName_" + c_classname
                    + ", \">\", NULL);\n");
        }

        CUtils.printBlockComment(c_writer, "Remove namespace, if new.");        
        
        c_writer.write("\tif (!bArray && blnIsNewPrefix)\n");
        c_writer.write("\t\taxiscSoapSerializerRemoveNamespacePrefix(pSZ, Axis_URI_" + c_classname + ");\n");
        c_writer.write("\n");
        
        c_writer.write("\treturn AXISC_SUCCESS;\n");
        c_writer.write("}\n");
    }

    /**
     * @throws IOException
     */
    private void writeDOCArrayPortionOfSerializeGlobalMethod() throws IOException
    {
        CUtils.printBlockComment(c_writer, "Serialize top-most element, possibly defining new namespace.");        
        
        // For doc/literal objects
        c_writer.write("\tif (!bArray)\n\t{\n");
        c_writer.write("\t\tconst AxiscChar* sPrefix = axiscSoapSerializerGetNamespacePrefix(pSZ,Axis_URI_" + c_classname + ", &blnIsNewPrefix);\n");
        c_writer.write("\t\tif (blnIsNewPrefix)\n");
        c_writer.write("\t\t\taxiscSoapSerializerSerialize(pSZ,\" xmlns:\", sPrefix, \"=\\\"\", " 
                        + "Axis_URI_" + c_classname + ", \"\\\"\", NULL);\n");
        c_writer.write("\t}\n");
    }

    /**
     * @throws IOException
     */
    private void writeRPCArrayPortionOfSerializeGlobalMethod() throws IOException
    {
        // For rpc/encoded objects
        c_writer.write( "\tif( bArray)\n");
        c_writer.write( "\t\taxiscSoapSerializerSerialize(pSZ, \"<\", Axis_TypeName_" + c_classname + ", \">\", NULL);\n");
        c_writer.write( "\telse\n");
        c_writer.write( "\t{\n");
        c_writer.write( "\t\tconst AxiscChar * sPrefix = axiscSoapSerializerGetNamespacePrefix(pSZ, Axis_URI_" 
                + c_classname + ", &blnIsNewPrefix);\n\n");
        c_writer.write( "\t\t// If there are objects that require a local namespace, then define it here.\n");
        c_writer.write( "\t\t// NB: This namespace will go out of scope when the closing tag is reached.\n");
        c_writer.write( "\t\tif( !blnIsNewPrefix)\n");
        c_writer.write( "\t\t\taxiscSoapSerializerSerialize(pSZ, \"<\", Axis_TypeName_" + c_classname + ", " 
                    + "\" xsi:type=\\\"\", sPrefix, \":\", "
                    + "Axis_TypeName_" + c_classname + ", \"\\\">\", NULL);\n");
        c_writer.write( "\t\telse\n");
        c_writer.write( "\t\t\taxiscSoapSerializerSerialize(pSZ, \"<\", Axis_TypeName_" + c_classname + ", " 
                    + "\" xsi:type=\\\"\", sPrefix, \":\", " 
                    + "Axis_TypeName_" + c_classname + ", \"\\\" xmlns:\", " 
                    + "sPrefix, \"=\\\"\", Axis_URI_" + c_classname + ", \"\\\">\", NULL);\n");
        c_writer.write("\t}\n");
    }

    private void writeDeSerializeExtensionCode() throws IOException, WrapperFault
    {  
        if (extensionBaseAttrib != null
                && extensionBaseAttrib.getTypeName() != null)
        {
            CUtils.printBlockComment(c_writer, "Deserialize extension.");
            
            if (extensionBaseAttrib.isSimpleType())
            {
                c_writer.write("\t{\n"); // ==== begin scope
                c_writer.write("\t\tvoid* pCharDataAs;\n\n");
                String typeName = extensionBaseAttrib.getTypeName();
                String xsdType = CUtils.getXSDEnumeratorForType(typeName);
                c_writer.write("\t\taxiscSoapDeSerializerGetChardataAs(pDZ, &pCharDataAs, " + xsdType + ");\n");
                c_writer.write("\t\tparam->" + extensionBaseAttrib.getParamNameAsMember() + " = ");
                
                if (CUtils.isPointerType(typeName))
                    c_writer.write("(" + typeName + ") pCharDataAs;\n");
                else
                {
                    c_writer.write(" *(" + typeName + "*) pCharDataAs;\n");
                    c_writer.write("\t\taxiscAxisDelete(pCharDataAs, " + xsdType + ");\n");
                }      
                c_writer.write("\t}\n"); // ==== end scope
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
        CUtils.printMethodComment(c_writer, "Function to deserialize an object of type "  
                + c_classname + ".");  
        
        c_writer.write("int Axis_DeSerialize_" + c_classname + "(" + c_classname 
                + "* param, AXISCHANDLE pDZ)\n{\n");

        //=============================================================================
        // No attributes or elements to deserialize? Then deserialize extension and return.
        //=============================================================================        
       
        if (attribs.length == 0)
        {
            writeDeSerializeExtensionCode();

            c_writer.write("\treturn AXISC_SUCCESS;\n");
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
                    else
                    {
                        CUtils.printComment(c_writer, "Deserialize \"all\" group of elements."); 
                        
                        c_writer.write("\twhile (1)\n\t{\n");
                        
                        // Need to adjust tabs since we will be in a loop
                        tab1 = "\t\t";
                        tab2 = "\t\t";
                    }
                    
                    // for choice and all, we need to do a peek.
                    c_writer.write(tab1 + "peekedElementName=axiscSoapDeSerializerPeekNextElementName(pDZ);\n");

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
                    c_writer.write(tab1 + "\t\taxiscAxisGenerateRedundantElementException(peekedElementName);\n\n");
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
            
            if (attribs[i].isAnyTypeOrAnyElement())
            {
                String fieldName = attribs[i].getParamNameAsMember();
                
                if (attribs[i].getType().isAnyElement())
                {
                    anyCounter += 1;
                    fieldName  = "any" + Integer.toString(anyCounter);
                }
                
                c_writer.write(tab2 + "param->" + fieldName + " = axiscSoapDeSerializerGetAnyObject(pDZ);\n");
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

                    c_writer.write(tab2 + "if (param->" + attribs[i].getParamNameAsMember() + " != NULL)\n");
                    c_writer.write(tab2 + "{\n");
                    c_writer.write(tab2 + "\taxiscAxisDelete(param->" + attribs[i].getParamNameAsMember() + ", XSDC_ARRAY);\n");
                    c_writer.write(tab2 + "\tparam->" + attribs[i].getParamNameAsMember() + "= NULL;\n");
                    c_writer.write(tab2 + "}\n");
                    c_writer.write("\n");
                 
                    c_writer.write(tab2 + "param->" + attribs[i].getParamNameAsMember() 
                            + " = (" + baseTypeName + "_Array *)" 
                            + "axiscSoapDeSerializerGetBasicArray(pDZ, " 
                            + CUtils.getXSDEnumeratorForType(baseTypeName) + ", \"" 
                            + attribs[i].getParamNameAsSOAPString() + "\",0);\n");
                }
                else
                {
                    arrayType = attribs[i].getTypeName();
                    c_writer.write(tab1 + "axiscSoapDeSerializerGetCmplxArray(pDZ, (Axisc_Array *)param->" + attribs[i].getParamNameAsMember() 
                            + ", (void*)Axis_DeSerialize_"  + arrayType 
                            + ", (void*)Axis_Create_" + arrayType 
                            + ", (void*)Axis_Delete_" + arrayType 
                            + ", \""  + attribs[i].getElementNameAsSOAPString() + "\", Axis_URI_" + arrayType + ");\n");
                }
            }
            else if ((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()))
            {                
                String soapTagName = (attribs[i].isAttribute() ? attribs[i].getParamNameAsSOAPString() : attribs[i].getElementNameAsSOAPString());
                
                // We only peek for elements, not element attributes!
                if (attribs[i].isOptional() && !attribs[i].isAttribute() && !handleAll && !handleChoice)
                {
                    c_writer.write(tab1 + "peekedElementName = axiscSoapDeSerializerPeekNextElementName(pDZ);\n");
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
                
                if (attribs[i].isNillable() ||
                        isElementNillable(i) ||
                        isElementOptional(i) ||
                        attribs[i].getChoiceElement() ||
                        attribs[i].getAllElement() ||
                        attribs[i].isOptional() ||
                        isPointerType)                
                {
                    c_writer.write(tab2 + "param->"
                            + attribs[i].getParamNameAsMember() + " = "
                            + "axiscSoapDeSerializer"
                            + CUtils.getDeserializerMethodName(
                                    attribs[i].getTypeName(), attribs[i].isAttribute()) + "(pDZ, \""
                            + soapTagName + "\",0);\n");
                }                
                else
                {
                    String elementNameToSearchFor = attribs[i].isAttribute()? attribs[i].getParamNameAsSOAPString():attribs[i].getElementNameAsSOAPString();
                    
                    c_writer.write(tab2 + "{\n"); // start local scope
                    
                    c_writer.write(tab2 + "\t" + attribs[i].getTypeName() + " * "
                        + attribs[i].getParamNameAsMember() + " = " 
                        + "axiscSoapDeSerializer"
                        + CUtils.getDeserializerMethodName(attribs[i].getTypeName(), attribs[i].isAttribute()) 
                        + "(pDZ, \"" + elementNameToSearchFor + "\",0);\n");
                    
                    c_writer.write(tab2 + "\tif (" + attribs[i].getParamNameAsMember() + " != NULL)\n");
                    c_writer.write(tab2 + "\t{\n");
                    c_writer.write(tab2 + "\t\tparam->" + attribs[i].getParamNameAsMember() + " = *"
                            + attribs[i].getParamNameAsMember() + ";\n");

                    if (CUtils.getXSDEnumeratorForType( attribs[i].getTypeName()).equals("XSDC_HEXBINARY")
                            || CUtils.getXSDEnumeratorForType( attribs[i].getTypeName()).equals("XSDC_BASE64BINARY"))
                    {
                        c_writer.write(tab2 + "\t\t" + attribs[i].getParamNameAsMember() + "->__ptr = NULL;\n");
                    }
                    
                    c_writer.write(tab2 + "\t\taxiscAxisDelete( (void *) " + attribs[i].getParamNameAsMember() 
                            + ", " + CUtils.getXSDEnumeratorForType( attribs[i].getTypeName()) + ");\n");
                    c_writer.write(tab2 + "\t}\n");
                    
                    c_writer.write(tab2 + "}\n");  // end local scope                
                }
                
                if (attribs[i].isOptional() && !attribs[i].isAttribute() && !handleAll && !handleChoice)
                {
                    c_writer.write("\t\t\t}\n");
                    c_writer.write("\t\telse\n");
                    c_writer.write("\t\t\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                }
            }
            else
            {
                //if complex type
                String soapTagName = attribs[i].getParamNameAsSOAPString();
                
                if (attribs[i].isOptional() && !handleAll && !handleChoice)
                {
                    c_writer.write(tab1 + "peekedElementName = axiscSoapDeSerializerPeekNextElementName(pDZ);\n");
                    c_writer.write(tab1 + "if (strcmp(peekedElementName, \"" + soapTagName + "\") == 0)\n");
                    
                    tab2 += "\t";
                }

                c_writer.write(tab2 + "param->" + attribs[i].getParamNameAsMember() 
                        + " = ("  + attribs[i].getTypeName()
                        + "*)axiscSoapDeSerializerGetCmplxObject(pDZ,(void*)Axis_DeSerialize_" + attribs[i].getTypeName()
                        + ", (void*)Axis_Create_" + attribs[i].getTypeName() 
                        + ", (void*)Axis_Delete_" + attribs[i].getTypeName() 
                        + ", \"" + soapTagName + "\", Axis_URI_" + attribs[i].getTypeName() + ");\n");
                
                if (attribs[i].isOptional()  && !handleAll && !handleChoice)
                {
                    c_writer.write(tab1 + "else\n");
                    c_writer.write(tab1 + "\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                }      
            }

            if (attribs[i].getChoiceElement() || attribs[i].getAllElement())
                c_writer.write(tab1 + "}\n");
            
            c_writer.write("\n");
        }
        
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
        c_writer.write("\tpeekedElementName = axiscSoapDeSerializerPeekNextElementName(pDZ);\n");
        c_writer.write("\tif (0x00 != *peekedElementName)\n");
        c_writer.write("\t\taxiscAxisGenerateUnknownElementException(peekedElementName);\n");

        c_writer.write("\n");
        c_writer.write("\treturn axiscSoapDeSerializerGetStatus(pDZ);\n");
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
              c_writer.write(tab1 + "\taxiscAxisGenerateUnknownElementException(peekedElementName);\n");
            
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
                        CUtils.printComment(c_writer, "Ensure no missing elements in \"all\" groups."); 
                        commentPrinted = true;
                    }

                    c_writer.write("\tif (param->" + attribs[j].getParamNameAsMember() + " == NULL)");
                    c_writer.write(" axiscAxisGenerateElementMissingException(\"" + attribs[j].getParamNameAsMember() + "\");\n");
                }
        }
        
        c_writer.write("\n");
    }

    /**
     * @throws IOException
     */
    private void writeCreateGlobalMethod() throws IOException
    {       
        CUtils.printMethodComment(c_writer, "Function used to create objects of type " 
                + c_classname + ".");
        
        c_writer.write("void* Axis_Create_" + c_classname + "(int nSize)\n{\n");

        c_writer.write("\tif (nSize > 0)\n");
        c_writer.write("\t{\n");
        c_writer.write("\t\tint i;\n");        
        c_writer.write("\t\t" + c_classname + "** pNew = (" + 
                c_classname + "**) axiscAxisNewCArray(nSize);\n");
        c_writer.write("\t\tfor (i=0; i < nSize; ++i)\n");
        c_writer.write("\t\t\tpNew[i] = (" + c_classname + "*)Axis_Create_" + c_classname + "(0);\n");
        c_writer.write("\t\treturn (void *)pNew;\n");
        c_writer.write("\t}\n");
        c_writer.write("\telse\n"); 
        c_writer.write("\t{\n");        
        
        c_writer.write("\t\t" + c_classname + "* pTemp = (" + c_classname + " *)malloc(sizeof(" + c_classname + "));\n");
        c_writer.write("\t\tmemset(pTemp, 0, sizeof(" + c_classname + "));\n");
        c_writer.write("\n");
        
        boolean writeNewline = false;
        
        // The only items in the structure that we pre-allocate is for the container structure
        // for arrays.  All other variables and the actual element array that gets put into 
        // the container structure for arrays are created by the corresponding deserializer.
        for (int i = 0; i < attribs.length; i++)
        {
            if (attribs[i].isArray() && !attribs[i].isAnyTypeOrAnyElement())
            {
                writeNewline = true;
                
                // If simple type array we call the axiscAxisNew() API; otherwise, we 
                // invoke the dynamically generated Axis_Create_xxxx() function. 
                if (attribs[i].isSimpleType() || attribs[i].getType().isSimpleType())
                {
                    String baseTypeName = null;
                    
                    if (!attribs[i].isSimpleType() && attribs[i].getType().isSimpleType())
                        baseTypeName = CUtils.getSimpleType(attribs[i].getType().getBaseType());
                    else
                        baseTypeName = attribs[i].getTypeName();
                    
                    c_writer.write("\t\tpTemp->" + attribs[i].getParamNameAsMember() 
                            + " = (" + baseTypeName + "_Array *)axiscAxisNew(XSDC_ARRAY, 0);\n");
                    
                    c_writer.write("\t\tpTemp->" + attribs[i].getParamNameAsMember() + "->m_Type = " 
                            + CUtils.getXSDEnumeratorForType(baseTypeName) + ";\n");
                }
                else
                {
                        c_writer.write("\t\tpTemp->" + attribs[i].getParamNameAsMember() + " = "
                                + "Axis_Create_" + attribs[i].getTypeName() + "_Array(0);\n");
                }     
            }
        }
        
        if (writeNewline)
            c_writer.write("\n");
        c_writer.write("\t\treturn pTemp;\n");
        c_writer.write("\t}\n");   
        c_writer.write("}\n");
    }

    /**
     * @throws IOException
     */
    private void writeDeleteGlobalMethod() throws IOException
    {
        CUtils.printMethodComment(c_writer, "Function used to delete objects of type " 
                + c_classname + ".");
        
        c_writer.write("void Axis_Delete_" + c_classname
                + "(" + c_classname + "* param, int nSize)\n");
        
        c_writer.write("{\n");
        c_writer.write("\t/* If NULL, just return */\n");
        c_writer.write("\tif (param == NULL)\n");
        c_writer.write("\t\treturn;\n");
        c_writer.write("\n");
        
        c_writer.write("\t/* Reclaim memory resources (recursion is used to reclaim arrays) */\n");
        c_writer.write("\tif (nSize > 0)\n");
        c_writer.write("\t{\n");
        c_writer.write("\t\tint i;\n");
        c_writer.write("\t\t" + c_classname + " **paramArray = (" + c_classname + " **)param;\n");
        c_writer.write("\t\tfor (i = 0 ; i < nSize ; i++ )\n");
        c_writer.write("\t\t\tif (paramArray[i])\n");
        c_writer.write("\t\t\t\tAxis_Delete_" + c_classname + "(paramArray[i],0);\n");
        c_writer.write("\t\taxiscAxisDeleteCArray((void **)param);\n");
        c_writer.write("\t}\n");
        
        c_writer.write("\telse\n");
        
        c_writer.write("\t{\n");
        int anyCounter = 0;
        
        for (int i = 0; i < attribs.length; i++)
        {
            if (attribs[i].isSimpleType() || attribs[i].getType().isSimpleType())
            {
                String passedInBaseType;
                String baseTypeName = null;
                
                if (!attribs[i].isSimpleType() && attribs[i].getType().isSimpleType())
                    baseTypeName = CUtils.getSimpleType(attribs[i].getType().getBaseType());
                else
                    baseTypeName = attribs[i].getTypeName();
                
                if (CUtils.getXSDEnumeratorForType( baseTypeName).equals("XSDC_HEXBINARY")
                        || CUtils.getXSDEnumeratorForType( baseTypeName).equals("XSDC_BASE64BINARY"))
                {
                    // need to delete the pointer
                    String dot = ".";
                    if (isElementNillable(i) || isElementOptional(i) 
                            || attribs[i].getChoiceElement() || attribs[i].getAllElement()) 
                        dot = "->";
                    
                    c_writer.write("\t\tif (param->" + attribs[i].getParamNameAsMember() + dot + "__ptr != NULL)\n");                    
                    c_writer.write("\t\t\taxiscAxisDelete(param->" + attribs[i].getParamNameAsMember() 
                            + dot + "__ptr, XSDC_UNSIGNEDBYTE);\n");
                    c_writer.write("\n");
                }
                else if (CUtils.isPointerType(attribs[i].getTypeName()) || attribs[i].isArray()
                        || isElementNillable(i) || isElementOptional(i) 
                        || attribs[i].getChoiceElement() || attribs[i].getAllElement())
                {                    
                    if (attribs[i].isArray())
                        passedInBaseType = "XSDC_ARRAY";
                    else
                        passedInBaseType = CUtils.getXSDEnumeratorForType(baseTypeName);
                                    
                    c_writer.write("\t\tif (param->" + attribs[i].getParamNameAsMember() + " != NULL)\n");
                    c_writer.write("\t\t\taxiscAxisDelete(param->" + attribs[i].getParamNameAsMember() 
                            + "," + passedInBaseType + ");\n");
                    c_writer.write("\n");
                }
            }
            else if (attribs[i].isAnyTypeOrAnyElement())
            {
                String fieldName = attribs[i].getParamNameAsMember();
                
                if (attribs[i].getType().isAnyElement())
                {
                    anyCounter += 1;
                    fieldName  = "any" + Integer.toString(anyCounter);
                }
                
                c_writer.write("\t\tif (param->" + fieldName + " != NULL)\n");
                c_writer.write("\t\t\taxiscAxisDelete(param->" + fieldName + ", XSDC_ANY);\n");               
            }            
            else
            {
                String deleteFunctionSuffix = "";
                if (attribs[i].isArray())
                    deleteFunctionSuffix = "_Array";
                
                c_writer.write("\t\tif (param->" + attribs[i].getParamNameAsMember() + ")\n");
                c_writer.write("\t\t\tAxis_Delete_" + attribs[i].getTypeName() + deleteFunctionSuffix 
                            + "(param->" + attribs[i].getParamNameAsMember() + ", 0);\n");  
                    
            }
        }
        
        c_writer.write("\t\tfree(param);\n");
        c_writer.write("\t}\n");
        
        c_writer.write("}\n");
    }
    
    /**
     * @throws WrapperFault
     */
    protected void writeRestrictionCheckerFunction() throws WrapperFault
    {
        try
        {
            CUtils.printMethodComment(c_writer, "Function used to check whether object has allowed values. Not implemented yet.");
            
            c_writer.write("int Check_Restrictions_" + c_classname + "(" + c_classname + " value)\n");
            c_writer.write("{\n");
            c_writer.write("\treturn 0;\n");
            //TODO write code to check the restrictions
            c_writer.write("}\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}