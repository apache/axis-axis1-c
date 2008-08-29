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

package org.apache.axis.wsdl.wsdl2ws;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Enumeration;
import java.util.Hashtable;

import javax.wsdl.Binding;
import javax.wsdl.Port;
import javax.wsdl.Service;
import javax.xml.namespace.QName;

import org.apache.axis.wsdl.symbolTable.BaseType;
import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.DefinedType;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.wsdl2ws.info.FaultInfo;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ServiceInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.TypeMap;
import org.apache.axis.wsdl.wsdl2ws.info.WSDLInfo;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
import org.apache.axis.wsdl.wsdl2ws.info.WrapperInfo;

/**
 * This is the main class for the WSDL2Ws Tool. This class reuses the code in the 
 * Axis java implementations to parse the WSDL file. Here is what is done: 
 * 
 *  1) create a Symbol table by parsing WSDL file.
 *  2) create TypeMap object by iterating through types in the Symbol Table.
 *  3) create WrapperInfo object using command line arguments and SymbolTable information.
 *  4) create ServiceInfo object parsing the Symbol table.
 *  5) create WebServiceContext using above three classes and start execution 
 * 
 * @author hemapani@opensource.lk
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 * @author hawkeye (hawkinsj@uk.ibm.com)
 * @author nadir amra (amra@us.ibm.com)
 */
public class WSDL2Ws
{
    public static boolean c_verbose = false;

    // Command line arguments
    private CLArgParser c_cmdLineArgs = null;
            
    // WSDL parser symbol table
    private SymbolTable c_symbolTable;
    
    // WSDL info.
    private WSDLInfo c_wsdlInfo;

    /**
     * Prints out usage.
     */
    public static void usage()
    {
        System.out.println(
            "java WSDL2Ws -<options> <wsdlfile>\n"
                + "-h, -help              print this message\n"
                + "-o<folder>             target output folder - default is current folder.\n"
                + "-l<c++|c>              target language (c++|c) - default is c++.\n"
                + "-s<server|client>      target side (server|client) - default is server.\n"
                + "-v, -verbose           be verbose.\n"
                + "-t<timeout>            uri resolution timeout in seconds - default is 0 (no timeout).\n"
                + "-w<wrapped|unwrapped>  generate wrapper style or not - default is wrapped.\n"
                );
    }
    
    /**
     * Main entry point. 
     * 
     * @param args
     * @throws Exception
     */
    public static void main(String[] args) throws Exception
    {
        // Kick off code generation
        try
        {
            WSDL2Ws gen = new WSDL2Ws(args);
            gen.generateWrappers();
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.out.println("\nCode generation failed. Please see errors above.\n");
        }
    }    
    
    /**
     * Gathers the parameters passed in and parses the WSDL file, generating the symbol table. 
     * 
     * @param args
     * @throws WrapperFault
     */
    public WSDL2Ws(String[] args) throws WrapperFault
    {
        try
        {
            // ==================================================
            // Process the parameters
            // ==================================================            

            // Get parameters and validate
            c_cmdLineArgs = new CLArgParser(args);
            if (!c_cmdLineArgs.areOptionsValid() 
                    || c_cmdLineArgs.isSet("h") || c_cmdLineArgs.getArgumentCount() != 1)
            {
                usage();
                return;
            }
            
            // Verbose mode?
            c_verbose = c_cmdLineArgs.beVerbose();
            
            // language c or c++ - CUtils.setLanguage MUST be invoked at the very beginning!
            CUtils.setLanguage(c_cmdLineArgs.getTargetLanguage());
            
            // ==================================================
            // Parse the WSDL file
            // ==================================================
            
            c_wsdlInfo = new WSDLInfo(c_cmdLineArgs.getURIToWSDL());
            c_wsdlInfo.setVerbose(c_verbose);
            c_wsdlInfo.setTimeout(c_cmdLineArgs.getTimeout()); 
            c_wsdlInfo.setNoWrapperStyle(c_cmdLineArgs.isWrapperStyle() == false);

            c_symbolTable = c_wsdlInfo.parse();
            
            // ==================================================
            // Let us do some validation on the WSDL passed in.
            // ==================================================
            
            // Maximum of one <service> tag is supported in WSDL for the time being.
            if (c_wsdlInfo.getServices().size() > 1)
                throw new WrapperFault("Multiple service definitions not supported.");
            
            // TODO
            // At this time we require a service definition to be defined, but in 
            // future if not found that caller needs to specify a binding to use in 
            // order for us to generate the stubs.  Not having service definition will
            // only result in not knowing the Web service end point, so it is really not necessary.
            if (c_wsdlInfo.getServices().size() == 0)
                throw new WrapperFault("Service definition not found. A service definition must be specified.");
        }
        catch (WrapperFault e)
        {
            throw e;
        }
        catch (Exception e)
        {
            throw new WrapperFault(e);
        }
    }

