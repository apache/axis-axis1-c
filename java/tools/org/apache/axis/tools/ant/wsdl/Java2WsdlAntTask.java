/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
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
 * 3. The end-user documentation included with the redistribution, if
 *    any, must include the following acknowlegement:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowlegement may appear in the software itself,
 *    if and wherever such third-party acknowlegements normally appear.
 *
 * 4. The names "The Jakarta Project", "Ant", and "Apache Software
 *    Foundation" must not be used to endorse or promote products derived
 *    from this software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache"
 *    nor may "Apache" appear in their names without prior written
 *    permission of the Apache Group.
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
package org.apache.axis.tools.ant.wsdl;

import org.apache.axis.encoding.DefaultSOAPEncodingTypeMappingImpl;
import org.apache.axis.encoding.DefaultTypeMappingImpl;
import org.apache.axis.utils.ClassUtils;
import org.apache.axis.wsdl.fromJava.Emitter;
import org.apache.tools.ant.AntClassLoader;
import org.apache.tools.ant.BuildException;
import org.apache.tools.ant.Project;
import org.apache.tools.ant.Task;
import org.apache.tools.ant.types.Path;

import java.io.File;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.util.HashMap;
import java.util.StringTokenizer;

/*
 * Important. we autogenerate the ant task docs from this.
 * after adding a new attribute
 * 1. add the javadoc for the end users. Make it meaningful
 * 2. get jakarta_ant/proposals/xdocs from ant CVS
 * 3. run the xdocs target in tools/build.xml
 *    this creates xml files in xdocs/build
 * 4. run proposals/xdocs/dvsl build.xml to create the html files
 *    these are also created under xdocs/build
 * 5. copy the the html files to docs/ant
 * 4. check in the changes in docs/ant
 */
/**
 * Generates a WSDL description from a Java class.
 * @author Rich Scheuerle (scheu@us.ibm.com)
 * @author Steve Loughran
 * @ant.task category="axis" name="axis-java2wsdl"
 */

public class Java2WsdlAntTask extends Task
{
    private String namespace = "";
    private String namespaceImpl = null;
    private HashMap namespaceMap = new HashMap();
    private String location = "";
    private String locationImport = null;
    private String output = "." ;
    private String importSchema = null ;
    private String input = null ;
    private String outputImpl = null;
    private String className = "." ;
    private String servicePortName = null ;
    private String portTypeName = null ;
    private String bindingName = null ;
    private String implClass = null;
    private boolean useInheritedMethods = false;
    private String exclude = null;
    private String stopClasses = null;
    private String typeMappingVersion = TypeMappingVersionEnum.DEFAULT_VERSION;
    private String style = null;
    private String serviceElementName=null;
    private String methods=null;
    private String use = null;
    private MappingSet mappings=new MappingSet();
    private String extraClasses = null;
    private Path classpath = null;
    private String soapAction = null;

    /**
     * trace out parameters
     * @param logLevel to log at
     * @see org.apache.tools.ant.Project#log
     */
    public void traceParams(int logLevel) {
        log("Running Java2WsdlAntTask with parameters:", logLevel);
        log("\tnamespace:" + namespace, logLevel);
        log("\tPkgtoNS:" + namespaceMap, logLevel);
        log("\tlocation:" + location, logLevel);
        log("\toutput:" + output, logLevel);
        log("\timportSchema:" + importSchema, logLevel);
        log("\tinput:" + input, logLevel);
        log("\tclassName:" + className, logLevel);
        log("\tservicePortName:" + servicePortName, logLevel);
        log("\tportTypeName:" + portTypeName, logLevel);
        log("\tbindingName:" + bindingName, logLevel);
        log("\timplClass:" + implClass, logLevel);
        log("\tinheritance:" + useInheritedMethods, logLevel);
        log("\texcluded:" + exclude, logLevel);
        log("\tstopClasses:" + stopClasses, logLevel);
        log("\ttypeMappingVersion:" + typeMappingVersion, logLevel);
        log("\tstyle:" + style, logLevel);
        log("\toutputImpl:" + outputImpl, logLevel);
        log("\tuse:" + use, logLevel);
        log("\tnamespaceImpl:" + namespaceImpl, logLevel);
        log("\tlocationImport:" + locationImport, logLevel);
        log("\tserviceElementName:" + serviceElementName, logLevel);
        log("\tmethods:" + methods, logLevel);
        log("\textraClasses:" + extraClasses, logLevel);
        log("\tsoapAction:" + soapAction, logLevel);
      
}

    /**
     * validation code
     * @throws  BuildException  if validation failed
     */
    protected void validate()
            throws BuildException {
        if(className==null || className.length() ==0) {
            throw new BuildException("No classname was specified");
        }
        if(location==null || location.length() == 0) {
            throw new BuildException("No location was specified");
        }
    }

