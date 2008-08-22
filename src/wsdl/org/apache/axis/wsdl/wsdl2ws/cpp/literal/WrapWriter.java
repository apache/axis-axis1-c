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
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
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
            returntype = null;
        else if (1 == noOfOutParams)
            returntype = (ParameterInfo) minfo.getOutputParameterTypes().iterator().next();
        else
            isAllTreatedAsOutParams = true;

        Collection params = minfo.getInputParameterTypes();
        String methodName = minfo.getMethodname();
        Type retType = null;
        String outparamType = null;
        boolean returntypeissimple = false;
        boolean returntypeisarray = false;
        
        if (returntype != null)
        {
            retType = wscontext.getTypemap().getType(returntype.getSchemaName());
            if (retType != null)
            {
                if (retType.isSimpleType())
                { 
                    returntypeissimple = true;
                    outparamType = CUtils.getSimpleType(retType.getBaseType());
                }
                else if (returntype.isArray())
                {
                    outparamType = CUtils.getClassNameFromParamInfoConsideringArrays(returntype,wscontext);
                    returntypeissimple =
                        (null != CUtils.getSimpleType(retType.getName())
                            && CUtils.isSimpleType(CUtils.getSimpleType(retType.getName())));
                    returntypeisarray = true;
                }
                else
                {
                    outparamType = retType.getLanguageSpecificName();
                    returntypeissimple = CUtils.isSimpleType(outparamType);
                    returntypeisarray = retType.isArray();
                }
            }
            else
            {
                outparamType = returntype.getLangName();
                returntypeissimple = CUtils.isSimpleType(outparamType);
            }
        }
        
        CUtils.printMethodComment(c_writer, "This method wraps the service method " + methodName + ".");

        //method signature
        c_writer.write("int " + c_classname + "::" + methodName + "(void* pMsg)\n{\n");
        c_writer.write("\tIMessageData* mc = (IMessageData*)pMsg;\n");
        c_writer.write("\tint nStatus;\n\n");
        
        c_writer.write("\tIWrapperSoapSerializer* pIWSSZ = NULL;\n");
        c_writer.write("\tmc->getSoapSerializer(&pIWSSZ);\n");
        c_writer.write("\tif (!pIWSSZ)\n");
        c_writer.write("\t\treturn AXIS_FAIL;\n\n");
        
        c_writer.write("\tIWrapperSoapDeSerializer* pIWSDZ = NULL;\n");
        c_writer.write("\tmc->getSoapDeSerializer(&pIWSDZ);\n");
        c_writer.write("\tif (!pIWSDZ)\n");
        c_writer.write("\t\treturn AXIS_FAIL;\n\n");

        c_writer.write("\t// check whether we have got correct message\n");
        c_writer.write("\tif (AXIS_SUCCESS != pIWSDZ->checkMessageBody(\""
                + minfo.getInputMessage().getLocalPart() + "\", \""
                + minfo.getInputMessage().getNamespaceURI() + "\"))\n");
        c_writer.write("\t\treturn AXIS_FAIL;\n\n");

        if (minfo.getOutputMessage() != null)
        {
            c_writer.write("\tpIWSSZ->createSoapMethod(\""
                    + minfo.getOutputMessage().getLocalPart() + "\", \""
                    + minfo.getOutputMessage().getNamespaceURI() + "\");\n");
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
                paraTypeName = CUtils.getSimpleType(type.getBaseType());
            else if (param.isArray())
                paraTypeName = CUtils.getClassNameFromParamInfoConsideringArrays(param,wscontext);
            else
                paraTypeName = param.getLangName();

            elementName = param.getElementNameAsSOAPString();
            if (type != null && type.isSimpleType())
            {
                String splatPtr = " ";
                String splatDeref = " ";
                
                if (!CUtils.isPointerType(type.getLanguageSpecificName()))
                {
                    if (param.isNillable() || param.isOptional())
                        splatPtr   = " * ";
                    else 
                        splatDeref = " * ";
                }
                
                c_writer.write("\t" + paraTypeName + splatPtr + "v" + i + " =" + splatDeref
                        + "(pIWSDZ->" + CUtils.getDeserializerMethodName(paraTypeName,false)
                        + "(\"" + elementName + "\",0));\n");
            }
            else if ((CUtils.isSimpleType(param.getLangName())))
            {
                //for simple types    
                if (param.isArray())
                {
                    String containedType = CUtils.getSimpleType(type.getName());
                    
                    c_writer.write("\n\t" + containedType + "_Array * v" + i +" = new " + containedType + "_Array();\n");
                    c_writer.write("\t"
                            + "Axis_Array * RetArray" + i + " = pIWSDZ->getBasicArray("
                            + CUtils.getXSDEnumeratorForType(containedType)
                            + ", \"" + elementName + "\",0);\n");
                    c_writer.write ("\tv" + i + "->clone(*RetArray"+ i + ");\n");
                    c_writer.write ("\tAxis::AxisDelete( (void *)RetArray" + i + ", XSD_ARRAY);\n\n");
                }
                else if (CUtils.isPointerType(paraTypeName))
                {
                    c_writer.write("\n\t" + paraTypeName + " v" + i + " = NULL;\n");
                    if (param.isOptional())
                    {
                        c_writer.write("\tconst char * elementName" + i + " = pIWSDZ->peekNextElementName();\n");
                        c_writer.write("\tif ( strcmp( elementName" + i + ", \"" + elementName + "\" ) == 0)\n");
                        c_writer.write("\t{\n");
                    }
                    c_writer.write("\t" + paraTypeName + " value" + i + " = pIWSDZ->"
                        + CUtils.getDeserializerMethodName(paraTypeName,false)
                        + "(\"" + elementName + "\",0);\n");
                    c_writer.write("\tif ( value" + i + " )\n");
                    c_writer.write("\t{\n");
                    c_writer.write("\t\tv" + i + " = new char[ strlen( value" + i + ") + 1 ];\n");
                    c_writer.write("\t\tstrcpy( v" + i + ", value" + i + ");\n");
                    c_writer.write("\t\tAxis::AxisDelete( (void *) value" + i + ", " + CUtils.getXSDEnumeratorForType(paraTypeName) + " );\n");
                    c_writer.write("\t}\n");
                    if (param.isOptional())
                        c_writer.write("\t}\n");
                }
                else if (param.isNillable()  || param.isOptional())
                {
                    c_writer.write("\n\t" + paraTypeName + " * v" + i + " = NULL;\n");
                    if (param.isOptional())
                    {
                        c_writer.write("\tconst char * elementName" + i + " = pIWSDZ->peekNextElementName();\n");
                        c_writer.write("\tif (strcmp( elementName" + i + ", \"" + elementName + "\" ) == 0)\n");
                        c_writer.write("\t{\n");
                    }
                    c_writer.write("\t" + paraTypeName + " * pValue" + i + " = pIWSDZ->"
                            + CUtils.getDeserializerMethodName(paraTypeName,false)
                            + "(\"" + elementName + "\",0);\n");
                    c_writer.write("\tif (pValue" + i +")\n");
                    c_writer.write("\t{\n");
                    c_writer.write("\t\tv" + i + " = new " + paraTypeName + "();\n");
                    c_writer.write("\t\t*v" + i + " = *pValue" + i + ";\n");
                    c_writer.write("\t\tAxis::AxisDelete( (void *) pValue" + i + ", " + CUtils.getXSDEnumeratorForType(paraTypeName) + ");\n");
                    c_writer.write("\t}\n");
                    if (param.isOptional())
                        c_writer.write("\t}\n");
                }
                else
                {
                    c_writer.write("\n\t" + paraTypeName + " v" + i);
                    String typeInitValue = CUtils.getInitValueForType(paraTypeName);
                    if (typeInitValue != null)
                        c_writer.write(" = " + typeInitValue);

                    c_writer.write(";\n");
                    c_writer.write("\t"
                            + paraTypeName + " * pValue" + i + " = pIWSDZ->"
                            + CUtils.getDeserializerMethodName(paraTypeName,false) + "(\""
                            + elementName + "\", 0);\n");
                    c_writer.write("\tif (pValue" + i + ")\n");
                    c_writer.write("\t{\n");
                    c_writer.write("\t\tv" + i + " = *pValue" + i + ";\n");
                    c_writer.write("\t\tAxis::AxisDelete( (void *) pValue"
                            + i + ", " + CUtils.getXSDEnumeratorForType(paraTypeName)+ ");\n");
                    c_writer.write("\t}\n");
                }
            }
            else if ((type != null) && type.isArray())
            {
                Type arrayType = CUtils.getArrayType(type);
                QName qname = arrayType.getName();
                String containedType = null;
                if (CUtils.isSimpleType(qname))
                {
                    containedType = CUtils.getSimpleType(qname);
                    c_writer.write("\n\t" + outparamType + "_Array * v" + i +" = new " + outparamType + "_Array();\n");
                    c_writer.write("\t"
                        + "Axis_Array * RetArray" + i + " = pIWSDZ->getBasicArray("
                        + CUtils.getXSDEnumeratorForType(containedType)
                        + ", \"" + elementName + "\",0);\n");
                    c_writer.write ("\tv" + i + "->clone(*RetArray"+ i + ");\n");
                    c_writer.write ("\tAxis::AxisDelete( (void *)RetArray" + i + ", XSD_ARRAY);\n\n");
                }
                else if (arrayType.isSimpleType())
                {
                    containedType = CUtils.getSimpleType(arrayType.getBaseType());
                    c_writer.write("\n\t" + outparamType + " * v" + i +" = new " + outparamType + "();\n");
                    c_writer.write("\t"
                        + "Axis_Array * RetArray" + i + " = pIWSDZ->getBasicArray("
                        + CUtils.getXSDEnumeratorForType(containedType)
                        + ", \"" + elementName + "\",0);\n");
                    c_writer.write ("\tv" + i + "->clone(*RetArray"+ i + ");\n");
                    c_writer.write ("\tAxis::AxisDelete( (void *)RetArray" + i + ", XSD_ARRAY);\n\n");
                }
                else
                {
                    containedType = qname.getLocalPart();
                    c_writer.write("\n\t" + paraTypeName + " * v" + i +" = new " + paraTypeName + "();\n");
                    c_writer.write("\t"
                        + "pIWSDZ->getCmplxArray(v" + i + ", (void*)Axis_DeSerialize_" + containedType
                        + ",\n\t\t(void*)Axis_Create_" + containedType
                        + ", (void*)Axis_Delete_" + containedType
                        + ",\n\t\t \"" + elementName + "\", Axis_URI_" + containedType + ");\n");
                }
            }
            else if (param.isAnyType())
            {
                c_writer.write("\t" + paraTypeName + " *v" + i + " = (" + paraTypeName
                        + "*)pIWSDZ->getAnyObject();\n");
            }
            else
            {
                //for complex types 
                c_writer.write("\t" + paraTypeName + " *v" + i + " = (" + paraTypeName
                        + "*)pIWSDZ->getCmplxObject((void*)Axis_DeSerialize_" + paraTypeName
                        + "\n\t\t, (void*)Axis_Create_" + paraTypeName
                        + ", (void*)Axis_Delete_" + paraTypeName
                        + "\n\t\t, \"" + elementName
                        + "\", Axis_URI_" + paraTypeName + ");\n");
            }
        } // for loop
        
        c_writer.write("\n\tif (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus()))\n");
        c_writer.write("\t\treturn nStatus;\n\n");
        
        // Multiples parameters so fill the methods prototype
        if (isAllTreatedAsOutParams)
        {
            ArrayList paramsC = (ArrayList) minfo.getOutputParameterTypes();
            for (int i = 0; i < paramsC.size(); i++)
            {
                ParameterInfo param = (ParameterInfo) paramsC.get(i);
                String typeName = CUtils.getClassNameFromParamInfoConsideringArrays(
                                    (ParameterInfo) paramsC.get(i), wscontext);
                c_writer.write("\t" + typeName);
                
                if ( (param.isOptional() || param.isNillable()) 
                        && CUtils.isSimpleType(typeName) 
                        && !CUtils.isPointerType(typeName) && !param.isArray())
                    c_writer.write(" *");
                c_writer.write(" out" + i + ";\n");
            }
        }
        
        c_writer.write("\ttry\n\t{\n"); //nithya
        if (returntype != null)
        { 
            /* Invoke the service when return type not void */
            returnParamName = returntype.getElementNameAsSOAPString();
            c_writer.write("\t\t" + outparamType);
            if ((outparamType.lastIndexOf ("_Array") > 0)
                    ||(!returntypeisarray 
                            && (!returntypeissimple
                                    || (returntypeissimple 
                                            && (returntype.isNillable() || returntype.isOptional())
                                            && !(CUtils.isPointerType(retType.getLanguageSpecificName()))))))
                c_writer.write(" *");
            
            c_writer.write(" ret = " + "pWs->" + methodName + "(");
            if (0 < paramsB.size())
            {
                for (int i = 0; i < paramsB.size() - 1; i++)
                    c_writer.write("v" + i + ",");

                c_writer.write("v" + (paramsB.size() - 1));
            }

            c_writer.write(");\n");
            /* set the result */
            if (returntypeissimple)
            {
                if (returntype.isArray())
                {
                    String containedType = CUtils.getSimpleType(retType.getName());
                    c_writer.write("\t\tnStatus = pIWSSZ->addOutputBasicArrayParam(ret, "
                            + CUtils.getXSDEnumeratorForType(containedType) + ", \""
                            + returnParamName + "\");\n");
                    c_writer.write("\t\tdelete ret;\n");
                    c_writer.write("\t\treturn nStatus;\n");
                }
                else
                {
                    String returnParamTypeName = retType.getLanguageSpecificName();
                    if (returntype.isNillable()
                            || returntype.isOptional()
                            || CUtils.isPointerType(returnParamTypeName))
                    {
                        c_writer.write("\t\treturn pIWSSZ->addOutputParam(\"" + returnParamName
                            + "\", (void*)ret, " + CUtils.getXSDEnumeratorForType(outparamType) + ");\n");
                    }
                    else
                    {
                        c_writer.write("\t\treturn pIWSSZ->addOutputParam(\"" + returnParamName
                            + "\", (void*)&ret, " + CUtils.getXSDEnumeratorForType(outparamType) + ");\n");
                    }
                }
            }
            else if (returntypeisarray)
            {
                Type arrayType = CUtils.getArrayType(retType);
                QName qname = arrayType.getName();
                String containedType = null;
                if (CUtils.isSimpleType(qname))
                {
                    containedType = CUtils.getSimpleType(qname);
                    c_writer.write("\t\tnStatus = pIWSSZ->addOutputBasicArrayParam(ret, "
                                + CUtils.getXSDEnumeratorForType(containedType)
                                + ", \"" + returnParamName + "\");\n");
                    c_writer.write("\t\tdelete ret;\n");
                    c_writer.write("\t\treturn nStatus;\n");
                }
                else if (arrayType.isSimpleType())
                {
                    containedType = CUtils.getSimpleType(arrayType.getBaseType());
                    c_writer.write("\t\tnStatus = pIWSSZ->addOutputBasicArrayParam(ret, "
                            + CUtils.getXSDEnumeratorForType(containedType)
                            + ", \"" + returnParamName + "\");\n");
                    c_writer.write("\t\tdelete ret;\n");
                    c_writer.write("\t\treturn nStatus;\n");
                }
                else
                {
                    containedType = qname.getLocalPart();
                    c_writer.write("\t\tnStatus = pIWSSZ->addOutputCmplxArrayParam(ret,"
                            + "(void*) Axis_Serialize_" + containedType
                            + ", (void*) Axis_Delete_" + containedType
                            + ", \"" + returnParamName
                            + "\", Axis_URI_" + containedType + ");\n");
                    c_writer.write("\t\tdelete ret;\n");
                    c_writer.write("\t\treturn nStatus;\n");
                }
            }
            else if (returntype.isAnyType())
                c_writer.write( "\t\treturn pIWSSZ->addOutputAnyObject(ret);\n");
            else
            {
                //complex type
                c_writer.write("\t\treturn pIWSSZ->addOutputCmplxParam(ret, (void*)Axis_Serialize_"
                        + outparamType
                        + ", (void*)Axis_Delete_" + outparamType
                        + ", \"" + returnParamName + "\", Axis_URI_" + outparamType + ");\n");
            }
        }
        else if (isAllTreatedAsOutParams)
        {
            c_writer.write("\tpWs->" + methodName + "(");
            if (0 < paramsB.size())
                for (int i = 0; i < paramsB.size(); i++)
                    c_writer.write("v" + i + ",");
            
            ArrayList paramsC = (ArrayList) minfo.getOutputParameterTypes();
            for (int i = 0; i < paramsC.size() - 1; i++)
                c_writer.write("&out" + i + ",");

            c_writer.write("&out" + (paramsC.size() - 1));
            c_writer.write(");\n");
            paramsC = (ArrayList) minfo.getOutputParameterTypes();
            for (int i = 0; i < paramsC.size(); i++)
            {
                ParameterInfo param = (ParameterInfo) paramsC.get(i);
                retType = wscontext.getTypemap().getType(param.getSchemaName());
                if (retType != null)
                {
                    if (retType.isSimpleType())
                    {
                        returntypeissimple = true;
                        outparamType =
                            CUtils.getSimpleType(retType.getBaseType());
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
                
                returnParamName = param.getElementNameAsSOAPString();
                
                if (returntypeissimple)
                {
                    if (param.isArray())
                    {
                        String containedType = CUtils.getSimpleType(retType.getName());
                        c_writer.write("\treturn pIWSSZ->addOutputBasicArrayParam((Axis_Array*)(&out" + i + "),"
                                + CUtils.getXSDEnumeratorForType(containedType)
                                + ", \"" + returnParamName + "\");\n");
                    }
                    else if (CUtils.isPointerType(outparamType) 
                                || param.isOptional() 
                                || param.isNillable())
                    {
                        if (param.isOptional())
                        {
                            c_writer.write("\tif (out" + i + ")\n");
                            c_writer.write("\t{\n");
                            c_writer.write("\t");
                        }
                        
                        c_writer.write("\tpIWSSZ->addOutputParam(\""
                                    + returnParamName
                                    + "\", (void*)out" + i + ", "
                                    + CUtils.getXSDEnumeratorForType(outparamType) + ");\n");
                        
                        if (param.isOptional())
                            c_writer.write("\t}\n");
                    }
                    else
                    {
                        c_writer.write("\tpIWSSZ->addOutputParam(\""
                                    + returnParamName
                                    + "\", (void*)&out" + i + ", "
                                    + CUtils.getXSDEnumeratorForType(outparamType) + ");\n");
                    }
                }
                else if (returntypeisarray)
                {
                    Type arrayType = CUtils.getArrayType(retType);
                    QName qname = arrayType.getName();
                    String containedType = null;
                    
                    if (CUtils.isSimpleType(qname))
                    {
                        containedType = CUtils.getSimpleType(qname);
                        c_writer.write("\tpIWSSZ->addOutputBasicArrayParam((Axis_Array*)(&out"
                                + i + ")," + CUtils.getXSDEnumeratorForType( containedType)
                                + ", \"" + returnParamName + "\");\n");
                    }
                    else if (arrayType.isSimpleType())
                    {
                        containedType = CUtils.getSimpleType(arrayType.getBaseType());
                        c_writer.write("\tpIWSSZ->addOutputBasicArrayParam((Axis_Array*)(&out"
                                + i + ")," + CUtils.getXSDEnumeratorForType(containedType)
                                + ", \"" + returnParamName + "\");\n");
                    }
                    else
                    {
                        containedType = qname.getLocalPart();
                        c_writer.write("\tpIWSSZ->addOutputCmplxArrayParam((Axis_Array*)(&out" + i  + "),"
                                + "(void*) Axis_Serialize_" + containedType
                                + ", (void*) Axis_Delete_" + containedType
                                + ", \"" + returnParamName + "\", Axis_URI_" + containedType + ");\n");
                    }
                }
                else if (param.isAnyType())
                    c_writer.write("\tpIWSSZ->addOutputAnyObject(out" + i + ");\n");
                else
                {
                    if (param.isOptional())
                    {
                        c_writer.write("\tif (out" + i + ")\n");
                        c_writer.write("\t{\n");
                        c_writer.write("\t");
                    }
                    //complex type
                    c_writer.write("\tpIWSSZ->addOutputCmplxParam(out" + i
                            + ", (void*)Axis_Serialize_" + outparamType
                            + ", (void*)Axis_Delete_" + outparamType
                            + ", \""  + returnParamName
                            + "\", Axis_URI_" + outparamType + ");\n");
                    
                    if (param.isOptional())
                        c_writer.write("\t}\n");
                }
            }
            c_writer.write("\treturn AXIS_SUCCESS;\n");
        }
        else
        { 
            //method does not return anything Invoke the service when return type is void
            c_writer.write("\tpWs->" + methodName + "(");
            if (0 < paramsB.size())
            {
                for (int i = 0; i < paramsB.size() - 1; i++)
                    c_writer.write("v" + i + ",");

                c_writer.write("v" + (paramsB.size() - 1));
            }
            c_writer.write(");\n");
            c_writer.write("\treturn AXIS_SUCCESS;\n");
        }
        
        c_writer.write("\t}\n"); //nithya          
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
                faultType = CUtils.getClassNameFromParamInfoConsideringArrays(par,wscontext);
                writeExceptions(faultType, faultInfoName, paramName, langName);
            }
        }
        
        // Handle SOAP faults not specified within the WSDL (ie OtherFaultException)
        c_writer.write("\tcatch(OtherFaultException * pObjFault)\n");
        c_writer.write("\t{\n");
        c_writer.write("\t\tif (pObjFault)\n");
        c_writer.write("\t\t{\n");
        c_writer.write("\t\t\tpIWSSZ->createSoapFault(\"\", \"\", pObjFault->getFaultCode(), pObjFault->getFaultString());\n");
        c_writer.write("\t\t\tpIWSSZ->addFaultDetail(pObjFault->getFaultDetail());\n");
        c_writer.write("\t\t\tdelete pObjFault;\n");
        c_writer.write("\t\t\tthrow AxisServiceException(AXISC_SERVICE_THROWN_EXCEPTION);\n");
        c_writer.write("\t\t}\n");
        c_writer.write("\t\treturn AXIS_FAIL;\n");
        c_writer.write("\t}\n");
        
        // Handle generic exception, placing the message into a generic SOAP fault
        c_writer.write("\tcatch (exception & e)\n");
        c_writer.write("\t{\n");
        c_writer.write("\t\tpIWSSZ->createSoapFault(\"\", \"\", \"Server\", e.what());\n");
        c_writer.write("\t\tthrow AxisServiceException(AXISC_SERVICE_THROWN_EXCEPTION);\n");
        c_writer.write("\t\treturn AXIS_FAIL;\n");
        c_writer.write("\t}\n");
        
        // Handle any other exception
        c_writer.write("\tcatch(...)\n");
        c_writer.write("\t{\n");
        c_writer.write("\t\treturn AXIS_FAIL;\n");
        c_writer.write("\t}\n");

        c_writer.write("}\n");
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
            c_writer.write("\tcatch(" + faulttype + " pObjFault)\n");
            c_writer.write("\t{\n");
            c_writer.write("\t\tif (pObjFault)\n");
            c_writer.write("\t\t{\n");
            c_writer.write("\t\t\tpIWSSZ->createSoapFault(\"" + faultInfoName
                    + "\", \"" + wscontext.getWrapperInfo().getTargetNameSpaceOfWSDL()
                    + "\",\"AxisC++ Faultcode\", \"Custom Out of bound exception\");\n");

            c_writer.write("\t\t\tpIWSSZ->addFaultDetail(pObjFault, (void*) Axis_Serialize_" + langName + ",\n");
            c_writer.write("\t\t\t\t(void*) Axis_Delete_" + langName
                    + ",\"" + faultInfoName + "\", Axis_URI_" + langName + ");\n");
            c_writer.write("\t\t\tthrow AxisServiceException(AXISC_SERVICE_THROWN_EXCEPTION);\n");
            c_writer.write("\t\t}\n");
            c_writer.write("\t\treturn AXIS_FAIL;\n");
            c_writer.write("\t}\n");
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
    }
}
