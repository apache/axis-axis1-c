/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
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
 *        Apache Software Foundation (http://www.apache.org/)."
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
 
/**
 * This class has the basic logic of the genarating Param classes (Type wrappers).
 * The responsibility of writing serializing and desirializing code is given to the
 * concreate subclasses.
 * @author JayaKumaran
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 */


package org.apache.axis.wsdl.wsdl2ws.cpp.literal;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.TypeMap;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public abstract class ParamWriter extends BasicFileWriter{
    protected static final int INPUT_PARM = 0;
    protected static final int RETURN_PARM = 1;
    protected static final int COMMAN_PARM = 2;

	/* array of parameter types and parameter names of the this param */
    protected String[][] attribs;
    
    protected WebServiceContext wscontext;
    
    /* Type of this param */
    protected Type type;

    public ParamWriter(WebServiceContext wscontext,Type type) throws WrapperFault {
            super(WrapperUtils.getWrapperClassName4QualifiedName(type.getLanguageSpecificName()));
            this.wscontext = wscontext;
            this.type = type;
            this.attribs = this.getAttribList(wscontext.getSerInfo().getQualifiedServiceName());
    }
 
    protected void writeClassComment() throws WrapperFault {
        try{
			writer.write("/*\n");
			writer.write(" *This file is automatically generated by the Axis C++ Wrapper Class Generator\n");
			writer.write(" *Web service wrapper class's implementation generated by Axis WCG\n");
			writer.write(" *Parameters and wrapper methos to manipulate "+classname+"\n");
			writer.write(" */\n\n");
      } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }
   
 	/* genarate the arrtibs array */
	public String[][] getAttribList(String Qualifiedname) throws WrapperFault {
		String[][] attribs;
		ArrayList attribfeilds = new ArrayList();
		ArrayList elementfeilds = new ArrayList();

		Iterator names = type.getAttributeNames();
		while (names.hasNext()){
			attribfeilds.add(names.next());
		}
        
		names = type.getElementnames();
				while (names.hasNext()){
					elementfeilds.add(names.next());
		}
        
        
		//get all the fields
		int intAttrFieldSz = attribfeilds.size();
		int intEleFieldSz = elementfeilds.size();
		attribs = new String[intAttrFieldSz+intEleFieldSz][];

		for (int i = 0 ; i < intAttrFieldSz; i++) {
			//[variablename,typename,typeQNameURI,typeQNamelocalpart,attributeTypeURI,attributeTypeLocalpart]
			attribs[i] = new String[6];
			attribs[i][0] = ((String) attribfeilds.get(i));
   
			Type attribType = type.getTypForAttribName(attribs[i][0]);
            
			if(CPPUtils.isSimpleType(attribType.getName()))
				attribs[i][1] = CPPUtils.getclass4qname(attribType.getName());
			else
				attribs[i][1] = attribType.getLanguageSpecificName();

			attribs[i][2] = attribType.getName().getNamespaceURI();
			attribs[i][3] = attribType.getName().getLocalPart();

			attribs[i][4] = null;
			attribs[i][5] = null;
		}

		for (int i = intAttrFieldSz ; i < intAttrFieldSz+intEleFieldSz; i++) {
			attribs[i] = new String[6];
			attribs[i][0] = ((String) elementfeilds.get(i));
   
			Type elementType = type.getElementForElementName(attribs[i][0]).getType();
            
			if(CPPUtils.isSimpleType(elementType.getName()))
				attribs[i][1] = CPPUtils.getclass4qname(elementType.getName());
			else
				attribs[i][1] = elementType.getLanguageSpecificName();

		   attribs[i][2] = elementType.getName().getNamespaceURI();
		   attribs[i][3] = elementType.getName().getLocalPart();
		   if(elementType.isArray()){
				Type arrayType = WrapperUtils.getArrayType(elementType);
				attribs[i][4] = arrayType.getName().getNamespaceURI();
				attribs[i][5] = arrayType.getName().getLocalPart();
		   }else{
				attribs[i][4] = null;
				attribs[i][5] = null;
		   }
		}

        
		return attribs;
	}
    
 	protected String getCorrectParmNameConsideringArraysAndComplexTypes(QName name,String classname)throws WrapperFault{
		//System.out.println(name);
		Type t = wscontext.getTypemap().getType(name);
		if(!TypeMap.isSimpleType(name)){ //array or complex types
			if (t.isArray()){
				return t.getLanguageSpecificName();
			}
			else{
				return classname+"*"; //All complex types will be pointers	
			}
		}else
			return classname;
	}

}
