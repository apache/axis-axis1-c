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

package org.apache.geronimo.ews.ws4j2ee.toWs;

import java.util.List;

import org.apache.axis.utils.CLArgsParser;
import org.apache.axis.utils.CLOption;
import org.apache.axis.utils.CLOptionDescriptor;

/**
 * @author hemapani
 */
public class Ws4J2eeCLOptionParser {
    // Define our short one-letter option identifiers.
    protected static final int SERVER_OPT = 's';
    protected static final int SKELETON_DEPLOY_OPT = 'S';
    protected static final int NAMESPACE_OPT = 'N';
    protected static final int NAMESPACE_FILE_OPT = 'f';
    protected static final int OUTPUT_OPT = 'o';
    protected static final int SCOPE_OPT = 'd';
    protected static final int TEST_OPT = 't';
    protected static final int PACKAGE_OPT = 'p';
    protected static final int ALL_OPT = 'a';
    protected static final int TYPEMAPPING_OPT = 'T';
    protected static final int FACTORY_CLASS_OPT = 'F';
    protected static final int HELPER_CLASS_OPT = 'H';
    protected static final int USERNAME_OPT = 'U';
    protected static final int PASSWORD_OPT = 'P';
	protected static final int IMPL_STYLE_OPT = 'I';
	protected static final int CONTAINER_OPT = 'C';

    private String wscffile;
    private String outputDirectory = ".";
    private boolean isServerSide = false;
    private String userName;
    private String password;
    private String implStyle = GenerationConstants.USE_LOCAL_AND_REMOTE;
    private String contanier = GenerationConstants.JBOSS_CONTAINER;

    protected static final CLOptionDescriptor[] options = new CLOptionDescriptor[]{
        new CLOptionDescriptor("server-side",
                CLOptionDescriptor.ARGUMENT_OPTIONAL,
                SERVER_OPT,
                "Genarate Server side codes"),
        new CLOptionDescriptor("output",
                CLOptionDescriptor.ARGUMENT_REQUIRED,
                OUTPUT_OPT,
                "output Directory "),
        new CLOptionDescriptor("user",
                CLOptionDescriptor.ARGUMENT_REQUIRED,
                USERNAME_OPT,
                "user name"),
        new CLOptionDescriptor("password",
                CLOptionDescriptor.ARGUMENT_REQUIRED,
                PASSWORD_OPT,
                "password"),
		new CLOptionDescriptor("implStyle",
					   CLOptionDescriptor.ARGUMENT_REQUIRED,
					   IMPL_STYLE_OPT,
					   "impelemtation Style"),  
		new CLOptionDescriptor("container",
							   CLOptionDescriptor.ARGUMENT_REQUIRED,
							   CONTAINER_OPT,
							   "the J2EE contianer")   					         
    };

    public Ws4J2eeCLOptionParser(String[] args) {

        CLArgsParser argsParser = new CLArgsParser(args, options);

        // Print parser errors, if any
        if (null != argsParser.getErrorString()) {
            System.err.println(argsParser.getErrorString());
            //printUsage();
        }

        // Get a list of parsed options
        List clOptions = argsParser.getArguments();
        int size = clOptions.size();

        try {
            // Parse the options and configure the emitter as appropriate.
            for (int i = 0; i < size; i++) {
                parseOption((CLOption) clOptions.get(i));
            }

            // validate argument combinations
            //
            //validateOptions();

            //parser.run(wsdlURI);

            // everything is good
            //System.exit(0);
        } catch (Throwable t) {
            t.printStackTrace();
            System.exit(1);
        }

    }

    protected void parseOption(CLOption option) {
        switch (option.getId()) {
            case SERVER_OPT:
                isServerSide = true;

                break;

            case OUTPUT_OPT:
                outputDirectory = option.getArgument();
                break;

            case USERNAME_OPT:
                userName = option.getArgument();
                break;

            case PASSWORD_OPT:
                password = option.getArgument();
                break;

            case CLOption.TEXT_ARGUMENT:
                if (wscffile != null) {
                    throw new UnrecoverableGenarationFault("Only one arguement allowed ");
                    //printUsage();
                }
                wscffile = option.getArgument();
                break;
            case IMPL_STYLE_OPT: 
            	this.implStyle = option.getArgument();
				break;	 
			case CONTAINER_OPT: 
				this.contanier = option.getArgument();
				break;	 	 
            default:
                throw new UnrecoverableGenarationFault("unknown option");
        }
    } // parseOption

    /**
     * @return 
     */
    public String getWscffile() {
        return wscffile;
    }

    /**
     * @param string 
     */
    public void setWscffile(String string) {
        wscffile = string;
    }

    /**
     * @return 
     */
    public boolean isServerSide() {
        return isServerSide;
    }

    /**
     * @return 
     */
    public String getOutputDirectory() {
        return outputDirectory;
    }

    /**
     * @return 
     */
    public String getPassword() {
        return password;
    }

    /**
     * @return 
     */
    public String getUserName() {
        return userName;
    }

    /**
     * @param b 
     */
    public void setServerSide(boolean b) {
        isServerSide = b;
    }

    /**
     * @param string 
     */
    public void setOutputDirectory(String string) {
        outputDirectory = string;
    }

    /**
     * @param string 
     */
    public void setPassword(String string) {
        password = string;
    }

    /**
     * @param string 
     */
    public void setUserName(String string) {
        userName = string;
    }
	/**
	 * @return
	 */
	public String getImplStyle() {
		return implStyle;
	}

	/**
	 * @param string
	 */
	public void setImplStyle(String string) {
		implStyle = string;
	}

	/**
	 * @return
	 */
	public String getContanier() {
		return contanier;
	}

	/**
	 * @param string
	 */
	public void setContanier(String string) {
		contanier = string;
	}

}
