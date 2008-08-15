/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

package org.apache.axis.wsdl.wsdl2ws.info;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;

import javax.wsdl.Binding;
import javax.wsdl.BindingInput;
import javax.wsdl.BindingOperation;
import javax.wsdl.BindingOutput;
import javax.wsdl.Port;
import javax.wsdl.Service;
import javax.wsdl.WSDLElement;
import javax.wsdl.extensions.soap.SOAPBinding;
import javax.wsdl.extensions.soap.SOAPOperation;
import javax.wsdl.extensions.soap.SOAPAddress;

import org.apache.axis.Constants;
import org.apache.axis.wsdl.gen.Parser;
import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.axis.wsdl.symbolTable.SymTabEntry;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;


/**
 * This class initiates the collection of various bits of information needed by the 
 * wsdl2ws tool by parsing the WSDL file.
 * 
 * @author nadir amra
 *
 */
public class WSDLInfo
{
    // Private constants for retrieving extensibility elements.
    private static final int INSTANCEOF_SOAPBINDING   = 1;
    private static final int INSTANCEOF_SOAPADDRESS   = 2;
    private static final int INSTANCEOF_SOAPBODY      = 3;
    private static final int INSTANCEOF_SOAPOPERATION = 4;



    // verbose flag 
    private boolean c_verbose = false;
    
    // parser timeout value, in seconds. 0=no timeout. 
    private long c_timeout = 0;
    
    // URI to WSDL document. 
    private String c_URIToWSDLDocument = null;
    
    // Whether wrapper-style is not requested. 
    private boolean c_noWrapperStyle = false;
    
    // WSDL parser from the last time parse() was invoked. 
    private Parser c_wsdlParser = null;
    
    // Symbol table associated with the parser.
    private SymbolTable c_symbolTable = null;
    
    // Target name space of WSDL 
    private String c_targetNameSpaceOfWSDL = null;
    
    // Service definitions in WSDL 
    ArrayList c_services = new ArrayList();
    
    // Maps service definition to set of ports that use RPC binding style 
    ArrayList c_bindings = new ArrayList();
    
    
    /**
     * Constructor.
     */
    public WSDLInfo(String uri)
    {
        c_URIToWSDLDocument = uri;
    }
    
    /**
     * Initiates the parsing of the WSDL document. Returns the symbol table that is generated
     * by the parser. After parsing the WSDL document, various artifacts that the wsdl2ws tool needs
     * is collected for easy access.  
     * 
     * @throws Exception 
     */
    public SymbolTable parse() throws Exception
    {
        c_wsdlParser = new Parser();
        
        // Set verbose in WSDL parser
        c_wsdlParser.setVerbose(c_verbose);
        
        // Set timeout for parser, setTimeout method expects the time in milliseconds.
        c_wsdlParser.setTimeout(c_timeout*1000); 
        
        // Set unwrapped if requested
        c_wsdlParser.setNowrap(c_noWrapperStyle);

        // Parse the WSDL document.
        c_wsdlParser.run(c_URIToWSDLDocument);
        c_symbolTable =  c_wsdlParser.getSymbolTable();
        
        // Dump symbol table if in verbose mode.
        if (c_verbose)
            c_symbolTable.dump(System.out);
        
        // Collect various bits of information from the document.
        processWSDLDocument();

        // Return the symbol table
        return c_symbolTable;
    }

    /**
     * Sets the WSDL parser timeout value. 
     * 
     * @param t  timeout value in seconds. Null implies 0 timeout (no timeout).
     */
    public void setTimeout(String t)
    {
        if (t == null)
            t = "0"; 
        
        c_timeout = Long.parseLong(t);
    }
    
    /**
     * Sets the WSDL parser verbose mode. 
     * 
     * @param b  true=verbose; false=no verbose.
     */
    public void setVerbose(boolean b)
    {
        c_verbose = b;
    }
    
    /**
     * Indicates whether wrapper-style interfaces is allowed. 
     * 
     * @param b  true=no wrapper style; false=allow wrapper style.
     */
    public void setNoWrapperStyle(boolean b)
    {
        c_noWrapperStyle = b;
    }

    /**
     * Returns target name space of WSDL.
     * 
     * @return String representing the target name space of WSDL.
     */
    public String getTargetNameSpaceOfWSDL()
    {
        return c_targetNameSpaceOfWSDL;
    }

    /**
     * Returns array of services defined in WSDL.  The array
     * may be empty if service was not defined in WSDL.
     * 
     * @return array of java.wsdl.Service objects.
     */
    public ArrayList getServices()
    {
        return c_services;
    }
    