    /**
     * Kicks of the generation of the stub code.
     * 
     * @throws WrapperFault
     */
    public void generateWrappers() throws Exception
    {        
        // ==================================================
        // Get service, ports, binding, and port type
        // ==================================================           
   
        //TODO  resolve this
        //  this code will generate one stub corresponding to a port.  Other ports
        //  are ignored. Should really generate one service stub per port.

        // Get service definition, binding entry, port type.  We first ask for SOAP 1.1 ports
        // that have a binding style of document....if there is none, then we ask for 
        // SOAP 1.1 ports that have a binding style of rpc.
        Service service = (Service)c_wsdlInfo.getServices().get(0);
        ArrayList servicePorts = c_wsdlInfo.getPortsSOAP11Document(service);
        if (servicePorts.isEmpty())
            servicePorts = c_wsdlInfo.getPortsSOAP11RPC(service);
        if (servicePorts.isEmpty())
            throw new WrapperFault("A port with a supported binding was not found.");

        Port port                 = (Port)servicePorts.get(0);
        Binding binding           = port.getBinding();
        BindingEntry bindingEntry = c_symbolTable.getBindingEntry(binding.getQName());
        
        // ==================================================
        // Build the context that is needed by the code generators.
        // ==================================================            
                       
        // Wrapper info
        WrapperInfo wrapperInfo = 
            new WrapperInfo(bindingEntry.getBindingStyle().getName(), 
                            CUtils.getLanguage(), 
                            c_cmdLineArgs.getOutputDirectory(), 
                            c_cmdLineArgs.getTargetEngine(),
                            c_wsdlInfo.getTargetNameSpaceOfWSDL());
        
        // Service info
        boolean userRequestedWSDLWrappingStyle = c_cmdLineArgs.isSet("w") && c_cmdLineArgs.isWrapperStyle();
        String serviceName       = WSDLInfo.getServiceName(bindingEntry);
        ArrayList serviceMethods = c_wsdlInfo.processServiceMethods(bindingEntry, 
                                                                    c_cmdLineArgs.isWrapperStyle(), 
                                                                    userRequestedWSDLWrappingStyle);
        ServiceInfo serviceInfo  = new ServiceInfo(serviceName, serviceMethods, WSDLInfo.getTargetEndPointURI(port));
        
        // Context
        WebServiceContext wsContext = new WebServiceContext(wrapperInfo, serviceInfo, c_wsdlInfo.getTypeMap()); 
        
        // Generator
        WebServiceGenerator wsg = WebServiceGeneratorFactory.createWebServiceGenerator(wsContext);
        
        // ==================================================
        // Determine which types to externalize.
        // ==================================================    
        
        // There must be a better way to do this
        exposeReferenceTypes(wsContext);
        exposeMessagePartsThatAreAnonymousTypes(wsContext);
        // This call must be last one called of the exposexxx methods!
        exposeNestedTypesThatAreAnonymousTypes(wsContext);
        
        // Dump the map if requested.
        if (c_verbose)
            c_wsdlInfo.getTypeMap().dump();
        
        // ==================================================
        // Generate the artifacts
        // ================================================== 
        
        // Generate code
        wsg.generate();
        
        // Indicate code generation complete and show where stored.
        System.out.println("\nCode generation completed. Generated files in directory '" + c_cmdLineArgs.getOutputDirectory() + "'.");
    }    
    
    // The following 3 exposeXXX methods attempts to expose anonymous types so that 
    // the types are externalized to the user.  
    
