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

package org.apache.axismora.wsdl2ws.testing;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Vector;

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
public class RPCTestCaseWriter extends JavaClassWriter {
    private WebServiceContext wscontext;
    private ArrayList methods;
    private QName soap;

    /**
     * @param packagename
     * @param classname
     * @throws WrapperFault
     */
    public RPCTestCaseWriter(WebServiceContext wscontext) throws WrapperFault {
        super(wscontext.getSerInfo().getQualifiedServiceName()+"Test",wscontext.getWrapInfo().getTargetOutputLocation());
        this.wscontext = wscontext;
        this.methods = wscontext.getSerInfo().getMethods();
        this.soap = new QName(wscontext.getSerInfo().getServicename());
    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeAttributes()
     */
    protected void writeAttributes() throws WrapperFault {
        try {
            writer.write("\n\tprivate java.lang.String enduri = org.apache.axismora.wsdl2ws.testing.TestUtils.ENDPOINT_URI;");
			writer.write("\n\tprivate "+wscontext.getSerInfo().getQualifiedServiceName()+" stub;\n");
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
            
           // writer.write("\n\tpublic " + classname + "(java.lang.String enduri){");
            //writer.write("\t\t\tthis.enduri = enduri;\n");
			///writer.write("\t\tthis();\n");
			//writer.write("\t}\n");

			writer.write("\n\tpublic " + classname + "()" + "{\n");
			writer.write("\n\t\tstub = (new HeavyTestLocator(enduri)).getStub();\n");
			writer.write("\t}\n");
        } catch (Exception e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }

    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeMethods()
     */
    protected void writeMethods() throws WrapperFault {
    	int var = 0;
        MethodInfo minfo;
        QName paramQName;
        Type paramType;
        Object obj;
        try {
            for (int i = 0; i < methods.size(); i++) {
                minfo = (MethodInfo) this.methods.get(i);
                

                ParameterInfo returnType = minfo.getReturnType();
                
                String outparam = null;
                
                
				Type t = null;
				if(returnType == null)        
					outparam = "void";
				else{	
					t = returnType.getType();
					outparam = t.getLanguageSpecificName();
			
					if(t.isArray()){
						outparam = WrapperUtils.getArrayType(t).getLanguageSpecificName()+"[]";
					}
				}
                
                
               
				writer.write("\n\tpublic void test"+minfo.getMethodname() + "()throws Exception{\n");

                //write parameter names 
                Vector params = new Vector(minfo.getParameterTypes());
                
				for (int j = 0; j <params.size(); j++){ 
					ParameterInfo parm = (ParameterInfo)params.get(0);
					t = parm.getType();
										
					if(t.isArray()){
						String arrayType = WrapperUtils.getArrayType(t).getLanguageSpecificName()+"[]";
						String arrstr = "";
						
						int length = TestUtils.getRandomInt(20);
						for(int l = 0;l<length;l++){
							String javaType = WrapperUtils.getArrayType(t).getLanguageSpecificName();
							String wrappername = TypeMap.getWrapperCalssNameForJavaClass(javaType);
							
							if(javaType.equals(wrappername)){
								writer.write("\t\t"+javaType + " aparam"+var+" = new "+ javaType + "();\n");
								writer.write("\t\taparam"+ var +".init();\n");
							}else{
								writer.write("\t\t"+wrappername + " atparam"+ var +" = new "+ wrappername + "();\n");
								writer.write("\t\tatparam"+ var +".init();");
								writer.write("\t\t"+javaType + " aparam"+ var +" = atparam.getParam();\n");
							}
							
							if(l == 0)
								arrstr = "aparam"+var;
							else
								arrstr = arrstr +",aparam"+var;	
							var++;	
						}
						
						writer.write("\t\t"+arrayType +"param"+j+" = new "+arrayType+"{");
						writer.write(arrstr);
						writer.write("};\n");
						
					}else{
						String javaType = t.getLanguageSpecificName();
						String wrappername = TypeMap.getWrapperCalssNameForJavaClass(javaType);
						if(javaType.equals(wrappername)){
							writer.write("\t\t"+javaType + " param"+j+" = new "+ javaType + "()\n");
							writer.write("\t\tparam"+j+".init();\n");
						}else{
							writer.write(wrappername + " tparam"+j+" = new "+ wrappername + "();\n");
							writer.write("\t\ttparam"+j+".init();");
							writer.write("\t\t"+javaType + " param"+j+" = tparam.getParam();\n");
						}	
					}
				}
				writer.write("\t\t");
                if(!"void".equals(outparam))
					writer.write(outparam + "returnVal = ");
				writer.write("stub."+minfo.getMethodname() +"(");
                if(params.size()>0){
					writer.write("param0");
                }
				for (int j = 1; j<params.size(); j++) 
					writer.write(",param"+j);
				writer.write(");\n");
				writer.write("\tSystem.out.println(\"test"+minfo.getMethodname()+" passes\");");	
				writer.write("\t}\n");
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }

    }

    /* (non-Javadoc)
    * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#getExtendsPart()
    */
    protected String getExtendsPart() {
    	return " extends junit.framework.TestCase";
    }


    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeClassComment()
     */
    protected void writeClassComment() throws WrapperFault {
        try {
            writer.write("/* This class is automatically generated by \n");
            writer.write(" * WSDL2Ws generator. This genarate a testcase and the \n");
			writer.write(" * parameters are initialized with random values. \n");
            writer.write(" */\n\n");
        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }
}
