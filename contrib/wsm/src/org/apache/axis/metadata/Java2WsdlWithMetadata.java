/*
 * Created on 2004. 1. 12.
 *
 */
package org.apache.axis.metadata;

import java.util.*;

import org.apache.axis.encoding.DefaultTypeMappingImpl;
import org.apache.axis.utils.CLArgsParser;
import org.apache.axis.utils.CLOption;
import org.apache.axis.utils.Messages;
import org.apache.axis.wsdl.fromJava.Emitter;
import org.apache.axis.metadata.annotation.*;
import java.lang.reflect.*;

/**
 * @author Ias
 *
 */
public class Java2WsdlWithMetadata extends org.apache.axis.wsdl.Java2WSDL {

	protected boolean locationSet;
	
	/**
	 * validateOptions
	 * This method is invoked after the options are set to validate
	 * the option settings.
	 * 
	 * @return 
	 */
	protected boolean validateOptions() {

		// Can't proceed without a class name
		if ((className == null)) {
			System.out.println(Messages.getMessage("j2wMissingClass00"));
			printUsage();

			return false;
		}
		if (!locationSet
				&& ((mode == Emitter.MODE_ALL)
				|| (mode == Emitter.MODE_IMPLEMENTATION))) {
			System.out.println(Messages.getMessage("j2wMissingLocation00"));
			printUsage();

			return false;
		}
		
		// Default to SOAP 1.2 JAX-RPC mapping
		if (emitter.getDefaultTypeMapping() == null) {
			emitter.setDefaultTypeMapping(
					DefaultTypeMappingImpl.getSingleton());
		}

		return true;    // a-OK
	}

	public static void main(String args[]) {

		Java2WsdlWithMetadata java2wsdl = new Java2WsdlWithMetadata();

		System.exit(java2wsdl.run(args));
	}
	
	protected int run(String[] args) {

		// Parse the arguments
		CLArgsParser argsParser = new CLArgsParser(args, options);

		// Print parser errors, if any
		if (null != argsParser.getErrorString()) {
			System.err.println(
					Messages.getMessage("j2werror00", argsParser.getErrorString()));
			printUsage();

			return (1);
		}

		// Get a list of parsed options
		List clOptions = argsParser.getArguments();
		int size = clOptions.size();
		try {

			// Parse the options and configure the emitter as appropriate.
			for (int i = 0; i < size; i++) {
				if (parseOption((CLOption) clOptions.get(i)) == false) {
					return (1);
				}
			}

			// Find the class using the name
			emitter.setCls(className);
			
			Class serviceEndpointInterface = emitter.getCls();
			
			String targetNamespace = 
			(
			(TargetNamespace) serviceEndpointInterface.getAnnotation(TargetNamespace.class)
			).value();
			if (targetNamespace != null) {
                Package javaPackage = serviceEndpointInterface.getPackage();
                java.lang.String javaPackageName = null;
                if (javaPackage == null) {
                    javaPackageName = "";
                } else {
                    javaPackageName = javaPackage.getName();
                }
                namespaceMap.put(javaPackageName, targetNamespace);
			}
			
			String wsdlFile =  
				(
						(WsdlFile) serviceEndpointInterface.getAnnotation(WsdlFile.class)
				).value();
			if (wsdlFile != null) {
				wsdlFilename = wsdlFile;
			}

			String serviceLocation = 
			(
					(ServiceLocation) serviceEndpointInterface.getAnnotation(ServiceLocation.class)
			).value();
			if (serviceLocation != null) {
				emitter.setLocationUrl(serviceLocation);
				locationSet = true;
			}
			EncodingType style = 
			(
					(Protocol) serviceEndpointInterface.getAnnotation(Protocol.class)
			).soapStyle();
			
			// Currently the following commented-out block doesn't work.
			// This block works from Tiger beta 2 b38.
			
			/*
			switch (style) {
				case documentLiteral:
					emitter.setStyle("document");
					emitter.setUse("literal");
					break;
				case rpcLiteral:
					emitter.setStyle("rpc");
					emitter.setUse("literal");
					break;
				case soapEncoded:
					emitter.setStyle("rpc");
					emitter.setUse("encoded");
					break;
				default:
			}
			*/
			
			if (style == EncodingType.documentLiteral) {
				emitter.setStyle("document");
				emitter.setUse("literal");
			} else if (style == EncodingType.rpcLiteral) {
				emitter.setStyle("rpc");
				emitter.setUse("literal");
			} else if (style == EncodingType.soapEncoded) {
				emitter.setStyle("rpc");
				emitter.setUse("encoded");
			}
 			
			Vector allowedMethods = new Vector();
			Method[] methods = serviceEndpointInterface.getMethods();
			for (Method method : methods) {
				if (method.isAnnotationPresent(Operation.class)) {
					allowedMethods.add(method.getName());
				}
			}
			
			if (!allowedMethods.isEmpty()) {
				emitter.setAllowedMethods(allowedMethods);
			}
			// Set the namespace map
			if (!namespaceMap.isEmpty()) {
				emitter.setNamespaceMap(namespaceMap);
			}

			// validate argument combinations
			if (validateOptions() == false) {
				return (1);
			}

			// Generate a full wsdl, or interface & implementation wsdls
			if (wsdlImplFilename == null) {
				emitter.emit(wsdlFilename, mode);
			} else {
				emitter.emit(wsdlFilename, wsdlImplFilename);
			}

			// everything is good
			return (0);
		} catch (Throwable t) {
			t.printStackTrace();

			return (1);
		}
	}    // run
	
}