    /**
     * This method goes through the types and for any types that are referenced works out whether
     * they need to be exposed as a seperate class.
     * If they do require to be a seperate class then the name of the type will be changed from 
     * ">nameoftype" to "nameoftype". This will then get picked up later on in the process and the
     * type will be exposed as a seperate class. 
     * 
     * @param wsContext the webservice context.
     */
    private void exposeReferenceTypes(WebServiceContext wsContext)
    {
        // get the main types
        Collection types = c_symbolTable.getTypeIndex().values();
        Iterator typeIterator = types.iterator();   
        while(typeIterator.hasNext())
        {
            Object highLevelType = typeIterator.next();
            if(!(highLevelType instanceof BaseType))
            {
                DefinedType type = (DefinedType)highLevelType;
                
                if(!type.getQName().getLocalPart().toString().startsWith(">"))
                {
                    // It's not an "inner" type so look for the refs (this might not be valid 
                    // logic and refs might be acceptable for these types too !)
                    HashSet nestedTypes = type.getNestedTypes(c_symbolTable, true);
                    Iterator nestTypeIter = nestedTypes.iterator();
                    while(nestTypeIter.hasNext())
                    {
                        Object nestedType =nestTypeIter.next();
                        if(!(nestedType instanceof BaseType))
                        {
                            TypeEntry defType = (TypeEntry)nestedType;

                            TypeEntry referencedType =defType.getRefType(); 
                            if (referencedType==null)
                                continue;
                            
                            if(c_verbose)
                                System.out.println( "EXPOSE1: Checking whether to expose ref-types for "+defType.getQName().getLocalPart());

                            // If ref type is anonymous and thus currently not exposed because 
                            // it's an "inner" type, expose it and any nested types (latter is TODO).                            
                            
                            if(referencedType.getQName().getLocalPart().startsWith(">") 
                                    && referencedType.getQName().getLocalPart().lastIndexOf(">") == 0)
                            {
                                if(c_verbose)
                                    System.out.println( "EXPOSE1: Exposing ref-type "+referencedType.getQName());

                                Type innerClassType = wsContext.getTypemap().getType(referencedType.getQName());
                                
                                String newLocalPart =  new QName(defType.getQName().getLocalPart()).toString();
                                innerClassType.externalize(new QName(innerClassType.getName().getNamespaceURI(), newLocalPart));
                            }
                        }
                    }
                }
                
            }
        }
    }
    
    /**
     * This method attempts to find anonymous types in the parameter list of 
     * web-service methods to determine if the type should be exposed.
     * @param wsContext
     */
    private void exposeMessagePartsThatAreAnonymousTypes(WebServiceContext wsContext)
    {
        // get the main types
        Collection types = c_symbolTable.getTypeIndex().values();
        Iterator typeIterator = types.iterator();   
        while(typeIterator.hasNext())
        {
            Object highLevelType = typeIterator.next();
            if(!(highLevelType instanceof BaseType))
            {
                DefinedType type = (DefinedType)highLevelType;
                if(type.getQName().getLocalPart().toString().startsWith(">"))
                {
                    if(c_verbose)
                        System.out.println( "EXPOSE2: Checking whether to expose anon type "+type.getQName().getLocalPart());
                    
                    // this is an "inner" type that will not be exposed
                    // however, it needs to be if it is referenced in a message part.
                    // check all the messages
                    ArrayList methods = wsContext.getServiceInfo().getMethods();
                    for(int i=0; i<methods.size(); i++)
                    {
                          MethodInfo method = (MethodInfo)methods.get(i);
                          
                          // Check for faults that need to be externalized
                          Collection faultTypes = method.getFaultType();
                          Iterator faultIterator = faultTypes.iterator();
                          while(faultIterator.hasNext())
                          {
                              FaultInfo faultType = (FaultInfo)faultIterator.next();
                              Collection parameterTypes = faultType.getParams();
                              Iterator paramIterator = parameterTypes.iterator();
                              while(paramIterator.hasNext())
                              {
                                  ParameterInfo parameterInfo =(ParameterInfo)paramIterator.next();
                                  Type parameterType = parameterInfo.getType();

                                  if(c_verbose)
                                      System.out.println( "EXPOSE2: Exposing fault type "+parameterType.getName());
                                  externalizeTypeAndUpdateTypeMap(wsContext, parameterType);
                              }                              
                          }

                          // Check input parameters
                          Collection inputParameterTypes = method.getInputParameterTypes();
                          Iterator paramIterator = inputParameterTypes.iterator();
                          while(paramIterator.hasNext())
                          {
                              ParameterInfo parameterInfo =(ParameterInfo)paramIterator.next();
                              Type parameterType = parameterInfo.getType();
                              if(parameterType.getName().equals(type.getQName()))
                              {
                                  if(c_verbose)
                                      System.out.println( "EXPOSE2: Matches input parm, exposing anon type "+parameterType.getName());
                                  externalizeTypeAndUpdateTypeMap(wsContext, parameterType);
                              }
                          }
                          
                          // Check output parameters
                          Collection outputParameterTypes = method.getOutputParameterTypes();
                          paramIterator = outputParameterTypes.iterator();
                          while(paramIterator.hasNext())
                          {
                              ParameterInfo parameterInfo =(ParameterInfo)paramIterator.next();
                              Type parameterType = parameterInfo.getType();
                              if(parameterType.getName().equals(type.getQName()))
                              {
                                  if(c_verbose)
                                      System.out.println( "EXPOSE2: Matches output parm, exposing anon type "+parameterType.getName());                             
                                  externalizeTypeAndUpdateTypeMap(wsContext, parameterType);
                              }
                          }
                    }
                }
            }
        }
    }
    
