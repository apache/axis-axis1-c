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

package org.apache.axis.wsdl.wsdl2ws;

import java.util.Iterator;
import java.util.List;

import javax.wsdl.Binding;
import javax.wsdl.BindingInput;
import javax.wsdl.BindingOperation;
import javax.wsdl.BindingOutput;
import javax.wsdl.Port;
import javax.wsdl.extensions.soap.SOAPOperation;

import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;

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
	public static List getInputInfo(BindingInput input,MethodInfo methodinfo){
	  if (input == null)
			return null;
	  List soapbodies = input.getExtensibilityElements();

	  if (soapbodies != null) {
		  for (int j = 0; j < soapbodies.size(); j++) {
			  if (soapbodies.get(j)
				  instanceof javax.wsdl.extensions.soap.SOAPBody) {
					javax.wsdl.extensions.soap.SOAPBody body =
						 ((javax.wsdl.extensions.soap.SOAPBody) soapbodies
						  .get(j));
					methodinfo.setInputEncoding(body.getEncodingStyles());
					methodinfo.setInputUse(body.getUse());
			  }
		  }
	  }
	  return null;
	}
	public static List getOutputInfo(BindingOutput input,MethodInfo methodinfo){
	  if (input == null)
			return null;
	  List soapbodies = input.getExtensibilityElements();

	  if (soapbodies != null) {
		  for (int j = 0; j < soapbodies.size(); j++) {
			  if (soapbodies.get(j)
				  instanceof javax.wsdl.extensions.soap.SOAPBody) {
					javax.wsdl.extensions.soap.SOAPBody body =
						 ((javax.wsdl.extensions.soap.SOAPBody) soapbodies
						  .get(j));
					methodinfo.setInputEncoding(body.getEncodingStyles());
					methodinfo.setInputUse(body.getUse());
			  }
		  }
	  }
	  return null;
	}

}
