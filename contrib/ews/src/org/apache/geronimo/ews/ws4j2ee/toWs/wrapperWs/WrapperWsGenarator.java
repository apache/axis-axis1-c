/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2004 The Apache Software Foundation.  All rights
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

package org.apache.geronimo.ews.ws4j2ee.toWs.wrapperWs;

import org.apache.axis.components.logger.LogFactory;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.SEIOperation;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.Generator;
import org.apache.geronimo.ews.ws4j2ee.utils.Utils;

import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map;

/**
 * <p>This genarated theWrapper WS required in the
 * Axis.</p>
 * 
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class WrapperWsGenarator implements Generator {
    private J2EEWebServiceContext j2eewscontext;
    private PrintWriter out;
    protected static Log log =
            LogFactory.getLog(WrapperWsGenarator.class.getName());

    public WrapperWsGenarator(J2EEWebServiceContext j2eewscontext) {
        this.j2eewscontext = j2eewscontext;
    }

    public void genarate() throws GenerationFault {
        try {
            String filename = j2eewscontext.getMiscInfo().getOutPutPath() + "/jaxrpc/" +
                    j2eewscontext.getMiscInfo().getJaxrpcSEI().replace('.', '/') + "BindingImpl.java";
            log.info(filename + " generating.....................");
            out = new PrintWriter(new FileWriter(filename));
            String superclass = Utils.getClassNameFromQuallifiedName(j2eewscontext.getMiscInfo().getJaxrpcSEI());
            String classname = superclass + "BindingImpl";
            String packagename = Utils.getPackageNameFromQuallifiedName(j2eewscontext.getMiscInfo().getJaxrpcSEI());

            if (packagename != null && packagename.length() > 0)
                out.write("package " + packagename + ";\n");
            out.write("public class " + classname + " implements " + superclass + "{\n");
            out.write("private " + j2eewscontext.getMiscInfo().getEjbsei() + " ejb = null;\n");
            out.write("\tpublic " + classname + "(){}\n");
            writeGetRemoteRef(classname);

            String parmlistStr = "";
            ArrayList operations = j2eewscontext.getMiscInfo().getSEIOperations();
            for (int i = 0; i < operations.size(); i++) {
                SEIOperation op = (SEIOperation) operations.get(i);
                out.write("\tpublic " + op.getReturnType() + " " + op.getMethodName() + "(");

                Map params = op.getParameters();
                Iterator pas = params.keySet().iterator();
                boolean first = true;
                while (pas.hasNext()) {
                    String name = (String) pas.next();
                    String type = (String) params.get(name);
                    if (first) {
                        first = false;
                        out.write(type + " " + name);
                        parmlistStr = parmlistStr + name;
                    } else {
                        out.write("," + type + " " + name);
                        parmlistStr = "," + name;
                    }

                }

                out.write(") throws java.rmi.RemoteException,");
                ArrayList faults = op.getFaults();
                for (int j = 0; j < faults.size(); j++) {
                    out.write((String) faults.get(i));
                }
                out.write("{\n");
                out.write("\t\tif(ejb ==  null)\n");
                out.write("\t\t\tejb = getRemoteRef();\n");

                if (op.getReturnType() != null || !"void".equals(op.getReturnType()))
                    out.write("\t\treturn " + op.getMethodName() + "(" + parmlistStr + ");\n");
                else
                    out.write("\t\tejb." + op.getMethodName() + "(" + parmlistStr + ");\n");

                out.write("\t}\n");
            }
            out.write("}\n");
            out.close();
        } catch (Exception e) {
            throw new GenerationFault(e);
        }
    }

    private void writeGetRemoteRef(String classname) {
        out.write("\tpublic " + j2eewscontext.getMiscInfo().getEjbsei() + " getRemoteRef()throws org.apache.axis.AxisFault{\n");
        out.write("\t\ttry{\n");
        out.write("\t\t\tjava.util.Properties env = new java.util.Properties();\n");
        out.write("\t\t\tenv.put(javax.naming.Context.INITIAL_CONTEXT_FACTORY,\"org.jnp.interfaces.NamingContextFactory\");\n");
        out.write("\t\t\tenv.put(javax.naming.Context.PROVIDER_URL, \"127.0.0.1:1099\");\n");

        out.write("\t\t\tjavax.naming.Context initial = new javax.naming.InitialContext(env);\n");
        out.write("\t\t\tObject objref = initial.lookup(\"" + j2eewscontext.getMiscInfo().getEjbName() + "\");\n");
        String ejbhome = j2eewscontext.getMiscInfo().getEjbhome();
        out.write("\t\t\t" + ejbhome + " home = \n\t\t\t\t(" + ejbhome
                + ")javax.rmi.PortableRemoteObject.narrow(objref," + ejbhome + ".class);\n");
        out.write("\t\t\treturn home.create();\n");
        out.write("\t\t}catch (Exception e) {\n");
        out.write("\t\t    throw org.apache.axis.AxisFault.makeFault(e);\n");
        out.write("\t\t}\n");
        out.write("\t}\n");
    }

}