    /**
     * execute the task
     * @throws BuildException
     */
    public void execute() throws BuildException {
        if (classpath != null) {
            AntClassLoader cl = new AntClassLoader(null, project, classpath, false);
            log("Using CLASSPATH " + cl.getClasspath(),
              Project.MSG_VERBOSE);
            ClassUtils.setClassLoader(className, cl);
            ClassUtils.setClassLoader(implClass, cl);
            //add extra classes to the classpath when the classpath attr is not null
            //??why do we do this? Why don't we do this when the classpath is unset?
            if(extraClasses!=null) {
                StringTokenizer tokenizer = new StringTokenizer(extraClasses, " ,");
                while (tokenizer.hasMoreTokens()) {
                    String clsName = tokenizer.nextToken();
                    ClassUtils.setClassLoader(clsName, cl);
                }
            }
        }
        try {
            traceParams(Project.MSG_VERBOSE);
            validate();
            // Instantiate the emitter
            Emitter emitter = new Emitter();
            //do the mappings, packages are the key for this map
            mappings.execute(this,namespaceMap, true);
            if (!namespaceMap.isEmpty()) {
                emitter.setNamespaceMap(namespaceMap);
            }
            if (servicePortName != null) {
                emitter.setServicePortName(servicePortName);
            }
            if (portTypeName != null) {
                emitter.setPortTypeName(portTypeName);
            }
            if (bindingName != null) {
                emitter.setBindingName(bindingName);
            }
            log("Java2WSDL " + className, Project.MSG_INFO);
            emitter.setCls(className);
            if (implClass != null) {
                emitter.setImplCls(implClass);
            }
            if (exclude != null) {
                emitter.setDisallowedMethods(exclude);
            }
            if (stopClasses != null) {
                emitter.setStopClasses(stopClasses);
            }
            if (extraClasses != null) {
                emitter.setExtraClasses(extraClasses);
            }

            if (typeMappingVersion.equals("1.1")) {
                emitter.setDefaultTypeMapping(DefaultTypeMappingImpl.getSingleton());
            } else {
                emitter.setDefaultTypeMapping(DefaultSOAPEncodingTypeMappingImpl.create());
            }
            if (style != null) {
                emitter.setStyle(style);
            }

            if (use != null) {
                emitter.setUse(use);
            }

            if (importSchema != null) {
                emitter.setInputSchema(importSchema);
            }
            if (input != null) {
                emitter.setInputWSDL(input);
            }
            emitter.setIntfNamespace(namespace);
            emitter.setImplNamespace(namespaceImpl);
            emitter.setLocationUrl(location);
            emitter.setImportUrl(locationImport);
            emitter.setUseInheritedMethods(useInheritedMethods);
            if(serviceElementName!=null) {
                emitter.setServiceElementName( serviceElementName);
            }
            if(methods!=null) {
                emitter.setAllowedMethods(methods);
            }
            if (soapAction != null) {
                emitter.setSoapAction(soapAction);
            }
            if (outputImpl == null) {
                // Normal case
                emitter.emit(output, Emitter.MODE_ALL);
            } else {
                // Emit interface and implementation wsdls
                emitter.emit(output, outputImpl);
            }


        } catch(BuildException b) {
            //pass build exceptions up the wire
           throw b;
        } catch (Throwable t) {
            //other trouble: stack trace the trouble and throw an exception
            StringWriter writer = new StringWriter();
            t.printStackTrace(new PrintWriter(writer));
            log(writer.getBuffer().toString(), Project.MSG_ERR);
            throw new BuildException("Error while running " + getClass().getName(), t);
        }
    }

    public Path createClasspath() {
      if (classpath == null) {
        classpath = new Path(project);
      }
      return classpath.createPath();
    }

    /**
     * The name of the output WSDL file.
     * If not specified, a suitable default WSDL file is written into
     * the current directory.
     * @param parameter
     */
    public void setOutput(File parameter) {
        this.output = parameter.getPath();
    }

    /**
     * Option attribute that indicates the name of an XML Schema file that
     * should be physically imported into the generated WSDL.
     * @param parameter
     */
    public void setImportSchema(File parameter) throws BuildException {
        try {
            this.importSchema = parameter.toURL().toString();
        } catch (java.io.IOException ioe) {
            throw new BuildException(ioe);
        }
    }

    /**
     * Optional attribute that indicates the name of the input wsdl file.
     * The output wsdl file will contain everything from the input wsdl
     * file plus the new constructs. If a new construct is already present
     * in the input wsdl file, it is not added. This option is useful for
     * constructing a wsdl file with multiple ports, bindings, or portTypes.
     * @param parameter filename
     */
    public void setInput(File parameter) {
        this.input = parameter.getPath();
    }

