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
 * This calss represent the Custom Complex type in the service.
 * This Class is the  representation of the WSDL Schema type. The class name is given in the
 * context of the xml QName. It is up to the user to make sense of the QName* 
 * 
 * @author Srianth Perera (hemapani@opensource.lk)
 */
package org.apache.axis.wsdl.wsdl2ws.info;

import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.cpp.CPPUtils;

public class Type {
    /* max no of attribs expected in a type */
    private static final int MAXIMUM_NO_ATTRIBS = 101;
    private QName name;

    /* This can be null */
    private String languageSpecificName;
    /* attribute names and the type of the attributes */
    private Hashtable types;
    /* has the attributes are specified with order <sequence> in the schema */
    private boolean hasOrder;
    /*if order presents the order is set in the vector */
    private Vector attribOrder;
    /* weather the type is Array */
    private boolean isArray;
    
    private String language;

    public Type(QName name, String languageSpecificName, boolean hasOrder,String language) {
        this.languageSpecificName = languageSpecificName;
        this.hasOrder = hasOrder;
        this.name = name;
        types = new Hashtable();
        if(language == null)
			this.language = WrapperConstants.LANGUAGE_JAVA;
        else
        	this.language = language;
        	
        // if the language specific name does not specified try weather is it a simple type  	 
        if(languageSpecificName == null){
        	if(WrapperConstants.LANGUAGE_CPP.equalsIgnoreCase(this.language))
				this.languageSpecificName = CPPUtils.getclass4qname(name);
			else
				this.languageSpecificName = TypeMap.getBasicTypeClass4qname(name);
			 
					
        }
        
        //if it is not a simple type genarate the name using usual QName -> language specific name mapping
        if(this.languageSpecificName == null)
            	this.languageSpecificName = qname2LSN();
        else{
        	//remove any funny Charactors
			this.languageSpecificName.replaceAll("/","_");  
			this.languageSpecificName.replaceAll(":","_");   
			//give it A GOOD java look :)
			this.languageSpecificName = WrapperUtils.firstCharacterToLowercase(this.languageSpecificName);
			
        }    
       	this.attribOrder = new Vector();
    }

    /**
     * @return QName
     */
    public QName getName() {
        return name;
    }

    /**
     * Sets the name.
     * @param name The name to set
     */
    public void setName(QName name) {
        this.name = name;
    }

    public Enumeration getAttribNames() {
        return this.types.keys();
    }

/*    public void setTypeNameForAttribName(String attribName, String typeName) {
        if (hasOrder)
            this.attribOrder.add(typeName);
        this.types.put(attribName, typeName);
    }*/

/**
 * The Type take the attributes name to lowercase when add, If there is two names like "Name" and "name"
 * they will convert to "name"  Is that acceptable ....  
 */
    public void setTypeNameForAttribName(String attribName, QName typeName) {
		attribName = TypeMap.resoleveWSDL2LanguageNameClashes(attribName,this.language);
        if (hasOrder)
            this.attribOrder.add(attribName);
        this.types.put(attribName, typeName);
    }

    public void setAttribOrder(Vector order) {
        this.attribOrder = order;
    }



    public QName getTypNameForAttribName(String attribName) {
        return (QName) this.types.get(attribName);
    }

    public boolean hasOrder() {
        return this.hasOrder;
    }

    public String getLanguageSpecificName() {
        return languageSpecificName;
    }

    public void setLanguageSpecificName(String languageSpecificName) {
        this.languageSpecificName = languageSpecificName;
    }
	/**
	 *  This mrthod define the standread conversion from qname to language spesific name
	 *  @return language specific name 
	 */ 
    protected String qname2LSN(){
       String nsuri = this.name.getNamespaceURI();
       if(nsuri == null) return  this.name.getLocalPart();
 	
	   if(language.equalsIgnoreCase(WrapperConstants.LANGUAGE_CPP)){
	   	 /* if it is CPP the namespace is neglected fr time been */
		 return this.name.getLocalPart(); 
	   }else if (language.equalsIgnoreCase(WrapperConstants.LANGUAGE_C)){
		 return this.name.getLocalPart();
	   }else			   
         return WrapperUtils.firstCharacterToLowercase(WrapperUtils.nsURI2packageName(nsuri)) +"."+ WrapperUtils.capitalizeFirstCaractor(this.name.getLocalPart());
    }
	/**
	 * @return
	 */
	public boolean isArray() {
		return isArray;
	}

	/**
	 * @param b
	 */
	public void setArray(boolean b) {
		isArray = b;
	}

}
