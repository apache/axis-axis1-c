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
 *    Apache Software Foundation (http://www.apache.org/)."
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

package org.apache.axismora.wsdl2ws.java.client;

import java.io.File;
import java.io.IOException;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;
import org.apache.axismora.wsdl2ws.java.JavaClassWriter;

/**
 * Created on Sep 22, 2003
 * @author vtpavan(vtpavan@opensource.lk)
 */

public class LocatorWriter extends JavaClassWriter {
    private WebServiceContext wscontext;
    private String classname;
    public LocatorWriter(WebServiceContext wscontext) throws WrapperFault {
        super(
            WrapperUtils.getPackegeName4QualifiedName(
                wscontext.getSerInfo().getQualifiedServiceName()),
            WrapperUtils.getClassNameFromFullyQualifiedName(
                wscontext.getSerInfo().getQualifiedServiceName())
                + "Locator");
        classname =
            WrapperUtils.getClassNameFromFullyQualifiedName(
                wscontext.getSerInfo().getQualifiedServiceName())
                + "Locator";
        this.wscontext = wscontext;
    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.SourceWriter#writeSource()
     */

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#getJavaFilePath()
     */
    protected File getJavaFilePath() throws WrapperFault {
        String targetOutputLocation =
            this.wscontext.getWrapInfo().getTargetOutputLocation();
        if (targetOutputLocation.endsWith("/"))
            targetOutputLocation =
                targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
        new File(
            targetOutputLocation
                + "/"
                + WrapperUtils
                    .getPackegeName4QualifiedName(
                        this.wscontext.getSerInfo().getQualifiedServiceName())
                    .replace('.', '/'))
            .mkdirs();
        String fileName =
            targetOutputLocation
                + "/"
                + (
                    this.wscontext.getSerInfo().getQualifiedServiceName()
                        + "Locator").replace(
                    '.',
                    '/')
                + ".java";
        return new File(fileName);
    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeAttributes()
     */
    protected void writeAttributes() throws WrapperFault {
        try {
            writer.write(
                "\n\tprivate"
                    + " "
                    + wscontext.getSerInfo().getQualifiedServiceName()
                    + " "
                    + "ws;");
        } catch (Exception e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeConstructors()
     */
    protected void writeConstructors() throws WrapperFault {
        try {
            writer.write("\n\tpublic " + classname + "()" + "{\n\t}");

            writer.write("\n\tpublic " + classname + "(java.lang.String enduri){\n");
            writer.write(
                "\tthis.ws = new"
                    + " "
                    + wscontext.getSerInfo().getQualifiedServiceName()
                    + "Stub"
                    + "(enduri);\n");
            writer.write("\t}\n");
        } catch (Exception e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeMethods()
     */
    protected void writeMethods() throws WrapperFault {

        try {
            writer.write("\n\tpublic ");
            writer.write(wscontext.getSerInfo().getQualifiedServiceName() + " ");
            writer.write("getStub()" + "{");
            writer.write("\n\t\treturn" + " " + "this.ws" + ";");
            writer.write("\n\t}\n");

        } catch (Exception e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }

    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeClassComment()
     */
    protected void writeClassComment() throws WrapperFault {
        try {
            writer.write("/*This class is automatically generated by \n");
            writer.write("*axis_lsf client service generator\n");
            writer.write("*The client side Locator of the web service. \n");
            writer.write("*/\n\n");
        } catch (IOException e) {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axismora.wsdl2ws.SourceWriter#writeSource()
     */
    public void writeSource() throws WrapperFault {
        super.writeSource();
    }
}