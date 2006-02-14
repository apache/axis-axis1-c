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

package org.apache.axis.wsdl.wsdl2ws.cpp;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.FaultInfo;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ServiceHeaderWriter extends HeaderFileWriter
{
    protected ArrayList methods;
    public ServiceHeaderWriter(WebServiceContext wscontext) throws WrapperFault
    {
        super(
            WrapperUtils.getClassNameFromFullyQualifiedName(
                wscontext.getSerInfo().getQualifiedServiceName()));
        this.wscontext = wscontext;
        this.methods = wscontext.getSerInfo().getMethods();
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeClassComment()
     */
    protected void writeClassComment() throws WrapperFault
    {
        try
        {
            writer.write("/*\n");
            writer.write(
                " * This is the Service Class genarated by the tool WSDL2Ws\n");
            writer.write(
                " * "
                    + classname
                    + CUtils.CPP_HEADER_SUFFIX
                    + ": interface for the "
                    + classname
                    + "class.\n");
            writer.write(" *\n");
            writer.write(" */\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeConstructors()
     */
    protected void writeConstructors() throws WrapperFault
    {
        try
        {
            writer.write("\tpublic:\n\t\t" + classname + "();\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
     */
    protected void writeDestructors() throws WrapperFault
    {
        try
        {
            writer.write("\tpublic:\n\t\tvirtual ~" + classname + "();\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
     */
    protected void writeMethods() throws WrapperFault
    {
        MethodInfo minfo;
        try
        {
            writer.write("\tpublic: \n");
            writer.write("\t\tvoid onFault();\n");
            //writer.write("\t\tvoid init();\n");
            //writer.write("\t\tvoid fini();\n");
            for (int i = 0; i < methods.size(); i++)
            {
                minfo = (MethodInfo) this.methods.get(i);
                boolean isAllTreatedAsOutParams = false;
                ParameterInfo returntype = null;
                int noOfOutParams = minfo.getOutputParameterTypes().size();
                if (0 == noOfOutParams)
                {
                    returntype = null;
                    writer.write("\t\tvoid ");
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
                        String returnTypeName = returntype.getLangName();
                        String returnType = WrapperUtils.getClassNameFromParamInfoConsideringArrays(returntype,wscontext);
                        
                        if ((returnType.lastIndexOf ("_Array") > 0)
                                || (CUtils.isSimpleType(returnTypeName)
    							&& (returntype.isNillable() || returntype.isOptional())
    							&& !(CUtils.isPointerType(returnTypeName))))
                        {
                        	writer.write(
    	                            "\t\t"
    	                                + returnType
    	                                + " * ");
                        }
                        else
                        {
	                        writer.write(
	                            "\t\t"
	                                + returnType
	                                + " ");
	                    }
                    }
                    else
                    {
                        isAllTreatedAsOutParams = true;
                        writer.write("\t\tvoid ");
                    }
                }
                //write return type
                writer.write(minfo.getMethodname() + "(");
                //write parameter names 
                
                boolean hasInputParms = false;
                Iterator params = minfo.getInputParameterTypes().iterator();
                if (params.hasNext())
                {
                	hasInputParms = true;
                	ParameterInfo fparam = (ParameterInfo) params.next();
                    String paramTypeName = fparam.getLangName();
                    String paramType = WrapperUtils.getClassNameFromParamInfoConsideringArrays(fparam,wscontext);
                    
                    if (fparam.getType().isAttachment())
                    {
                    	writer.write("ISoapAttachment *Value" + 0);
                    }
                    
                    else if ((paramType.lastIndexOf ("_Array") > 0)||(CUtils.isSimpleType(paramTypeName)
                    		&& (fparam.isNillable() || fparam.isOptional())
							&& !(CUtils.isPointerType(paramTypeName))))
                    {
                    	writer.write(
                    			paramType
    	                            + " * Value"
    	                            + 0);
                    }
                    else
                    {
	                    writer.write(
	                        WrapperUtils
	                            .getClassNameFromParamInfoConsideringArrays(
	                            fparam,
	                            wscontext)
	                            + " Value"
	                            + 0);
	                }
                }
                for (int j = 1; params.hasNext(); j++)
                {
                	
                    ParameterInfo nparam = (ParameterInfo) params.next();
                    String paramTypeName = nparam.getLangName();
                    String typeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(nparam,wscontext);
                    
                    if (nparam.getType().isAttachment())
                    {
                    	writer.write(", ISoapAttachment *Value" + j);
                    }
                                        
                    else if ((typeName.lastIndexOf ("_Array") > 0)||(CUtils.isSimpleType(paramTypeName)
                    		&& (nparam.isNillable()|| nparam.isOptional())
							&& !(CUtils.isPointerType(paramTypeName))))
                    {
                    	writer.write(
    	                        ","
    	                            + typeName
    	                            + " * Value"
    	                            + j);
                    }
                    else
                    {
	                    writer.write(
	                        ","
	                            + typeName
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
                        
                        if (0 != j || hasInputParms)
                        {
                            writer.write(",");
                        }
                        
                        String typeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(
                                        	nparam, wscontext);
                        
                        writer.write(" AXIS_OUT_PARAM "
                                + typeName + " ");
                        
                        
                        
                        if (( nparam.isOptional() || nparam.isNillable())
                                && CUtils.isSimpleType(typeName)
                                && !CUtils.isPointerType(typeName)
                                && !nparam.isArray())
                        {
                            writer.write("*");
                        }
                        
                        writer.write("* OutValue" + j);
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
            Type atype;
            Iterator types = this.wscontext.getTypemap().getTypes().iterator();
            HashSet typeSet = new HashSet();
            writer.write("#include <axis/AxisUserAPI.hpp>\n");
            writer.write("#include <axis/AxisUserAPIArrays.hpp>\n");
            writer.write("#include <axis/ISoapAttachment.hpp>\n");
            writer.write("#include \"AxisServiceException.hpp\" \n\n");
            String typeName = null;
            while (types.hasNext())
            {
                atype = (Type) types.next();
                if (atype.getLanguageSpecificName().startsWith(">"))
                {
                    continue;
                }
                typeName = WrapperUtils.getLanguageTypeName4Type(atype);
                if (null != typeName)
                {
                    typeSet.add(typeName);
                }

            }
            Iterator itr = typeSet.iterator();
            while (itr.hasNext())
            {
                writer.write(
                    "#include \""
                        + itr.next().toString()
                        + CUtils.CPP_HEADER_SUFFIX
                        + "\"\n");
            }
            //writeFaultHeaders();
            writer.write("\n");
        }
        catch (IOException e)
        {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
    	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
    	 */
    protected void writeFaultHeaders() throws WrapperFault
    {
        try
        {

            MethodInfo minfo;
            for (int i = 0; i < methods.size(); i++)
            {
                minfo = (MethodInfo) methods.get(i);
                Iterator fault = minfo.getFaultType().iterator();
                String faultInfoName = null;
                while (fault.hasNext())
                {
                    FaultInfo info = (FaultInfo) fault.next();
                    faultInfoName = info.getFaultInfo();
                    writer.write(
                        "#include \"Axis"
                            + faultInfoName.toString()
                            + "Exception"
                            + CUtils.CPP_HEADER_SUFFIX
                            + "\"\n");
                }
            }
            writer.write("\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    protected String getFileType()
    {
        return "ServerSkeleton";
    }

    protected String getExtendsPart()
    {
        return " ";
    }
}
