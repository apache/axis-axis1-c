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



package org.apache.axismora.wsdl2ws.doclit;

/**
 * @author Dimuthu Leelarathne. (muthulee@opensouce.lk)
 * Created on Oct 31, 2002
 */

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.MethodInfo;
import org.apache.axismora.wsdl2ws.info.ParameterInfo;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;
import org.apache.axismora.wsdl2ws.java.JavaClassWriter;

/**
 * Service Genarator (write the Webservice (WS class in our convention))
 * @author Srinath(hemapani@opensource.lk)
 */
public class DocLitServiceWriter extends JavaClassWriter {
	private ArrayList methods;
	private WebServiceContext wscontext;

	public DocLitServiceWriter(WebServiceContext wscontext) throws WrapperFault {
		super(
			WrapperUtils.getPackegeName4QualifiedName(
				wscontext.getSerInfo().getQualifiedServiceName()),
			WrapperUtils.getClassNameFromFullyQualifiedName(
				wscontext.getSerInfo().getQualifiedServiceName())
				+ "Impl");
		this.wscontext = wscontext;
		this.methods = wscontext.getSerInfo().getMethods();
	}

	protected void writeClassComment() throws WrapperFault {
		try {
			writer.write(
				"/**\n* This is the service class build with the information given\n");
			writer.write(
				" * by the wsdl file the user should fill the logic here \n */\n");
		} catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}

	protected void writeImportStatements() throws WrapperFault {
	}
	protected void writeAttributes() throws WrapperFault {
	}
	protected void writeConstructors() throws WrapperFault {
	}
	protected void writeMethods() throws WrapperFault {
		MethodInfo minfo;
		try {
			for (int i = 0; i < methods.size(); i++) {
				minfo = (MethodInfo) this.methods.get(i);
				writer.write("\tpublic ");
				if (minfo.getReturnType() == null
					|| minfo.getReturnType().getLangName() == null)
					writer.write("void ");
				else
					writer.write(
						WrapperUtils.getClassNameFromParamInfoConsideringArrays(
							minfo.getReturnType(),
							wscontext)
							+ " ");
				writer.write(minfo.getMethodname() + "(");

				//write parameter names 
				Iterator params = minfo.getParameterTypess().iterator();
				if (params.hasNext())
					writer.write(
						WrapperUtils.getClassNameFromParamInfoConsideringArrays(
							(ParameterInfo) params.next(),
							wscontext)
							+ " param"
							+ 0);

				for (int j = 1; params.hasNext(); j++) {
					writer.write(
						","
							+ WrapperUtils.getClassNameFromParamInfoConsideringArrays(
								(ParameterInfo) params.next(),
								wscontext)
							+ " param"
							+ j);
				}

				writer.write("){}\n");
			}
		} catch (Exception e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}

	protected File getJavaFilePath() {
		String targetOutputLocation =
			this.wscontext.getWrapInfo().getTargetOutputLocation();
		if (targetOutputLocation.endsWith("/"))
			targetOutputLocation =
				targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
		new File(
			targetOutputLocation
				+ "/"
				+ WrapperUtils
					.getPackegeName4QualifiedName(
						this.wscontext.getSerInfo().getQualifiedServiceName())
					.replace('.', '/'))
			.mkdirs();
		String fileName =
			targetOutputLocation
				+ "/"
				+ this.wscontext.getSerInfo().getQualifiedServiceName().replace('.', '/')
				+ "Impl.java";
		return new File(fileName);
	}
}
