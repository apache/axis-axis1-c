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

package org.apache.axismora.wsdl2ws.java;

import java.io.IOException;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.TypeMap;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

import org.apache.axis.encoding.SerializationContext;

/**
 * @author {jkuamranc@opensource.lk}
 *	created onAug 22, 2003
 */
public class ArrayParamWriter extends ParmWriter {

    private boolean isDirectReturn;
    private String arrtype;
    private QName qname;
    /**
     * @param wscontext
     * @param type
     * @throws WrapperFault
     */
    public ArrayParamWriter(WebServiceContext wscontext, Type type) throws WrapperFault {
        super(wscontext, type);

        this.isDirectReturn =
            this.wscontext.getSerInfo().isDirectReturn(type.getLanguageSpecificName());

        Iterator enu = type.getAttribNames();
        if (!enu.hasNext())
            throw new WrapperFault("Parameter with no types ???? Array Writer");

        qname = type.getTypNameForAttribName((String) enu.next());

        Type t = wscontext.getTypemap().getType(qname);
        if (t != null)
            this.arrtype = t.getLanguageSpecificName();
        else {
            //the type should be inbuild simple type
            this.arrtype = TypeMap.getBasicTypeClass4qname(qname);
            if (this.arrtype == null)
                throw new WrapperFault(
                    "if not inbuild or not in type map what is this type " + qname);
        }
    }

    public void writeDesireializeCode() throws WrapperFault {
        try {
            writer.write("\t\tjava.util.Vector obj = new java.util.Vector();\n");
            writer.write("\t\tjavax.xml.namespace.QName arrayname = null;\n");
            writer.write(
                "\t\tif(org.apache.axismora.wsdl2ws.java.ParmWriter.tag == null)\n");
            writer.write(
                "\t\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();\n\n");
            writer.write(
                "\t\twhile(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() != org.xmlpull.v1.XmlPullParser.START_TAG) {\n");
            writer.write(
                "\t\t\tif (org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.END_DOCUMENT) {\n");
			writer.write("\t\t\t\tthrow new org.apache.axis.AxisFault(\"end of the document\");\n");
			writer.write("\t\t\t}\n");
            writer.write(
                "\t\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();\n");
			writer.write("\t\t}\n");
            writer.write(
                "\t\tarrayname = new javax.xml.namespace.QName(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getUri(),org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getLocalpart());\n");
            writer.write(
                "\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();\n\n");

            writer.write(
                "\t\t//if the type of the next tag is end tag that means the content of element is null\n");
            writer.write(
                "\t\tif(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.END_TAG)\n");
			writer.write("\t\t\treturn null;\n\n");

            writer.write(
                "\t\twhile(!((org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.END_TAG) && \n");
            writer.write(
                "\t\t\t\t\t arrayname.equals(new javax.xml.namespace.QName(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getUri(),org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getLocalpart())))){\n");
            writer.write(
                "\t\t\tif(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() != org.xmlpull.v1.XmlPullParser.START_TAG){\n");
            writer.write(
                "\t\t\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();\n\t\t\t\tcontinue;\n\t\t\t}\n");
            if (!TypeMap.isSimpleType(arrtype)) {
                writer.write(
                    "\t\t\t"
                        + WrapperUtils.getWrapperName4FullyQualifiedName(arrtype)
                        + " "
                        + " item =(new "
                        + WrapperUtils.getWrapperName4FullyQualifiedName(arrtype)
                        + "());\n");
                writer.write("\t\t\titem.desierialize(msgdata);\n");
                writer.write("\t\t\tobj.add(item);\n");
            } else {
                writer.write(
                    "\t\t\t"
                        + WrapperUtils.getWrapperName4FullyQualifiedName(arrtype)
                        + " item =(new "
                        + WrapperUtils.getWrapperName4FullyQualifiedName(arrtype)
                        + "(msgdata));\n");
                writer.write("\t\t\t\t\tobj.add(item);\n");
            }
            writer.write(
                "\t\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();\n");
			writer.write("\t\t}\n\n");
            writer.write("\t\tint length = obj.size();\n");

            if (!TypeMap.isSimpleType(arrtype)) {
                writer.write(
                    "\t\t"
                        + WrapperUtils.getWrapperName4FullyQualifiedName(arrtype)
                        + "[] arr = new "
                        + WrapperUtils.getWrapperName4FullyQualifiedName(arrtype)
                        + "[length];\n");
                writer.write("\t\tfor(int i = 0;i<length;i++)\n");
                writer.write(
                    "\t\t\tarr[i] = ("
                        + WrapperUtils.getWrapperName4FullyQualifiedName(arrtype)
                        + ")obj.get(i);\n");
            } else {
                writer.write(
                    "\t\t" + arrtype + "[] arr = new " + arrtype + "[length];\n");
                writer.write("\t\tfor(int i = 0;i<length;i++)\n");
                writer.write(
                    "\t\t\tarr[i] = (("
                        + WrapperUtils.getWrapperName4FullyQualifiedName(arrtype)
                        + ")obj.get(i)).getParam();\n");
            }
            writer.write("\t\t this.param = arr;\n");
        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    public void writeSerialieCode() throws WrapperFault {
        try {
			if (this.isDirectReturn) {
            	writer.write(
                	"\t\tString m_URI =\"" + type.getName().getNamespaceURI() + "\";\n");
            	writer.write(
                	"\t\tString type_name = \""
                    + type.getName().getLocalPart()
                    + "\";\n");

            
                SerializationContext context;
                writer.write(
                    "\t\tboolean writeOutTag = !org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten;\n");
                writer.write("\t\tif(writeOutTag){\n");
                writer.write(
                    "\t\t\tcontext.writeString(\"<prf:\");\n" 
                    +"\t\t\tcontext.writeString(type_name);\n"
                    +"\t\t\tcontext.writeString(\" xmlns:prf =\\\"\");\n"
                    +"\t\t\tcontext.writeString(m_URI);\n"
                    +"\t\t\tcontext.writeString(\"\\\" >\");\n");
				writer.write("\t\t}\n");   
            }
            writer.write(
                "\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;\n");

            writer.write("\t\tfor (int i = 0; i < param.length; i++) {\n");
            writer.write(
                "\t\t\tcontext.writeString(\"<item\"+i+ \" "
                    + org.apache.axismora.wsdl2ws.WrapperUtils.getParamTypeString(qname)
                    + ">\");\n");
            writer.write(
                JavaUtils.isJavaSimpleType(arrtype) ? "" : "\t\t\tif(param[i]!=null){\n");
            if (!org.apache.axismora.wsdl2ws.info.TypeMap.isSimpleType(arrtype)) {
                writer.write(
                    "\t\t\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;\n");
                writer.write("\t\t\t\tparam[i].serialize(context);\n");
            } else
                writer.write("\t\t\t\tcontext.writeString(String.valueOf(param[i]));\n");
            writer.write(JavaUtils.isJavaSimpleType(arrtype) ? "" : "\t\t\t}\n");
            writer.write("\t\t\tcontext.writeString(\"</item\"+i+ \">\");\n\t\t}\n");
            writer.write("\t\t//name of parameter will be written by upper level\n");
            if (this.isDirectReturn) {
                writer.write("\t\t//write the end tag\n");
                writer.write("\t\tif(writeOutTag){\n");
                writer.write(
                    "\t\t\tcontext.writeString(\"</prf:\");\n"
                    +"\t\t\tcontext.writeString(type_name);\n"
                    +"\t\t\tcontext.writeString(\">\");\n");
				writer.write("\t\t}\n");    
            }

        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

}
