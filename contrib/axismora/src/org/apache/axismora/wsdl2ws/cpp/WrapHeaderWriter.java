package org.apache.axismora.wsdl2ws.cpp;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.MethodInfo;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

/**
 * @author Srinath Perera(hemapani@openource.lk)
 */
public class WrapHeaderWriter extends HeaderFileWriter{
	private WebServiceContext wscontext;
	private ArrayList methods;	
	public WrapHeaderWriter(WebServiceContext wscontext)throws WrapperFault{
		super(WrapperUtils.getClassNameFromFullyQualifiedName(wscontext.getSerInfo().getQualifiedServiceName()+CPPUtils.WRAPPER_NAME_APPENDER));
		this.wscontext = wscontext;
		this.methods = wscontext.getSerInfo().getMethods();
	}
	protected File getFilePath() throws WrapperFault {
		String targetOutputLocation = this.wscontext.getWrapInfo().getTargetOutputLocation();
		if(targetOutputLocation.endsWith("/"))
			targetOutputLocation = targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
		new File(targetOutputLocation).mkdirs();
		String fileName = targetOutputLocation + "/" + classname + ".h";
		return new File(fileName);
	}

	protected void writeClassComment() throws WrapperFault {
			try{
				writer.write("/////////////////////////////////////////////////////////////////////////////\n");
				writer.write("// This is the Service Class genarated by the tool WSDL2Ws\n");
				writer.write("//		"+classname+".h: interface for the "+classname+"class.\n");
				writer.write("//\n");
				writer.write("//////////////////////////////////////////////////////////////////////\n");
			}catch(IOException e){
				throw new WrapperFault(e);
			}
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.HeaderFileWriter#writeConstructors()
	 */
	protected void writeConstructors() throws WrapperFault {
		try{
		writer.write("public:\n\t"+classname+"();\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
	 */
	protected void writeDistructors() throws WrapperFault {
		try{
		writer.write("public:\n\tvirtual ~"+classname+"();\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
	 */
	protected void writeMethods() throws WrapperFault {
		try{
			writer.write("public://implementation of WrapperClassHandler interface\n");
			writer.write("\tint Invoke(IMessageData* mc);\n");
			writer.write("\tvoid OnFault(IMessageData* pMsg);\n");
			writer.write("\tint Init();\n");
			writer.write("\tint Fini();\n");
			writer.write("private://Methods corresponding to the web service methods\n");
			writer.write("\tint SetResponseMethod(IMessageData* mc, const AxisChar* name);\n");
			MethodInfo minfo;
			for (int i = 0; i < methods.size(); i++) {
					 minfo = (MethodInfo)methods.get(i);
					 writer.write("\tint "+minfo.getMethodname()+ "(IMessageData* mc);");
					 writer.write("\n");
				 }
     
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.HeaderFileWriter#writePreprocssorStatements()
	 */
	protected void writePreprocssorStatements() throws WrapperFault {
		try{
			writer.write("#include \""+CPPUtils.getWebServiceNameFromWrapperName(classname)+".h\"\n");
			writer.write("#include <WrapperClassHandler.h>\n");
			writer.write("#include <IMessageData.h>\n");
			writer.write("#include <GDefine.h>\n");
			writer.write("#include <IWrapperSoapDeSerializer.h>\n");
			writer.write("#include <IWrapperSoapSerializer.h>\n");
			writer.write("#include <ISoapMethod.h>\n");
			writer.write("#include <IParam.h>\n\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}
	protected String getExtendsPart(){return " : public WrapperClassHandler";}
	protected void writeAttributes()throws WrapperFault{
		try{
			writer.write("private:// Actual web service object\n\t"+CPPUtils.getWebServiceNameFromWrapperName(classname)+" *pWs;\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}			
	}
}
