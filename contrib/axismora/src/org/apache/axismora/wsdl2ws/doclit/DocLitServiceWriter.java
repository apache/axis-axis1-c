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
