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

package org.apache.axis.wsdl.wsdl2ws.c.literal;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ClientStubWriter
    extends org.apache.axis.wsdl.wsdl2ws.c.ClientStubWriter
{
  public ClientStubWriter(WebServiceContext wscontext) throws WrapperFault
  {
      super(wscontext);
  }

  /**
   * This method genarate methods that wraps the each method of the service
   * @param MethodInfo
   * @throws IOException
   * @throws WrapperFault
   * 
   */

    public void writeMethodInWrapper(MethodInfo minfo) throws WrapperFault, IOException
    {             
        boolean isAllTreatedAsOutParams = false;
        ParameterInfo returntype = null;
        int noOfOutParams = minfo.getOutputParameterTypes().size();
        
        if (0 == noOfOutParams)
            returntype = null;
        else if (1 == noOfOutParams)
            returntype = (ParameterInfo)minfo.getOutputParameterTypes().iterator().next();
        else
            isAllTreatedAsOutParams = true;

        Collection params = minfo.getInputParameterTypes();
        
        Type retType = null;
        boolean returntypeissimple = false;
        boolean returntypeisarray = false;
        String outparamType = null;
        
        if (returntype != null)
        {
            retType = wscontext.getTypemap().getType(returntype.getSchemaName());
            if (retType != null)
            {
                outparamType = CUtils.getClassNameFromParamInfoConsideringArrays(returntype, wscontext);
                if (retType.isSimpleType())
                   returntypeissimple = true;
                else
                {
                    returntypeissimple = CUtils.isSimpleType (outparamType);
                    returntypeisarray  = CUtils.isArrayType(outparamType);
                }
            
                returntypeisarray |= retType.isArray();
            }
            else
            {
                outparamType = returntype.getLangName();
                returntypeissimple = CUtils.isSimpleType(outparamType);
            } 
        }

        //=============================================================================
        // Generate method prototype
        //=============================================================================        
        
        CUtils.printMethodComment(c_writer, "This function wraps the service method " + minfo.getMethodname() + ".");
        
        //method signature
        String paramTypeName;
        boolean typeisarray = false;
        boolean typeissimple = false;
        Type type;
        
        if (returntype == null)
            c_writer.write("void");
        else if (returntypeissimple
                && (!(returntype.isNillable() || returntype.isOptional()) 
                        || CUtils.isPointerType(outparamType)))
            c_writer.write(outparamType);
        else if (outparamType.lastIndexOf("*") > 0)
            c_writer.write(outparamType);
        else 
            c_writer.write(outparamType + "*");
   
        // Method name may conflict with a C type, so if it does, need to make method unique.
        String methodName = minfo.getSanitizedMethodName();
        int ii = 0;
        while (wscontext.getTypemap().doesTypeExist(methodName))
        {
            methodName = minfo.getSanitizedMethodName() + ii++;
        }

        c_writer.write(" " + methodName + "(AXISCHANDLE stub");
        ArrayList paramsB = (ArrayList) params;
        ParameterInfo paramtype = null;
        if (0 < paramsB.size ())
        {
            c_writer.write(", ");
            
            type = wscontext.getTypemap ().getType (((ParameterInfo) paramsB.get (0)).getSchemaName ());
            paramtype = (ParameterInfo) paramsB.get (0);
            String baseTypeName = null;
            if (type != null)
            {
                if (type.isSimpleType ())
                {        
                    baseTypeName = CUtils.getSimpleType (type.getBaseType ());
                    paramTypeName = CUtils.getClassNameFromParamInfoConsideringArrays(paramtype, wscontext);
                }
                else
                {
                    paramTypeName = type.getLanguageSpecificName ();
                    if (CUtils.isSimpleType (paramTypeName))
                        paramTypeName = CUtils.getClassNameFromParamInfoConsideringArrays(paramtype, wscontext);

                    typeisarray = CUtils.isArrayType(paramTypeName);
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
                c_writer.write("ISoapAttachment *Value0");
            else if (typeissimple
                    && (!(((ParameterInfo) paramsB.get (0)).isNillable () || ((ParameterInfo) paramsB.get (0)).isOptional())
                            || CUtils.isPointerType(baseTypeName)))
            {
                c_writer.write (paramTypeName + " Value0");
            }
            else if (paramTypeName.lastIndexOf ("*") > 0)
                c_writer.write (paramTypeName + " Value0");
            else //for AnyType too
                c_writer.write (paramTypeName + "* Value0");

            for (int i = 1; i < paramsB.size (); i++)
            {
                baseTypeName = null;
                type = wscontext.getTypemap ().getType (((ParameterInfo) paramsB.get (i)).getSchemaName ());
                paramtype = (ParameterInfo) paramsB.get (i);
                if (type != null)
                {
                    if (type.isSimpleType ())
                    {        //schema defined simpleType
                        baseTypeName = CUtils.getSimpleType (type.getBaseType ());
                        paramTypeName = CUtils.getClassNameFromParamInfoConsideringArrays(paramtype, wscontext);
                    }
                    else
                    {
                        paramTypeName = type.getLanguageSpecificName ();
                        if (CUtils.isSimpleType (paramTypeName))
                            paramTypeName = CUtils.getClassNameFromParamInfoConsideringArrays(paramtype, wscontext);

                        typeisarray = CUtils.isArrayType(paramTypeName);
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
                       c_writer.write(", ISoapAttachment *Value" + i);
                else if (typeissimple
                            && (!(((ParameterInfo) paramsB.get (i)).isNillable () 
                                    || ((ParameterInfo) paramsB.get (i)).isOptional())
                                        || CUtils.isPointerType(baseTypeName)))
                    c_writer.write (", " + paramTypeName + " Value" + i);
                else if (paramTypeName.lastIndexOf ("*") > 0)
                    c_writer.write (", " + paramTypeName + " Value" + i);
                else //for AnyType too
                    c_writer.write (", " + paramTypeName + "* Value" + i);
            } // end for loop
        } // end if (0 < paramsB.size ())
        
        // Multiples parameters so fill the methods prototype
        ArrayList paramsC = (ArrayList) minfo.getOutputParameterTypes();
        if (isAllTreatedAsOutParams)
            for (int i = 0; i < paramsC.size (); i++)
            {
                String baseTypeName = null;
                type = wscontext.getTypemap ().getType (((ParameterInfo) paramsC.get (i)).getSchemaName ());
    
                ParameterInfo param = (ParameterInfo) paramsC.get (i);
                String    paramType = CUtils.getClassNameFromParamInfoConsideringArrays (param, wscontext);
                if (type.isSimpleType())
                    baseTypeName = CUtils.getSimpleType(type.getBaseType());
                else
                    baseTypeName = paramType;
                
                boolean bTypeHasStar = paramType.endsWith("*");
                
                c_writer.write(", ");
                
                c_writer.write("AXISC_OUT_PARAM " + paramType);
                if (CUtils.isSimpleType(baseTypeName))
                {
                    if ((param.isOptional() || param.isNillable()) && !CUtils.isPointerType(baseTypeName))
                    {
                        if (bTypeHasStar)
                            c_writer.write(" *");
                        else
                            c_writer.write(" **");
                    }
                    else if (CUtils.isPointerType(baseTypeName) || !bTypeHasStar)
                        c_writer.write(" *");
                }
                else if(bTypeHasStar)
                    c_writer.write(" *");
                else
                    c_writer.write(" **");
                
                c_writer.write(" OutValue" + i);
            } // end for-loop
        
        c_writer.write(")\n{\n");
        
        //=============================================================================
        // Generate global variables 
        //=============================================================================   
        
        c_writer.write ("\tAxiscBool blnIsNewPrefix;\n");
        c_writer.write ("\tconst AxiscChar *pcNSPrefix;\n");
        c_writer.write ("\tAXISCHANDLE pSZ;\n");
        c_writer.write ("\tAXISCHANDLE call = axiscStubGetCall(stub);\n");
        
        if (returntype != null)
        {
            c_writer.write("\t");
            
            if (returntypeisarray && !returntype.isAnyElement())
            {   
                QName qname = null;
                if (CUtils.getArrayType (retType) != null)
                    qname = CUtils.getArrayType (retType).getName ();
                else
                    qname = retType.getName ();
                if (CUtils.isSimpleType (qname))               
                    c_writer.write(outparamType + " *RetArray = (" + outparamType + " *)NULL;\n");
                else
                    c_writer.write(outparamType + " *RetArray = (" + outparamType + " *)Axis_Create_" + outparamType + "(0);\n");
            }
            else if (!returntypeissimple)
            {
                // for AnyType and complex types
                if (outparamType.lastIndexOf("*") > 0)
                    c_writer.write(outparamType + " pReturn = NULL;\n");
                else
                    c_writer.write(outparamType + "* pReturn = NULL;\n");
            }
            else if ((returntype.isNillable() || returntype.isOptional())
                        && !(CUtils.isPointerType(outparamType)))
                c_writer.write(outparamType + "* Ret = NULL;\n");
            else
            {
                String initValue = CUtils.getInitValueForType(outparamType);
                if (initValue != null)
                    c_writer.write(outparamType + " Ret = " + initValue + ";\n");
                else if (CUtils.getXSDEnumeratorForType( outparamType).equals("XSDC_DATETIME")
                        || CUtils.getXSDEnumeratorForType( outparamType).equals("XSDC_DATE")
                        || CUtils.getXSDEnumeratorForType( outparamType).equals("XSDC_TIME"))
                {
                    c_writer.write(outparamType + " Ret;\n");
                    c_writer.write("\tmemset(&Ret,0,sizeof(" + outparamType + "));\n");
                }
                else
                    c_writer.write(outparamType + " Ret;\n");
            }
        }
        
        c_writer.write("\n");
        
        //=============================================================================
        // Generate fault handling code
        //=============================================================================        
                
        writeFaultHandlingCode(minfo);
        c_writer.write("\n");        
        
        //=============================================================================
        // Generate method logic
        //=============================================================================        

        CUtils.printBlockComment(c_writer, "Initialize client engine, set SOAP version, SOAPAction, operation, etc.");
        
        c_writer.write("\tif (AXISC_SUCCESS != axiscCallInitialize(call, C_DOC_PROVIDER " + "))\n");
        c_writer.write("\t\treturn ");
        if (returntype != null)
            c_writer.write((returntypeisarray ? "RetArray" : returntypeissimple ? "Ret" : "pReturn") + ";\n");
        else
            c_writer.write(";\n");
        c_writer.write("\n");
        
        c_writer.write("\taxiscCallSetTransportProperty(call,AXISC_SOAPACTION_HEADER , \""
                + minfo.getSoapAction() + "\");\n");
        c_writer.write("\n");
        
        c_writer.write("\taxiscCallSetSOAPVersion(call, SOAP_VER_1_1);\n");
        //TODO check which version is it really.
        
        // Issue setOperation logic...namespace for the operation is 
        // obtained from the namespace of the input message...if there
        // is no input message then the namespace is obtained from 
        // the SOAP body extensability element for the input element; if
        // there is no namespace, then we will use a null string.
        // For doc/literal, the SOAP body extensability element 
        // must not contain the namespace attribute.  The SOAP body 
        // entry element for doc/literal style gets its namespace from the 
        // target namespace of the XML schema declaring this element. 
        String namespaceURI;
        if( minfo.getInputMessage() != null)
            namespaceURI = minfo.getInputMessage().getNamespaceURI();
        else
            namespaceURI = minfo.getInputNamespaceURI();
        
        if (namespaceURI == null)
            namespaceURI = "";

        // Need to give indication to serializer whether wrapped or unwrapped style is being done.
        // And for non-wrapper style, the "operation" is not the method name, but the element name
        // of the root node. 
        
        if (minfo.isUnwrapped())
        {
            String actualMethodName = "";

            if( minfo.getInputMessage() != null)
                actualMethodName = minfo.getInputMessage().getLocalPart();
            
            c_writer.write("\taxiscCallSetOperationUnwrapped(call, \"" +
                           actualMethodName + "\", \"" + namespaceURI + "\");\n");
        }
        else
        {
            c_writer.write("\taxiscCallSetOperation(call, \"" +
                            minfo.getMethodname() + "\", \"" + namespaceURI + "\");\n");
        }
        
        //=============================================================================
        // Apply user specified properties
        //=============================================================================        

        CUtils.printBlockComment(c_writer, "Apply SSL configuration properties and user-set SOAP headers.");        
        c_writer.write ("\taxiscStubIncludeSecure(stub);\n");  
        c_writer.write ("\taxiscStubApplyUserPreferences(stub);\n");

        //=============================================================================
        // Process elements
        //=============================================================================        
        
        boolean commentIssued=false;
        for (int i = 0; i < paramsB.size(); i++)
        {
            ParameterInfo param = (ParameterInfo) paramsB.get(i);

            // Ignore attributes
            if (param.isAttribute ())
                continue;
            
            if (!commentIssued)
            {
                commentIssued = true;
                CUtils.printBlockComment(c_writer, "Process parameters.");
                c_writer.write ("\tpSZ = axiscCallGetSOAPSerializer(call);\n\n");
            }
            else
                c_writer.write ("\n");
                        
            // add elements
            type = wscontext.getTypemap().getType(param.getSchemaName());
            if (type != null)
            {
                if (type.isSimpleType())
                    paramTypeName = CUtils.getSimpleType(type.getBaseType());
                else
                {
                    paramTypeName = type.getLanguageSpecificName();
                    if (CUtils.isSimpleType(paramTypeName))
                        paramTypeName = CUtils.getClassNameFromParamInfoConsideringArrays(param,wscontext);
                    
                    typeisarray = CUtils.isArrayType(paramTypeName);
                    if (!typeisarray)
                        paramTypeName = type.getLanguageSpecificName();
                }
                
                typeisarray |= type.isArray();
            }
            else
            {
                paramTypeName = ((ParameterInfo) paramsB.get (i)).getLangName ();
                typeisarray = false;
            }
 
            if (param.isAnyElement ())
                c_writer.write("\taxiscCallAddAnyObject(call, Value" + i);
            else
            {
                String parameterName = ((ParameterInfo) paramsB.get (i)).getElementNameAsSOAPString ();
                String namespace = ((ParameterInfo) paramsB.get (i)).getElementName ().getNamespaceURI ();
    
                if (((ParameterInfo)paramsB.get(i)).isOptional())
                    c_writer.write("\tif (Value" + i + " != NULL)\n\t{\n");
                else
                    c_writer.write("\t{\n"); // following was added to instantiate variables on the fly
                
                if (namespace.length () == 0)
                {
                    c_writer.write ("\t\tchar cPrefixAndParamName"
                              + i + "[" + "] = \"" + parameterName + "\";\n");
                }
                else
                {
                    int stringLength = 8 + 1 + parameterName.length () + 1;
                    c_writer.write ("\t\tchar cPrefixAndParamName" + i + "[" + stringLength + "];\n");
                    
                    c_writer.write("\t\tpcNSPrefix = axiscSoapSerializerGetNamespacePrefix(pSZ, \"" + namespace + "\", &blnIsNewPrefix);\n");
                    c_writer.write("\t\tif (blnIsNewPrefix)\n");
                    c_writer.write("\t\t\taxiscCallSetSOAPMethodAttribute(call, pcNSPrefix, \"xmlns\", NULL, \"" + namespace + "\");\n");
                    c_writer.write("\t\tsprintf( cPrefixAndParamName" + i + ", \"%s:" + parameterName + "\", pcNSPrefix);\n");
                }
    
                if (param.getType().isAttachment())
                {
                    // TODO
                    String attchType = param.getType().getName().getLocalPart();
                    c_writer.write("\t\tconst AxiscChar *xmlSoapNsPfx" + i + 
                        " = axiscCallGetNamespacePrefix(call,\"" + 
                        WrapperConstants.APACHE_XMLSOAP_NAMESPACE + "\");\n");
                    c_writer.write("\t\tchar attchType" + i + "[64];\n");
                    c_writer.write("\t\tstrcpy(attchType" + i + ", xmlSoapNsPfx" + i + ");\n");
                    c_writer.write("\t\tstrcat(attchType" + i + ", \":" + attchType + "\");\n");
                    c_writer.write("\t\tAXISCHANDLE attrs" + i + "[2];\n");
                    c_writer.write("\t\tattrs" + i + "[0] = axiscCallCreateAttribute(call,\"type\", \"xsi\", attchType" + i + 
                        ");\n");
                    c_writer.write("\t\tattrs" + i + "[1] = axiscCallCreateAttribute(call,xmlSoapNsPfx" + i + 
                        ", \"xmlns\", \"http://xml.apache.org/xml-soap\");\n");
                    c_writer.write("\t\taxiscCallAddAttachmentParameter(call, Value" + i + ", cPrefixAndParamName" + i + 
                        ", attrs" + i + ", 2");
                }
                else if (typeisarray)
                {
                    Type arrayType = CUtils.getArrayType (type);
        
                    QName qname = null;
                    if (arrayType != null)
                        qname = arrayType.getName ();
                    else
                        qname = type.getName ();
                
                    if (CUtils.isSimpleType (qname))
                    {
                        // Array of simple type
                        String containedType = CUtils.getSimpleType (qname);
                        c_writer.write ("\t\taxiscCallAddBasicArrayParameter(call,");
                        c_writer.write ("(Axisc_Array *)Value" + i + ", " +
                              CUtils.getXSDEnumeratorForType(containedType) + ", cPrefixAndParamName" + i);
                    }
                    else if (arrayType != null && arrayType.isSimpleType ())
                    {
                        String containedType = CUtils.getSimpleType (arrayType.getBaseType ());
                        c_writer.write ("\t\taxiscCallAddBasicArrayParameter(call,");
                        c_writer.write ("(Axisc_Array *)Value" + i + ", " +
                                  CUtils.getXSDEnumeratorForType(containedType) +
                                  ", cPrefixAndParamName" + i);
                    }
                    else
                    {
                        // Array of complex type
                        String containedType = qname.getLocalPart ();
                        c_writer.write ("\t\taxiscCallAddCmplxArrayParameter(call,");
                        c_writer.write ("(Axisc_Array *)Value" + i +
                                  ", (void*)Axis_Serialize_" + containedType +
                                  ", (void*)Axis_Delete_" + containedType +
                                  ", \"" + parameterName + "\"" + ", ");
                        
                        if (namespace.length () == 0)
                            c_writer.write ("NULL");
                        else
                            c_writer.write ("Axis_URI_" + containedType);
                    }
                }
                else if (CUtils.isSimpleType (paramTypeName))
                {
                    if (param.isNillable () 
                            || param.isOptional()
                            || CUtils.isPointerType(paramTypeName))
                    {
                        c_writer.write ("\t\taxiscCallAddParameter(call,");
                        c_writer.write ("(void*)Value" + i + ", cPrefixAndParamName" + i
                                  + ", " + CUtils.getXSDEnumeratorForType(paramTypeName));
                    }
                    else
                    {
                        c_writer.write ("\t\taxiscCallAddParameter(call,");
                        c_writer.write ("(void*)&Value" + i + ", cPrefixAndParamName" + i
                                  + ", " + CUtils.getXSDEnumeratorForType(paramTypeName));
                    }
                }
                else
                {
                    // Complex Type
                    c_writer.write ("\t\taxiscCallAddCmplxParameter(call,");
                    c_writer.write ("Value" + i
                          + ", (void*)Axis_Serialize_" + paramTypeName
                          + ", (void*)Axis_Delete_" + paramTypeName
                          + ", cPrefixAndParamName" + i + ", Axis_URI_" + paramTypeName);
                }              
            }

            c_writer.write (");\n");
            if (!param.isAnyElement ())
                c_writer.write("\t}\n");            
          } // end for-loop

        c_writer.write("\n");
        
        //=============================================================================
        // Invoke web service - one-way or two-way message processing
        //=============================================================================  
        
        // Tricky part...if in the WSDL the response is an element that references a type, for example:
        // 
        // <simpleType name="ActionResultType">
        //    <restriction base="xsd:string">
        //        <enumeration value="Success"/>
        //        <enumeration value="Connection Failure"/>
        //    </restriction>
        // </simpleType>
        // <element name="callControlResponse" type="tns:ActionResultType"/>
        //
        // Then the SOAP response looks like the following:
        //  <ns37:callControlResponse xmlns:ns37="http://ws.xxx.com/ip/">Success</ns37:callControlResponse>
        //
        // So we need to validate response body element w/out consuming node. This also holds true when doing
        // unwrapped methods.
        String consumeBodyNode="true_";
        if (!minfo.consumeBodyOnMessageValidation())
            consumeBodyNode = "false_";
        
        if (minfo.getOutputMessage () != null)
        {
            CUtils.printBlockComment(c_writer, "Invoke web service, send/receive operation. Handle output parameters, if any.");
            c_writer.write("\tif (AXISC_SUCCESS == axiscCallSendAndReceive(call))\n\t{\n");       
            c_writer.write("\t\tif(AXISC_SUCCESS == axiscCallValidateMessage(call, \""
                + minfo.getOutputMessage().getLocalPart() + "\", \""
                + minfo.getOutputMessage().getNamespaceURI() + "\", " + consumeBodyNode + "))\n\t\t{\n");
        }
        else
        {
            CUtils.printBlockComment(c_writer, "Invoke web service, send-only operation.");
            c_writer.write("\tif (AXISC_SUCCESS == axiscCallSend(call))\n\t{\n");      
        }
        
        //=============================================================================
        // Process output parameters
        //=============================================================================     
        
        String returnStatement = "";
        
        if (isAllTreatedAsOutParams)
        {
            String currentParamName;
            String currentParaType;
            
            for (int i = 0; i < paramsC.size(); i++)
            {
                String baseTypeName = null;
                ParameterInfo currentType = (ParameterInfo) paramsC.get(i);
                
                type = wscontext.getTypemap().getType(currentType.getSchemaName());
                if (type != null)
                {
                    if (type.isSimpleType ())
                    {
                        baseTypeName = CUtils.getSimpleType (type.getBaseType ());
                        currentParaType = CUtils.getClassNameFromParamInfoConsideringArrays(currentType, wscontext);
                    }
                    else
                    {
                        currentParaType = CUtils.getClassNameFromParamInfoConsideringArrays(currentType, wscontext);
                        typeisarray = CUtils.isArrayType(currentParaType);
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
                if (currentType.isAnyElement ())
                {
                    // TODO work needs to be done to clean up storage!
                    c_writer.write ("\t\t\t"
                          + currentParamName + " = *(" + currentParaType 
                          + "*)axiscCallGetAnyObject(call);\n");
                }
                else if (typeisarray)
                {
                    QName qname = null;
                    if (CUtils.getArrayType (type) != null)
                        qname = CUtils.getArrayType (type).getName ();
                    else
                        qname = type.getName ();
                    
                    String containedType = null;
                    String containedTypeArrayName = null;

                    if (CUtils.isSimpleType(qname))
                    {
                        containedType = CUtils.getSimpleType(qname);
                        
                        c_writer.write("\n\t\t\tOutValue" + i + " = axiscCallGetBasicArray(call, " 
                                + CUtils.getXSDEnumeratorForType (containedType) 
                                + ", \"" + currentType.getParamNameAsSOAPString ()
                                + "\", 0);\n\n");
                    }
                    else
                    {
                        containedType          = qname.getLocalPart ();
                        containedTypeArrayName = CUtils.getArrayNameForComplexType(qname);
                        
                        c_writer.write("\n\t\t\tif (OutValue" + i + " != NULL)\n" );
                        c_writer.write("\t\t\t{\n");
                        
                        c_writer.write("\t\t\t\tif (" + currentParamName + " != NULL)\n");
                        c_writer.write("\t\t\t\t\t" + "Axis_Delete_" + containedTypeArrayName + "(" + currentParamName + ",0);\n");
                        c_writer.write("\t\t\t\t" + currentParamName + " = Axis_Create_" + containedTypeArrayName + "(0);\n");
                        
                        c_writer.write("\t\t\t\taxiscCallGetCmplxArray(call, (Axisc_Array *)" + currentParamName 
                              + ", (void*) Axis_DeSerialize_" + containedType
                              + ", (void*) Axis_Create_" + containedType
                              + ", (void*) Axis_Delete_" + containedType
                              + ", \"" + currentType.getElementNameAsSOAPString () 
                              + "\", Axis_URI_" + containedType + ");\n");
                        
                        c_writer.write("\t\t\t}\n");
                        c_writer.write("\t\t\telse\n");
                        c_writer.write("\t\t\t{\n");
                        
                        c_writer.write("\t\t\t\t/* Unable to return value, but will deserialize to ensure subsequent elements can be correctly processed. */\n");
                        c_writer.write("\t\t\t\t" + containedTypeArrayName + " * pTemp" + i 
                              + " = Axis_Create_" + containedTypeArrayName + "(0);\n");
                        c_writer.write("\t\t\t\taxiscCallGetCmplxArray(call, (Axisc_Array *)pTemp" + i 
                              + ", (void*) Axis_DeSerialize_" + containedType
                              + ", (void*) Axis_Create_" + containedType
                              + ", (void*) Axis_Delete_" + containedType
                              + ", \"" + currentType.getElementNameAsSOAPString () 
                              + "\", Axis_URI_" + containedType + ");\n");
                        c_writer.write("\t\t\t\tAxis_Delete_" + containedTypeArrayName + "(pTemp" + i + ", 0);\n");
                        c_writer.write("\t\t\t}\n");                        
                    }
                }
                else if (typeissimple)
                {
                    if( i > 0)
                        c_writer.write( "\n");
                    
                    c_writer.write("\t\t\t{\n"); // begin scope
                    if (CUtils.isPointerType(baseTypeName))
                    {
                        String xsdType =  CUtils.getClassNameFromParamInfoConsideringArrays ((ParameterInfo) paramsC.get (i), wscontext);
                        
                        if( !CUtils.isPointerType(baseTypeName))
                        {
                            if (!baseTypeName.equals(currentParaType))
                                xsdType = currentParaType;

                            xsdType += " *";
                        }
                        
                        c_writer.write( "\t\t\t" + currentParaType + " pReturn" + i + " = " 
                                + "axiscCall"
                                + CUtils.getDeserializerMethodName( baseTypeName, false) 
                                + "(call,  \"" + currentType.getParamNameAsSOAPString() + "\", 0);\n");
                        c_writer.write( "\n");
                        c_writer.write( "\t\t\tif( pReturn" + i + " != NULL && OutValue" + i + " != NULL)\n");
                        c_writer.write( "\t\t\t{\n");
                        c_writer.write( "\t\t\t\tif( *OutValue" + i + " != NULL)\n");
                        c_writer.write( "\t\t\t\t{\n");
                        c_writer.write( "\t\t\t\t\tint\tiStringSize" + i + " = strlen( (char *) *OutValue" + i + ");\n");
                        c_writer.write( "\t\t\t\t\tint\tiStrLenValue" + i + " = strlen( pReturn" + i + ");\n");
                        c_writer.write( "\n");
                        c_writer.write( "\t\t\t\t\tif( iStrLenValue" + i + " > iStringSize" + i + ")\n");
                        c_writer.write( "\t\t\t\t\t{\n");
                        c_writer.write( "\t\t\t\t\t\t*OutValue" + i + " =(" + xsdType + ") axiscAxisNew(XSDC_STRING, iStrLenValue" + i + " + 1);\n");
                        c_writer.write( "\t\t\t\t\t\tstrcpy( (char *) *OutValue" + i + ", pReturn" + i + ");\n");
                        c_writer.write( "\t\t\t\t\t}\n");
                        c_writer.write( "\t\t\t\t\telse\n");
                        c_writer.write( "\t\t\t\t\t\tstrcpy( (char *) *OutValue" + i + ", pReturn" + i + ");\n");
                        c_writer.write( "\t\t\t\t}\n");
                        c_writer.write( "\t\t\t\telse\n");
                        c_writer.write( "\t\t\t\t{\n");
                        c_writer.write( "\t\t\t\t\t*OutValue" + i + " = (" + xsdType + ") axiscAxisNew(XSDC_STRING,strlen( pReturn" + i + ") + 1);\n");
                        c_writer.write( "\t\t\t\t\tstrcpy( (char *) *OutValue" + i + ", pReturn" + i + ");\n");
                        c_writer.write( "\t\t\t\t}\n");
                        c_writer.write( "\t\t\t}\n");
                        c_writer.write( "\n");
                        c_writer.write( "\t\t\taxiscAxisDelete( (void *) pReturn" + i + ", " + CUtils.getXSDEnumeratorForType( baseTypeName) + ");\n");
                    }
                    else 
                    {
                        c_writer.write( "\t\t\t" + currentParaType + " * pReturn" + i + " = " 
                                + "axiscCall"
                                + CUtils.getDeserializerMethodName( baseTypeName, false) 
                                + "(call,  \"" + currentType.getParamNameAsSOAPString() + "\", 0);\n");
                        c_writer.write( "\n");
                        c_writer.write( "\t\t\tif( pReturn" + i + " != NULL && OutValue" + i + " != NULL)\n");
                        c_writer.write( "\t\t\t{\n");
                        if (currentType.isNillable() || currentType.isOptional())
                        {
                            c_writer.write( "\t\t\t\tif( *OutValue" + i + " == NULL)\n");
                            c_writer.write( "\t\t\t\t\t*OutValue" + i + " = axiscAxisNew(" + CUtils.getXSDEnumeratorForType( baseTypeName) + ", 0);\n");
                            c_writer.write( "\n");
                            c_writer.write( "\t\t\t\t*");
                        }
                        else
                            c_writer.write( "\t\t\t\t");

                        c_writer.write( "*OutValue" + i + " = *pReturn" + i + ";\n");
                        c_writer.write( "\t\t\t}\n");
                        c_writer.write( "\n");
                        
                        if (CUtils.getXSDEnumeratorForType( baseTypeName).equals("XSDC_HEXBINARY")
                                || CUtils.getXSDEnumeratorForType( baseTypeName).equals("XSDC_BASE64BINARY"))
                        {
                            c_writer.write( "\t\t\tpReturn" + i + "->__ptr = NULL;\n");
                        }
                        
                        c_writer.write( "\t\t\taxiscAxisDelete( (void *) pReturn" + i + ", " + CUtils.getXSDEnumeratorForType( baseTypeName) + ");\n");
                    }
                    c_writer.write("\t\t\t}\n"); // end scope
                }
                else
                {
                    int lastIndexOfStar = currentParaType.lastIndexOf("*");
                    if (lastIndexOfStar > 0)
                        currentParaType = currentParaType.substring(0, lastIndexOfStar);

                    c_writer.write ("\n\t\t\t"
                              + currentParamName + " = (" + currentParaType
                              + "*)axiscCallGetCmplxObject(call, (void*) Axis_DeSerialize_" + currentParaType 
                              + ", (void*) Axis_Create_" + currentParaType 
                              + ", (void*) Axis_Delete_" + currentParaType + ",\"" 
                              + currentType.getElementNameAsSOAPString () + "\", 0);\n");
                }
            }
            
            c_writer.write ("\t\t}\n");
        }
        else if (returntype == null)
        {
            if (minfo.getOutputMessage () != null)
                c_writer.write ("\t\t\t// no output to process\n\t\t}\n");
        }
        else if (returntype.isAnyElement ())
        {
            // TODO need to handle arrays?
            c_writer.write ("\t\t\tpReturn = (" + outparamType + ")axiscCallGetAnyObject(call);\n\t\t}\n");

            returnStatement = "\treturn pReturn;\n";
        }
        else if (returntypeisarray)
        {
            QName qname = null;
            if (CUtils.getArrayType (retType) != null)
                qname = CUtils.getArrayType (retType).getName ();
            else
                qname = retType.getName ();
            
            String containedType = null;
            String containedTypeArrayName = null;

            if (CUtils.isSimpleType (qname))
            {
                containedType          = CUtils.getSimpleType (qname);
                containedTypeArrayName = CUtils.getArrayNameforSimpleType(qname, containedType);

                c_writer.write ("\t\t\tRetArray =(" + containedTypeArrayName + " *) axiscCallGetBasicArray(call, " 
                        + CUtils.getXSDEnumeratorForType (containedType) 
                        + ", \"" + returntype.getParamNameAsSOAPString () + "\", 0);\n");
            }
            else
            {
                containedType          = qname.getLocalPart ();
                containedTypeArrayName = CUtils.getArrayNameForComplexType(qname);

                c_writer.write("\t\t\tRetArray = (" + containedTypeArrayName 
                        + " *) axiscCallGetCmplxArray(call, (Axisc_Array *)RetArray, (void*) Axis_DeSerialize_"
                        + containedType 
                        + ", (void*) Axis_Create_" + containedType
                          + ", (void*) Axis_Delete_" + containedType
                          + ", \"" + returntype.getElementNameAsSOAPString ()
                          + "\", Axis_URI_" + containedType + ");\n");
            }
            
            c_writer.write ("\t\t}\n");

            returnStatement = "\treturn RetArray;\n";
        }
        else if (returntypeissimple)
        {
            if (returntype.isNillable () || returntype.isOptional() || CUtils.isPointerType(outparamType))
            {
               c_writer.write( "\t\t\tRet = axiscCall"
                       + CUtils.getDeserializerMethodName( outparamType, false) 
                       + "(call, \"" + returntype.getParamNameAsSOAPString() + "\", 0);\n");
                c_writer.write( "\t\t}\n");
            }
            else
            {
                c_writer.write ("\t\t\t" + outparamType + " * pReturn = " 
                        + "axiscCall"
                        + CUtils.getDeserializerMethodName(outparamType, false) 
                        + "(call, \"" + returntype.getElementNameAsSOAPString() + "\", 0);\n");
                
                c_writer.write ("\t\t\tif(pReturn)\n");
                c_writer.write ("\t\t\t{\n");
                
                c_writer.write ("\t\t\t\tRet = *pReturn;\n");

                if (CUtils.getXSDEnumeratorForType( outparamType).equals("XSDC_HEXBINARY")
                        || CUtils.getXSDEnumeratorForType( outparamType).equals("XSDC_BASE64BINARY"))
                {
                    c_writer.write( "\t\t\t\tpReturn->__ptr = NULL;\n");
                }
                
                c_writer.write ("\t\t\t\taxiscAxisDelete( (void *) pReturn, " 
                        + CUtils.getXSDEnumeratorForType( outparamType) + ");\n");

                c_writer.write ("\t\t\t}\n");
                
                c_writer.write ("\t\t}\n");
            }

            returnStatement = "\treturn Ret;\n";
        }
        else
        {
            if (outparamType.lastIndexOf ("*") > 0)
            {
                String outparamTypeBase = outparamType.substring (0,outparamType.lastIndexOf("*"));
                c_writer.write ("\t\t\tpReturn = (" + outparamType +
                          ")axiscCallGetCmplxObject(call, (void*) Axis_DeSerialize_" + outparamTypeBase +
                          ", (void*) Axis_Create_" + outparamTypeBase +
                          ", (void*) Axis_Delete_" + outparamTypeBase + ",\"" +
                          returntype.getElementNameAsSOAPString () + "\", 0);\n\t\t}\n");
            }
            else
            {
                c_writer.write ("\t\t\tpReturn = (" + outparamType
                          + "*)axiscCallGetCmplxObject(call, (void*) Axis_DeSerialize_" + outparamType +
                          ", (void*) Axis_Create_" + outparamType +
                          ", (void*) Axis_Delete_" + outparamType + ",\"" +
                          returntype.getElementNameAsSOAPString () + "\", 0);\n\t\t}\n");
            }

            returnStatement = "\treturn pReturn;\n";
        }
        
        if (minfo.getOutputMessage () != null)
            c_writer.write ("\n\t\taxiscStubCheckForExtraneousElements(stub);\n");
        c_writer.write ("\t}\n");
        c_writer.write ("\taxiscCallUnInitialize(call);\n");
        c_writer.write(returnStatement);
        
        //=============================================================================
        // End of method
        //=============================================================================        
                       
        c_writer.write("}\n");
    }

}
