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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

/*
 * Revision 1.1  2004/05/26 samisa
 * Added Stub base class into code generation
 */

package org.apache.axis.wsdl.wsdl2ws.cpp.literal;

import java.io.IOException;
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ClientStubHeaderWriter
    extends org.apache.axis.wsdl.wsdl2ws.cpp.ClientStubHeaderWriter
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
            writer.write("public: \n");

            for (int i = 0; i < methods.size(); i++)
            {
                minfo = (MethodInfo) this.methods.get(i);
                boolean isAllTreatedAsOutParams = false;
                int noOfOutParams = minfo.getOutputParameterTypes().size();
                //write return type
                if (0 == noOfOutParams)
                {
                    writer.write("\tSTORAGE_CLASS_INFO void ");
                }
                else
                {
                    if (1 == noOfOutParams)
                    {
                        ParameterInfo returnParam =
                            (ParameterInfo) minfo
                                .getOutputParameterTypes()
                                .iterator()
                                .next();
                        String outParamTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(returnParam, wscontext);
                        if (CUtils.isSimpleType(outParamTypeName)
								&& returnParam.isNillable()
								&& !(CUtils.isPointerType(outParamTypeName)))
                        {
                        	writer.write(
                                    "\tSTORAGE_CLASS_INFO "
                                        + outParamTypeName
                                        + " * ");
                        }
                        else{
                        writer.write(
                            "\tSTORAGE_CLASS_INFO "
                                + outParamTypeName
                                + " ");
                        }
                    }
                    else
                    {
                        isAllTreatedAsOutParams = true;
                        writer.write("\tSTORAGE_CLASS_INFO void ");
                    }
                }
                //write return type
                writer.write(minfo.getMethodname() + "(");

                //write parameter names 
                boolean hasInputParms = false;
                Iterator params = minfo.getInputParameterTypes().iterator();
                for (int j = 0; params.hasNext(); j++)
                {
                    if (j>0) writer.write(", ");
                    hasInputParms = true;
                    ParameterInfo nparam = (ParameterInfo) params.next();
                    String paramTypeName = WrapperUtils.getClassNameFromParamInfoConsideringArrays(nparam, wscontext);
                    if (nparam.getType().isAttachment())
                    {
                    	writer.write("ISoapAttachment *Value" + j);
                    }
                    else if (CUtils.isSimpleType(paramTypeName)
							&& nparam.isNillable()
							&& !(CUtils.isPointerType(paramTypeName)))
                    {
                    	writer.write(paramTypeName + " * Value" + j);
                    }
                    else
                    {
	                    writer.write(paramTypeName + " Value" + j);
                    }
                }

                if (isAllTreatedAsOutParams)
                {
                    params = minfo.getOutputParameterTypes().iterator();
                    for (int j = 0; params.hasNext(); j++)
                    {
                        ParameterInfo nparam = (ParameterInfo) params.next();
                        String comma = ", ";
                        if (!hasInputParms && 0==j) comma = "";
                        writer.write(comma
                                + "AXIS_OUT_PARAM "
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
            writer.write("#include <axis/client/Stub.hpp>\n");
            writer.write("#include <axis/OtherFaultException.hpp>\n");
            writer.write("#include <axis/ISoapAttachment.hpp>\n");
            writer.write("#include <axis/ISoapFault.hpp>\n");
            writer.write("AXIS_CPP_NAMESPACE_USE\n");
            Type atype;
            Iterator types = this.wscontext.getTypemap().getTypes().iterator();
            HashSet typeSet = new HashSet();
            HashSet removeSet = new HashSet();
            while (types.hasNext())
            {
                atype = (Type) types.next();
                if (atype.isArray())
                {
                    if (atype.getElementType().equals("string"))
                    {
                        removeSet.add(atype.getLanguageSpecificName());
                    }
                }
                if (atype.getBaseType() != null)
                {
                    if (atype.getBaseType().getLocalPart().equals("string"))
                    {
                        removeSet.add(
                            atype.getLanguageSpecificName() + "_Array");
                    }
                }
                if (atype.getLanguageSpecificName().startsWith(">"))
                {
                    continue;
                }
                typeSet.add(atype.getLanguageSpecificName());
            }
            Iterator ritr = removeSet.iterator();
            while (ritr.hasNext())
                typeSet.remove(ritr.next());

            Iterator itr = typeSet.iterator();
            while (itr.hasNext())
            {
                writer.write(
                    "#include \""
                        + itr.next().toString()
                        + CUtils.CPP_HEADER_SUFFIX
                        + "\"\n");
            }
            //	Method to print the Fault Exception headers
            //writeFaultHeaders();
            writer.write("\n");
        }
        catch (IOException e)
        {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }
}
