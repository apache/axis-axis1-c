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

package org.apache.axismora.soap;
/**
 * 
 * @author Dimuthu Leelarathe (muthulee@opensource.lk)
 */

public class XMLTextData {
    private int type;
    private String value;
    private String uri;
    private String localPart;
    private String attrType;
    //    private String attrName[];
    //    private String attrValue[];

    public XMLTextData(
        int type,
        String value,
        String uri,
        String localPart,
        String attrType) {
        this.type = type;
        this.value = value;
        this.uri = uri;
        this.localPart = localPart;
        this.attrType = attrType;
    }

    /*public XMLTextData(int type,String value,String uri,String localPart, String[] tempNames, String[] tempValues){
    	this.type=type;
    	this.value=value;
    	this.uri=uri;
    	this.localPart=localPart;
    	this.attrName = tempNames;
    	this.attrValue = tempValues;
    }*/

    /**
     * @return
     */
    public int getType() {
        return type;
    }

    /**
     * @return
     */
    public String getValue() {
        return value;
    }

    /**
     * @param string
     */
    public void setValue(String string) {
        value = string;
    }

    public void setType(int argType) {
        type = argType;
    }

    /**
     * @return
     */
    public String getLocalpart() {
        return localPart;
    }

    /**
     * @return
     */
    public String getUri() {
        return uri;
    }

    /**
     * @param string
     */
    public void setLocalpart(String string) {
        localPart = string;
    }

    /**
     * @param string
     */
    public void setUri(String string) {
        uri = string;
    }

    public String getAttrType() {
        return this.attrType;
    }
    /*
     * Usage of the below code was questioned
     * Hence we decided to comment it for time being
     * It is a tested mehtod .........
     * Just uncoment the above two arrays for this to perform
     *
     * */

    /*    public String getAttributeValue(String nameAtr){
        	String attrVal=null;
            if(this.attrName==null || nameAtr==null){
            	return null;
            }
            for(int i=0; i<this.attrName.length; i++){
                 if(nameAtr.equals((String)attrName[i])){
                       return this.attrValue[i];
                 }
            }
        	return attrVal;
        }
    */

}
