// Copyright 2003-2004 The Apache Software Foundation.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*
 * Created on Jun 4, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
package org.apache.axis.wsdl.wsdl2ws.cpp;
import org.apache.axis.wsdl.wsdl2ws.SourceWriter;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

/**
 * @author nithya
 *
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public class AllExceptionWriter implements SourceWriter{
private WebServiceContext wscontext;
private String strFlag="";
	
  public AllExceptionWriter(WebServiceContext wscontext,String strFlag){
	  this.wscontext =wscontext;
	  this.strFlag =strFlag;	  
   }
    /**
	 * genarate all the Exceptions.
	 * @see org.apache.axis.wsdl.wsdl2ws.SourceWriter#writeSource()
	 */
	public void writeSource() throws WrapperFault 
	{		    		
	     try
	     {
          if (strFlag.equals("Client"))
	          {
			       (new ExceptionHeaderWriter(wscontext,"Client")).writeSource();
				   (new ExceptionWriter(wscontext,"Client")).writeSource();
	          }
     	  else if (strFlag.equals("Server"))
	     	  {		     	  	  
				  (new ExceptionHeaderWriter(wscontext,"Service")).writeSource();
				  (new ExceptionWriter(wscontext,"Service")).writeSource();
	     	  }					
		 }			
		 catch(Exception e)
		{
				System.out.println("Error occurred yet we continue to genarate other classes ... you should check the error");
				e.printStackTrace();
		}	
     }
}

