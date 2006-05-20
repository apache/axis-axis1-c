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
 * @author Kanchana Welagedara(kanchana@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws.c.literal;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;

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
          writer.write("\n");
          writer.write("/* ================================================== */\n" +
                       "/* Functions relating to web service client proxy     */\n" +
                       "/* ================================================== */\n");
          writer.write("\n");
          
          // get_xxx_stub() routine
          writer.write("AXISCHANDLE get_" + classname + "_stub(const char* pchEndPointUri)\n{\n");
          writer.write("\tif(pchEndPointUri)\n");
          writer.write("\t\treturn axiscStubCreate(pchEndPointUri, AXISC_APTHTTP1_1);\n");
          writer.write("\telse\n");
          writer.write("\t\treturn axiscStubCreate(\"" 
                  + wscontext.getWrapInfo().getTargetEndpointURI() 
                  + "\", AXISC_APTHTTP1_1);\n");
          writer.write("}\n\n");
          
          // destroy_xxxx_stub()
          writer.write("void destroy_" + classname + "_stub(AXISCHANDLE p)\n{\n");
          writer.write("\taxiscStubDestroy(p);\n}\n\n");

          // get_xxxx_Status() routine
          writer.write("int get_" + classname + "_Status(AXISCHANDLE stub)\n{\n");
          writer.write("\tAXISCHANDLE call = axiscStubGetCall(stub);\n");
          writer.write("\treturn axiscCallGetStatus(call);\n");
          writer.write("}\n");

          writer.write("\n");
          writer.write("/* ================================================== */\n" +
                       "/* Functions corresponding to the web service methods */\n" +
                       "/* ================================================== */\n");
          writer.write("\n");
          
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
        String methodName = minfo.getMethodname();
        Type retType = null;
        boolean returntypeissimple = false;
        boolean returntypeisarray = false;
        String outparamType = null;
        
        if (returntype != null)
            retType = wscontext.getTypemap().getType(returntype.getSchemaName());
    
        if (retType != null)
        {
            if (retType.isSimpleType())
                outparamType = CUtils.getclass4qname(retType.getBaseType());
            else
            {
                outparamType = WrapperUtils.getClassNameFromParamInfoConsideringArrays(returntype,wscontext);
                returntypeisarray = (outparamType.lastIndexOf("_Array") > 0);
            }
            
            returntypeisarray |= retType.isArray();
        }
        else if (returntype != null)
            outparamType = returntype.getLangName();
        
        if (returntype != null)
            returntypeissimple = CUtils.isSimpleType(outparamType);

        writer.write("\n/*\n");
        writer.write(" * This function wraps the service method " + methodName + "\n");
        writer.write(" */\n");
        
        //method signature
        String paraTypeName;
        boolean typeisarray = false;
        boolean typeissimple = false;
        Type type;
        
        if (returntype == null)
            writer.write("void");
        else if (returntypeissimple
                && (!(returntype.isNillable() || returntype.isOptional()) 
                        || CUtils.isPointerType(outparamType)))
            writer.write(outparamType);
        else if (outparamType.lastIndexOf("*") > 0)
            writer.write(outparamType);
        else // for AnyType too
            writer.write(outparamType + "*");
   
        writer.write(" " + methodName + "(AXISCHANDLE stub");
        ArrayList paramsB = (ArrayList) params;
        ParameterInfo paramtype = null;
        if (0 < paramsB.size ())
        {
            writer.write(", ");
            
            type = wscontext.getTypemap ().getType (((ParameterInfo) paramsB.get (0)).getSchemaName ());
            paramtype = (ParameterInfo) paramsB.get (0);
            String baseTypeName = null;
            if (type != null)
            {
                if (type.isSimpleType ())
                {        
                    baseTypeName = CUtils.getclass4qname (type.getBaseType ());
                    paraTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(paramtype, wscontext);
                }
                else
                {
                    paraTypeName = type.getLanguageSpecificName ();
                    if (CUtils.isSimpleType (paraTypeName))
                        paraTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(paramtype, wscontext);

                    typeisarray = (paraTypeName.lastIndexOf ("_Array") > 0);
                    if (!typeisarray)
                        paraTypeName = type.getLanguageSpecificName ();

                    typeissimple = CUtils.isSimpleType (paraTypeName);
                }
                typeisarray |= type.isArray ();
            }
            else
            {
                paraTypeName = ((ParameterInfo) paramsB.get (0)).getLangName ();
                paramtype = (ParameterInfo) paramsB.get (0);
                typeisarray = false;
            }
            
            if (baseTypeName == null)
                baseTypeName = paraTypeName;

            typeissimple = CUtils.isSimpleType (baseTypeName);
            if (paramtype.getType().isAttachment())
                writer.write("ISoapAttachment *Value0");
            else if (typeissimple
                    && (!(((ParameterInfo) paramsB.get (0)).isNillable () || ((ParameterInfo) paramsB.get (0)).isOptional())
                            || CUtils.isPointerType(baseTypeName)))
            {
                writer.write (paraTypeName + " Value0");
            }
            else if (paraTypeName.lastIndexOf ("*") > 0)
                writer.write (paraTypeName + " Value0");
            else //for AnyType too
                writer.write (paraTypeName + "* Value0");

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
                        paraTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(paramtype, wscontext);
                    }
                    else
                    {
                        paraTypeName = type.getLanguageSpecificName ();
                        if (CUtils.isSimpleType (paraTypeName))
                            paraTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(paramtype, wscontext);

                        typeisarray = (paraTypeName.lastIndexOf ("_Array") > 0);
                        if (!typeisarray)
                            paraTypeName = type.getLanguageSpecificName ();       
                    }
                    
                    typeisarray |= type.isArray ();
                    typeissimple = CUtils.isSimpleType (paraTypeName);
                }
                else
                {
                    paraTypeName = ((ParameterInfo) paramsB.get (i)).getLangName ();
                    paramtype = (ParameterInfo) paramsB.get (i);
                    typeisarray = false;
                }
                
                if (baseTypeName == null)
                    baseTypeName = paraTypeName;

                typeissimple = CUtils.isSimpleType (baseTypeName);
                if (paramtype.getType().isAttachment())
                       writer.write(", ISoapAttachment *Value" + i);
                else if (typeissimple
                            && (!(((ParameterInfo) paramsB.get (i)).isNillable () 
                                    || ((ParameterInfo) paramsB.get (i)).isOptional())
                                        || CUtils.isPointerType(baseTypeName)))
                    writer.write (", " + paraTypeName + " Value" + i);
                else if (paraTypeName.lastIndexOf ("*") > 0)
                    writer.write (", " + paraTypeName + " Value" + i);
                else //for AnyType too
                    writer.write (", " + paraTypeName + "* Value" + i);
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
                String    paramType = WrapperUtils.getClassNameFromParamInfoConsideringArrays (param, wscontext);
                if (type.isSimpleType())
                    baseTypeName = CUtils.getclass4qname(type.getBaseType());
                else
                    baseTypeName = paramType;
                
                boolean bTypeHasStar = paramType.endsWith("*");
                
                writer.write(", ");
                
                writer.write("AXISC_OUT_PARAM " + paramType);
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
        
        writer.write(")\n{\n");
        
        writer.write("\tAXISCHANDLE call = axiscStubGetCall(stub);\n");
        
        if (returntype != null)
        {
            writer.write("\t");
            
            if (returntypeisarray)
            {   
                QName qname = null;
                if (WrapperUtils.getArrayType (retType) != null)
                    qname = WrapperUtils.getArrayType (retType).getName ();
                else
                    qname = retType.getName ();
                if (CUtils.isSimpleType (qname))               
                    writer.write(outparamType + " *RetArray = (" + outparamType + " *)axiscAxisNew(XSDC_ARRAY, 0);\n");
                else
                    writer.write(outparamType + " *RetArray = (" + outparamType + " *)Axis_Create_" + outparamType + "(0);\n");
            }
            else if (!returntypeissimple)
            {
                // for AnyType and complex types
                if (outparamType.lastIndexOf("*") > 0)
                    writer.write(outparamType + " pReturn = NULL;\n");
                else
                    writer.write(outparamType + "* pReturn = NULL;\n");
            }
            else if ((returntype.isNillable() || returntype.isOptional())
                        && !(CUtils.isPointerType(outparamType)))
                writer.write(outparamType + "* Ret = NULL;\n");
            else
            {
                String initValue = CUtils.getInitValue(outparamType);
                if (initValue != null)
                    writer.write(outparamType + " Ret = " + initValue + ";\n");
                else if (outparamType.equals("xsdc__dateTime")
                        || outparamType.equals("xsdc__date")
                        || outparamType.equals("xsdc__time"))
                {
                    writer.write(outparamType + " Ret;\n");
                    writer.write("\tmemset(&Ret,0,sizeof(" + outparamType + "));\n");
                }
                else
                    writer.write(outparamType + " Ret;\n");
            }
            // TODO initialize return parameter appropriately.
        }
        
        writer.write ("\tconst char* pcCmplxFaultName = NULL;\n");
        writer.write("\n");
        
        writer.write("\tif (AXISC_SUCCESS != axiscCallInitialize(call, C_DOC_PROVIDER " + ")) return ");
        if (returntype != null)
            writer.write((returntypeisarray ? "RetArray" : returntypeissimple ? "Ret" : "pReturn") + ";\n");
        else
            writer.write(";\n");
        writer.write("\n");
        
        writer.write("\tif (NULL==axiscCallGetTransportProperty(call,\"SOAPAction\",0))\n");
        writer.write("\t\taxiscCallSetTransportProperty(call,AXISC_SOAPACTION_HEADER , \""
                + minfo.getSoapAction() + "\");\n");
        writer.write("\n");
        
        writer.write("\taxiscCallSetSOAPVersion(call, SOAP_VER_1_1);\n");
        //TODO check which version is it really.
        
        if( minfo.getInputMessage() != null)
        {        
            writer.write("\taxiscCallSetOperation(call, \""
                + minfo.getInputMessage().getLocalPart() + "\", \""
                + minfo.getInputMessage().getNamespaceURI() + "\");\n");
        }

        // Add attributes to soap method
        for (int i = 0; i < paramsB.size (); i++)
        {
            ParameterInfo param = (ParameterInfo) paramsB.get (i);
            
            // Skip non-attributes
            if (!param.isAttribute ())
                continue;
            
            // Process attributes
            String elementType = param.getElementName ().getLocalPart ();
    
            if ("string".equals (elementType))
            {
                writer.write ("\taxiscCallSetSOAPMethodAttribute(call, \""
                      + param.getParamName () + "\", \"\", Value" + i + ");\n");
            }
            else if ("int".equals (elementType))
            {
                writer.write ("\t{\n");
                writer.write ("\t\tchar buffer[20];\n");
                writer.write ("\t\tsprintf(buffer,\"%d\", Value" + i + ");\n");
                writer.write ("\t\taxiscCallSetSOAPMethodAttribute(call, \"" +
                       param.getParamName () + "\", \"\", buffer);\n");
                writer.write ("\t}\n");
            }
        } // end for-loop
        
        // new calls from stub base
        writer.write("\n");
        writer.write ("\taxiscStubIncludeSecure(stub);\n");  
        writer.write ("\taxiscStubApplyUserPreferences(stub);\n");
        writer.write("\n");
        
        for (int i = 0; i < paramsB.size(); i++)
        {
            ParameterInfo param = (ParameterInfo) paramsB.get(i);

            // Ignore attributes
            if (param.isAttribute ())
                continue;
            
            // Add elements
            type = wscontext.getTypemap().getType(param.getSchemaName());
            if (type != null)
            {
                if (type.isSimpleType())
                    paraTypeName = CUtils.getclass4qname(type.getBaseType());
                else
                {
                    paraTypeName = type.getLanguageSpecificName();
                    if (CUtils.isSimpleType(paraTypeName))
                        paraTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(param,wscontext);
                    
                    typeisarray = (paraTypeName.lastIndexOf("_Array") > 0);
                    if (!typeisarray)
                        paraTypeName = type.getLanguageSpecificName();
                }
                
                typeisarray |= type.isArray();
            }
            else
            {
                paraTypeName = ((ParameterInfo) paramsB.get (i)).getLangName ();
                typeisarray = false;
            }
 
            if (param.isAnyType ())
                writer.write("\taxiscCallAddAnyObject(call, Value" + i);
            else
            {
                String parameterName = ((ParameterInfo) paramsB.get (i)).getElementNameAsString ();
                String namespace = ((ParameterInfo) paramsB.get (i)).getElementName ().getNamespaceURI ();
    
                if (((ParameterInfo)paramsB.get(i)).isOptional())
                    writer.write("\tif (Value" + i + " != NULL)\n\t{\n");
                else
                    writer.write("\t{\n"); // following was added to instantiate variables on the fly
                
                if (namespace.length () == 0)
                {
                    writer.write ("\tchar cPrefixAndParamName"
                              + i + "[" + "] = \"" + parameterName + "\";\n");
                }
                else
                {
                    int stringLength = 8 + 1 + parameterName.length () + 1;
                    writer.write ("\tchar cPrefixAndParamName" + i + "[" + stringLength + "];\n");
                    writer.write ("\tsprintf( cPrefixAndParamName" + i +
                              ", \"%s:" + parameterName +
                              "\", axiscCallGetNamespacePrefix(call,\"" +  namespace + "\"));\n");
                }
    
                if (param.getType().isAttachment())
                {
                    // TODO
                    String attchType = param.getType().getName().getLocalPart();
                    writer.write("\n\tconst AxiscChar *xmlSoapNsPfx" + i + 
                        " = axiscCallGetNamespacePrefix(call,\"" + 
                        WrapperConstants.APACHE_XMLSOAP_NAMESPACE + "\");\n");
                    writer.write("\tchar attchType" + i + "[64];\n");
                    writer.write("\tstrcpy(attchType" + i + ", xmlSoapNsPfx" + i + ");\n");
                    writer.write("\tstrcat(attchType" + i + ", \":" + attchType + "\");\n");
                    writer.write("\tAXISCHANDLE attrs" + i + "[2];\n");
                    writer.write("\tattrs" + i + "[0] = axiscCallCreateAttribute(call,\"type\", \"xsi\", attchType" + i + 
                        ");\n");
                    writer.write("\tattrs" + i + "[1] = axiscCallCreateAttribute(call,xmlSoapNsPfx" + i + 
                        ", \"xmlns\", \"http://xml.apache.org/xml-soap\");\n");
                    writer.write("\taxiscCallAddAttachmentParameter(call, Value" + i + ", cPrefixAndParamName" + i + 
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
                        writer.write ("\taxiscCallAddBasicArrayParameter(call,");
                        writer.write ("(Axisc_Array *)Value" + i + ", " +
                              CUtils.getXSDTypeForBasicType(containedType) + ", cPrefixAndParamName" + i);
                    }
                    else if (arrayType != null && arrayType.isSimpleType ())
                    {
                        String containedType = CUtils.getclass4qname (arrayType.getBaseType ());
                        writer.write ("\taxiscCallAddBasicArrayParameter(call,");
                        writer.write ("(Axisc_Array *)Value" + i + ", " +
                                  CUtils.getXSDTypeForBasicType(containedType) +
                                  ", cPrefixAndParamName" + i);
                    }
                    else
                    {
                        // Array of complex type
                        String containedType = qname.getLocalPart ();
                        writer.write ("\taxiscCallAddCmplxArrayParameter(call,");
                        writer.write ("(Axisc_Array *)Value" + i +
                                  ", (void*)Axis_Serialize_" + containedType +
                                  ", (void*)Axis_Delete_" + containedType +
                                  ", \"" + parameterName + "\"" + ", ");
                        
                        if (namespace.length () == 0)
                            writer.write ("NULL");
                        else
                            writer.write ("Axis_URI_" + containedType);
                    }
                }
                else if (CUtils.isSimpleType (paraTypeName))
                {
                    if (param.isNillable () 
                            || param.isOptional()
                            || CUtils.isPointerType(paraTypeName))
                    {
                        writer.write ("\taxiscCallAddParameter(call,");
                        writer.write ("(void*)Value" + i + ", cPrefixAndParamName" + i
                                  + ", " + CUtils.getXSDTypeForBasicType(paraTypeName));
                    }
                    else
                    {
                        writer.write ("\taxiscCallAddParameter(call,");
                        writer.write ("(void*)&Value" + i + ", cPrefixAndParamName" + i
                                  + ", " + CUtils.getXSDTypeForBasicType(paraTypeName));
                    }
                }
                else
                {
                    // Complex Type
                    writer.write ("\taxiscCallAddCmplxParameter(call,");
                    writer.write ("Value" + i
                          + ", (void*)Axis_Serialize_" + paraTypeName
                          + ", (void*)Axis_Delete_" + paraTypeName
                          + ", cPrefixAndParamName" + i + ", Axis_URI_" + paraTypeName);
                }              
            }

            writer.write (");\n");
            if (!param.isAnyType ())
                writer.write("\t}\n");            
          } // end for-loop

        writer.write("\n");
        
        writer.write("\tif (AXISC_SUCCESS == axiscCallInvoke(call))\n\t{\n");       
        if (minfo.getOutputMessage () != null)
        {
            writer.write("\t\tif(AXISC_SUCCESS == axiscCallCheckMessage(call, \""
                + minfo.getOutputMessage().getLocalPart() + "\", \""
                + minfo.getOutputMessage().getNamespaceURI() + "\"))\n\t\t{\n");
        }
        
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

                    if (CUtils.isSimpleType(qname))
                    {
                        containedType = CUtils.getclass4qname(qname);
                        
                        writer.write("\n\t\t\tOutValue" + i + " = axiscCallGetBasicArray(call, " 
                                + CUtils.getXSDTypeForBasicType (containedType) 
                                + ", \"" + currentType.getParamName ()
                                + "\", 0);\n\n");
                    }
                    else
                    {
                        containedType = qname.getLocalPart ();
                        writer.write("\n\t\t\tif (OutValue" + i + " != NULL)\n" );
                        writer.write("\t\t{\n");
                        
                        writer.write("\t\t\t\tif (" + currentParamName + " != NULL)\n");
                        writer.write("\t\t\t\t\t" + currentParamName + " = Axis_Delete_" + containedType + "_Array(" + currentParamName + ",0);\n");
                        writer.write("\t\t\t\t" + currentParamName + " = Axis_Create_" + containedType + "_Array(0);\n");
                        
                        writer.write("\t\t\t\taxiscCallGetCmplxArray(call, (Axisc_Array *)" + currentParamName 
                              + ", (void*) Axis_DeSerialize_" + containedType
                              + ", (void*) Axis_Create_" + containedType
                              + ", (void*) Axis_Delete_" + containedType
                              + ", \"" + currentType.getElementNameAsString () 
                              + "\", Axis_URI_" + containedType + ");\n");
                        
                        writer.write("\t\t\t}\n");
                        writer.write("\t\t\telse\n");
                        writer.write("\t\t\t{\n");
                        
                        writer.write("\t\t\t\t/* Unable to return value, but will deserialize to ensure subsequent elements can be correctly processed. */\n");
                        writer.write("\t\t\t\t" + containedType + "_Array * pTemp" + i 
                              + " = Axis_Create_" + containedType + "_Array(0);\n");
                        writer.write("\t\t\t\taxiscCallGetCmplxArray(call, (Axisc_Array *)pTemp" + i 
                              + ", (void*) Axis_DeSerialize_" + containedType
                              + ", (void*) Axis_Create_" + containedType
                              + ", (void*) Axis_Delete_" + containedType
                              + ", \"" + currentType.getElementNameAsString () 
                              + "\", Axis_URI_" + containedType + ");\n");
                        writer.write("\t\t\t\tAxis_Delete_" + containedType + "_Array(pTemp" + i + ", 0);\n");
                        writer.write("\t\t\t}\n");                        
                    }
                }
                else if (typeissimple)
                {
                    if( i > 0)
                        writer.write( "\n");
                    
                    writer.write("\t\t\t{\n"); // begin scope
                    if (CUtils.isPointerType(baseTypeName))
                    {
                        String xsdType =  WrapperUtils.getClassNameFromParamInfoConsideringArrays ((ParameterInfo) paramsC.get (i), wscontext);
                        
                        if( !CUtils.isPointerType(baseTypeName))
                        {
                            if (!baseTypeName.equals(currentParaType))
                                xsdType = currentParaType;

                            xsdType += " *";
                        }
                        
                        writer.write( "\t\t\t" + currentParaType + " pReturn" + i + " = " 
                                + "axiscCall"
                                + CUtils.getParameterGetValueMethodName( baseTypeName, false) 
                                + "(call,  \"" + currentType.getParamName() + "\", 0);\n");
                        writer.write( "\n");
                        writer.write( "\t\t\tif( pReturn" + i + " != NULL && OutValue" + i + " != NULL)\n");
                        writer.write( "\t\t\t{\n");
                        writer.write( "\t\t\t\tif( *OutValue" + i + " != NULL)\n");
                        writer.write( "\t\t\t\t{\n");
                        writer.write( "\t\t\t\t\tint\tiStringSize" + i + " = strlen( (char *) *OutValue" + i + ");\n");
                        writer.write( "\t\t\t\t\tint\tiStrLenValue" + i + " = strlen( pReturn" + i + ");\n");
                        writer.write( "\n");
                        writer.write( "\t\t\t\t\tif( iStrLenValue" + i + " > iStringSize" + i + ")\n");
                        writer.write( "\t\t\t\t\t{\n");
                        writer.write( "\t\t\t\t\t\t*OutValue" + i + " =(" + xsdType + ") axiscAxisNew(XSDC_STRING, iStrLenValue" + i + " + 1);\n");
                        writer.write( "\t\t\t\t\t\tstrcpy( (char *) *OutValue" + i + ", pReturn" + i + ");\n");
                        writer.write( "\t\t\t\t\t}\n");
                        writer.write( "\t\t\t\t\telse\n");
                        writer.write( "\t\t\t\t\t\tstrcpy( (char *) *OutValue" + i + ", pReturn" + i + ");\n");
                        writer.write( "\t\t\t\t}\n");
                        writer.write( "\t\t\t\telse\n");
                        writer.write( "\t\t\t\t{\n");
                        writer.write( "\t\t\t\t\t*OutValue" + i + " = (" + xsdType + ") axiscAxisNew(XSDC_STRING,strlen( pReturn" + i + ") + 1);\n");
                        writer.write( "\t\t\t\t\tstrcpy( (char *) *OutValue" + i + ", pReturn" + i + ");\n");
                        writer.write( "\t\t\t\t}\n");
                        writer.write( "\t\t\t}\n");
                        writer.write( "\n");
                        writer.write( "\t\t\taxiscAxisDelete( (void *) pReturn" + i + ", " + CUtils.getXSDTypeForBasicType( baseTypeName) + ");\n");
                    }
                    else 
                    {
                        writer.write( "\t\t\t" + currentParaType + " * pReturn" + i + " = " 
                                + "axiscCall"
                                + CUtils.getParameterGetValueMethodName( baseTypeName, false) 
                                + "(call,  \"" + currentType.getParamName() + "\", 0);\n");
                        writer.write( "\n");
                        writer.write( "\t\t\tif( pReturn" + i + " != NULL && OutValue" + i + " != NULL)\n");
                        writer.write( "\t\t\t{\n");
                        if (currentType.isNillable() || currentType.isOptional())
                        {
                            writer.write( "\t\t\t\tif( *OutValue" + i + " == NULL)\n");
                            writer.write( "\t\t\t\t\t*OutValue" + i + " = axiscAxisNew(" + CUtils.getXSDTypeForBasicType( baseTypeName) + ", 0);\n");
                            writer.write( "\n");
                            writer.write( "\t\t\t\t*");
                        }
                        else
                            writer.write( "\t\t\t\t");

                        writer.write( "*OutValue" + i + " = *pReturn" + i + ";\n");
                        writer.write( "\t\t\t}\n");
                        writer.write( "\n");
                        writer.write( "\t\t\taxiscAxisDelete( (void *) pReturn" + i + ", " + CUtils.getXSDTypeForBasicType( baseTypeName) + ");\n");
                    }
                    writer.write("\t\t\t}\n"); // end scope
                }
                else if (currentType.isAnyType ())
                {
                    writer.write ("\t\t\t"
                          + currentParamName + " = *(" + currentParaType 
                          + "*)axiscCallGetAnyObject(call);\n");
                }
                else
                {
                    int lastIndexOfStar = currentParaType.lastIndexOf("*");
                    if (lastIndexOfStar > 0)
                        currentParaType = currentParaType.substring(0, lastIndexOfStar);

                    writer.write ("\n\t\t\t"
                              + currentParamName + " = (" + currentParaType
                              + "*)axiscCallGetCmplxObject(call, (void*) Axis_DeSerialize_" + currentParaType 
                              + ", (void*) Axis_Create_" + currentParaType 
                              + ", (void*) Axis_Delete_" + currentParaType + ",\"" 
                              + currentType.getElementNameAsString () + "\", 0);\n");
                }
            }
            
            writer.write ("\t\t}\n");
            writer.write ("\t}\n");
            writer.write ("\taxiscCallUnInitialize(call);\n");
        }
        else if (returntype == null)
        {
            if (minfo.getOutputMessage () != null)
                writer.write ("\t\t\t/*not successful*/\n\t\t}\n");

            writer.write ("\t}\n");
            writer.write ("\taxiscCallUnInitialize(call);\n");
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
                writer.write ("\t\t\tRetArray =(" + containedType + "_Array *) axiscCallGetBasicArray(call, " 
                        + CUtils.getXSDTypeForBasicType (containedType) 
                        + ", \"" + returntype.getParamName () + "\", 0);\n");
            }
            else
            {
                containedType = qname.getLocalPart ();
                writer.write("\t\t\tRetArray = (" + containedType 
                        + "_Array *) axiscCallGetCmplxArray(call, (Axisc_Array *)RetArray, (void*) Axis_DeSerialize_"
                        + containedType 
                        + ", (void*) Axis_Create_" + containedType
                          + ", (void*) Axis_Delete_" + containedType
                          + ", \"" + returntype.getElementNameAsString ()
                          + "\", Axis_URI_" + containedType + ");\n");
            }
            
            writer.write ("\t\t}\n");
            writer.write ("\t}\n");
            writer.write ("\taxiscCallUnInitialize(call);\n");
            writer.write ("\treturn RetArray;\n");
        }
        else if (returntypeissimple)
        {
            if (returntype.isNillable () 
                    || CUtils.isPointerType(outparamType))
            {
                // Just return the pointer as-is - no need to delete.
                writer.write( "\t\t\tRet = axiscCall"
                        + CUtils.getParameterGetValueMethodName( outparamType, false) 
                        + "(call, \"" + returntype.getParamName() + "\", 0);\n");

                writer.write( "\t\t}\n");
            }
            else
            {
                writer.write ("\t\t\t" + outparamType + " * pReturn = " 
                        + "axiscCall"
                        + CUtils.getParameterGetValueMethodName(outparamType, false) 
                        + "(call, \"" + returntype.getSOAPElementNameAsString() + "\", 0);\n");
                
                writer.write ("\t\t\tif(pReturn)\n");
                writer.write ("\t\t\t{\n");
                
                writer.write ("\t\t\t\tRet = *pReturn;\n");
                // TODO - hex and base and any...what about internal pointers?  
                // TODO - need to null out the pointers in the structure.
                writer.write ("\t\t\t\taxiscAxisDelete( (void *) pReturn, " 
                        + CUtils.getXSDTypeForBasicType( outparamType) + ");\n");

                writer.write ("\t\t\t}\n");
                
                writer.write ("\t\t}\n");
            }
            writer.write ("\t}\n");
            writer.write ("\taxiscCallUnInitialize(call);\n");
            writer.write ("\treturn Ret;\n");
        }
        else if (returntype.isAnyType ())
        {
            writer.write ("\t\t\tpReturn = (" + outparamType + "*)axiscCallGetAnyObject(call);\n\t\t}\n");
            writer.write ("\t}\n");
            writer.write ("\taxiscCallUnInitialize(call);\n");
            writer.write ("\treturn pReturn;\n");
        }
        else
        {
            if (outparamType.lastIndexOf ("*") > 0)
            {
                String outparamTypeBase = outparamType.substring (0,outparamType.lastIndexOf("*"));
                writer.write ("\t\t\tpReturn = (" + outparamType +
                          ")axiscCallGetCmplxObject(call, (void*) Axis_DeSerialize_" + outparamTypeBase +
                          ", (void*) Axis_Create_" + outparamTypeBase +
                          ", (void*) Axis_Delete_" + outparamTypeBase + ",\"" +
                          returntype.getElementNameAsString () + "\", 0);\n\t\t}\n");
            }
            else
            {
                writer.write ("\t\t\tpReturn = (" + outparamType
                          + "*)axiscCallGetCmplxObject(call, (void*) Axis_DeSerialize_" + outparamType +
                          ", (void*) Axis_Create_" + outparamType +
                          ", (void*) Axis_Delete_" + outparamType + ",\"" +
                          returntype.getElementNameAsString () + "\", 0);\n\t\t}\n");
            }

            writer.write ("\t}\n");
            writer.write ("\taxiscCallUnInitialize(call);\n");
            writer.write ("\treturn pReturn;\n");
        }

        //write end of method
        writer.write("}\n");
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.c.CFileWriter#writeGlobalCodes()
     */
    protected void writeGlobalCodes() throws WrapperFault 
    {
    }
}
