/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */
package org.apache.geronimo.ews.jaxrpcmapping;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Collection;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Properties;
import java.util.Vector;

import javax.wsdl.Binding;
import javax.wsdl.Definition;
import javax.xml.namespace.QName;

import org.apache.geronimo.ews.jaxrpcmapping.descriptor.FullyQualifiedClassType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.PackageMappingType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.XsdAnyURIType;

import org.apache.axis.i18n.Messages;
import org.apache.axis.utils.ClassUtils;
import org.apache.axis.wsdl.gen.Generator;
import org.apache.axis.wsdl.gen.NoopFactory;
import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.CollectionElement;
import org.apache.axis.wsdl.symbolTable.MessageEntry;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.axis.wsdl.symbolTable.SymTabEntry;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.symbolTable.Type;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.toJava.Emitter;
import org.apache.axis.wsdl.toJava.Namespaces;
import org.apache.axis.wsdl.toJava.Utils;

/**
 * @author Ias (iasandcb@tmax.co.kr)
 *
 */

public class J2eeEmitter extends Emitter {

	private String mappingFilePath;
	private static final int timeoutms = 45000000;
  private InputStream mappingFileInputStream;
  private QName serviceQName;
  private JaxRpcMapper jaxRpcMapper;
  private SymbolTable symbolTable;

	public J2eeEmitter() {
		J2eeGeneratorFactory factory = new J2eeGeneratorFactory();
		setFactory(factory);
		factory.setEmitter(this);
	} // ctor

	public void setMappingFilePath(String mappingFilePath) {
		this.mappingFilePath = mappingFilePath;
	}

	private void loadMapping()
	{
    jaxRpcMapper = new JaxRpcMapper();
    if (mappingFilePath == null) {
      jaxRpcMapper.loadMappingFromInputStream(mappingFileInputStream);
    }
    else {
      jaxRpcMapper.loadMappingFromDir(mappingFilePath);
    }

    List packageList = jaxRpcMapper.getMapping().getPackageMapping();
		Map namespaceMap = getNamespaceMap();
		for (Iterator i = packageList.iterator(); i.hasNext(); )
		{
			PackageMappingType pack = (PackageMappingType) i.next();
			FullyQualifiedClassType qPack = pack.getPackageType();
			XsdAnyURIType namespace = pack.getNamespaceURI();
			namespaceMap.put(namespace.getValue(), qPack.getValue());
		}
	}

	/**
	 * Emit appropriate Java files for a WSDL at a given URL.
	 *
	 * This method will time out after the number of milliseconds specified
	 * by our timeoutms member.
	 *
	 */
	public void run(String wsdlURL) throws Exception {
		setup();
		runTemp(wsdlURL);
	} // run

  public void runServerSide(String wsdlURL) throws Exception {
    setup();
    if (getFactory() == null) {
      setFactory(new NoopFactory());
    }
    symbolTable = new SymbolTable(
        getFactory().getBaseTypeMapping(),
        imports,
        verbose,
              nowrap);
    symbolTable.populate(wsdlURL, username, password);
    generate(symbolTable);
    
  }
  
  public SymbolTable getSymbolTable() {
    return symbolTable;
  }
  
	private void setup() throws IOException {
		if (baseTypeMapping == null) {
			setTypeMappingVersion(typeMappingVersion);
		}
		getFactory().setBaseTypeMapping(baseTypeMapping);

		namespaces = new Namespaces(getOutputDir());

		if (getPackageName() != null) {
			 namespaces.setDefaultPackage(getPackageName());
		} else {
			// First, read the namespace mapping file - configurable, by default
			// NStoPkg.properties - if it exists, and load the namespaceMap HashMap
			// with its data.
			getNStoPkgFromPropsFile(namespaces);
            loadMapping();
			if (getNamespaceMap() != null) {
				namespaces.putAll(getNamespaceMap());
			}
		}
	} // setup

