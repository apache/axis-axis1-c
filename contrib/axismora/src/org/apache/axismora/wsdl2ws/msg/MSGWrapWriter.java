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

package org.apache.axismora.wsdl2ws.msg;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import org.apache.axismora.Constants;
import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.MethodInfo;
import org.apache.axismora.wsdl2ws.info.ParameterInfo;
import org.apache.axismora.wsdl2ws.info.TypeMap;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;
import org.apache.axismora.wsdl2ws.java.JavaClassWriter;

/**
 * This wrapper generator is for message style services
 * Right now it supports only the methods with the below signature.
 *      <code>      public Element [] method(Element [] bodies) </code>
 * @author Dimuthu Leelarathne. (muthulee@opensource.lk) 
 */

public class MSGWrapWriter extends JavaClassWriter {
    private ArrayList methods;
    private WebServiceContext wscontext;

    public MSGWrapWriter(WebServiceContext wscontext) throws WrapperFault {
        super(
            WrapperUtils.getPackegeName4QualifiedName(
                wscontext.getSerInfo().getQualifiedServiceName()),
            WrapperUtils.getClassNameFromFullyQualifiedName(
                wscontext.getSerInfo().getQualifiedServiceName())
                + Constants.WRAPPER_NAME_APPENDER);
        this.wscontext = wscontext;
        methods = this.wscontext.getSerInfo().getMethods();
    }

    protected String getExtendsPart() {
        return " extends org.apache.axismora.server.utils.BasicHandler";
    }

    protected void writeClassComment() throws WrapperFault {
        try {
            writer.write(
                "/**\n * This Code is Genarated by the Wrapper Genarator. \n * This Class act as the Wrapper to invoke the Webservice methods\n*/\n");
        } catch (IOException e) {
            throw new WrapperFault(e);
        }
    }

    protected void writeImportStatements() throws WrapperFault {
        try {
            writer.write(
                "import org.apache.axis.AxisFault;\nimport org.apache.axis.message.SOAPFault;\n");
        } catch (IOException e) {
            throw new WrapperFault(e);
        }
    }
    protected void writeAttributes() throws WrapperFault {
        try {
            writer.write(
                "\tprivate "
                    + wscontext.getSerInfo().getQualifiedServiceName()
                    + " service;\n\n");
            writer.write("\tprivate Element[] eleArry;\n");
        } catch (IOException e) {
            throw new WrapperFault(e);
        }
    }
    protected void writeConstructors() throws WrapperFault {
        try {
            writer.write(
                "\tpublic "
                    + servicename
                    + "(){\n\t\t\tservice = new "
                    + wscontext.getSerInfo().getQualifiedServiceName()
                    + "();\n\t}\n\n");
        } catch (IOException e) {
            throw new WrapperFault(e);
        }
    }
    protected void writeMethods() throws WrapperFault {
        try {
            //write invoke method
            writer.write("/*\n\tThis method is called by the Wrapper. \n*/\n");
            writeGetElementArray();
            writeInvoke();
            writer.write("\n");
            MethodInfo minfo;
            //write service wrapping methods
            for (int i = 0; i < methods.size(); i++) {
                minfo = (MethodInfo) methods.get(i);
                this.writeMethodInWrapper(
                    minfo.getMethodname(),
                    minfo.getParameterTypess(),
                    minfo.getReturnType().getLangName());
                writer.write("\n");
            }
        } catch (IOException e) {
            throw new WrapperFault(e);
        }
    }