    /**
     * Use this option to indicate the name of the output implementation WSDL
     * file.  If specified, Java2WSDL will produce separate interface and implementation
     * WSDL files.  If not, a single WSDL file is generated
     * @param parameter
     */
    public void setOutputImpl(File parameter) {
        this.outputImpl = parameter.getPath();
    }

    /**
     * The url of the location of the service. The name after the last slash or
     * backslash is the name of the service port (unless overridden by the -s
     * option). The service port address location attribute is assigned the
     * specified value.
     * @param parameter a URL
     */
    public void setLocation(String parameter) {
        this.location = parameter;
    }

    /**
     * the location of the interface WSDL when generating an implementation WSDL
     * Required when <tt>outputImpl</tt> is set
     * @param parameter URL?
     */
    public void setLocationImport(String parameter) {
        this.locationImport = parameter;
    }

    /**
     * the class name to import, eg. org.example.Foo. Required.
     * The class must be on the classpath.
     * @param parameter fully qualified class name
     */
    public void setClassName(String parameter) {
        this.className = parameter;
    }

    /**
     * Sometimes extra information is available in the implementation class
     * file. Use this option to specify the implementation class.
     * @param parameter
     */
    public void setImplClass(String parameter) {
        this.implClass = parameter;
    }

    /**
     * service port name (obtained from location if not specified)
     * @param parameter portname
     */
    public void setServicePortName(String parameter) {
        this.servicePortName = parameter;
    }

    /**
     * Indicates the name to use use for the portType element.
     * If not specified, the class-of-portType name is used.
     * @param parameter
     */
    public void setPortTypeName(String parameter) {
        this.portTypeName = parameter;
    }

    /**
     * The name to use use for the binding element.
     * If not specified, the value of the
     * <tt>servicePortName</tt> + "SoapBinding" is used.
     * @param parameter
     */
    public void setBindingName(String parameter) {
        this.bindingName = parameter;
    }

    /**
     * the target namespace. Required.
     * @param parameter
     */
    public void setNamespace(String parameter) {
        this.namespace = parameter;
    }

    /**
     * Namespace of the implementation WSDL.
     * @param parameter
     */
    public void setNamespaceImpl(String parameter) {
        this.namespaceImpl = parameter;
    }

    /**
     * should inherited methods be exported too? Default=false
     * @param parameter
     */
    public void setUseInheritedMethods(boolean parameter) {
        this.useInheritedMethods = parameter;
    }

    /**
     * Comma separated list of methods to exclude from the wsdl file.
     * @param exclude
     */
    public void setExclude(String exclude) {
        this.exclude = exclude;
    }

    /**
     * Comma separated list of classes which stop the Java2WSDL
     * inheritance search.
     * @param stopClasses
     */
    public void setStopClasses(String stopClasses) {
        this.stopClasses = stopClasses;
    }

    /**
     * The style of the WSDL document: RPC, DOCUMENT or WRAPPED.
     * If RPC, a rpc/encoded wsdl is generated. If DOCUMENT, a
     * document/literal wsdl is generated. If WRAPPED, a
     * document/literal wsdl is generated using the wrapped approach.
     * @param style
     */
    public void setStyle(String style) {
        this.style = style;
    }

    /**
     * add a mapping of namespaces to packages
     */
    public void addMapping(NamespaceMapping mapping) {
        mappings.addMapping(mapping);
    }

    /**
     * add a mapping of namespaces to packages
     */
    public void addMappingSet(MappingSet mappingset) {
        mappings.addMappingSet(mappingset);
    }


    /**
     *  the default type mapping registry to use. Either 1.1 or 1.2.
     * Default is 1.1
     * @param parameter new version
     */
    public void setTypeMappingVersion(TypeMappingVersionEnum parameter) {
        this.typeMappingVersion = parameter.getValue();
    }

    /**
     * If this option is specified, only the indicated methods in your
     * interface class will be exported into the WSDL file.  The methods list
     * must be comma separated.  If not specified, all methods declared in
     * the interface class will be exported into the WSDL file
     * @param methods list of methods
     */
    public void setMethods(String methods) {
        this.methods = methods;
    }

    /**
     * Set the use option
     */
    public void setUse(String use) {
        this.use = use;
    }

    /**
     * the name of the service element.
     * If not specified, the service element is the <tt>portTypeName</tt>Service.
     * @param serviceElementName
     */
    public void setServiceElementName(String serviceElementName) {
        this.serviceElementName = serviceElementName;
    }

    /**
     * The setter for the "extraClasses" attribute
     */
    public void setExtraClasses(String extraClasses) {
        this.extraClasses = extraClasses;
    }
    
    /**
     * The setter for the "soapAction" attribute
     */
    public void setSoapAction( String soapAction ) {
		this.soapAction = soapAction;
    }

}
