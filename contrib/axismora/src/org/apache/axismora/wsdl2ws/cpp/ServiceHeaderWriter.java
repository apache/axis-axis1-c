package org.apache.axismora.wsdl2ws.cpp;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.MethodInfo;
import org.apache.axismora.wsdl2ws.info.ParameterInfo;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class ServiceHeaderWriter extends HeaderFileWriter{
	private WebServiceContext wscontext;
	private ArrayList methods;	
	public ServiceHeaderWriter(WebServiceContext wscontext)throws WrapperFault{
		super(WrapperUtils.getClassNameFromFullyQualifiedName(wscontext.getSerInfo().getQualifiedServiceName()));
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

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.HeaderFileWriter#writeAttributes()
	 */
	protected void writeAttributes() throws WrapperFault {
		// TODO Auto-generated method stub

	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.HeaderFileWriter#writeClassComment()
	 */
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
		writer.write("\tpublic:\n\t\t"+classname+"();\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
	 */
	protected void writeDistructors() throws WrapperFault {
		try{
		writer.write("\tpublic:\n\t\tvirtual ~"+classname+"();\n");
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
		  writer.write("\tpublic: \n");	
		  for(int i = 0; i < methods.size(); i++){
			  minfo = (MethodInfo)this.methods.get(i);
			  //write return type
			  if(minfo.getReturnType().getLangName()==null)
				  writer.write("\t\tvoid ");
			  else {
			  	  String outparam = minfo.getReturnType().getLangName();
				  isSimpleType = CPPUtils.isSimpleType(outparam);
				  writer.write("\t\t"+WrapperUtils.getClassNameFromParamInfoConsideringArrays(minfo.getReturnType(),wscontext)+(isSimpleType?" ":" *"));
			  }
			  writer.write(minfo.getMethodname()+"(");
            
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
			  writer.write(");\n");
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
			Type atype;
			Iterator types = this.wscontext.getTypemap().getTypes().iterator();
			while(types.hasNext()){
				atype = (Type)types.next();
				writer.write("#include \""+atype.getLanguageSpecificName()+".h\"\n");
			}
			writer.write("\n");
		}catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}

}