    /**
     * write the invoke method
     * @throws IOException
     */
    private void writeInvoke() throws IOException {
        // following code to reads the SOAPBody as an array of elements.

        // the arrays will contain one element for each XML element inside the <soap:body> in the envelope.
        writer.write("\tpublic void invoke(org.apache.axismora.MessageData msgdata){\n");
        //msgdata.setSoapFault(new SOAPFault(new AxisFault()))
        writer.write("\t\t try{\n");
        writer.write(
            "\t\t\tString methodToCall = msgdata.getMethodName().getLocalPart();\n");

        //if no methods in the service simply return
        if (methods.size() == 0) {
            writer.write("\t}\n");
            return;
        }
        MethodInfo minfo = (MethodInfo) methods.get(0);
        //if conditions (if parts)
        writer.write(
            "\t\t\tif(\"" + minfo.getMethodname() + "\".equals(methodToCall))\n");
        writer.write("\t\t\t\tthis." + minfo.getMethodname() + "(bodies);\n\t\t\n");
        //(else if parts)

        if (methods.size() > 1) {
            for (int i = 1; i < methods.size(); i++) {
                minfo = (MethodInfo) methods.get(i);
                writer.write(
                    "\t\t\telse if(\""
                        + minfo.getMethodname()
                        + "\".equals(methodToCall))\n");
                writer.write(
                    "\t\t\t\tthis." + minfo.getMethodname() + "(bodies);\n\t\t\n");
            }
        }
        //(else part)
        writer.write("\t\t\telse  throw new AxisFault(\"method not found\");\n");

        //catch block
        writer.write(
            "\t\t}catch(AxisFault e){\n\t\t\t\tmsgdata.setSoapFault(new SOAPFault(e));\n\t\t}\n");
        writer.write(
            "\t\tcatch(Exception e){\n\t\t\t\tmsgdata.setSoapFault(new SOAPFault(new AxisFault(\"error at wrapper invoke\",e)));\n\t\t}\n");
        //end of method
        writer.write("\t}\n");
    }

    /**
     * This method genarate methods that wraps the each method of the service
     * @param methodName
     * @param params
     * @param outparam
     * @throws IOException
     */

    public void writeMethodInWrapper(
        String methodName,
        Collection params,
        String outparam)
        throws IOException {
        //method signature
        writer.write(
            "\tpublic void "
                + methodName
                + "(org.apache.axismora.MessageData msgdata){\n");

        //create the param classes for each parameter
        String paraTypeName;
        ArrayList paramsB = new ArrayList(params);
        Iterator p = params.iterator();

        for (int i = 0; i < paramsB.size(); i++) {

            paraTypeName = "test";
            //WrapperUtils.getClassNameFromParamInfoConsideringArrays((ParameterInfo)paramsB.get(i),wscontext);

            if ((TypeMap.isSimpleType(((ParameterInfo) paramsB.get(i)).getLangName())))
                writer.write(
                    paraTypeName
                        + " paramIn"
                        + i
                        + " =  (new  "
                        + paraTypeName
                        + "(msgdata)).getParam();\n");
            else {
                writer.write(
                    "\t\t"
                        + paraTypeName
                        + "paramIn"
                        + i
                        + " =  new  "
                        + paraTypeName
                        + "();\n");
                writer.write("\t\tparamIn" + i + ".desierialize(msgdata);\n");
            }
            //writer.write("\t\t paramIn" + i + ".desierialize(msgdata);\n");
        }
        if (!(outparam == null || outparam.equals("void"))) {
            boolean isSimpleType = TypeMap.isSimpleType(outparam);

            //invoke the method on the result and ser the result to message data
            /*	if (!isSimpleType)
            	    writer.write("\t\tmsgdata.setSoapBodyContent(new " + WrapperUtils.getWrapperName4FullyQualifiedName(outparam) + "(service." + methodName + "(");	writer.write("\t\tmsgdata.setResult(service." + methodName + "(");
            	else
            		writer.write("\t\tmsgdata.setResult(new " + WrapperUtils.getClassNameFromParamInfoConsideringArrays((ParameterInfo)paramsB.get(i) ,wscontext) + "(service." + methodName + "(");
               */
            for (int i = 0; i < paramsB.size() - 1; i++) {
                writer.write("paramIn" + i + ",");
            }
            writer.write("paramIn" + (paramsB.size() - 1));
            //close parethsis
            if (!isSimpleType)
                writer.write("));\n");
            else
                writer.write(")));\n");
        } else {
            writer.write("\t\t service." + methodName + "(");
            for (int i = 0; i < paramsB.size() - 1; i++) {
                writer.write("paramIn" + i + ",");
            }
            writer.write("paramIn" + (paramsB.size() - 1));
            writer.write(")\n");
        }

        //write end of method
        writer.write("\t}\n");

    }

