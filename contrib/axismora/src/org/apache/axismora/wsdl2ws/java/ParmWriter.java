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

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axismora.soap.XMLTextData;
import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.TypeMap;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

/**
 * This class has the basic logic of the genarating Param classes (Type wrappers).
 * The responsibility of writing serializing and desirializing code is given to the
 * concreate subclasses.
 * 
 * If user try to genarate parametr class with no parameters,the genarated classes
 * will have a two default constructors and give an error. The user have to fix it
 * manually.
 *  
 * @author JayaKumaran
 */
public abstract class ParmWriter extends JavaClassWriter {
    public static boolean tagWritten = false;
    public static XMLTextData tag = null;

    protected static final int INPUT_PARM = 0;
    protected static final int RETURN_PARM = 1;
    protected static final int COMMAN_PARM = 2;

    /* array of parameter types and parameter names of the this param */
    protected String[][] attribs;

    protected WebServiceContext wscontext;

    /* Type of this param */
    protected Type type;

    public ParmWriter(WebServiceContext wscontext, Type type) throws WrapperFault {

        super(
            WrapperUtils.getPackegeName4QualifiedName(type.getLanguageSpecificName()),
            WrapperUtils.getClassNameFromFullyQualifiedName(
                type.getLanguageSpecificName()));
        this.wscontext = wscontext;
        this.type = type;
        this.attribs =
            this.getAttribList(wscontext.getSerInfo().getQualifiedServiceName());
    }

    /**
     * This method handle the logic of serialization.
     * @throws WrapperFault
     */
    public abstract void writeSerialieCode() throws WrapperFault;

    /**
     * This method handle the logic of deserialization.
     * @throws WrapperFault
     */
    public abstract void writeDesireializeCode() throws WrapperFault;

    protected String getimplementsPart() {
        return " implements org.apache.axismora.encoding.InOutParameter";
    }

