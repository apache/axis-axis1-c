package org.apache.axismora.wsdl2ws;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;

import javax.wsdl.Binding;
import javax.wsdl.BindingInput;
import javax.wsdl.BindingOperation;
import javax.wsdl.BindingOutput;
import javax.wsdl.Port;
import javax.wsdl.extensions.soap.SOAPOperation;

/**
 * @author hemapani
 */
public class SymbolTableParsingUtils {
	public static String getTargetEndPointURI(Iterator ports){
	  //we are checking only the first port. 
	  //if the targetEndPointURI not specifed we continue having it null
	  //The WrapperInfo will set a default value for the targetEndPointURI
			
	  if (ports.hasNext()) {
		  Port port = (Port) ports.next();
		  List adresslist = port.getExtensibilityElements();
		  if (adresslist != null
			  && adresslist.size() != 0
			  && (adresslist.get(0)
				  instanceof javax.wsdl.extensions.soap.SOAPAddress))
			  return 
				  ((javax.wsdl.extensions.soap.SOAPAddress) adresslist.get(0))
					  .getLocationURI();
	  }
	  return null;
	}
	
	public static String getTransportType(Binding binding){
		List soapbinding = binding.getExtensibilityElements();
		if (soapbinding != null
			&& soapbinding.size() > 0
			&& (soapbinding.get(0) instanceof javax.wsdl.extensions.soap.SOAPBinding))
			return 	((javax.wsdl.extensions.soap.SOAPBinding) soapbinding.get(0))
					.getTransportURI();
		return null;			
	}
	
	public static String getSoapAction(BindingOperation bindingOperation){
		List extenstions = bindingOperation.getExtensibilityElements();
		for(int i=0;i<extenstions.size();i++){
			if(extenstions.get(i) instanceof SOAPOperation)
				return ((SOAPOperation)extenstions.get(i)).getSoapActionURI();
		}
		return null;
	}
	public static List getInputEncodingStype(BindingInput input){
	  if (input == null)
			return null;
	  List soapbodies = input.getExtensibilityElements();

	  if (soapbodies != null) {
		  for (int j = 0; j < soapbodies.size(); j++) {
			  if (soapbodies.get(j)
				  instanceof javax.wsdl.extensions.soap.SOAPBody) {
				  return  ((javax.wsdl.extensions.soap.SOAPBody) soapbodies
						  .get(j))
						  .getEncodingStyles();
			  }
		  }
	  }
	  return null;
	}
	public static List getOutputEncodingStype(BindingOutput input){
	  if (input == null)
			return null;
	  List soapbodies = input.getExtensibilityElements();

	  if (soapbodies != null) {
		  for (int j = 0; j < soapbodies.size(); j++) {
			  if (soapbodies.get(j)
				  instanceof javax.wsdl.extensions.soap.SOAPBody) {
				  return  ((javax.wsdl.extensions.soap.SOAPBody) soapbodies
						  .get(j))
						  .getEncodingStyles();
			  }
		  }
	  }
	  return null;
	}

}
