package org.apache.axismora.wsdl2ws.c;
import java.util.Iterator;

import org.apache.axismora.wsdl2ws.SourceWriter;
import org.apache.axismora.wsdl2ws.WrapperConstants;
import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

/**
 * Parameter genarator.. genarate all necessary param classes
 * @author hemapani
 */
public class AllParamWriter implements SourceWriter{
	private WebServiceContext wscontext;
	
	public AllParamWriter(WebServiceContext wscontext){
		this.wscontext =wscontext;
	}

	/**
	 * genarate all the wrappets for custom complex types.
	 * @see org.apache.axismora.wsdl2ws.SourceWriter#writeSource()
	 */
	public void writeSource() throws WrapperFault {
		Iterator enu = wscontext.getTypemap().getTypes().iterator();
		String generator = wscontext.getWrapInfo().getImplStyle();
		Type type;
		while(enu.hasNext()){	
		try{	
			type = (Type)enu.next();
			if(wscontext.getWrapInfo().getImplStyle().equals(WrapperConstants.IMPL_STYLE_STRUCT)){
					if(type.isArray()){
						System.out.println("Array writer called ......not yet suuported");
						//(new ArrayParamWriter(wscontext,type)).writeSource();
					}	
					else{	
						System.out.println("struct writer called ......");
						(new BeanParamWriter(wscontext,type)).writeSource();
						(new ParmHeaderFileWriter(wscontext,type)).writeSource();	
					}	
				}	
			}catch(Exception e){
				System.out.println("Error occured yet we continue to genarate other classes ... you should check the error");
				e.printStackTrace();
			}	
		}
	}
}
