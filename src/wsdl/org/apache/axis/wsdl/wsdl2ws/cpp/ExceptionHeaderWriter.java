/*
 *   Copyright 2003-2004 The Apache Software Foundation.
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
package org.apache.axis.wsdl.wsdl2ws.cpp;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.FaultInfo; 
/**
 * @author nithya
 *
 */
public class ExceptionHeaderWriter extends HeaderFileWriter{
	
	private WebServiceContext wscontext;
	private ArrayList methods;		
	String faultInfoName;
	
	public ExceptionHeaderWriter(WebServiceContext wscontext,String faultInfoName)throws WrapperFault{
	    //super(WrapperUtils.getClassNameFromFullyQualifiedName(wscontext.getSerInfo().getQualifiedServiceName()));
	    super("Axis"+faultInfoName+"Exception");//damitha
        System.out.println("faultInfoName is:"+faultInfoName);
	    this.wscontext = wscontext;
	    this.methods = wscontext.getSerInfo().getMethods();
	    this.faultInfoName ="Axis"+faultInfoName+"Exception" ;	
    }

     protected File getFilePath() throws WrapperFault {
      	String targetOutputLocation = this.wscontext.getWrapInfo().getTargetOutputLocation();
	    if(targetOutputLocation.endsWith("/"))
		       targetOutputLocation = targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
	     new File(targetOutputLocation).mkdirs();
	    String fileName = targetOutputLocation + "/" + faultInfoName + ".h";
	    return new File(fileName);
    }

     	/* (non-Javadoc)
		 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writePreprocssorStatements()
		 */
		protected void writePreprocssorStatements() throws WrapperFault {
			try{				
				    writer.write("#include <string>\n");
				    writer.write("#include <exception>\n");
				    writer.write("#include <axis/server/AxisException.h>\n");
				    writer.write("#include <axis/ISoapFault.h>\n");
				    getLangName();				
				    writer.write("using namespace std;\n");				
			}catch(IOException e){
				throw new WrapperFault(e);
			}
		}

	/* (non-Javadoc)
		 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeClassComment()
		 */
		protected void writeClassComment() throws WrapperFault {
			try{
				writer.write("/*\n");	
				writer.write(" * This file was auto-generated by the Axis C++ Web Service " +
					"Generator (WSDL2Ws)\n");
				writer.write(" * This file contains an Exception class of the web service.\n");										
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
			writer.write("public:\n\t"+faultInfoName+"();\n");
			writer.write("\t"+faultInfoName+"(ISoapFault* pFault);\n");
			writer.write("\t"+faultInfoName+"(int iExceptionCode);\n");
			writer.write("\t"+faultInfoName+"(exception* e);\n");
			writer.write("\t"+faultInfoName+"(exception* e, int iExceptionCode);\n");				
			}catch(IOException e){
				throw new WrapperFault(e);
			}
		}
		
	/* (non-Javadoc)
		 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
		 */
		protected void writeDistructors() throws WrapperFault {
			try{
			writer.write("\tvirtual ~"+faultInfoName+"() throw();\n");
			}catch(IOException e){
				throw new WrapperFault(e);
			}
		}
	/* (non-Javadoc)
		 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
		 */
		protected void writeMethods() throws WrapperFault {
			try{
				writer.write("\t const char* what() throw();\n");
				writer.write("\t const int getExceptionCode();\n");
				writer.write("\t const string getMessage(exception* e);\n");
				writer.write("\t const string getMessage(int iExceptionCode);\n");
				writer.write("private:\n\t void processException(exception* e);\n");
				writer.write("\t void processException(ISoapFault* pFault);\n");
				writer.write("\t void processException(exception* e, int iExceptionCode);\n");
				writer.write("\t void processException(int iExceptionCode);\n");
				writer.write("\t string m_sMessage;\n");				writer.write("\t int m_iExceptionCode;\n\n");								
			}catch (Exception e) {
			  e.printStackTrace();
			  throw new WrapperFault(e);
	    	}
		}
		
	    protected String getFileType()
		{
			return "Exception";	// must change accordingly
		}
        protected String getExtendsPart(){return ": public AxisException";}
        
	   public void getLangName() throws WrapperFault
	   {		
	       ArrayList methods;
   	       methods = wscontext.getSerInfo().getMethods();
	       MethodInfo minfo;
	       FaultInfo faultinfo;
  	       try
  	       {
				for (int i = 0; i < methods.size(); i++) 
				{
				    minfo = (MethodInfo)methods.get(i);
					Iterator paramsFault = minfo.getFaultType().iterator();
					String langName =null;
					String paramName =null;
					while (paramsFault.hasNext())
					{
					     FaultInfo info = (FaultInfo)paramsFault.next();			
						 ArrayList paramInfo =info.getParams();
						 for (int j= 0; j < paramInfo.size(); j++)
						 {
						     ParameterInfo par =(ParameterInfo)paramInfo.get(j);                                                                                                                                                           
							 paramName  = par.getParamName();
							 langName =par.getLangName();								 
							 writer.write("#include \""+langName+".h\"\n\n");					 								
						  }
					  }
				   }			
			  }
			  catch(Exception e)
			  {
			 	   System.out.println("Error occured yet we continue to genarate other classes ... you should check the error");
				   e.printStackTrace();
			  }	
	    }      
}
