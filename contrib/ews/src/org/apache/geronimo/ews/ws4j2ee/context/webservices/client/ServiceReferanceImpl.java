package org.apache.geronimo.ews.ws4j2ee.context.webservices.client;

import java.util.Vector;

import javax.xml.namespace.QName;

import org.apache.geronimo.ews.ws4j2ee.context.webservices.client.interfaces.ServiceReferance;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFHandler;

/**
 * @see org.apache.geronimo.ews.ws4j2ee.context.webservices.client.interfaces.ServiceReferance;
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class ServiceReferanceImpl implements ServiceReferance{
		/**
		 * Service Reference Name. This defines a logical name for the 
		 * reference that is used in the client source code. It is recommended,
		 * but not required that the name begin with service/*.
		 */ 
		private String servicerefName;
		/**
		 * Service type: The service-interface element defines the
		 * fully qualified name of the JAXRPC Service Interface class
		 * returned by the JNDI lookup.
		 */
		private String serviceInterface;
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
		private String wsdlFile;
	
		private String sei;
		/**
		 * Service Port. If the specified wsdl-file has more than
		 *  one service element, the developer must specify the service-qname.
		 */
		private QName servcieQName;
		/**
		 * Ports. The developer declares requirements for container 
		 * managed port resolution using the portcomponent-ref element. 
		 * The port-component-ref elements are resolved to a WSDLport by 
		 * the container. See Chapter 4 for a discussion of container 
		 * managed port access.
		 */
		private String portComponetlink;
		/**
		 * JAX-RPC Mapping. The developer specifies the correlation 
		 * of the WSDL definition to the interfaces using the jaxrpc-mapping-file element. 
		 * The location is relative to the root of the module. The same mapping file must 
		 * be used for all interfaces associated with a wsdl-file. The developer must 
		 * specify the jaxrpc-mapping-file if the wsdl-file is specified.
		 */
		 private String jaxrpcmappingFile;
		 /**
		  * Handlers. A developer may optionally specify handlers associated with the 
		  * service-ref using the handler element.
		  */
		private Vector handlers = new Vector(); 

		/**
		 * @return
		 */
		public String getJaxrpcmappingFile() {
			return jaxrpcmappingFile;
		}

		/**
		 * @return
		 */
		public QName getServcieQName() {
			return servcieQName;
		}

		/**
		 * @return
		 */
		public String getServiceInterface() {
			return serviceInterface;
		}

		/**
		 * @return
		 */
		public String getServicerefName() {
			return servicerefName;
		}

		/**
		 * @return
		 */
		public String getWsdlFile() {
			return wsdlFile;
		}

		/**
		 * @param string
		 */
		public void setJaxrpcmappingFile(String string) {
			jaxrpcmappingFile = string;
		}

		/**
		 * @param name
		 */
		public void setServcieQName(QName name) {
			servcieQName = name;
		}

		/**
		 * @param string
		 */
		public void setServiceInterface(String string) {
			serviceInterface = string;
		}

		/**
		 * @param string
		 */
		public void setServicerefName(String string) {
			servicerefName = string;
		}

		/**
		 * @param string
		 */
		public void setWsdlFile(String string) {
			wsdlFile = string;
		}

	/* (non-Javadoc)
	 * @see org.apache.geronimo.ews.ws4j2ee.context.webservices.client.interfaces.ServiceReferance#addHandler(org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFHandler)
	 */
	public void addHandler(WSCFHandler handler) {
		this.handlers.add(handler);

	}

	/* (non-Javadoc)
	 * @see org.apache.geronimo.ews.ws4j2ee.context.webservices.client.interfaces.ServiceReferance#getHandlers()
	 */
	public WSCFHandler[] getHandlers() {
		WSCFHandler[] wscfhandlers = new WSCFHandler[handlers.size()];
		for(int i = 0;i<wscfhandlers.length;i++){
			wscfhandlers[i] = (WSCFHandler)handlers.get(i);
		}
		return wscfhandlers;
	}

}
