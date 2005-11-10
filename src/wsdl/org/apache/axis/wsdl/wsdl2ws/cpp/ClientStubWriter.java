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
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws.cpp;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.FaultInfo;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ClientStubWriter extends CPPClassWriter
{
    protected ArrayList methods;

    public ClientStubWriter(WebServiceContext wscontext) throws WrapperFault
    {
        super(WrapperUtils.getClassNameFromFullyQualifiedName(wscontext
                .getSerInfo().getQualifiedServiceName()));
        this.wscontext = wscontext;
        this.methods = wscontext.getSerInfo().getMethods();
    }

    protected String getServiceName() throws WrapperFault
    {
        return wscontext.getSerInfo().getServicename();
    }

    protected void writeClassComment() throws WrapperFault
    {
        try
        {
            writer.write("/*\n");
            writer
                    .write(" * This file was auto-generated by the Axis C++ Web Service "
                            + "Generator (WSDL2Ws)\n");
            writer
                    .write(" * This file contains Client Stub implementation for remote web service.\n");
            writer.write(" */\n\n");
        } catch (IOException e)
        {
            throw new WrapperFault(e);
        }
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
            writer
                    .write(classname
                            + "::"
                            + classname
                            + "(const char* pchEndpointUri, AXIS_PROTOCOL_TYPE eProtocol)\n:Stub(pchEndpointUri, eProtocol)\n{\n");
            writer.write("}\n\n");
            writer.write(classname + "::" + classname
                    + "()\n:Stub(\" \", APTHTTP1_1)\n{\n");
            //TODO get TransportURI from WrapInfo and check what the transport
            // is and do the following line accordingly
            writer
                    .write("\tm_pCall->setEndpointURI(\""
                            + wscontext.getWrapInfo().getTargetEndpointURI()
                            + "\");\n");
            writer.write("}\n\n");
        } catch (IOException e)
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
            writer.write(classname + "::~" + classname + "()\n{\n}\n\n");
        } catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
     */
    protected void writeMethods() throws WrapperFault
    {
        try
        {
            writer
                    .write("\n/*Methods corresponding to the web service methods*/\n");
            MethodInfo minfo;
            for (int i = 0; i < methods.size(); i++)
            {
                minfo = (MethodInfo) methods.get(i);
                this.writeMethodInWrapper(minfo);
                writer.write("\n");
            }
            //damitha
        } catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /*
     * (non-Javadoc)
     * 
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writePreprocssorStatements()
     */
    protected void writePreprocessorStatements() throws WrapperFault
    {
        try
        {
            if ("AxisClientException".equals(classname))
            {
                writer.write("#include \"" + getServiceName() + "_" + classname
                        + CUtils.CPP_HEADER_SUFFIX + "\"\n\n");
            }
            else
            {
                writer.write("#include \"" + classname
                        + CUtils.CPP_HEADER_SUFFIX + "\"\n\n");
            }
            writer.write("#include <axis/AxisWrapperAPI.hpp>\n");
            writer.write("#include <string.h>\n\n"); // for memcpy
            writer.write("using namespace std;\n\n ");

        } catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /**
     * This method genarate methods that wraps the each method of the service
     * 
     * @param methodName
     * @param params
     * @param outparam
     * @throws IOException
     */

    public void writeMethodInWrapper(MethodInfo minfo) throws WrapperFault,
            IOException
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
                returntype = (ParameterInfo) minfo.getOutputParameterTypes()
                        .iterator().next();
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
        String outparamTypeName = null;
        if (returntype != null)
        {
            outparamTypeName = WrapperUtils
                    .getClassNameFromParamInfoConsideringArrays(returntype,
                            wscontext);
            retType = wscontext.getTypemap()
                    .getType(returntype.getSchemaName());
            if (retType != null)
            {
                returntypeisarray = retType.isArray();
                if (WSDL2Ws.verbose)
                {
                    System.out.println(retType.getLanguageSpecificName()
                            + "LanguageName  .................... ");
                }
                if (CUtils.isSimpleType(retType.getLanguageSpecificName()))
                {
                    returntypeissimple = true;
                }
            }
        }
        writer.write("\n/*\n");
        writer.write(" * This method wrap the service method " + methodName
                + "\n");
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
        {
            if (returntypeisarray || (returntypeissimple && returntype.isNillable()
                    && !(CUtils.isPointerType(outparamTypeName))))
            {
                writer.write(outparamTypeName + " *");
            }
            else
            {
                writer.write(outparamTypeName);
            }

            if (WSDL2Ws.verbose)
            {
                System.out.println("Output Parameter type Name :"
                        + outparamTypeName);
            }
        }
        writer.write(" " + classname + "::" + methodName + "(");
        ArrayList paramsB = (ArrayList) params;
        for (int i = 0; i < paramsB.size(); i++)
        {
            paramTypeName = WrapperUtils
                    .getClassNameFromParamInfoConsideringArrays(
                            (ParameterInfo) paramsB.get(i), wscontext);
            if (i > 0)
            {
                writer.write(", ");
            }
            typeissimple = CUtils.isSimpleType(paramTypeName);
            if (typeissimple && ((ParameterInfo) paramsB.get(i)).isNillable()
                    && !(CUtils.isPointerType(paramTypeName)))
            {
                writer.write(paramTypeName + " * Value" + i);
            }
            else
            {
                writer.write(paramTypeName + " Value" + i);
            }
        }
        // Multiples parameters so fill the methods prototype
        ArrayList paramsC = (ArrayList) minfo.getOutputParameterTypes();
        if (isAllTreatedAsOutParams)
        {
            String currentParaTypeName;
            for (int i = 0; i < paramsC.size(); i++)
            {
                type = wscontext.getTypemap().getType(
                        ((ParameterInfo) paramsC.get(i)).getSchemaName());
                writer.write(", AXIS_OUT_PARAM  "
                        + WrapperUtils
                                .getClassNameFromParamInfoConsideringArrays(
                                        (ParameterInfo) paramsC.get(i),
                                        wscontext) + " *OutValue" + i);
            }
        }
        writer.write(")\n{\n");
        if (returntype != null)
        {
            writer.write("\t");
            if (returntypeisarray)
            {
                //for arrays
                writer.write(outparamTypeName + " * RetArray = new " + outparamTypeName + "();\n");
            }
            else
            {
                if (!returntypeissimple)
                {
                    writer.write(outparamTypeName + " pReturn = NULL;\n");
                    //for complex types
                }
                else
                {
                    //for simple types
                    if (returntype.isNillable()
                            && !(CUtils.isPointerType(outparamTypeName)))
                    {
                        writer.write(outparamTypeName + "* Ret = NULL;\n");
                    }
                    else if (outparamTypeName.equals("xsd__string"))
                    {
                        writer.write(outparamTypeName + " Ret;\n");
                        writer.write("\tmemset(&Ret,0,sizeof("
                                + outparamTypeName + "));\n");
                    }
                    else
                    {
                        String initValue = CUtils
                                .getInitValue(outparamTypeName);
                        if (initValue != null)
                        {
                            writer.write(outparamTypeName + "* Ret = NULL;\n");//" +
                                                                               // initValue
                                                                               // +
                                                                               // ";\n");
                        }
                        else
                        {
                            if (outparamTypeName.equals("xsd__base64Binary")
                                    || outparamTypeName
                                            .equals("xsd__hexBinary"))
                            {
                                writer
                                        .write(outparamTypeName
                                                + "* Ret=NULL;\n");
                                //writer.write("\tRet->__ptr = NULL;\n");
                                //writer.write("\tRet->__size = 0;\n");
                            }

                            else
                            {
                                writer
                                        .write(outparamTypeName
                                                + "* Ret=NULL;\n");
                            }
                        }
                        //TODO initialize return parameter appropriately.
                    }
                }
            }
        }

        //writer.write("\tchar* cFaultcode;\n");
        //writer.write("\tchar* cFaultstring;\n");
        //writer.write("\tchar* cFaultactor;\n");
        writer.write("\tconst char* pcCmplxFaultName;\n");
        writer.write("\ttry\n\t{");
        writer
                .write("\n\t\tif (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER"
                        + ")) \n\t\t\treturn ");
        //damitha
        if (returntype != null)
        {
            if (outparamTypeName.equals("xsd__string") && returntypeissimple)
                writer.write("Ret;\n");
            else
                writer.write((returntypeisarray ? "RetArray"
                        : returntypeissimple ? "*Ret" : "pReturn")
                        + ";\n");
        }
        else
        {
            writer.write(";\n");
        }
        writer
                .write("\tif (NULL==m_pCall->getTransportProperty(\"SOAPAction\",false))\n");
        writer.write("\t{\n");
        writer.write("\t\tm_pCall->setTransportProperty(SOAPACTION_HEADER , \""
                + minfo.getSoapAction() + "\");\n");
        writer.write("\t}\n");
        writer.write("\t\tm_pCall->setSOAPVersion(SOAP_VER_1_1);\n");
        //TODO check which version is it really.
        writer.write("\t\tm_pCall->setOperation(\"" + minfo.getMethodname()
                + "\", \"" + wscontext.getWrapInfo().getTargetNameSpaceOfWSDL()
                + "\");\n");
        writer.write("\t\tapplyUserPreferences();\n");
        for (int i = 0; i < paramsB.size(); i++)
        {
            type = wscontext.getTypemap().getType(
                    ((ParameterInfo) paramsB.get(i)).getSchemaName());
            if (type != null)
            {
                paramTypeName = type.getLanguageSpecificName();
                typeisarray = type.isArray();
            }
            else
            {
                paramTypeName = ((ParameterInfo) paramsB.get(i)).getLangName();
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
                    writer.write("\tm_pCall->addBasicArrayParameter(");
                    writer.write("(Axis_Array*)(&Value" + i + "), "
                            + CUtils.getXSDTypeForBasicType(containedType)
                            + ", \""
                            + ((ParameterInfo) paramsB.get(i)).getParamName()
                            + "\"");
                }
                else
                {
                    containedType = qname.getLocalPart();
                    writer.write("\tm_pCall->addCmplxArrayParameter(");
                    writer.write("Value" + i
                            + ", (void*)Axis_Serialize_" + containedType
                            + ", (void*)Axis_Delete_" + containedType
                            + ", (void*) Axis_GetSize_" + containedType
                            + ", \""
                            + ((ParameterInfo) paramsB.get(i)).getParamName()
                            + "\", Axis_URI_" + containedType);
                }
            }
            else
            {
                if (typeissimple)
                {

                    //for simple types
                    if (((ParameterInfo) paramsB.get(i)).isNillable()
                            || CUtils.isPointerType(paramTypeName))
                    {
                        writer.write("\t\tm_pCall->addParameter(");
                        writer.write("(void*)Value"
                                + i
                                + ", \""
                                + ((ParameterInfo) paramsB.get(i))
                                        .getParamName() + "\", "
                                + CUtils.getXSDTypeForBasicType(paramTypeName));
                    }
                    else
                    {
                        writer.write("\t\tm_pCall->addParameter(");
                        writer.write("(void*)&Value"
                                + i
                                + ", \""
                                + ((ParameterInfo) paramsB.get(i))
                                        .getParamName() + "\", "
                                + CUtils.getXSDTypeForBasicType(paramTypeName));
                    }
                }
                else
                {
                    //for complex types
                    writer.write("\tm_pCall->addCmplxParameter(");
                    writer.write("Value" + i + ", (void*)Axis_Serialize_"
                            + paramTypeName + ", (void*)Axis_Delete_"
                            + paramTypeName + ", \""
                            + ((ParameterInfo) paramsB.get(i)).getParamName()
                            + "\", Axis_URI_" + paramTypeName);
                }
            }
            writer.write(");\n");
        }
        writer.write("\t\tif (AXIS_SUCCESS == m_pCall->invoke())\n\t\t{\n");
        writer.write("\t\t\tif(AXIS_SUCCESS == m_pCall->checkMessage(\""
                + minfo.getOutputMessage().getLocalPart() + "\", \""
                + wscontext.getWrapInfo().getTargetNameSpaceOfWSDL()
                + "\"))\n\t\t\t{\n");

        if (isAllTreatedAsOutParams)
        {
            String currentParamName;
            String currentParaType;
            for (int i = 0; i < paramsC.size(); i++)
            {
                ParameterInfo currentType = (ParameterInfo) paramsC.get(i);
                type = wscontext.getTypemap().getType(
                        currentType.getSchemaName());
                if (type != null)
                {
                    currentParaType = type.getLanguageSpecificName();
                    typeisarray = type.isArray();
                }
                else
                {
                    currentParaType = ((ParameterInfo) paramsC.get(i))
                            .getLangName();
                    typeisarray = false;
                }
                typeissimple = CUtils.isSimpleType(currentParaType);

                currentParamName = "*OutValue" + i;
                // Some code need to be merged as we have some duplicated in
                // coding here.
                if (typeisarray)
                {
                    QName qname = WrapperUtils.getArrayType(type).getName();
                    String containedType = null;
                    if (CUtils.isSimpleType(qname))
                    {
                        containedType = CUtils.getclass4qname(qname);
                        writer.write("\t\t\t\t" + currentParamName + " = ("
                                + currentParaType + "&)m_pCall->getBasicArray("
                                + CUtils.getXSDTypeForBasicType(containedType)
                                + ", \"" + currentType.getParamName()
                                + "\", 0);\n");
                    }
                    else
                    {
                        containedType = qname.getLocalPart();
                        writer
                                .write("\t\t\t\t"
                                        + currentParamName
                                        + " = ("
                                        + currentParaType
                                        + "&)m_pCall->getCmplxArray((void*) Axis_DeSerialize_"
                                        + containedType);
                        writer.write("\t\t\t\t, (void*) Axis_Create_"
                                + containedType + ", (void*) Axis_Delete_"
                                + containedType + ", (void*) Axis_GetSize_"
                                + containedType + ", \""
                                + currentType.getParamName() + "\", Axis_URI_"
                                + containedType + ");\n");
                    }
                }
                else
                {
                    if (typeissimple)
                    {
                        //Chinthana:
                        //Changes have done for handle AXIS_OUT_PARAM Types.
                        if (CUtils.isPointerType(currentParaType))
                        {
                            writer.write("\t\t\t\t"
                                    + currentParamName
                                    + " = m_pCall->"
                                    + CUtils.getParameterGetValueMethodName(
                                            currentParaType, false) + "(\""
                                    + currentType.getParamName() + "\", 0);\n");
                        }
                        else
                        {
                            writer
                                    .write("\t\t\t\t"
                                            + currentParamName
                                            + " = *(m_pCall->"
                                            + CUtils
                                                    .getParameterGetValueMethodName(
                                                            currentParaType,
                                                            false) + "(\""
                                            + currentType.getParamName()
                                            + "\", 0));\n");
                        }
                        //02/06/2006.....................................................
                    }
                    else
                    {
                        writer
                                .write("\t\t\t\t"
                                        + currentParamName
                                        + " = ("
                                        + currentParaType
                                        + "*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_"
                                        + currentParaType
                                        + ", (void*) Axis_Create_"
                                        + currentParaType
                                        + ", (void*) Axis_Delete_"
                                        + currentParaType + ",\""
                                        + currentType.getParamName()
                                        + "\", 0);\n");
                    }
                }
            }
            writer.write("\t\t\t}\n");
            writer.write("\t\t}\n");
            writer.write("\tm_pCall->unInitialize();\n");
        }
        else if (returntype == null)
        {
            writer.write("\t\t\t/*not successful*/\n\t\t}\n");
            writer.write("\t\t}\n");
            writer.write("\tm_pCall->unInitialize();\n");
        }
        else if (returntypeisarray)
        {
            QName qname = WrapperUtils.getArrayType(retType).getName();
            String containedType = null;
            if (CUtils.isSimpleType(qname))
            {
                containedType = CUtils.getclass4qname(qname);
                writer.write("\t\t\t\tAxis_Array * RetAxisArray = "
                        + "m_pCall->getBasicArray("
                        + CUtils.getXSDTypeForBasicType(containedType) + ", \""
                        + returntype.getParamName() + "\", 0);\n");
            }
            else
            {
                containedType = qname.getLocalPart();
                writer.write("\t\t\t\tAxis_Array * RetAxisArray = "
                        + "m_pCall->getCmplxArray((void*) Axis_DeSerialize_"
                        + containedType);
                //damitha
                writer.write(", (void*) Axis_Create_" + containedType
                        + ", (void*) Axis_Delete_" + containedType
                        + ", (void*) Axis_GetSize_" + containedType + ", \""
                        + returntype.getParamName() + "\", Axis_URI_"
                        + containedType + ");\n");
	            
            }
            writer.write ("\t\t\t\tRetArray.clone(*RetAxisArray);\n\t\t\t}\n");
            writer.write ("\t\t\t\tAxis::AxisDelete( (void *)RetAxisArray, XSD_ARRAY);\n\t\t\t}\n");
            writer.write("\t\t}\n");
            writer.write("\tm_pCall->unInitialize();\n");
            //        writer.write("\t\t}\n\t\tm_pCall->unInitialize();\n");
            writer.write("\t\treturn RetArray;\n");
        }
        else if (returntypeissimple)
        {
            writer.write("\t\t\t\tRet = m_pCall->"
                    + CUtils.getParameterGetValueMethodName(outparamTypeName,
                            false) + "(\"" + returntype.getParamName()
                    + "\", 0);\n\t\t\t}\n");
            writer.write("\t\t}\n");
            writer.write("\tm_pCall->unInitialize();\n");
            //            writer.write("\t\t}\n\t\tm_pCall->unInitialize();\n");
            if (outparamTypeName.equals("xsd__string"))
                writer.write("\t\treturn Ret;\n");
            else
            {
                writer.write("\t\t" + outparamTypeName + " r = *Ret;\n"); // make // This does not do a deep
                                                                          // deep // copy! This will only copy 
                                                                          // copy // pointers not content!
                writer.write("\t\tdelete Ret;\n"); // delete pointer
                writer.write("\t\treturn r;\n");
            }
        }
        else
        {
            outparamTypeName = returntype.getLangName();
            //need to have complex type name without *
            writer.write("\t\t\t\tpReturn = (" + outparamTypeName
                    + "*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_"
                    + outparamTypeName + ", (void*) Axis_Create_"
                    + outparamTypeName + ", (void*) Axis_Delete_"
                    + outparamTypeName + ",\"" + returntype.getParamName()
                    + "\", 0);\n\t\t}\n");
            writer.write("\t\t}\n");
            writer.write("\tm_pCall->unInitialize();\n");
            //            writer.write("\t\t}\n\t\tm_pCall->unInitialize();\n");
            writer.write("\t\treturn pReturn;\n");

        }
        //added by nithya
        writer.write("\t}\n");
        writer.write("\tcatch(AxisException& e)\n\t{\n");
        writer.write("\t\tint iExceptionCode = e.getExceptionCode();\n");
        writer
                .write("\t\tif(AXISC_NODE_VALUE_MISMATCH_EXCEPTION != iExceptionCode)\n");
        writer.write("\t\t{\n");
        writer.write("\t\t\tthrow SoapFaultException(e);\n");
        writer.write("\t\t}\n");
        //ISoapFault* pSoapFault = (ISoapFault*) m_pCall->checkFault("Fault",
        // "http://localhost/axis/MathOps");

        writer.write("\t\tISoapFault* pSoapFault = (ISoapFault*)\n");
        writer.write("\t\t\tm_pCall->checkFault(\"Fault\",\""
                + wscontext.getWrapInfo().getTargetEndpointURI() + "\" );\n");
        writer.write("\t\tif(pSoapFault)\n");
        writer.write("\t\t{\n");
        //writer.write("\t\t\tpcCmplxFaultName =
        // pSoapFault->getCmplxFaultObjectName();\n");
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
            writer.write("\t\t\tm_pCall->unInitialize();\n");
            writer.write("\t\t\tthrow SoapFaultException(e);\n");
        }
        else
        {
            flag = true;
            writer
                    .write("\t\t\tpcCmplxFaultName = pSoapFault->getCmplxFaultObjectName();\n");
        }
        while (paramsFault.hasNext())
        {
            j = j + 1;
            FaultInfo info = (FaultInfo) paramsFault.next();
            faultInfoName = info.getFaultInfo();
            ArrayList paramInfo = info.getParams();
            for (int i = 0; i < paramInfo.size(); i++)
            {
                ParameterInfo par = (ParameterInfo) paramInfo.get(i);
                paramName = par.getParamName();
                langName = par.getLangName();
                faultType = WrapperUtils
                        .getClassNameFromParamInfoConsideringArrays(par,
                                wscontext);
                if (j > 1)
                {
                    writer.write("\t\t\telse if");
                    writeExceptions(faultType, faultInfoName, paramName,
                            langName);
                }
                else
                {
                    writer.write("\t\t\tif");
                    writeExceptions(faultType, faultInfoName, paramName,
                            langName);
                }
            }
        }

        if (flag == true)
        {
            writer.write("\t\t\telse\n");
            writer.write("\t\t\t{\n");
            writer.write("\t\t\t\tm_pCall->unInitialize();\n");
            writer.write("\t\t\t\tthrow SoapFaultException(e);\n");
            writer.write("\t\t\t}\n");
        }

        writer.write("\t\t}\n");
        writer.write("\t\telse throw;\n");
        writer.write("\t}\n");
        writer.write("}\n");
    }

    private void writeExceptions(String faulttype, String faultInfoName,
            String paramName, String langName) throws WrapperFault
    {
        try
        {
            writer.write("(0 == strcmp(\"" + faultInfoName
                    + "\", pcCmplxFaultName))\n");
            writer.write("\t\t\t{\n");
            writer.write("\t\t\t\t" + faulttype + " pFaultDetail = \n");
            writer.write("\t\t\t\t\t(" + faulttype
                    + ")pSoapFault->getCmplxFaultObject(\n");
            writer.write("\t\t\t\t\t\t(void*) Axis_DeSerialize_" + langName
                    + ",\n");
            writer.write("\t\t\t\t\t\t(void*) Axis_Create_" + langName + ",\n");
            writer.write("\t\t\t\t\t\t(void*) Axis_Delete_" + langName + ",\n");
            writer.write("\t\t\t\t\t\t\"" + faultInfoName + "\",\n");
            writer.write("\t\t\t\t\t\t0);\n\n");
            writer
                    .write("\t\t\t\tpFaultDetail->setFaultCode(pSoapFault->getFaultcode());\n");
            writer
                    .write("\t\t\t\tpFaultDetail->setFaultString(pSoapFault->getFaultstring());\n");
            writer
                    .write("\t\t\t\tpFaultDetail->setFaultActor(pSoapFault->getFaultactor());\n");
            writer
                    .write("\t\t\t\tpFaultDetail->setExceptionCode(e.getExceptionCode());\n");
            writer.write("\t\t\t\tm_pCall->unInitialize();\n");
            writer.write("\t\t\t\tthrow *pFaultDetail;\n");
            writer.write("\t\t\t}\n");
        } catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /*
     * (non-Javadoc)
     * 
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
                writer.write("extern int Axis_DeSerialize_" + typeName + "("
                        + typeName
                        + "* param, IWrapperSoapDeSerializer* pDZ);\n");
                writer.write("extern void* Axis_Create_" + typeName + "("
                        + typeName
                        + " *Obj, bool bArray = false, int nSize=0);\n");
                writer.write("extern void Axis_Delete_" + typeName + "("
                        + typeName
                        + "* param, bool bArray = false, int nSize=0);\n");
                writer
                        .write("extern int Axis_Serialize_"
                                + typeName
                                + "("
                                + typeName
                                + "* param, IWrapperSoapSerializer* pSZ, bool bArray = false);\n");
                writer.write("extern int Axis_GetSize_" + typeName + "();\n\n");
            }
        } catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
