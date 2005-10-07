/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 // (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/**
 * @author Srinath Perera(hemapani@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws.cpp;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.ElementInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ParmHeaderFileWriter extends ParamWriter {
	public ParmHeaderFileWriter(WebServiceContext wscontext, Type type)
			throws WrapperFault {
		super(wscontext, type);
	}

	public void writeSource() throws WrapperFault {
		try {
			this.writer = new BufferedWriter(new FileWriter(getFilePath(),
					false));
			writeClassComment();
			// if this headerfile not defined define it
			this.writer.write("#if !defined(__" + classname.toUpperCase() + "_"
					+ getFileType().toUpperCase() + "_H__INCLUDED_)\n");
			this.writer.write("#define __" + classname.toUpperCase() + "_"
					+ getFileType().toUpperCase() + "_H__INCLUDED_\n\n");
			writePreprocessorStatements();

			this.writer.write("class " + classname);
			if (this.type.isFault())
				this.writer.write(" : public SoapFaultException");
			this.writer.write("\n{\n");

			writeAttributes();
			writeGetSetMethods();
			writeConstructors();
			writeDestructors();
			this.writer.write("};\n\n");
			this.writer.write("#endif /* !defined(__" + classname.toUpperCase()
					+ "_" + getFileType().toUpperCase() + "_H__INCLUDED_)*/\n");
			writer.flush();
			writer.close();
			if (WSDL2Ws.verbose) {
				System.out.println(getFilePath().getAbsolutePath()
						+ " created.....");
			}
		} catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}

	protected void writeAttributes() throws WrapperFault {
		int anyCounter = 0;
		if (type.isArray())
			return;
		try {
			writer.write("public:\n");
			for (int i = 0; i < attribs.length; i++) {
				//chek if attrib name is same as class name and if so change
				if (classname.equals(attribs[i].getParamName())) {
					attribs[i].setParamName("m_" + attribs[i].getParamName());
				}
				// FJP Nillable vv
				if (isElementNillable(i)) {
					
					if(attribs[i].isAnyType()){
						anyCounter += 1;
						writer
						.write("\t"
								+ getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
								+ " *\t" + attribs[i].getParamName()
								+ Integer.toString(anyCounter)
								+ ";\n");
						
					}
						
					else{
					writer
							.write("\t"
									+ getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
									+ " *\t" + attribs[i].getParamName()
									+ ";\n");
					}
					
				} else {
					// FJP Nillable ^^
					
					if(attribs[i].isAnyType()){
						anyCounter += 1;
						writer
						.write("\t"
								+ getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
								+ " \t" + attribs[i].getParamName()
								+ Integer.toString(anyCounter)
								+ ";\n");
						
					}
						
					else{
					
					writer
							.write("\t"
									+ getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
									+ "\t" + attribs[i].getParamName() + ";\n");
					}
				}
			}
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}

	/**
	 * Dushshantha: This method writes getters and setters of the attributes.
	 */
	protected void writeGetSetMethods() throws WrapperFault {
		int anyCounter = 0; 
		if (type.isArray()) {
			return;
		}
		try {
			for (int i = 0; i < attribs.length; i++) {
				//              FJP Nillable vv
				if (i == 0) {
					writer.write("\n");
				}
				
				String methodName = attribs[i].getParamNameWithoutSymbols();
				
				if( methodName.endsWith( "_"))
                {
                    String localMethodName = methodName.substring( 0, methodName.length() - 1);
                    
                    if( localMethodName.equals( classname))
                    {
                        methodName = localMethodName; 
                    }
                }
				
				if (isElementNillable(i)) {
					if ( attribs[i].isAnyType()){
						anyCounter += 1;

						writer
							.write("\t"
									+ getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
									+ " * get"
									+ methodName
									+ Integer.toString(anyCounter)
									+ "();\n");

						writer
							.write("\t"
									+ "void set"
									+ methodName
									+ Integer.toString(anyCounter)
									+ "("
									+ getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
									+ " * pInValue);\n\n");
					}
					else {
						writer
						.write("\t"
								+ getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
								+ " * get"
								+ methodName
								+ "();\n");

					    writer
						.write("\t"
								+ "void set"
								+ methodName
								+ "("
								+ getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
								+ " * pInValue);\n\n");
						
					}
					
				} else {
					//                	 FJP Nillable ^^
					
					if ( attribs[i].isAnyType()){
						anyCounter += 1;
						writer
							.write("\t"
									+ getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
									+ " get"
									+ methodName
									+ Integer.toString(anyCounter)
									+ "();\n");

						writer
							.write("\t"
									+ "void set"
									+ methodName
									+ Integer.toString(anyCounter)
									+ "("
									+ getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
									+ " InValue);\n\n");
					}
					else {
					
					
					
					/**
					 * Dushshantha: Write setter
					 */

						writer
							.write("\t"
									+ getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
									+ " get"
									+ methodName
									+ "();\n");

					/**
					 * Dushshantha: Write getter
					 */

						writer
							.write("\t"
									+ "void set"
									+ methodName
									+ "("
									+ getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
									+ " InValue);\n\n");
					}
				}
			}
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}

	protected void writeConstructors() throws WrapperFault {
		try {
			writer.write("\t" + classname + "();\n");
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}

	protected void writeDestructors() throws WrapperFault {
		try {
			if (this.type.isFault())
				writer.write("\tvirtual ~" + classname + "() throw();\n");
			else
				writer.write("\tvirtual ~" + classname + "();\n");
			//damitha added virtual
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}

	protected void writeMethods() throws WrapperFault {
	}

	protected File getFilePath() throws WrapperFault {
		return this.getFilePath(false);
	}

	protected File getFilePath(boolean useServiceName) throws WrapperFault {
		String targetOutputLocation = this.wscontext.getWrapInfo()
				.getTargetOutputLocation();
		if (targetOutputLocation.endsWith("/")) {
			targetOutputLocation = targetOutputLocation.substring(0,
					targetOutputLocation.length() - 1);
		}
		new File(targetOutputLocation).mkdirs();

		String fileName = targetOutputLocation + "/" + classname
				+ CUtils.CPP_HEADER_SUFFIX;

		if (useServiceName) {
			fileName = targetOutputLocation + "/"
					+ this.wscontext.getSerInfo().getServicename() + "_"
					+ classname + CUtils.CPP_HEADER_SUFFIX;
		}

		return new File(fileName);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.BasicFileWriter#writePreprocssorStatements()
	 */
	protected void writePreprocessorStatements() throws WrapperFault {
		try {
			writer.write("#include <axis/AxisUserAPI.hpp>\n");
			if (this.type.isFault()) {
				writer.write("#include <axis/SoapFaultException.hpp>\n");
				writer.write("using namespace std;\n");
			}
			writer.write("AXIS_CPP_NAMESPACE_USE \n\n");
			HashSet typeSet = new HashSet();
			for (int i = 0; i < attribs.length; i++) {
				if ((attribs[i].isArray()) && (!attribs[i].isSimpleType())) {
					typeSet.add(attribs[i].getTypeName() + "_Array");
				}
				if (!(attribs[i].isSimpleType() || attribs[i].isAnyType())) {
					typeSet.add(attribs[i].getTypeName());
				}

			}
			Iterator itr = typeSet.iterator();
			while (itr.hasNext()) {
				writer.write("#include \"" + itr.next().toString()
						+ CUtils.CPP_HEADER_SUFFIX + "\"\n");
			}

			//Local name and the URI for the type
			writer.write("/*Local name and the URI for the type*/\n");
			writer.write("static const char* Axis_URI_" + classname + " = \""
					+ type.getName().getNamespaceURI() + "\";\n");
			writer.write("static const char* Axis_TypeName_" + classname
					+ " = \"" + type.getName().getLocalPart() + "\";\n\n");

			// Define class to avoid compilation issue (cycle in includes).
			typeSet = new HashSet();
			for (int i = 0; i < attribs.length; i++) {
				//if (!attribs[i].isArray() && !attribs[i].isSimpleType())
				if (!attribs[i].isArray() && !attribs[i].isSimpleType()
						&& !attribs[i].isAnyType()) {
					typeSet.add(attribs[i].getTypeName());
				}
			}
			itr = typeSet.iterator();
			while (itr.hasNext()) {
				writer.write("class " + itr.next().toString() + ";\n");
			}
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}

	protected String getFileType() {
		return "Param";
	}

	//	 FJP Nillable vv
	protected boolean isElementNillable(int index) {
		ElementInfo ei = type.getElementForElementName(attribs[index]
				.getParamName());
		boolean bNillable = false;

		if (ei != null
				&& !("xsd__string".equalsIgnoreCase(attribs[index]
						.getTypeName()))
				|| "xsd__anyURI".equalsIgnoreCase(attribs[index].getTypeName())
				|| "xsd__QName".equalsIgnoreCase(attribs[index].getTypeName())
				|| "xsd__NOTATION".equalsIgnoreCase(attribs[index]
						.getTypeName())) {
			bNillable = ei.getNillable();
		}

		return bNillable;
	}
	//	 FJP Nillable ^^
}