	/**
	 * Tries to load the namespace-to-package mapping file.
	 * <ol>
	 *   <li>if a file name is explicitly set using <code>setNStoPkg()</code>, tries
	 *      to load the mapping from this file. If this fails, the built-in default
	 *      mapping is used.
	 *
	 *    <li>if no file name is set, tries to load the file <code>DEFAULT_NSTOPKG_FILE</code>
	 *       as a java resource. If this fails, the built-in dfault mapping is used.
	 * </ol>
	 *
	 * @param namespaces  a hashmap which is filled with the namespace-to-package mapping
	 *    in this method
	 *
	 * @see #setNStoPkg(String)
	 * @see #DEFAULT_NSTOPKG_FILE
	 * @see org.apache.axis.utils.ClassUtils#getResourceAsStream(java.lang.Class,String)
	 *
	 */
	private void getNStoPkgFromPropsFile(HashMap namespaces) throws IOException
	{

		Properties mappings = new Properties();
		if (NStoPkgFilename != null) {
			try {
				mappings.load(new FileInputStream(NStoPkgFilename));
				if (verbose) {
					System.out.println(
						Messages.getMessage("nsToPkgFileLoaded00", NStoPkgFilename)
					);
				}
			} catch (Throwable t) {
				// loading the custom mapping file failed. We do not try
				// to load the mapping from a default mapping file.
				throw new IOException(
						Messages.getMessage("nsToPkgFileNotFound00", NStoPkgFilename)
				);
			}
		}
		else {
			try {
				mappings.load(new FileInputStream(DEFAULT_NSTOPKG_FILE));
				if (verbose) {
					System.out.println(
					  Messages.getMessage("nsToPkgFileLoaded00", DEFAULT_NSTOPKG_FILE)
					);
				}
			} catch (Throwable t) {
				try {
					mappings.load(ClassUtils.getResourceAsStream(
						Emitter.class, DEFAULT_NSTOPKG_FILE));
					if (verbose) {
						System.out.println(
						  Messages.getMessage("nsToPkgDefaultFileLoaded00", DEFAULT_NSTOPKG_FILE)
						);
					}

				} catch(Throwable t1) {
					// loading the default mapping file failed.
					// The built-in default mapping is used
					// No message is given, since this is generally what happens
				}
			}
		}

		Enumeration keys = mappings.propertyNames();
		while (keys.hasMoreElements()) {
			String key = (String) keys.nextElement();
			namespaces.put(key, mappings.getProperty(key));
		}
	} // getNStoPkgFromPropsFile

  /**
   * Convert the specified QName into a full Java Name.
   */

  public String getJavaName(QName qName) {



      // If this is one of our special 'collection' qnames.

      // get the element type and append []

      if (qName.getLocalPart().indexOf("[") > 0) {

          String localPart = qName.getLocalPart().substring(0,qName.getLocalPart().indexOf("["));

          QName eQName = new QName(qName.getNamespaceURI(), localPart);

          return getJavaName(eQName) + "[]";

      }



      // Handle the special "java" namespace for types

      if (qName.getNamespaceURI().equalsIgnoreCase("java")) {

          return qName.getLocalPart();

      }



      // The QName may represent a base java name, so check this first

      String fullJavaName = getFactory().getBaseTypeMapping().getBaseName(qName);

      if (fullJavaName != null)

          return fullJavaName;



      // Use the namespace uri to get the appropriate package
      
      String pkg = getPackage(qName.getNamespaceURI());

      if (pkg != null) {

          fullJavaName = pkg + "." + Utils.xmlNameToJavaClass(qName.getLocalPart());

      } else {

          fullJavaName = Utils.xmlNameToJavaClass(qName.getLocalPart());

      }

      return fullJavaName;

  } // getJavaName
  
	/**
	 * Parse a WSDL at a given URL.
	 *
	 * This method will time out after the number of milliseconds specified
	 * by our timeoutms member.
	 *
	 */
	public void runTemp(String wsdlURI) throws Exception {
		if (getFactory() == null) {
			setFactory(new NoopFactory());
		}
		symbolTable = new SymbolTable(
        getFactory().getBaseTypeMapping(),
        imports,
        verbose,
      				nowrap);
    // We run the actual Emitter in a thread that we can kill
		WSDLRunnable runnable = new WSDLRunnable(symbolTable, wsdlURI);
		Thread wsdlThread = new Thread(runnable);
		wsdlThread.start();

		try {
			if (timeoutms > 0)
				wsdlThread.join(timeoutms);
			else
				wsdlThread.join();
		} catch (InterruptedException e) {
		}

		if (wsdlThread.isAlive()) {
			wsdlThread.interrupt();
			throw new IOException(Messages.getMessage("timedOut"));
		}

		if (runnable.getFailure() != null) {
			throw runnable.getFailure();
		}
	} // run

	private class WSDLRunnable implements Runnable {
		private SymbolTable symbolTable;
		private String wsdlURI;
		private Exception failure = null;

		public WSDLRunnable(SymbolTable symbolTable, String wsdlURI) {
			this.symbolTable = symbolTable;
			this.wsdlURI = wsdlURI;
		} // ctor

		public void run() {
			try {
				symbolTable.populate(wsdlURI, username, password);
				generate(symbolTable);
			} catch (Exception e) {
				failure = e;
			}
		} // run

		public Exception getFailure() {
			return failure;
		} // getFailure
	} // WSDLRunnable

        protected void sanityCheck(SymbolTable symbolTable) {
            Iterator it = symbolTable.getHashMap().values().iterator();
            while (it.hasNext()) {
                Vector v = (Vector) it.next();
                for (int i = 0; i < v.size(); ++i) {
                    SymTabEntry entry = (SymTabEntry) v.elementAt(i);
                    String namespace = entry.getQName().getNamespaceURI();
                    String packageName =
                            org.apache.axis.wsdl.toJava.Utils.makePackageName(namespace);
                    String localName = entry.getQName().getLocalPart();
                    if (localName.equals(packageName) &&
                            packageName.equals(namespaces.getCreate(namespace))) {
                        packageName += "_pkg";
                        namespaces.put(namespace, packageName);
                    }

                }
            }
        }

