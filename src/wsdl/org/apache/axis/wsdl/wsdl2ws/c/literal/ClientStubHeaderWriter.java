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
package org.apache.axis.wsdl.wsdl2ws.c.literal;
import java.io.IOException;
import java.util.Iterator;
import java.util.Vector;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ClientStubHeaderWriter
    extends org.apache.axis.wsdl.wsdl2ws.c.ClientStubHeaderWriter
{
    /**
     * @param wscontext
     * @throws WrapperFault
     */
    public ClientStubHeaderWriter(WebServiceContext wscontext)
        throws WrapperFault
    {
        super(wscontext);
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
     */
    protected void writeMethods() throws WrapperFault
    {
        MethodInfo minfo;
        try
        {
            writer.write("\n");
            writer.write("/* --- Functions relating to web service client proxy --- */\n");
            writer.write("extern AXISCHANDLE get_" + classname + "_stub(const char* pchEndPointUri);\n");
            writer.write("extern void destroy_" + classname + "_stub(AXISCHANDLE pStub);\n");
            writer.write("extern int get_" + classname + "_Status(AXISCHANDLE pStub);\n");

            writer.write("\n");
            writer.write("/* --- Functions relating to web service methods --- */\n");

            for (int i = 0; i < methods.size(); i++)
            {
                minfo = (MethodInfo) this.methods.get(i);
                boolean isAllTreatedAsOutParams = false;
                int noOfOutParams = minfo.getOutputParameterTypes().size();
                
                //write return type
                if (0 == noOfOutParams)
                    writer.write("extern void ");
                else if (1 == noOfOutParams)
                {
                    ParameterInfo returnParam =
                        (ParameterInfo) minfo.getOutputParameterTypes().iterator().next();
                    String outParamTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(returnParam, wscontext);
                    if ((outParamTypeName.lastIndexOf ("_Array") > 0) 
                            || (CUtils.isSimpleType(outParamTypeName)
                            && (returnParam.isNillable() || returnParam.isOptional())
                            && !(CUtils.isPointerType(outParamTypeName))))
                        writer.write("extern " + outParamTypeName + " * ");
                    else
                        writer.write("extern " + outParamTypeName + " ");
                }
                else
                {
                    isAllTreatedAsOutParams = true;
                    writer.write("extern void ");
                }
                
                //write return type
                writer.write(minfo.getMethodname() + "(AXISCHANDLE pStub");                

                //write parameter names 
                boolean hasInputParms = false;
                Iterator params = minfo.getInputParameterTypes().iterator();
                for (int j = 0; params.hasNext(); j++)
                {

                    writer.write(", ");
                    hasInputParms = true;
                    ParameterInfo nparam = (ParameterInfo) params.next();
                    String paramTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(nparam, wscontext);
                    Type type = nparam.getType();
                    String baseTypeName = null;
                    
                    if (type.isSimpleType())
                        baseTypeName = CUtils.getclass4qname (type.getBaseType ());
                    else
                        baseTypeName = paramTypeName;
                    
                    if (nparam.getType().isAttachment())
                        writer.write("AXISCHANDLE *Value" + j);
                    else if ((paramTypeName.lastIndexOf ("_Array") > 0)
                                || (CUtils.isSimpleType(baseTypeName)
                                        && (nparam.isNillable() || nparam.isOptional())
                                        && !(CUtils.isPointerType(baseTypeName))))
                        writer.write(paramTypeName + " * Value" + j);
                    else
                        writer.write(paramTypeName + " Value" + j);
                }

                if (isAllTreatedAsOutParams)
                {
                    params = minfo.getOutputParameterTypes().iterator();
                    for (int j = 0; params.hasNext(); j++)
                    {
                        ParameterInfo nparam = (ParameterInfo) params.next();
                        String paramType = WrapperUtils.getClassNameFromParamInfoConsideringArrays( nparam, wscontext);
                        Type type = nparam.getType();
                        String baseTypeName = null;
                        
                        if (type.isSimpleType())
                            baseTypeName = CUtils.getclass4qname (type.getBaseType ());
                        else
                            baseTypeName = paramType;
                        
                        boolean bTypeHasStar = paramType.endsWith( "*");
                        

                        writer.write(", ");
                        
                        writer.write("AXIS_OUT_PARAM " + paramType);
                        if (CUtils.isSimpleType(baseTypeName))
                        {
                            if ((nparam.isOptional() 
                                    || nparam.isNillable()) 
                                    && !CUtils.isPointerType(baseTypeName))
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
                        
                        writer.write(" OutValue" + j);
                    } // for loop
                }
                writer.write(");\n");
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
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
            writer.write("#include <axis/Axis.h>\n");
            writer.write("#include <axis/GDefine.h>\n");
            writer.write("#include <axis/AxisUserAPI.h>\n");
            writer.write("#include <axis/SoapEnvVersions.h>\n");
            writer.write("#include <axis/WSDDDefines.h>\n");
            writer.write("#include <axis/TypeMapping.h>\n");
            writer.write("#include <axis/client/Stub.h>\n");
            writer.write("#include <axis/client/Call.h>\n");
            writer.write("\n");
            
            Type atype;
            Iterator types = this.wscontext.getTypemap().getTypes().iterator();
            Vector typeSet = new Vector();
            while (types.hasNext())
            {
                atype = (Type) types.next();
                if (atype.getLanguageSpecificName().startsWith(">"))
                    continue;
                if (!atype.isArray())
                    typeSet.insertElementAt(atype.getLanguageSpecificName(), 0);
                else
                    typeSet.add(atype.getLanguageSpecificName());
            }
            Iterator itr = typeSet.iterator();
            while (itr.hasNext())
            {
                writer.write("#include \"" + itr.next().toString() + CUtils.C_HEADER_SUFFIX + "\"\n");
            }
            writer.write("\n");
        }
        catch (IOException e)
        {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }
}
