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

package org.apache.axismora.handlers.testBodyAcsess;
import javax.xml.namespace.QName;
import javax.xml.rpc.ParameterMode;

import org.apache.axis.client.Call;
import org.apache.axis.client.Service;
import org.apache.axis.encoding.XMLType;
import org.apache.axis.message.SOAPHeaderElement;

public class CalcClient {
	   public static void main(String [] args) throws Exception {
           String port ="4444";                             //port the TCP mon listens
            String SOAPAction ="CalculatorB";	   	//service name
	   	
		   String endpoint = "http://127.0.0.1:" +  port + "/service/servlet/AxisServlet";
            //String endpoint = "http://127.0.0.1:" +  port + "/axis/services/Calculator";

		  QName method =new QName("someuri","add");
           
           String value1 = "9";
           String value2 ="2";
     
		   Integer i1 = new Integer(value1);
		   Integer i2 = new Integer(value2);

		   Service  service = new Service();
		   Call     call    = (Call) service.createCall();

		   call.setTargetEndpointAddress( new java.net.URL(endpoint) );
		   call.setSOAPActionURI(SOAPAction);
		   call.setOperationName(method );
		   call.addParameter( "op1", XMLType.XSD_INT, ParameterMode.IN );
		   call.addParameter( "op2", XMLType.XSD_INT, ParameterMode.IN );
		   call.setReturnType( XMLType.XSD_INT );

           SOAPHeaderElement header = new SOAPHeaderElement("opensource.lk","acsessbody");
           header.setObjectValue("<myns:add xmlns:myns=\"someuri\"><op1>9</op1><op2>2</op2></myns:add>");
		   header.setActor("copyHeaderToBody");
           call.addHeader(header);

		   long st = System.currentTimeMillis();
		   Integer ret = (Integer) call.invoke( new Object [] { i1, i2 });
		   long end = System.currentTimeMillis();
           ret = (Integer) call.invoke( new Object [] { i1, i2 });

		   System.out.println("Got result : " + ret);
		   System.out.println("It takes "+(end-st)+" miliseconds");
	   }
	}

