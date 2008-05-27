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

import java.io.File;
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
            CUtils.printBlockComment(writer, "Serialize extension.");
            
            String typeName = extensionBaseAttrib.getTypeName(); 

            if (extensionBaseAttrib.isSimpleType())
            {
                writer.write("\taxiscSoapSerializerSerializeAsChardata(pSZ,(void*)");                
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
        CUtils.printMethodComment(writer, "Function to serialize an object of type "  
                + classname + ".");  
        
        writer.write("int Axis_Serialize_" + classname
                + "(" + classname + "* param, AXISCHANDLE pSZ, AxiscBool bArray)\n");
        writer.write( "{\n");
        
        //=============================================================================
        // No attributes or elements to serialize? Then serialize extension and return.
        //=============================================================================        

        if (attribs.length == 0)
        {
            CUtils.printBlockComment(writer, "No attributes or elements to serialize.");
        
            writer.write("\taxiscSoapSerializerSerialize(pSZ,\">\", NULL);\n");

            writeSerializeExtensionCode();
            
            writer.write("\treturn AXISC_SUCCESS;\n");
            writer.write("}\n");
            return;
        }
        
        //=============================================================================
        // NULL param passed in? Assume nillable although type does not know whether
        // it is used as a nillable parameter so this may not be the appropriate place
        // to put this, or we need to find a way to determine if nillable.
        //=============================================================================        
        
        writer.write("\tAxiscBool blnIsNewPrefix = xsdc_boolean_false;\n\n");

        CUtils.printBlockComment(writer, "If null input, serialize as nil element.");
        
        writer.write("\tif ( param == NULL )\n\t{\n");
        writer.write("\t\taxiscSoapSerializerSerializeAsAttribute(pSZ, \"xsi:nil\", 0, (void*)&(xsdc_boolean_true), XSDC_BOOLEAN);\n");
        writer.write("\t\taxiscSoapSerializerSerialize(pSZ, \">\", NULL);\n");
        writer.write("\t\treturn AXISC_SUCCESS;\n");
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
                writer.write("\taxiscSoapSerializerSerializeAsAttribute(pSZ,\""
                        + attribs[i].getParamNameAsSOAPString() + "\", 0, (void*)(param->"
                        + attribs[i].getParamNameAsMember() + "), "
                        + CUtils.getXSDTypeForBasicType(basicType) + ");\n");
            }
            else
            {
                writer.write("\taxiscSoapSerializerSerializeAsAttribute(pSZ,\""
                        + attribs[i].getParamNameAsSOAPString() + "\", 0, (void*)&(param->"
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
            writer.write("\t\tAxiscBool blnIsNewPrefix = xsdc_boolean_false;\n");
            writer.write("\t\tconst AxiscChar* sPrefix = axiscSoapSerializerGetNamespacePrefix(pSZ,Axis_URI_"
                        + classname + ", &blnIsNewPrefix);\n");
            writer.write("\t\taxiscSoapSerializerSerialize(pSZ, \" xmlns:\", sPrefix, \"=\\\"\",");
            writer.write("Axis_URI_" + classname + ", \" " + " \\\"\"");
            writer.write(", NULL);\n\t}\n");
        }               
        
        if(wscontext.getWrapInfo().getWrapperStyle().equals("document"))
            writer.write("\taxiscSoapSerializerSerialize(pSZ, \">\", 0);\n");
        
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
            boolean ifCheckPrinted = false;
            if (attribs[i].getChoiceElement())
            {
                if (!firstIfWritten)
                {
                    writer.write("\tif");
                    firstIfWritten = true;
                } 
                else
                    writer.write("\telse if");

                ifCheckPrinted = true;
                writer.write("(param->" + attribs[i].getParamNameAsMember() + ")\n\t{\n\t");
            }
 
            //if the attribute is a 'all' following should do
            if (attribs[i].getAllElement())
                if (attribs[i].getMinOccurs() == 0)
                {
                    ifCheckPrinted = true;
                    writer.write("\tif(param->" + attribs[i].getParamNameAsMember() + ")\n\t{\n\t");
                }
             
            if (attribs[i].isAnyType())
            {
                anyCounter += 1;
                
                if (attribs[i].isOptional())
                    writer.write("\tif (param->any" + Integer.toString(anyCounter) + " != NULL)\n");
                                          
                writer.write("\t\taxiscSoapSerializerSerializeAnyObject(pSZ, param->any" + Integer.toString(anyCounter) +");\n");
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
                    
                    writer.write("\taxiscSoapSerializerSerializeBasicArray(pSZ, (const Axisc_Array *)param->" + attribs[i].getParamNameAsMember()
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
                    
                    writer.write("\taxiscSoapSerializerSerializeCmplxArray(pSZ, (const Axisc_Array *)param->"
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
                    baseTypeName = CUtils.getclass4qname (attribs[i].getType().getBaseType ());
                else
                    baseTypeName = typeName;
                
                if (!ifCheckPrinted && attribs[i].isOptional())
                    writer.write("\tif (param->" + attribs[i].getParamNameAsMember() + " != NULL)\n\t");
                
                // If the simple type is a choice it is handled
                // as a pointer variable.  This is the same in 'all' element and nillable elements.
                String ampersand = "&";
                if (CUtils.isPointerType(baseTypeName)
                            || attribs[i].getChoiceElement()
                            || attribs[i].getAllElement()
                            || isElementNillable(i) || isElementOptional(i))
                    ampersand = "";
                
                writer.write("\taxiscSoapSerializerSerializeAsElement(pSZ, \""
                        + attribs[i].getElementNameAsSOAPString() + "\", " + namespace
                        + ", (void*)" + ampersand + "(param->" + attribs[i].getParamNameAsMember() + "), "
                        + CUtils.getXSDTypeForBasicType(baseTypeName) + ");\n");
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
                    writer.write("\tif (param->" + attribs[i].getParamNameAsMember() + " != NULL)\n\t{\n\t");
                }
                
                if (attribs[i].getNsQualified())
                {
                    writer.write("\taxiscSoapSerializerSerialize(pSZ, \"<\", axiscSoapSerializerGetNamespacePrefix(pSZ, \""
                                    + type.getName().getNamespaceURI()
                                    + "\", NULL), \":\", \"" + elm + "\", 0);\n");
                    writer.write(tab + "\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamNameAsMember() + ", pSZ, 0);\n");
                    writer.write(tab + "\taxiscSoapSerializerSerialize(pSZ, \"</\", axiscSoapSerializerGetNamespacePrefix(pSZ, \""
                                    + type.getName().getNamespaceURI()
                                    + "\", NULL), \":\", \"" + elm + "\", \">\", 0);\n");
                }
                else
                {
                    writer.write("\taxiscSoapSerializerSerialize(pSZ, \"<" + elm + "\", 0);\n");
                    writer.write(tab + "\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamNameAsMember() + ", pSZ, 0);\n");
                    writer.write(tab + "\taxiscSoapSerializerSerialize(pSZ, \"</" + elm + "\", \">\", 0);\n");
                }
                
                if (!ifCheckPrinted && attribs[i].isOptional())
                    writer.write("\t}\n");
            }

            //end if choice element

            if (ifCheckPrinted)
                writer.write("\t}\n");
        }
        
        //=============================================================================
        // End of attribute and element serialization
        //=============================================================================                
                
        if (wscontext.getWrapInfo().getWrapperStyle().equals("rpc"))
        {
            writer.write("\n\taxiscSoapSerializerSerialize(pSZ, \"</\", Axis_TypeName_" + classname
                    + ", \">\", NULL);\n");
        }

        CUtils.printBlockComment(writer, "Remove namespace, if new.");        
        
        writer.write("\tif (!bArray && blnIsNewPrefix)\n");
        writer.write("\t\taxiscSoapSerializerRemoveNamespacePrefix(pSZ, Axis_URI_" + classname + ");\n");
        writer.write("\n");
        
        writer.write("\treturn AXISC_SUCCESS;\n");
        writer.write("}\n");
    }

    /**
     * @throws IOException
     */
    private void writeDOCArrayPortionOfSerializeGlobalMethod() throws IOException
    {
        CUtils.printBlockComment(writer, "Serialize top-most element, possibly defining new namespace.");        
        
        // For doc/literal objects
        writer.write("\tif (!bArray)\n\t{\n");
        writer.write("\t\tconst AxiscChar* sPrefix = axiscSoapSerializerGetNamespacePrefix(pSZ,Axis_URI_" + classname + ", &blnIsNewPrefix);\n");
        writer.write("\t\tif (blnIsNewPrefix)\n");
        writer.write("\t\t\taxiscSoapSerializerSerialize(pSZ,\" xmlns:\", sPrefix, \"=\\\"\", " 
                        + "Axis_URI_" + classname + ", \"\\\"\", NULL);\n");
        writer.write("\t}\n");
    }

    /**
     * @throws IOException
     */
    private void writeRPCArrayPortionOfSerializeGlobalMethod() throws IOException
    {
        // For rpc/encoded objects
        writer.write( "\tif( bArray)\n");
        writer.write( "\t\taxiscSoapSerializerSerialize(pSZ, \"<\", Axis_TypeName_" + classname + ", \">\", NULL);\n");
        writer.write( "\telse\n");
        writer.write( "\t{\n");
        writer.write( "\t\tconst AxiscChar * sPrefix = axiscSoapSerializerGetNamespacePrefix(pSZ, Axis_URI_" 
                + classname + ", &blnIsNewPrefix);\n\n");
        writer.write( "\t\t// If there are objects that require a local namespace, then define it here.\n");
        writer.write( "\t\t// NB: This namespace will go out of scope when the closing tag is reached.\n");
        writer.write( "\t\tif( !blnIsNewPrefix)\n");
        writer.write( "\t\t\taxiscSoapSerializerSerialize(pSZ, \"<\", Axis_TypeName_" + classname + ", " 
                    + "\" xsi:type=\\\"\", sPrefix, \":\", "
                    + "Axis_TypeName_" + classname + ", \"\\\">\", NULL);\n");
        writer.write( "\t\telse\n");
        writer.write( "\t\t\taxiscSoapSerializerSerialize(pSZ, \"<\", Axis_TypeName_" + classname + ", " 
                    + "\" xsi:type=\\\"\", sPrefix, \":\", " 
                    + "Axis_TypeName_" + classname + ", \"\\\" xmlns:\", " 
                    + "sPrefix, \"=\\\"\", Axis_URI_" + classname + ", \"\\\">\", NULL);\n");
        writer.write("\t}\n");
    }

    private void writeDeSerializeExtensionCode() throws IOException, WrapperFault
    {  
        if (extensionBaseAttrib != null
                && extensionBaseAttrib.getTypeName() != null)
        {
            CUtils.printBlockComment(writer, "Deserialize extension.");
            
            if (extensionBaseAttrib.isSimpleType())
            {
                writer.write("\t{\n"); // ==== begin scope
                writer.write("\t\tvoid* pCharDataAs;\n\n");
                String typeName = extensionBaseAttrib.getTypeName();
                String xsdType = CUtils.getXSDTypeForBasicType(typeName);
                writer.write("\t\taxiscSoapDeSerializerGetChardataAs(pDZ, &pCharDataAs, " + xsdType + ");\n");
                writer.write("\t\tparam->" + extensionBaseAttrib.getParamNameAsMember() + " = ");
                
                if (CUtils.isPointerType(typeName))
                    writer.write("(" + typeName + ") pCharDataAs;\n");
                else
                {
                    writer.write(" *(" + typeName + "*) pCharDataAs;\n");
                    writer.write("\t\taxiscAxisDelete(pCharDataAs, " + xsdType + ");\n");
                }      
                writer.write("\t}\n"); // ==== end scope
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
        CUtils.printMethodComment(writer, "Function to deserialize an object of type "  
                + classname + ".");  
        
        writer.write("int Axis_DeSerialize_" + classname + "(" + classname 
                + "* param, AXISCHANDLE pDZ)\n{\n");

        //=============================================================================
        // No attributes or elements to deserialize? Then deserialize extension and return.
        //=============================================================================        
       
        if (attribs.length == 0)
        {
            writeDeSerializeExtensionCode();

            writer.write("\treturn AXISC_SUCCESS;\n");
            writer.write("}\n");
            return;
        }  
        
        // Determine whether to print variable used for peaking ahead
        for (int i = 0; i < attribs.length; i++)
        {
            if (!attribs[i].isAttribute() && attribs[i].isOptional() && !attribs[i].isArray() && !attribs[i].isAnyType())
            {
                writer.write("\tconst char* peekedElementName;\n");
                break;
            }
        }

        //=============================================================================
        // Deserialize attributes.
        // Actually, attribute deserialization takes place in same loop as elements
        // in order to avoid duplication. But here, we put out a comment block.
        //=============================================================================        
        
        if (attributeParamCount > 0)
            CUtils.printBlockComment(writer, "Deserialize attributes.");
        
        //=============================================================================
        // Deserialize attributes and elements.
        //=============================================================================        
        
        String arrayType = null;
        boolean peekCalled = false;
        boolean firstIfWritten = false;
        boolean foundAll = false;
        int anyCounter = 0; //counter for any types.
        int arrayCount = 0;
     
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
                    writer.write("\tconst char* choiceName=axiscSoapDeSerializerPeekNextElementName(pDZ);\n");
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
                        writer.write("\tAxiscBool peekCalled = xsdc_boolean_false;\n");
                        foundAll = true;
                    }

                    writer.write("\n\tif(!peekCalled)\n\t{\n\t");
                    writer.write("\tallName=axiscSoapDeSerializerPeekNextElementName(pDZ);\n");
                    writer.write("\t\tpeekCalled = xsdc_boolean_true;\n");
                    writer.write("\t}\n");
                    writer.write("\tif(strcmp(allName,\""
                            + attribs[i].getParamNameAsMember() + "\")==0)\n\t{\n\t");
                    writer.write("\tpeekCalled = xsdc_boolean_false;\n\t");
                }
            
            if (attribs[i].isAnyType())
            {
                anyCounter +=1;
                writer.write(tab1 + "param->any" + anyCounter + " = axiscSoapDeSerializerGetAnyObject(pDZ);\n");
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

                    writer.write(tab1 + "if (param->" + attribs[i].getParamNameAsMember() + " != NULL)\n");
                    writer.write(tab1 + "{\n");
                    writer.write(tab1 + "\taxiscAxisDelete(param->" + attribs[i].getParamNameAsMember() + ", XSDC_ARRAY);\n");
                    writer.write(tab1 + "\tparam->" + attribs[i].getParamNameAsMember() + "= NULL;\n");
                    writer.write(tab1 + "}\n");
                    writer.write("\n");
                 
                    writer.write(tab1 + "param->" + attribs[i].getParamNameAsMember() 
                            + " = (" + baseTypeName + "_Array *)" 
                            + "axiscSoapDeSerializerGetBasicArray(pDZ, " 
                            + CUtils.getXSDTypeForBasicType(baseTypeName) + ", \"" 
                            + attribs[i].getParamNameAsSOAPString() + "\",0);\n");

                    writer.write("\n");
                }
                else
                {
                    arrayType = attribs[i].getTypeName();
                    writer.write(tab1 + "axiscSoapDeSerializerGetCmplxArray(pDZ, (Axisc_Array *)param->" + attribs[i].getParamNameAsMember() 
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
                if (attribs[i].isOptional() && !attribs[i].isAttribute())
                {
                    writer.write(tab1 + "peekedElementName = axiscSoapDeSerializerPeekNextElementName(pDZ);\n");
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
                        attribs[i].getChoiceElement() ||
                        attribs[i].getAllElement() ||
                        attribs[i].isOptional() ||
                        isPointerType)                
                {
                    writer.write(tab2 + "param->"
                            + attribs[i].getParamNameAsMember() + " = "
                            + "axiscSoapDeSerializer"
                            + CUtils.getParameterGetValueMethodName(
                                    attribs[i].getTypeName(), attribs[i].isAttribute()) + "(pDZ, \""
                            + soapTagName + "\",0);\n");
                }                
                else
                {
                    String elementNameToSearchFor = attribs[i].isAttribute()? attribs[i].getParamNameAsSOAPString():attribs[i].getElementNameAsSOAPString();
                    
                    writer.write(tab2 + "{\n"); // start local scope
                    
                    writer.write(tab2 + "\t" + attribs[i].getTypeName() + " * "
                        + attribs[i].getParamNameAsMember() + " = " 
                        + "axiscSoapDeSerializer"
                        + CUtils.getParameterGetValueMethodName(attribs[i].getTypeName(), attribs[i].isAttribute()) 
                        + "(pDZ, \"" + elementNameToSearchFor + "\",0);\n");
                    
                    writer.write(tab2 + "\tif (" + attribs[i].getParamNameAsMember() + " != NULL)\n");
                    writer.write(tab2 + "\t{\n");
                    writer.write(tab2 + "\t\tparam->" + attribs[i].getParamNameAsMember() + " = *"
                            + attribs[i].getParamNameAsMember() + ";\n");

                    if (CUtils.getXSDTypeForBasicType( attribs[i].getTypeName()).equals("XSDC_HEXBINARY")
                            || CUtils.getXSDTypeForBasicType( attribs[i].getTypeName()).equals("XSDC_BASE64BINARY"))
                    {
                        writer.write(tab2 + "\t\t" + attribs[i].getParamNameAsMember() + "->__ptr = NULL;\n");
                    }
                    
                    writer.write(tab2 + "\t\taxiscAxisDelete( (void *) " + attribs[i].getParamNameAsMember() 
                            + ", " + CUtils.getXSDTypeForBasicType( attribs[i].getTypeName()) + ");\n");
                    writer.write(tab2 + "\t}\n");
                    
                    writer.write(tab2 + "}\n");  // end local scope                
                }
                
                if (attribs[i].isOptional() && !attribs[i].isAttribute())
                {
                    writer.write("\t\t\t}\n");
                    writer.write("\t\telse\n");
                    writer.write("\t\t\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                }
            }
            else
            {
                //if complex type
                String soapTagName = attribs[i].getParamNameAsSOAPString();
                
                if (attribs[i].isOptional())
                {
                    writer.write(tab1 + "peekedElementName = axiscSoapDeSerializerPeekNextElementName(pDZ);\n");
                    writer.write(tab1 + "if (strcmp(peekedElementName, \"" + soapTagName + "\") == 0)\n");
                    tab2 += "\t";
                }

                writer.write(tab2 + "param->" + attribs[i].getParamNameAsMember() 
                        + " = ("  + attribs[i].getTypeName()
                        + "*)axiscSoapDeSerializerGetCmplxObject(pDZ,(void*)Axis_DeSerialize_" + attribs[i].getTypeName()
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
        
        writer.write("\treturn axiscSoapDeSerializerGetStatus(pDZ);\n");
        writer.write("}\n");
    }
    

    /**
     * @throws IOException
     */
    private void writeCreateGlobalMethod() throws IOException
    {       
        CUtils.printMethodComment(writer, "Function used to create objects of type " 
                + classname + ".");
        
        writer.write("void* Axis_Create_" + classname + "(int nSize)\n{\n");

        writer.write("\tif (nSize > 0)\n");
        writer.write("\t{\n");
        writer.write("\t\tint i;\n");        
        writer.write("\t\t" + classname + "** pNew = (" + 
                classname + "**) axiscAxisNewCArray(nSize);\n");
        writer.write("\t\tfor (i=0; i < nSize; ++i)\n");
        writer.write("\t\t\tpNew[i] = (" + classname + "*)Axis_Create_" + classname + "(0);\n");
        writer.write("\t\treturn (void *)pNew;\n");
        writer.write("\t}\n");
        writer.write("\telse\n"); 
        writer.write("\t{\n");        
        
        writer.write("\t\t" + classname + "* pTemp = (" + classname + " *)malloc(sizeof(" + classname + "));\n");
        writer.write("\t\tmemset(pTemp, 0, sizeof(" + classname + "));\n");
        writer.write("\n");
        
        boolean writeNewline = false;
        
        // The only items in the structure that we pre-allocate is for the container structure
        // for arrays.  All other variables and the actual element array that gets put into 
        // the container structure for arrays are created by the corresponding deserializer.
        for (int i = 0; i < attribs.length; i++)
        {
            if (attribs[i].isArray())
            {
                writeNewline = true;
                
                // If simple type array we call the axiscAxisNew() API; otherwise, we 
                // invoke the dynamically generated Axis_Create_xxxx() function. 
                if (attribs[i].isSimpleType() || attribs[i].getType().isSimpleType())
                {
                    String baseTypeName = null;
                    
                    if (!attribs[i].isSimpleType() && attribs[i].getType().isSimpleType())
                        baseTypeName = CUtils.getclass4qname(attribs[i].getType().getBaseType());
                    else
                        baseTypeName = attribs[i].getTypeName();
                    
                    writer.write("\t\tpTemp->" + attribs[i].getParamNameAsMember() 
                            + " = (" + baseTypeName + "_Array *)axiscAxisNew(XSDC_ARRAY, 0);\n");
                    
                    writer.write("\t\tpTemp->" + attribs[i].getParamNameAsMember() + "->m_Type = " 
                            + CUtils.getXSDTypeForBasicType(baseTypeName) + ";\n");
                }
                else
                {
                        writer.write("\t\tpTemp->" + attribs[i].getParamNameAsMember() + " = "
                                + "Axis_Create_" + attribs[i].getTypeName() + "_Array(0);\n");
                }     
            }
        }
        
        if (writeNewline)
            writer.write("\n");
        writer.write("\t\treturn pTemp;\n");
        writer.write("\t}\n");   
        writer.write("}\n");
    }

    /**
     * @throws IOException
     */
    private void writeDeleteGlobalMethod() throws IOException
    {
        CUtils.printMethodComment(writer, "Function used to delete objects of type " 
                + classname + ".");
        
        writer.write("void Axis_Delete_" + classname
                + "(" + classname + "* param, int nSize)\n");
        
        writer.write("{\n");
        writer.write("\t/* If NULL, just return */\n");
        writer.write("\tif (param == NULL)\n");
        writer.write("\t\treturn;\n");
        writer.write("\n");
        
        writer.write("\t/* Reclaim memory resources (recursion is used to reclaim arrays) */\n");
        writer.write("\tif (nSize > 0)\n");
        writer.write("\t{\n");
        writer.write("\t\tint i;\n");
        writer.write("\t\t" + classname + " **paramArray = (" + classname + " **)param;\n");
        writer.write("\t\tfor (i = 0 ; i < nSize ; i++ )\n");
        writer.write("\t\t\tif (paramArray[i])\n");
        writer.write("\t\t\t\tAxis_Delete_" + classname + "(paramArray[i],0);\n");
        writer.write("\t\taxiscAxisDeleteCArray((void **)param);\n");
        writer.write("\t}\n");
        
        writer.write("\telse\n");
        
        writer.write("\t{\n");
        int anyCounter = 0;
        
        for (int i = 0; i < attribs.length; i++)
        {
            if (attribs[i].isSimpleType() || attribs[i].getType().isSimpleType())
            {
                String passedInBaseType;
                String baseTypeName = null;
                
                if (!attribs[i].isSimpleType() && attribs[i].getType().isSimpleType())
                    baseTypeName = CUtils.getclass4qname(attribs[i].getType().getBaseType());
                else
                    baseTypeName = attribs[i].getTypeName();
                
                if (CUtils.getXSDTypeForBasicType( baseTypeName).equals("XSDC_HEXBINARY")
                        || CUtils.getXSDTypeForBasicType( baseTypeName).equals("XSDC_BASE64BINARY"))
                {
                    // need to delete the pointer
                    String dot = ".";
                    if (isElementNillable(i) || isElementOptional(i) 
                            || attribs[i].getChoiceElement() || attribs[i].getAllElement()) 
                        dot = "->";
                    
                    writer.write("\t\tif (param->" + attribs[i].getParamNameAsMember() + dot + "__ptr != NULL)\n");                    
                    writer.write("\t\t\taxiscAxisDelete(param->" + attribs[i].getParamNameAsMember() 
                            + dot + "__ptr, XSDC_UNSIGNEDBYTE);\n");
                    writer.write("\n");
                }
                else if (CUtils.isPointerType(attribs[i].getTypeName()) || attribs[i].isArray()
                        || isElementNillable(i) || isElementOptional(i) 
                        || attribs[i].getChoiceElement() || attribs[i].getAllElement())
                {                    
                    if (attribs[i].isArray())
                        passedInBaseType = "XSDC_ARRAY";
                    else
                        passedInBaseType = CUtils.getXSDTypeForBasicType(baseTypeName);
                                    
                    writer.write("\t\tif (param->" + attribs[i].getParamNameAsMember() + " != NULL)\n");
                    writer.write("\t\t\taxiscAxisDelete(param->" + attribs[i].getParamNameAsMember() 
                            + "," + passedInBaseType + ");\n");
                    writer.write("\n");
                }
            }
            else if (attribs[i].isAnyType())
            {
                anyCounter += 1;
                String name = attribs[i].getParamNameAsMember() + anyCounter;
                
                writer.write("\t\tif (param->" + name + " != NULL)\n");
                writer.write("\t\t\taxiscAxisDelete(param->" + name + ", XSDC_ANY);\n");               
            }            
            else
            {
                String deleteFunctionSuffix = "";
                if (attribs[i].isArray())
                    deleteFunctionSuffix = "_Array";
                
                writer.write("\t\tif (param->" + attribs[i].getParamNameAsMember() + ")\n");
                writer.write("\t\t\tAxis_Delete_" + attribs[i].getTypeName() + deleteFunctionSuffix 
                            + "(param->" + attribs[i].getParamNameAsMember() + ", 0);\n");  
                    
            }
        }
        
        writer.write("\t\tfree(param);\n");
        writer.write("\t}\n");
        
        writer.write("}\n");
    }
    
    /**
     * @throws WrapperFault
     */
    protected void writeRestrictionCheckerFunction() throws WrapperFault
    {
        try
        {
            CUtils.printMethodComment(writer, "Function used to check whether object has allowed values. Not implemented yet.");
            
            writer.write("int Check_Restrictions_" + classname + "(" + classname + " value)\n");
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
}