	private void generate(SymbolTable symbolTable) throws IOException {
		sanityCheck(symbolTable);
		Definition def = symbolTable.getDefinition();
		getFactory().generatorPass(def, symbolTable);
		if (isDebug()) {
			symbolTable.dump(System.out);
		}
    if (getOutputDir() == null) {
      return;
    }

		// Generate bindings for types
		generateTypes(symbolTable);

		Iterator it = symbolTable.getHashMap().values().iterator();
		while (it.hasNext()) {
			Vector v = (Vector) it.next();
			for (int i = 0; i < v.size(); ++i) {
				SymTabEntry entry = (SymTabEntry) v.elementAt(i);
				Generator gen = null;
				if (entry instanceof MessageEntry) {
					gen = getFactory().getGenerator(
							((MessageEntry) entry).getMessage(), symbolTable);
				}
				else if (entry instanceof PortTypeEntry) {
					PortTypeEntry pEntry = (PortTypeEntry) entry;
					// If the portType is undefined, then we're parsing a Definition
					// that didn't contain a portType, merely a binding that referred
					// to a non-existent port type.  Don't bother writing it.
					if (pEntry.getPortType().isUndefined()) {
						continue;
					}
					gen = getFactory().getGenerator(pEntry.getPortType(), symbolTable);
				}
				else if (entry instanceof BindingEntry) {
					BindingEntry bEntry = (BindingEntry)entry;
					Binding binding = bEntry.getBinding();

					// If the binding is undefined, then we're parsing a Definition
					// that didn't contain a binding, merely a service that referred
					// to a non-existent binding.  Don't bother writing it.
					if (binding.isUndefined() || !bEntry.isReferenced()) {
						continue;
					}
					gen = getFactory().getGenerator(binding, symbolTable);
				}
				else if (entry instanceof ServiceEntry) {
          ServiceEntry sEntry = (ServiceEntry) entry;
          serviceQName = sEntry.getService().getQName();
					gen = getFactory().getGenerator(sEntry.getService(), symbolTable);
				}
				if (gen != null) {
					gen.generate();
				}
			}
		}

		// Output extra stuff (deployment files and faults)
		// outside of the recursive emit method.
		Generator gen = getFactory().getGenerator(def, symbolTable);
		gen.generate();
	} // generate

	/**
	 * Generate bindings (classes and class holders) for the complex types.
	 * If generating serverside (skeleton) spit out beanmappings
	 */
	private void generateTypes(SymbolTable symbolTable) throws IOException {
		Map elements = symbolTable.getElementIndex();
		Collection elementCollection = elements.values();
		for (Iterator i = elementCollection.iterator(); i.hasNext(); ) {
			TypeEntry type = (TypeEntry) i.next();
			type.setOnlyLiteralReference(false);

			// Write out the type if and only if:
			//  - we found its definition (getNode())
			//  - it is referenced
			//  - it is not a base type
			//  - it is a Type (not an Element) or a CollectionElement
			// (Note that types that are arrays are passed to getGenerator
			//  because they may require a Holder)

			// A CollectionElement is an array that might need a holder

//			boolean isType = (type instanceof Type ||
//					type instanceof CollectionElement);
//			if (type.getNode() != null &&
//					type.isReferenced() &&
//					isType &&
//					type.getBaseType() == null) {
				Generator gen = getFactory().getGenerator(type, symbolTable);
				gen.generate();
//			}
		}
		Map types = symbolTable.getTypeIndex();
		Collection typeCollection = types.values();
		for (Iterator i = typeCollection.iterator(); i.hasNext(); ) {
			TypeEntry type = (TypeEntry) i.next();

			// Write out the type if and only if:
			//  - we found its definition (getNode())
			//  - it is referenced
			//  - it is not a base type
			//  - it is a Type (not an Element) or a CollectionElement
			// (Note that types that are arrays are passed to getGenerator
			//  because they may require a Holder)

			// A CollectionElement is an array that might need a holder
			boolean isType = (type instanceof Type ||
					type instanceof CollectionElement);
			if (type.getNode() != null &&
					type.isReferenced() &&
					isType &&
					type.getBaseType() == null) {
				Generator gen = getFactory().getGenerator(type, symbolTable);
				gen.generate();
			}
		}
	} // generateTypes

  /**
   * @param mappingFileInputStream The mappingFileInputStream to set.
   */
  public void setMappingFileInputStream(InputStream mappingFileInputStream) {
    this.mappingFileInputStream = mappingFileInputStream;
  }

  /**
   * @return Returns the serviceQName.
   */
  public QName getServiceQName() {
    return serviceQName;
  }

  /**
   * @return
   */
  public boolean isGeneratingInterface() {
    // TODO Auto-generated method stub
    return false;
  }

  /**
   * @return
   */
  public boolean isGeneratingTypes() {
    // TODO Auto-generated method stub
    return false;
  }

  /**
   * @return Returns the jaxRpcMapper.
   */
  public JaxRpcMapper getJaxRpcMapper() {
    return jaxRpcMapper;
  }

  /**
   * @param jaxRpcMapper The jaxRpcMapper to set.
   */
  public void setJaxRpcMapper(JaxRpcMapper jaxRpcMapper) {
    this.jaxRpcMapper = jaxRpcMapper;
  }

} // class MyEmitter
