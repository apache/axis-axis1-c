/*
 * Created on Jun 4, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
package org.apache.axis.wsdl.wsdl2ws.cpp;
import java.util.Iterator;
import java.util.ArrayList; 
import org.apache.axis.wsdl.wsdl2ws.SourceWriter;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
//import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;

//import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.FaultInfo; 

/**
 * @author nithya
 *
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public class AllExceptionWriter implements SourceWriter{
private WebServiceContext wscontext;
	
public AllExceptionWriter(WebServiceContext wscontext){
	this.wscontext =wscontext;
}
    /**
	 * genarate all the Exceptions.
	 * @see org.apache.axis.wsdl.wsdl2ws.SourceWriter#writeSource()
	 */
	public void writeSource() throws WrapperFault {		
    ArrayList methods;
	methods = wscontext.getSerInfo().getMethods();
	MethodInfo minfo;
	FaultInfo faultinfo;
	try{
				for (int i = 0; i < methods.size(); i++) {
					minfo = (MethodInfo)methods.get(i);
					Iterator paramsFault = minfo.getFaultType().iterator();
							String faultInfoName =null;
							String faultType =null;	 
							String langName =null;
							String paramName =null;
							while (paramsFault.hasNext()){
								FaultInfo info = (FaultInfo)paramsFault.next();
								faultInfoName =info.getFaultInfo();
								ArrayList paramInfo =info.getParams();
								for (int j= 0; j < paramInfo.size(); j++) {
									ParameterInfo par =(ParameterInfo)paramInfo.get(j);                                                                                                                                                           
									paramName  = par.getParamName();
									langName =par.getLangName();
									faultType = WrapperUtils.getClassNameFromParamInfoConsideringArrays(par,wscontext);
														(new ExceptionHeaderWriter(wscontext,faultInfoName,langName,faultType)).writeSource();
														(new ExceptionWriter(wscontext,faultInfoName,langName,faultType)).writeSource();	
									}
								}
				}
			
			}catch(Exception e){
				System.out.println("Error occured yet we continue to genarate other classes ... you should check the error");
				e.printStackTrace();
			}	
	}
}

