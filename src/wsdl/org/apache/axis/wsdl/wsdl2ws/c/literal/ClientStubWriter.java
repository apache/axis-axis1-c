/*
 *   Copyright 2003-2004 The Apache Software Foundation.
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
 * @author Kanchana Welagedara(kanchana@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws.c.literal;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ClientStubWriter
    extends org.apache.axis.wsdl.wsdl2ws.c.ClientStubWriter
{
    /**
     * @param wscontext
     * @throws WrapperFault
     */
    public ClientStubWriter(WebServiceContext wscontext) throws WrapperFault
    {
        super(wscontext);
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#writeMethods()
     */
    protected void writeMethods() throws WrapperFault
    {
        try
        {
            writer.write(
                "AXISCHANDLE get_"
                    + classname
                    + "_stub(const char* pchEndPointUri)\n{");
            writer.write("\tif(pchEndPointUri)\n");
            writer.write("\t{\n");
            writer.write(
                "\t\treturn axiscCreateStub(pchEndPointUri, AXISC_PTHTTP1_1);\n");
            writer.write("\t}\n");
            writer.write("\telse\n");
            writer.write("\t{\n");
            writer.write(
                "\t\treturn axiscCreateStub(\""
                    + wscontext.getWrapInfo().getTargetEndpointURI()
                    + "\", AXISC_PTHTTP1_1);\n");
            writer.write("\t}\n");
            writer.write("}\n");
            writer.write("void destroy_" + classname + "_stub(AXISCHANDLE p){\n");
            writer.write("\taxiscDestroyStub(p);\n}\n");

            writer.write("int get_" + classname + "_Status(AXISCHANDLE stub){\n");
            writer.write("\tAXISCHANDLE call = axiscGetCall(stub);\n");
            writer.write("\tif ( stub == NULL )\n");
            writer.write("\t\treturn AXISC_FAIL;\n");
            writer.write("\telse\n");
            writer.write("\t\treturn axiscGetStatusCall(call);\n");
            writer.write("}\n");

            writer.write(
                "\n/*Methods corresponding to the web service methods*/\n");
            MethodInfo minfo;
            for (int i = 0; i < methods.size(); i++)
            {
                minfo = (MethodInfo) methods.get(i);
                this.writeMethodInWrapper(minfo);
                writer.write("\n");
            }

        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /**
     * This method genarate methods that wraps the each method of the service
     * @param MethodInfo
     * @throws IOException
     * @throws WrapperFault
     * 
     * @see org.apache.axis.wsdl.wsdl2ws.c.ClientStubWriter#writeMethodInWrapper(org.apache.axis.wsdl.wsdl2ws.info.MethodInfo) 
     */

    public void writeMethodInWrapper(MethodInfo minfo)
        throws WrapperFault, IOException
    {
        boolean isAllTreatedAsOutParams = false;
        ParameterInfo returntype = null;
        int noOfOutParams = minfo.getOutputParameterTypes().size();
        if (0 == noOfOutParams)
        {
            returntype = null;
        }
        else
            if (1 == noOfOutParams)
            {
                returntype =
                    (ParameterInfo) minfo
                        .getOutputParameterTypes()
                        .iterator()
                        .next();
            }
            else
            {
                isAllTreatedAsOutParams = true;
            }
        Collection params = minfo.getInputParameterTypes();
        String methodName = minfo.getMethodname();
        Type retType = null;
        boolean returntypeissimple = false;
        boolean returntypeisarray = false;
        boolean aretherearrayparams = false;
        String outparamType = null;
        if (returntype != null)
            retType =
                wscontext.getTypemap().getType(returntype.getSchemaName());
        if (retType != null)
        {
            outparamType = retType.getLanguageSpecificName();
            returntypeisarray = retType.isArray();
        }
        else
            if (returntype != null)
            {
                outparamType = returntype.getLangName();
            }
        if (returntype != null)
            returntypeissimple = CUtils.isSimpleType(outparamType);
        writer.write("\n/*\n");
        writer.write(
            " * This method wrap the service method " + methodName + "\n");
        writer.write(" */\n");
        //method signature
        String paramTypeName;
        boolean typeisarray = false;
        boolean typeissimple = false;
        Type type;
        if (returntype == null)
        {
            writer.write("void");
        }
        else
            if (returntypeissimple || returntypeisarray)
            {
                writer.write(outparamType);
            }
            else
            {
                writer.write(outparamType + "*");
            }
        writer.write(" " + methodName + "(AXISCHANDLE stub");
        ArrayList paramsB = (ArrayList) params;
        for (int i = 0; i < paramsB.size(); i++)
        {
            paramTypeName =
                WrapperUtils.getClassNameFromParamInfoConsideringArrays(
                    (ParameterInfo) paramsB.get(i),
                    wscontext);
            writer.write(", " + paramTypeName + " Value" + i);
            if ((type =
                wscontext.getTypemap().getType(
                    ((ParameterInfo) paramsB.get(i)).getSchemaName()))
                != null
                && type.isArray())
            {
                aretherearrayparams = true;
            }
        }
        // Multiples parameters so fill the methods prototype
        ArrayList paramsC = (ArrayList) minfo.getOutputParameterTypes();
        if (isAllTreatedAsOutParams)
        {
            for (int i = 0; i < paramsC.size(); i++)
            {
                type =
                    wscontext.getTypemap().getType(
                        ((ParameterInfo) paramsC.get(i)).getSchemaName());
                writer.write(
                    ", AXIS_OUT_PARAM  "
                        + WrapperUtils
                            .getClassNameFromParamInfoConsideringArrays(
                            (ParameterInfo) paramsC.get(i),
                            wscontext)
                        + "* OutValue"
                        + i);
                if ((type =
                    wscontext.getTypemap().getType(
                        ((ParameterInfo) paramsC.get(i)).getSchemaName()))
                    != null
                    && type.isArray())
                {
                    aretherearrayparams = true;
                }
            }
        }
        writer.write(")\n{\n");
        if (aretherearrayparams || returntypeisarray)
        {
            writer.write("\tAxisc_Array array;\n");
        }
        writer.write("\tAXISCHANDLE call = axiscGetCall(stub);\n");
        if (returntype != null)
        {
            writer.write("\t");
            if (returntypeisarray)
            {
                //for arrays
                writer.write(outparamType + " RetArray = {NULL, 0};\n");
            }
            else
                if (!returntypeissimple)
                {
                    writer.write(outparamType + "* pReturn = NULL;\n");
                    //for complex types
                }
                else
                {
                    //for simple types
                    writer.write(outparamType + " Ret;\n");
                    //TODO initialize return parameter appropriately.
                }
        }
        writer.write(
            "\t/* Following will establish the connections with the server too */\n");
        writer.write(
            "\tif (AXISC_SUCCESS != axiscInitializeCall(call, C_DOC_PROVIDER "
                + ")) return ");
        if (returntype != null)
        {
            writer.write(
                (returntypeisarray
                    ? "RetArray"
                    : returntypeissimple
                    ? "Ret"
                    : "pReturn")
                    + ";\n");
        }
        else
        {
            writer.write(";\n");
        }
        writer.write(
            "\taxiscSetTransportPropertyCall(call,AXISC_SOAPACTION_HEADER , \""
                + minfo.getSoapAction()
                + "\");\n");
        writer.write(
            "\taxiscSetSOAPVersionCall(call, SOAP_VER_1_1);\n");
        //TODO check which version is it really.
        writer.write(
            "\taxiscSetOperationCall(call, \""
                + minfo.getInputMessage().getLocalPart()
                + "\", \""
                + minfo.getInputMessage().getNamespaceURI()
                + "\");\n");
        for (int i = 0; i < paramsB.size(); i++)
        {
            ParameterInfo param = (ParameterInfo) paramsB.get(i);
            type = wscontext.getTypemap().getType(param.getSchemaName());
            if (type != null)
            {
                if (type.isSimpleType())
                { //schema defined simpleType possibly with restrictions
                    paramTypeName = CUtils.getclass4qname(type.getBaseType());
                }
                else
                {
                    paramTypeName = type.getLanguageSpecificName();
                }
                typeisarray = type.isArray();
            }
            else
            {
                paramTypeName = param.getLangName();
                typeisarray = false;
            }
            typeissimple = CUtils.isSimpleType(paramTypeName);
            if (typeisarray)
            {
                //arrays
                QName qname = WrapperUtils.getArrayType(type).getName();
                String containedType = null;
                if (CUtils.isSimpleType(qname))
                {
                    containedType = CUtils.getclass4qname(qname);
                    writer.write(
                        "\taxiscAddBasicArrayParameterCall(call, ");
                    writer.write(
                        "(Axisc_Array*)(&Value"
                            + i
                            + "), "
                            + CUtils.getXSDTypeForBasicType(containedType)
                            + ", \""
                            + param.getElementNameAsString()
                            + "\"");
                }
                else
                {
                    containedType = qname.getLocalPart();
                    writer.write(
                        "\taxiscAddCmplxArrayParameterCall(call, ");
                    writer.write(
                        "(Axisc_Array*)(&Value"
                            + i
                            + "), (void*)Axis_Serialize_"
                            + containedType
                            + ", (void*)Axis_Delete_"
                            + containedType
                            + ", (void*) Axis_GetSize_"
                            + containedType
                            + ", \""
                            + param.getElementNameAsString()
                            + "\", Axis_URI_"
                            + containedType);
                }
            }
            else
                if (typeissimple)
                {
                    //for simple types	
                    writer.write(
                        "\taxiscAddParameterCall(call, ");
                    writer.write(
                        "(void*)&Value"
                            + i
                            + ", \""
                            + param.getElementNameAsString()
                            + "\", "
                            + CUtils.getXSDTypeForBasicType(paramTypeName));
                }
                else
                    if (param.isAnyType())
                    {
                        //for anyTtype 
                        writer.write(
                            "\taxiscAddAnyObjectCall(call, Value"
                                + i);
                    }
                    else
                    {
                        //for complex types 
                        writer.write(
                            "\taxiscAddCmplxParameterCall(call, ");
                        writer.write(
                            "Value"
                                + i
                                + ", (void*)Axis_Serialize_"
                                + paramTypeName
                                + ", (void*)Axis_Delete_"
                                + paramTypeName
                                + ", \""
                                + param.getElementNameAsString()
                                + "\", Axis_URI_"
                                + paramTypeName);
                    }
            writer.write(");\n");
        }
        writer.write(
            "\tif (AXISC_SUCCESS == axiscInvokeCall(call))\n\t{\n");
        writer.write(
            "\t\tif(AXISC_SUCCESS == axiscCheckMessageCall(call, \""
                + minfo.getOutputMessage().getLocalPart()
                + "\", \""
                + minfo.getOutputMessage().getNamespaceURI()
                + "\"))\n\t\t{\n");
        if (isAllTreatedAsOutParams)
        {
            String currentParamName;
            String currentParaType;
            for (int i = 0; i < paramsC.size(); i++)
            {
                ParameterInfo currentType = (ParameterInfo) paramsC.get(i);
                type =
                    wscontext.getTypemap().getType(currentType.getSchemaName());
                if (type != null)
                {
                    if (type.isSimpleType())
                    {
                        currentParaType =
                            CUtils.getclass4qname(type.getBaseType());
                    }
                    else
                    {
                        currentParaType = type.getLanguageSpecificName();
                    }
                    typeisarray = type.isArray();
                }
                else
                {
                    currentParaType =
                        ((ParameterInfo) paramsC.get(i)).getLangName();
                    typeisarray = false;
                }
                typeissimple = CUtils.isSimpleType(currentParaType);

                currentParamName = "*OutValue" + i;
                // Some code need to be merged as we have some duplicated in coding here.
                if (typeisarray)
                {
                    QName qname = WrapperUtils.getArrayType(type).getName();
                    String containedType = null;
                    if (CUtils.isSimpleType(qname))
                    {
                        containedType = CUtils.getclass4qname(qname);
                        writer.write(
                            "\t\t\tarray = axiscGetBasicArrayCall(call, "
                                + CUtils.getXSDTypeForBasicType(containedType)
                                + ", \""
                                + currentType.getElementNameAsString()
                                + "\", 0);\n");
                        writer.write(
                            "\t\t\tmemcpy(OutValue"
                                + i
                                + ", &array, sizeof(Axisc_Array));\n");

                    }
                    else
                    {
                        containedType = qname.getLocalPart();
                        writer.write(
                            "\t\t\tarray = axiscGetCmplxArrayCall(call, (void*) Axis_DeSerialize_"
                                + containedType);
                        writer.write(
                            ", (void*) Axis_Create_"
                                + containedType
                                + ", (void*) Axis_Delete_"
                                + containedType
                                + ", (void*) Axis_GetSize_"
                                + containedType
                                + ", \""
                                + currentType.getElementNameAsString()
                                + "\", Axis_URI_"
                                + containedType
                                + ");\n");
                        writer.write(
                            "\t\t\tmemcpy(OutValue"
                                + i
                                + ", &array, sizeof(Axisc_Array));\n");
                    }
                }
                else
                    if (typeissimple)
                    {
                        writer.write(
                            "\t\t\t"
                                + currentParamName
                                + " = "
                                + CUtils.getParameterGetValueMethodName(
                                    currentParaType,
                                    false)
                                + "(call, \""
                                + currentType.getElementNameAsString()
                                + "\", 0);\n");
                    }
                    else
                        if (currentType.isAnyType())
                        {
                            //for anyTtype 
                            writer.write(
                                "\t\t\t"
                                    + currentParamName
                                    + " = ("
                                    + currentParaType
                                    + "*)axiscGetAnyObjectCall(call);\n");
                        }
                        else
                        {
                            writer.write(
                                "\t\t\t"
                                    + currentParamName
                                    + " = ("
                                    + currentParaType
                                    + "*)axiscGetCmplxObjectCall(call, (void*) Axis_DeSerialize_"
                                    + currentParaType
                                    + ", (void*) Axis_Create_"
                                    + currentParaType
                                    + ", (void*) Axis_Delete_"
                                    + currentParaType
                                    + ",\""
                                    + currentType.getElementNameAsString()
                                    + "\", 0);\n");
                        }
            }
            writer.write("\t\t}\n");
            writer.write(
                "\t}\n\taxiscUnInitializeCall(call);\n");
        }
        else
            if (returntype == null)
            {
                writer.write("\t\t\t/*not successful*/\n\t\t}\n");
                writer.write(
                    "\t}\n\taxiscUnInitializeCall(call);\n");
            }
            else
                if (returntypeisarray)
                {
                    QName qname = WrapperUtils.getArrayType(retType).getName();
                    String containedType = null;
                    if (CUtils.isSimpleType(qname))
                    {
                        containedType = CUtils.getclass4qname(qname);
                        writer.write(
                            "\tarray = axiscGetBasicArrayCall(call, "
                                + CUtils.getXSDTypeForBasicType(containedType)
                                + ", \""
                                + returntype.getElementNameAsString()
                                + "\", 0);\n");
                        writer.write(
                            "\tmemcpy(&RetArray, &array, sizeof(Axisc_Array));\n");
                    }
                    else
                    {
                        containedType = qname.getLocalPart();
                        writer.write(
                            "\tarray = axiscGetCmplxArrayCall(call, (void*) Axis_DeSerialize_"
                                + containedType);
                        writer.write(
                            ", (void*) Axis_Create_"
                                + containedType
                                + ", (void*) Axis_Delete_"
                                + containedType
                                + ", (void*) Axis_GetSize_"
                                + containedType
                                + ", \""
                                + returntype.getElementNameAsString()
                                + "\", Axis_URI_"
                                + containedType
                                + ");\n");
                        writer.write(
                            "\tmemcpy(&RetArray, &array, sizeof(Axisc_Array));\n");
                    }
                    writer.write("\t\t}\n");
                    writer.write(
                        "\t}\n\taxiscUnInitializeCall(call);\n");
                    writer.write("\treturn RetArray;\n");
                }
                else
                    if (returntypeissimple)
                    {
                        writer.write(
                            "\t\t\tRet = "
                                + CUtils.getParameterGetValueMethodName(
                                    outparamType,
                                    false)
                                + "(call, \""
                                + returntype.getElementNameAsString()
                                + "\", 0);\n");
                        writer.write("\t\t}\n");
                        writer.write(
                            "\t}\n\taxiscUnInitializeCall(call);\n");
                        writer.write("\treturn Ret;\n");
                    }
                    else
                        if (returntype.isAnyType())
                        {
                            //for anyTtype 
                            writer.write(
                                "\t\t\tpReturn = ("
                                    + outparamType
                                    + "*)axiscGetAnyObjectCall(call);\n\t\t}\n");
                            writer.write(
                                "\t}\n\taxiscUnInitialize(call);\n");
                            writer.write("\treturn pReturn;\n");
                        }
                        else
                        {
                            writer.write(
                                "\t\t\tpReturn = ("
                                    + outparamType
                                    + "*)axiscGetCmplxObjectCall(call, (void*) Axis_DeSerialize_"
                                    + outparamType
                                    + ", (void*) Axis_Create_"
                                    + outparamType
                                    + ", (void*) Axis_Delete_"
                                    + outparamType
                                    + ",\""
                                    + returntype.getElementNameAsString()
                                    + "\", 0);\n");
                            writer.write("\t\t}\n");
                            writer.write(
                                "\t}\n\taxiscUnInitializeCall(call);\n");
                            writer.write("\treturn pReturn;\n");
                        }

        //write end of method
        writer.write("}\n");
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.c.CFileWriter#writeGlobalCodes()
     */
    protected void writeGlobalCodes() throws WrapperFault
    {
        Iterator types = wscontext.getTypemap().getTypes().iterator();
        HashSet typeSet = new HashSet();
        String typeName;
        Type type;
        try
        {
            while (types.hasNext())
            {
                type = (Type) types.next();
                if (type.isSimpleType())
                    continue;
                if (type.isArray())
                    continue;
                typeName = type.getLanguageSpecificName();
                if (typeName.startsWith(">"))
                    continue;
                typeSet.add(typeName);
            }
            Iterator itr = typeSet.iterator();
            while (itr.hasNext())
            {
                typeName = itr.next().toString();
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
                        + " *Obj, bool bArray, int nSize);\n");
                writer.write(
                    "extern void Axis_Delete_"
                        + typeName
                        + "("
                        + typeName
                        + "* param, bool bArray, int nSize);\n");
                writer.write(
                    "extern int Axis_Serialize_"
                        + typeName
                        + "("
                        + typeName
                        + "* param, AXISCHANDLE pSZ, bool bArray);\n");
                writer.write("extern int Axis_GetSize_" + typeName + "();\n\n");
            }
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
