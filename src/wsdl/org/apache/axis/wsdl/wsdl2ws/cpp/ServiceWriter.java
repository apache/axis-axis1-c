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
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ServiceWriter extends CPPClassWriter
{
    private ArrayList methods;
    public ServiceWriter(WebServiceContext wscontext) throws WrapperFault
    {
        super(wscontext.getServiceInfo().getServicename());
        this.wscontext = wscontext;
        this.methods = wscontext.getServiceInfo().getMethods();
    }

    public void writeSource() throws WrapperFault
    {
        // We should not overwrite the service file if it already exists
        if (! getFilePath(false).exists())
            super.writeSource();
    }

    protected void writeClassComment() throws WrapperFault
    {
        try
        {
            c_writer.write("/*\n");
			c_writer.write(" * Copyright 2003-2006 The Apache Software Foundation.\n\n");
			c_writer.write(" *\n");
			c_writer.write(" * Licensed under the Apache License, Version 2.0 (the \"License\");\n");
			c_writer.write(" * you may not use this file except in compliance with the License.\n");
			c_writer.write(" * You may obtain a copy of the License at\n");
			c_writer.write(" *\n");
			c_writer.write(" *\t\thttp://www.apache.org/licenses/LICENSE-2.0\n");
			c_writer.write(" *\n");
			c_writer.write(" * Unless required by applicable law or agreed to in writing, software\n");
			c_writer.write(" * distributed under the License is distributed on an \"AS IS\" BASIS,\n");
			c_writer.write(" * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n");
			c_writer.write(" * See the License for the specific language governing permissions and\n");
			c_writer.write(" * limitations under the License.\n");
			c_writer.write(" *\n");
            c_writer.write(" * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)\n");
            c_writer.write(" * This file contains definitions of the web service\n");
            c_writer.write(" */\n\n");
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
            c_writer.write("\n" + c_classname + "::\n" + c_classname + "()\n{\n");
            c_writer.write("}\n");
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
            c_writer.write("\n" + c_classname + "::\n~" + c_classname + "()\n{\n");
            c_writer.write("}\n");
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
            c_writer.write(
                "\n/* This function is called by the AxisEngine when something went wrong"
                    + "\n with the current web service request processing. Appropriate actions should"
                    + "\n be taken here.*/");
            c_writer.write("\nvoid " + c_classname + "::\nonFault()\n{\n}");
            /*writer.write(
                "\n/* This function is called by the AxisEngine when this web service"
                    + "\n library is first loaded. So here we can initialize any global/static"
                    + "\n data structures of this web service or open database connections *//*");
            writer.write("\nvoid " + classname + "::\ninit()\n{\n}");
            writer.write(
                "\n/* This function is called by the AxisEngine when this web service"
                    + "\n library is unloaded. So we can deallocate any global/static data structures"
                    + "\n and close database connections etc here. *//*");
            writer.write("\nvoid " + classname + "::\nfini()\n{\n}");*/
            c_writer.write("\n\n");
            for (int i = 0; i < methods.size(); i++)
            {
                minfo = (MethodInfo) this.methods.get(i);
                boolean isAllTreatedAsOutParams = false;
                ParameterInfo returntype = null;
                int noOfOutParams = minfo.getOutputParameterTypes().size();
                if (0 == noOfOutParams)
                {
                    returntype = null;
                    c_writer.write("void ");
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
                        if ((returnType.lastIndexOf ("_Array") > 0)||(CUtils.isSimpleType(returntype.getLangName())
                        		&& (returntype.isNillable()|| returntype.isOptional())
								&& !(CUtils.isPointerType(returnTypeName))))
                        {
                        	c_writer.write(
                        			returnType
    	                                + " * ");
                        }
                        else
                        {
	                        c_writer.write(
	                        		returnType
	                                + " ");
                        }
                    }
                    else
                    {
                        isAllTreatedAsOutParams = true;
                        c_writer.write("void ");
                    }
                }
                c_writer.write(c_classname + "::\n" + minfo.getMethodname() + "(");
                //write parameter names 
                
                boolean hasInputParms = false;
                Iterator params = minfo.getInputParameterTypes().iterator();
                if (params.hasNext())
                {
                	hasInputParms = true;
                	ParameterInfo fparam = (ParameterInfo) params.next();
                    String fparamTypeName = fparam.getLangName();
                    String fparamType = CUtils.getClassNameFromParamInfoConsideringArrays(fparam,wscontext);
                    
                    if (fparam.getType().isAttachment())
                    {
                    	c_writer.write("ISoapAttachment *Value" + 0);
                    }
                    
                    else if ((fparamType.lastIndexOf ("_Array") > 0)||(CUtils.isSimpleType(fparamTypeName)
							&& (fparam.isNillable()|| fparam.isOptional())
							&& !(CUtils.isPointerType(fparamTypeName))))
                    {
                    	c_writer.write(
                    			fparamType
    	                            + " * Value"
    	                            + 0);
                    }
                    else
                    {
	                    c_writer.write(
	                    		fparamType
	                            + " Value"
	                            + 0);
                    }
                }
                for (int j = 1; params.hasNext(); j++)
                {
                	ParameterInfo nparam = (ParameterInfo) params.next();
                    String paramTypeName = nparam.getLangName();
                    String paramType = CUtils.getClassNameFromParamInfoConsideringArrays(nparam,wscontext);
                    
                    if (nparam.getType().isAttachment())
                    {
                    	c_writer.write(", ISoapAttachment *Value" + j);
                    }
                                        
                    else if ((paramType.lastIndexOf ("_Array") > 0)||(CUtils.isSimpleType(paramTypeName)
                    		&& (nparam.isNillable()|| nparam.isOptional())
							&& !(CUtils.isPointerType(paramTypeName))))
                    {
                    	c_writer.write(
    	                        ","
    	                            + paramType
    	                            + " * Value"
    	                            + j);
                    }
                    else
                    {
	                    c_writer.write(
	                        ","
	                            + paramType
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
                        
                        
                        
                        if (( nparam.isOptional() || nparam.isNillable() )
                                && CUtils.isSimpleType(typeName)
                                && !CUtils.isPointerType(typeName)
                                && !nparam.isArray())
                        {
                            c_writer.write("*");
                        }
                        
                        c_writer.write("* OutValue" + j);
                    }
                }
                c_writer.write(")  \n{\n}\n\n");

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
            c_writer.write(
                "#include \""
                    + c_classname
                    + CUtils.getHeaderFileExtension()
                    + "\"\n\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
