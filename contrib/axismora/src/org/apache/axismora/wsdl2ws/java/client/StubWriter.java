/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *    Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

package org.apache.axismora.wsdl2ws.java.client;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.MethodInfo;
import org.apache.axismora.wsdl2ws.info.ParameterInfo;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.TypeMap;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;
import org.apache.axismora.wsdl2ws.java.JavaClassWriter;
import org.apache.axismora.wsdl2ws.java.JavaUtils;

/**
 * jkumaran@opensource.lk
 * vtpavan@opensource.lk
 * Sep 23, 2002axis2server
 *
 */
public class StubWriter extends JavaClassWriter {
    private String classname;
    private WebServiceContext wscontext;
    private ArrayList methods;
    private QName soap;

    /**
     * @param packagename
     * @param classname
     * @throws WrapperFault
     */
    public StubWriter(WebServiceContext wscontext) throws WrapperFault {
        super(
            WrapperUtils.getPackegeName4QualifiedName(
                wscontext.getSerInfo().getQualifiedServiceName()),
            WrapperUtils.getClassNameFromFullyQualifiedName(
                wscontext.getSerInfo().getQualifiedServiceName())
                + "Stub");
        this.classname =
            WrapperUtils.getClassNameFromFullyQualifiedName(
                wscontext.getSerInfo().getQualifiedServiceName())
                + "Stub";
        this.wscontext = wscontext;
        this.methods = wscontext.getSerInfo().getMethods();
        this.soap = new QName(wscontext.getSerInfo().getServicename());
    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeAttributes()
     */
    protected void writeAttributes() throws WrapperFault {
        try {
            writer.write("\n\tprivate java.lang.String enduri;");
            writer.write("\n\tprivate javax.xml.namespace.QName SOAPAction;");
            writer.write("\n\tprivate org.apache.axismora.client.Service service;\n");
        } catch (Exception e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeConstructors()
     */
    protected void writeConstructors() throws WrapperFault {
        try {
            writer.write("\n\tpublic " + classname + "()" + "{\n\t}");
            writer.write("\n\tpublic " + classname + "(java.lang.String enduri){");
            writer.write("\n\t\ttry{\n");
            writer.write("\t\t\tthis.enduri = enduri;\n");
            writer.write(
                "\t\t\tthis.SOAPAction = new javax.xml.namespace.QName(\""
                    + wscontext.getSerInfo().getServicename()
                    + "\");\n");
            writer.write(
                "\t\t\tthis.service = new org.apache.axismora.client.Service();");
            writer.write("\n\t\t}catch(Exception e){");
            writer.write("\n\t\t\te.printStackTrace();\n\t\t}\n\t}\n");
        } catch (Exception e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }

    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeMethods()
     */
    protected void writeMethods() throws WrapperFault {
        MethodInfo minfo;
        QName paramQName;
        Type paramType;
        Object obj;
        try {
            for (int i = 0; i < methods.size(); i++) {
                minfo = (MethodInfo) this.methods.get(i);
                writer.write("\n\tpublic ");

                ParameterInfo returnType = minfo.getReturnType();
                if (returnType == null
                    || returnType.getLangName() == null
                    || returnType.getLangName() == "void")
                    writer.write("void ");
                else
                    writer.write(
                        WrapperUtils.getClassNameFromParamInfoConsideringArrays(
                            minfo.getReturnType(),
                            wscontext)
                            + " ");
                writer.write(minfo.getMethodname() + "(");

                //write parameter names 
                Iterator params = minfo.getParameterTypess().iterator();
                if (params.hasNext())
                    writer.write(
                        WrapperUtils.getClassNameFromParamInfoConsideringArrays(
                            (ParameterInfo) params.next(),
                            wscontext)
                            + " param"
                            + 0);
                for (int j = 1; params.hasNext(); j++) {
                    writer.write(
                        ","
                            + WrapperUtils.getClassNameFromParamInfoConsideringArrays(
                                (ParameterInfo) params.next(),
                                wscontext)
                            + " param"
                            + j);
                }
                writer.write(")throws java.rmi.RemoteException{");
                writer.write(
                    "\n\t\tjavax.xml.namespace.QName methodName = new javax.xml.namespace.QName(\""
                        + minfo.getMethodname()
                        + "\");");
                String ops = "";
                writer.write(
                    "\n\t\torg.apache.axismora.client.Call call = (org.apache.axismora.client.Call)service.createCall();");
                writer.write("\n\t\tcall.setOperationName(methodName);");
                writer.write("\n\t\tcall.setPortTypeName(SOAPAction);");
                Iterator params1 = minfo.getParameterTypess().iterator();
                if (params1.hasNext()) {
                    obj = params1.next();
                    paramType =
                        wscontext.getTypemap().getType(
                            ((ParameterInfo) obj).getSchemaName());
                    paramQName = ((ParameterInfo) obj).getSchemaName();
                    if (TypeMap.isSimpleType(paramQName)) {
                        String paramName =
                            WrapperUtils.getWrapperName4FullyQualifiedName(
                                ((ParameterInfo) obj).getLangName());
                        writer.write(
                            "\n\t\t"
                                + paramName
                                + " op0 = new "
                                + paramName
                                + "(param0);");

                        //TODO prob here now fixed I think
                        //writer.write("\n\t\torg.apache.axismora.wrappers.simpleType."+WrapperUtils.capitalizeFirstCaractor(((ParameterInfo)obj).getSchemaName().getLocalPart())+"Param op0 = new org.apache.axismora.wrappers.simpleType."+WrapperUtils.capitalizeFirstCaractor(((ParameterInfo)obj).getSchemaName().getLocalPart())+"Param(param0);");
                        //writer.write("\n\t\top0.setParam(param0);");
                        writer.write(
                            "\n\t\tcall.addParameter(\"param0\",new javax.xml.namespace.QName(\""
                                + paramQName.getNamespaceURI()
                                + "\",\""
                                + paramQName.getLocalPart()
                                + "\"),javax.xml.rpc.ParameterMode.IN);");
                        ops = "op0";
                    } else if (paramType != null && paramType.isArray()) {
                        writer.write(
                            "\n\t\t"
                                + ((ParameterInfo) obj).getType().getLanguageSpecificName()
                                + " op0 = new "
                                + ((ParameterInfo) obj).getType().getLanguageSpecificName()
                                + "();");
                        writer.write("\n\t\top0.setParam(param0);");
                        paramQName = ((ParameterInfo) obj).getSchemaName();
                        writer.write(
                            "\n\t\tcall.addParameter(\"param0\",new javax.xml.namespace.QName(\""
                                + paramQName.getNamespaceURI()
                                + "\",\""
                                + paramQName.getLocalPart()
                                + "\"),javax.xml.rpc.ParameterMode.IN);");
                        ops = "op0";
                    } else {
                        //paramType = ((ParameterInfo)obj).getType();
                        paramQName = ((ParameterInfo) obj).getSchemaName();
                        writer.write(
                            "\n\t\tcall.addParameter(\"param0\",new javax.xml.namespace.QName(\""
                                + paramQName.getNamespaceURI()
                                + "\",\""
                                + paramQName.getLocalPart()
                                + "\"),javax.xml.rpc.ParameterMode.IN);");
                        ops = "param0";
                    }
                }
                for (int j = 1; params1.hasNext(); j++) {
                    obj = params1.next();
                    paramQName = ((ParameterInfo) obj).getSchemaName();
                    paramType =
                        wscontext.getTypemap().getType(
                            ((ParameterInfo) obj).getSchemaName());
                    if (TypeMap.isSimpleType(paramQName)) {
                        String paramName =
                            WrapperUtils.getWrapperName4FullyQualifiedName(
                                ((ParameterInfo) obj).getLangName());

                        writer.write(
                            "\n\t\t"
                                + paramName
                                + " op"
                                + j
                                + " = new "
                                + paramName
                                + "(param"
                                + j
                                + ");");
                        //TODO prob here now fixed I think
                        //writer.write("\n\t\torg.apache.axismora.wrappers.simpleType."+WrapperUtils.capitalizeFirstCaractor(((ParameterInfo)obj).getSchemaName().getLocalPart())+"Param op"+j+" = new org.apache.axismora.wrappers.simpleType."+WrapperUtils.capitalizeFirstCaractor(((ParameterInfo)obj).getSchemaName().getLocalPart())+"Param(param"+j+");");
                        //writer.write("\n\t\top0.setParam(param"+0+");");
                        writer.write(
                            "\n\t\tcall.addParameter(\"param"
                                + j
                                + "\",new javax.xml.namespace.QName(\""
                                + paramQName.getNamespaceURI()
                                + "\",\""
                                + paramQName.getLocalPart()
                                + "\"),javax.xml.rpc.ParameterMode.IN);");
                        ops = ops + ",op" + j;
                    } else if (paramType != null && paramType.isArray()) {
                        writer.write(
                            "\n\t\t "
                                + ((ParameterInfo) obj).getType().getLanguageSpecificName()
                                + " op"
                                + j
                                + " = new "
                                + ((ParameterInfo) obj).getType().getLanguageSpecificName()
                                + "();\n");
                        writer.write("\n\t\top" + j + ".setParam(param" + j + ");");
                        paramQName = ((ParameterInfo) obj).getSchemaName();
                        writer.write(
                            "\n\t\tcall.addParameter(\"param"
                                + j
                                + "\",new javax.xml.namespace.QName(\""
                                + paramQName.getNamespaceURI()
                                + "\",\""
                                + paramQName.getLocalPart()
                                + "\"),javax.xml.rpc.ParameterMode.IN);");
                        ops = ops + ",op" + j;
                    } else {
                        paramQName = ((ParameterInfo) obj).getSchemaName();
                        writer.write(
                            "\n\t\tcall.addParameter(\"param"
                                + j
                                + "\",new javax.xml.namespace.QName(\""
                                + paramQName.getNamespaceURI()
                                + "\",\""
                                + paramQName.getLocalPart()
                                + "\"),javax.xml.rpc.ParameterMode.IN);");
                        ops = ops + ",param" + j;
                    }
                }

                returnType = (ParameterInfo) minfo.getReturnType();
                writer.write("\n\t\tcall.setTargetEndpointAddress(this.enduri);");
                if (returnType != null) {
                    paramQName = returnType.getSchemaName();
                    paramType =
                        wscontext.getTypemap().getType(
                            ((ParameterInfo) minfo.getReturnType()).getSchemaName());
                    writer.write(
                        "\n\t\tcall.setReturnType(new javax.xml.namespace.QName(\""
                            + paramQName.getNamespaceURI()
                            + "\",\""
                            + paramQName.getLocalPart()
                            + "\"));");
                    writer.write(
                        "\n\t\torg.apache.axismora.MessageContext mx = (org.apache.axismora.MessageContext)call.invokeLowLevel(methodName,new org.apache.axismora.encoding.OutParameter[]{"
                            + ops
                            + "});");
                    if (TypeMap.isSimpleType(paramQName)) {
                        String paramName =
                            WrapperUtils.getWrapperName4FullyQualifiedName(
                                minfo.getReturnType().getLangName());
                        writer.write(
                            "\n\t\t" + paramName + " res = new " + paramName + "(mx);");
                        //TODO prob here now fixed I think
                        //writer.write("\n\t\torg.apache.axismora.wrappers.simpleType."+WrapperUtils.capitalizeFirstCaractor(paramQName.getLocalPart())+"Param res = (org.apache.axismora.wrappers.simpleType."+WrapperUtils.capitalizeFirstCaractor(paramQName.getLocalPart())+"Param)(new org.apache.axismora.wrappers.simpleType."+WrapperUtils.capitalizeFirstCaractor(paramQName.getLocalPart())+"Param(mx));");
                        writer.write(
                            "\n\t\treturn res"
                                + (!JavaUtils.isUnwrapperdSimpleType(paramName)
                                    ? ".getParam();"
                                    : ";"));
                    } else if (paramType != null && paramType.isArray()) {
                        writer.write(
                            "\n\t\t"
                                + paramType.getLanguageSpecificName()
                                + " res = ("
                                + paramType.getLanguageSpecificName()
                                + ")(new "
                                + paramType.getLanguageSpecificName()
                                + "()).desierialize(mx);");
                        writer.write(
                            "\n\t\t return ("
                                + WrapperUtils.getClassNameFromParamInfoConsideringArrays(
                                    minfo.getReturnType(),
                                    wscontext)
                                + ")res.getParam();\n");
                    } else {
                        writer.write(
                            "\n\t\t"
                                + paramType.getLanguageSpecificName()
                                + " res = ("
                                + paramType.getLanguageSpecificName()
                                + ")(new "
                                + paramType.getLanguageSpecificName()
                                + "()).desierialize(mx);");
                        writer.write("\n\t\t return res;\n");
                    }
                } else {
                    writer.write(
                        "\n\t\torg.apache.axismora.MessageContext mx = (org.apache.axismora.MessageContext)call.invokeLowLevel(methodName,new org.apache.axismora.encoding.OutParameter[]{"
                            + ops
                            + "});");
                }
                writer.write("\n\t\t}\n");
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }

    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#getJavaFilePath()
     */
    protected File getJavaFilePath() throws WrapperFault {
        String targetOutputLocation =
            this.wscontext.getWrapInfo().getTargetOutputLocation();
        if (targetOutputLocation.endsWith("/"))
            targetOutputLocation =
                targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
        new File(
            targetOutputLocation
                + "/"
                + WrapperUtils
                    .getPackegeName4QualifiedName(
                        this.wscontext.getSerInfo().getQualifiedServiceName())
                    .replace('.', '/'))
            .mkdirs();
        String fileName =
            targetOutputLocation
                + "/"
                + (this.wscontext.getSerInfo().getQualifiedServiceName() + "Stub").replace(
                    '.',
                    '/')
                + ".java";
        return new File(fileName);
    }
    /* (non-Javadoc)
    * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#getExtendsPart()
    */
    protected String getExtendsPart() {
        // TODO Auto-generated method stub
        return super.getExtendsPart();
    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#getimplementsPart()
     */
    protected String getimplementsPart() {
        return "implements " + wscontext.getSerInfo().getQualifiedServiceName();
    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeClassComment()
     */
    protected void writeClassComment() throws WrapperFault {
        try {
            writer.write("/*This class is automatically generated by \n");
            writer.write("*axis_lsf client stub generator\n");
            writer.write("*The client side stub of the web service. \n");
            writer.write("*/\n\n");
        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }
}
