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

import javax.xml.namespace.QName;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.TypeMap;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

/**
 * Genarate a webservice for the complex types likes structs.
 * @author Srinath Perera (hemapani@opensource.lk)
 */

public class BeanParamWriter extends ParmWriter {
    /* weather this is a direct return type of the service */
    private boolean isdirectReturn;

    public BeanParamWriter(WebServiceContext wscontext, Type type) throws WrapperFault {
        super(wscontext, type);
        this.isdirectReturn =
            this.wscontext.getSerInfo().isDirectReturn(type.getLanguageSpecificName());
    }

    public void writeSerialieCode() throws WrapperFault {
        try {
            if (attribs.length == 0) {
                //nothing to print if this is simple type we have inbuild types
                System.out.println(
                    "possible error calss with no attributes....................");
                return;
            }

            writer.write(
                "\t\tString m_URI =\"" + type.getName().getNamespaceURI() + "\";\n");
            writer.write(
                "\t\tString type_name = \"" + type.getName().getLocalPart() + "\";\n");

            //otherwise name of parameter written by upper level
            if (this.isdirectReturn) {
                writer.write("\t\t//write start tag\n");
                writer.write(
                    "\t\tboolean writeOutTag = !org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten;\n");
                writer.write("\t\tif(writeOutTag){\n");
                //write the start tag
                writer.write(
					 "\t\t\t//write the start tag\n" 	
                     +"\t\t\tcontext.writeString(\"<prf:\");\n"
                     +"\t\t\tcontext.writeString(type_name);\n" 
                     + "\t\t\tcontext.writeString(\"  xmlns:prf =\\\"\");\n"
                     + "\t\t\tcontext.writeString(m_URI);\n"
                     +"\t\t\tcontext.writeString(\"\\\">\\n\");\n\n");
				writer.write("\t\t}\n");     
            }
            writer.write(
                "\t\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;\n");

            writer.write("\t\t//write the parameters\n\n");
            for (int i = 0; i < attribs.length; i++) {
                /**
                 * if(WrapperConstants.STYLE_DOCUMENT.equals(this.wscontext.getWrapInfo().getWrapperStyle()));
                 * write the type=typename code here 
                 */

                Type t;
                boolean check4null = !JavaUtils.isJavaSimpleType(attribs[i][1]);

                if (TypeMap.isSimpleType(attribs[i][1])) {
                    //for simple type
                    writer.write(
                        "\t\tcontext.writeString(\"<" + attribs[i][0] + ">\");\n");
                    writer.write(
                        check4null
                            ? "\t\tif(this." + attribs[i][0] + "!=null){\n"
                            : "");
                    if (JavaUtils.isUnwrapperdSimpleType(attribs[i][1]))
                        writer.write(
                            "\t\t\tcontext.writeString(String.valueOf("
                                + attribs[i][0]
                                + ".getParam()));\n");
                    else
                        writer.write(
                            "\t\t\tcontext.writeString(String.valueOf("
                                + attribs[i][0]
                                + "));\n");

                } else if (
                    (t =
                        wscontext.getTypemap().getType(
                            new QName(attribs[i][2], attribs[i][3])))
                        != null
                        && t.isArray()) {
                    //for array type
                    QName arrayType = t.getTypNameForAttribName("item");
                    String arrTypeAdditionalString =
                        " xsi:type=\\\"soapenc:Array\\\" soapenc:arrayType=\\\"ns2:"
                            + arrayType.getLocalPart()
                            + "[]\\\" xmlns:ns2 = \\\""
                            + arrayType.getNamespaceURI()
                            + "\\\"";
                    writer.write(
                        "\t\tcontext.writeString(\"<"
                            + attribs[i][0]
                            + arrTypeAdditionalString
                            + ">\");\n");
                    writer.write(
                        check4null
                            ? "\t\tif(this." + attribs[i][0] + "!=null){\n"
                            : "");
                    writer.write("\t\t\tcontext.writeString(\"\\n\");\n");
                    writer.write("\t\t\t"
                            + attribs[i][1]+ " item" + i
                            + " = new " + attribs[i][1] + "();\n");
                    writer.write(
                        "\t\t\titem" + i + ".setParam(" + attribs[i][0] + ");\n");
                    writer.write(
                        "\t\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;\n");
                    writer.write("\t\t\titem" + i + ".serialize(context);\n");
                } else {
                    //for complex type 
                    writer.write(
                        "\t\tcontext.writeString(\"<" + attribs[i][0] + ">\");\n");
                    writer.write(
                        check4null
                            ? "\t\tif(this." + attribs[i][0] + "!=null){\n"
                            : "");
                    writer.write(
                        "\t\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;\n");
                    writer.write("\t\t\t" + attribs[i][0] + ".serialize(context);\n");
                }
                writer.write(check4null ? "\t\t}\n" : "");
                writer.write(
                    "\t\tcontext.writeString(\"</" + attribs[i][0] + ">\\n\");\n\n");
            }

            //otherwise name of parameter written by upper level
            if (this.isdirectReturn) {
                writer.write("\t\t//write the end tag\n");
                writer.write("\t\tif(writeOutTag){\n");
                writer.write("\t\tcontext.writeString(\"</prf:\");"
                    + "\t\tcontext.writeString(type_name);\n"
                    +"\t\tcontext.writeString(\">\\n\");\n");
				writer.write("\t\t}\n");     
            }
        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    public String capitalizeFirstCaractor(String value) {
        char[] chars = value.toCharArray();
        chars[0] = Character.toUpperCase(value.charAt(0));
        return new String(chars);
    }

    public void writeDesireializeCode() throws WrapperFault {
        try {
            if (attribs.length == 0) {
                //nothing to print if this is simple type we have inbuild types
                System.out.println(
                    "possible error calss with no attributes....................");
                return;
            }

            writer.write("\t\tint count = " + this.attribs.length + ";\n");
            //start looping
            writer.write(
                "\t\tif(org.apache.axismora.wsdl2ws.java.ParmWriter.tag == null)\n");
            writer.write(
                "\t\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tag= msgdata.getTag();\n");

            writer.write("\t\t//come to first start tag\n");
            writer.write(
                "\t\twhile(!(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.START_TAG))\n");
            writer.write(
                "\t\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();\n");
            writer.write(
                "\t\t//skip it says the type\n\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();\n");
            writer.write(
                "\t\t//if the type of the next tag is end tag that means the content of element is null\n");

            writer.write(
                "\t\tif(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.END_TAG)\t\t\treturn null;\n\n");

            writer.write("\t\tfor(int i = 0;i<count;i++) {\n");

            writer.write(
                "\t\t\twhile(!(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.START_TAG))\n");
            writer.write(
                "\t\t\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();\n");
            writer.write(
                "\t\t\t\tString localName = org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getLocalpart();\n");
            //if part
            writer.write(
                "\t\t\t\tif(localName.equalsIgnoreCase(\"" + attribs[0][0] + "\")) {\n");
            Type t;

            if (TypeMap.isSimpleType(attribs[0][1])) {
                if (JavaUtils.isUnwrapperdSimpleType(attribs[0][1]))
                    writer.write(
                        "\t\t\t\t\tthis."
                            + attribs[0][0]
                            + "= new "
                            + WrapperUtils.getWrapperName4FullyQualifiedName(attribs[0][1])
                            + "(msgdata);\n");
                else {
                    writer.write(
                        "\t\t\t\t\tthis."
                            + attribs[0][0]
                            + "= new "
                            + WrapperUtils.getWrapperName4FullyQualifiedName(attribs[0][1])
                            + "(msgdata).getParam();\n");
                }
            } else if (
                (t =
                    wscontext.getTypemap().getType(
                        new QName(attribs[0][2], attribs[0][3])))
                    != null
                    && t.isArray()) {
                writer.write(
                    "\t\t\t\t\t"
                        + WrapperUtils.getWrapperName4FullyQualifiedName(attribs[0][1])
                        + " arrayT0 = (new "
                        + WrapperUtils.getWrapperName4FullyQualifiedName(attribs[0][1])
                        + "());\n");
                writer.write("\t\t\t\t\tarrayT0.desierialize(msgdata);\n");
                writer.write(
                    "\t\t\t\t\tthis." + attribs[0][0] + " = arrayT0.getParam();\n");
            } else {
                writer.write(
                    "\t\t\t\t\tthis."
                        + attribs[0][0]
                        + "= (new "
                        + WrapperUtils.getWrapperName4FullyQualifiedName(attribs[0][1])
                        + "());\n");
                writer.write(
                    "\t\t\t\t\tthis." + attribs[0][0] + ".desierialize(msgdata);\n");
            }

            //else if part
            for (int i = 1; i < attribs.length; i++) {
                writer.write(
                    "\t\t\t\t}else if (localName.equalsIgnoreCase(\""
                        + attribs[i][0]
                        + "\")) {\n");
                if (TypeMap.isSimpleType(attribs[i][1])) {
                    if (JavaUtils.isUnwrapperdSimpleType(attribs[i][1]))
                        writer.write(
                            "\t\t\t\t\tthis."
                                + attribs[i][0]
                                + "= new "
                                + WrapperUtils.getWrapperName4FullyQualifiedName(
                                    attribs[i][1])
                                + "(msgdata);\n");
                    else
                        writer.write(
                            "\t\t\t\t\tthis."
                                + attribs[i][0]
                                + "= (new "
                                + WrapperUtils.getWrapperName4FullyQualifiedName(
                                    attribs[i][1])
                                + "(msgdata)).getParam();\n");
                } else if (
                    (t =
                        wscontext.getTypemap().getType(
                            new QName(attribs[i][2], attribs[i][3])))
                        != null
                        && t.isArray()) {
                    writer.write(
                        "\t\t\t\t\t"
                            + WrapperUtils.getWrapperName4FullyQualifiedName(attribs[i][1])
                            + " arrayT"
                            + i
                            + " = (new "
                            + WrapperUtils.getWrapperName4FullyQualifiedName(attribs[i][1])
                            + "());\n");
                    writer.write(
                        "\t\t\t\t\tarrayT" + i + ".desierialize(msgdata);\n");
                    writer.write(
                        "\t\t\t\t\tthis."
                            + attribs[i][0]
                            + " = arrayT"
                            + i
                            + ".getParam();\n");
                } else {
                    writer.write(
                        "\t\t\t\t\tthis."
                            + attribs[i][0]
                            + "= (new "
                            + WrapperUtils.getWrapperName4FullyQualifiedName(attribs[i][1])
                            + "());\n");
                    writer.write(
                        "\t\t\t\t\tthis."
                            + attribs[i][0]
                            + ".desierialize(msgdata);\n");
                }
            }
            //end of conditions
            writer.write(
                "\t\t\t\t}else\n\t\t\t\t\tthrow new org.apache.axis.AxisFault(\"unknown tag find \"+ localName);\n");
            //get next tag
            writer.write(
                "\t\t\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();\n");
            //end looping
            writer.write("\t\t}//end of for loop\n");
        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

}
