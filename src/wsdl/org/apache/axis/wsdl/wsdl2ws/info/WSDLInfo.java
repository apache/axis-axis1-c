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
import javax.wsdl.extensions.soap.SOAPOperation;

import org.apache.axis.wsdl.gen.Parser;
import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.axis.wsdl.symbolTable.SymTabEntry;
import org.apache.axis.wsdl.symbolTable.SymbolTable;


/**
 * This class initiates the collection of various bits of information needed by the 
 * wsdl2ws tool by parsing the WSDL file.
 * 
 * @author nadir amra
 *
 */
public class WSDLInfo
{
    /** verbose flag */
    private boolean c_verbose = false;
    
    /** parser timeout value, in seconds. 0=no timeout. */
    private long c_timeout = 0;
    
    /** URI to WSDL document. */
    private String c_URIToWSDLDocument = null;
    
    /** Whether wrapper-style is not requested. */
    private boolean c_noWrapperStyle = false;
    
    /** WSDL parser from the last time parse() was invoked. */
    private Parser c_wsdlParser = null;
    
    /** Target name space of WSDL */
    private String c_targetNameSpaceOfWSDL = null;
    
    /** Service definitions in WSDL */
    ArrayList c_services = new ArrayList();
    
    /** Bindings in WSDL */
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
        
        // Dump symbol table if in verbose mode.
        if (c_verbose)
            c_wsdlParser.getSymbolTable().dump(System.out);
        
        // Collect various bits of information from the document.
        processWSDLDocument();

        // Return the symbol table
        return c_wsdlParser.getSymbolTable();
    }

    /**
     * Collects all the information by the wsdl2ws tool.
     */
    private void processWSDLDocument() throws Exception
    {
        SymbolTable symbolTable =  c_wsdlParser.getSymbolTable();
        
        // Get target name space of WSDL
        c_targetNameSpaceOfWSDL = symbolTable.getDefinition().getTargetNamespace();

        // ==================================================
        // Collect services and bindings.   
        // ==================================================                
        
        Iterator it = symbolTable.getHashMap().values().iterator();
        while (it.hasNext())
        {
            Vector v = (Vector) it.next();
            for (int i = 0; i < v.size(); ++i)
            {
                SymTabEntry entry = (SymTabEntry) v.elementAt(i);

                if (entry instanceof ServiceEntry)
                {
                    c_services.add(((ServiceEntry) entry).getService());
                }
                else if (entry instanceof BindingEntry)
                {
                    // Currently we are only interested in SOAP bindings.
                    BindingEntry be = (BindingEntry)entry;
                    if (be.getBindingType() == BindingEntry.TYPE_SOAP)
                        c_bindings.add(entry);
                }
            }
        }
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
    
    public static String getTargetEndPointURI(Iterator ports)
    {
        // we are checking only the first port.
        // if the targetEndPointURI not specifed we continue having it null
        // The WrapperInfo will set a default value for the targetEndPointURI

        if (ports.hasNext())
        {
            Port port = (Port) ports.next();
            List adresslist = port.getExtensibilityElements();
            if (adresslist != null
                    && adresslist.size() != 0
                    && (adresslist.get(0) instanceof javax.wsdl.extensions.soap.SOAPAddress))
                return ((javax.wsdl.extensions.soap.SOAPAddress) adresslist.get(0))
                        .getLocationURI();
        }
        return null;
    }

    public static String getTransportType(Binding binding)
    {
        List soapbinding = binding.getExtensibilityElements();
        if (soapbinding != null
                && soapbinding.size() > 0
                && (soapbinding.get(0) instanceof javax.wsdl.extensions.soap.SOAPBinding))
            return ((javax.wsdl.extensions.soap.SOAPBinding) soapbinding.get(0)).getTransportURI();
        return null;
    }

    public static String getSoapAction(BindingOperation bindingOperation)
    {
        List extenstions = bindingOperation.getExtensibilityElements();
        for (int i = 0; i < extenstions.size(); i++)
        {
            if (extenstions.get(i) instanceof SOAPOperation)
                return ((SOAPOperation) extenstions.get(i)).getSoapActionURI();
        }
        return null;
    }

    public static List getInputInfo(BindingInput input, MethodInfo methodinfo)
    {
        if (input == null)
            return null;
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
        return null;
    }

    public static List getOutputInfo(BindingOutput input, MethodInfo methodinfo)
    {
        if (input == null)
            return null;
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
        return null;
    }
}
