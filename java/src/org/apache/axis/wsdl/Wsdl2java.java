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

import org.apache.avalon.excalibur.cli.CLArgsParser;
import org.apache.avalon.excalibur.cli.CLOption;
import org.apache.avalon.excalibur.cli.CLOptionDescriptor;
import org.apache.avalon.excalibur.cli.CLUtil;

import org.apache.axis.utils.JavaUtils;

import java.util.HashMap;
import java.util.List;

/**
 * Command line interface to the wsdl2java utility
 *
 * @author Tom Jordahl (tjordahl@macromedia.com)
 */
public class Wsdl2java {
    // Define our short one-letter option identifiers.
    protected static final int HELP_OPT = 'h';
    protected static final int VERBOSE_OPT = 'v';
    protected static final int SKELETON_OPT = 's';
    protected static final int NAMESPACE_OPT = 'N';
    protected static final int OUTPUT_OPT = 'o';
    protected static final int SCOPE_OPT = 'd';
    protected static final int TEST_OPT = 't';
    protected static final int NOIMPORTS_OPT = 'n';
    protected static final int PACKAGE_OPT = 'p';

    /**
     *  Define the understood options. Each CLOptionDescriptor contains:
     * - The "long" version of the option. Eg, "help" means that "--help" will
     * be recognised.
     * - The option flags, governing the option's argument(s).
     * - The "short" version of the option. Eg, 'h' means that "-h" will be
     * recognised.
     * - A description of the option for the usage message
     */
    protected static final CLOptionDescriptor[] options = new CLOptionDescriptor[]{
        new CLOptionDescriptor("help",
                CLOptionDescriptor.ARGUMENT_DISALLOWED,
                HELP_OPT,
                JavaUtils.getMessage("optionHelp00")),
        new CLOptionDescriptor("verbose",
                CLOptionDescriptor.ARGUMENT_DISALLOWED,
                VERBOSE_OPT,
                JavaUtils.getMessage("optionVerbose00")),
        new CLOptionDescriptor("skeleton",
                CLOptionDescriptor.ARGUMENT_DISALLOWED,
                SKELETON_OPT,
                JavaUtils.getMessage("optionSkel00")),
        new CLOptionDescriptor("NStoPkg",
                CLOptionDescriptor.DUPLICATES_ALLOWED + CLOptionDescriptor.ARGUMENTS_REQUIRED_2,
                NAMESPACE_OPT,
                JavaUtils.getMessage("optionNStoPkg00")),
        new CLOptionDescriptor("package",
                CLOptionDescriptor.ARGUMENT_REQUIRED,
                PACKAGE_OPT,
                JavaUtils.getMessage("optionPackage00")),
        new CLOptionDescriptor("output",
                CLOptionDescriptor.ARGUMENT_REQUIRED,
                OUTPUT_OPT,
                JavaUtils.getMessage("optionOutput00")),
        new CLOptionDescriptor("deployScope",
                CLOptionDescriptor.ARGUMENT_REQUIRED,
                SCOPE_OPT,
                JavaUtils.getMessage("optionScope00")),
        new CLOptionDescriptor("testCase",
                CLOptionDescriptor.ARGUMENT_DISALLOWED,
                TEST_OPT,
                JavaUtils.getMessage("optionTest00")),
        new CLOptionDescriptor("noImports",
                CLOptionDescriptor.ARGUMENT_DISALLOWED,
                NOIMPORTS_OPT,
                JavaUtils.getMessage("optionImport00"))
    };

    /**
     * Main
     */
    public static void main(String args[]) {
        boolean bSkeleton = false;
        boolean bTestClass = false;
        String wsdlURI = null;
        HashMap namespaceMap = new HashMap();
        boolean bPackageOpt = false;

        // Parse the arguments
        CLArgsParser parser = new CLArgsParser(args, options);

        // Print parser errors, if any
        if (null != parser.getErrorString()) {
            System.err.println(
                    JavaUtils.getMessage("error01", parser.getErrorString()));
            printUsage();
        }

        // Get a list of parsed options
        List clOptions = parser.getArguments();
        int size = clOptions.size();

        try {

            // Instantiate the emitter
            JavaWriterFactory writerFactory = new JavaWriterFactory();
            Emitter emitter = new Emitter(writerFactory);
            writerFactory.setEmitter(emitter);

            // Parse the options and configure the emitter as appropriate.
            for (int i = 0; i < size; i++) {
                CLOption option = (CLOption)clOptions.get(i);

                switch (option.getId()) {
                    case CLOption.TEXT_ARGUMENT:
                        if (wsdlURI != null) {
                            printUsage();
                        }
                        wsdlURI = option.getArgument();
                        break;

                    case HELP_OPT:
                        printUsage();
                        break;

                    case VERBOSE_OPT:
                        emitter.verbose(true);
                        break;

                    case SKELETON_OPT:
                        bSkeleton = true;
                        emitter.generateSkeleton(true);
                        break;

                    case NAMESPACE_OPT:
                        String namespace = option.getArgument(0);
                        String packageName = option.getArgument(1);
                        namespaceMap.put(namespace, packageName);
                        break;

                    case PACKAGE_OPT:
                        bPackageOpt = true;
                        emitter.setPackageName(option.getArgument());
                        break;

                    case OUTPUT_OPT:
                        emitter.setOutputDir(option.getArgument());
                        break;

                    case SCOPE_OPT:
                        String scope = option.getArgument();
                        if ("Application".equals(scope)) {
                            emitter.setScope(Emitter.APPLICATION_SCOPE);
                        }
                        else if ("Request".equals(scope)) {
                            emitter.setScope(Emitter.REQUEST_SCOPE);
                        }
                        else if ("Session".equals(scope)) {
                            emitter.setScope(Emitter.SESSION_SCOPE);
                        }
                        else {
                            System.err.println(
                                    JavaUtils.getMessage("badScope00", scope));
                        }
                        break;

                    case TEST_OPT:
                        bTestClass = true;
                        emitter.generateTestCase(true);
                        break;

                    case NOIMPORTS_OPT:
                        emitter.generateImports(false);
                        break;
                }
            }

            // validate argument combinations
            //
            if (wsdlURI == null) {
                printUsage();
            }
            if (!namespaceMap.isEmpty() && bPackageOpt) {
                System.out.println(JavaUtils.getMessage("badpackage00"));
                printUsage();
            }

            if (!namespaceMap.isEmpty()) {
                emitter.setNamespaceMap(namespaceMap);
            }

            emitter.emit(wsdlURI);
            
            // everything is good
            System.exit(0);
        }
        catch (Throwable t) {
            t.printStackTrace();
            System.exit(1);
        }

    }

    /**
     * Print usage message and exit
     */
    private static void printUsage() {
        String lSep = System.getProperty("line.separator");
        StringBuffer msg = new StringBuffer();
        msg.append("Wsdl2java " +
                JavaUtils.getMessage("emitter00")).append(lSep);
        msg.append(
                JavaUtils.getMessage("usage00",
                "java " + Wsdl2java.class.getName() + " [options] WSDL-URI"))
                .append(lSep);
        msg.append(JavaUtils.getMessage("options00")).append(lSep);
        msg.append(CLUtil.describeOptions(Wsdl2java.options).toString());
        System.out.println(msg.toString());
        System.exit(1);
    }

}