    protected void writeClassComment() throws WrapperFault {
        try {
            writer.write("/**\n * <p>This class is genarated by the tool WSDL2Ws.\n" +
            	" * It take care of the serialization and the desirialization of\n" +
            	" * the parameter types.\n" +
            	" * except for the serialize(), desirialize() methods it it a bean class.\n" +
            	" * We are specially concerned about the alogorithem used in the desirialize method.\n" +
            	" * If you have any suggestions to improve, your comments are welcome.</p>\n" +
            	" */ \n");
        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    protected void writeImportStatements() throws WrapperFault {
    }
    protected void writeAttributes() throws WrapperFault {
        if (type.isArray())
            return;
        try {
            for (int i = 0; i < attribs.length; i++) {
                //if((t = wscontext.getTypemap().getType(new QName(attribs[i][2],attribs[i][3])))!= null && t.isArray()) continue;
                writer.write(
                    "\tprivate "
                        + getCrroectParmNameConsideringArrays(
                            new QName(attribs[i][2], attribs[i][3]),
                            attribs[i][1])
                        + " "
                        + attribs[i][0]
                        + ";\n");
            }
			writer.write("\n");
        } catch (IOException e) {
            throw new WrapperFault(e);
        }
    }
    protected void writeConstructors() throws WrapperFault {
        try {
        	if(attribs.length>0){
            	writer.write(
                	"\tpublic "
                    	+ WrapperUtils.getClassNameFromFullyQualifiedName(
                        	type.getLanguageSpecificName())
                    	+ "(){\n");
             	//this.writeInitializer();
            	writer.write("\t}\n");
        	}	
            writeAttributesConstructor();
			writer.write("\n");
        } catch (IOException e) {
            throw new WrapperFault(e);
        }
    }
    protected void writeMethods() throws WrapperFault {
        try {
            if (this.type.isArray())
                writeArrayTypeAdditionalCode();
			writer.write("\n");    
            writeDesirializeMethod();
			writer.write("\n");
            writeSerializeMethod();
            writer.write("\n");
            writeGettersAndSetter();
            //writeEqual();
        } catch (IOException e) {
            throw new WrapperFault(e);
        }
    }

    public void writeDesirializeMethod() throws WrapperFault {
        try {
            writer.write(
                "\tpublic org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{\n");
            this.writeDesireializeCode();
            writer.write("\t\treturn this;\n");
            writer.write("\n\t}\n");
        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }

    }

    public void writeSerializeMethod() throws WrapperFault {
        try {
            writer.write(
                "\tpublic void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{\n");
            this.writeSerialieCode();
            writer.write("\t}\n");
        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    public void writeArrayTypeAdditionalCode() throws WrapperFault {
        try {
            Iterator e = type.getAttribNames();

            if (e.hasNext()) {
                QName elementQname = type.getTypNameForAttribName((String) e.next());
                Type type = this.wscontext.getTypemap().getType(elementQname);
                String contentTypeName;

                if (type != null)
                    contentTypeName = type.getLanguageSpecificName();
                else {
                    contentTypeName = TypeMap.getBasicTypeClass4qname(elementQname);
                    if (contentTypeName == null)
                        throw new WrapperFault(
                            "if not inbuild or not in type map what is this type "
                                + elementQname);
                }

                writer.write("\tprivate " + contentTypeName + "[] param;\n");
                writer.write(
                    "\tpublic "
                        + contentTypeName
                        + "[] getParam(){\n\t\treturn this.param;\n\t}\n");
                writer.write(
                    "\tpublic void setParam("
                        + contentTypeName
                        + "[] param){\n\t\tthis.param = param;\n\t}\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }

    }

    /**
     * get the path to the file.
     * @return
     */
    protected File getJavaFilePath() {
        new File(
            wscontext.getWrapInfo().getTargetOutputLocation()
                + "/"
                + WrapperUtils.getPackegeName4QualifiedName(
                    type.getLanguageSpecificName()).replace(
                    '.',
                    '/'))
            .mkdirs();
        String fileName =
            wscontext.getWrapInfo().getTargetOutputLocation()
                + "/"
                + type.getLanguageSpecificName().replace('.', '/')
                + ".java";
        System.out.println(fileName);
        return new File(fileName);
    }
    /* genarate the arrtibs array */
    public String[][] getAttribList(String Qualifiedname) throws WrapperFault {
        String[][] attribs;
        ArrayList feilds = new ArrayList();

        Iterator names = type.getAttribNames();
        while (names.hasNext()) {
            feilds.add(names.next());

        }
        //get all the fields

        attribs = new String[feilds.size()][];
        for (int i = 0; i < feilds.size(); i++) {
            attribs[i] = new String[4];
            attribs[i][0] = ((String) feilds.get(i));

            QName name = type.getTypNameForAttribName(attribs[i][0]);

            if (TypeMap.isSimpleType(name))
                attribs[i][1] = TypeMap.getBasicTypeClass4qname(name);
            else {

                Type t = this.wscontext.getTypemap().getType(name);
                attribs[i][1] = t.getLanguageSpecificName();
                System.out.println(name + " = " + attribs[i][1]);
            }

            attribs[i][2] = name.getNamespaceURI();
            attribs[i][3] = name.getLocalPart();

        }
        return attribs;
    }

    private void writeGettersAndSetter() throws IOException, WrapperFault {
        if (type.isArray())
            return;
        for (int i = 0; i < this.attribs.length; i++) {
            writer.write(
                "\tpublic void set"
                    + WrapperUtils.capitalizeFirstCaractor(attribs[i][0])
                    + "("
                    + getCrroectParmNameConsideringArrays(
                        new QName(attribs[i][2], attribs[i][3]),
                        attribs[i][1])
                    + " "
                    + attribs[i][0]
                    + "){\n\t\tthis."
                    + attribs[i][0]
                    + " = "
                    + attribs[i][0]
                    + ";\n\t}\n");
            writer.write(
                "\tpublic "
                    + getCrroectParmNameConsideringArrays(
                        new QName(attribs[i][2], attribs[i][3]),
                        attribs[i][1])
                    + " get"
                    + WrapperUtils.capitalizeFirstCaractor(attribs[i][0])
                    + "(){\n\t\treturn "
                    + attribs[i][0]
                    + ";\n\t}\n");
        }
    }
    protected void writeAttributesConstructor() throws WrapperFault {
        if (this.type.isArray())
            return;
        try {
            writer.write(
                "\tpublic "
                    + WrapperUtils.getClassNameFromFullyQualifiedName(
                        type.getLanguageSpecificName())
                    + "(");
            if (attribs.length > 0) {
                writer.write(
                    getCrroectParmNameConsideringArrays(
                        new QName(attribs[0][2], attribs[0][3]),
                        attribs[0][1])
                        + " "
                        + attribs[0][0]);
                for (int i = 1; i < this.attribs.length; i++)
                    writer.write(
                        ","
                            + getCrroectParmNameConsideringArrays(
                                new QName(attribs[i][2], attribs[i][3]),
                                attribs[i][1])
                            + " "
                            + attribs[i][0]);
            }
            writer.write("){\n");
            for (int i = 0; i < this.attribs.length; i++)
                writer.write("\t\tthis." + attribs[i][0] + " = " + attribs[i][0] + ";\n");
            writer.write("\t}\n");
        } catch (IOException e) {
            throw new WrapperFault(e);
        }
    }
    private String getCrroectParmNameConsideringArrays(QName name, String classname)
        throws WrapperFault {
        System.out.println(name);
        Type t = wscontext.getTypemap().getType(name);
        if (t != null && t.isArray()) {
            Iterator e = t.getAttribNames();
            String contentTypeName;
            if (e.hasNext()) {
                QName elementQname = t.getTypNameForAttribName((String) e.next());
                Type type = this.wscontext.getTypemap().getType(elementQname);

                if (type != null)
                    contentTypeName = type.getLanguageSpecificName();
                else {
                    contentTypeName = TypeMap.getBasicTypeClass4qname(elementQname);
                    if (contentTypeName == null)
                        throw new WrapperFault(
                            "if not inbuild or not in type map what is this type "
                                + elementQname);
                }
            } else
                throw new WrapperFault("Array with no type ????");
            return contentTypeName + "[]";
        } else
            return classname;
    }

    //TODO remove this is for ease of testing 

    public void writeInitializer() throws IOException, WrapperFault {
        String temp = null;
        if (type.isArray())
            return;

        for (int i = 0; i < attribs.length; i++) {
            String name =
                getCrroectParmNameConsideringArrays(
                    new QName(attribs[i][2], attribs[i][3]),
                    attribs[i][1]);
            writer.write("this." + attribs[i][0] + " =");

            if (name.endsWith("[]")) {
                writer.write(!"byte[]".equals(name) ? (" new " + name + "{") : "");
                temp = attribs[i][1];
                attribs[i][1] = name.substring(0, name.length() - 2);
            }

            if ("boolean".equals(attribs[i][1]))
                writer.write("false");
            else if (
                "int".equals(attribs[i][1])
                    || "long".equals(attribs[i][1])
                    || "float".equals(attribs[i][1])
                    || "double".equals(attribs[i][1])
                    || "short".equals(attribs[i][1]))
                writer.write(String.valueOf(i));
            else if ("byte".equals(attribs[i][1]))
                writer.write("\"string" + i + "\".getBytes();\n");
            else if ("char".equals(attribs[i][1]))
                writer.write("\'" + i + "\'");
            else if ("java.lang.String".equals(attribs[i][1]))
                writer.write("\"string" + i + "\"");
            else
                writer.write("new " + attribs[i][1] + "()");
            if (name.endsWith("[]")) {
                writer.write(!"byte[]".equals(name) ? "}" : "");
                attribs[i][1] = temp;
            }
            writer.write(";\n");

        }

    }

    public void writeEqual() throws IOException, WrapperFault {
        if (type.isArray())
            return;
        writer.write("\tpublic boolean equals(Object obj) {\n");
        writer.write(
            "\t\tif(!(obj instanceof "
                + type.getLanguageSpecificName()
                + "))\n\t\t\treturn false;\n");
        writer.write(
            "\t\t"
                + type.getLanguageSpecificName()
                + " value = ("
                + type.getLanguageSpecificName()
                + ")obj;\n");

        for (int i = 0; i < attribs.length; i++) {
            String name =
                getCrroectParmNameConsideringArrays(
                    new QName(attribs[i][2], attribs[i][3]),
                    attribs[i][1]);

            //if array		
            if (name.endsWith("[]")) {
                String tname = name.substring(0, name.length() - 2);
                writer.write(
                    "\t\tif("
                        + attribs[i][0]
                        + "!=null && "
                        + attribs[i][0]
                        + ".length !=0){\n");
                if ("int".equals(tname)
                    || "long".equals(tname)
                    || "float".equals(tname)
                    || "double".equals(tname)
                    || "short".equals(tname)
                    || "byte".equals(tname)
                    || "char".equals(tname)
                    || "boolean".equals(tname)) {
                    writer.write(
                        "\t\tif("
                            + attribs[i][0]
                            + "[0] != value.get"
                            + WrapperUtils.capitalizeFirstCaractor(attribs[i][0])
                            + "()[0])\n\t\t\treturn false;\n");
                } else {
                    //else
                    writer.write(
                        "\t\tif(!"
                            + attribs[i][0]
                            + "[0].equals(value.get"
                            + WrapperUtils.capitalizeFirstCaractor(attribs[i][0])
                            + "()[0]))\n\t\t\treturn false;\n");
                }
                writer.write("\t\t}\n");
                //if simple type	
            } else if (
                "int".equals(attribs[i][1])
                    || "long".equals(attribs[i][1])
                    || "float".equals(attribs[i][1])
                    || "double".equals(attribs[i][1])
                    || "short".equals(attribs[i][1])
                    || "byte".equals(attribs[i][1])
                    || "char".equals(attribs[i][1])
                    || "boolean".equals(attribs[i][1])) {
                writer.write(
                    "\t\tif("
                        + attribs[i][0]
                        + " != value.get"
                        + WrapperUtils.capitalizeFirstCaractor(attribs[i][0])
                        + "())\n\t\t\treturn false;\n");
            } else {
                //else
                writer.write(
                    "\t\tif(!"
                        + attribs[i][0]
                        + ".equals(value.get"
                        + WrapperUtils.capitalizeFirstCaractor(attribs[i][0])
                        + "()))\n\t\t\treturn false;\n");
            }

        }
        writer.write("\t\treturn false;");
        writer.write("\t}\n");

    }

}
