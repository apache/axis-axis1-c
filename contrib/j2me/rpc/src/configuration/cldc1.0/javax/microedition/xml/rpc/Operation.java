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

package javax.microedition.xml.rpc;

import javax.microedition.xml.rpc.Element;
import javax.microedition.xml.rpc.FaultDetailHandler;
import javax.xml.namespace.QName;
import javax.xml.rpc.JAXRPCException;

import org.apache.axis.j2me.rpc.Cldc10Operation;

/**
 * The javax.microedition.xml.rpc.Operation class corresponds to a
 * wsdl:operation defined for a target service endpoint.
 * 
 * @author Ias (iasandcb@tmax.co.kr)
 *  
 */
public class Operation {
	/** Standard property for SOAPAction. Indicates the SOAPAction URI. */
	public static final java.lang.String SOAPACTION_URI_PROPERTY =
		"javax.xml.rpc.soap.http.soapaction.uri";

	protected Operation() {

	}
	/**
	 * Creates an Operation corresponding to the operation that is being
	 * performed.
	 * 
	 * @param name -
	 *            the QName of the operation to be invoked.
	 * @param input -
	 *            the Element describing the input parameter to this operation.
	 *            NULL indicates that the operation with zero input message
	 *            parts is to be executed.
	 * @param output -
	 *            the Element describing the return result to this operation.
	 *            NULL indicates there is no return value.
	 * @return a new Operation with the given input and output Type
	 *         characteristics
	 */
	public static Operation newInstance(
		QName name,
		Element input,
		Element output) {
		return newInstance(name, input, output, null);
	}

	/**
	 * Creates an Operation corresponding to the operation that is being
	 * performed. The faultDetailHandler parameter is passed to the runtime and
	 * used to map custom SOAP faults.
	 * 
	 * @param name -
	 *            the QName of the operation to be invoked.
	 * @param input -
	 *            the Element describing the input parameter to this operation.
	 *            NULL indicates that the operation with zero input message
	 *            parts is to be executed.
	 * @param output -
	 *            the Element describing the return result to this operation.
	 *            NULL indicates there is no return value.
	 * @param faultDetailHandler -
	 *            the FaultDetailHandler to be called to handle custom faults
	 *            thrown by this Operation.
	 * @return a new Operation with the given input and output Type
	 *         characteristics
	 */

	public static Operation newInstance(
		QName name,
		Element input,
		Element output,
		FaultDetailHandler faultDetailHandler) {
		String configuration = System.getProperty("microedition.configuration");
		return new Cldc10Operation(name, input, output, faultDetailHandler);
	}

	/**
	 * Sets the property name to the value, value.
	 * 
	 * @param name -
	 *            the name of the property to be set
	 * @param value -
	 *            the value the property is to be set
	 * @throws java.lang.IllegalArgumentException -
	 *             if the property, name, is not recognized by the runtime.
	 *  
	 */
	public void setProperty(String name, String value)
		throws java.lang.IllegalArgumentException {
	}

	/**
	 * Invokes the wsdl:operation defined by this Operation and returns the
	 * result. The input parameters and return value are encoded such that
	 * primitive types are mapped to the equivalent object wrapper, for
	 * example, int is mapped to Integer, byte to Byte. arrays are an Object
	 * containing the array elements. complex types are represented by an array
	 * of objects mapped according to the above rules. Any additional elements,
	 * beyond those described by the description passed to
	 * Operation.newInstance, are ignored.
	 * 
	 * @param inParams -
	 *            an Object representing the input parameter value(s) to this
	 *            operation.
	 * @return a Object representing the output value(s) for this operation.
	 *         Can be null if this operation returns no value.
	 * @throws JAXRPCException-
	 *             if the runtime detects a type mismatch in input parameters
	 *             or return value. if an error occurs while excuting the
	 *             operation. Any exception corresponding to the error will be
	 *             attached, as the cause, to the JAXRPCException and can be
	 *             retrieved via the method getCause.
	 */
	public Object invoke(Object inParams) throws JAXRPCException {
		return null;
	}

}
