package org.apache.axismora.wsdl2ws.doclit;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Enumeration;

import javax.xml.namespace.QName;
import org.apache.axismora.encoding.AxisPullParser;
import org.apache.axismora.wsdl2ws.java.JavaClassWriter;
import org.apache.axismora.wsdl2ws.java.JavaUtils;
import org.apache.axismora.wsdl2ws.WrapperConstants;
import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.ElementInfo;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.TypeMap;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;


/**
 * This class do not handle arrays.
 * Just handles the deserialization and serialization of in and out parameters. 
 * @author Dimuthu Leelaratne. (muthulee@opensource.lk)
 * @author JeyaKumaran.
 * 
 *
 */
public class DocLitBeanWriter extends JavaClassWriter {
    WebServiceContext wscontext;
    Type type; // type of this param
    String[][] attribs;

  	public DocLitBeanWriter(WebServiceContext wscontext, Type type) throws WrapperFault {
		super(WrapperUtils.getPackegeName4QualifiedName(type.getLanguageSpecificName()),
            WrapperUtils.getClassNameFromFullyQualifiedName(
                type.getLanguageSpecificName()),wscontext.getWrapInfo().getTargetOutputLocation());
        this.wscontext = wscontext;
        this.type = type;
        if (type.isArray())
            throw new WrapperFault("I am doclit in, out param writer. I do not write arrays");

        this.attribs =
				 this.getAttribList(wscontext.getSerInfo().getQualifiedServiceName());
    }