    /**
     * Returns end point URI for a Port by looking for the soap:address extensibility element.
     * 
     * @param port
     * @return
     */
    public static String getTargetEndPointURI(Port port)
    {
        SOAPAddress e = (SOAPAddress)getExtensibilityElement(port, INSTANCEOF_SOAPADDRESS);
        if (e != null)
            return e.getLocationURI();
        return null;
    }

    /**
     * Returns the transport URI in a soap:binding element.
     * 
     * @param binding
     * @return
     */
    public static String getTransportType(Binding binding)
    {
        SOAPBinding e = (SOAPBinding)getExtensibilityElement(binding, INSTANCEOF_SOAPBINDING);
        if (e != null)
            return e.getTransportURI();
        return null;
    }

    /**
     * Returns the URI for SoapAction if it exists.
     * 
     * @param bindingOperation
     * @return
     */
    public static String getSoapAction(BindingOperation bindingOperation)
    {
        SOAPOperation e = (SOAPOperation)getExtensibilityElement(bindingOperation, INSTANCEOF_SOAPOPERATION);
        if (e != null)
            return e.getSoapActionURI();
        return null;
    }

    public static void getInputInfo(BindingInput input, MethodInfo methodinfo)
    {
        if (input == null)
            return;
        List soapbodies = input.getExtensibilityElements();

        if (soapbodies != null)
        {
            for (int j = 0; j < soapbodies.size(); j++)
            {
                if (soapbodies.get(j) instanceof javax.wsdl.extensions.soap.SOAPBody)
                {
                    javax.wsdl.extensions.soap.SOAPBody body = ((javax.wsdl.extensions.soap.SOAPBody) soapbodies.get(j));
                    methodinfo.setInputEncoding(body.getEncodingStyles());
                    methodinfo.setInputUse(body.getUse());
                    methodinfo.setInputNamespaceURI(body.getNamespaceURI());
                }
            }
        }
    }

    public static void getOutputInfo(BindingOutput input, MethodInfo methodinfo)
    {
        if (input == null)
            return;
        List soapbodies = input.getExtensibilityElements();

        if (soapbodies != null)
        {
            for (int j = 0; j < soapbodies.size(); j++)
            {
                if (soapbodies.get(j) instanceof javax.wsdl.extensions.soap.SOAPBody)
                {
                    javax.wsdl.extensions.soap.SOAPBody body = ((javax.wsdl.extensions.soap.SOAPBody) soapbodies.get(j));
                    methodinfo.setInputEncoding(body.getEncodingStyles());
                    methodinfo.setInputUse(body.getUse());
                    methodinfo.setOutputNamespaceURI(body.getNamespaceURI());
                }
            }
        }
    }
    
    /**
     * Returns list of Port objects in the specified service.  All ports in the list 
     * will have a binding style of document and uses the SOAP 1.1 binding. 
     * 
     * @param s service definition
     * @return list of ports that match the criteria described above.
     * @throws Exception
     */
    public ArrayList getPortsSOAP11Document(Service s) throws Exception
    {
        return getServicePorts(s, true, true, false, false);
    }
    
    /**
     * Returns list of Port objects in the specified service.  All ports in the list 
     * will have a binding style of rpc and uses the SOAP 1.1 binding. 
     * 
     * @param s service definition
     * @return list of ports that match the criteria described above.
     * @throws Exception
     */
    public ArrayList getPortsSOAP11RPC(Service s) throws Exception
    {
        return getServicePorts(s, false, true, false, false);
    }
    
    /**
     * Returns list of Port objects in the specified service.  All ports in the list 
     * will have a binding style of document and uses the SOAP 1.2 binding. 
     * 
     * @param s service definition
     * @return list of ports that match the criteria described above.
     * @throws Exception
     */
    public ArrayList getPortsSOAP12Document(Service s) throws Exception
    {
        return getServicePorts(s, true, false, true, false);
    }
    
    /**
     * Returns list of Port objects in the specified service.  All ports in the list 
     * will have a binding style of rpc and uses the SOAP 1.2 binding. 
     * 
     * @param s service definition
     * @return list of ports that match the criteria described above.
     * @throws Exception
     */
    public ArrayList getPortsSOAP12RPC(Service s) throws Exception
    {
        return getServicePorts(s, false, false, true, false);
    }
    
    /**
     * Returns list of Port objects in the specified service.  All ports in the list 
     * uses the HTTP binding. 
     * 
     * @param s
     * @param styleDocument
     * @return
     * @throws Exception
     */
    public ArrayList getPortsREST(Service s) throws Exception
    {
        return getServicePorts(s, true, false, false, true);
    }

