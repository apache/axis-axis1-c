
package org.apache.axismora.wsdl2ws.doclit;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import org.apache.axismora.Constants;
import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.MethodInfo;
import org.apache.axismora.wsdl2ws.info.ParameterInfo;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.TypeMap;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;
import org.apache.axismora.wsdl2ws.java.JavaClassWriter;
import org.apache.axismora.wsdl2ws.java.JavaUtils;
import org.apache.axismora.wsdl2ws.java.WrapWriter;


/**
 * @author Dimuthu Leelarathne. (muthulee@opensource.lk)
 * 
 * This class writes wrappers.
 * 
 */

public class DocLitWrapWriter extends JavaClassWriter {
 private ArrayList methods;

private WebServiceContext wscontext;

public DocLitWrapWriter(WebServiceContext wscontext) throws WrapperFault {
	super(
			  WrapperUtils.getPackegeName4QualifiedName(
				  wscontext.getSerInfo().getQualifiedServiceName()),
			  WrapperUtils.getClassNameFromFullyQualifiedName(
				  wscontext.getSerInfo().getQualifiedServiceName())
				  + Constants.WRAPPER_NAME_APPENDER);
		  this.wscontext = wscontext;
        
	methods = this.wscontext.getSerInfo().getMethods();
}



protected void writeClassComment() throws WrapperFault {
	try {
		writer.write(
			"/**\n * This Code is Genarated by the Wrapper Genarator. " +
			"\n * This Class is document\\literal Wrapper to invoke the Webservice methods\n*/\n");
	} catch (IOException e) {
		throw new WrapperFault(e);
	}
}


protected void writeConstructors() throws WrapperFault {
	   try {
		   writer.write(
			   "\tpublic "
				   + servicename
				   + "(){\n\t\t\tservice = new "
				   + wscontext.getSerInfo().getQualifiedServiceName()
				   + "Impl();\n\t}\n\n");
	   } catch (IOException e) {
		   throw new WrapperFault(e);
	   }
   }
   
protected String getExtendsPart() {
	   return " extends org.apache.axismora.handlers.BasicHandler";
   }


protected void writeImportStatements() throws WrapperFault {
		try {
			writer.write(
				"import org.apache.axis.AxisFault;\nimport org.apache.axis.message.SOAPFault;\n");
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}

protected void writeAttributes() throws WrapperFault {
		try {
			writer.write(
				"\tprivate "
					+ wscontext.getSerInfo().getQualifiedServiceName()
					+ "Impl service;\n\n");
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}
	
	
protected void writeMethods() throws WrapperFault {
 try {
	//write invoke method
	writer.write("/*\n\tThis method is called by the Wrapper. \n*/\n");
	writeInvoke();
	writer.write("\n");
	MethodInfo minfo;
	//write service wrapping methods
	for (int i = 0; i < methods.size(); i++) {
		minfo = (MethodInfo) methods.get(i);
			this.writeMethodInWrapper(
				minfo.getMethodname(),
				minfo.getParameterTypess(),
				minfo.getReturnType());
			writer.write("\n");
		}
	} catch (IOException e) {
		throw new WrapperFault(e);
	}
}

/**
 * write the invoke method
 * 
 * @throws IOException
 */
//Cannot extend from the super class because of setLiteral(true) line. 
//Check for possiblity after removing the two lines.
protected void writeInvoke() throws IOException{
	writer.write(
			  "\tpublic void invoke(org.apache.axismora.MessageContext msgdata){\n");
		  //msgdata.setSoapFault(new SOAPFault(new AxisFault()))
		  writer.write("\t\t try{\n");
		  writer.write(
			  "\t\t\tString methodToCall = msgdata.getMethodName().getLocalPart();\n");
          writer.write("\t\t\tmsgdata.setLitereal(true);\n");
       	  //if no methods in the service simply return
		  if (methods.size() == 0) {
			  writer.write("\t}\n");
			  return;
		  }
		  MethodInfo minfo = (MethodInfo) methods.get(0);
		  //if conditions (if parts)
		  writer.write(
			  "\t\t\tif(\"" + minfo.getMethodname() + "\".equals(methodToCall))\n");
		  writer.write("\t\t\t\tthis." + minfo.getMethodname() + "(msgdata);\n\t\t\n");
		  //(else if parts)
		  if (methods.size() > 1) {
			  for (int i = 1; i < methods.size(); i++) {
				  minfo = (MethodInfo) methods.get(i);
				  writer.write(
					  "\t\t\telse if(\""
						  + minfo.getMethodname()
						  + "\".equals(methodToCall))\n");
				  writer.write(
					  "\t\t\t\tthis." + minfo.getMethodname() + "(msgdata);\n\t\t\n");
			  }
		  }
		  //(else part)
		  writer.write("\t\t\telse  throw new AxisFault(\"method not found\");\n");
		  //catch block
		  writer.write(
			  "\t\t}catch(AxisFault e){\n\t\t\te.printStackTrace();\n\t\t\t\tmsgdata.setSoapFault(new SOAPFault(e));\n\t\t}\n");
		  writer.write(
			  "\t\tcatch(Exception e){\n\t\t\te.printStackTrace();\n\t\t\t\tmsgdata.setSoapFault(new SOAPFault(new AxisFault(\"error at wrapper invoke\",e)));\n\t\t}\n");
		  //end of method
		  writer.write("\t}\n");

}

/**
 * This method genarate methods that wraps the each method of the service
 * @param methodName
 * @param params
 * @param outparam
 * @throws IOException
 */
// cannot extend from super class because of 
public void writeMethodInWrapper(
	String methodName,
	Collection params,
	ParameterInfo returntype)
	throws WrapperFault, IOException {
	
	System.out.println("Details of the method "+ methodName+" collection "+params.size()+"  returnType "+returntype);
	String outparam;
	if (returntype == null)
		outparam = "void";
	else
		outparam = returntype.getLangName();

	//method signature
	writer.write(
		"\tpublic void "
			+ methodName
			+ "(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{\n");

	
	ArrayList paramsB = new ArrayList(params);
	//Iterator p = params.iterator();
	
// Create the parameter class for the first parameter. 
// Other parameters are ignored
// if serializing this is where you have to edit. 
	System.out.println(paramsB.size());
	writer.write(
			JavaUtils.getSimpleTypeParameterCreationCode(
				(ParameterInfo) paramsB.get(0),
				wscontext,
				1));
	
	if (!(outparam == null || outparam.equals("void"))) {
		boolean isSimpleType = TypeMap.isSimpleType(outparam);
		// Can a array be the output parameter of doc\literal ???
		boolean isArray = false;
		Type type;
		if ((type = this.wscontext.getTypemap().getType(returntype.getSchemaName()))
			!= null)
			isArray = type.isArray();

		//invoke the method on the result and set the result to message data
		if (isSimpleType) {
			writer.write(
				"\t\tmsgdata.setSoapBodyContent(new "
					+ WrapperUtils.getWrapperName4FullyQualifiedName(outparam)
					+ "(service."
					+ methodName
					+ "(");
			writer.write("paramIn1");
			writer.write(")));\n");

		} else if (isArray) {
		
			writer.write(
				"\t\t"
					+ returntype.getLangName()
					+ " ar = new "
					+ returntype.getLangName()
					+ "();");
			
			writer.write("\t\tar.setParam(service." + methodName + "(");
			writer.write("paramIn1");
			writer.write("));\n");
			writer.write("\t\tmsgdata.setSoapBodyContent(ar);");
		
		} else {
			writer.write(
				"\t\tmsgdata.setSoapBodyContent(service." + methodName + "(");
			writer.write("paramIn1");
			writer.write("));\n");
		}
	// void ends here.	
	} else {
		writer.write("\t\t service." + methodName + "(");
		writer.write("paramIn1");
		writer.write(");\n");
	}

	//write end of method
	writer.write("\t}\n");

}

/**
 * get the name of the output file
 * @return
 */
public File getJavaFilePath() {
	String dirpath;
		  String targetOutputLocation =
			  this.wscontext.getWrapInfo().getTargetOutputLocation();
		  if (targetOutputLocation.endsWith("/"))
			  targetOutputLocation =
				  targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
		  if (targetOutputLocation.equals(""))
			  dirpath = targetOutputLocation;
		  else{
			  dirpath =
				  targetOutputLocation
					  + "/"
					  + WrapperUtils.getPackegeName4QualifiedName(
							  this.wscontext.getSerInfo().getQualifiedServiceName())
						  .replace('.', '/');
		  }                
		  new File(dirpath).mkdirs();
		  return new File(dirpath + "/" + servicename + ".java");
	  }

	

}
