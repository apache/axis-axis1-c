/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
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
package org.apache.axis.wsdl;

import java.io.IOException;

import java.util.Vector;

import javax.wsdl.Fault;
import javax.wsdl.QName;

import org.apache.axis.utils.JavaUtils;

/**
* This is Wsdl2java's Fault Writer.  It writes the <faultName>.java file.
* NOTE:  this must be rewritten.  It doesn't follow JAX-RPC.
*/
public class JavaFaultWriter extends JavaWriter {
    private Fault fault;

    /**
     * Constructor.
     */
    protected JavaFaultWriter(Emitter emitter, QName qname, Fault fault) {
        super(emitter, qname, "", "java", JavaUtils.getMessage("genFault00"));
        this.fault = fault;
    } // ctor

    /**
     * Write the body of the Fault file.
     */
    protected void writeFileBody() throws IOException {
        pw.println("public class " + className + " extends Exception {");

        Vector params = new Vector();

        emitter.partStrings(params, fault.getMessage().getOrderedParts(null), false);

        for (int i = 0; i < params.size(); i += 2)
            pw.println("    public " + params.get(i) + " " + params.get(i + 1) + ";");

        pw.println();
        pw.println("    public " + className + "() {");
        pw.println("    }");
        pw.println();
        if (params.size() > 0) {
            pw.print("      public " + className + "(");
            for (int i = 0; i < params.size(); i += 2) {
                if (i != 0) pw.print(", ");
                pw.print(params.get(i) + " " + params.get(i + 1));
            }
            pw.println(") {");
            for (int i = 1; i < params.size(); i += 2) {
                String variable = (String) params.get(i);

                pw.println("        this." + variable + " = " + variable + ";");
            }
            pw.println("    }");
        }
        pw.println("}");
        pw.close();
    } // writeFileBody

} // class JavaFaultWriter
