package org.apache.axismora.wsdl2ws.cpp;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.MethodInfo;
import org.apache.axismora.wsdl2ws.info.ParameterInfo;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class ServiceWriter extends CPPClassWriter{
	private WebServiceContext wscontext;
	private ArrayList methods;	
	public ServiceWriter(WebServiceContext wscontext)throws WrapperFault{
		super(WrapperUtils.getClassNameFromFullyQualifiedName(wscontext.getSerInfo().getQualifiedServiceName()));
		this.wscontext = wscontext;
		this.methods = wscontext.getSerInfo().getMethods();
	}

	protected File getFilePath() throws WrapperFault {
		String targetOutputLocation = this.wscontext.getWrapInfo().getTargetOutputLocation();
		if(targetOutputLocation.endsWith("/"))
			targetOutputLocation = targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
		new File(targetOutputLocation).mkdirs();
		String fileName = targetOutputLocation + "/" + classname + ".cpp";
		return new File(fileName);
	}

	protected void writeClassComment() throws WrapperFault {
		try{
			writer.write("///////////////////////////////////////////////////////////////////////\n");	
			writer.write("//This is the Service implementation CPP file genarated by theWSDL2Ws.\n");
			writer.write("//		"+classname+".cpp: implemtation for the "+classname+".\n");
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
		writer.write("\n"+classname+"::"+classname+"()\n{\n}\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
	 */
	protected void writeDistructors() throws WrapperFault {
		try{
		writer.write("\n"+classname+"::~"+classname+"()\n{\n}\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
	 */
	protected void writeMethods() throws WrapperFault {
		MethodInfo minfo;
		boolean isSimpleType;
		 try{
		  writer.write("\n");	
		  for(int i = 0; i < methods.size(); i++){
			  minfo = (MethodInfo)this.methods.get(i);

			  if(minfo.getReturnType().getLangName()==null)
				  writer.write("void ");
			  else {
				String outparam = minfo.getReturnType().getLangName();
				isSimpleType = CPPUtils.isSimpleType(outparam);
				writer.write(WrapperUtils.getClassNameFromParamInfoConsideringArrays(minfo.getReturnType(),wscontext)+(isSimpleType?" ":" *"));
			  }
			  writer.write(classname+"::"+minfo.getMethodname()+"(");
			  //write parameter names 
			//write parameter names 
			Iterator params = minfo.getParameterTypess().iterator();
			if(params.hasNext()){
				ParameterInfo fparam = (ParameterInfo)params.next();
				isSimpleType = CPPUtils.isSimpleType(fparam.getLangName());
				writer.write(WrapperUtils.getClassNameFromParamInfoConsideringArrays(fparam,wscontext)+(isSimpleType?" Value":" *pValue")+0);
			}
			for(int j =1; params.hasNext();j++){
				ParameterInfo nparam = (ParameterInfo)params.next();
				isSimpleType = CPPUtils.isSimpleType(nparam.getLangName());
				writer.write(","+WrapperUtils.getClassNameFromParamInfoConsideringArrays(nparam,wscontext)+(isSimpleType?" Value":" *pValue")+j);
			}
			writer.write(")\n{\n}\n");
		  }
		}catch (Exception e) {
			  e.printStackTrace();
			  throw new WrapperFault(e);
		}	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.HeaderFileWriter#writePreprocssorStatements()
	 */
	protected void writePreprocssorStatements() throws WrapperFault {
		try{
		writer.write("#include \""+classname+".h\"\n\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

}
