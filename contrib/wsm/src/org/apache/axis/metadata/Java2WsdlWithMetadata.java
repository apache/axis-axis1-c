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
import javax.jws.*;
import javax.jws.soap.*;
import java.lang.reflect.*;

/**
 * @author Ias
 *
 */
public class Java2WsdlWithMetadata extends org.apache.axis.wsdl.Java2WSDL {

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
			
			Class<?> serviceEndpointInterface = emitter.getCls();
			
            WebService webServiceAnnotation = serviceEndpointInterface.getAnnotation(WebService.class); 
			String targetNamespace = webServiceAnnotation.targetNamespace();
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
			
			SOAPBinding soapBindingAnnotation = serviceEndpointInterface.getAnnotation(SOAPBinding.class);
			
            SOAPBinding.Style style = soapBindingAnnotation.style();
			switch (style) {
				case DOCUMENT:
					emitter.setStyle("document");
					break;
				case RPC:
					emitter.setStyle("rpc");
					break;
				case DEFAULT:
					emitter.setStyle("document");
					break;
				default:
                    emitter.setStyle("document");
			}
 			
            SOAPBinding.Use use = soapBindingAnnotation.use();
            switch (use) {
                case LITERAL:
                    emitter.setUse("literal");
                    break;
                case ENCODED:
                    emitter.setUse("encoded");
                    break;
                case DEFAULT:
                    emitter.setUse("literal");
                    break;
                default:
                    emitter.setUse("literal");
            }

            Vector allowedMethods = new Vector();
			Method[] methods = serviceEndpointInterface.getMethods();
			for (Method method : methods) {
				if (method.isAnnotationPresent(WebMethod.class)) {
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