    /**
     * 
     * @param theOrigMap
     * @param theType
     * @param nameMapper
     */
    private void exposeRelatedTypes(TypeMap theOrigMap, Type theType, Hashtable nameMapper)
    {
        QName oldName = theType.getName();                              
        Type classType =  theOrigMap.getType(oldName);
        if (classType != null && !classType.isExternalized())
        {
            if(c_verbose)
                System.out.println("\nEXPOSE4: Externalizing type " + oldName);
            
            // Externalize the type - if anonymous we have to change to name
            if (classType.isAnonymous())
            {
                QName newName   =  new QName(oldName.getNamespaceURI(), 
                                             classType.getLanguageSpecificName());
    
                classType.externalize(newName);
                
                // add old name to new name mapping to name mapper hash table
                nameMapper.put(oldName, newName);
            }
            else
                classType.externalize(true);

            // Now check to see related types of this type - recursively.
            Iterator relatedTypesIt = theType.getRelatedTypes();
            Type relatedType;
            while (relatedTypesIt.hasNext())
            {
                relatedType = (Type) relatedTypesIt.next();
                if (!relatedType.isExternalized())
                    exposeRelatedTypes(theOrigMap, relatedType, nameMapper);
            }            
        }
    }
    
    /**
     * 
     * @param wsContext
     */
    private void exposeNestedTypesThatAreAnonymousTypes(WebServiceContext wsContext)
    {
        // Go through the externalized types in the typemap and externalize the 
        // related types used by each externalized type. In order to complete the externalization,
        // we need to remove the entry from the typemap and replace it with a new name.  
        // However, this will have to be done after we have iterated through the typemap since
        // updating the typemap as we iterate through it will result in an exception.
        // So we have a hash table to map old names to new names for those types that have been 
        // externalized.
        Hashtable nameMapper = new Hashtable();
        Iterator typesIt = wsContext.getTypemap().getTypes().iterator();
        Type type;
        while (typesIt.hasNext())
        {
            type = (Type) typesIt.next();
            if (type.isExternalized())
            {
                if(c_verbose)
                    System.out.println("\nEXPOSE3: Checking related types for type " + type.getName());
                
                Iterator relatedTypesIt = type.getRelatedTypes();
                Type relatedType;
                while (relatedTypesIt.hasNext())
                {
                    relatedType = (Type) relatedTypesIt.next();
                    if (!relatedType.isExternalized())
                        exposeRelatedTypes(wsContext.getTypemap(), relatedType, nameMapper);
                }
            }              
        }
        
        // Now update the typemap, replacing old names with new names, using the hash table that
        // maps old names to new names.
        QName oldName;
        QName newName;
        
        for (Enumeration e = nameMapper.keys(); e.hasMoreElements() ;)
        {
            oldName = (QName) e.nextElement();
            newName = (QName) nameMapper.get(oldName);
            type    = wsContext.getTypemap().getType(oldName);
            if (type != null)
            {
                wsContext.getTypemap().removeType(oldName);
                wsContext.getTypemap().addType(newName, type);                
            }
        }
    }

    /**
     * 
     * @param wsContext
     * @param parameterType
     */
    private void externalizeTypeAndUpdateTypeMap(WebServiceContext wsContext, Type parameterType)
    {
        QName oldName = parameterType.getName();
        Type innerClassType =  wsContext.getTypemap().getType(oldName);
        if (innerClassType != null && !innerClassType.isExternalized())
        {
            QName newTypeName   =  new QName(parameterType.getName().getNamespaceURI(), 
                                             parameterType.getLanguageSpecificName());

            innerClassType.externalize(newTypeName);
            
            // Update the typemap with new info
            wsContext.getTypemap().removeType(oldName);
            wsContext.getTypemap().addType(newTypeName, innerClassType);
        }
    }
}
