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
			this.wscontext.getSerInfo().isDirectReturn(type.getName());
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
				"\t\tjava.lang.String m_URI =\"" + type.getName().getNamespaceURI() + "\";\n");
			writer.write(
				"\t\tjava.lang.String type_name = \"" + type.getName().getLocalPart() + "\";\n");


			writer.write("\t\t//write the parameters\n\n");
			for (int i = 0; i < attribs.length; i++) {
				/**
				 * if(WrapperConstants.STYLE_DOCUMENT.equals(this.wscontext.getWrapInfo().getWrapperStyle()));
				 * write the type=typename code here 
				 */

				Type t;
				boolean check4null = !JavaUtils.isJavaSimpleType(attribs[i].javaType);

				if (TypeMap.isSimpleType(attribs[i].javaType)) {
					//for simple type
					writer.write(
						"\t\tcontext.writeString(\"<" + attribs[i].javaNm + ">\");\n");
					writer.write(
						check4null
							? "\t\tif(this." + attribs[i].javaNm + "!=null){\n"
							: "");
					writer.write(
						"\t\t\tcontext.writeSafeString(java.lang.String.valueOf("
							+ attribs[i].javaNm
							+ "));\n");

				} else if (attribs[i].javaType.endsWith("[]") && !"byte[]".equals(attribs[i].javaType)){
					//for array type
					QName arrayType = attribs[i].xmlType;
					String arrTypeAdditionalString =
						" xsi:type=\\\"soapenc:Array\\\" soapenc:arrayType=\\\"ns2:"
							+ arrayType.getLocalPart()
							+ "[]\\\" xmlns:ns2 = \\\""
							+ arrayType.getNamespaceURI()
							+ "\\\"";
					writer.write(
						"\t\tcontext.writeString(\"<"
							+ attribs[i].javaNm
							+ arrTypeAdditionalString
							+ ">\");\n");
					writer.write(
						check4null
							? "\t\tif(this." + attribs[i].javaNm + "!=null){\n"
							: "");
					writer.write("\t\t\tcontext.writeString(\"\\n\");\n");
					writer.write("\t\t\t"
							+ attribs[i].wrapName+ " item" + i
							+ " = new " + attribs[i].wrapName + "();\n");
					writer.write(
						"\t\t\titem" + i + ".setParam(" + attribs[i].javaNm + ");\n");
					writer.write("\t\t\titem" + i + ".serialize(context);\n");
				} else {
					//for complex type 
					writer.write(
						"\t\tcontext.writeString(\"<" + attribs[i].javaNm + ">\");\n");
					writer.write(
						check4null
							? "\t\tif(this." + attribs[i].javaNm + "!=null){\n"
							: "");
					writer.write("\t\t\t" + attribs[i].javaNm + ".serialize(context);\n");
				}
				writer.write(check4null ? "\t\t}\n" : "");
				writer.write(
					"\t\tcontext.writeString(\"</" + attribs[i].javaNm + ">\\n\");\n\n");
			}

		} catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}
	
	public void writeSerialieCode1() throws WrapperFault {
		try {
			if (attribs.length == 0) {
				//nothing to print if this is simple type we have inbuild types
				System.out.println(
					"possible error calss with no attributes....................");
				return;
			}

			writer.write(
				"\t\tjava.lang.String m_URI =\"" + type.getName().getNamespaceURI() + "\";\n");
			writer.write(
				"\t\tjava.lang.String type_name = \"" + type.getName().getLocalPart() + "\";\n");


			writer.write("\t\t//write the parameters\n\n");
			for (int i = 0; i < attribs.length; i++) {
				/**
				 * if(WrapperConstants.STYLE_DOCUMENT.equals(this.wscontext.getWrapInfo().getWrapperStyle()));
				 * write the type=typename code here 
				 */

				Type t;
				boolean check4null = !JavaUtils.isJavaSimpleType(attribs[i].javaType);

				if (TypeMap.isSimpleType(attribs[i].javaType)) {
					//for simple type
					writer.write(
						"\t\tcontext.writeString(\"<" + attribs[i].javaNm + ">\");\n");
					writer.write(
						check4null
							? "\t\tif(this." + attribs[i].javaNm + "!=null){\n"
							: "");
					writer.write(
						"\t\t\tcontext.writeSafeString(java.lang.String.valueOf("
							+ attribs[i].javaNm
							+ "));\n");

				} else if (attribs[i].javaType.endsWith("[]") && !"byte[]".equals(attribs[i].javaType)){
					//for array type
					QName arrayType = attribs[i].xmlType;
					String arrTypeAdditionalString =
						" xsi:type=\\\"soapenc:Array\\\" soapenc:arrayType=\\\"ns2:"
							+ arrayType.getLocalPart()
							+ "[]\\\" xmlns:ns2 = \\\""
							+ arrayType.getNamespaceURI()
							+ "\\\"";
					writer.write(
						"\t\tcontext.writeString(\"<"
							+ attribs[i].javaNm
							+ arrTypeAdditionalString
							+ ">\");\n");
					writer.write(
						check4null
							? "\t\tif(this." + attribs[i].javaNm + "!=null){\n"
							: "");
					writer.write("\t\t\tcontext.writeString(\"\\n\");\n");
					writer.write("\t\t\t"
							+ attribs[i].wrapName+ " item" + i
							+ " = new " + attribs[i].wrapName + "();\n");
					writer.write(
						"\t\t\titem" + i + ".setParam(" + attribs[i].javaNm + ");\n");
					writer.write("\t\t\titem" + i + ".serialize(context);\n");
				} else {
					//for complex type 
					writer.write(
						"\t\tcontext.writeString(\"<" + attribs[i].javaNm + ">\");\n");
					writer.write(
						check4null
							? "\t\tif(this." + attribs[i].javaNm + "!=null){\n"
							: "");
					writer.write("\t\t\t" + attribs[i].javaNm + ".serialize(context);\n");
				}
				writer.write(check4null ? "\t\t}\n" : "");
				writer.write(
					"\t\tcontext.writeString(\"</" + attribs[i].javaNm + ">\\n\");\n\n");
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
            
			writer.write("\t\torg.apache.axismora.encoding.AxisPullParser psr = msgdata.getAxisParser();\n");
			writer.write("\t\tint count = " + this.attribs.length + ";\n");
			//start looping

			writer.write("\t\t//come to first start tag\n");
			writer.write("\t\twhile(!(psr.getState() == org.xmlpull.v1.XmlPullParser.START_TAG))\n");
			writer.write("\t\t\tpsr.next();\n");
			writer.write("\t\t//skip it says the type\n");
			writer.write("\t\tpsr.next();\n");
			writer.write("\t\t//if the type of the next tag is end tag that means the content of element is null\n");

			writer.write("\t\tif(psr.getState() == org.xmlpull.v1.XmlPullParser.END_TAG)\n");
			writer.write("\t\t\treturn null;\n\n");

			writer.write("\t\tfor(int i = 0;i<count;i++) {\n");

			writer.write("\t\t\twhile(!(psr.getState() == org.xmlpull.v1.XmlPullParser.START_TAG))\n");
			writer.write("\t\t\t\tpsr.next();\n");
			writer.write("\t\t\t\tString localName = psr.getName();\n");
			writer.write("\t\t\t\tint localNameHash = localName.hashCode();\n");
//			//if part
//			writer.write(
//				"\t\t\t\tif(localName.equalsIgnoreCase(\"" + attribs[0].javaNm + "\")) {\n");
//			//Type t;
//
//			JavaUtils.writeDeserializeCodeLine("this."+attribs[0].javaNm,attribs[0].javaNm,attribs[0].wrapName,"\t\t\t\t\t",writer,0);
//			//else if part
			writer.write("\t\t\t\tswitch(localNameHash){\n");
			for (int i = 0; i < attribs.length; i++) {
				writer.write("\t\t\t\t\tcase " + attribs[i].xmlNm.hashCode() +":\n");
				JavaUtils.writeDeserializeCodeLine("this."+attribs[i].javaNm,attribs[i].javaType,attribs[i].wrapName,"\t\t\t\t\t\t",writer,i);
				writer.write("\t\t\t\t\tbreak;\n");
			}
			//end of conditions
			writer.write("\t\t\t\t default:\n");
			writer.write(
				"\t\t\t\t\t\tthrow new org.apache.axis.AxisFault(\"unknown tag find \"+ localName);\n");
			writer.write("\t\t\t\t}\n");	
			//get next tag
            
			writer.write("\t\tpsr.next();\n");
			//end looping
			writer.write("\t\t}//end of for loop\n");
		} catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}

}
