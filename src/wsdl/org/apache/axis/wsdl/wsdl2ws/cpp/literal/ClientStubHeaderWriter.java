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

package org.apache.axis.wsdl.wsdl2ws.cpp.literal;

import java.io.File;
import java.io.IOException;
import java.util.HashSet;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.TypeMap;
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
            c_writer.write("public: \n");

            for (int i = 0; i < methods.size(); i++)
            {
                minfo = (MethodInfo) this.methods.get(i);
                boolean isAllTreatedAsOutParams = false;
                int noOfOutParams = minfo.getOutputParameterTypes().size();
                
                //write return type
                if (0 == noOfOutParams)
                    c_writer.write("\tSTORAGE_CLASS_INFO void ");
                else if (1 == noOfOutParams)
                {
                    ParameterInfo returnParam =
                        (ParameterInfo) minfo.getOutputParameterTypes().iterator().next();
                    String outParamTypeName = CUtils.getClassNameFromParamInfoConsideringArrays(returnParam, wscontext);
                    if ((CUtils.isArrayType(outParamTypeName)) 
                            || (CUtils.isSimpleType(outParamTypeName)
                                    && (returnParam.isNillable() || returnParam.isOptional())
                                    && !(CUtils.isPointerType(outParamTypeName))))
                        c_writer.write("\tSTORAGE_CLASS_INFO " + outParamTypeName + " * ");
                    else
                        c_writer.write("\tSTORAGE_CLASS_INFO " + outParamTypeName + " ");
                }
                else
                {
                    isAllTreatedAsOutParams = true;
                    c_writer.write("\tSTORAGE_CLASS_INFO void ");
                }
                //write return type
                c_writer.write(minfo.getSanitizedMethodName() + "(");

                //write parameter names 
                boolean hasInputParms = false;
                Iterator params = minfo.getInputParameterTypes().iterator();
                for (int j = 0; params.hasNext(); j++)
                {
                    if (j>0) 
                        c_writer.write(", ");
                    hasInputParms = true;
                    ParameterInfo nparam = (ParameterInfo) params.next();
                    String paramTypeName = CUtils.getClassNameFromParamInfoConsideringArrays(nparam, wscontext);
                    Type type = nparam.getType();
                    String baseTypeName = null;
                    
                    if (type.isSimpleType())
                        baseTypeName = CUtils.getSimpleType (type.getBaseType ());
                    else
                        baseTypeName = paramTypeName;
                    
                    if (nparam.getType().isAttachment())
                        c_writer.write("ISoapAttachment *Value" + j);
                    else if ((CUtils.isArrayType(paramTypeName))
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
                        
                        if (hasInputParms || 0!=j)
                            c_writer.write(", ");
                        
                        c_writer.write("AXIS_OUT_PARAM " + paramType);
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
            c_writer.write("#include <axis/client/Stub.hpp>\n");
            c_writer.write("#include <axis/OtherFaultException.hpp>\n");
            c_writer.write("#include <axis/ISoapAttachment.hpp>\n");
            c_writer.write("#include <axis/ISoapFault.hpp>\n");
            c_writer.write("\n");
            c_writer.write("AXIS_CPP_NAMESPACE_USE\n");
            c_writer.write("\n");
            
            // TODO - There should be a better way to determine what types are being generated!
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
                {
                    // TODO not sure about "string" check, whether it is needed....
                    if (atype.getElementType().equals("string"))
                        removeSet.add(atype.getLanguageSpecificName());

                    // NOTE: There is similar check in AllParamWriter.java.  
                    String elementType = atype.getElementType();
                    if (elementType != null)
                    {
                        if (TypeMap.isAnonymousType(elementType))
                            elementType = CUtils.sanitizeString(elementType);
                        
                        QName elementQname = new QName(atype.getName().getNamespaceURI(), elementType);                       
                        Type currentType = wscontext.getTypemap().getType(elementQname);
                        
                        if (currentType != null)
                            if ( currentType.isSimpleType())
                                continue;
                    }
                }
                
                // TODO not sure about "string" check, whther it is needed...
                if (atype.getBaseType() != null)
                    if (atype.getBaseType().getLocalPart().equals("string"))
                        removeSet.add(CUtils.getArrayNameForType(atype.getLanguageSpecificName()));
                
                   
                if (atype.isRestriction())
                    removeSet.add(CUtils.getArrayNameForType(atype.getLanguageSpecificName()));

                typeSet.add(atype.getLanguageSpecificName());
            }
            
            Iterator ritr = removeSet.iterator();
            while (ritr.hasNext())
                typeSet.remove(ritr.next());

            Iterator itr = typeSet.iterator();
            String targetLocation = wscontext.getWrapperInfo().getTargetOutputLocation();
            if (!targetLocation.endsWith(File.separator))
                targetLocation += File.separator;
          
            while (itr.hasNext())
            {
                String fn = itr.next().toString() + CUtils.getHeaderFileExtension();
                        
                // Not pretty but it works...this ensures we include generated types.
                if (new File(targetLocation  + fn).exists())
                    c_writer.write("#include \"" + fn + "\"\n");
            }
            
            //    Method to print the Fault Exception headers
            //writeFaultHeaders();
            c_writer.write("\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
