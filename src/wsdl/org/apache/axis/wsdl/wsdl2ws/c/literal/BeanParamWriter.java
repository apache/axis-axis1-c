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

package org.apache.axis.wsdl.wsdl2ws.c.literal;

import java.io.IOException;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

/**
 * Genarate a webservice for the complex types likes structs.
 * @author hemapani
 */

public class BeanParamWriter
    extends org.apache.axis.wsdl.wsdl2ws.c.BeanParamWriter
{
    /**
     * @param wscontext
     * @param type
     * @throws WrapperFault
     */
    public BeanParamWriter(WebServiceContext wscontext, Type type)
        throws WrapperFault
    {
        super(wscontext, type);
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.ParamCPPFileWriter#writeGlobalCodes()
     */
    protected void writeGlobalCodes() throws WrapperFault
    {
        try
        {           
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
     * @throws IOException
     * @throws WrapperFault
     */
    private void writeSerializeGlobalMethod() throws IOException, WrapperFault
    {
        writer.write("/**\n");
        writer.write(" * This static method serializes a " + classname + " type of object\n");
        writer.write(" */\n");
        writer.write("int Axis_Serialize_" + classname
                + "(" + classname + "* param, AXISCHANDLE pSZ, AxiscBool bArray)\n{\n");
        
        if (attribs.length == 0)
        {
            writer.write("\taxiscSerializeIWrapperSoapSerializer(pSZ,\">\", NULL);\n");

            if (extensionBaseAttrib != null)
            {
                String typeName = extensionBaseAttrib.getTypeName();
                writer.write("\taxiscSerializeAsChardata(pSZ,(void*)");
                
                if (!CUtils.isPointerType(typeName))
                    writer.write("&");
                
                writer.write("(param->"
                        + extensionBaseAttrib.getParamNameAsMember()
                        + "), "
                        + CUtils.getXSDTypeForBasicType(typeName) + ");\n");
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
        writer.write("\t\taxiscSerializeAsAttribute(pSZ, \"xsi:nil\", 0, (void*)&(xsdc_boolean_true), XSD_BOOLEAN);\n");
        writer.write("\t\taxiscSerializeIWrapperSoapSerializer(pSZ, \">\", NULL);\n");
        writer.write("\t\treturn AXISC_SUCCESS;\n");
        writer.write("\t}\n\n");

        writer.write("\tif (!bArray)\n\t{\n");
        writer.write("\t\tconst AxiscChar* sPrefix = axiscGetNamespacePrefixIWrapperSoapSerializer(pSZ,Axis_URI_" + classname + ", &blnIsNewPrefix);\n");
        writer.write("\t\tif (blnIsNewPrefix)\n\t\t{\n");
        writer.write("\t\t\taxiscSerializeIWrapperSoapSerializer(pSZ,\" xmlns:\", sPrefix, \"=\\\"\",\n");
        writer.write("\t\t\t\tAxis_URI_" + classname + ", \"\\\"\", NULL );\n");
        writer.write("\t\t}\n");
        writer.write("\t}\n");

        
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
                boolean isPointerType = false;
                String basicType = null;
                
                if (!attribs[i].isSimpleType() && type.isSimpleType())
                {
                    basicType = CUtils.getclass4qname(attribs[i].getType().getBaseType());
                    isPointerType = CUtils.isPointerType(CUtils.getclass4qname(type.getBaseType())); 
                }
                else
                {
                    basicType = attribs[i].getTypeName();
                    isPointerType = CUtils.isPointerType(attribs[i].getTypeName());
                }
                
                if (isPointerType)
                {
                    writer.write("\tif (0 != param->" + attribs[i].getParamNameAsMember() + ")\n");
                    writer.write("\t\taxiscSerializeAsAttribute(pSZ,\""
                            + soapTagName + "\", 0, (void*)(param->"
                            + attribs[i].getParamNameAsMember() + "), "
                            + CUtils.getXSDTypeForBasicType(basicType) + ");\n");
                }
                else
                {
                    writer.write("\t\taxiscSerializeAsAttribute(pSZ,\""
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
            writer.write("\t\tAxiscBool blnIsNewPrefix = xsdc_boolean_false;\n");
            writer.write("\t\tconst AxisChar* sPrefix = axiscGetNamespacePrefixIWrapperSoapSerializer(pSZ,Axis_URI_"
                        + classname + ", &blnIsNewPrefix);\n");
            writer.write("\t\taxiscSerializeIWrapperSoapSerializer(pSZ, \" xmlns:\", sPrefix, \"=\\\"\",");
            writer.write("Axis_URI_" + classname + ", \" " + " \\\"\"");
            writer.write(", NULL);\n\t}\n");
        }               
        
        writer.write("\taxiscSerializeIWrapperSoapSerializer(pSZ, \">\", 0);\n");
        if (extensionBaseAttrib != null)
        {
            String typeName = extensionBaseAttrib.getTypeName(); 
            if( typeName != null)
            {
                writer.write("\taxiscSerializeAsChardata(pSZ, (void*)");
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
                writer.write("\taxiscSerializeAnyObject(pSZ, param->any" + Integer.toString(anyCounter) +");\n");
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
                    
                    writer.write("\taxiscSerializeBasicArray(pSZ, (const Axisc_Array *)param->" + attribs[i].getParamName()
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
                    
                    writer.write("\taxiscSerializeCmplxArray(pSZ, param->"
                                    + attribs[i].getParamNameAsMember() + ",\n");
                    writer.write("\t\t\t\t\t\t (void*) Axis_Serialize_" + arrayType + ",\n");
                    writer.write("\t\t\t\t\t\t (void*) Axis_Delete_" + arrayType + ",\n");
                    writer.write("\t\t\t\t\t\t (void*) Axis_GetSize_" + arrayType + ",\n");
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
                    writer.write("\t\taxiscSerializeAsElement(pSZ, \""
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
                            && !(attribs[i].getTypeName().equals("xsdc__string")) )
                    {
                        writer.write("\t\taxiscSerializeAsElement(pSZ, \""
                                + attribs[i].getSOAPElementNameAsString() + "\", " + namespace
                                + ", (void*)(*(param->" + attribs[i].getParamNameWithoutSymbols()
                                + ")), " + CUtils.getXSDTypeForBasicType(baseTypeName) + ");\n");
                    }
                    else
                    {
                        writer.write("\t\taxiscSerializeAsElement(pSZ, \""
                                + attribs[i].getSOAPElementNameAsString() + "\", " + namespace
                                + ", (void*)(param->" + attribs[i].getParamNameWithoutSymbols()
                                + "), " + CUtils.getXSDTypeForBasicType(baseTypeName) + ");\n");
                    }    
                }                           
                else
                {
                    writer.write("\taxiscSerializeAsElement(pSZ, \""
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
                    writer.write("\taxiscSerializeIWrapperSoapSerializer(pSZ, \"<\", axiscGetNamespacePrefixIWrapperSoapSerializer(pSZ, \""
                                    + type.getName().getNamespaceURI()
                                    + "\"), \":\", \"" + elm + "\", 0);\n");
                    writer.write("\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamName() + ", pSZ);\n");
                    writer.write("\taxiscSerializeIWrapperSoapSerializer(pSZ, \"</\", axiscGetNamespacePrefixIWrapperSoapSerializer(pSZ, \""
                                    + type.getName().getNamespaceURI()
                                    + "\"), \":\", \"" + elm + "\", \">\", 0);\n");
                }
                else
                {
                    writer.write("\taxiscSerializeIWrapperSoapSerializer(pSZ, \"<" + elm + "\", 0);\n");
                    writer.write("\tAxis_Serialize_" + attribs[i].getTypeName()
                            + "(param->" + attribs[i].getParamName() + ", pSZ);\n");
                    writer.write("\taxiscSerializeIWrapperSoapSerializer(pSZ, \"</" + elm + "\", \">\", 0);\n");
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

        writer.write("\n\tif (!bArray && blnIsNewPrefix)\n");
        writer.write("\t\taxiscRemoveNamespacePrefix(pSZ, Axis_URI_" + classname + ");\n\n");
        
        writer.write("\treturn AXISC_SUCCESS;\n");
        writer.write("}\n\n");     
    }

    /**
     * @throws IOException
     * @throws WrapperFault
     */
    private void writeDeSerializeGlobalMethod() throws IOException, WrapperFault
    {
        writer.write("/**\n");
        writer.write(" * This static method deserializes a " + classname + " type of object\n");
        writer.write(" */\n");
        writer.write("int Axis_DeSerialize_" + classname
                + "(" + classname + "* param, AXISCHANDLE pDZ)\n{\n");
        
        if (attribs.length == 0)
        {
            if (extensionBaseAttrib != null)
            {
                writer.write("\taxiscGetChardataAs(pDZ, (void*)&(param->"
                        + extensionBaseAttrib.getParamNameAsMember() + "), "
                        + CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName()) + ");\n");
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
            // the choice - TODO

            //if the attribute is a 'all' construct we have to check Min
            // occures TODO

            
            if (attribs[i].isAnyType())
            {
                anyCounter +=1;
                writer.write("\tparam->any" + anyCounter + " = axiscGetAnyObject(pDZ);\n");
            }
            else if (attribs[i].isArray())
            {
                writer.write("\n\t{\n"); // start new variable scope
                arrayCount++;
                
                if (attribs[i].isSimpleType() || attribs[i].getType().isSimpleType())
                {
                    String baseTypeName = null;
                    if (!attribs[i].isSimpleType() && attribs[i].getType().isSimpleType())
                        baseTypeName = CUtils.getclass4qname(attribs[i].getType().getBaseType());
                    else
                        baseTypeName = attribs[i].getTypeName();
                    
                    writer.write("\tAxisc_Array *array" + arrayCount + "= axiscGetBasicArrayIWrapperSoapDeSerializer(pDZ, " 
                            + CUtils.getXSDTypeForBasicType(baseTypeName) + ", \"" 
                            + attribs[i].getParamNameAsSOAPElement()
                            + "\",0);\n");
                    
                    // TODO MEMORY MANAGEMENT
                }
                else
                {
                    arrayType = attribs[i].getTypeName();
                    writer.write("\tAxisc_Array array" + arrayCount + " = axiscGetCmplxArrayCall(pDZ," 
                            + "&array" + arrayCount + ","
                            + "(void*)Axis_DeSerialize_"  + arrayType
                            + "\n\t\t, (void*)Axis_Create_" + arrayType
                            + ", (void*)Axis_Delete_" + arrayType
                            + "\n\t\t, (void*)Axis_GetSize_" + arrayType
                            + ", \""  + attribs[i].getElementNameAsString()
                            + "\", Axis_URI_" + arrayType + ");\n");
                }
                
                writer.write("\tmemcpy(&(param->" + attribs[i].getParamName()
                        + "), &array" + arrayCount + ", sizeof(Axisc_Array));\n");
                
                writer.write("\n\t}\n"); // end new variable scope
            }
            else if ((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()))
            {
                writer.write("\n\t{\n"); // start new variable scope
                
                String soapTagName = (attribs[i].isAttribute() ? attribs[i].getParamName() : attribs[i].getElementNameAsString());
                if (soapTagName.lastIndexOf("_Ref") > -1)
                    soapTagName = soapTagName.substring(0, soapTagName.lastIndexOf("_Ref"));

                if (soapTagName.charAt(0) == '_')
                    soapTagName = soapTagName.substring(1, soapTagName.length());
                
                if (attribs[i].isOptional())
                {
                    writer.write("\tconst char* elementName" + i + " = axiscPeekNextElementName(pDZ);\n");
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
                        // TODO
                        writer.write("\tparam->"
                                + attribs[i].getParamNameAsMember()
                                + " = (" + attribs[i].getTypeName()
                                + "**)(" + attribs[i].getTypeName()
                                +"*)malloc(sizeof(" +attribs[i].getTypeName() + ");\n");
                        
                        writer.write("\t\t*(param->"
                                + attribs[i].getParamNameAsMember() + ") = "
                                + CUtils.getParameterGetValueMethodName(
                                        attribs[i].getTypeName(), attribs[i].isAttribute()) + "(pDZ, \""
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

                        String elementName = attribs[i].getParamNameAsMember();

                        writer.write("\t{\n");
                        if( isPointerType)
                        {
                            writer.write("\t" + typeName + "    pValue" + i + " = " +
                                    CUtils.getParameterGetValueMethodName(baseTypeName, attribs[i].isAttribute()) +
                                    "(pDZ,\"" + soapTagName + "\", 0);\n\n");
                        }
                        else
                        {
                            writer.write("\t" + typeName + " *  pValue" + i + " = " +
                                    CUtils.getParameterGetValueMethodName(baseTypeName, attribs[i].isAttribute()) +
                                    "(pDZ, \"" + soapTagName + "\", 0);\n\n");
                        }
                        
                        writer.write( "\tparam->" + elementName + "= pValue" + i + ";\n");
                        writer.write( "\tif( pValue" + i + " != NULL)\n");
                        writer.write("\t\taxiscAxisDelete( (void *) pValue" + i + ", " 
                                + CUtils.getXSDTypeForBasicType( baseTypeName) + ");\n\n");
                        writer.write("\t}\n\n");
                    }
                } 
                else if (attribs[i].getChoiceElement() || attribs[i].getAllElement())
                {
                    writer.write("\tparam->"
                            + attribs[i].getParamNameAsMember() + " = "
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
                        + CUtils.getParameterGetValueMethodName(attribs[i].getTypeName(), attribs[i].isAttribute()) 
                        + "(pDZ, \"" + elementNameToSearchFor + "\",0);\n");
                    
                    writer.write("\tif (" + attribs[i].getParamNameAsMember() + " != NULL)\n\t{\n");
                    writer.write("\t\tparam->" + attribs[i].getParamName() + " = *"
                            + attribs[i].getParamNameAsMember() + ";\n");
                    writer.write("\t\taxiscAxisDelete( (void *) " + attribs[i].getParamNameAsMember() 
                            + ", " + CUtils.getXSDTypeForBasicType( attribs[i].getTypeName()) + ");\n");
                    writer.write("\t}\n");  
                    writer.write("\t}\n");                    
                }
                
                if (attribs[i].isOptional())
                {
                    writer.write("\t\t\t}\n");
                    writer.write("\t\telse\n");
                    writer.write("\t\t{\n");
                    writer.write("\t\t\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                    writer.write("\t\t}\n\n");
                }
                
                writer.write("\n\t}\n"); // end new variable scope
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
                    writer.write("\tconst char* elementName" + i + " = axiscPeekNextElementName(pDZ);\n");
                    writer.write("\tif(strcmp(elementName" + i + ", \"" + soapTagName + "\") == 0)\n");
                    writer.write("\t{\n");
                }

                writer.write("\tparam->" + attribs[i].getParamNameAsMember() 
                        + " = ("  + attribs[i].getTypeName()
                        + "*)axiscGetCmplxObject(pDZ,(void*)Axis_DeSerialize_"
                        + attribs[i].getTypeName()
                        + "\n\t\t, (void*)Axis_Create_"
                        + attribs[i].getTypeName() + ", (void*)Axis_Delete_"
                        + attribs[i].getTypeName() + "\n\t\t, \"" + soapTagName
                        + "\", Axis_URI_" + attribs[i].getTypeName() + ");\n");
                
                if (attribs[i].isOptional())
                {
                    writer.write("\t}\n");
                    writer.write("\telse\n");
                    writer.write("\t{\n");
                    writer.write("\t\tparam->" + attribs[i].getParamNameAsMember() + " = NULL;\n");
                    writer.write("\t}\n\n");
                }      
                
                writer.write("\n\t}\n"); // end new variable scope
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
            writer.write("\taxiscGetChardataAs(pDZ, (void*)&(param->"
                    + extensionBaseAttrib.getParamNameAsMember() + "), "
                    + CUtils.getXSDTypeForBasicType(extensionBaseAttrib.getTypeName()) + ");\n");
        }
        
        writer.write("\treturn axiscGetStatusIWrapperSoapDeSerializer(pDZ);\n");
        writer.write("}\n");
    }

    /**
     * @throws IOException
     */
    private void writeCreateGlobalMethod() throws IOException
    {
        writer.write("/**\n");
        writer.write(" * This static method to deallocate a " + classname + " type of object\n");
        writer.write(" */\n");
        
        writer.write("void* Axis_Create_" + classname + "(void* pObj, AxiscBool bArray, int nSize)\n{\n");
        writer.write("\t" + classname + "* pTemp;\n");
        writer.write("\tif (bArray && (nSize > 0))\n\t{\n");
        writer.write("\t\tif (pObj)\n\t\t{\n");
        writer.write("\t\t\tpObj = (void *)  realloc(pObj, sizeof(" + classname + ")*nSize);\n");
        writer.write("\t\t\tpTemp = pObj;\n");
        writer.write("\t\t\tpTemp += nSize/2;\n");
        writer.write("\t\t\tmemset(pTemp, 0, sizeof(" + classname + ")*nSize/2);\n");
        writer.write("\t\t}\n\t\telse\n\t\t{\n");
        writer.write("\t\t\tpObj = (void *)  malloc(sizeof(" + classname + ")*nSize);\n");
        writer.write("\t\t\tmemset(pObj, 0, sizeof(" + classname + ")*nSize);\n\t\t}\n");
        writer.write("\t}\n\telse\n\t{\n");
        writer.write("\t\tpObj = (void *)  malloc(sizeof(" + classname + "));\n");
        writer.write("\t\tmemset(pObj, 0, sizeof(" + classname + "));\n\n");
        writer.write("\t}\n\treturn pObj;\n}\n");
    }

    /**
     * @throws IOException
     */
    private void writeDeleteGlobalMethod() throws IOException
    {
        writer.write("/**\n");
        writer.write(" * This static method to deallocate a " + classname + " type of object\n");
        writer.write(" */\n");

        writer.write("void Axis_Delete_" + classname
                + "(" + classname + "* param, AxiscBool bArray, int nSize)\n");
        writer.write("{\n");
        writer.write("\tif (!param) return;\n\n");
        writer.write("\tif (bArray)\n");
        writer.write("\t{\n");
        writer.write("\t\tif (nSize > 0)\n");
        writer.write("\t\t{\n");
        writer.write("\t\t\tint count;\n");
        writer.write("\t\t\tfor (count = 0 ; count < nSize ; count++ )\n");
        writer.write("\t\t\t{\n");
        writer.write("\t\t\t\tif ( (( " + classname + " ** ) param)[count])\n");
        writer.write("\t\t\t\t{\n");
        writer.write("\t\t\t\t\tfree ((( " + classname + " ** ) param)[count]);\n");
        writer.write("\t\t\t\t}\n");
        writer.write("\t\t\t}\n");
        writer.write("\t\t\tfree(( " + classname + " ** ) param);\n");
        writer.write("\t\t}\n");
        writer.write("\t}\n");
        writer.write("\telse\n");
        writer.write("\t{\n");
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
                        nillable = true;
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
                                moreThanOne = true;
                        }
                    }
                }
            }
        }

        return moreThanOne;
    }
    
}
