/*
 * Created on 2004. 1. 11.
 *
 */
package org.apache.axis.metadata;

import java.math.*;
import javax.xml.bind.*;
import org.apache.axis.jaxrpcmapping.descriptor.*;
import java.io.*;
import org.apache.axis.metadata.annotation.*;

/**
 * @author Ias
 *
 */
public class JaxRpcMappingGenerator {
    public static void main(java.lang.String[] args) throws Exception {
        java.lang.String className = args[0];
        Class serviceEndpointInterface = Class.forName(className);
        JAXBContext jc = null;
        try {
        	jc = JAXBContext.newInstance("org.apache.axis.jaxrpcmapping.descriptor");
        } catch (JAXBException e1) {
        	e1.printStackTrace();
        }
        Marshaller m = null;
        try {
        	m = jc.createMarshaller();
        } catch (JAXBException e) {
        	e.printStackTrace();
        }
        try {
        	ObjectFactory objFactory = new ObjectFactory();
        	JavaWsdlMapping mapping = objFactory.createJavaWsdlMapping();
        	PackageMappingType packageMapping = objFactory.createPackageMappingType();
			FullyQualifiedClassType packageType = objFactory.createFullyQualifiedClassType();
            Package javaPackage = serviceEndpointInterface.getPackage();
            java.lang.String javaPackageName = null;
            if (javaPackage == null) {
                javaPackageName = "";
            } else {
                javaPackageName = javaPackage.getName();
            }
            
			packageType.setValue(javaPackageName);
			XsdAnyURIType uri = objFactory.createXsdAnyURIType();
			uri.setValue(
						(
								(TargetNamespace) serviceEndpointInterface.getAnnotation(TargetNamespace.class)
						).value()
					);
			packageMapping.setNamespaceURI(uri);
			packageMapping.setPackageType(packageType);
			java.util.List packageList = mapping.getPackageMapping();
			packageList.add(packageMapping);
			mapping.setVersion(new BigDecimal("1.0"));
			m.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, Boolean.TRUE);
        	m.marshal(mapping, System.out);
        } catch (JAXBException e2) {
        	e2.printStackTrace();
        }
    }
}