    /**
    	  * This method handle the logic of deserialization.
    	  * @throws WrapperFault
    	  */
    public void writeDesireializeCode() throws WrapperFault {
        try {
            if (attribs.length == 0) {
                //nothing to print if this is simple type we have inbuild types
                System.out.println(
                    "possible error calss with no attributes....................");
                return;
            }

            writer.write("\t\tint count = " + this.attribs.length + ";\n");
				      writer.write("\t\tAxisPullParser aXpp = msgdata.getAxisParser();\n");
					  
            writer.write("\t\tint state=aXpp.next();\n");
            writer.write(
                "\t\t//if the type of the next tag is end tag that means the content of element is null\n");
            writer.write("if(state == XmlPullParser.END_TAG){\n");
            writer.write("\t\t\t return null;\n");
            writer.write("\t\t}else if(state == XmlPullParser.START_TAG){\n");
            writer.write(
						  "\t\t}else{\nthrow new AxisFault(\" Invalid things inside element tag. Text data is in the element straight away\");}\n");

            //start looping
            writer.write("\t\tfor(int i = 0;i<count;i++) {\n");
            writer.write("\t\t\twhile(!(state == XmlPullParser.START_TAG))\n");
            writer.write("\t\t\t\tstate = aXpp.next();\n");

            writer.write("\t\t\t\tString localName =aXpp.getName();\n");
            //if part
            writer.write(
                "\t\t\t\tif(localName.equalsIgnoreCase(\""
                    + attribs[0][0]
                    + "\")) {\n");
            Type t;

            if (TypeMap.isSimpleType(attribs[0][1])) {
                if (JavaUtils.isUnwrapperdSimpleType(attribs[0][1]))
                    writer.write(
                        "\t\t\t\t\tthis."
                            + attribs[0][0]
                            + "= new "
                            + WrapperUtils.getWrapperName4FullyQualifiedName(
                                attribs[0][1])
                            + "(msgdata);\n");
                else {
                    writer.write(
                        "\t\t\t\t\tthis."
                            + attribs[0][0]
                            + "= new "
                            + WrapperUtils.getWrapperName4FullyQualifiedName(
                                attribs[0][1])
                            + "(msgdata).getParam();\n");
                }
            } else if (attribs[0][1].endsWith("[]")) {
                writer.write(
                    "\t\t\t\t\t"
                        + attribs[0][4]
                        + " arrayT0 = (new "
                        + attribs[0][4]
                        + "());\n");
                writer.write("\t\t\t\t\tarrayT0.desierialize(msgdata);\n");
                writer.write(
                    "\t\t\t\t\tthis."
                        + attribs[0][0]
                        + " = arrayT0.getParam();\n");
            } else {
                writer.write(
                    "\t\t\t\t\tthis."
                        + attribs[0][0]
                        + "= (new "
                        + WrapperUtils.getWrapperName4FullyQualifiedName(
                            attribs[0][1])
                        + "());\n");
                writer.write(
                    "\t\t\t\t\tthis."
                        + attribs[0][0]
                        + ".desierialize(msgdata);\n");
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
                } else if (attribs[0][1].endsWith("[]")) {
                    writer.write(
                        "\t\t\t\t\t"
                            + attribs[i][4]
                            + " arrayT"
                            + i
                            + " = (new "
                            + attribs[i][4]
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
                            + WrapperUtils.getWrapperName4FullyQualifiedName(
                                attribs[i][1])
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
            writer.write("\t\t\t\tstate = aXpp.next();\n");
            //end looping
            writer.write("\t\t}//end of for loop\n");
            writer.write("\t\t return this;\n");
            writer.write("\t\t}\n");

        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }

    }

    /**
       * This method handle the logic of serialization.
       * @throws WrapperFault
       */
    public void writeSerialieCode() throws WrapperFault {
        try {
            if (attribs.length == 0) {
                //nothing to print if this is simple type we have inbuild types
                System.out.println(
                    "possible error calss with no attributes....................");
                return;
            }

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

                } else if (attribs[i][1].endsWith("[]")) {
                    //TODO :: for array type
                    //						QName arrayType = new QName(attribs[i][5],attribs[i][6]);
                    //						String arrTypeAdditionalString =
                    //							" xsi:type=\\\"soapenc:Array\\\" soapenc:arrayType=\\\"ns2:"
                    //								+ arrayType.getLocalPart()
                    //								+ "[]\\\" xmlns:ns2 = \\\""
                    //								+ arrayType.getNamespaceURI()
                    //								+ "\\\"";
                    //						writer.write(
                    //							"\t\tcontext.writeString(\"<"
                    //								+ attribs[i][0]
                    //								+ arrTypeAdditionalString
                    //								+ ">\");\n");
                    //						writer.write(
                    //							check4null
                    //								? "\t\tif(this." + attribs[i][0] + "!=null){\n"
                    //								: "");
                    //						writer.write("\t\t\tcontext.writeString(\"\\n\");\n");
                    //						writer.write("\t\t\t"
                    //								+ attribs[i][4]+ " item" + i
                    //								+ " = new " + attribs[i][4] + "();\n");
                    //						writer.write(
                    //							"\t\t\titem" + i + ".setParam(" + attribs[i][0] + ");\n");
                    //						writer.write(
                    //							"\t\t\torg.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;\n");
                    //						writer.write("\t\t\titem" + i + ".serialize(context);\n");
                    //						
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

        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    protected String getimplementsPart() {
        return " implements org.apache.axismora.encoding.InOutParameter";
    }

    protected void writeClassComment() throws WrapperFault {
        try {
			  writer.write("/**\n * <p>This class is genarated by the tool WSDL2Ws.\n" +
				  " * It take care of the serialization and the desirialization of\n" +
				  " * the in and out parameters of document literal web service.\n" +
				  " */ \n");
        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    protected void writeImportStatements() throws WrapperFault {
        try {
					writer.write("import org.apache.axis.AxisFault;\n");
            writer.write("import org.xmlpull.v1.XmlPullParser;\n");
					writer.write("import org.apache.axismora.encoding.AxisPullParser;\n");
        } catch (IOException e) {
            throw new WrapperFault(e);
        }
    }

    protected void writeAttributes() throws WrapperFault {
        try {
            for (int i = 0; i < attribs.length; i++) {
                //if((t = wscontext.getTypemap().getType(new QName(attribs[i][2],attribs[i][3])))!= null && t.isArray()) continue;
                writer.write(
                    "\tprivate " + attribs[i][1] + " " + attribs[i][0] + ";\n");
            }
            writer.write("\n");
        } catch (IOException e) {
            throw new WrapperFault(e);
        }
    }
    protected void writeConstructors() throws WrapperFault {
        try {
            if (attribs.length > 0) {
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

//    /**
//     * get the path to the file.
//     * @return
//     */
//    protected File getJavaFilePath() {
//        new File(
//            wscontext.getWrapInfo().getTargetOutputLocation()
//                + "/"
//				  + WrapperUtils.getPackegeName4QualifiedName(
//					  type.getLanguageSpecificName()).replace(
//					  '.',
//					  '/'))
//            .mkdirs();
//        String fileName =
//            wscontext.getWrapInfo().getTargetOutputLocation()
//                + "/"
//                + type.getLanguageSpecificName().replace('.', '/')
//                + ".java";
//        return new File(fileName);
//    }

    /** genarate the arrtibs into an array 
     * Odd numbers for names.
     * Even numbers for types.
     * */
    public String[][] getAttribList(String Qualifiedname) throws WrapperFault {
        String[][] attribs;
        ArrayList attribfeilds = new ArrayList();
        ArrayList elementfeilds = new ArrayList();

        //this is for encoded stuff afford to consider the 
        //attributes and elemnts equal

        Enumeration names = type.getAttributeNames();
        while (names.hasMoreElements()) {
            attribfeilds.add(names.nextElement());
        }
        names = type.getElementnames();
        while (names.hasMoreElements()) {
            elementfeilds.add(names.nextElement());
        }

        //get all the fields

        attribs = new String[attribfeilds.size() + elementfeilds.size()][];
        for (int i = 0; i < attribfeilds.size(); i++) {
            attribs[i] = new String[7];
            attribs[i][0] = ((String) attribfeilds.get(i));

            Type t = type.getTypForAttribName(attribs[i][0]);
            attribs[i][1] = t.getLanguageSpecificName();
            QName name = t.getName();

            attribs[i][2] = name.getNamespaceURI();
            attribs[i][3] = name.getLocalPart();
            attribs[i][4] = attribs[i][1];
            attribs[i][5] = null;
            attribs[i][6] = null;
        }

        
		  for (int i = attribfeilds.size(); i < attribfeilds.size()+elementfeilds.size(); i++) {
            attribs[i] = new String[7];
			  attribs[i][0] = ((String) elementfeilds.get(i - attribfeilds.size()));

            ElementInfo element = type.getElementForElementName(attribs[i][0]);
            Type t = element.getType();
            attribs[i][1] = t.getLanguageSpecificName();
            QName name = t.getName();

            attribs[i][2] = name.getNamespaceURI();
            attribs[i][3] = name.getLocalPart();

            attribs[i][4] = attribs[i][1];

            if (t.isArray()) {
                attribs[i][4] = attribs[i][1];
                Type arrayType = WrapperUtils.getArrayType(t);
                attribs[i][1] = arrayType.getLanguageSpecificName() + "[]";
                attribs[i][5] = arrayType.getName().getNamespaceURI();
                attribs[i][6] = arrayType.getName().getLocalPart();

            }

            if (element.getMaxOccurs() > 1) {
                attribs[i][1] = attribs[i][1] + "[]";
				  Type typedata = new Type(new QName(name.getNamespaceURI(),name.getLocalPart()+"Array")
					  ,null,false,WrapperConstants.LANGUAGE_JAVA);
				  typedata.setTypeNameForElementName(new ElementInfo(new QName("item"),t));
                typedata.setArray(true);
                attribs[i][4] = TypeMap.regestorArrayTypeToCreate(typedata);
                attribs[i][5] = t.getName().getNamespaceURI();
                attribs[i][6] = t.getName().getLocalPart();

            }
        }

        return attribs;
    }

    private void writeGettersAndSetter() throws IOException, WrapperFault {
        for (int i = 0; i < this.attribs.length; i++) {
            writer.write(
                "\tpublic void set"
                    + WrapperUtils.capitalizeFirstCaractor(attribs[i][0])
                    + "("
                    + attribs[i][1]
                    + " "
                    + attribs[i][0]
                    + "){\n\t\tthis."
                    + attribs[i][0]
                    + " = "
                    + attribs[i][0]
                    + ";\n\t}\n");
            writer.write(
                "\tpublic "
                    + attribs[i][1]
                    + " get"
                    + WrapperUtils.capitalizeFirstCaractor(attribs[i][0])
                    + "(){\n\t\treturn "
                    + attribs[i][0]
                    + ";\n\t}\n");
        }
    }
    protected void writeAttributesConstructor() throws WrapperFault {
        try {
            writer.write(
                "\tpublic "
                    + WrapperUtils.getClassNameFromFullyQualifiedName(
                        type.getLanguageSpecificName())
                    + "(");
            if (attribs.length > 0) {
				  writer.write(attribs[0][1]
						  + " "
						  + attribs[0][0]);
                for (int i = 1; i < this.attribs.length; i++)
					  writer.write(", "+attribs[i][1]
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

    public void writeInitializer() throws IOException, WrapperFault {
        String temp = null;

        for (int i = 0; i < attribs.length; i++) {
            String name = attribs[i][1];
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
            String name = attribs[i][1];

            //TODO :: Dimuthu remve this. if array
            // extends part		
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
