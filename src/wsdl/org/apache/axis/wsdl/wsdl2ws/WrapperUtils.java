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
 * Utility Classes
 * @author Srinath Perera(hemapani@openource.lk)
 */
package org.apache.axis.wsdl.wsdl2ws;

import java.util.Enumeration;
import java.util.Stack;
import java.util.StringTokenizer;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.Constants;
import org.apache.axis.wsdl.wsdl2ws.cpp.CPPUtils;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.TypeMap;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class WrapperUtils {
	private static int nscount = 0;
	/**
	 * translation fullyqualifiedname -> packagename
	 */
    public static String getPackegeName4QualifiedName(String fullyQualifiedName) {
        int index = fullyQualifiedName.indexOf('.');
        int lastIndex = 0;
        while (index != -1) {
            lastIndex = index;
            index = fullyQualifiedName.indexOf('.', lastIndex + 1);
        }
        if (lastIndex == 0) return fullyQualifiedName;

        return fullyQualifiedName.substring(0, lastIndex);

    }

    /**
     * take care of the conversion from basic type name to parameter names. e.g. int -> Int
     * the param will not intParam but IntParm !!!
     * @param packagename
     * @param classname
     * @return fully quallified name for the param class.   
     */

    /**
     * extract the parameter name from the fully qualified name
     * @param fullyQualifiedName
     * @return only the class name 
     */
    public static String getClassNameFromFullyQualifiedName(String fullyQualifiedName) {
        int index = fullyQualifiedName.indexOf('.');
        int lastIndex = 0;
        while (index != -1) {
            lastIndex = index;
            index = fullyQualifiedName.indexOf('.', lastIndex + 1);
        }
        if (lastIndex == 0) return fullyQualifiedName;

        return fullyQualifiedName.substring(lastIndex + 1);
    }

	/**
	 *  get classpart of the class and if name happen to be a Simple type return 
	 *  the Wrapper Class name(service.0 wrapper class name) eg int -> Int ect
	 *  
	 */
    public static String getWrapperClassName4QualifiedName(String fullyQualifiedName) {
        String classname = getClassNameFromFullyQualifiedName(fullyQualifiedName);
        String paramclass;
        if (classname.equals("boolean")) {
            paramclass = "Boolean";
        } else if (classname.equals("byte")) {
            paramclass = "Byte";
        } else if (classname.equals("char")) {
            paramclass = "Char";
        } else if (classname.equals("short")) {
            paramclass = "Short";
        } else if (classname.equals("int")) {
            paramclass = "Int";
        } else if (classname.equals("long")) {
            paramclass = "Long";
        } else if (classname.equals("float")) {
            paramclass = "Float";
        } else if (classname.equals("double")) {
            paramclass = "Double";
        } else
            paramclass = classname;
        return paramclass;
    }

	/**
	 * Capitalize the first Character of a given String. 
	 * @param value String 
	 * @return changed String 
	 */
    public static String capitalizeFirstCaractor(String value) {
        char[] chars = value.toCharArray();
        chars[0] = Character.toUpperCase(value.charAt(0));
        return new String(chars);
    }
	//TODO does anybody using this ... else remove 
    public static String getWrapperName4FullyQualifiedName(String fullyQualifiedName) {
        //if simple type capitalize firstcharactor and add param
        if (TypeMap.isSimpleType(fullyQualifiedName))
            return WrapperConstants.DEFAULT_SIMPLETYPE_PACKAGE + capitalizeFirstCaractor(getClassNameFromFullyQualifiedName(fullyQualifiedName)) + Constants.PARAM_NAME_APPENDER;
        else
            return fullyQualifiedName;
    }
	/* This return the String of type xsi:type ="typename"*/
	public static String getParamTypeString(QName name){
		nscount++; 
		return " xsi:type=\\\"ns"+nscount+":"+name.getLocalPart()+ "\\\"  xmlns:ns"+nscount+" = \\\""+name.getNamespaceURI()+"\\\"";
	}
	
	public static String firstCharacterToLowercase(String value){
		char[] chars = value.toCharArray();
		chars[0] = Character.toLowerCase(value.charAt(0));
		return new String(chars);
	}
	public static String nsURI2packageName(String nsuri){
		int index;
		
		//gard agien if nsuri is urn | http and nothing return		
		if(("urn".equals(nsuri) || "http".equals(nsuri)))
			return nsuri;
		
		StringTokenizer tokenizer = new StringTokenizer(nsuri,":/.",false);
		String token;
		Stack stack = new Stack();
		
		//first ine may be urn: or http: remove it
		if(tokenizer.hasMoreTokens()){
			token = tokenizer.nextToken();
			if(!("urn".equals(token) || "http".equals(token)))
				stack.push(token);
		}		
		
		while(tokenizer.hasMoreTokens()){
			token = tokenizer.nextToken();
			if(!(token == null || "".equals(token)))
				stack.push(token);
		} 		
		
		// create the String from the stack
		StringBuffer buff = new StringBuffer(150);
		if(!stack.isEmpty())
			buff.append((String)stack.pop());
		while(!stack.isEmpty()){
			buff.append('.');
			buff.append((String)stack.pop());

		}
		
		String changednsuri = buff.toString();
		//remove any unexpected charactors		
		changednsuri = changednsuri.replaceAll("[^(a-zA-z0-9|.|_)]","_");
    	return changednsuri;
	}
	
	public static String getClassNameFromParamInfoConsideringArrays(ParameterInfo param,WebServiceContext wscontext)throws WrapperFault{
		Type type = wscontext.getTypemap().getType(param.getSchemaName());
		if(type!= null && type.isArray()){
			Enumeration e = type.getAttribNames();
			if(e.hasMoreElements()){
				QName qname = type.getTypNameForAttribName((String)e.nextElement());
				Type t  = wscontext.getTypemap().getType(qname);
				String name;    
				   
				if(t != null)
						name =t.getLanguageSpecificName()+"[]";
				else{
					//the type should be inbuild simpletype
					if(WrapperConstants.LANGUAGE_JAVA.equalsIgnoreCase(wscontext.getWrapInfo().getWrapperLanguage()))
						name = TypeMap.getBasicTypeClass4qname(qname)+"[]";
					else
						name = CPPUtils.getclass4qname(qname)+"[]";
				if(name == null) throw new WrapperFault("if not inbuild or not in type map what is this type "+qname);
				} 
				return name;
			}else
				throw new WrapperFault("enumeration no type is given ?????");	   
		}else
		return param.getLangName();		
	}
}

