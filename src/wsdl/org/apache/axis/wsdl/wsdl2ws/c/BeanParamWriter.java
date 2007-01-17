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
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

/**
 * Genarate a webservice for the complex types likes structs.
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
            // Ensure writeSerializeGlobalMethod() is first since it ensure attribute name does not conflict with
            // existing classes
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
     * @throws IOException
     * @throws WrapperFault
     */
    private void writeSerializeGlobalMethod() throws IOException, WrapperFault
    {
        writer.write("\n");
        writer.write("/**\n");
        writer.write(" * This static method serializes a " + classname + " type of object\n");
        writer.write(" */\n");
        writer.write("int Axis_Serialize_" + classname
                + "(" + classname + "* param, AXISCHANDLE pSZ, AxiscBool bArray)\n{\n");
        
        if (attribs.length == 0)
        {
            writer.write("\taxiscSoapSerializerSerialize(pSZ,\">\", NULL);\n");

            if (extensionBaseAttrib != null)
            {
                String typeName = extensionBaseAttrib.getTypeName();
                
                if (extensionBaseAttrib.isSimpleType())
                {                
                    writer.write("\taxiscSoapSerializerSerializeAsChardata(pSZ,(void*)");
                    
                    if (!CUtils.isPointerType(typeName))
                        writer.write("&");
                    
                    writer.write("(param->" + extensionBaseAttrib.getParamNameAsMember()
                            + "), " + CUtils.getXSDTypeForBasicType(typeName) + ");\n");
                }
                else
                {
                    // TODO
                }
            } 
            else
            {
                System.out.println("Possible error in class " + classname
                        + ": class with no attributes....................");
            }
            
            writer.write("\treturn AXISC_SUCCESS;\n");
            writer.write("}\n\n");
            return;
        }

        String arrayType;
        
        
        /*
         * A type does not know whether it is used as a nillable parameter So
         * this may not be the appropriate place to do this
         */
        writer.write("\tAxiscBool blnIsNewPrefix = xsdc_boolean_false;\n\n");
        
        writer.write("\tif ( param == NULL )\n\t{\n");
        writer.write("\t\taxiscSoapSerializerSerializeAsAttribute(pSZ, \"xsi:nil\", 0, (void*)&(xsdc_boolean_true), XSDC_BOOLEAN);\n");
        writer.write("\t\taxiscSoapSerializerSerialize(pSZ, \">\", NULL);\n");
        writer.write("\t\treturn AXISC_SUCCESS;\n");
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
            // Ensure field name is valid and does not cause conflict with class names
            String sanitizedAttrName = CUtils.sanitiseAttributeName(attribs[i].getParamName());
            if (CUtils.classExists(wscontext, sanitizedAttrName))
                sanitizedAttrName += "_Ref";
            attribs[i].setParamName(sanitizedAttrName);
            
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
                
                if (attribs[i].isOptional())
                    writer.write("\tif (0 != param->" + attribs[i].getParamNameAsMember() + ")\n");

                if (CUtils.isPointerType(basicType) || attribs[i].isOptional())
                {
                    writer.write("\t\taxiscSoapSerializerSerializeAsAttribute(pSZ,\""
                            + soapTagName + "\", 0, (void*)(param->"
                            + attribs[i].getParamNameAsMember() + "), "
                            + CUtils.getXSDTypeForBasicType(basicType) + ");\n");
                }
                else
                {
                    writer.write("\taxiscSoapSerializerSerializeAsAttribute(pSZ,\""
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
            writer.write("\t\tAxiscBool blnIsNewPrefix = xsdc_boolean_false;\n");
            writer.write("\t\tconst AxiscChar* sPrefix = axiscSoapSerializerGetNamespacePrefix(pSZ,Axis_URI_"
                        + classname + ", &blnIsNewPrefix);\n");
            writer.write("\t\taxiscSoapSerializerSerialize(pSZ, \" xmlns:\", sPrefix, \"=\\\"\",");
            writer.write("Axis_URI_" + classname + ", \" " + " \\\"\"");
            writer.write(", NULL);\n\t}\n");
        }               
        
        if(wscontext.getWrapInfo().getWrapperStyle().equals("document"))
            writer.write("\taxiscSoapSerializerSerialize(pSZ, \">\", 0);\n");
        
        if (extensionBaseAttrib != null)
        {
            String typeName = extensionBaseAttrib.getTypeName(); 
            
            if (extensionBaseAttrib.isSimpleType())
            {
                writer.write("\taxiscSoapSerializerSerializeAsChardata(pSZ, (void*)");
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

        writer.write("\n\t/* then serialize elements if any*/\n");

        boolean firstIfWritten = false;
        int anyCounter = 0; //counter for any types.
        
        for (int i = attributeParamCount; i < attribs.length; i++)
        {
            // Ensure field name is valid and does not cause conflict with class names
            String sanitizedAttrName = CUtils.sanitiseAttributeName(attribs[i].getParamName());
            if (CUtils.classExists(wscontext, sanitizedAttrName))
                sanitizedAttrName += "_Ref";
            attribs[i].setParamName(sanitizedAttrName);

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
                writer.write("\taxiscSoapSerializerSerializeAnyObject(pSZ, param->any" + Integer.toString(anyCounter) +");\n");
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
                    
                    writer.write("\taxiscSoapSerializerSerializeBasicArray(pSZ, (const Axisc_Array *)param->" + attribs[i].getParamName()
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
                    
                    writer.write("\taxiscSoapSerializerSerializeCmplxArray(pSZ, (const Axisc_Array *)param->"
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
                    writer.write("\tif (param->" + attribs[i].getParamNameWithoutSymbols() + " != NULL)\n\t\t{\n\t");
                
                if (CUtils.isPointerType(baseTypeName))
                {
                    writer.write("\taxiscSoapSerializerSerializeAsElement(pSZ, \""
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
                        writer.write("\t\taxiscSoapSerializerSerializeAsElement(pSZ, \""
                                + attribs[i].getSOAPElementNameAsString() + "\", " + namespace
                                + ", (void*)(*(param->" + attribs[i].getParamNameWithoutSymbols()
                                + ")), " + CUtils.getXSDTypeForBasicType(baseTypeName) + ");\n");
                    }
                    else
                    {
                        writer.write("\t\taxiscSoapSerializerSerializeAsElement(pSZ, \""
                                + attribs[i].getSOAPElementNameAsString() + "\", " + namespace
                                + ", (void*)(param->" + attribs[i].getParamNameWithoutSymbols()
                                + "), " + CUtils.getXSDTypeForBasicType(baseTypeName) + ");\n");
                    }    
                }                           
                else
                {
                    writer.write("\taxiscSoapSerializerSerializeAsElement(pSZ, \""
                            + attribs[i].getSOAPElementNameAsString() + "\", " + namespace
                            + ", (void*)&(param->" + attribs[i].getParamNameWithoutSymbols()
                            + "), " + CUtils.getXSDTypeForBasicType(baseTypeName) + ");\n");
                }
                
                if (attribs[i].isOptional())
                    writer.write("\t\t}\n");
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
                    writer.write("\taxiscSoapSerializerSerialize(pSZ, \"<\", axiscSoapSerializerGetNamespacePrefix(pSZ, \""
                                    + type.getName().getNamespaceURI()
                                    + "\", NULL), \":\", \"" + elm + "\", 0);\n");
                    writer.write("\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamName() + ", pSZ, 0);\n");
                    writer.write("\taxiscSoapSerializerSerialize(pSZ, \"</\", axiscSoapSerializerGetNamespacePrefix(pSZ, \""
                                    + type.getName().getNamespaceURI()
                                    + "\", NULL), \":\", \"" + elm + "\", \">\", 0);\n");
                }
                else
                {
                    writer.write("\taxiscSoapSerializerSerialize(pSZ, \"<" + elm + "\", 0);\n");
                    writer.write("\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamName() + ", pSZ, 0);\n");
                    writer.write("\taxiscSoapSerializerSerialize(pSZ, \"</" + elm + "\", \">\", 0);\n");
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
            writer.write("\n\taxiscSoapSerializerSerialize(pSZ, \"</\", Axis_TypeName_" + classname
                    + ", \">\", NULL);\n");
        }
        
        writer.write("\n\tif (!bArray && blnIsNewPrefix)\n");
        writer.write("\t\taxiscSoapSerializerRemoveNamespacePrefix(pSZ, Axis_URI_" + classname + ");\n\n");
        
        writer.write("\treturn AXISC_SUCCESS;\n");
        writer.write("}\n");
    }

    /**
     * @throws IOException
     */
    private void writeDOCArrayPortionOfSerializeGlobalMethod() throws IOException
    {
        // For doc/literal objects
        writer.write("\tif (!bArray)\n\t{\n");
        writer.write("\t\tconst AxiscChar* sPrefix = axiscSoapSerializerGetNamespacePrefix(pSZ,Axis_URI_" + classname + ", &blnIsNewPrefix);\n");
        writer.write("\t\tif (blnIsNewPrefix)\n\t\t{\n");
        writer.write("\t\t\taxiscSoapSerializerSerialize(pSZ,\" xmlns:\", sPrefix, \"=\\\"\",\n");
        writer.write("\t\t\t\tAxis_URI_" + classname + ", \"\\\"\", NULL );\n");
        writer.write("\t\t}\n");
        writer.write("\t}\n\n");
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
        writer.write( "\t\tconst AxiscChar * sPrefix = axiscSoapSerializerGetNamespacePrefix(pSZ, Axis_URI_" + classname + ",\n" +
                      "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t&blnIsNewPrefix);\n\n");
        writer.write( "// If there are objects that require a local namespace, then define it here.\n");
        writer.write( "// NB: This namespace will go out of scope when the closing tag is reached.\n");
        writer.write( "\t\tif( !blnIsNewPrefix)\n");
        writer.write( "\t\t{\n");
        writer.write( "\t\t\taxiscSoapSerializerSerialize(pSZ, \"<\",\n\t\t\t\t\t\t\tAxis_TypeName_" + classname + ",\n" +
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
        writer.write( "\t\t\taxiscSoapSerializerSerialize(pSZ, \"<\",\n" +
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
        writer.write("\t\t}\n");
        writer.write("\t}\n\n");
    }

    private void writeDeSerializeGlobalMethod() throws IOException, WrapperFault
    {
        writer.write("\n");
        writer.write("/**\n");
        writer.write(" * This static method deserializes a " + classname + " type of object\n");
        writer.write(" */\n");
        writer.write("int Axis_DeSerialize_" + classname
                + "(" + classname + "* param, AXISCHANDLE pDZ)\n{\n");
        
        if (attribs.length == 0)
        {
            if (extensionBaseAttrib != null)
            {
                if (extensionBaseAttrib.isSimpleType())
                {
                    writer.write("\tvoid* pCharDataAs;\n\n");
                    String typeName = extensionBaseAttrib.getTypeName();
                    String xsdType = CUtils.getXSDTypeForBasicType(typeName);
                    writer.write("\taxiscSoapDeSerializerGetChardataAs(pDZ, &pCharDataAs, " + xsdType + ");\n");
                    writer.write("\tparam->" + extensionBaseAttrib.getParamNameAsMember() + " = ");
                    
                    if (CUtils.isPointerType(typeName))
                        writer.write("(" + typeName + ") pCharDataAs;\n");
                    else
                    {
                        writer.write(" *(" + typeName + "*) pCharDataAs;\n");
                        writer.write("\taxiscAxisDelete(pCharDataAs, " + xsdType + ");\n");
                    }     
                }
                else
                {
                    // TODO
                }
            }
            else
            {
                System.out.println("Possible error in class " + classname
                        + ": class with no attributes....................");
            }

            writer.write("\treturn AXISC_SUCCESS;\n");
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
                writer.write("\tparam->any" + anyCounter + " = axiscSoapDeSerializerGetAnyObject(pDZ);\n");
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

                    writer.write("\t/* If there is an existing array, delete it */\n");
                    writer.write("\tif (param->" + attribs[i].getParamNameAsMember() + " != NULL)\n");
                    writer.write("\t{\n");
                    writer.write("\t\taxiscAxisDelete(param->" + attribs[i].getParamNameAsMember() + ", XSDC_ARRAY);\n");
                    writer.write("\t\tparam->" + attribs[i].getParamNameAsMember() + "= NULL;\n");
                    writer.write("\t}\n");
                    writer.write("\n");
                    
                    writer.write("\t/* Deserialize array */\n");
                    writer.write("\tparam->" + attribs[i].getParamNameAsMember() 
                            + " = (" + baseTypeName + "_Array *)" 
                            + "axiscSoapDeSerializerGetBasicArray(pDZ, " 
                            + CUtils.getXSDTypeForBasicType(baseTypeName) + ", \"" 
                            + attribs[i].getParamNameAsSOAPElement() + "\",0);\n");

                    writer.write("\n");
                }
                else
                {
                    arrayType = attribs[i].getTypeName();
                    writer.write("\taxiscSoapDeSerializerGetCmplxArray(pDZ,\n" 
                            + "\t\t(Axisc_Array *)param->" + attribs[i].getParamName() + ",\n" 
                            + "\t\t(void*)Axis_DeSerialize_"  + arrayType + ",\n"
                            + "\t\t(void*)Axis_Create_"       + arrayType + ",\n"
                            + "\t\t(void*)Axis_Delete_"       + arrayType + ",\n"
                            + "\t\t\""  + attribs[i].getElementNameAsString() + "\",\n"  
                            + "\t\tAxis_URI_" + arrayType + ");\n");
                    
                    // TODO C-BINDING MEMORY MANAGEMENT?
                }
            }
            else if ((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()))
            {                
                //remove _Ref sufix and _ prefix in SOAP tag name
                String soapTagName = (attribs[i].isAttribute() ? attribs[i].getParamName() : attribs[i].getElementNameAsString());
                if (soapTagName.lastIndexOf("_Ref") > -1)
                    soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref"));

                if (soapTagName.charAt(0) == '_')
                    soapTagName = soapTagName.substring(1, soapTagName.length());
                
                // We only peek for elements, not element attributes!
                if (attribs[i].isOptional() && !attribs[i].isAttribute())
                {
                    writer.write("\n\t{\n"); // start new variable scope                    
                    writer.write("\tconst char* elementName" + i + " = axiscSoapDeSerializerPeekNextElementName(pDZ);\n");
                    writer.write("\tif(strcmp(elementName" + i + ", \"" + soapTagName + "\") == 0)\n");
                    writer.write("\t{\n");
                }
                
                Type type = attribs[i].getType();
                boolean isPointerType = false;
                if (type.isSimpleType())
                    isPointerType = CUtils.isPointerType(CUtils.getclass4qname(type.getBaseType())); 
                else
                    isPointerType = CUtils.isPointerType(attribs[i].getTypeName());
                
                if (attribs[i].getChoiceElement() || attribs[i].getAllElement()
                        || attribs[i].isNillable() || isElementNillable(i) ||
                        isElementOptional(i) || isPointerType)
                {
                    writer.write("\tparam->"
                            + attribs[i].getParamNameAsMember() + " = "
                            + "axiscSoapDeSerializer"
                            + CUtils.getParameterGetValueMethodName(
                                    attribs[i].getTypeName(), attribs[i].isAttribute()) + "(pDZ, \""
                            + soapTagName + "\",0);\n");
                }                
                else
                {
                    String elementNameToSearchFor = attribs[i].isAttribute()? attribs[i].getParamNameAsMember():attribs[i].getSOAPElementNameAsString();
                    
                    writer.write("\t{\n");
                    writer.write("\t" + attribs[i].getTypeName() + " * "
                        + attribs[i].getParamNameAsMember() + " = " 
                        + "axiscSoapDeSerializer"
                        + CUtils.getParameterGetValueMethodName(attribs[i].getTypeName(), attribs[i].isAttribute()) 
                        + "(pDZ, \"" + elementNameToSearchFor + "\",0);\n");
                    
                    writer.write("\tif (" + attribs[i].getParamNameAsMember() + " != NULL)\n\t{\n");
                    writer.write("\t\tparam->" + attribs[i].getParamName() + " = *"
                            + attribs[i].getParamNameAsMember() + ";\n");

                    if (CUtils.getXSDTypeForBasicType( attribs[i].getTypeName()).equals("XSDC_HEXBINARY")
                            || CUtils.getXSDTypeForBasicType( attribs[i].getTypeName()).equals("XSDC_BASE64BINARY"))
                    {
                        writer.write( "\t\t" + attribs[i].getParamNameAsMember() + "->__ptr = NULL;\n");
                    }
                    
                    writer.write("\t\taxiscAxisDelete( (void *) " + attribs[i].getParamNameAsMember() 
                            + ", " + CUtils.getXSDTypeForBasicType( attribs[i].getTypeName()) + ");\n");
                    writer.write("\t}\n");  
                    writer.write("\t}\n");                    
                }
                
                if (attribs[i].isOptional() && !attribs[i].isAttribute())
                {
                    writer.write("\t\t\t}\n");
                    writer.write("\t\telse\n");
                    writer.write("\t\t\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                    writer.write("\n");
                    writer.write("\n\t}\n"); // end new variable scope
                }
            }
            else
            {
                writer.write("\n\t{\n"); // start new variable scope
                
                //if complex type
                //remove _Ref sufix and _ prefix in SOAP tag name
                String soapTagName = attribs[i].getParamName();

                if (soapTagName.lastIndexOf("_Ref") > -1)
                    soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref"));

                if (soapTagName.charAt(0) == '_')
                    soapTagName = soapTagName.substring(1, soapTagName.length());
                
                if (attribs[i].isOptional())
                {
                    writer.write("\tconst char* elementName" + i + " = axiscSoapDeSerializerPeekNextElementName(pDZ);\n");
                    writer.write("\tif(strcmp(elementName" + i + ", \"" + soapTagName + "\") == 0)\n");
                    writer.write("\t{\n");
                }

                writer.write("\tparam->" + attribs[i].getParamNameAsMember() 
                        + " = ("  + attribs[i].getTypeName()
                        + "*)axiscSoapDeSerializerGetCmplxObject(pDZ,(void*)Axis_DeSerialize_"
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
                
                writer.write("\n\t}\n"); // end new variable scope
            }

            if (attribs[i].getChoiceElement())
                writer.write("\t}\n");
            
            if (attribs[i].getAllElement())
                if (attribs[i].getMinOccurs() == 0)
                    writer.write("\t}\n");
            
            writer.write("\n");
        }
        
        if (extensionBaseAttrib != null
                && extensionBaseAttrib.getTypeName() != null)
        {
            if (extensionBaseAttrib.isSimpleType())
            {
                writer.write("\t{\n"); // ==== begin scope
                writer.write("\tvoid* pCharDataAs;\n");
                String typeName = extensionBaseAttrib.getTypeName();
                String xsdType = CUtils.getXSDTypeForBasicType(typeName);
                writer.write("\taxiscSoapDeSerializerGetChardataAs(pDZ, &pCharDataAs, " + xsdType + ");\n");
                writer.write("\tparam->" + extensionBaseAttrib.getParamNameAsMember() + " = ");
                
                if (CUtils.isPointerType(typeName))
                    writer.write("(" + typeName + ") pCharDataAs;\n");
                else
                {
                    writer.write(" *(" + typeName + "*) pCharDataAs;\n");
                    writer.write("\taxiscAxisDelete(pCharDataAs, " + xsdType + ");\n");
                }    
                writer.write("\t}\n"); // ==== end scope
            }
            else
            {
                // TODO
            }
        }
        
        writer.write("\t/* Return deserialization status */\n");
        writer.write("\treturn axiscSoapDeSerializerGetStatus(pDZ);\n");
        writer.write("}\n");
    }
    

    /**
     * @throws IOException
     */
    private void writeCreateGlobalMethod() throws IOException
    {
        boolean writeNewline = false;
        
        writer.write("\n");
        writer.write("/**\n");
        writer.write(" * This static method to allocate a " + classname + " type of object\n");
        writer.write(" */\n");
        
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
                    
                    String m_type =  CUtils.getXSDTypeForBasicType(baseTypeName);
                                    
                    writer.write("\t\tpTemp->" + attribs[i].getParamNameAsMember() 
                            + " = (" + baseTypeName + "_Array *)axiscAxisNew(XSDC_ARRAY, 0);\n");
                    
                    writer.write("\t\tpTemp->" + attribs[i].getParamNameAsMember() + "->m_Type = " 
                            + CUtils.getXSDTypeForBasicType(baseTypeName) + ";\n");
                }
                else
                {
                        writer.write("\t\tpTemp->" + attribs[i].getParamName() + " = "
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
        writer.write("\n");
        writer.write("/**\n");
        writer.write(" * This static method to deallocate a " + classname + " type of object\n");
        writer.write(" */\n");

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
                
                writer.write("\t\tif (param->" + attribs[i].getParamName() + ")\n");
                writer.write("\t\t\tAxis_Delete_" + attribs[i].getTypeName() + deleteFunctionSuffix 
                            + "(param->" + attribs[i].getParamName() + ", 0);\n");  
                    
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
            writer.write("\n");
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
    
    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#getFilePath(boolean)
     */
    protected File getFilePath(boolean useServiceName) throws WrapperFault
    {
        return null;
    }
}