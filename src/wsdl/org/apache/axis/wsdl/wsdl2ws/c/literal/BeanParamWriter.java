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
                if (!typeName.equals(type.getName().getLocalPart()))
                {
                    writer.write(
                        "extern int Axis_DeSerialize_"
                            + typeName
                            + "("
                            + typeName
                            + "* param, AXISCHANDLE pDZ);\n");
                    writer.write(
                        "extern void* Axis_Create_"
                            + typeName
                            + "("
                            + typeName
                            + "* pObj, AxiscBool bArray, int nSize);\n");
                    writer.write(
                        "extern void Axis_Delete_"
                            + typeName
                            + "("
                            + typeName
                            + "* param, AxiscBool bArray, int nSize);\n");
                    writer.write(
                        "extern int Axis_Serialize_"
                            + typeName
                            + "("
                            + typeName
                            + "* param, AXISCHANDLE pSZ, AxiscBool bArray);\n");
                    writer.write(
                        "extern int Axis_GetSize_" + typeName + "();\n\n");
                }
                else
                {
                    writer.write(
                        "int Axis_DeSerialize_"
                            + typeName
                            + "("
                            + typeName
                            + "* param, AXISCHANDLE pDZ);\n");
                    writer.write(
                        "void* Axis_Create_"
                            + typeName
                            + "(void* pObj, AxiscBool bArray, int nSize);\n");
                    writer.write(
                        "void Axis_Delete_"
                            + typeName
                            + "("
                            + typeName
                            + "* param, AxiscBool bArray, int nSize);\n");
                    writer.write(
                        "int Axis_Serialize_"
                            + typeName
                            + "("
                            + typeName
                            + "* param, AXISCHANDLE pSZ, AxiscBool bArray);\n");
                    writer.write("int Axis_GetSize_" + typeName + "();\n\n");
                }
            }
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
        writer.write(
            " * This static method serialize a "
                + classname
                + " type of object\n");
        writer.write(" */\n");

        writer.write(
            "int Axis_Serialize_"
                + classname
                + "("
                + classname
                + "* param, AXISCHANDLE pSZ, AxiscBool bArray)\n{\n");
        if (attribs.length == 0)
        {
            System.out.println(
                "Possible error in class "
                    + classname
                    + ": class with no attributes....................");
            writer.write(
                "\taxiscSerializeIWrapperSoapSerializer(pSZ, \">\");\n");
            writer.write("\treturn AXISC_SUCCESS;\n");
            writer.write("}\n\n");
            return;
        }
        writer.write("\tif ( param == NULL ) {\n");
        writer.write("\t\t/* TODO : may need to check nillable value*/\n");
        writer.write(
            "\t\taxiscSerializeAsAttribute(pSZ,\"xsi:nil\", 0, (void*)&(xsdc_boolean_true), XSD_BOOLEAN);\n");
        writer.write("\t\taxiscSerializeIWrapperSoapSerializer(pSZ, \">\");\n");
        writer.write("\t\treturn AXISC_SUCCESS;\n");
        writer.write("\t}\n");
        String arrayType = null;
        writer.write("\t/* first serialize attributes if any*/\n");
        for (int i = 0; i < attributeParamCount; i++)
        {
            if (attribs[i].isArray() || !(attribs[i].isSimpleType()))
            {
                throw new WrapperFault("Error : an attribute is not basic type");
            }
            else
            {
                writer.write(
                    "\tif (0 != param->" + attribs[i].getParamName() + ")\n");
                writer.write(
                    "\t\taxiscSerializeAsAttribute(pSZ, \""
                        + attribs[i].getParamName()
                        + "\", 0, (void*)&(param->"
                        + attribs[i].getParamName()
                        + "), "
                        + CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())
                        + ");\n");
                if (!attribs[i].isOptional())
                {
                    /* TODO : AxisTrace need to be adpated for used in C */
                }
            }
        }
        writer.write("\taxiscSerializeIWrapperSoapSerializer(pSZ, \">\");\n");
        writer.write("\t/* then serialize elements if any*/\n");
        for (int i = attributeParamCount; i < attribs.length; i++)
        {
            if (attribs[i].isAnyType())
            {
                writer.write(
                    "\taxiscSerializeAnyObject(pSZ, param->any);\n");
            }
            else
                if (attribs[i].isArray())
                {
                    //if Array
                    arrayType = attribs[i].getTypeName();
                    if (attribs[i].isSimpleType())
                    {
                        writer.write(
                            "\taxiscSerializeBasicArray(pSZ, (Axisc_Array*)(&param->"
                                + attribs[i].getParamName()
                                + "),"
                                + CUtils.getXSDTypeForBasicType(arrayType)
                                + ", \""
                                + attribs[i].getElementName().getLocalPart()
                                + "\");\n");
                    }
                    else
                    {
                        writer.write(
                            "\taxiscSerializeCmplxArray(pSZ, (Axisc_Array*)(&param->"
                                + attribs[i].getParamName()
                                + "),\n");
                        writer.write(
                            "\t\t(void*) Axis_Serialize_"
                                + arrayType
                                + ", (void*) Axis_Delete_"
                                + arrayType
                                + ", (void*) Axis_GetSize_"
                                + arrayType
                                + ",\n");
                        writer.write(
                            "\t\t\""
                                + attribs[i].getElementName().getLocalPart()
                                + "\", Axis_URI_"
                                + arrayType
                                + ");\n");
                    }
                }
                else
                    if (attribs[i].isSimpleType())
                    {
                        //Samisa 22/08/2004
                        writer.write(
                            "\taxiscSerializeAsElement(pSZ, \""
                                + attribs[i].getElementNameAsString()
                                + "\", NULL, (void*)&(param->"
                                + attribs[i].getParamName()
                                + "), "
                                + CUtils.getXSDTypeForBasicType(
                                    attribs[i].getTypeName())
                                + ");\n");
                        //Samisa
                    }
                    else
                    {
                        //if complex type
                        String elm = attribs[i].getParamName();
                        if (attribs[i].isReference())
                            elm = attribs[i].getTypeName();
                        writer.write(
                            "\taxiscSerializeIWrapperSoapSerializer(pSZ, \"<"
                                + elm
                                + "\");\n");
                        writer.write(
                            "\tAxis_Serialize_"
                                + attribs[i].getTypeName()
                                + "(param->"
                                + attribs[i].getParamName()
                                + ", pSZ, false);\n");
                        writer.write(
                            "\taxiscSerializeIWrapperSoapSerializer(pSZ, \"</"
                                + elm
                                + ">\");\n");
                    }
        }
        writer.write("\treturn AXISC_SUCCESS;\n");
        writer.write("}\n\n");

    }

    /**
     * @throws IOException
     * @throws WrapperFault
     */
    private void writeDeSerializeGlobalMethod()
        throws IOException, WrapperFault
    {
        writer.write("/**\n");
        writer.write(
            " * This static method deserialize a "
                + classname
                + " type of object\n");
        writer.write(" */\n");

        writer.write(
            "int Axis_DeSerialize_"
                + classname
                + "("
                + classname
                + "* param, AXISCHANDLE pDZ)\n{\n");
        if (attribs.length == 0)
        {
            //nothing to print if this is simple type we have inbuild types
            System.out.println(
                "Possible error in class "
                    + classname
                    + ": class with no attributes....................");
            // compilation issue;
            writer.write("\treturn AXISC_SUCCESS;\n");
            writer.write("}\n\n");
            return;
        }
        boolean aretherearrayparams = false;
        for (int i = 0; i < attribs.length; i++)
        {
            if (attribs[i].isArray())
            {
                aretherearrayparams = true;
                break;
            }
        }
        if (aretherearrayparams)
        {
            writer.write("\tAxisc_Array array;\n");
        }
        writer.write("\t/* first deserialize attributes if any*/\n");
        for (int i = 0; i < attribs.length; i++)
        {
            if (i == attributeParamCount)
                writer.write("\t/* then deserialize elements if any*/\n");
            if (attribs[i].isAnyType())
            {
                writer.write(
                    "\tparam->any = axiscGetAnyObject(pDZ);\n");
            }
            else
                if (attribs[i].isArray())
                {
                    //if Array
                    String containedType = attribs[i].getTypeName();
                    if (attribs[i].isSimpleType())
                    {
                        writer.write(
                            "\tarray = axiscGetBasicArray(pDZ, "
                                + CUtils.getXSDTypeForBasicType(containedType)
                                + ", \""
                                + attribs[i].getElementName().getLocalPart()
                                + "\",0);\n");
                        writer.write(
                            "\tmemcpy(&(param->"
                                + attribs[i].getParamName()
                                + "), &array, sizeof(Axisc_Array));\n");
                    }
                    else
                    {
                        writer.write(
                            "\tarray = axiscGetCmplxArray(pDZ, (void*)Axis_DeSerialize_"
                                + containedType
                                + "\n\t\t, (void*)Axis_Create_"
                                + containedType
                                + ", (void*)Axis_Delete_"
                                + containedType
                                + "\n\t\t, (void*)Axis_GetSize_"
                                + containedType
                                + ", \""
                                + attribs[i].getElementName().getLocalPart()
                                + "\", Axis_URI_"
                                + containedType
                                + ");\n");
                        writer.write(
                            "\tmemcpy(&(param->"
                                + attribs[i].getParamName()
                                + "), &array, sizeof(Axisc_Array));\n");
                    }
                }
                else
                    if (attribs[i].isSimpleType())
                    {
                        //if symple type
                        if (attribs[i].isAttribute())
                        {
                            if (attribs[i].isOptional())
                            {
                                //TODO
                            }
                            else
                            {
                                writer.write(
                                    "\tparam->"
                                        + attribs[i].getParamName()
                                        + " = "
                                        + CUtils.getParameterGetValueMethodName(
                                            attribs[i].getTypeName(),
                                            true)
                                        + "(pDZ, \""
                                        + attribs[i].getParamName()
                                        + "\", 0);\n");
                            }
                        }
                        else
                        {
                            writer.write(
                                "\tparam->"
                                    + attribs[i].getParamName()
                                    + " = "
                                    + CUtils.getParameterGetValueMethodName(
                                        attribs[i].getTypeName(),
                                        false)
                                    + "(pDZ, \""
                                    + attribs[i].getElementName().getLocalPart()
                                    + "\", 0);\n");
                        }
                    }
                    else
                    {
                        //if complex type
                        writer.write(
                            "\tparam->"
                                + attribs[i].getParamName()
                                + " = ("
                                + attribs[i].getTypeName()
                                + "*)axiscGetCmplxObject(pDZ, (void*)Axis_DeSerialize_"
                                + attribs[i].getTypeName()
                                + "\n\t\t, (void*)Axis_Create_"
                                + attribs[i].getTypeName()
                                + ", (void*)Axis_Delete_"
                                + attribs[i].getTypeName()
                                + "\n\t\t, \""
                                + attribs[i].getElementName().getLocalPart()
                                + "\", Axis_URI_"
                                + attribs[i].getTypeName()
                                + ");\n");
                    }
        }
        writer.write("\treturn axiscGetStatusIWrapperSoapDeSerializer(pDZ);\n");
        writer.write("}\n");
    }

    /**
     * @throws IOException
     */
    private void writeCreateGlobalMethod() throws IOException
    {
        writer.write(
            "void* Axis_Create_"
                + classname
                + "(void* pObj, AxiscBool bArray, int nSize)\n{\n");
        writer.write("\t" + classname + "* pTemp;\n");
        writer.write("\tif (bArray && (nSize > 0))\n\t{\n");
        writer.write("\t\tif (pObj)\n\t\t{\n");
        writer.write(
            "\t\t\tpObj = (void *)  realloc(pObj, sizeof("
                + classname
                + ")*nSize);\n");
        writer.write("\t\t\tpTemp = pObj;\n");
        writer.write("\t\t\tpTemp += nSize/2;\n");
        writer.write(
            "\t\t\tmemset(pTemp, 0, sizeof(" + classname + ")*nSize/2);\n");
        writer.write("\t\t}\n\t\telse\n\t\t{\n");
        writer.write(
            "\t\t\tpObj = (void *)  malloc(sizeof("
                + classname
                + ")*nSize);\n");
        writer.write(
            "\t\t\tmemset(pObj, 0, sizeof(" + classname + ")*nSize);\n\t\t}\n");
        writer.write("\t\treturn pObj;\n");
        writer.write("\t}\n\telse\n\t{\n");
        writer.write(
            "\t\tpObj = (void *)  malloc(sizeof(" + classname + "));\n");
        writer.write("\t\tmemset(pObj, 0, sizeof(" + classname + "));\n\n");
        writer.write("\t\tpTemp = pObj;\n");
        for (int i = 0; i < attribs.length; i++)
        {
            if (attribs[i].isArray())
            {
                writer.write(
                    "\t\tpTemp->"
                        + attribs[i].getParamName()
                        + ".m_Array = 0;\n");
                writer.write(
                    "\t\tpTemp->"
                        + attribs[i].getParamName()
                        + ".m_Size = 0;\n");
            }
            else
                if (!attribs[i].isSimpleType())
                {
                    writer.write(
                        "\t\tpTemp->" + attribs[i].getParamName() + "=0;\n");
                }
        }
        writer.write("\t}\n\treturn pObj;\n}\n");
    }

    /**
     * @throws IOException
     */
    private void writeDeleteGlobalMethod() throws IOException
    {
        writer.write("/**\n");
        writer.write(
            " * This static method to deallocate a "
                + classname
                + " type of object\n");
        writer.write(" */\n");

        writer.write(
            "void Axis_Delete_"
                + classname
                + "("
                + classname
                + "* param, AxiscBool bArray, int nSize)\n");
        writer.write("{\n");
        boolean hasComplexTypeOrArray = false;
        for (int i = 0; i < attribs.length; i++)
        {
            if (!attribs[i].isSimpleType())
            {
                hasComplexTypeOrArray = true;
                break;
            }
            else
                if ("xsdc__string".equals(attribs[i].getTypeName()))
                {
                    hasComplexTypeOrArray = true;
                    break;
                }
                else
                    if ("xsdc__base64Binary".equals(attribs[i].getTypeName()))
                    {
                        hasComplexTypeOrArray = true;
                        break;
                    }
                    else
                        if ("xsdc__hexBinary".equals(attribs[i].getTypeName()))
                        {
                            hasComplexTypeOrArray = true;
                            break;
                        }
        }
        if (hasComplexTypeOrArray)
        {
            writer.write("\tint x, i;\n");
            writer.write("\t" + classname + "* pTemp;\n");
        }
        writer.write("\tif (bArray)\n");
        writer.write("\t{\n");
        if (hasComplexTypeOrArray)
        {
            writer.write(
                "\t\t/*delete any pointer members or array members of this struct here*/\n");
            writer.write("\t\tpTemp = param;\n");
            writer.write("\t\tfor (x=0; x<nSize; x++)\n");
            writer.write("\t\t{\n");
            for (int i = 0; i < attribs.length; i++)
            {
                if (attribs[i].isArray())
                {
                    if (attribs[i].isSimpleType())
                    {
                        writer.write(
                            "\t\t\tif (pTemp->"
                                + attribs[i].getParamName()
                                + ".m_Array) free(pTemp->"
                                + attribs[i].getParamName()
                                + ".m_Array);\n");
                    }
                    else
                    {
                        writer.write(
                            "\t\t\tif (pTemp->"
                                + attribs[i].getParamName()
                                + ".m_Array) Axis_Delete_"
                                + attribs[i].getTypeName()
                                + "(pTemp->"
                                + attribs[i].getParamName()
                                + ".m_Array, true, pTemp->"
                                + attribs[i].getParamName()
                                + ".m_Size);\n");
                    }
                }
                else
                    if (attribs[i].isAnyType())
                    {
                        writer.write(
                            "\t\t\tif (pTemp->"
                                + attribs[i].getParamName()
                                + ") \n\t\t\t{ \n");
                        writer.write(
                            "\t\t\t\tfor (i=0; i<pTemp->"
                                + attribs[i].getParamName()
                                + "->_size; i++)\n\t\t\t\t{\n");
                        writer.write(
                            "\t\t\t\t\tif (pTemp->"
                                + attribs[i].getParamName()
                                + "->_array[i]) free(pTemp->"
                                + attribs[i].getParamName()
                                + "->_array[i]);\n");
                        writer.write("\t\t\t\t}\n");
                        writer.write(
                            "\t\t\t\tfree(pTemp->"
                                + attribs[i].getParamName()
                                + ");\n");
                        writer.write("\t\t\t}\n");
                    }
                    else
                        if (!attribs[i].isSimpleType())
                        {
                            writer.write(
                                "\t\t\tif (pTemp->"
                                    + attribs[i].getParamName()
                                    + ") Axis_Delete_"
                                    + attribs[i].getTypeName()
                                    + "(pTemp->"
                                    + attribs[i].getParamName()
                                    + ", false, 0);\n");
                        }
                        else
                            if ("xsdc__string".equals(attribs[i].getTypeName()))
                            {
                                writer.write(
                                    "\t\t\tif(pTemp->"
                                        + attribs[i].getParamName()
                                        + ") free(pTemp->"
                                        + attribs[i].getParamName()
                                        + ");\n");
                            }
                            else
                                if ("xsdc__base64Binary"
                                    .equals(attribs[i].getTypeName()))
                                {
                                    writer.write(
                                        "\t\t\tif(pTemp->"
                                            + attribs[i].getParamName()
                                            + ".__ptr) free(pTemp->"
                                            + attribs[i].getParamName()
                                            + ".__ptr);\n");
                                }
                                else
                                    if ("xsdc__hexBinary"
                                        .equals(attribs[i].getTypeName()))
                                    {
                                        writer.write(
                                            "\t\t\tif(pTemp->"
                                                + attribs[i].getParamName()
                                                + ".__ptr) free(pTemp->"
                                                + attribs[i].getParamName()
                                                + ".__ptr);\n");
                                    }
                                    else
                                        if (attribs[i].isOptional())
                                        {
                                            //TODO
                                        }
            }
            writer.write("\t\t\tpTemp++;\n");
            writer.write("\t\t}\n");
        }
        writer.write("\t\tfree(param);\n");
        writer.write("\t}\n");
        writer.write("\telse\n");
        writer.write("\t{\n");
        writer.write(
            "\t\t/*delete any pointer members or array members of this struct here*/\n");
        for (int i = 0; i < attribs.length; i++)
        {
            if (attribs[i].isArray())
            {
                if (attribs[i].isSimpleType())
                {
                    writer.write(
                        "\t\tif (param->"
                            + attribs[i].getParamName()
                            + ".m_Array) free(param->"
                            + attribs[i].getParamName()
                            + ".m_Array);\n");
                }
                else
                {
                    writer.write(
                        "\t\tif (param->"
                            + attribs[i].getParamName()
                            + ".m_Array) Axis_Delete_"
                            + attribs[i].getTypeName()
                            + "(param->"
                            + attribs[i].getParamName()
                            + ".m_Array, true, param->"
                            + attribs[i].getParamName()
                            + ".m_Size);\n");
                }
            }
            else
                if (attribs[i].isAnyType())
                {
                    writer.write(
                        "\t\tif (param->"
                            + attribs[i].getParamName()
                            + ") \n\t\t{ \n");
                    writer.write(
                        "\t\t\tfor (i=0; i<param->"
                            + attribs[i].getParamName()
                            + "->_size; i++)\n\t\t\t{\n");
                    writer.write(
                        "\t\t\t\tif (param->"
                            + attribs[i].getParamName()
                            + "->_array[i]) free(param->"
                            + attribs[i].getParamName()
                            + "->_array[i]);\n");
                    writer.write("\t\t\t}\n");
                    writer.write(
                        "\t\t\tfree(param->"
                            + attribs[i].getParamName()
                            + ");\n");
                    writer.write("\t\t}\n");
                }
                else
                    if (!attribs[i].isSimpleType())
                    {
                        writer.write(
                            "\t\tif (param->"
                                + attribs[i].getParamName()
                                + ") Axis_Delete_"
                                + attribs[i].getTypeName()
                                + "(param->"
                                + attribs[i].getParamName()
                                + ", false, 0);\n");
                    }
                    else
                        if ("xsdc__string".equals(attribs[i].getTypeName()))
                        {
                            writer.write(
                                "\t\tif(param->"
                                    + attribs[i].getParamName()
                                    + ") free(param->"
                                    + attribs[i].getParamName()
                                    + ");\n");
                        }
                        else
                            if ("xsdc__base64Binary"
                                .equals(attribs[i].getTypeName()))
                            {
                                writer.write(
                                    "\t\tif(param->"
                                        + attribs[i].getParamName()
                                        + ".__ptr) free(param->"
                                        + attribs[i].getParamName()
                                        + ".__ptr);\n");
                            }
                            else
                                if ("xsdc__hexBinary"
                                    .equals(attribs[i].getTypeName()))
                                {
                                    writer.write(
                                        "\t\tif(param->"
                                            + attribs[i].getParamName()
                                            + ".__ptr) free(param->"
                                            + attribs[i].getParamName()
                                            + ".__ptr);\n");
                                }
                                else
                                    if (attribs[i].isOptional())
                                    {
                                        //TODO
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
            writer.write(
                "int Check_Restrictions_"
                    + classname
                    + "("
                    + classname
                    + " value)\n");
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
}