    /**
     * Returns list of Port objects in a service definition based on selection criteria.
     * 
     * @param s              service definition.
     * @param styleDocument  true=return document style; false=return "rpc" style. 
     *                       This parameter is ignored for REST (HTTP) bindings.
     * @param soap11         true=return SOAP 1.1 bindings; false=SOAP 1.1 bindings are ignored.
     * @param soap12         true=return SOAP 1.2 bindings; false=SOAP 1.2 bindings are ignored.
     * @param rest           true=return HTTP bindings; false=ignore HTTP bindings.
     * @return               List of ports that match selection criteria.
     * @throws Exception
     */
    private ArrayList getServicePorts(Service s, 
                                      boolean styleDocument, 
                                      boolean soap11, 
                                      boolean soap12, 
                                      boolean rest) throws Exception
    {        
        ArrayList a = new ArrayList();
        
        if (s == null)
            return a;

        Iterator ports = s.getPorts().values().iterator();
        while (ports.hasNext())
        {
            Port p = (Port) ports.next();
            Binding b = p.getBinding();
            BindingEntry be = c_symbolTable.getBindingEntry(b.getQName());
            if (b == null || be == null)
                throw new WrapperFault("No binding exists for port '" + p.getName() + "'.");
            
            if ((be.getBindingType() == BindingEntry.TYPE_SOAP) && (soap11 || soap12))
            {
                String style = be.getBindingStyle().getName();
                if (style == null)
                    style = "rpc"; // TODO need to revisit.
                
                if ((styleDocument && style.equalsIgnoreCase("document"))
                        || (!styleDocument && style.equalsIgnoreCase("rpc")))
                {
                    String ns = Constants.URI_WSDL11_SOAP;
                    SOAPBinding soapbinding = (SOAPBinding)getExtensibilityElement(b, INSTANCEOF_SOAPBINDING);
                    if (soapbinding != null && null != soapbinding.getElementType().getNamespaceURI())
                        ns = soapbinding.getElementType().getNamespaceURI();
                        
                    if ((soap11 && ns.equals(Constants.URI_WSDL11_SOAP))
                            || (soap12 && ns.equals(Constants.URI_WSDL12_SOAP)))
                            a.add(p);
                }
            }
            else if (rest && (be.getBindingType() == BindingEntry.TYPE_HTTP_GET 
                                || be.getBindingType() == BindingEntry.TYPE_HTTP_POST))
            {
                a.add(p);
            }
        }
        
        return a;
    }
    
    /**
     * Collects all the information by the wsdl2ws tool.
     */
    private void processWSDLDocument() throws Exception
    {        
        // Get target name space of WSDL
        c_targetNameSpaceOfWSDL = c_symbolTable.getDefinition().getTargetNamespace();

        // Collect services and bindings.           
        Iterator it = c_symbolTable.getHashMap().values().iterator();
        while (it.hasNext())
        {
            Vector v = (Vector) it.next();
            for (int i = 0; i < v.size(); ++i)
            {
                SymTabEntry entry = (SymTabEntry) v.elementAt(i);

                if (entry instanceof org.apache.axis.wsdl.symbolTable.ServiceEntry)
                    c_services.add(((ServiceEntry) entry).getService());
                else if (entry instanceof org.apache.axis.wsdl.symbolTable.BindingEntry)
                    c_bindings.add(entry);
            }
        }
    }
    
    /**
     * Helper function that returns requested extensibility element.
     * 
     * @param e element to retrieve extensibility elements from.
     * @param clazz instance of class
     * @return extensibility element.
     */
    private static Object getExtensibilityElement(WSDLElement e, int clazz)
    {
        if (e != null)
        {
            List extElems = e.getExtensibilityElements();
            if (extElems != null)
            {
                Iterator it = extElems.iterator();
                
                while (it.hasNext())
                {
                    Object o = it.next();
                    if ((clazz == INSTANCEOF_SOAPBINDING && (o instanceof javax.wsdl.extensions.soap.SOAPBinding))
                       || (clazz == INSTANCEOF_SOAPADDRESS && (o instanceof javax.wsdl.extensions.soap.SOAPAddress))
                       || (clazz == INSTANCEOF_SOAPOPERATION && (o instanceof javax.wsdl.extensions.soap.SOAPOperation))
                       || (clazz == INSTANCEOF_SOAPBODY && (o instanceof javax.wsdl.extensions.soap.SOAPBody)))
                        return o;
                }
            }
        }
        
        return null;
    }
}
