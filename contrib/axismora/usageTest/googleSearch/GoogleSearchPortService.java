package googleSearch;
import org.apache.axis.AxisFault;
import org.apache.axis.message.SOAPFault;
/**
 * This Code is Genarated by the Wrapper Genarator. 
 * This Class act as the Wrapper to invoke the Webservice methods
*/
public class GoogleSearchPortService extends org.apache.axismora.handlers.BasicHandler {
	private googleSearch.GoogleSearchPort service;

	public GoogleSearchPortService(){
			service = new googleSearch.GoogleSearchPort();
	}

/*
	This method is called by the Wrapper. 
*/
	public void invoke(org.apache.axismora.MessageContext msgdata){
		 try{
			String methodToCall = msgdata.getMethodName().getLocalPart();
			if("doGetCachedPage".equals(methodToCall))
				this.doGetCachedPage(msgdata);
		
			else if("doSpellingSuggestion".equals(methodToCall))
				this.doSpellingSuggestion(msgdata);
		
			else if("doGoogleSearch".equals(methodToCall))
				this.doGoogleSearch(msgdata);
		
			else  throw new AxisFault("method not found");
		}catch(AxisFault e){
			e.printStackTrace();
				msgdata.setSoapFault(new SOAPFault(e));
		}
		catch(Exception e){
			e.printStackTrace();
				msgdata.setSoapFault(new SOAPFault(new AxisFault("error at wrapper invoke",e)));
		}
	}

	public void doGetCachedPage(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		java.lang.String paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		java.lang.String paramIn1 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(service.doGetCachedPage(paramIn0,paramIn1));
	}

	public void doSpellingSuggestion(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		java.lang.String paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		java.lang.String paramIn1 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.StringParam(service.doSpellingSuggestion(paramIn0,paramIn1)));
	}

	public void doGoogleSearch(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		java.lang.String paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		boolean paramIn1 =  (new  org.apache.axismora.wrappers.simpleType.BooleanParam(msgdata)).getParam();
		int paramIn2 =  (new  org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
		java.lang.String paramIn3 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		java.lang.String paramIn4 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		boolean paramIn5 =  (new  org.apache.axismora.wrappers.simpleType.BooleanParam(msgdata)).getParam();
		java.lang.String paramIn6 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		java.lang.String paramIn7 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		int paramIn8 =  (new  org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
		java.lang.String paramIn9 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(service.doGoogleSearch(paramIn0,paramIn1,paramIn2,paramIn3,paramIn4,paramIn5,paramIn6,paramIn7,paramIn8,paramIn9));
	}

}
