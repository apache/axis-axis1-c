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
				System.out.println("Error occured yet we continue to genarate other classes ... you should check the error");
				e.printStackTrace();
		}	
     }
}

