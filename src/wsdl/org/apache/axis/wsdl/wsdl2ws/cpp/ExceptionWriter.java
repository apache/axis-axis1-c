/*
 * Created on Jun 3, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
package org.apache.axis.wsdl.wsdl2ws.cpp;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
//import java.util.Collection;
//import java.util.HashSet;
//import java.util.Iterator;
//
//import javax.xml.namespace.QName;
//
//import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
//import org.apache.axis.wsdl.wsdl2ws.CUtils;
//import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
//import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
//import org.apache.axis.wsdl.wsdl2ws.info.Type;
//import org.apache.axis.wsdl.wsdl2ws.info.FaultInfo; 
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
/**
 * @author nithya
 *
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public class ExceptionWriter extends CPPExceptionClassWriter{
	   private WebServiceContext wscontext;
	   private ArrayList methods;		
	  // String  classname = "AxisDivByZeroException";	
	   String faultInfoName;
	   String langName;
	   String faultType;
	   
		public ExceptionWriter(WebServiceContext wscontext,String faultInfoName,String langName,String faultType)throws WrapperFault{
			super(WrapperUtils.getClassNameFromFullyQualifiedName(wscontext.getSerInfo().getQualifiedServiceName()));
			this.wscontext = wscontext;
			this.methods = wscontext.getSerInfo().getMethods();
			this.faultInfoName ="Axis"+faultInfoName+"Exception";
			this.langName =langName;
			this.faultType =faultType;
	
			
		}
	
	    protected File getFilePath() throws WrapperFault {
			String targetOutputLocation = this.wscontext.getWrapInfo().getTargetOutputLocation();
			if(targetOutputLocation.endsWith("/"))
				targetOutputLocation = targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
			new File(targetOutputLocation).mkdirs();
			String fileName = targetOutputLocation + "/" + faultInfoName + ".cpp";
			return new File(fileName);
		}	
		

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writePreprocssorStatements()
	 */
	protected void writePreprocssorStatements() throws WrapperFault {
		try{
			writer.write("#include \""+faultInfoName+".h\"\n\n");
			writer.write("#include <axis/server/AxisWrapperAPI.h>\n\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}
		
	    protected void writeClassComment() throws WrapperFault {
				try{
					writer.write("/*\n");	
					writer.write(" * This is the  implementation file genarated by WSDL2Ws tool.\n");
					writer.write(" * "+faultInfoName+".cpp: implemtation for the "+faultInfoName+".\n");
					writer.write(" *\n");
					writer.write(" */\n\n");
				}catch(IOException e){
					throw new WrapperFault(e);
				}
		}
		
	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeConstructors()
	 */
	protected void writeConstructors() throws WrapperFault {
		try{				
					
		writer.write(faultInfoName+"::"+faultInfoName+"()\n{\n");
		writer.write("/* This only serves the pupose of indicating that the \n");
		writer.write(" * service has thrown an excpetion \n");
		writer.write(" */ \n");
		writer.write("\tm_iExceptionCode = AXISC_SERVICE_THROWN_EXCEPTION; \n");
		writer.write("\tprocessException(m_iExceptionCode); \n");
		writer.write("}\n\n");
		
		writer.write(faultInfoName+"::"+faultInfoName+"("+faultType +"pFault)\n");
		writer.write("{\n");
		writer.write("\tm_iExceptionCode = AXISC_SERVICE_THROWN_EXCEPTION;\n");//damitha
		writer.write("\tprocessException(pFault);");//damitha
		writer.write("}\n\n");
		
		writer.write(faultInfoName+"::"+faultInfoName+"(int iExceptionCode)\n");
		writer.write("{\n\n");
		writer.write("\tm_iExceptionCode = iExceptionCode;\n");//damitha
		writer.write("\tprocessException (iExceptionCode);\n");//damitha
		writer.write("}\n\n");
		
		writer.write(faultInfoName+"::"+faultInfoName+"(exception* e)\n");
		writer.write("{\n");
		writer.write("\tprocessException (e);\n");//damitha
		writer.write("}\n\n");
		
		writer.write(faultInfoName+"::"+faultInfoName+"(exception* e,int iExceptionCode)\n");
		writer.write("{\n\n");
		writer.write("\tprocessException (e, iExceptionCode);\n");//damitha
		writer.write("}\n\n");	
	    }catch(IOException e){
			throw new WrapperFault(e);
		}	
	}
	
    	/* (non-Javadoc)
		 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
		 */
	  protected void writeDistructors() throws WrapperFault {
			try{
			writer.write(faultInfoName+"::~"+faultInfoName+"() throw () \n{\n\tm_sMessage =\"\";\n}\n\n");
			}catch(IOException e){
				throw new WrapperFault(e);
			}
		}
		
	   protected void writeMethods() throws WrapperFault {
	
	   try{	
	       writer.write("void "+faultInfoName+":: processException(exception* e, int iExceptionCode)\n");
	       writer.write("{\n");
	       writer.write("\tm_sMessage = getMessage (e) + getMessage (iExceptionCode);\n");//damitha
	       writer.write("}\n\n");

	       writer.write("void "+faultInfoName+"::processException ("+faultType+" pFault)\n");
		   writer.write("{\n");
                   writer.write("\t/*User can do something like deserializing the struct into a string*/");//damitha
		   writer.write("}\n\n");

		   writer.write("void "+faultInfoName+"::processException(exception* e)\n");
		   writer.write("{\n");
		   writer.write("\tm_sMessage = getMessage (e);\n");//damitha
		   writer.write("}\n\n");

		    writer.write("void "+faultInfoName+"::processException(int iExceptionCode)\n");//damitha
		    writer.write("{\n");
		    writer.write("\tm_sMessage = getMessage (iExceptionCode);\n");//damitha
		    writer.write("}\n\n");
		
	       writer.write("const string "+faultInfoName+"::getMessage (exception* objException)\n");
	       writer.write("{\n");
	       writer.write("\tstring sMessage = objException->what();\n");//damitha
	       writer.write("\treturn sMessage;\n");//damitha
	       writer.write("}\n\n");

		   writer.write("const string "+faultInfoName+"::getMessage (int iExceptionCode)\n");
		   writer.write("{\n");
		   writer.write("\tstring sMessage;\n");
		   writer.write("\tswitch(iExceptionCode)\n");
		   writer.write("\t{\n");
		   writer.write("\t\tcase AXISC_SERVICE_THROWN_EXCEPTION:\n");
		   writer.write("\t\tsMessage = \"A service has thrown an exception. see detail\";\n");
		   writer.write("\t\tbreak;\n");
		   writer.write("\t\tdefault:\n");
		   writer.write("\t\tsMessage = \"Unknown Exception has occured\";\n");
		   writer.write("\t}\n");
		   writer.write("return sMessage;\n");
	       writer.write("}\n\n");

		   writer.write("const char* "+faultInfoName+"::what() throw ()\n");
	       writer.write("{\n");
		   writer.write("\treturn m_sMessage.c_str ();\n");
		   writer.write("}\n\n");
		   
      	   writer.write("const int "+faultInfoName+"::getExceptionCode()");//damitha
	  	   writer.write("{\n");
		   writer.write("\treturn m_iExceptionCode;\n");
		   writer.write("}\n\n");
			  	     
	 }catch(IOException e){
					 throw new WrapperFault(e);
				 }
	   }	
}
