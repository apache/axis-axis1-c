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

package org.apache.axis.wsdl.wsdl2ws.cpp.literal;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.FaultInfo;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class WrapWriter extends org.apache.axis.wsdl.wsdl2ws.cpp.WrapWriter
{
    public WrapWriter(WebServiceContext wscontext) throws WrapperFault
    {
        super(wscontext);
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
        Type type;
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
                    if (returntype.isArray())
                    {
                        outparamType =
                            WrapperUtils
                                .getClassNameFromParamInfoConsideringArrays(
                                returntype,
                                wscontext);
                        returntypeissimple =
                            (null != CUtils.getclass4qname(retType.getName())
                                && CUtils.isSimpleType(
                                    CUtils.getclass4qname(retType.getName())));
                        returntypeisarray = true;
                    }
                    else
                    {
                        outparamType = retType.getLanguageSpecificName();
                        returntypeissimple = CUtils.isSimpleType(outparamType);
                        returntypeisarray = retType.isArray();
                    }
                }
            }
            else
            {
                outparamType = returntype.getLangName();
                returntypeissimple = CUtils.isSimpleType(outparamType);
            }
        }
        writer.write("\n/*\n");
        writer.write(" * This method wrap the service method \n");
        writer.write(" */\n");
        //method signature
        writer.write(
            "int " + classname + "::" + methodName + "(void* pMsg)\n{\n");
        writer.write("\tIMessageData* mc = (IMessageData*)pMsg;\n");
        writer.write("\tint nStatus;\n");
        writer.write("\tIWrapperSoapSerializer* pIWSSZ = NULL;\n");
        writer.write("\tmc->getSoapSerializer(&pIWSSZ);\n");
        writer.write("\tif (!pIWSSZ) return AXIS_FAIL;\n");
        writer.write("\tIWrapperSoapDeSerializer* pIWSDZ = NULL;\n");
        writer.write("\tmc->getSoapDeSerializer(&pIWSDZ);\n");
        writer.write("\tif (!pIWSDZ) return AXIS_FAIL;\n");
        writer.write("\t/* check whether we have got correct message */\n");
        writer.write(
            "\tif (AXIS_SUCCESS != pIWSDZ->checkMessageBody(\""
                + minfo.getInputMessage().getLocalPart()
                + "\", \""
                + minfo.getInputMessage().getNamespaceURI()
                + "\")) return AXIS_FAIL;\n");
        if (minfo.getOutputMessage() != null)
        {
            writer.write(
                "\tpIWSSZ->createSoapMethod(\""
                    + minfo.getOutputMessage().getLocalPart()
                    + "\", \""
                    + minfo.getOutputMessage().getNamespaceURI()
                    + "\");\n");
        }
        //create and populate variables for each parameter
        String paraTypeName;

        String elementName;
        String returnParamName;
        ArrayList paramsB = new ArrayList(params);
        for (int i = 0; i < paramsB.size(); i++)
        {
            ParameterInfo param = (ParameterInfo) paramsB.get(i);
            type = this.wscontext.getTypemap().getType(param.getSchemaName());
            if (type != null && type.isSimpleType())
            { //schema defined simpleType possibly with restrictions
                paraTypeName = CUtils.getclass4qname(type.getBaseType());
            }
            else
            {
                if (param.isArray())
                {
                    paraTypeName =
                        WrapperUtils
                            .getClassNameFromParamInfoConsideringArrays(
                            param,
                            wscontext);
                }
                else
                {
                    paraTypeName = param.getLangName();
                }
            }

            elementName = param.getElementNameAsString();
            if (type != null && type.isSimpleType())
            { //schema defined simpleType possibly with restrictions
            	if (param.isNillable() && 
            			!(type.getLanguageSpecificName().equals("xsd__string")
            					|| type.getLanguageSpecificName().equals("xsd__anyURI")
								|| type.getLanguageSpecificName().equals("xsd__QName")
								|| type.getLanguageSpecificName().equals("xsd__notation")))
            	{
                writer.write(
                    "\t"
                        + paraTypeName
                        + "* v"
                        + i
                        + " = pIWSDZ->"
                        + CUtils.getParameterGetValueMethodName(
                            paraTypeName,
                            false)
                        + "(\""
                        + elementName
                        + "\",0);\n");
            	}
            	else
            	{
            		writer.write(
                            "\t"
                                + paraTypeName
                                + " v"
                                + i
                                + " = *(pIWSDZ->"
                                + CUtils.getParameterGetValueMethodName(
                                    paraTypeName,
                                    false)
                                + "(\""
                                + elementName
                                + "\",0));\n");
            	}
            }
            else
            {
                if ((CUtils.isSimpleType(param.getLangName())))
                {
                    //for simple types	
                    if (param.isArray())
                    { /*parameters that are declared as arrays in the wrapping element.*/
                        String containedType =
                            CUtils.getclass4qname(type.getName());
                        writer.write(
                            "\t"
                                + paraTypeName
                                + " v"
                                + i
                                + " = ("
                                + CUtils.getBasicArrayNameforType(containedType)
                                + "&)pIWSDZ->getBasicArray("
                                + CUtils.getXSDTypeForBasicType(containedType)
                                + ", \""
                                + elementName
                                + "\",0);\n");
                    }
                    else
                    {
                    	if (paraTypeName.equals("xsd__string")
										|| paraTypeName.equals("xsd__anyURI")
										|| paraTypeName.equals("xsd__QName")
										|| paraTypeName.equals("xsd__notation"))
                    	{
                    		writer.write("\t"
                                + paraTypeName
                                + " v"
                                + i
                                + " = pIWSDZ->"
                                + CUtils.getParameterGetValueMethodName(
                                    paraTypeName,
                                    false)
                                + "(\""
                                + elementName
                                + "\",0);\n");
                    	}
                    	else
                    	{
                    		if (param.isNillable())
                    		{
                    			writer.write("\t"
                                        + paraTypeName
                                        + "* v"
                                        + i
                                        + " = pIWSDZ->"
                                        + CUtils.getParameterGetValueMethodName(
                                            paraTypeName,
                                            false)
                                        + "(\""
                                        + elementName
                                        + "\",0);\n");
                    		}
                    		else
                    		{
	                    		writer.write("\t"
	                                + paraTypeName
	                                + " v"
	                                + i
	                                + " = *(pIWSDZ->"
	                                + CUtils.getParameterGetValueMethodName(
	                                    paraTypeName,
	                                    false)
	                                + "(\""
	                                + elementName
	                                + "\",0));\n");
                    		}
                    	}
                    }
                }
                else
                {
                    if ((type != null) && type.isArray())
                    {
                        Type arrayType = WrapperUtils.getArrayType(type);
                        QName qname = arrayType.getName();
                        String containedType = null;
                        if (CUtils.isSimpleType(qname))
                        {
                            containedType = CUtils.getclass4qname(qname);
                            writer.write(
                                "\t"
                                    + paraTypeName
                                    + " v"
                                    + i
                                    + " = ("
                                    + CUtils.getBasicArrayNameforType(
                                        containedType)
                                    + "&)pIWSDZ->getBasicArray("
                                    + CUtils.getXSDTypeForBasicType(
                                        containedType)
                                    + ", \""
                                    + elementName
                                    + "\",0);\n");
                        }
                        else
                        {
                            if (arrayType.isSimpleType())
                            { //SimpleType in the schema 
                                containedType =
                                    CUtils.getclass4qname(
                                        arrayType.getBaseType());
                                writer.write(
                                    "\t"
                                        + paraTypeName
                                        + " v"
                                        + i
                                        + " = ("
                                        + CUtils.getBasicArrayNameforType(
                                            containedType)
                                        + "&)pIWSDZ->getBasicArray("
                                        + CUtils.getXSDTypeForBasicType(
                                            containedType)
                                        + ", \""
                                        + elementName
                                        + "\",0);\n");
                            }
                            else
                            {
                                containedType = qname.getLocalPart();
                                writer.write(
                                    "\t"
                                        + paraTypeName
                                        + " v"
                                        + i
                                        + " = ("
                                        + paraTypeName
                                        + "&)pIWSDZ->getCmplxArray((void*)Axis_DeSerialize_"
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
                            }
                        }
                    }
                    else
                    {
                        if (param.isAnyType())
                        {
                            //for anyType
                            writer.write(
                                "\t"
                                    + paraTypeName
                                    + " *v"
                                    + i
                                    + " = ("
                                    + paraTypeName
                                    + "*)pIWSDZ->getAnyObject();\n");
                        }
                        else
                        {
                            //for complex types 
                            writer.write(
                                "\t"
                                    + paraTypeName
                                    + " *v"
                                    + i
                                    + " = ("
                                    + paraTypeName
                                    + "*)pIWSDZ->getCmplxObject((void*)Axis_DeSerialize_"
                                    + paraTypeName
                                    + "\n\t\t, (void*)Axis_Create_"
                                    + paraTypeName
                                    + ", (void*)Axis_Delete_"
                                    + paraTypeName
                                    + "\n\t\t, \""
                                    + elementName
                                    + "\", Axis_URI_"
                                    + paraTypeName
                                    + ");\n");
                        }
                    }
                }
            }
        }
        writer.write(
            "\tif (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;\n");
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
        writer.write("\ttry\n\t{\n"); //nithya
        if (returntype != null)
        { /* Invoke the service when return type not void */
            returnParamName = returntype.getElementNameAsString();
            writer.write("\t" + outparamType);
            if (!returntypeisarray 
        		&& (!returntypeissimple
            		|| (!returntypeissimple
        				&& returntype.isNillable()
						&& !(retType.getLanguageSpecificName().equals("xsd__string")
							|| retType.getLanguageSpecificName().equals("xsd__anyURI")
							|| retType.getLanguageSpecificName().equals("xsd__QName")
							|| retType.getLanguageSpecificName().equals("xsd__notation")))))
            {
            	writer.write(" *");
            }
            writer.write(" ret = "
                    + "pWs->"
                    + methodName
                    + "(");
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
                if (returntype.isArray())
                { /*parameters that are declared as arrays in the wrapping element.*/
                    String containedType =
                        CUtils.getclass4qname(retType.getName());
                    writer.write(
                        "\treturn pIWSSZ->addOutputBasicArrayParam((Axis_Array*)(&ret),"
                            + CUtils.getXSDTypeForBasicType(containedType)
                            + ", \""
                            + returnParamName
                            + "\");\n");
                }
                else
                {
                	String returnParamTypeName = retType.getLanguageSpecificName();
                	if (returntype.isNillable()
                			|| returnParamTypeName.equals("xsd__string")
                			|| returnParamTypeName.equals("xsd__anyURI")
							|| returnParamTypeName.equals("xsd__QName")
							|| returnParamTypeName.equals("xsd__notation"))
                	{
	                    writer.write(
	                        "\treturn pIWSSZ->addOutputParam(\""
	                            + returnParamName
	                            + "\", (void*)ret, "
	                            + CUtils.getXSDTypeForBasicType(outparamType)
	                            + ");\n");
                	}
                	else
                	{
                		writer.write(
    	                        "\treturn pIWSSZ->addOutputParam(\""
    	                            + returnParamName
    	                            + "\", (void*)&ret, "
    	                            + CUtils.getXSDTypeForBasicType(outparamType)
    	                            + ");\n");
                	}
                }
            }
            else
            {
                if (returntypeisarray)
                {
                    Type arrayType = WrapperUtils.getArrayType(retType);
                    QName qname = arrayType.getName();
                    String containedType = null;
                    if (CUtils.isSimpleType(qname))
                    {
                        containedType = CUtils.getclass4qname(qname);
                        writer.write(
                            "\treturn pIWSSZ->addOutputBasicArrayParam((Axis_Array*)(&ret),"
                                + CUtils.getXSDTypeForBasicType(containedType)
                                + ", \""
                                + returnParamName
                                + "\");\n");
                    }
                    else
                    {
                        if (arrayType.isSimpleType())
                        { //SimpleType in the schema 
                            containedType =
                                CUtils.getclass4qname(arrayType.getBaseType());
                            writer.write(
                                "\treturn pIWSSZ->addOutputBasicArrayParam((Axis_Array*)(&ret),"
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
                                "\treturn pIWSSZ->addOutputCmplxArrayParam((Axis_Array*)(&ret),"
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
                }
                else
                {
                    if (returntype.isAnyType())
                    {
                        writer.write(
                            "\treturn pIWSSZ->addOutputAnyObject(ret);\n");
                    }
                    else
                    {
                        //complex type
                        writer.write(
                            "\treturn pIWSSZ->addOutputCmplxParam(ret, (void*)Axis_Serialize_"
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
            }
        }
        else
        {
            if (isAllTreatedAsOutParams)
            {
                writer.write("\tpWs->" + methodName + "(");
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
                        if (param.isArray())
                        { /*parameters that are declared as arrays in the wrapping element.*/
                            String containedType =
                                CUtils.getclass4qname(retType.getName());
                            writer.write(
                                "\treturn pIWSSZ->addOutputBasicArrayParam((Axis_Array*)(&ret),"
                                    + CUtils.getXSDTypeForBasicType(
                                        containedType)
                                    + ", \""
                                    + returnParamName
                                    + "\");\n");
                        }
                        else
                        {
                            writer.write(
                                "\tpIWSSZ->addOutputParam(\""
                                    + returnParamName
                                    + "\", (void*)&out"
                                    + i
                                    + ", "
                                    + CUtils.getXSDTypeForBasicType(outparamType)
                                    + ");\n");
                        }
                    }
                    else
                    {

                        if (returntypeisarray)
                        {
                            Type arrayType = WrapperUtils.getArrayType(retType);
                            QName qname = arrayType.getName();
                            String containedType = null;
                            if (CUtils.isSimpleType(qname))
                            {
                                containedType = CUtils.getclass4qname(qname);
                                writer.write(
                                    "\tpIWSSZ->addOutputBasicArrayParam((Axis_Array*)(&out"
                                        + i
                                        + "),"
                                        + CUtils.getXSDTypeForBasicType(
                                            containedType)
                                        + ", \""
                                        + returnParamName
                                        + "\");\n");
                            }
                            else
                            {
                                if (arrayType.isSimpleType())
                                { //SimpleType in the schema 
                                    containedType =
                                        CUtils.getclass4qname(
                                            arrayType.getBaseType());
                                    writer.write(
                                        "\tpIWSSZ->addOutputBasicArrayParam((Axis_Array*)(&out"
                                            + i
                                            + "),"
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
                                        "\tpIWSSZ->addOutputCmplxArrayParam((Axis_Array*)(&out"
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
                        }
                        else
                        {
                            if (param.isAnyType())
                            {
                                //anyType
                                writer.write(
                                    "\tpIWSSZ->addOutputAnyObject(out"
                                        + i
                                        + ");\n");
                            }
                            else
                            {
                                //complex type
                                writer.write(
                                    "\tpIWSSZ->addOutputCmplxParam(out"
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
                    }
                }
                writer.write("\treturn AXIS_SUCCESS;\n");
            }
            else
            { //method does not return anything
                /* Invoke the service when return type is void */
                writer.write("\tpWs->" + methodName + "(");
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
        }
        writer.write("\t}\n"); //nithya          
        Iterator paramsFault = minfo.getFaultType().iterator();
        String faultInfoName = null;
        String faultType = null;
        String langName = null;
        String paramName = null;
        while (paramsFault.hasNext())
        {
            FaultInfo info = (FaultInfo) paramsFault.next();
            faultInfoName = info.getFaultInfo();
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
                writeExceptions(faultType, faultInfoName, paramName, langName);
            }
        }
        writer.write("\tcatch(...){\n"); //nithya
        writer.write("\t}\n"); //nithya
        //write end of method
        writer.write("}\n");
    }
    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.CPPClassWriter#writeGlobalCodes()
     */

    private void writeExceptions(
        String faulttype,
        String faultInfoName,
        String paramName,
        String langName)
        throws WrapperFault
    {
        try
        {
            writer.write("\tcatch(" + faulttype + " pObjFault)\n");
            writer.write("\t{\n");
            writer.write("\t\tif (pObjFault)\n");
            writer.write("\t\t{\n");
            writer.write(
                "\t\tpIWSSZ->createSoapFault(\""
                    + faultInfoName
                    + "\", \""
                    + wscontext.getWrapInfo().getTargetNameSpaceOfWSDL()
                    + "\",\"AxisC++ Faultcode\", \"Custom Out of bound exception\");\n");
            //	writer.write("\t\t"+faulttype+" pObjFault = new "+langName+"();\n");//damitha			                 
            writer.write(
                "\t\t\tpIWSSZ->addFaultDetail(pObjFault, (void*) Axis_Serialize_"
                    + langName
                    + ",\n");
            writer.write(
                "\t\t\t(void*) Axis_Delete_"
                    + langName
                    + ",\""
                    + faultInfoName
                    + "\", Axis_URI_"
                    + langName
                    + ");\n");
            writer.write("\t\tthrow AxisServiceException();\n");
            writer.write("\t\t}\n");
            writer.write("\t}\n");
            writer.write("\n");
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
