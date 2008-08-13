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

package org.apache.axis.wsdl.wsdl2ws.c;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ClientStubHeaderWriter extends HeaderFileWriter
{
    protected ArrayList methods;

    /**
     * @param wscontext
     * @throws WrapperFault
     */
    public ClientStubHeaderWriter(WebServiceContext wscontext)
        throws WrapperFault
    {
        super(wscontext.getServiceInfo().getServicename());
        this.wscontext = wscontext;
        this.methods = wscontext.getServiceInfo().getMethods();
    }
    
    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#writeClassComment()
     */
    protected void writeClassComment() throws WrapperFault
    {
        try
        {
            writer.write("/*\n");
            writer.write(" * This file was auto-generated by the Axis C++ Web Service "
                    + "Generator (WSDL2Ws)\n");
            writer.write(" * This file contains Client Stub for remote web service \n");
            writer.write(" */\n\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
    
    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#writeAttributes()
     */
    protected void writeAttributes() throws WrapperFault
    {}



    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#writeMethods()
     */
    protected void writeMethods() throws WrapperFault
    {
        MethodInfo minfo;
        try
        {
            writer.write("\n");
            writer.write("/* ********************************************************************* */\n");
            writer.write("/* --- Functions relating to web service client proxy                --- */\n");
            writer.write("/* ********************************************************************* */\n");
            writer.write("\n");

            writer.write("extern AXISCHANDLE get_" + classname + "_stub(const char* pchEndPointUri);\n");
            writer.write("extern void destroy_" + classname + "_stub(AXISCHANDLE pStub);\n");
            writer.write("extern int get_" + classname + "_Status(AXISCHANDLE pStub);\n");

            writer.write("\n");
            writer.write("/* ********************************************************************* */\n");
            writer.write("/* --- Functions relating to web service methods                     --- */\n");
            writer.write("/* ********************************************************************* */\n");
            writer.write("\n");

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
                Iterator params = minfo.getInputParameterTypes().iterator();
                if (params.hasNext())
                {
                    writer.write(", ");   
                    
                    ParameterInfo fparam = (ParameterInfo) params.next();
                    String paramTypeName = WrapperUtils
                    .getClassNameFromParamInfoConsideringArrays(
                            fparam,
                            wscontext);
                    if ((paramTypeName.lastIndexOf ("_Array") > 0)
                            ||(CUtils.isSimpleType(paramTypeName)
                            && fparam.isNillable()
                            && !(CUtils.isPointerType(paramTypeName))))
                    {
                        writer.write(
                                paramTypeName
                                    + " * Value"
                                    + 0);
                     }
                    else
                    {
                        writer.write(
                            paramTypeName
                                + " Value"
                                + 0);
                    }
                }
                
                for (int j = 1; params.hasNext(); j++)
                {
                    writer.write(", ");
                    
                    ParameterInfo nparam = (ParameterInfo) params.next();
                    String paramTypeName = WrapperUtils
                    .getClassNameFromParamInfoConsideringArrays(
                            nparam,
                            wscontext);
                    if (CUtils.isSimpleType(paramTypeName)
                            && nparam.isNillable()
                            && !(CUtils.isPointerType(paramTypeName)))
                    {
                        writer.write(", "
                                + paramTypeName
                                + " * Value"
                                + j);
                    }
                    else
                    {
                        writer.write(", "
                                + paramTypeName
                                + " Value"
                                + j);
                    }
                }

                if (isAllTreatedAsOutParams)
                {
                    params = minfo.getOutputParameterTypes().iterator();
                    for (int j = 0; params.hasNext(); j++)
                    {
                        ParameterInfo nparam = (ParameterInfo) params.next();
                        writer.write(
                            ", AXISC_OUT_PARAM "
                                + WrapperUtils
                                    .getClassNameFromParamInfoConsideringArrays(
                                    nparam,
                                    wscontext)
                                + " *OutValue"
                                + j);
                    }
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

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writePreprocssorStatements()
     */
    protected void writePreprocessorStatements() throws WrapperFault
    {
        try
        {
            writer.write("#include <axis/client/Stub.h>\n");
            writer.write("#include <axis/AxisWrapperAPI.h>\n");
            Type atype;
            Iterator types = this.wscontext.getTypemap().getTypes().iterator();
            HashSet typeSet = new HashSet();
            String typeName = null;
            while (types.hasNext())
            {
                atype = (Type) types.next();
                if (atype.isAnonymous() && !atype.isExternalized())
                    continue;

                typeName = WrapperUtils.getLanguageTypeName4Type(atype);
                if (null != typeName)
                    typeSet.add(typeName);
            }
            
            Iterator itr = typeSet.iterator();
            while (itr.hasNext())
            {
                writer.write("#include \"" + itr.next().toString() + CUtils.C_HEADER_SUFFIX+"\"\n");
            }
            writer.write("\n");
        }
        catch (IOException e)
        {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    /**
     * @return
     */
    protected String getFileType()
    {
        return "ClientStub";
    }
}
