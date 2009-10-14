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
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ClientStubHeaderWriter
    extends org.apache.axis.wsdl.wsdl2ws.c.ClientStubHeaderWriter
{
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
            c_writer.write("\n");
            c_writer.write("/* ********************************************************************* */\n");
            c_writer.write("/* --- Functions relating to web service client proxy                --- */\n");
            c_writer.write("/* ********************************************************************* */\n");
            c_writer.write("\n");
            c_writer.write("extern AXISCHANDLE get_" + c_classname + "_stub(const char* pchEndPointUri);\n");
            c_writer.write("extern void destroy_" + c_classname + "_stub(AXISCHANDLE pStub);\n");
            c_writer.write("extern int get_" + c_classname + "_Status(AXISCHANDLE pStub);\n");
            c_writer.write("extern void set_" + c_classname + "_ExceptionHandler(AXISCHANDLE pStub, AXIS_EXCEPTION_HANDLER_FUNCT fp);\n");
            c_writer.write("\n");
            c_writer.write("/* ********************************************************************* */\n");
            c_writer.write("/* --- Functions relating to web service methods                     --- */\n");
            c_writer.write("/* ********************************************************************* */\n");
            c_writer.write("\n");

            for (int i = 0; i < methods.size(); i++)
            {
                minfo = (MethodInfo) this.methods.get(i);
                boolean isAllTreatedAsOutParams = false;
                int noOfOutParams = minfo.getOutputParameterTypes().size();
                
                //write return type
                if (0 == noOfOutParams)
                    c_writer.write("extern void ");
                else if (1 == noOfOutParams)
                {
                    ParameterInfo returnParam =
                        (ParameterInfo) minfo.getOutputParameterTypes().iterator().next();
                    String outParamTypeName = CUtils.getClassNameFromParamInfoConsideringArrays(returnParam, wscontext);
                    if ((outParamTypeName.lastIndexOf ("_Array") > 0) 
                            || (CUtils.isSimpleType(outParamTypeName)
                            && (returnParam.isNillable() || returnParam.isOptional())
                            && !(CUtils.isPointerType(outParamTypeName))))
                        c_writer.write("extern " + outParamTypeName + " * ");
                    else
                        c_writer.write("extern " + outParamTypeName + " ");
                }
                else
                {
                    isAllTreatedAsOutParams = true;
                    c_writer.write("extern void ");
                }
                
                // write operation prototype
                // Operation name may conflict with a C type, so if it does, need to make unique.
                String methodName = minfo.getMethodname();
                int ii = 0;
                while (wscontext.getTypemap().doesTypeExist(methodName))
                {
                    methodName = minfo.getMethodname() + ii++;
                }
                c_writer.write(methodName + "(AXISCHANDLE pStub");                

                //write parameter names 
                Iterator params = minfo.getInputParameterTypes().iterator();
                for (int j = 0; params.hasNext(); j++)
                {
                    c_writer.write(", ");
                    ParameterInfo nparam = (ParameterInfo) params.next();
                    String paramTypeName = CUtils.getClassNameFromParamInfoConsideringArrays(nparam, wscontext);
                    Type type = nparam.getType();
                    String baseTypeName = null;
                    
                    if (type.isSimpleType())
                        baseTypeName = CUtils.getSimpleType (type.getBaseType ());
                    else
                        baseTypeName = paramTypeName;
                    
                    if (nparam.getType().isAttachment())
                        c_writer.write("AXISCHANDLE *Value" + j);
                    else if ((paramTypeName.lastIndexOf ("_Array") > 0)
                                || (CUtils.isSimpleType(baseTypeName)
                                        && (nparam.isNillable() || nparam.isOptional())
                                        && !(CUtils.isPointerType(baseTypeName))))
                        c_writer.write(paramTypeName + " * Value" + j);
                    else
                        c_writer.write(paramTypeName + " Value" + j);
                }

                if (isAllTreatedAsOutParams)
                {
                    params = minfo.getOutputParameterTypes().iterator();
                    for (int j = 0; params.hasNext(); j++)
                    {
                        ParameterInfo nparam = (ParameterInfo) params.next();
                        String paramType = CUtils.getClassNameFromParamInfoConsideringArrays( nparam, wscontext);
                        Type type = nparam.getType();
                        String baseTypeName = null;
                        
                        if (type.isSimpleType())
                            baseTypeName = CUtils.getSimpleType (type.getBaseType ());
                        else
                            baseTypeName = paramType;
                        
                        boolean bTypeHasStar = paramType.endsWith( "*");
                        

                        c_writer.write(", ");
                        
                        c_writer.write("AXISC_OUT_PARAM " + paramType);
                        if (CUtils.isSimpleType(baseTypeName))
                        {
                            if ((nparam.isOptional() 
                                    || nparam.isNillable()) 
                                    && !CUtils.isPointerType(baseTypeName))
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
                        
                        c_writer.write(" OutValue" + j);
                    } // for loop
                }
                c_writer.write(");\n");
            }
        }
        catch (Exception e)
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
            c_writer.write("#include <axis/Axis.h>\n");
            c_writer.write("#include <axis/GDefine.h>\n");
            c_writer.write("#include <axis/AxisUserAPI.h>\n");
            c_writer.write("#include <axis/SoapEnvVersions.h>\n");
            c_writer.write("#include <axis/WSDDDefines.h>\n");
            c_writer.write("#include <axis/TypeMapping.h>\n");
            c_writer.write("#include <axis/ISoapFault.h>\n");
            c_writer.write("#include <axis/client/Stub.h>\n");
            c_writer.write("#include <axis/client/Call.h>\n");
            c_writer.write("\n");
            
            Type atype;
            Iterator types = this.wscontext.getTypemap().getTypes().iterator();
            HashSet typeSet = new HashSet();
            HashSet removeSet = new HashSet();

            while (types.hasNext())
            {
                atype = (Type) types.next();
                
                if (!atype.isExternalized())
                    continue;

                if (atype.isArray())
                    if (atype.getElementType().equals("string"))
                        removeSet.add(atype.getLanguageSpecificName());
                
                if (atype.getBaseType() != null)
                    if (atype.getBaseType().getLocalPart().equals("string"))
                        removeSet.add(atype.getLanguageSpecificName() + "_Array");

                if (atype.isRestriction())
                    removeSet.add(atype.getLanguageSpecificName()  + "_Array");

                typeSet.add(atype.getLanguageSpecificName());
            }
            
            Iterator ritr = removeSet.iterator();
            while (ritr.hasNext())
                typeSet.remove(ritr.next());
            
            Iterator itr = typeSet.iterator();
            while (itr.hasNext())
            {
                c_writer.write("#include \"" + itr.next().toString() + CUtils.getHeaderFileExtension() + "\"\n");
            }
            c_writer.write("\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
