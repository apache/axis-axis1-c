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
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

/*
 * Revision 1.1  2004/05/26 samisa
 * Added Stub base class into code generation
 */

package org.apache.axis.wsdl.wsdl2ws.cpp.literal;

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
import org.apache.axis.wsdl.wsdl2ws.info.FaultInfo;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ClientStubWriter
    extends org.apache.axis.wsdl.wsdl2ws.cpp.ClientStubWriter
{
    public ClientStubWriter(WebServiceContext wscontext) throws WrapperFault
    {
        super(wscontext);
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeConstructors()
     */
    protected void writeConstructors() throws WrapperFault
    {
        try
        {
            writer.write(
                classname
                    + "::"
                    + classname
                    + "(const char* pcEndpointUri, AXIS_PROTOCOL_TYPE eProtocol):Stub(pcEndpointUri, eProtocol)\n{\n");
            writer.write("}\n\n");
            writer.write(
                classname
                    + "::"
                    + classname
                    + "()\n:Stub(\" \", APTHTTP1_1)\n{\n");
            //TODO get TransportURI from WrapInfo and check what the transport is and do the following line accordingly
            writer.write(
                "\tm_pCall->setEndpointURI(\""
                    + wscontext.getWrapInfo().getTargetEndpointURI()
                    + "\");\n");
            writer.write("}\n\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
     */
    protected void writeMethods() throws WrapperFault
    {
        try
        {
            writer.write(
                "\n/*Methods corresponding to the web service methods*/\n");
            MethodInfo minfo;
            for (int i = 0; i < methods.size(); i++)
            {
                minfo = (MethodInfo) methods.get(i);
                this.writeMethodInWrapper(minfo);
                writer.write("\n");
            }

            writer.write("/*Methods for supporting SecureChannel*/\n\n");
            // FJP - SecureChannel
            writer.write(
                "void "
                    + classname
                    + "::SetSecure( char * pszArguments, ...)\n");
            // FJP - SecureChannel
            writer.write("{\n"); // FJP - SecureChannel
            writer.write("\tchar **\tppszArgPtr = &pszArguments;\n");
            // FJP - SecureChannel
            writer.write("\tint\t\tiArgIndex = 0;\n\n"); // FJP - SecureChannel
            writer.write("\twhile( *ppszArgPtr != NULL)\n");
            // FJP - SecureChannel
            writer.write("\t{\n"); // FJP - SecureChannel
            writer.write("\t\tsArguments[iArgIndex] = *ppszArgPtr;\n\n");
            // FJP - SecureChannel
            writer.write("\t\tiArgIndex++;\n"); // FJP - SecureChannel
            writer.write("\t\tppszArgPtr++;\n"); // FJP - SecureChannel
            writer.write("\t}\n"); // FJP - SecureChannel
            writer.write("}\n\n"); // FJP - SecureChannel
            writer.write("void " + classname + "::includeSecure()\n");
            // FJP - SecureChannel
            writer.write("{\n"); // FJP - SecureChannel
            writer.write(
                "\tm_pCall->setTransportProperty( SECURE_PROPERTIES, (const char *) &sArguments);\n");
            // FJP - SecureChannel
            writer.write("}\n"); // FJP - SecureChannel
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writePreprocssorStatements()
     */
    protected void writePreprocessorStatements() throws WrapperFault
    {
        try
        {
            if ("AxisClientException".equals(classname))
            {
                writer.write(
                    "#include \""
                        + getServiceName()
                        + "_"
                        + classname
                        + CUtils.CPP_HEADER_SUFFIX
                        + "\"\n\n");
            }
            else
            {
                writer.write(
                    "#include \""
                        + classname
                        + CUtils.CPP_HEADER_SUFFIX
                        + "\"\n\n");
            }
            writer.write("#include <axis/AxisWrapperAPI.hpp>\n\n");
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
        {

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
        }
        Collection params = minfo.getInputParameterTypes();
        String methodName = minfo.getMethodname();
        Type retType = null;
        boolean returntypeissimple = false;
        boolean returntypeisarray = false;
        String outparamType = null;
        if (returntype != null)
        {
            retType =
                wscontext.getTypemap().getType(returntype.getSchemaName());
        }
        if (retType != null)
        {
            if (retType.isSimpleType())
            {
                outparamType = CUtils.getclass4qname(retType.getBaseType());
            }
            else
            {
                outparamType = retType.getLanguageSpecificName();
            }
            returntypeisarray = retType.isArray();
        }
        else
        {

            if (returntype != null)
            {
                outparamType = returntype.getLangName();
            }
        }
        if (returntype != null)
        {
            returntypeissimple = CUtils.isSimpleType(outparamType);
        }
        writer.write("\n/*\n");
        writer.write(
            " * This method wrap the service method" + methodName + "\n");
        writer.write(" */\n");
        //method signature
        String paraTypeName;
        boolean typeisarray = false;
        boolean typeissimple = false;
        Type type;
        if (returntype == null)
        {
            writer.write("void");
        }
        else
        {
            if (returntypeissimple || returntypeisarray)
            {
                writer.write(outparamType);
            }
            else
            { //for AnyType too
                writer.write(outparamType + "*");
            }
        }
        writer.write(" " + classname + "::" + methodName + "(");
        ArrayList paramsB = (ArrayList) params;
        if (0 < paramsB.size())
        {
            type =
                wscontext.getTypemap().getType(
                    ((ParameterInfo) paramsB.get(0)).getSchemaName());
            if (type != null)
            {
                if (type.isSimpleType())
                { //schema defined simpleType
                    paraTypeName = CUtils.getclass4qname(type.getBaseType());
                }
                else
                {
                    paraTypeName = type.getLanguageSpecificName();
                }
                typeisarray = type.isArray();
            }
            else
            {
                paraTypeName = ((ParameterInfo) paramsB.get(0)).getLangName();
                typeisarray = false;
            }
            typeissimple = CUtils.isSimpleType(paraTypeName);
            if (typeisarray || typeissimple)
            {
                writer.write(paraTypeName + " Value0");
            }
            else
            { //for AnyType too
                writer.write(paraTypeName + "* Value0");
            }
            for (int i = 1; i < paramsB.size(); i++)
            {
                type =
                    wscontext.getTypemap().getType(
                        ((ParameterInfo) paramsB.get(i)).getSchemaName());
                if (type != null)
                {
                    if (type.isSimpleType())
                    { //schema defined simpleType
                        paraTypeName =
                            CUtils.getclass4qname(type.getBaseType());
                    }
                    else
                    {
                        paraTypeName = type.getLanguageSpecificName();
                    }
                    typeisarray = type.isArray();
                }
                else
                {
                    paraTypeName =
                        ((ParameterInfo) paramsB.get(i)).getLangName();
                    typeisarray = false;
                }
                typeissimple = CUtils.isSimpleType(paraTypeName);
                if (typeisarray || typeissimple)
                {
                    writer.write(", " + paraTypeName + " Value" + i);
                }
                else
                { //for AnyType too
                    writer.write(", " + paraTypeName + "* Value" + i);
                }
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
            }
        }

        writer.write(")\n{\n");
        if (returntype != null)
        {
            writer.write("\t");
            if (returntypeisarray)
            {
                //for arrays
                writer.write(outparamType + " RetArray = {NULL, 0};\n");
            }
            else
            {

                if (!returntypeissimple)
                { //for AnyType too
                    writer.write(outparamType + "* pReturn = NULL;\n");
                    //for complex types
                }
                else
                {
                    //for simple types
                    String initValue = CUtils.getInitValue(outparamType);
                    if (initValue != null)
                    {
                        writer.write(
                            outparamType + " Ret = " + initValue + ";\n");
                    }
                    else
                    {

                        if (outparamType.equals("xsd__base64Binary")
                            || outparamType.equals("xsd__hexBinary"))
                        {
                            writer.write(outparamType + " Ret;\n");
                            writer.write("\tRet.__ptr = NULL;\n");
                            writer.write("\tRet.__size = 0;\n");
                        }
                        else
                        {
                            writer.write(outparamType + " Ret;\n");
                        }
                    }
                }
                //TODO initialize return parameter appropriately.
            }
        }
        String channelSecurityType =
            (WrapperConstants
                .CHANNEL_SECURITY_SSL
                .equals(wscontext.getWrapInfo().getChannelSecurity()))
                ? "SSL_CHANNEL"
                : "NORMAL_CHANNEL";
        writer.write("\tconst char* pcCmplxFaultName;\n");
        writer.write("\ttry\n\t{");

        writer.write(
            "\tif (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER, "
                + channelSecurityType
                + ")) return ");
        if (returntype != null)
        {
            writer.write(
                (returntypeisarray
                    ? "RetArray"
                    : returntypeissimple
                    ? "Ret"
                    : "pReturn")
                    + ";\n\t");
        }
        else
        {
            writer.write(";\n");
        }
        writer.write(
            "\tm_pCall->setTransportProperty(SOAPACTION_HEADER , \""
                + minfo.getSoapAction()
                + "\");\n");
        writer.write("\tm_pCall->setSOAPVersion(SOAP_VER_1_1);\n");
        //TODO check which version is it really.
        writer.write(
            "\tm_pCall->setOperation(\""
                + minfo.getInputMessage().getLocalPart()
                + "\", \""
                + minfo.getInputMessage().getNamespaceURI()
                + "\");\n");

        // Add attributes to soap method
        for (int i = 0; i < paramsB.size(); i++)
        {
            ParameterInfo param = (ParameterInfo) paramsB.get(i);
            if (param.isAttribute())
            {
                String elementType = param.getElementName().getLocalPart();

                if ("string".equals(elementType))
                {
                    writer.write(
                        "\tsetSOAPMethodAttribute(\""
                            + param.getParamName()
                            + "\", \"\", Value"
                            + i
                            + ");\n");
                }
                else
                {
                    if ("int".equals(elementType))
                    {
                        writer.write("\t{\n");
                        writer.write("\t\tchar buffer[20];\n");
                        writer.write(
                            "\t\tsprintf(buffer,\"%d\", Value" + i + ");\n");
                        writer.write(
                            "\t\tsetSOAPMethodAttribute(\""
                                + param.getParamName()
                                + "\", \"\", buffer);\n");
                        writer.write("\t}\n");
                    }
                }
            }
        }

        //new calls from stub base
        writer.write("\tincludeSecure();\n"); // FJP - SecureChannel
        writer.write("\tapplyUserPreferences();\n");

        for (int i = 0; i < paramsB.size(); i++)
        {
            ParameterInfo param = (ParameterInfo) paramsB.get(i);

            // Ignore attributes, while adding elements
            if (!param.isAttribute())
            {
                type = wscontext.getTypemap().getType(param.getSchemaName());
                if (type != null)
                {
                    if (type.isSimpleType())
                    { //schema defined simpleType possibly with restrictions
                        paraTypeName =
                            CUtils.getclass4qname(type.getBaseType());
                    }
                    else
                    {
                        paraTypeName = type.getLanguageSpecificName();
                    }
                    typeisarray = type.isArray();
                }
                else
                {
                    paraTypeName =
                        ((ParameterInfo) paramsB.get(i)).getLangName();
                    typeisarray = false;
                }

                if (param.isAnyType())
                {
                    //for anyType
                    writer.write("\tm_pCall->addAnyObject(Value" + i);
                }
                else
                {
                    //String parameterName = ((ParameterInfo)paramsB.get(i)).getElementName().getLocalPart();
                    //Samisa 22/08/2004
                    String parameterName =
                        ((ParameterInfo) paramsB.get(i))
                            .getElementNameAsString();
                    //Samisa
                    String namespace =
                        ((ParameterInfo) paramsB.get(i))
                            .getElementName()
                            .getNamespaceURI();
                    // If namespace is empty then getNamespacePrefix will create a new prefix
                    // with no namespace which causes the server to send a fault message.
                    // If no namespace for current tag, then use WSDL default namespace
                    if (namespace.length() == 0)
                    {
                        namespace = minfo.getInputMessage().getNamespaceURI();
                    }
                    int stringLength = 8 + 1 + parameterName.length() + 1;

                    writer.write(
                        "\tchar cPrefixAndParamName"
                            + i
                            + "["
                            + stringLength
                            + "];\n");
                    writer.write(
                        "\tsprintf( cPrefixAndParamName"
                            + i
                            + ", \"%s:"
                            + parameterName
                            + "\", getNamespacePrefix(\""
                            + namespace
                            + "\"));\n");

                    if (typeisarray)
                    {
                        // Array
                        Type arrayType = WrapperUtils.getArrayType(type);
                        QName qname = arrayType.getName();
                        if (CUtils.isSimpleType(qname))
                        {
                            // Array of simple type
                            String containedType = CUtils.getclass4qname(qname);
                            writer.write("\tm_pCall->addBasicArrayParameter(");
                            writer.write(
                                "(Axis_Array*)(&Value"
                                    + i
                                    + "), "
                                    + CUtils.getXSDTypeForBasicType(
                                        containedType)
                                    + ", cPrefixAndParamName"
                                    + i);
                        }
                        else
                        {
                            if (arrayType.isSimpleType())
                            {
                                // Simple type in the schema
                                String containedType =
                                    CUtils.getclass4qname(
                                        arrayType.getBaseType());
                                writer.write(
                                    "\tm_pCall->addBasicArrayParameter(");
                                writer.write(
                                    "(Axis_Array*)(&Value"
                                        + i
                                        + "), "
                                        + CUtils.getXSDTypeForBasicType(
                                            containedType)
                                        + ", cPrefixAndParamName"
                                        + i);
                            }
                            else
                            {
                                // Array of complex type
                                String containedType = qname.getLocalPart();
                                writer.write(
                                    "\tm_pCall->addCmplxArrayParameter(");
                                writer.write(
                                    "(Axis_Array*)(&Value"
                                        + i
                                        + "), (void*)Axis_Serialize_"
                                        + containedType
                                        + ", (void*)Axis_Delete_"
                                        + containedType
                                        + ", (void*) Axis_GetSize_"
                                        + containedType
                                        + ", cPrefixAndParamName"
                                        + i
                                        + ", Axis_URI_"
                                        + containedType);
                            }
                        }
                    }
                    else
                    {
                        if (CUtils.isSimpleType(paraTypeName))
                        {
                            // Simple Type
                            writer.write("\tm_pCall->addParameter(");
                            writer.write(
                                "(void*)&Value"
                                    + i
                                    + ", cPrefixAndParamName"
                                    + i
                                    + ", "
                                    + CUtils.getXSDTypeForBasicType(
                                        paraTypeName));
                        }
                        else
                        {
                            // Complex Type
                            writer.write("\tm_pCall->addCmplxParameter(");
                            writer.write(
                                "Value"
                                    + i
                                    + ", (void*)Axis_Serialize_"
                                    + paraTypeName
                                    + ", (void*)Axis_Delete_"
                                    + paraTypeName
                                    + ", cPrefixAndParamName"
                                    + i
                                    + ", Axis_URI_"
                                    + paraTypeName);
                        }
                    }
                }
                // Adrian - end of namespace correction
                writer.write(");\n");
            }
        }
        writer.write("\tif (AXIS_SUCCESS == m_pCall->invoke())\n\t{\n");
        if (minfo.getOutputMessage() != null)
        {
            writer.write(
                "\t\tif(AXIS_SUCCESS == m_pCall->checkMessage(\""
                    + minfo.getOutputMessage().getLocalPart()
                    + "\", \""
                    + minfo.getOutputMessage().getNamespaceURI()
                    + "\"))\n\t\t{\n");
        }
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
                    Type arrayType = WrapperUtils.getArrayType(type);
                    QName qname = arrayType.getName();
                    String containedType = null;
                    if (CUtils.isSimpleType(qname))
                    {
                        containedType = CUtils.getclass4qname(qname);
                        writer.write(
                            "\t\t\t"
                                + currentParamName
                                + " = ("
                                + currentParaType
                                + "&)m_pCall->getBasicArray("
                                + CUtils.getXSDTypeForBasicType(containedType)
                                + ", \""
                                + currentType.getElementName().getLocalPart()
                                + "\", 0);\n");
                    }
                    else
                    {

                        if (arrayType.isSimpleType())
                        { //SimpleType in the schema 
                            containedType =
                                CUtils.getclass4qname(arrayType.getBaseType());
                            writer.write(
                                "\t\t\t"
                                    + currentParamName
                                    + " = ("
                                    + currentParaType
                                    + "&)m_pCall->getBasicArray("
                                    + CUtils.getXSDTypeForBasicType(
                                        containedType)
                                    + ", \""
                                    + currentType.getElementName().getLocalPart()
                                    + "\", 0);\n");
                        }
                        else
                        {
                            containedType = qname.getLocalPart();
                            writer.write(
                                "\t\t\t"
                                    + currentParamName
                                    + " = ("
                                    + currentParaType
                                    + "&)m_pCall->getCmplxArray((void*) Axis_DeSerialize_"
                                    + containedType);
                            //writer.write(", (void*) Axis_Create_"+containedType+", (void*) Axis_Delete_"+containedType+", (void*) Axis_GetSize_"+containedType+", \""+currentType.getElementName().getLocalPart()+"\", Axis_URI_"+containedType+");\n");
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
                        }
                    }
                }
                else
                {

                    if (typeissimple)
                    {
                        writer.write(
                            "\t\t\t"
                                + currentParamName
                                + " = m_pCall->"
                                + CUtils.getParameterGetValueMethodName(
                                    currentParaType,
                                    false)
                                + "(\""
                                + currentType.getParamName()
                                + "\", 0);\n");
                    }
                    else
                    {

                        if (currentType.isAnyType())
                        {
                            //for anyTtype 
                            writer.write(
                                "\t\t\t"
                                    + currentParamName
                                    + " = ("
                                    + currentParaType
                                    + "*)m_pCall->getAnyObject();\n");
                        }
                        else
                        {
                            //writer.write("\t\t\t" + currentParamName + " = ("+currentParaType+"*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_"+currentParaType+", (void*) Axis_Create_"+currentParaType+", (void*) Axis_Delete_"+currentParaType+",\""+currentType.getElementName().getLocalPart()+"\", 0);\n"); 
                            //Samisa 22/08/2004
                            writer.write(
                                "\t\t\t"
                                    + currentParamName
                                    + " = ("
                                    + currentParaType
                                    + "*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_"
                                    + currentParaType
                                    + ", (void*) Axis_Create_"
                                    + currentParaType
                                    + ", (void*) Axis_Delete_"
                                    + currentParaType
                                    + ",\""
                                    + currentType.getElementNameAsString()
                                    + "\", 0);\n");
                            //Samisa
                        }
                    }
                }
            }
            writer.write("\t\t}\n");
            writer.write("\t}\n");
            writer.write("\tupdateStateAfterResponse();\n");
            writer.write("\tm_pCall->unInitialize();\n");
        }
        else
        {
            if (returntype == null)
            {
                if (minfo.getOutputMessage() != null)
                {
                    writer.write("\t\t\t/*not successful*/\n\t\t}\n");
                }
                writer.write("\t}\n");
                writer.write("\tupdateStateAfterResponse();\n");
                writer.write("\tm_pCall->unInitialize();\n");
                //writer.write("\t}\n\tm_pCall->unInitialize();\n");
            }
            else
            {

                if (returntypeisarray)
                {
                    QName qname = WrapperUtils.getArrayType(retType).getName();
                    String containedType = null;
                    if (CUtils.isSimpleType(qname))
                    {
                        containedType = CUtils.getclass4qname(qname);
                        writer.write(
                            "\tRetArray = ("
                                + outparamType
                                + "&)m_pCall->getBasicArray("
                                + CUtils.getXSDTypeForBasicType(containedType)
                                + ", \""
                                + returntype.getElementName().getLocalPart()
                                + "\", 0);\n\t\t}\n");
                    }
                    else
                    {
                        containedType = qname.getLocalPart();
                        writer.write(
                            "\tRetArray = ("
                                + outparamType
                                + "&)m_pCall->getCmplxArray((void*) Axis_DeSerialize_"
                                + containedType);
                        //writer.write(", (void*) Axis_Create_"+containedType+", (void*) Axis_Delete_"+containedType+", (void*) Axis_GetSize_"+containedType+", \""+returntype.getElementName().getLocalPart()+"\", Axis_URI_"+containedType+");\n\t\t}\n");
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
                                + ");\n\t\t}\n");
                    }
                    writer.write("\t}\n");
                    writer.write("\tupdateStateAfterResponse();\n");
                    writer.write("\tm_pCall->unInitialize();\n");
                    //        writer.write("\t}\n\tm_pCall->unInitialize();\n");
                    writer.write("\treturn RetArray;\n");
                }
                else
                {

                    if (returntypeissimple)
                    {
                        writer.write(
                            "\t\t\tRet = m_pCall->"
                                + CUtils.getParameterGetValueMethodName(
                                    outparamType,
                                    false)
                                + "(\""
                                + returntype.getParamName()
                                + "\", 0);\n\t\t}\n");
                        writer.write("\t}\n");
                        writer.write("\tupdateStateAfterResponse();\n");
                        writer.write("\tm_pCall->unInitialize();\n");
                        //            writer.write("\t}\n\tm_pCall->unInitialize();\n");
                        writer.write("\treturn Ret;\n");
                    }
                    else
                    {

                        if (returntype.isAnyType())
                        {
                            //for anyTtype 
                            writer.write(
                                "\t\t\tpReturn = ("
                                    + outparamType
                                    + "*)m_pCall->getAnyObject();\n\t\t}\n");
                            writer.write("\t}\n");
                            writer.write("\tupdateStateAfterResponse();\n");
                            writer.write("\tm_pCall->unInitialize();\n");
                            //                writer.write("\t}\n\tm_pCall->unInitialize();\n");
                            writer.write("\treturn pReturn;\n");
                        }
                        else
                        {
                            //writer.write("\t\t\tpReturn = ("+outparamType+"*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_"+outparamType+", (void*) Axis_Create_"+outparamType+", (void*) Axis_Delete_"+outparamType+",\""+returntype.getElementName().getLocalPart()+"\", 0);\n\t\t}\n"); 
                            //Samisa 22/08/2004
                            writer.write(
                                "\t\t\tpReturn = ("
                                    + outparamType
                                    + "*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_"
                                    + outparamType
                                    + ", (void*) Axis_Create_"
                                    + outparamType
                                    + ", (void*) Axis_Delete_"
                                    + outparamType
                                    + ",\""
                                    + returntype.getElementNameAsString()
                                    + "\", 0);\n\t\t}\n");
                            //Samisa
                            writer.write("\t}\n");
                            writer.write("\tupdateStateAfterResponse();\n");
                            writer.write("\tm_pCall->unInitialize();\n");
                            //                writer.write("\t}\n\tm_pCall->unInitialize();\n");
                            writer.write("\treturn pReturn;\n");
                        }
                    }
                }
            }
        }
        //added by nithya

        writer.write("\t}\n");
        writer.write("\tcatch(AxisException& e)\n\t{\n");
        writer.write("\t\tint iExceptionCode = e.getExceptionCode();\n");
        writer.write(
            "\t\tif(AXISC_NODE_VALUE_MISMATCH_EXCEPTION != iExceptionCode)\n");
        writer.write("\t\t{\n");
        writer.write(
            "\t\t\tthrow "
                + wscontext.getSerInfo().getServicename()
                + "_AxisClientException(e.what());\n");
        writer.write("\t\t}\n");
        writer.write(
            "\t\tISoapFault* pSoapFault = (ISoapFault*) m_pCall->checkFault(\"Fault\",\""
                + wscontext.getWrapInfo().getTargetEndpointURI()
                + "\" );\n");
        writer.write("\t\tif(pSoapFault)\n");
        writer.write("\t\t{\n");

        //to get fault info  		
        Iterator paramsFault = minfo.getFaultType().iterator();
        String faultInfoName = null;
        String faultType = null;
        String langName = null;
        String paramName = null;
        boolean flag = false;
        int j = 0;
        if (!paramsFault.hasNext())
        {
            writer.write("\tupdateStateAfterResponse();\n");
            writer.write("\tm_pCall->unInitialize();\n");
            //writer.write("\t\t\tm_pCall->unInitialize();\n");
            writer.write(
                "\t\t\tthrow "
                    + wscontext.getSerInfo().getServicename()
                    + "_AxisClientException(pSoapFault);\n");
        }
        else
        {
            flag = true;
            writer.write(
                "\t\t\tpcCmplxFaultName = pSoapFault->getCmplxFaultObjectName().c_str();\n");
        }
        while (paramsFault.hasNext())
        {
            j = j + 1;
            FaultInfo info = (FaultInfo) paramsFault.next();
            faultInfoName = info.getFaultInfo();

            // FJP - D0004 > Looking through the list of attributes for the 'error' part of
            //               the fault message.  If found, update the faultInfoName with the
            //               'localname' of the qname of the attribute.				
            Iterator infoArrayListIterator = info.getParams().iterator();
            boolean found = false;

            while (infoArrayListIterator.hasNext() && !found)
            {
                ParameterInfo paramInfo =
                    (ParameterInfo) infoArrayListIterator.next();

                if (paramInfo != null)
                {
                    if ("error".equals(paramInfo.getParamName()))
                    {
                        faultInfoName =
                            paramInfo.getElementName().getLocalPart();

                        found = true;
                    }
                }
            }
            // FJP - D0004 <				

            ArrayList paramInfo = info.getParams();
            for (int i = 0; i < paramInfo.size(); i++)
            {
                ParameterInfo par = (ParameterInfo) paramInfo.get(i);
                paramName = par.getParamName();
                langName = par.getLangName();
                faultType =
                    WrapperUtils.getClassNameFromParamInfoConsideringArrays(
                        par,
                        wscontext);
                if (j > 1)
                {
                    writer.write("\t\t\telse if");
                    writeExceptions(
                        faultType,
                        faultInfoName,
                        paramName,
                        langName);
                }
                else
                {
                    writer.write("\t\t\tif");
                    writeExceptions(
                        faultType,
                        faultInfoName,
                        paramName,
                        langName);
                }
            }
        }
        if (flag == true)
        {
            writer.write("\t\t\telse\n\t\t\t{\n");
            writer.write("\tupdateStateAfterResponse();\n");
            writer.write("\tm_pCall->unInitialize();\n");
            //writer.write("\t\t\t\t  m_pCall->unInitialize();\n");
            writer.write(
                "\t\t\t\t  throw "
                    + wscontext.getSerInfo().getServicename()
                    + "_AxisClientException(pSoapFault);\n");
            writer.write("\t\t\t}\n");
        }
        writer.write("\t\t}\n");
        writer.write("\t\telse throw;\n");
        writer.write("\t}\n");
        writer.write("}\n");
    }

    private void writeExceptions(
        String faulttype,
        String faultInfoName,
        String paramName,
        String langName)
        throws WrapperFault
    {
        try
        {
            writer.write(
                "(0 == strcmp(\"" + faultInfoName + "\", pcCmplxFaultName))\n");
            writer.write("\t\t\t{\n");
            writer.write("\t\t\t\t" + faulttype + " pFaultDetail = NULL;\n");
            writer.write(
                "\t\t\t\tpFaultDetail = (" + faulttype + ")pSoapFault->\n");
            writer.write(
                "\t\t\t\t\tgetCmplxFaultObject((void*) Axis_DeSerialize_"
                    + langName
                    + ",\n");
            writer.write("\t\t\t\t\t(void*) Axis_Create_" + langName + ",\n");
            writer.write(
                "\t\t\t\t\t(void*) Axis_Delete_"
                    + langName
                    + ",\""
                    + faultInfoName
                    + "\", 0);\n");
            writer.write(
                "\t\t\t\tpSoapFault->setCmplxFaultObject(pFaultDetail);\n");
            writer.write("\tupdateStateAfterResponse();\n");
            writer.write("\tm_pCall->unInitialize();\n");
            //writer.write("\t\t\t\tm_pCall->unInitialize();\n");
            writer.write(
                "\t\t\t\tthrow "
                    + wscontext.getSerInfo().getServicename()
                    + "_AxisClientException(pSoapFault);\n");
            writer.write("\t\t\t}\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.CPPClassWriter#writeGlobalCodes()
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
                {
                    continue;
                }
                if (type.isArray())
                {
                    continue;
                }
                typeName = type.getLanguageSpecificName();
                if (typeName.startsWith(">"))
                {
                    continue;
                }
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
                        + " *Obj, bool bArray = false, int nSize=0);\n");
                writer.write(
                    "extern void Axis_Delete_"
                        + typeName
                        + "("
                        + typeName
                        + "* param, bool bArray = false, int nSize=0);\n");
                writer.write(
                    "extern int Axis_Serialize_"
                        + typeName
                        + "("
                        + typeName
                        + "* param, IWrapperSoapSerializer* pSZ, bool bArray = false);\n");
                writer.write("extern int Axis_GetSize_" + typeName + "();\n\n");
            }
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
