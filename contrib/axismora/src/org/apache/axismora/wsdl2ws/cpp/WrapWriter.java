package org.apache.axismora.wsdl2ws.cpp;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.MethodInfo;
import org.apache.axismora.wsdl2ws.info.ParameterInfo;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

/**
 * @author Srinath Perera(hemapani@openource.lk)
 */

public class WrapWriter extends CPPClassWriter{
	private WebServiceContext wscontext;
	private ArrayList methods;	
	public WrapWriter(WebServiceContext wscontext)throws WrapperFault{
		super(WrapperUtils.getClassNameFromFullyQualifiedName(wscontext.getSerInfo().getQualifiedServiceName()+CPPUtils.WRAPPER_NAME_APPENDER));
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
				writer.write("//////////////////////////////////////////////////////////////////////\n\n");
			}catch(IOException e){
				throw new WrapperFault(e);
			}
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.HeaderFileWriter#writeConstructors()
	 */
	protected void writeConstructors() throws WrapperFault {
		try{
		writer.write(classname+"::"+classname+"()\n{\n");
		writer.write("\tpWs = new "+CPPUtils.getWebServiceNameFromWrapperName(classname)+ "();\n");
		writer.write("}\n\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
	 */
	protected void writeDistructors() throws WrapperFault {
		try{
		writer.write(classname+"::~"+classname+"()\n{\n\tdelete pWs;\n}\n\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
	 */
	protected void writeMethods() throws WrapperFault {
		try{
			writer.write("//implementation of WrapperClassHandler interface\n");
			
			writer.write("void "+classname+"::OnFault(IMessageData *pMsg)\n{\n}\n\n");
			writer.write("int "+classname+"::Init()\n{\n\treturn SUCCESS;\n}\n\n");
			writer.write("int "+classname+"::Fini()\n{\n\treturn SUCCESS;\n}\n\n");
			writeInvoke();
			writeSetSoapMethod();
			writer.write("\n//Methods corresponding to the web service methods\n");
			MethodInfo minfo;
			for (int i = 0; i < methods.size(); i++) {
					 minfo = (MethodInfo)methods.get(i);
					 this.writeMethodInWrapper(minfo.getMethodname(), minfo.getParameterTypess(),minfo.getReturnType());
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
		writer.write("#include \""+classname+".h\"\n\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}
	
	/**
	 * write the invoke method
	 * @throws IOException
	 */
	private void writeInvoke() throws IOException {
		writer.write("\n/////////////////////////////////////////////////////////////////\n");
		writer.write("// This method invokes the right service method \n");
		writer.write("//////////////////////////////////////////////////////////////////\n");
		writer.write("int "+classname+"::Invoke(IMessageData *mc)\n{\n");
		//msgdata.setSoapFault(new SOAPFault(new AxisFault()))
		writer.write("\tIWrapperSoapDeSerializer *pIWSDZ = NULL;\n");
		writer.write("\tmc->getSoapDeSerializer(&pIWSDZ);\n");
		writer.write("\tif (!pIWSDZ) return FAIL;\n");
		writer.write("\tconst AxisChar *method = pIWSDZ->GetMethodName();\n");
		//if no methods in the service simply return
		if (methods.size() == 0) {
			writer.write("}\n");
			return;
		}
		MethodInfo minfo = (MethodInfo)methods.get(0);
		//if conditions (if parts)		
		writer.write("\tif (0 == strcmp(method, \""+ minfo.getMethodname() +"\"))\n");
		writer.write("\t\treturn "+minfo.getMethodname()+"(mc);\n");
		//(else if parts)
		if (methods.size() > 1) {
			for (int i = 1; i < methods.size(); i++) {
				minfo = (MethodInfo)methods.get(i);
				writer.write("\telse if (0 == strcmp(method, \""+ minfo.getMethodname() +"\")\n");
				writer.write("\t\treturn "+minfo.getMethodname()+"(mc);\n");
			}
		}
		//(else part)
		writer.write("\telse return FAIL;\n");
		//end of method
		writer.write("}\n\n");
	}

	private void writeSetSoapMethod() throws IOException {
		writer.write("\n/////////////////////////////////////////////////////////////////\n");
		writer.write("// This method sets the method element of the Serializer response \n");
		writer.write("//////////////////////////////////////////////////////////////////\n");
		writer.write("int "+classname+"::SetResponseMethod(IMessageData* mc, const AxisChar* name)\n{\n");
		writer.write("\tIWrapperSoapSerializer* pIWSSZ = NULL;\n");
		writer.write("\tmc->getSoapSerializer(&pIWSSZ);\n");
		writer.write("\tif (!pIWSSZ) return FAIL;\n");
		writer.write("\tISoapMethod* pMethod = pIWSSZ->createSoapMethod();\n");
		writer.write("\tpMethod->setLocalName(name);\n");
		writer.write("\tpMethod->setPrefix(pIWSSZ->getNewNamespacePrefix());\n");
		writer.write("\tpMethod->setUri(\"http://www.opensource.lk/"+CPPUtils.getWebServiceNameFromWrapperName(classname)+"\");\n");
		writer.write("\treturn SUCCESS;\n}\n");
	}
	/**
	 * This method genarate methods that wraps the each method of the service
	 * @param methodName
	 * @param params
	 * @param outparam
	 * @throws IOException
	 */

	public void writeMethodInWrapper(String methodName, Collection params, ParameterInfo returntype) throws WrapperFault,IOException {
		String outparam = returntype.getLangName();
		writer.write("\n/////////////////////////////////////////////////////////////////\n");
		writer.write("// This method wrap the service method \n");
		writer.write("//////////////////////////////////////////////////////////////////\n");
		//method signature
		writer.write("int "+classname+"::" + methodName + "(IMessageData* mc)\n{\n");
		writer.write("\tIWrapperSoapSerializer *pIWSSZ = NULL;\n");
		writer.write("\tmc->getSoapSerializer(&pIWSSZ);\n");
		writer.write("\tif (!pIWSSZ) return FAIL;\n");
		writer.write("\tIWrapperSoapDeSerializer *pIWSDZ = NULL;\n");
		writer.write("\tmc->getSoapDeSerializer(&pIWSDZ);\n");
		writer.write("\tif (!pIWSDZ) return FAIL;\n");
		writer.write("\tSetResponseMethod(mc, \""+methodName+"Response\");\n");

		//create the param classes for each parameter
		String paraTypeName;
		ArrayList paramsB = new ArrayList(params);
		Iterator p =  params.iterator();
		for (int i = 0; i < paramsB.size(); i++) {
			paraTypeName = ((ParameterInfo)paramsB.get(i)).getLangName();
			Type type;
			writer.write("\tIParam *param"+i+"= pIWSDZ->GetParam();\n");			
			if((CPPUtils.isSimpleType(((ParameterInfo)paramsB.get(i)).getLangName()))){
				//for simple types	
				writer.write("\t"+paraTypeName+" v"+i+" = param->"+CPPUtils.getParameterGetValueMethodName(paraTypeName)+";\n");
			}else if((type = this.wscontext.getTypemap().getType(((ParameterInfo)paramsB.get(i)).getSchemaName())) != null 
						&& type.isArray()){
            	//TODO for Array types				
				//String ContentparaTypeName = WrapperUtils.getParameterName4ParamInfo((ParameterInfo)paramsB.get(i),wscontext);
			
			}else{
				//for complex types 
				writer.write("\t"+paraTypeName+" *v"+i+" = new "+paraTypeName+"();\n");
				writer.write("\tparam"+i+"->SetUserType(v"+i+", (AXIS_DESERIALIZE_FUNCT)Axis_DeSerialize_"+paraTypeName+", (AXIS_OBJECT_DELETE_FUNCT)Axis_Delete_"+paraTypeName+");\n");
				writer.write("\tpIWSDZ->Deserialize(param"+i+",0);\n");
			}
		}
			
		if(!(outparam == null ||outparam.equals("void"))){				
			boolean isSimpleType = CPPUtils.isSimpleType(outparam);
			boolean isArray = returntype.getType().isArray();
			// -------- I dont understand why following lines does-Susantha -------//
			Type type;
			if ((type = this.wscontext.getTypemap().getType(returntype.getSchemaName())) != null ){
				if (isArray = type.isArray()){
					outparam = type.getTypNameForAttribName("item")+"[]";
				}
			}	
			// -------------------------------------------------------------------//
			/* Invoke the service when return type not void */
			writer.write("\t"+outparam+(isSimpleType?" ":" *")+ "ret = "+"pWs->"+methodName+"(");
			for (int i = 0; i <  paramsB.size() - 1; i++)
					writer.write("v" + i + ",");
			writer.write("v" + ( paramsB.size() - 1));					
			writer.write(");\n");					
			/* set the result */
			if (isSimpleType){
				writer.write("\tIParam *pRetParam = pIWSSZ->AddOutputParam(ret);\n");
			}else if(isArray){
				//TODO array type
			}
			else{
				//complex type
				writer.write("\tIParam *pRetParam = pIWSSZ->AddOutputParam(ret, (void*)Axis_Serialize_"+outparam+", (void*)Axis_Delete_"+outparam+");\n");
			}
			writer.write("\tpRetParam->SetName(\""+methodName+"Return\");\n");
			writer.write("\treturn SUCCESS;\n");
		}else{//method does not return anything
			/* Invoke the service when return type is void */
	 		writer.write("\t pWs->" + methodName + "(");
			for (int i = 0; i <  paramsB.size() - 1; i++) {
				writer.write("v" + i + ",");
			}
			writer.write("v" + ( paramsB.size() - 1));
			writer.write(")\n");
	}
	//write end of method
	writer.write("}\n");
	}
	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.CPPClassWriter#writeGlobalCodes()
	 */
	protected void writeGlobalCodes() throws WrapperFault {
		Iterator types = wscontext.getTypemap().getTypes().iterator();
		String typeName;
		try {
			while(types.hasNext()){
				typeName = ((Type)types.next()).getLanguageSpecificName();
				writer.write("extern int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer *pDZ);\n");
				writer.write("extern void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray = false, int nSize=0);\n");
				writer.write("extern int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer& pSZ, bool bArray = false);\n");
				writer.write("extern int Axis_GetSize_"+typeName+"("+typeName+"* param);\n\n");
			}
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}
}
