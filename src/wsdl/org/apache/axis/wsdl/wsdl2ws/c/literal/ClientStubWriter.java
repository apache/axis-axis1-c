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
          // get_xxx_stub() routine
          writer.write("AXISCHANDLE get_" + classname + "_stub(const char* pchEndPointUri)\n{\n");
          writer.write("\tif(pchEndPointUri)\n");
          writer.write("\t\treturn axiscCreateStub(pchEndPointUri, AXISC_PTHTTP1_1);\n");
          writer.write("\telse\n");
          writer.write("\t\treturn axiscCreateStub(\"" 
                  + wscontext.getWrapInfo().getTargetEndpointURI() 
                  + "\", AXISC_PTHTTP1_1);\n");
          writer.write("}\n\n");
          
          // destroy_xxxx_stub()
          writer.write("void destroy_" + classname + "_stub(AXISCHANDLE p)\n{\n");
          writer.write("\taxiscDestroyStub(p);\n}\n\n");

          // get_xxxx_Status() routine
          writer.write("int get_" + classname + "_Status(AXISCHANDLE stub)\n{\n");
          writer.write("\tAXISCHANDLE call = axiscGetCall(stub);\n");
          writer.write("\treturn axiscGetStatusCall(call);\n");
          writer.write("}\n\n");

          writer.write("/* Functions corresponding to the web service methods*/\n");
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
        boolean aretherearrayparams = false;
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
        else if (returntypeisarray
                || (returntypeissimple 
                        && (!returntype.isNillable() || CUtils.isPointerType(outparamType))))
            writer.write(outparamType);
        else if (outparamType.lastIndexOf("*") > 0)
            writer.write(outparamType);
        else // for AnyType too
            writer.write(outparamType + "*");
   
        writer.write(" " + methodName + "(AXISCHANDLE stub");
        ArrayList paramsB = (ArrayList) params;
        for (int i = 0; i < paramsB.size(); i++)
        {
            paraTypeName =
                WrapperUtils.getClassNameFromParamInfoConsideringArrays((ParameterInfo) paramsB.get(i),wscontext);
            writer.write(", " + paraTypeName + " Value" + i);
            
            if ((type = wscontext.getTypemap().getType(((ParameterInfo) paramsB.get(i)).getSchemaName())) != null
                    && type.isArray())
                aretherearrayparams = true;
        }
        
        // Multiples parameters so fill the methods prototype
        ArrayList paramsC = (ArrayList) minfo.getOutputParameterTypes();
        if (isAllTreatedAsOutParams)
            for (int i = 0; i < paramsC.size(); i++)
            {
                type = wscontext.getTypemap().getType(((ParameterInfo) paramsC.get(i)).getSchemaName());
                writer.write(", AXIS_OUT_PARAM  "
                        + WrapperUtils.getClassNameFromParamInfoConsideringArrays(
                                        (ParameterInfo) paramsC.get(i), wscontext) + "* OutValue" + i);
                if ((type = wscontext.getTypemap().getType(((ParameterInfo) paramsC.get(i)).getSchemaName())) != null
                        && type.isArray())
                    aretherearrayparams = true;
            }
        
        writer.write(")\n{\n");
        if (aretherearrayparams || returntypeisarray)
            writer.write("\tAxisc_Array array;\n");
        
        writer.write("\tAXISCHANDLE call = axiscGetCall(stub);\n");
        if (returntype != null)
        {
            writer.write("\t");
            if (returntypeisarray)
                writer.write(outparamType + " RetArray = {NULL, 0, XSD_UNKNOWN};\n");
            else if (!returntypeissimple)
            {
                // for AnyType and complex types
                if (outparamType.lastIndexOf("*") > 0)
                    writer.write(outparamType + " pReturn = NULL;\n");
                else
                    writer.write(outparamType + "* pReturn = NULL;\n");
            }
            else if (returntype.isNillable() && !(CUtils.isPointerType(outparamType)))
                writer.write(outparamType + "* Ret = NULL;\n");
            else
            {
                String initValue = CUtils.getInitValue(outparamType);
                if (initValue != null)
                    writer.write(outparamType + " Ret = " + initValue + ";\n");
                else if (outparamType.equals("xsd__base64Binary")
                        || outparamType.equals("xsd__hexBinary"))
                {
                    writer.write(outparamType + " Ret;\n");
                    writer.write("\tRet.__ptr = NULL;\n");
                    writer.write("\tRet.__size = 0;\n");
                }
                else if (outparamType.equals("xsd__dateTime")
                        || outparamType.equals("xsd__date")
                        || outparamType.equals("xsd__time"))
                {
                    writer.write(outparamType + " Ret;\n");
                    writer.write("\tmemset(&Ret,0,sizeof(" + outparamType + "));\n");
                }
                else
                    writer.write(outparamType + " Ret;\n");
                // TODO initialize return parameter appropriately.
            }
        }
        
        writer.write ("\tconst char* pcCmplxFaultName;\n");
        writer.write ("\tpcCmplxFaultName = NULL;\n");

        writer.write("\t/* Following will establish the connections with the server too */\n");
        writer.write("\tif (AXISC_SUCCESS != axiscInitializeCall(call, C_DOC_PROVIDER " + ")) return ");
        
        if (returntype != null)
            writer.write((returntypeisarray ? "RetArray" : returntypeissimple ? "Ret" : "pReturn") + ";\n");
        else
            writer.write(";\n");

        writer.write("\tif (NULL==axiscGetTransportPropertyCall(call,\"SOAPAction\",0))\n");
        writer.write("\t\taxiscSetTransportPropertyCall(call,AXISC_SOAPACTION_HEADER , \""
                + minfo.getSoapAction() + "\");\n");
        writer.write("\taxiscSetSOAPVersionCall(call, SOAP_VER_1_1);\n");
        //TODO check which version is it really.
        writer.write("\taxiscSetOperationCall(call, \""
                + minfo.getInputMessage().getLocalPart() + "\", \""
                + minfo.getInputMessage().getNamespaceURI() + "\");\n");

        // TODO add attributes to soap method

        // new calls from stub base
        writer.write ("\taxiscIncludeSecure(stub);\n");  
        writer.write ("\taxiscApplyUserPreferences(stub);\n");
          
        for (int i = 0; i < paramsB.size(); i++)
        {
            ParameterInfo param = (ParameterInfo) paramsB.get(i);

            // Ignore attributes, while adding elements
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
                paraTypeName = param.getLangName();
                typeisarray = false;
            }
            
            typeissimple = CUtils.isSimpleType(paraTypeName);
            if (typeisarray)
            {
                //arrays
                QName qname = WrapperUtils.getArrayType(type).getName();
                String containedType = null;
                if (CUtils.isSimpleType(qname))
                {
                    containedType = CUtils.getclass4qname(qname);
                    writer.write("\taxiscAddBasicArrayParameterCall(call, ");
                    writer.write("(Axisc_Array*)(&Value" + i + "), "
                            + CUtils.getXSDTypeForBasicType(containedType) + ", \""
                            + param.getElementNameAsString() + "\"");
                }
                else
                {
                    containedType = qname.getLocalPart();
                    writer.write("\taxiscAddCmplxArrayParameterCall(call, ");
                    writer.write("(Axisc_Array*)(&Value" + i
                                 + "), (void*)Axis_Serialize_" + containedType
                                 + ", (void*)Axis_Delete_" + containedType
                                 + ", (void*) Axis_GetSize_" + containedType
                                 + ", \""
                                 + param.getElementNameAsString()
                                 + "\", Axis_URI_" + containedType);
                }
            }
            else if (typeissimple)
            {
                writer.write("\taxiscAddParameterCall(call, ");
                if (param.isNillable() || CUtils.isPointerType(paraTypeName))
                    writer.write("(void*)Value" + i + ", \"" 
                            + param.getElementNameAsString()
                            + "\", " + CUtils.getXSDTypeForBasicType(paraTypeName));
                else
                    writer.write("(void*)&Value" + i + ", \"" 
                            + param.getElementNameAsString()
                            + "\", " + CUtils.getXSDTypeForBasicType(paraTypeName));
            }
            else if (param.isAnyType())
                writer.write("\taxiscAddAnyObjectCall(call, Value" + i);
            else
            {
                // for complex types
                writer.write( "\taxiscAddCmplxParameterCall(call, ");
                writer.write( "Value"
                                + i
                                + ", (void*)Axis_Serialize_" + paraTypeName
                                + ", (void*)Axis_Delete_" + paraTypeName
                                + ", \""
                                + param.getElementNameAsString()
                                + "\", Axis_URI_" + paraTypeName);
            }
            writer.write(");\n");
          }
        
        writer.write("\tif (AXISC_SUCCESS == axiscInvokeCall(call))\n\t{\n");
        writer.write("\t\tif(AXISC_SUCCESS == axiscCheckMessageCall(call, \""
                + minfo.getOutputMessage().getLocalPart() + "\", \""
                + minfo.getOutputMessage().getNamespaceURI() + "\"))\n\t\t{\n");
        
        if (isAllTreatedAsOutParams)
        {
            String currentParamName;
            String currentParaType;
            for (int i = 0; i < paramsC.size(); i++)
            {
                ParameterInfo currentType = (ParameterInfo) paramsC.get(i);
                type = wscontext.getTypemap().getType(currentType.getSchemaName());
                if (type != null)
                {
                    if (type.isSimpleType())
                        currentParaType = CUtils.getclass4qname(type.getBaseType());
                    else
                        currentParaType = type.getLanguageSpecificName();
                    typeisarray = type.isArray();
                }
                else
                {
                    currentParaType = ((ParameterInfo) paramsC.get(i)).getLangName();
                    typeisarray = false;
                }
                
                typeissimple = CUtils.isSimpleType(currentParaType);

                if (CUtils.isPointerType(currentParaType))
                    currentParamName = "*OutValue" + i;
                else
                    currentParamName = "OutValue" + i;
                
                // Some code need to be merged as we have some duplicated in coding here.
                if (typeisarray)
                {
                    QName qname = WrapperUtils.getArrayType(type).getName();
                    String containedType = null;
                    if (CUtils.isSimpleType(qname))
                    {
                        containedType = CUtils.getclass4qname(qname);
                        writer.write("\t\t\tarray = axiscGetBasicArrayCall(call, "
                                     + CUtils.getXSDTypeForBasicType(containedType) + ", \""
                                     + currentType.getElementNameAsString() + "\", 0);\n");
                    }
                    else
                    {
                        containedType = qname.getLocalPart();
                        writer.write("\t\t\tarray = axiscGetCmplxArrayCall(call, (void*) Axis_DeSerialize_"
                                     + containedType);
                        writer.write(", (void*) Axis_Create_" + containedType
                                     + ", (void*) Axis_Delete_" + containedType
                                     + ", (void*) Axis_GetSize_" + containedType
                                     + ", \""
                                     + currentType.getElementNameAsString()
                                     + "\", Axis_URI_" + containedType
                                     + ");\n");

                    }
                    writer.write("\t\t\tmemcpy(OutValue" + i + ", &array, sizeof(Axisc_Array));\n");                    
                }
                else if (typeissimple)
                {
                    writer.write( "\t\t\t"
                                  + currentParamName + " = "
                                  + CUtils.getParameterGetValueMethodName( currentParaType, false)
                                  + "(call, \""  + currentType.getElementNameAsString() + "\", 0);\n");
                }
                else if (currentType.isAnyType())
                {
                    writer.write( "\t\t\t"
                                  + currentParamName
                                  + " = (" + currentParaType + "*)axiscGetAnyObjectCall(call);\n");
                }
                else if (currentParaType.lastIndexOf ("*") > 0)
                {
                    writer.write( "\t\t\t"
                                  + currentParamName
                                  + " = ("
                                  + currentParaType
                                  + ")axiscGetCmplxObjectCall(call, (void*) Axis_DeSerialize_"
                                  + currentParaType
                                  + ", (void*) Axis_Create_" + currentParaType
                                  + ", (void*) Axis_Delete_" + currentParaType
                                  + ",\""
                                  + currentType.getElementNameAsString()
                                  + "\", 0);\n");                      
                }
                else
                {
                    writer.write( "\t\t\t"
                                  + currentParamName
                                  + " = ("
                                  + currentParaType
                                  + "*)axiscGetCmplxObjectCall(call, (void*) Axis_DeSerialize_"
                                  + currentParaType
                                  + ", (void*) Axis_Create_" + currentParaType
                                  + ", (void*) Axis_Delete_" + currentParaType
                                  + ",\""
                                  + currentType.getElementNameAsString()
                                  + "\", 0);\n");
                 }
            }
            
            writer.write("\t\t}\n");
            writer.write( "\t}\n\taxiscUnInitializeCall(call);\n");
        }
        else if (returntype == null)
        {
            writer.write("\t\t\t/*not successful*/\n\t\t}\n");
            writer.write("\t}\n\taxiscUnInitializeCall(call);\n");
        }
        else if (returntypeisarray)
        {
            QName qname = null;
            if (WrapperUtils.getArrayType (retType) != null)
                qname = WrapperUtils.getArrayType (retType).getName ();
            else
                qname = retType.getName ();
            
            String containedType = null;
            if (CUtils.isSimpleType(qname))
            {
                containedType = CUtils.getclass4qname(qname);
                writer.write( "\tarray = axiscGetBasicArrayCall(call, "
                                + CUtils.getXSDTypeForBasicType(containedType)
                                + ", \"" + returntype.getElementNameAsString() + "\", 0);\n");
            }
            else
            {
                containedType = qname.getLocalPart();
                writer.write( "\tarray = axiscGetCmplxArrayCall(call, (void*) Axis_DeSerialize_"
                                + containedType);
                writer.write( ", (void*) Axis_Create_" + containedType
                                + ", (void*) Axis_Delete_" + containedType
                                + ", (void*) Axis_GetSize_" + containedType
                                + ", \""
                                + returntype.getElementNameAsString()
                                + "\", Axis_URI_" + containedType
                                + ");\n");
            }
            
            writer.write("\tmemcpy(&RetArray, &array, sizeof(Axisc_Array));\n");            
            writer.write("\t\t}\n");
            writer.write( "\t}\n\taxiscUnInitializeCall(call);\n");
            writer.write("\treturn RetArray;\n");
        }
        else if (returntypeissimple)
        {
            if (returntype.isNillable ())
            {
                writer.write( "\t\t\tRet = "
                              + CUtils.getParameterGetValueMethodName( outparamType, false)
                              + "(call, \"" + returntype.getElementNameAsString() + "\", 0);\n");
            }
            else if (CUtils.isPointerType(outparamType))
            {
                writer.write( "\t\t\t" + outparamType 
                              + " pReturn = " 
                              + CUtils.getParameterGetValueMethodName( outparamType, false)
                              + "(call, \"" + returntype.getElementNameAsString() + "\", 0);\n");           
                writer.write ("\t\t\tif(pReturn)\n");
                writer.write ("\t\t\t\tRet = pReturn;\n");
            }
            else
            {
                writer.write( "\t\t\t" + outparamType 
                              + " *pReturn = " 
                              + CUtils.getParameterGetValueMethodName( outparamType, false)
                              + "(call, \"" + returntype.getElementNameAsString() + "\", 0);\n");           
                writer.write ("\t\t\tif(pReturn)\n");
                writer.write ("\t\t\t\tRet = *pReturn;\n");
            }

            writer.write("\t\t}\n");
            writer.write("\t}\n\taxiscUnInitializeCall(call);\n");
            writer.write("\treturn Ret;\n");
        }
        else if (returntype.isAnyType())
        {
            writer.write( "\t\t\tpReturn = (" + outparamType + "*)axiscGetAnyObjectCall(call);\n\t\t}\n");
            writer.write( "\t}\n\taxiscUnInitialize(call);\n");
            writer.write("\treturn pReturn;\n");
        }
        else
        {
            if (outparamType.lastIndexOf ("*") > 0)
            {
                String outparamTypeBase = outparamType.substring (0, outparamType.lastIndexOf("*"));

                writer.write( "\t\t\tpReturn = ("
                              + outparamType
                              + ")axiscGetCmplxObjectCall(call, (void*) Axis_DeSerialize_" + outparamTypeBase
                              + ", (void*) Axis_Create_" + outparamTypeBase
                              + ", (void*) Axis_Delete_" + outparamTypeBase
                              + ",\"" + returntype.getElementNameAsString() + "\", 0);\n");
            }
            else
            {
                writer.write( "\t\t\tpReturn = ("
                              + outparamType
                              + "*)axiscGetCmplxObjectCall(call, (void*) Axis_DeSerialize_" + outparamType
                              + ", (void*) Axis_Create_" + outparamType
                              + ", (void*) Axis_Delete_" + outparamType
                              + ",\"" + returntype.getElementNameAsString() + "\", 0);\n");
            }
            
            writer.write("\t\t}\n");
            writer.write("\t}\n\taxiscUnInitializeCall(call);\n");
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
                writer.write("extern int Axis_DeSerialize_" + typeName
                             + "(" + typeName + "* param, AXISCHANDLE pDZ);\n");
                writer.write("extern void* Axis_Create_" + typeName
                             + "(" + typeName + " *Obj, AxiscBool bArray, int nSize);\n");
                writer.write("extern void Axis_Delete_" + typeName
                             + "(" + typeName + "* param, AxiscBool bArray, int nSize);\n");
                writer.write("extern int Axis_Serialize_" + typeName
                             + "(" + typeName + "* param, AXISCHANDLE pSZ, AxiscBool bArray);\n");
                writer.write("extern int Axis_GetSize_" + typeName + "();\n\n");
            }
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
