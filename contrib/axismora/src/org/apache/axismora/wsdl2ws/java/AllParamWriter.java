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

import java.util.Iterator;

import org.apache.axismora.wsdl2ws.SourceWriter;
import org.apache.axismora.wsdl2ws.WrapperConstants;
import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.TypeMap;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

/**
 * Parameter genarator.. genarate all necessary param classes
 * @author hemapani
 */
public class AllParamWriter implements SourceWriter {
    private WebServiceContext wscontext;

    public AllParamWriter(WebServiceContext wscontext) {
        this.wscontext = wscontext;
    }

    /**
     * genarate all the wrappets for custom complex types.
     * @see org.apache.axismora.wsdl2ws.SourceWriter#writeSource()
     */
    public void writeSource() throws WrapperFault {
        Iterator enu = wscontext.getTypemap().getTypes().iterator();
        String generator = wscontext.getWrapInfo().getImplStyle();
        Type type;
        
        while (enu.hasNext()) {
            try {
                type = (Type) enu.next();
                if(TypeMap.isSimpleType(type.getName()))
                	break;
                
                if (wscontext
                    .getWrapInfo()
                    .getImplStyle()
                    .equals(WrapperConstants.IMPL_STYLE_STRUCT)) {
                    if(type.getEnumerationdata() != null){
                    
                    }else if (type.isArray()) {
  //                      (new ArrayParamWriter(wscontext, type)).writeSource();
  						TypeMap.regestorArrayTypeToCreate(type);
                    } else {
                        System.out.println("struct writer called ......");
                        (new BeanParamWriter(wscontext, type)).writeSource();
                    }
                }
            } catch (Exception e) {
                System.out.println(
                    "Error occured yet we continue to genarate other classes ... you should check the error");
                e.printStackTrace();
            }
        }
        
        Iterator arrayTypes = TypeMap.getUnregisterdArrayTypes();
        while(arrayTypes.hasNext()){
			System.out.println("Array writer called ......");
			(new ArrayParamWriter(wscontext, (Type)arrayTypes.next())).writeSource();
        }
    }
}
