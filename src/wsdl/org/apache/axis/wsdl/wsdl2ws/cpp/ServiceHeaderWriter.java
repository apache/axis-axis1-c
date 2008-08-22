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
        super(wscontext.getServiceInfo().getServicename());
        this.wscontext = wscontext;
        this.methods = wscontext.getServiceInfo().getMethods();
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeClassComment()
     */
    protected void writeClassComment() throws WrapperFault
    {
        try
        {
            c_writer.write("/*\n");
            c_writer.write(
                " * This is the Service Class genarated by the tool WSDL2Ws\n");
            c_writer.write(
                " * "
                    + c_classname
                    + CUtils.getHeaderFileExtension()
                    + ": interface for the "
                    + c_classname
                    + "class.\n");
            c_writer.write(" *\n");
            c_writer.write(" */\n");
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
            c_writer.write("\tpublic:\n\t\t" + c_classname + "();\n");
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
            c_writer.write("\tpublic:\n\t\tvirtual ~" + c_classname + "();\n");
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
            c_writer.write("\tpublic: \n");
            c_writer.write("\t\tvoid onFault();\n");
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
                    c_writer.write("\t\tvoid ");
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
                        String returnType = CUtils.getClassNameFromParamInfoConsideringArrays(returntype,wscontext);
                        
                        if ((returnType.lastIndexOf ("_Array") > 0)
                                || (CUtils.isSimpleType(returnTypeName)
    							&& (returntype.isNillable() || returntype.isOptional())
    							&& !(CUtils.isPointerType(returnTypeName))))
                        {
                        	c_writer.write(
    	                            "\t\t"
    	                                + returnType
    	                                + " * ");
                        }
                        else
                        {
	                        c_writer.write(
	                            "\t\t"
	                                + returnType
	                                + " ");
	                    }
                    }
                    else
                    {
                        isAllTreatedAsOutParams = true;
                        c_writer.write("\t\tvoid ");
                    }
                }
                //write return type
                c_writer.write(minfo.getMethodname() + "(");
                //write parameter names 
                
                boolean hasInputParms = false;
                Iterator params = minfo.getInputParameterTypes().iterator();
                if (params.hasNext())
                {
                	hasInputParms = true;
                	ParameterInfo fparam = (ParameterInfo) params.next();
                    String paramTypeName = fparam.getLangName();
                    String paramType = CUtils.getClassNameFromParamInfoConsideringArrays(fparam,wscontext);
                    
                    if (fparam.getType().isAttachment())
                    {
                    	c_writer.write("ISoapAttachment *Value" + 0);
                    }
                    
                    else if ((paramType.lastIndexOf ("_Array") > 0)||(CUtils.isSimpleType(paramTypeName)
                    		&& (fparam.isNillable() || fparam.isOptional())
							&& !(CUtils.isPointerType(paramTypeName))))
                    {
                    	c_writer.write(
                    			paramType
    	                            + " * Value"
    	                            + 0);
                    }
                    else
                    {
	                    c_writer.write(
	                            CUtils
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
                    String typeName = CUtils.getClassNameFromParamInfoConsideringArrays(nparam,wscontext);
                    
                    if (nparam.getType().isAttachment())
                    {
                    	c_writer.write(", ISoapAttachment *Value" + j);
                    }
                                        
                    else if ((typeName.lastIndexOf ("_Array") > 0)||(CUtils.isSimpleType(paramTypeName)
                    		&& (nparam.isNillable()|| nparam.isOptional())
							&& !(CUtils.isPointerType(paramTypeName))))
                    {
                    	c_writer.write(
    	                        ","
    	                            + typeName
    	                            + " * Value"
    	                            + j);
                    }
                    else
                    {
	                    c_writer.write(
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
                            c_writer.write(",");
                        }
                        
                        String typeName = CUtils.getClassNameFromParamInfoConsideringArrays(
                                        	nparam, wscontext);
                        
                        c_writer.write(" AXIS_OUT_PARAM "
                                + typeName + " ");
                        
                        
                        
                        if (( nparam.isOptional() || nparam.isNillable())
                                && CUtils.isSimpleType(typeName)
                                && !CUtils.isPointerType(typeName)
                                && !nparam.isArray())
                        {
                            c_writer.write("*");
                        }
                        
                        c_writer.write("* OutValue" + j);
                    }
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
            Type atype;
            Iterator types = this.wscontext.getTypemap().getTypes().iterator();
            HashSet typeSet = new HashSet();
            HashSet removeSet = new HashSet();
            
            c_writer.write("#include <axis/AxisUserAPI.hpp>\n");
            c_writer.write("#include <axis/AxisUserAPIArrays.hpp>\n");
            c_writer.write("#include <axis/ISoapAttachment.hpp>\n");
            c_writer.write("#include \"AxisServiceException.hpp\" \n\n");
            String typeName = null;
            while (types.hasNext())
            {
                atype = (Type) types.next();
                
                if (!atype.isExternalized())
                    continue;

                typeName = CUtils.getLanguageTypeName4Type(atype);
                if (null != typeName)
                    typeSet.add(typeName);
                   
                if (atype.isRestriction())
                    removeSet.add(atype.getLanguageSpecificName()  + "_Array");
            }
            
            Iterator ritr = removeSet.iterator();
            while (ritr.hasNext())
                typeSet.remove(ritr.next());
            
            Iterator itr = typeSet.iterator();
            while (itr.hasNext())
            {
                c_writer.write("#include \"" + itr.next().toString() + CUtils.getHeaderFileExtension() + "\"\n");
            }
            //writeFaultHeaders();
            c_writer.write("\n");
        }
        catch (IOException e)
        {
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
                    c_writer.write(
                        "#include \"Axis"
                            + faultInfoName.toString()
                            + "Exception"
                            + CUtils.getHeaderFileExtension()
                            + "\"\n");
                }
            }
            c_writer.write("\n");
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
