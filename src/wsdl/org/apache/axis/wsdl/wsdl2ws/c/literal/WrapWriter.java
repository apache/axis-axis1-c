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
 * @author Srinath Perera(hemapani@openource.lk)
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
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class WrapWriter extends org.apache.axis.wsdl.wsdl2ws.c.WrapWriter
{
    /**
     * @param wscontext
     * @throws WrapperFault
     */
    public WrapWriter(WebServiceContext wscontext) throws WrapperFault
    {
        super(wscontext);
        this.bindingStyle = "DOC_LITERAL";
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#writePreprocessorStatements()
     */
    protected void writePreprocessorStatements() throws WrapperFault
    {
        try
        {
            writer.write(
                "#include \"" + classname + CUtils.C_HEADER_SUFFIX + "\"\n");
            //As there is no service header file for C the header files for types should be included here itself
            Type atype;
            Iterator types = this.wscontext.getTypemap().getTypes().iterator();
            while (types.hasNext())
            {
                atype = (Type) types.next();
                if (atype.getLanguageSpecificName().startsWith(">"))
                    continue;
                writer.write(
                    "#include \""
                        + atype.getLanguageSpecificName()
                        + CUtils.C_HEADER_SUFFIX
                        + "\"\n");
            }
            writer.write("\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /**
     * This method genarate methods that wraps the each method of the service
     * @param methodName
     * @param params
     * @param outparam
     * @throws IOException
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
        String methodName = minfo.getMethodname();
        Collection params = minfo.getInputParameterTypes();
        Type retType = null;
        String outparamType = null;
        boolean returntypeissimple = false;
        boolean returntypeisarray = false;
        if (returntype != null)
        {
            retType =
                wscontext.getTypemap().getType(returntype.getSchemaName());
            if (retType != null)
            {
                if (retType.isSimpleType())
                { //schema defined simpleType possibly with restrictions
                    returntypeissimple = true;
                    outparamType = CUtils.getclass4qname(retType.getBaseType());
                }
                else
                {
                    outparamType = retType.getLanguageSpecificName();
                    returntypeisarray = retType.isArray();
                    returntypeissimple = CUtils.isSimpleType(outparamType);
                }
            }
            else
            {
                outparamType = returntype.getLangName();
                returntypeissimple = CUtils.isSimpleType(outparamType);
            }
        }
        String paraTypeName;
        ArrayList paramsB = new ArrayList(params);
        Type type;

        writer.write(
            "\n/*forward declaration for the c method " + methodName + " */\n");
        //TODO forward declaration writing logic should be changed when arrays come into picture
        if (returntype == null)
        {
            writer.write("extern void " + methodName + "(");
        }
        else
        {
            writer.write(
                "extern "
                    + outparamType
                    + ((returntypeissimple || returntypeisarray) ? " " : "* ")
                    + methodName
                    + "(");
        }

        for (int i = 0; i < paramsB.size(); i++)
        {
            if (i > 0)
                writer.write(",");
            type =
                this.wscontext.getTypemap().getType(
                    ((ParameterInfo) paramsB.get(i)).getSchemaName());
            paraTypeName = ((ParameterInfo) paramsB.get(i)).getLangName();
            if ((CUtils.isSimpleType(paraTypeName))
                || (type != null && type.isSimpleType()))
            {
                //for simple types	
                writer.write(paraTypeName);
            }
            else
                if (type != null && type.isArray())
                {
                    writer.write(paraTypeName);
                }
                else
                {
                    writer.write(paraTypeName + "*");
                }
        }
        if (isAllTreatedAsOutParams)
        {
            ArrayList paramsC = (ArrayList) minfo.getOutputParameterTypes();
            for (int i = 0; i < paramsC.size(); i++)
            {
                type =
                    wscontext.getTypemap().getType(
                        ((ParameterInfo) paramsC.get(i)).getSchemaName());
                writer.write(
                    ", AXIS_OUT_PARAM "
                        + WrapperUtils
                            .getClassNameFromParamInfoConsideringArrays(
                            (ParameterInfo) paramsC.get(i),
                            wscontext)
                        + "*");
            }
        }
        writer.write(");\n");
        writer.write("\n/*\n");
        writer.write(" * This method wrap the service method \n");
        writer.write(" */\n");
        //method signature
        writer.write(
            "int "
                + methodName
                + CUtils.WRAPPER_METHOD_APPENDER
                + "(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)\n{\n");
        writer.write("\tint nStatus;\n");
        boolean aretherearrayparams = false;
        String elementName;
        String returnParamName;
        for (int i = 0; i < paramsB.size(); i++)
        {
            ParameterInfo param = (ParameterInfo) paramsB.get(i);
            type = this.wscontext.getTypemap().getType(param.getSchemaName());
            paraTypeName = param.getLangName();
            if ((CUtils.isSimpleType(paraTypeName))
                || (type != null && type.isSimpleType()))
            {
                //for simple types	
                writer.write("\t" + paraTypeName + " v" + i + ";\n");
            }
            else
                if (type != null && type.isArray())
                {
                    //for arrays
                    aretherearrayparams = true;
                    writer.write("\t" + paraTypeName + " v" + i + ";\n");
                }
                else
                {
                    //for complex types
                    writer.write("\t" + paraTypeName + "* v" + i + ";\n");
                }
        }
        if (returntype != null)
        {
            writer.write(
                "\t"
                    + outparamType
                    + ((returntypeisarray || returntypeissimple) ? " " : "* ")
                    + "ret;\n");
        }
        if (aretherearrayparams)
        {
            writer.write("\tAxis_Array array;\n");
        }
        // Multiples parameters so fill the methods prototype
        if (isAllTreatedAsOutParams)
        {
            ArrayList paramsC = (ArrayList) minfo.getOutputParameterTypes();
            for (int i = 0; i < paramsC.size(); i++)
            {
                type =
                    wscontext.getTypemap().getType(
                        ((ParameterInfo) paramsC.get(i)).getSchemaName());
                writer.write(
                    "\t"
                        + WrapperUtils
                            .getClassNameFromParamInfoConsideringArrays(
                            (ParameterInfo) paramsC.get(i),
                            wscontext)
                        + " out"
                        + i
                        + ";\n");
            }
        }
        writer.write(
            "\tif (AXIS_SUCCESS != DZ._functions->checkMessageBody(DZ._object, \""
                + minfo.getInputMessage().getLocalPart()
                + "\", \""
                + minfo.getInputMessage().getNamespaceURI()
                + "\")) return AXIS_FAIL;\n");
        writer.write(
            "\tSZ._functions->createSoapMethod(SZ._object, \""
                + minfo.getOutputMessage().getLocalPart()
                + "\", \""
                + minfo.getOutputMessage().getNamespaceURI()
                + "\");\n");
        //create and populate variables for each parameter
        for (int i = 0; i < paramsB.size(); i++)
        {
            ParameterInfo param = (ParameterInfo) paramsB.get(i);
            type = this.wscontext.getTypemap().getType(param.getSchemaName());
            if (type != null && type.isSimpleType())
            { //schema defined simpleType possibly with restrictions
                paraTypeName = CUtils.getclass4qname(type.getBaseType());
                ;
            }
            else
            {
                paraTypeName = param.getLangName();
            }
            elementName = param.getElementName().getLocalPart();
            if (type != null && type.isSimpleType())
            { //schema defined simpleType possibly with restrictions
                writer.write(
                    "\tv"
                        + i
                        + " = DZ._functions->"
                        + CUtils.getParameterGetValueMethodName(
                            paraTypeName,
                            false)
                        + "(DZ._object,\""
                        + elementName
                        + "\", 0);\n");
            }
            else
                if ((CUtils.isSimpleType(param.getLangName())))
                {
                    //for simple types	
                    writer.write(
                        "\tv"
                            + i
                            + " = DZ._functions->"
                            + CUtils.getParameterGetValueMethodName(
                                paraTypeName,
                                false)
                            + "(DZ._object,\""
                            + elementName
                            + "\", 0);\n");
                }
                else
                    if (type != null && type.isArray())
                    {
                        QName qname = WrapperUtils.getArrayType(type).getName();
                        String containedType = null;
                        if (CUtils.isSimpleType(qname))
                        {
                            containedType = CUtils.getclass4qname(qname);
                            writer.write(
                                "\tarray = DZ._functions->getBasicArray(DZ._object, "
                                    + CUtils.getXSDTypeForBasicType(
                                        containedType)
                                    + ", \""
                                    + elementName
                                    + "\", 0);\n");
                            writer.write(
                                "\tmemcpy(&v"
                                    + i
                                    + ", &array, sizeof(Axis_Array));\n");
                        }
                        else
                        {
                            containedType = qname.getLocalPart();
                            writer.write(
                                "\tarray = DZ._functions->getCmplxArray(DZ._object, (void*)Axis_DeSerialize_"
                                    + containedType
                                    + "\n\t\t, (void*)Axis_Create_"
                                    + containedType
                                    + ", (void*)Axis_Delete_"
                                    + containedType
                                    + "\n\t\t, (void*)Axis_GetSize_"
                                    + containedType
                                    + ", \""
                                    + elementName
                                    + "\", Axis_URI_"
                                    + containedType
                                    + ");\n");
                            writer.write(
                                "\tmemcpy(&v"
                                    + i
                                    + ", &array, sizeof(Axis_Array));\n");
                        }
                    }
                    else
                        if (param.isAnyType())
                        {
                            //for anyType
                            writer.write(
                                "\tv"
                                    + i
                                    + " = ("
                                    + paraTypeName
                                    + "*)DZ._functions->getAnyObject(DZ._object);\n");
                        }
                        else
                        {
                            //for complex types 
                            writer.write(
                                "\tv"
                                    + i
                                    + " = ("
                                    + paraTypeName
                                    + "*)DZ._functions->getCmplxObject(DZ._object, (void*)Axis_DeSerialize_"
                                    + paraTypeName
                                    + "\n\t\t, (void*)Axis_Create_"
                                    + paraTypeName
                                    + ", (void*)Axis_Delete_"
                                    + paraTypeName
                                    + "\n\t\t,\""
                                    + elementName
                                    + "\", Axis_URI_"
                                    + paraTypeName
                                    + ");\n");
                        }
        }
        writer.write(
            "\tif (AXIS_SUCCESS != (nStatus = DZ._functions->getStatus(DZ._object))) return nStatus;\n");
        if (returntype != null)
        {
            returnParamName = returntype.getElementName().getLocalPart();
            /* Invoke the service when return type not void */
            writer.write("\tret = " + methodName + "(");
            if (0 < paramsB.size())
            {
                for (int i = 0; i < paramsB.size() - 1; i++)
                {
                    writer.write("v" + i + ",");
                }
                writer.write("v" + (paramsB.size() - 1));
            }
            writer.write(");\n");
            /* set the result */
            if (returntypeissimple)
            {
                writer.write(
                    "\treturn SZ._functions->addOutputParam(SZ._object, \""
                        + returnParamName
                        + "\", (void*)&ret, "
                        + CUtils.getXSDTypeForBasicType(outparamType)
                        + ");\n");
            }
            else
                if (returntypeisarray)
                {
                    Type arrayType = WrapperUtils.getArrayType(retType);
                    QName qname = arrayType.getName();
                    String containedType = null;
                    if (CUtils.isSimpleType(qname))
                    {
                        containedType = CUtils.getclass4qname(qname);
                        writer.write(
                            "\treturn SZ._functions->addOutputBasicArrayParam(SZ._object, (Axis_Array*)(&ret),"
                                + CUtils.getXSDTypeForBasicType(containedType)
                                + ", \""
                                + returnParamName
                                + "\");\n");
                    }
                    else
                        if (arrayType.isSimpleType())
                        { //SimpleType in the schema 
                            containedType =
                                CUtils.getclass4qname(arrayType.getBaseType());
                            writer.write(
                                "\treturn SZ._functions->addOutputBasicArrayParam(SZ._object, (Axis_Array*)(&ret),"
                                    + CUtils.getXSDTypeForBasicType(
                                        containedType)
                                    + ", \""
                                    + returnParamName
                                    + "\");\n");
                        }
                        else
                        {
                            containedType = qname.getLocalPart();
                            writer.write(
                                "\treturn SZ._functions->addOutputCmplxArrayParam(SZ._object, (Axis_Array*)(&ret), (void*) Axis_Serialize_"
                                    + containedType
                                    + ", (void*) Axis_Delete_"
                                    + containedType
                                    + ", (void*) Axis_GetSize_"
                                    + containedType
                                    + ", \""
                                    + returnParamName
                                    + "\", Axis_URI_"
                                    + containedType
                                    + ");\n");
                        }
                }
                else
                    if (returntype.isAnyType())
                    {
                        writer.write(
                            "\treturn SZ._functions->addOutputAnyObject(SZ._object, ret);\n");
                    }
                    else
                    {
                        //complex type
                        writer.write(
                            "\treturn SZ._functions->addOutputCmplxParam(SZ._object, ret, (void*)Axis_Serialize_"
                                + outparamType
                                + ", (void*)Axis_Delete_"
                                + outparamType
                                + ", \""
                                + returnParamName
                                + "\", Axis_URI_"
                                + outparamType
                                + ");\n");
                    }
        }
        else
            if (isAllTreatedAsOutParams)
            {
                writer.write("\t" + methodName + "(");
                if (0 < paramsB.size())
                {
                    for (int i = 0; i < paramsB.size(); i++)
                    {
                        writer.write("v" + i + ",");
                    }
                }
                ArrayList paramsC = (ArrayList) minfo.getOutputParameterTypes();
                for (int i = 0; i < paramsC.size() - 1; i++)
                {
                    writer.write("&out" + i + ",");
                }
                writer.write("&out" + (paramsC.size() - 1));
                writer.write(");\n");
                paramsC = (ArrayList) minfo.getOutputParameterTypes();
                for (int i = 0; i < paramsC.size(); i++)
                {
                    ParameterInfo param = (ParameterInfo) paramsC.get(i);
                    retType =
                        wscontext.getTypemap().getType(param.getSchemaName());
                    if (retType != null)
                    {
                        if (retType.isSimpleType())
                        {
                            returntypeissimple = true;
                            outparamType =
                                CUtils.getclass4qname(retType.getBaseType());
                        }
                        else
                        {
                            outparamType = retType.getLanguageSpecificName();
                            returntypeisarray = retType.isArray();
                            returntypeissimple =
                                CUtils.isSimpleType(outparamType);
                        }
                    }
                    else
                    {
                        outparamType = param.getLangName();
                        returntypeissimple = CUtils.isSimpleType(outparamType);
                    }
                    returnParamName = param.getElementName().getLocalPart();
                    if (returntypeissimple)
                    {
                        writer.write(
                            "\tSZ._functions->addOutputParam(SZ._object, \""
                                + returnParamName
                                + "\", (void*)&out"
                                + i
                                + ", "
                                + CUtils.getXSDTypeForBasicType(outparamType)
                                + ");\n");
                    }
                    else
                        if (returntypeisarray)
                        {
                            QName qname =
                                WrapperUtils.getArrayType(retType).getName();
                            String containedType = null;
                            if (CUtils.isSimpleType(qname))
                            {
                                containedType = CUtils.getclass4qname(qname);
                                writer.write(
                                    "\tSZ._functions->addOutputBasicArrayParam(SZ._object, (Axis_Array*)(&out"
                                        + i
                                        + "), "
                                        + CUtils.getXSDTypeForBasicType(
                                            containedType)
                                        + ", \""
                                        + returnParamName
                                        + "\");\n");
                            }
                            else
                            {
                                containedType = qname.getLocalPart();
                                writer.write(
                                    "\tSZ._functions->addOutputCmplxArrayParam(SZ._object, (Axis_Array*)(&out"
                                        + i
                                        + "),"
                                        + "(void*) Axis_Serialize_"
                                        + containedType
                                        + ", (void*) Axis_Delete_"
                                        + containedType
                                        + ", (void*) Axis_GetSize_"
                                        + containedType
                                        + ", \""
                                        + returnParamName
                                        + "\", Axis_URI_"
                                        + containedType
                                        + ");\n");
                            }
                        }
                        else
                            if (param.isAnyType())
                            {
                                //anyType
                                writer.write(
                                    "\tSZ._functions->addOutputAnyObject(SZ._object, out"
                                        + i
                                        + ");\n");
                            }
                            else
                            {
                                //complex type
                                writer.write(
                                    "\tSZ._functions->addOutputCmplxParam(SZ._object, out"
                                        + i
                                        + ", (void*)Axis_Serialize_"
                                        + outparamType
                                        + ", (void*)Axis_Delete_"
                                        + outparamType
                                        + ", \""
                                        + returnParamName
                                        + "\", Axis_URI_"
                                        + outparamType
                                        + ");\n");
                            }
                }
                writer.write("\treturn AXIS_SUCCESS;\n");
            }
            else
            { //method does not return anything
                /* Invoke the service when return type is void */
                writer.write("\t" + methodName + "(");
                if (0 < paramsB.size())
                {
                    for (int i = 0; i < paramsB.size() - 1; i++)
                    {
                        writer.write("v" + i + ",");
                    }
                    writer.write("v" + (paramsB.size() - 1));
                }
                writer.write(");\n");
                writer.write("\treturn AXIS_SUCCESS;\n");
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
                        + "* param, IWrapperSoapDeSerializer* pDZ);\n");
                writer.write(
                    "extern void* Axis_Create_"
                        + typeName
                        + "("
                        + typeName
                        + "* Obj, bool bArray, int nSize);\n");
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
                        + "* param, IWrapperSoapSerializer* pSZ, bool bArray);\n");
                writer.write("extern int Axis_GetSize_" + typeName + "();\n\n");
            }
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
