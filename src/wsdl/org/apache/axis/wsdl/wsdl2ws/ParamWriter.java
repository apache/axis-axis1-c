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


package org.apache.axis.wsdl.wsdl2ws;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.info.ElementInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
import org.apache.axis.wsdl.wsdl2ws.info.AttributeInfo;

public abstract class ParamWriter extends BasicFileWriter{
    protected static final int INPUT_PARM = 0;
    protected static final int RETURN_PARM = 1;
    protected static final int COMMAN_PARM = 2;
	
	/* no of parameters treated as attributes: ie first attributeParamCount of
	 * attribs will be treated as attributes
	 */
	protected int attributeParamCount = 0;
	/* array of parameter types and parameter names of the this param */
    protected AttributeInfo[] attribs;
    
    protected WebServiceContext wscontext;
    
    /* Type of this param */
    protected Type type;

    public ParamWriter(WebServiceContext wscontext,Type type) throws WrapperFault {
            super(WrapperUtils.getLanguageTypeName4Type(type));
            this.wscontext = wscontext;
            this.type = type;
            populateAttribList(wscontext.getSerInfo().getQualifiedServiceName());
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
	public AttributeInfo[] getAttribList(String Qualifiedname) throws WrapperFault {
		return this.attribs;
	}   
 	/* genarate the arrtibs array */
 	private void populateAttribList(String Qualifiedname) throws WrapperFault {
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
		int intAttrFieldSz = attribfeilds.size();
		attributeParamCount = intAttrFieldSz;
		int intEleFieldSz = elementfeilds.size();
		this.attribs = new AttributeInfo[intAttrFieldSz+intEleFieldSz];
		for (int i = 0 ; i < intAttrFieldSz; i++) {
			this.attribs[i] = new AttributeInfo();
			this.attribs[i].setParamName((String)attribfeilds.get(i));
			Type attribType = type.getTypForAttribName(this.attribs[i].getParamName());            
			if(CUtils.isSimpleType(attribType.getName()))
				this.attribs[i].setTypeName(CUtils.getclass4qname(attribType.getName()));
			else{
				this.attribs[i].setTypeName(attribType.getLanguageSpecificName());
				this.attribs[i].setSimpleType(false);
			}
			this.attribs[i].setType(attribType);
			this.attribs[i].setAttribute(true);
			//TODO : how to find whether this attribute is optional or not ?
		}

		for (int i = intAttrFieldSz ; i < intAttrFieldSz+intEleFieldSz; i++) {
			this.attribs[i] = new AttributeInfo();
			this.attribs[i].setParamName((String) elementfeilds.get(i-attributeParamCount));   
			ElementInfo elem = type.getElementForElementName(this.attribs[i].getParamName());
			Type elementType = elem.getType();
			if(CUtils.isSimpleType(elementType.getName()))
				this.attribs[i].setTypeName(CUtils.getclass4qname(elementType.getName()));
			else{
				this.attribs[i].setTypeName(elementType.getLanguageSpecificName());
				this.attribs[i].setSimpleType(false);
			}
			this.attribs[i].setType(elementType);
		   	if(elementType.isArray()){ //soap encoding arrays.
				Type arrayType = WrapperUtils.getArrayType(elementType); //get contained type
				this.attribs[i].setArray(true);
				if(CUtils.isSimpleType(arrayType.getName()))
					this.attribs[i].setTypeName(CUtils.getclass4qname(arrayType.getName()));
				else{
					this.attribs[i].setTypeName(arrayType.getLanguageSpecificName());
					this.attribs[i].setSimpleType(false);
				}
				this.attribs[i].setType(arrayType); //set contained type as type
		   }else if (elem.getMaxOccurs() > 1){
		   		//arrays but the same type as was set above
				this.attribs[i].setArray(true);
		   }
		   if (elem.getMinOccurs() == 0) this.attribs[i].setOptional(true);
		}	
 	}

 	protected String getCorrectParmNameConsideringArraysAndComplexTypes(AttributeInfo attrib)throws WrapperFault{
		if (attrib.isArray()){
			return attrib.getTypeName()+"_Array";
		}
		else if (!attrib.isSimpleType()){
			return attrib.getTypeName()+" *";	
		}else{
			if (attrib.isAttribute() && attrib.isOptional()){ //variables corresponding to optional attributes are pointer types
				return attrib.getTypeName()+" *";	
			}
			else
				return attrib.getTypeName();
		}
	}

}
