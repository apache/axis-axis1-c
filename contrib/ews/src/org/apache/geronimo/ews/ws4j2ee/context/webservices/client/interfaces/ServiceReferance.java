package org.apache.geronimo.ews.ws4j2ee.context.webservices.client.interfaces;

import javax.xml.namespace.QName;

import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFHandler;

/**
 * This class represent the service-ref element as define by the j2ee webserice 
 * client schema. this elemet may in the web.xml or ejb-jar.xml.   
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public interface ServiceReferance {
	/**
	 * Service type: The service-interface element defines the
	 * fully qualified name of the JAXRPC Service Interface class
	 * returned by the JNDI lookup.
	 */
	
	public void setServiceInterface(String string);
	public String getServiceInterface();

	/**
	 * WSDL definition (optional). The wsdl-file element specifies a
	 * location of the WSDL description of the service. The location
	 * is relative to the root of the module. The WSDL description may
	 * be a partial WSDL, but must at least include the portType and
	 * binding elements. The WSDL description provided by the developer
	 * is considered a template that must be preserved by the
	 * assembly/deployment process. In other words, the WSDL description contains
	 * a declaration of the application’s dependency on portTypes, bindings, and QNames.
	 * The WSDL document must be fully specified, including the service and port elements,
	 * if the application is dependent on port QNames
	 * 	(e.g. uses the Service.getPort(QName,Class) method). The developer must
	 * 	specify the wsdl-file if any of the Service methods declared
	 * in section 4.2.2.4 or 4.2.2.5 are used 
	 */
	public String getWsdlFile();
	public void setWsdlFile(String string);
	
	/**
	 * Service Port. If the specified wsdl-file has more than
	 *  one service element, the developer must specify the service-qname.
	 */
	public void setServcieQName(QName name);
	public QName getServcieQName();

	/**
	 * JAX-RPC Mapping. The developer specifies the correlation 
	 * of the WSDL definition to the interfaces using the jaxrpc-mapping-file element. 
	 * The location is relative to the root of the module. The same mapping file must 
	 * be used for all interfaces associated with a wsdl-file. The developer must 
	 * specify the jaxrpc-mapping-file if the wsdl-file is specified.
	 */
	public String getJaxrpcmappingFile();
	public void setJaxrpcmappingFile(String string);
	/**
	 * Service Reference Name. This defines a logical name for the 
	 * reference that is used in the client source code. It is recommended,
	 * but not required that the name begin with service/*.
	 */
	public String getServicerefName();
	public void setServicerefName(String string);
	
	public WSCFHandler[] getHandlers();
	public void addHandler(WSCFHandler handler);
}