    private void writeGetElementArray() {
        try {
            writer.write(
                "\npublic void BodyToElements(MessageData msgData,String rootNameSpace,String rootName) throws AxisFault{\n");
            writer.write("\tXmlPullParser xpp = msgData.getBodyParser();\n");
            writer.write(
                "\tString nameSpace = msgData.getEnvelope().getNamespaceURI();\n");
            writer.write("\ttry{\n");
            writer.write("\t\tint state= xpp.getEventType();\n");
            writer.write("\t\twhile(state!=XmlPullParser.END_DOCUMENT){\n");
            writer.write("\t\t\tif(state==XmlPullParser.START_TAG){\n ");
            writer.write(
                "\t\t\t\tif(nameSpace.equals(xpp.getNamespace()) && \"Body\".equals(xpp.getName()) ){\n");
            writer.write(
                "\t\t\t\t\tParser2Element.RootElement2ChildElements(xpp.getNamespace(),\"Body\",xpp);\n");
            // get the Element array
            writer.write("\t\t\t\t\tbreak;\n");
            writer.write("\t\t\t\t}\n");
            writer.write("\t\t\t}\n");
            writer.write("\t\t\tstate= xpp.next();\n");
            writer.write("\t\t\t}//while");
            writer.write("\t} catch (XmlPullParserException e) {\n");
            writer.write("\t} catch (IOException e) {");
            writer.write("\t}");

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    /**
     * create a table of param classes that need to be genarated.
     * take care of
     *   1) one param is used in more than one time. we want to write only one param class
     *   2) param may used as input as well as output we genarate one class that can do the both
     * @return Hashtable of parms need to be created
     */
    /*  public Hashtable getParamsToGenarated() {
    		Hashtable bag = new Hashtable(35);
    		for (int i = 0; i < this.returnParams.length; i++) {
    			addParamToList(bag, AbstractParmGenarator.RETURN_PARM, returnParams[i]);
    		}
    		for (int i = 0; i < this.methods.length; i++) {
    			for (int j = 0; j < params[i].length; j++) {
    				//TODO remove
    				System.out.println(params[i][j]);
    				addParamToList(bag, AbstractParmGenarator.INPUT_PARM, params[i][j]);
    			}
    		}
    		return bag;
    	}*/

    /**
     * conveniance method. use add aparam to list check conditions.
     * @param bag
     * @param behaviour
     * @param param
     */
    /*   private void addParamToList(Hashtable bag, int behaviour, String param) {
    		if (!bag.containsKey(param))
    			bag.put(param, new Integer(behaviour));
    		else {
    			int bvalue = ((Integer) bag.get(param)).intValue();
    			if (bvalue != AbstractParmGenarator.COMMAN_PARM && bvalue != behaviour) {
    				bag.remove(param);
    				bag.put(param, new Integer(AbstractParmGenarator.COMMAN_PARM));
    			}
    		}
    	}*/
    /**
     * get the name of the output file
     * @return
     */
    public File getJavaFilePath() {
        String dirpath;
        String targetOutputLocation =
            this.wscontext.getWrapInfo().getTargetOutputLocation();
        if (targetOutputLocation.endsWith("/"))
            targetOutputLocation =
                targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
        if (targetOutputLocation.equals(""))
            dirpath = targetOutputLocation;
        else
            dirpath =
                targetOutputLocation
                    + "/"
                    + WrapperUtils
                        .getPackegeName4QualifiedName(
                            this.wscontext.getSerInfo().getQualifiedServiceName())
                        .replace('.', '/');
        new File(dirpath).mkdirs();
        return new File(dirpath + "/" + servicename + ".java");
    }
}
