package org.apache.axis.components.wsil;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.wsil.Abstract;
import org.apache.wsil.Description;
import org.apache.wsil.Service;
import org.apache.wsil.ServiceName;
import org.apache.wsil.WSILDocument;
import org.apache.wsil.WSILDocumentFactory;
import org.apache.wsil.WSILException;
import org.apache.wsil.extension.wsdl.Reference;
import org.apache.wsil.extension.wsdl.WSDLConstants;
import org.apache.wsil.impl.extension.wsdl.WSDLExtensionBuilder;
import org.apache.wsil.xml.XMLWriter;
import org.apache.axis.AxisEngine;
import org.apache.axis.AxisFault;
import org.apache.axis.ConfigurationException;
import org.apache.axis.EngineConfiguration;
import org.apache.axis.configuration.EngineConfigurationFactoryFinder;

import org.apache.axis.description.ServiceDesc;
import org.apache.axis.server.AxisServer;

/**
 * Generates a WS-Inspection document from the collection
 * of services deployed into the Axis server.
 * 
 * @author James M Snell <jasnell@us.ibm.com>
 */
public class InspectionServlet
  extends HttpServlet {
  
  private AxisServer axisServer;
  protected static final String ATTR_AXIS_ENGINE =
      "AxisEngine" ;
  
  protected void doGet(
    HttpServletRequest request, 
    HttpServletResponse response)
      throws ServletException, IOException {
        try {
          WSILDocument document = generateWSILDocument();
          XMLWriter writer = new XMLWriter();
          writer.writeDocument(document, response.getOutputStream());
        } catch (WSILException e) {
          throw new ServletException(e);
        } catch (AxisFault e) {
          throw new ServletException(e);
        } catch (ConfigurationException e) {
          throw new ServletException(e);
        }
  }

  private WSILDocument generateWSILDocument() 
    throws WSILException, AxisFault, ConfigurationException {
    
      WSILDocumentFactory factory = WSILDocumentFactory.newInstance();
      WSILDocument document = factory.newDocument();
    
      Abstract inspectionAbstract = document.createAbstract();
      inspectionAbstract.setText("Apache Axis Deployed Services");
      document.getInspection().addAbstract(inspectionAbstract);
    
      AxisServer server = getEngine();
      for (
        Iterator i = getEngine().getConfig().getDeployedServices(); 
        i.hasNext();) {
          ServiceDesc serviceDesc = (ServiceDesc)i.next();
          
          Service wsilService = document.createService();
          ServiceName wsilServiceName = document.createServiceName();
          wsilServiceName.setText(serviceDesc.getName());
          wsilService.addServiceName(wsilServiceName);
          
          Description wsilDescription = document.createDescription();
          wsilDescription.setReferencedNamespace(
            WSDLConstants.NS_URI_WSDL);
          wsilDescription.setLocation(
            serviceDesc.getName() + "?WSDL");
            
          WSDLExtensionBuilder builder = 
            (WSDLExtensionBuilder) document.getExtensionRegistry().
                getBuilder(WSDLConstants.NS_URI_WSIL_WSDL);
          
          Reference reference = (Reference)builder.createElement(
            Reference.QNAME);
          reference.setEndpointPresent(new Boolean(true));
          
          wsilDescription.setExtensionElement(reference);
          wsilService.addDescription(wsilDescription);
          
          document.getInspection().addService(wsilService);
      }
    
      return document;
  }
  
    
  public AxisServer getEngine() throws AxisFault {
      if (axisServer == null)
          axisServer = getEngine(this);
      return axisServer;
  }

  public static AxisServer getEngine(HttpServlet servlet) throws AxisFault
  {
      AxisServer engine = null;
      ServletContext context = servlet.getServletContext();
      synchronized (context) {
          engine = retrieveEngine(context);
          if (engine == null) {
              Map environment = getEngineEnvironment(servlet);
              engine = AxisServer.getServer(environment);
              storeEngine(context, engine);
          }
      }
      return engine;
  }

  private static void storeEngine(ServletContext context, AxisServer engine) {
      if (engine == null) {
          context.removeAttribute(ATTR_AXIS_ENGINE);
      } else {
          context.setAttribute(ATTR_AXIS_ENGINE, engine);
      }
  }

  private static AxisServer retrieveEngine(ServletContext context) {
      Object contextObject = context.getAttribute(ATTR_AXIS_ENGINE);
      if (contextObject instanceof AxisServer) {
          return (AxisServer) contextObject;
      }
      else {
          return null;
      }
   }


  protected static Map getEngineEnvironment(HttpServlet servlet) {
      Map environment = new HashMap();
      String attdir= servlet.getInitParameter(AxisEngine.ENV_ATTACHMENT_DIR);
      if (attdir != null)
          environment.put(AxisEngine.ENV_ATTACHMENT_DIR, attdir);
      ServletContext context = servlet.getServletContext();
      environment.put(AxisEngine.ENV_SERVLET_CONTEXT, context);
      String webInfPath = context.getRealPath("/WEB-INF");
      if (webInfPath != null)
          environment.put(AxisEngine.ENV_SERVLET_REALPATH,
                          webInfPath + File.separator + "attachments");
      EngineConfiguration config =
          EngineConfigurationFactoryFinder.newFactory(context)
                  .getServerEngineConfig();
      if (config != null) {
          environment.put(EngineConfiguration.PROPERTY_NAME, config);
      }
      return environment;
  }
}
