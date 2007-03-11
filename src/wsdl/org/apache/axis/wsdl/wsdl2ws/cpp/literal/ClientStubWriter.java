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


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* CHANGES TO FILE MAY NEED TO BE PROPAGATED TO THE                   */
/* C-EQUIVALENT FILE IN SUPPORT OF THE C-BINDING INTERFACES.          */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

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
    public ClientStubWriter (WebServiceContext wscontext) throws WrapperFault
    {
        super (wscontext);
    }

    /**
     * This method genarate methods that wraps the each method of the service
     * @param MethodInfo
     * @throws IOException
     * @throws WrapperFault
     * 
     */

    public void writeMethodInWrapper (MethodInfo minfo) throws WrapperFault, IOException
    {
        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
        /* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
        /* ----------------------------------------------------------------   */
        /* CHANGES TO FILE MAY NEED TO BE PROPAGATED TO THE                   */
        /* C-EQUIVALENT FILE IN SUPPORT OF THE C-BINDING INTERFACES.          */
        /* ----------------------------------------------------------------   */
        /* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */   
        
        boolean isAllTreatedAsOutParams = false;
        ParameterInfo returntype = null;
        int noOfOutParams = minfo.getOutputParameterTypes().size();
        
        if (0 == noOfOutParams)
            returntype = null;
        else if (1 == noOfOutParams)
            returntype = (ParameterInfo) minfo.getOutputParameterTypes().iterator().next();
        else
            isAllTreatedAsOutParams = true;
      
        Collection params = minfo.getInputParameterTypes ();
        String methodName = minfo.getMethodname ();
        Type retType = null;
        boolean returntypeissimple = false;
        boolean returntypeisarray = false;
        String outparamType = null;
        
        if (returntype != null)
            retType = wscontext.getTypemap ().getType (returntype.getSchemaName ());
        
        if (retType != null)
        {
            if (retType.isSimpleType ())
                outparamType = CUtils.getclass4qname (retType.getBaseType ());
            else
            {
                outparamType = WrapperUtils.getClassNameFromParamInfoConsideringArrays (returntype, wscontext);
                returntypeisarray = (outparamType.lastIndexOf ("_Array") > 0);
            }
            
            returntypeisarray |= retType.isArray ();
        }
        else if (returntype != null)
            outparamType = returntype.getLangName ();
        
        if (returntype != null)
            returntypeissimple = CUtils.isSimpleType (outparamType);

        //=============================================================================
        // Generate method prototype
        //=============================================================================        

        CUtils.printMethodComment(writer, "This method wraps the service method " + methodName + ".");
        
        //method signature
        String paramTypeName;
        boolean typeisarray = false;
        boolean typeissimple = false;
        Type type;
        
        if (returntype == null)
            writer.write ("void");
        else if (returntypeissimple
                    && (!(returntype.isNillable() || returntype.isOptional()) 
                            || CUtils.isPointerType(outparamType)))
            writer.write (outparamType);
        else if (outparamType.lastIndexOf ("*") > 0)
            writer.write (outparamType);
        else 
            writer.write (outparamType + "*");

        writer.write (" " + classname + "::\n" + methodName + "(");
        ArrayList paramsB = (ArrayList) params;
        ParameterInfo paramtype = null;
        if (0 < paramsB.size ())
        {
            type = wscontext.getTypemap ().getType (((ParameterInfo) paramsB.get (0)).getSchemaName ());
            paramtype = (ParameterInfo) paramsB.get (0);
            String baseTypeName = null;
            if (type != null)
            {
                if (type.isSimpleType ())
                {        
                    baseTypeName = CUtils.getclass4qname (type.getBaseType ());
                    paramTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(paramtype, wscontext);
                }
                else
                {
                    paramTypeName = type.getLanguageSpecificName ();
                    if (CUtils.isSimpleType (paramTypeName))
                        paramTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(paramtype, wscontext);

                    typeisarray = (paramTypeName.lastIndexOf ("_Array") > 0);
                    if (!typeisarray)
                        paramTypeName = type.getLanguageSpecificName ();

                    typeissimple = CUtils.isSimpleType (paramTypeName);
                }
                typeisarray |= type.isArray ();
            }
            else
            {
                paramTypeName = ((ParameterInfo) paramsB.get (0)).getLangName ();
                paramtype = (ParameterInfo) paramsB.get (0);
                typeisarray = false;
            }
            
            if (baseTypeName == null)
                baseTypeName = paramTypeName;

            typeissimple = CUtils.isSimpleType (baseTypeName);
            if (paramtype.getType().isAttachment())
                writer.write("ISoapAttachment *Value0");
            else if (typeissimple
                    && (!(((ParameterInfo) paramsB.get (0)).isNillable () || ((ParameterInfo) paramsB.get (0)).isOptional())
                            || CUtils.isPointerType(baseTypeName)))
            {
                writer.write (paramTypeName + " Value0");
            }
            else if (paramTypeName.lastIndexOf ("*") > 0)
                writer.write (paramTypeName + " Value0");
            else //for AnyType too
                writer.write (paramTypeName + "* Value0");

            for (int i = 1; i < paramsB.size (); i++)
            {
                baseTypeName = null;
                type = wscontext.getTypemap ().getType (((ParameterInfo) paramsB.get (i)).getSchemaName ());
                paramtype = (ParameterInfo) paramsB.get (i);
                if (type != null)
                {
                    if (type.isSimpleType ())
                    {        //schema defined simpleType
                        baseTypeName = CUtils.getclass4qname (type.getBaseType ());
                        paramTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(paramtype, wscontext);
                    }
                    else
                    {
                        paramTypeName = type.getLanguageSpecificName ();
                        if (CUtils.isSimpleType (paramTypeName))
                            paramTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(paramtype, wscontext);

                        typeisarray = (paramTypeName.lastIndexOf ("_Array") > 0);
                        if (!typeisarray)
                            paramTypeName = type.getLanguageSpecificName ();       
                    }
                    
                    typeisarray |= type.isArray ();
                    typeissimple = CUtils.isSimpleType (paramTypeName);
                }
                else
                {
                    paramTypeName = ((ParameterInfo) paramsB.get (i)).getLangName ();
                    paramtype = (ParameterInfo) paramsB.get (i);
                    typeisarray = false;
                }
                
                if (baseTypeName == null)
                    baseTypeName = paramTypeName;

                typeissimple = CUtils.isSimpleType (baseTypeName);
                if (paramtype.getType().isAttachment())
                       writer.write(", ISoapAttachment *Value" + i);
                else if (typeissimple
                            && (!(((ParameterInfo) paramsB.get (i)).isNillable () 
                                    || ((ParameterInfo) paramsB.get (i)).isOptional())
                                        || CUtils.isPointerType(baseTypeName)))
                    writer.write (", " + paramTypeName + " Value" + i);
                else if (paramTypeName.lastIndexOf ("*") > 0)
                    writer.write (", " + paramTypeName + " Value" + i);
                else //for AnyType too
                    writer.write (", " + paramTypeName + "* Value" + i);
            } // end for loop
        } // end if (0 < paramsB.size ())
    
        // Multiples parameters so fill the methods prototype
        ArrayList paramsC = (ArrayList) minfo.getOutputParameterTypes ();
        if (isAllTreatedAsOutParams)
            for (int i = 0; i < paramsC.size (); i++)
            {
                String baseTypeName = null;
                type = wscontext.getTypemap ().getType (((ParameterInfo) paramsC.get (i)).getSchemaName ());
    
                ParameterInfo param = (ParameterInfo) paramsC.get (i);
                String    paramType = WrapperUtils.getClassNameFromParamInfoConsideringArrays (param, wscontext);
                if (type.isSimpleType())
                    baseTypeName = CUtils.getclass4qname(type.getBaseType());
                else
                    baseTypeName = paramType;
                
                boolean bTypeHasStar = paramType.endsWith("*");
                
                if (paramsB.size()!=0 || 0!=i)
                    writer.write(", ");
                
                writer.write("AXIS_OUT_PARAM " + paramType);
                if (CUtils.isSimpleType(baseTypeName))
                {
                    if ((param.isOptional() || param.isNillable()) && !CUtils.isPointerType(baseTypeName))
                    {
                        if (bTypeHasStar)
                            writer.write(" *");
                        else
                            writer.write(" **");
                    }
                    else if (CUtils.isPointerType(baseTypeName) || !bTypeHasStar)
                        writer.write(" *");
                }
                else if(bTypeHasStar)
                    writer.write(" *");
                else
                    writer.write(" **");
                
                writer.write(" OutValue" + i);
            } // end for-loop
    
        writer.write (")\n{\n");
        
        //=============================================================================
        // Generate global variables (outside of try block)
        //=============================================================================   
        
        if (returntype != null)
        {
            writer.write ("\t");
    
            if (returntypeisarray)
                writer.write (outparamType + " * RetArray = new " + outparamType + "();\n");
            else if (!returntypeissimple)
            {        
                //for AnyType too
                if (outparamType.lastIndexOf ("*") > 0)
                    writer.write (outparamType + " pReturn = NULL;\n");
                else
                    writer.write (outparamType + "* pReturn = NULL;\n");
            }
            else if ((returntype.isNillable () || returntype.isOptional())
                        && !(CUtils.isPointerType(outparamType)))
                writer.write (outparamType + "* Ret = NULL;\n");
            else
            {
                String initValue = CUtils.getInitValue (outparamType);
                if (initValue != null)
                    writer.write (outparamType + " Ret = " + initValue + ";\n");
                else if (CUtils.getXSDTypeForBasicType( outparamType).equals("XSD_DATETIME")
                        || CUtils.getXSDTypeForBasicType( outparamType).equals("XSD_DATE")
                        || CUtils.getXSDTypeForBasicType( outparamType).equals("XSD_TIME"))
                {
                    writer.write (outparamType + " Ret;\n");
                    writer.write ("\tmemset(&Ret,0,sizeof(" + outparamType + "));\n");
                }
                else
                    writer.write (outparamType + " Ret;\n");
            }
        }
        
        writer.write ("\tconst char* pcCmplxFaultName = NULL;\n\n");
        
        //=============================================================================
        // Generate try block and method logic
        //=============================================================================        
                
        writer.write ("\ttry\n\t{\n");
    
        CUtils.printBlockComment(writer, "Initialize client engine, set SOAP version, SOAPAction, operation, etc.");
        
        writer.write("\t\tif (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER" + "))\n");
        writer.write("\t\t\treturn ");
        if (returntype != null)
            writer.write ((returntypeisarray ? "RetArray" : returntypeissimple ? "Ret" : "pReturn") + ";\n");
        else
            writer.write (";\n");
        writer.write ("\n");
        
        writer.write ("\t\tif (NULL==m_pCall->getTransportProperty(\"SOAPAction\",false))\n");
        writer.write ("\t\t\tm_pCall->setTransportProperty(SOAPACTION_HEADER , \""
               + minfo.getSoapAction () + "\");\n");
        writer.write("\n");
        
        writer.write ("\t\tm_pCall->setSOAPVersion(SOAP_VER_1_1);\n");
        //TODO check which version is it really.
        
        if( minfo.getInputMessage() != null)
        {
            writer.write( "\t\tm_pCall->setOperation(\"" 
                    + minfo.getInputMessage().getLocalPart() + "\", \"" 
                    + minfo.getInputMessage().getNamespaceURI() + "\");\n");
        }
        
        // Add attributes to soap method
        boolean commentIssued=false;
        for (int i = 0; i < paramsB.size (); i++)
        {
            ParameterInfo param = (ParameterInfo) paramsB.get (i);
            
            // Skip non-attributes
            if (!param.isAttribute ())
                continue;
            
            if (!commentIssued)
            {
                commentIssued = true;
                CUtils.printBlockComment(writer, "Add attributes to soap method.");
            }
            else
                writer.write ("\n");
            
            // Process attributes
            String elementType = param.getElementName ().getLocalPart ();
    
            if ("string".equals (elementType))
            {
                writer.write ("\t\tm_pCall->setSOAPMethodAttribute(\""
                      + param.getParamNameAsSOAPString () + "\", \"\", Value" + i + ");\n");
            }
            else if ("int".equals (elementType))
            {
                writer.write ("\t\t{\n");
                writer.write ("\t\t\tchar buffer[20];\n");
                writer.write ("\t\t\tsprintf(buffer,\"%d\", Value" + i + ");\n");
                writer.write ("\t\t\tm_pCall->setSOAPMethodAttribute(\"" +
                       param.getParamNameAsSOAPString () + "\", \"\", buffer);\n");
                writer.write ("\t\t}\n");
            }
        } // end for-loop
    
        //new calls from stub base
        CUtils.printBlockComment(writer, "Apply SSL configuration properties and user-set SOAP headers.");
        writer.write ("\t\tincludeSecure();\n");
        writer.write ("\t\tapplyUserPreferences();\n");

        // Process elements
        commentIssued=false;
        String tab2;
        for (int i = 0; i < paramsB.size (); i++)
        {
            tab2 = "";
            ParameterInfo param = (ParameterInfo) paramsB.get (i);
    
            // Ignore attributes
            if (param.isAttribute ())
                continue;

            if (!commentIssued)
            {
                commentIssued = true;
                CUtils.printBlockComment(writer, "Process parameters.");
            }
            else
                writer.write ("\n");
            
            // add elements
            type = wscontext.getTypemap ().getType (param.getSchemaName ());
            if (type != null)
            {
                if (type.isSimpleType ())
                    paramTypeName = CUtils.getclass4qname (type.getBaseType ());
                else
                {
                    paramTypeName = type.getLanguageSpecificName ();
                    if (CUtils.isSimpleType (paramTypeName))
                        paramTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(param,wscontext);
                    
                    typeisarray = (paramTypeName.lastIndexOf ("_Array") > 0);
                    if (!typeisarray)
                        paramTypeName = type.getLanguageSpecificName ();
                }
                
                typeisarray |= type.isArray ();
            }
            else
            {
                paramTypeName = ((ParameterInfo) paramsB.get (i)).getLangName ();
                typeisarray = false;
            }
    
            if (param.isAnyType ())
                writer.write ("\t\tm_pCall->addAnyObject(Value" + i);
            else
            {
                String parameterName = ((ParameterInfo) paramsB.get (i)).getElementNameAsSOAPString ();
                String namespace = ((ParameterInfo) paramsB.get (i)).getElementName ().getNamespaceURI ();
    
                if (((ParameterInfo)paramsB.get(i)).isOptional())
                {
                    writer.write("\t\tif (Value" + i + " != NULL)\n\t\t{\n");
                    tab2 = "\t";
                }
                
                if (namespace.length () == 0)
                {
                    writer.write (tab2 + "\t\tchar cPrefixAndParamName"
                              + i + "[" + "] = \"" + parameterName + "\";\n");
                }
                else
                {
                    int stringLength = 8 + 1 + parameterName.length () + 1;
                    writer.write (tab2 + "\t\tchar cPrefixAndParamName" + i + "[" + stringLength + "];\n");
                    writer.write (tab2 + "\t\tsprintf( cPrefixAndParamName" + i +
                              ", \"%s:" + parameterName +
                              "\", m_pCall->getNamespacePrefix(\"" +  namespace + "\"));\n");
                }
    
                if (param.getType().isAttachment())
                {
                    String attchType = param.getType().getName().getLocalPart();
                          writer.write(tab2 + "\t\tconst AxisChar *xmlSoapNsPfx" + i + 
                        " = m_pCall->getNamespacePrefix(\"" + 
                        WrapperConstants.APACHE_XMLSOAP_NAMESPACE + "\");\n");
                    writer.write(tab2 + "\t\tchar attchType" + i + "[64];\n");
                    writer.write(tab2 + "\t\tstrcpy(attchType" + i + ", xmlSoapNsPfx" + i + ");\n");
                    writer.write(tab2 + "\t\tstrcat(attchType" + i + ", \":" + attchType + "\");\n");
                    writer.write(tab2 + "\t\tIAttribute *attrs" + i + "[2];\n");
                    writer.write(tab2 + "\t\tattrs" + i + "[0] = m_pCall->createAttribute(\"type\", \"xsi\", attchType" + i + 
                        ");\n");
                    writer.write(tab2 + "\t\tattrs" + i + "[1] = m_pCall->createAttribute(xmlSoapNsPfx" + i + 
                        ", \"xmlns\", \"http://xml.apache.org/xml-soap\");\n");
                    writer.write(tab2 + "\t\tm_pCall->addAttachmentParameter(Value" + i + ", cPrefixAndParamName" + i + 
                        ", attrs" + i + ", 2");
                }
                else if (typeisarray)
                {
                    Type arrayType = WrapperUtils.getArrayType (type);
        
                    QName qname = null;
                    if (arrayType != null)
                        qname = arrayType.getName ();
                    else
                        qname = type.getName ();
                
                    if (CUtils.isSimpleType (qname))
                    {
                        // Array of simple type
                        String containedType = CUtils.getclass4qname (qname);
                        writer.write (tab2 + "\t\tm_pCall->addBasicArrayParameter(");
                        writer.write ("Value" + i + ", " +
                              CUtils.getXSDTypeForBasicType(containedType) + ", cPrefixAndParamName" + i);
                    }
                    else if (arrayType != null && arrayType.isSimpleType ())
                    {
                        String containedType = CUtils.getclass4qname (arrayType.getBaseType ());
                        writer.write (tab2 + "\t\tm_pCall->addBasicArrayParameter(");
                        writer.write ("Value" + i + ", " +
                                  CUtils.getXSDTypeForBasicType(containedType) +
                                  ", cPrefixAndParamName" + i);
                    }
                    else
                    {
                        // Array of complex type
                        String containedType = qname.getLocalPart ();
                        writer.write (tab2 + "\t\tm_pCall->addCmplxArrayParameter(");
                        writer.write ("Value" + i +
                                  ", (void*)Axis_Serialize_" + containedType +
                                  ", (void*)Axis_Delete_" + containedType +
                                  ", \"" + parameterName + "\"" + ", ");
                        
                        if (namespace.length () == 0)
                            writer.write ("NULL");
                        else
                            writer.write ("Axis_URI_" + containedType);
                    }
                }
                else if (CUtils.isSimpleType (paramTypeName))
                {
                    if (param.isNillable () 
                            || param.isOptional()
                            || CUtils.isPointerType(paramTypeName))
                    {
                        writer.write (tab2 + "\t\tm_pCall->addParameter(");
                        writer.write ("(void*)Value" + i + ", cPrefixAndParamName" + i
                                  + ", " + CUtils.getXSDTypeForBasicType(paramTypeName));
                    }
                    else
                    {
                        writer.write (tab2 + "\t\tm_pCall->addParameter(");
                        writer.write ("(void*)&Value" + i + ", cPrefixAndParamName" + i
                                  + ", " + CUtils.getXSDTypeForBasicType(paramTypeName));
                    }
                }
                else
                {
                    // Complex Type
                    writer.write (tab2 + "\t\tm_pCall->addCmplxParameter(");
                    writer.write ("Value" + i
                          + ", (void*)Axis_Serialize_" + paramTypeName
                          + ", (void*)Axis_Delete_" + paramTypeName
                          + ", cPrefixAndParamName" + i + ", Axis_URI_" + paramTypeName);
                }              
            }

            writer.write (");\n");
            if (((ParameterInfo)paramsB.get(i)).isOptional())
                writer.write("\t\t}\n");
        } // end for-loop
        

        if (minfo.getOutputMessage () != null)
        {
            CUtils.printBlockComment(writer, "Invoke web service, send/receive operation. Handle output parameters, if any.");
            writer.write ("\t\tif (AXIS_SUCCESS == m_pCall->sendAndReceive())\n\t\t{\n");
            writer.write ("\t\t\tif(AXIS_SUCCESS == m_pCall->checkMessage(\""
                  + minfo.getOutputMessage ().getLocalPart () + "\", \""
                  + minfo.getOutputMessage ().getNamespaceURI () + "\"))\n\t\t\t{\n");
        }
        else
        {
            CUtils.printBlockComment(writer, "Invoke web service, send-only operation.");
            writer.write ("\t\tif (AXIS_SUCCESS == m_pCall->send())\n\t\t{\n");
        }
        
        if (isAllTreatedAsOutParams)
        {
            String currentParamName;
            String currentParaType;
            
            for (int i = 0; i < paramsC.size (); i++)
            {
                String baseTypeName = null;
                ParameterInfo currentType = (ParameterInfo) paramsC.get (i);
                
                type = wscontext.getTypemap ().getType (currentType.getSchemaName ());
                if (type != null)
                {
                    if (type.isSimpleType ())
                    {
                        baseTypeName = CUtils.getclass4qname (type.getBaseType ());
                        currentParaType = WrapperUtils.getClassNameFromParamInfoConsideringArrays(currentType, wscontext);
                    }
                    else
                    {
                        currentParaType = WrapperUtils.getClassNameFromParamInfoConsideringArrays(currentType, wscontext);
                        typeisarray = (currentParaType.lastIndexOf("_Array") > 0);
                    }
                    
                    typeisarray |= type.isArray ();
                }
                else
                {
                    currentParaType = ((ParameterInfo) paramsC.get (i)).getLangName ();
                    typeisarray = false;
                }
                
                if (baseTypeName == null)
                    baseTypeName = currentParaType;

                typeissimple = CUtils.isSimpleType (baseTypeName);
                currentParamName = "*OutValue" + i;
                
                // Some code need to be merged as we have some duplicated in coding here.
                if (typeisarray)
                {
                    QName qname = null;
                    if (WrapperUtils.getArrayType (type) != null)
                        qname = WrapperUtils.getArrayType (type).getName ();
                    else
                        qname = type.getName ();
                    
                    String containedType = null;
                    
                    if (CUtils.isSimpleType (qname))
                    {
                        containedType = CUtils.getclass4qname (qname);
        
                        writer.write("\n\t\t\t\tAxis_Array * pReturn" + i + " = m_pCall->getBasicArray(" + CUtils.getXSDTypeForBasicType (containedType) 
                            + ", \"" + currentType.getParamNameAsSOAPString ()
                            + "\", 0);\n\n");
                        writer.write("\t\t\t\tif( pReturn" + i + " != NULL && OutValue" + i + " != NULL)\n");
                        writer.write("\t\t\t\t{\n");
                        writer.write("\t\t\t\t\tif( *OutValue" + i + " == NULL)\n");
                        writer.write("\t\t\t\t\t\t*OutValue" + i + " = new " + currentParaType + "();\n");
                        writer.write("\t\t\t\t\telse\n");
                        writer.write("\t\t\t\t\t\t(*OutValue" + i + ")->clear();\n");
                        writer.write("\t\t\t\t\t(*OutValue" + i + ")->clone(*pReturn" + i + ");\n");
                        writer.write("\t\t\t\t}\n\n");
                        writer.write("\t\t\t\tAxis::AxisDelete( (void *) pReturn" + i + ", XSD_ARRAY);\n");
                    }
                    else
                    {
                        containedType = qname.getLocalPart ();
                        writer.write("\n\t\t\t\tif (OutValue" + i + " != NULL)\n" );
                        writer.write("\t\t\t\t{\n");
                        writer.write("\t\t\t\t\tif (" + currentParamName + " == NULL)\n");
                        writer.write("\t\t\t\t\t\t" + currentParamName + " = new " + containedType + "_Array();\n");
                        writer.write("\t\t\t\t\telse\n");
                        writer.write("\t\t\t\t\t\t(" + currentParamName + ")->clear();\n");
                        writer.write("\t\t\t\t\tm_pCall->getCmplxArray(" + currentParamName 
                              + ", (void*) Axis_DeSerialize_" + containedType
                              + ", (void*) Axis_Create_" + containedType
                              + ", (void*) Axis_Delete_" + containedType
                              + ", \"" + currentType.getElementNameAsSOAPString () 
                              + "\", Axis_URI_" + containedType + ");\n");
                        writer.write("\t\t\t\t}\n");
                        writer.write("\t\t\t\telse\n");
                        writer.write("\t\t\t\t{\n");
                        writer.write("\t\t\t\t\t// Unable to return value, but will deserialize to ensure subsequent elements can be correctly processed.\n");
                        writer.write("\t\t\t\t\t" + containedType + "_Array * pTemp" + i 
                                + " = new " + containedType + "_Array();\n");
                        writer.write("\t\t\t\t\tm_pCall->getCmplxArray(pTemp" + i 
                              + ", (void*) Axis_DeSerialize_" + containedType
                              + ", (void*) Axis_Create_" + containedType
                              + ", (void*) Axis_Delete_" + containedType
                              + ", \"" + currentType.getElementNameAsSOAPString () 
                              + "\", Axis_URI_" + containedType + ");\n");
                        writer.write("\t\t\t\t\tdelete pTemp" + i + ";\n");
                        writer.write("\t\t\t\t}\n");
                    }
                }
                else if (typeissimple)
                {
                    if( i > 0)
                        writer.write( "\n");
                    
                    if (CUtils.isPointerType(baseTypeName))
                    {
                        String xsdType =  WrapperUtils.getClassNameFromParamInfoConsideringArrays ((ParameterInfo) paramsC.get (i), wscontext);
                        
                        if( !CUtils.isPointerType(baseTypeName))
                        {
                            if (!baseTypeName.equals(currentParaType))
                                xsdType = currentParaType;

                            xsdType += " *";
                        }
                        
                        writer.write( "\t\t\t\t" + currentParaType + " pReturn" + i + " = m_pCall->" + CUtils.getParameterGetValueMethodName( baseTypeName, false) + "( \"" + currentType.getParamNameAsSOAPString() + "\", 0);\n");
                        writer.write( "\n");
                        writer.write( "\t\t\t\tif( pReturn" + i + " != NULL && OutValue" + i + " != NULL)\n");
                        writer.write( "\t\t\t\t\t{\n");
                        writer.write( "\t\t\t\t\tif( *OutValue" + i + " != NULL)\n");
                        writer.write( "\t\t\t\t\t{\n");
                        writer.write( "\t\t\t\t\t\tint\tiStringSize" + i + " = strlen( (char *) *OutValue" + i + ");\n");
                        writer.write( "\t\t\t\t\t\tint\tiStrLenValue" + i + " = strlen( pReturn" + i + ");\n");
                        writer.write( "\n");
                        writer.write( "\t\t\t\t\t\tif( iStrLenValue" + i + " > iStringSize" + i + ")\n");
                        writer.write( "\t\t\t\t\t\t{\n");
                        writer.write( "\t\t\t\t\t\t\t*OutValue" + i + " =(" + xsdType + ") new char[iStrLenValue" + i + " + 1];\n");
                        writer.write( "\t\t\t\t\t\t\tstrcpy( (char *) *OutValue" + i + ", pReturn" + i + ");\n");
                        writer.write( "\t\t\t\t\t\t}\n");
                        writer.write( "\t\t\t\t\t\telse\n");
                        writer.write( "\t\t\t\t\t\t\tstrcpy( (char *) *OutValue" + i + ", pReturn" + i + ");\n");
                        writer.write( "\t\t\t\t\t}\n");
                        writer.write( "\t\t\t\t\telse\n");
                        writer.write( "\t\t\t\t\t{\n");
                        writer.write( "\t\t\t\t\t\t*OutValue" + i + " = (" + xsdType + ") new char[strlen( pReturn" + i + ") + 1];\n");
                        writer.write( "\t\t\t\t\t\tstrcpy( (char *) *OutValue" + i + ", pReturn" + i + ");\n");
                        writer.write( "\t\t\t\t\t}\n");
                        writer.write( "\t\t\t\t}\n");
                        writer.write( "\n");
                        writer.write( "\t\t\t\tAxis::AxisDelete( (void *) pReturn" + i + ", " + CUtils.getXSDTypeForBasicType( baseTypeName) + ");\n");
                    }
                    else 
                    {
                        writer.write( "\t\t\t\t" + currentParaType + " * pReturn" + i + " = m_pCall->" + CUtils.getParameterGetValueMethodName( baseTypeName, false) + "( \"" + currentType.getParamNameAsSOAPString() + "\", 0);\n");
                        writer.write( "\n");
                        writer.write( "\t\t\t\tif( pReturn" + i + " != NULL && OutValue" + i + " != NULL)\n");
                        writer.write( "\t\t\t\t{\n");
                        
                        if (currentType.isNillable() || currentType.isOptional())
                        {
                            writer.write( "\t\t\t\t\tif( *OutValue" + i + " == NULL)\n");
                            writer.write( "\t\t\t\t\t\t*OutValue" + i + " = new " + currentParaType + "();\n");
                            writer.write( "\n");
                            writer.write( "\t\t\t\t\t*");
                        }
                        else
                            writer.write( "\t\t\t\t\t");

                        writer.write( "*OutValue" + i + " = *pReturn" + i + ";\n");
                        writer.write( "\t\t\t\t}\n");
                        writer.write( "\n");
                        writer.write( "\t\t\t\tAxis::AxisDelete( (void *) pReturn" + i + ", " + CUtils.getXSDTypeForBasicType( baseTypeName) + ");\n");
                    }
                }
                else if (currentType.isAnyType ())
                {
                    writer.write ("\t\t\t\t"
                          + currentParamName + " = *(" + currentParaType 
                          + "*)m_pCall->getAnyObject();\n");
                }
                else
                {
                    int lastIndexOfStar = currentParaType.lastIndexOf("*");
                    if (lastIndexOfStar > 0)
                        currentParaType = currentParaType.substring(0, lastIndexOfStar);

                    writer.write ("\n\t\t\t\t"
                              + currentParamName + " = (" + currentParaType
                              + "*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_" + currentParaType 
                              + ", (void*) Axis_Create_" + currentParaType 
                              + ", (void*) Axis_Delete_" + currentParaType + ",\"" 
                              + currentType.getElementNameAsSOAPString () + "\", 0);\n");
                }
            } // end for-loop for paramsC
            
            writer.write ("\t\t\t}\n");
            writer.write ("\t\t}\n");
            writer.write ("\t\tm_pCall->unInitialize();\n");
        }
        else if (returntype == null)
        {
            if (minfo.getOutputMessage () != null)
                writer.write ("\t\t\t\t/*not successful*/\n\t\t\t}\n");

            writer.write ("\t\t}\n");
            writer.write ("\t\tm_pCall->unInitialize();\n");
        }
        else if (returntypeisarray)
        {
            QName qname = null;
            if (WrapperUtils.getArrayType (retType) != null)
                qname = WrapperUtils.getArrayType (retType).getName ();
            else
                qname = retType.getName ();
            String containedType = null;
            if (CUtils.isSimpleType (qname))
            {
                containedType = CUtils.getclass4qname (qname);
                writer.write ("\t\t\t\tAxis_Array * RetAxisArray = m_pCall->getBasicArray(" 
                        + CUtils.getXSDTypeForBasicType (containedType) 
                        + ", \"" + returntype.getParamNameAsSOAPString () + "\", 0);\n");
                writer.write ("\t\t\t\tRetArray->clone(*RetAxisArray);\n");
                writer.write ("\t\t\t\tAxis::AxisDelete( (void *)RetAxisArray, XSD_ARRAY);\n");
            }
            else
            {
                containedType = qname.getLocalPart ();
                writer.write("\t\t\t\tRetArray = (" + containedType + "_Array *) m_pCall->getCmplxArray(RetArray, (void*) Axis_DeSerialize_"
                        + containedType 
                        + ", (void*) Axis_Create_" + containedType
                          + ", (void*) Axis_Delete_" + containedType
                          + ", \"" + returntype.getElementNameAsSOAPString ()
                          + "\", Axis_URI_" + containedType + ");\n");
            }
            
            writer.write ("\t\t\t}\n");
            writer.write ("\t\t}\n");
            writer.write ("\t\tm_pCall->unInitialize();\n");
            writer.write ("\t\treturn RetArray;\n");
        }
        else if (returntypeissimple)
        {
            if (returntype.isNillable ())
            {
                if( CUtils.isPointerType( outparamType))
                {
                    writer.write( "\t\t\t\t" + outparamType + " pReturn = m_pCall->" 
                            + CUtils.getParameterGetValueMethodName( outparamType, false) 
                            + "(\"" + returntype.getParamNameAsSOAPString() + "\", 0);\n");
                }
                else
                {
                    writer.write( "\t\t\t\t" + outparamType + " * pReturn = m_pCall->" 
                            + CUtils.getParameterGetValueMethodName( outparamType, false) 
                            + "(\"" + returntype.getParamNameAsSOAPString() + "\", 0);\n");
                }
                
                writer.write( "\n");
                writer.write( "\t\t\t\tif( pReturn != NULL)\n");
                writer.write( "\t\t\t\t{\n");
                if( CUtils.isPointerType(outparamType))
                {
                    writer.write( "\t\t\t\t\tRet = new char[strlen( pReturn) + 1];\n");
                    writer.write( "\t\t\t\t\tstrcpy( Ret, pReturn);\n");
                }
                else
                {
                    writer.write( "\t\t\t\t\tRet = new " + outparamType + "();\n");
                    writer.write( "\t\t\t\t\t*Ret = *pReturn;\n");
                }
                
                writer.write( "\t\t\t\t\tAxis::AxisDelete( (void *) pReturn, " + CUtils.getXSDTypeForBasicType( outparamType) + ");\n");
                writer.write( "\t\t\t\t}\n");
                writer.write( "\t\t\t}\n");
            }
            else
            {
                if (CUtils.isPointerType(outparamType))
                {
                    writer.write ("\t\t\t\t" + outparamType +
                              " pReturn = m_pCall->" +
                              CUtils.getParameterGetValueMethodName(outparamType,false) + "(\"" +
                              returntype.getParamNameAsSOAPString () + "\", 0);\n");
                    writer.write ("\t\t\t\tif(pReturn)\n");
                    writer.write ("\t\t\t\t{\n");
                    writer.write ("\t\t\t\t\tRet = new char[strlen( pReturn) + 1];\n");
                    writer.write ("\t\t\t\t\tstrcpy( Ret, pReturn);\n");
                    writer.write ("\t\t\t\t\tAxis::AxisDelete( pReturn, XSD_STRING);\n");
                    writer.write ("\t\t\t\t}\n");
                }
                else
                {
                    writer.write ("\t\t\t\t" + outparamType + " * pReturn = m_pCall->" +
                              CUtils.getParameterGetValueMethodName(outparamType, false) + "(\"" +
                              returntype.getElementNameAsSOAPString() + "\", 0);\n");
                    writer.write ("\t\t\t\tif(pReturn)\n");
                    writer.write ("\t\t\t\t{\n");
                    
                    if( CUtils.isPointerType( outparamType))
                        writer.write ("\t\t\t\t\tRet = *pReturn;\n");
                    else
                        writer.write ("\t\t\t\t\tRet = *pReturn;\n");
    
                    writer.write ("\t\t\t\t\tAxis::AxisDelete( (void *) pReturn, " + CUtils.getXSDTypeForBasicType( outparamType) + ");\n");
                    writer.write ("\t\t\t\t}\n");
                }
                
                // TODO If we unexpectedly receive a nill value, when nillable="false" we should do something appropriate, perhaps as below:
//                              writer.write("\t\t\telse");
//                              writer.write("\t\t\t\tthrow new Exception(\"Unexpected use of nill\");");
                writer.write ("\t\t\t}\n");

            }
            writer.write ("\t\t}\n");
            writer.write ("\t\tm_pCall->unInitialize();\n");
            writer.write ("\t\treturn Ret;\n");
        }
        else if (returntype.isAnyType ())
        {
            writer.write ("\t\t\t\tpReturn = (" + outparamType + "*)m_pCall->getAnyObject();\n\t\t}\n");
            writer.write ("\t\t}\n");
            writer.write ("\t\tm_pCall->unInitialize();\n");
            writer.write ("\t\treturn pReturn;\n");
        }
        else
        {
            if (outparamType.lastIndexOf ("*") > 0)
            {
                String outparamTypeBase = outparamType.substring (0,outparamType.lastIndexOf("*"));
                writer.write ("\t\t\t\tpReturn = (" + outparamType +
                          ")m_pCall->getCmplxObject((void*) Axis_DeSerialize_" + outparamTypeBase +
                          ", (void*) Axis_Create_" + outparamTypeBase +
                          ", (void*) Axis_Delete_" + outparamTypeBase + ",\"" +
                          returntype.getElementNameAsSOAPString () + "\", 0);\n\t\t\t}\n");
            }
            else
            {
                writer.write ("\t\t\t\tpReturn = (" + outparamType
                          + "*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_" + outparamType +
                          ", (void*) Axis_Create_" + outparamType +
                          ", (void*) Axis_Delete_" + outparamType + ",\"" +
                          returntype.getElementNameAsSOAPString () + "\", 0);\n\t\t\t}\n");
            }

            writer.write ("\t\t}\n");
            writer.write ("\t\tm_pCall->unInitialize();\n");
            writer.write ("\t\treturn pReturn;\n");
        }
    
        writer.write ("\t}\n");
        
        //=============================================================================
        // End of try block, beginning of catch block
        //=============================================================================                
        
        writeCatchBlock(minfo);

        //=============================================================================
        // End of method
        //=============================================================================        
                        
        writer.write ("}\n");
    }
}
