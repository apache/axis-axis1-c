/*
 *   Copyright 2003-2004 The Apache Software Foundation.
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

/**
 * @author Srinath Perera(hemapani
 */

package org.apache.axis.wsdl.wsdl2ws;

import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class WebServiceGeneratorImpl implements WebServiceGenerator
{
    private WebServiceContext wscontext;
    public WebServiceGeneratorImpl(WebServiceContext wscontext)
    {
        this.wscontext = wscontext;
    }

    /**
     * Generate the wrapper generator, Service generator,Param Generator and call
     * Generate on them.
     * @see org.apache.axis.wsdl.wsdl2ws.WebServiceGenerator#generate()
     */
    public void generate() throws WrapperFault
    {
        String language = wscontext.getWrapInfo().getWrapperLanguage();

        if (WrapperConstants.LANGUAGE_JAVA.equalsIgnoreCase(language))
        {
            (new Generator(WrapperConstants.GENERATOR_WRAPPER_JAVA, wscontext))
                .generate();
            (new Generator(WrapperConstants.GENERATOR_SERVICE_JAVA, wscontext))
                .generate();
            (new Generator(WrapperConstants.GENERATOR_PARAM_JAVA, wscontext))
                .generate();
        }
        else
        {

            if (WrapperConstants.LANGUAGE_CPP.equalsIgnoreCase(language))
            {
                if (WrapperConstants
                    .SERVER
                    .equals(wscontext.getWrapInfo().getTargetEngine()))
                {
                    // Generate Server objects
                    (new Generator(WrapperConstants.GENERATOR_WRAPPER_CPP,
                        wscontext))
                        .generate();
                    (new Generator(WrapperConstants.GENERATOR_WRAPPER_HPP,
                        wscontext))
                        .generate();
                    (new Generator(WrapperConstants.GENERATOR_SERVICE_CPP,
                        wscontext))
                        .generate();
                    (new Generator(WrapperConstants.GENERATOR_SERVICE_HPP,
                        wscontext))
                        .generate();
                    (new Generator(WrapperConstants.GENERATOR_CLASSLOADER_CPP,
                        wscontext))
                        .generate();
                    (new Generator(WrapperConstants.GENERATOR_DEPLOYMENT,
                        wscontext))
                        .generate();
                    (new Generator(WrapperConstants.GENERATOR_SERVER_EXCEPTION,
                        wscontext))
                        .generate();
                    (new Generator(WrapperConstants.GENERATOR_UNDEPLOYMENT,
                        wscontext))
                        .generate();
                }
                else
                {
                    // Generate Client objects
                    (new Generator(WrapperConstants.GENERATOR_CLIENT_STUB_CPP,
                        wscontext))
                        .generate();
                    (new Generator(WrapperConstants.GENERATOR_CLIENT_STUB_HPP,
                        wscontext))
                        .generate();
                    (new Generator(WrapperConstants.GENERATOR_CLIENT_EXCEPTION,
                        wscontext))
                        .generate();
                }
                // Generate objects common to Client and Server
                (new Generator(WrapperConstants.GENERATOR_PARAM_CPP_ALL,
                    wscontext))
                    .generate();
            }
            else
            {

                if (WrapperConstants.LANGUAGE_C.equalsIgnoreCase(language))
                {
                    if (WrapperConstants
                        .SERVER
                        .equals(wscontext.getWrapInfo().getTargetEngine()))
                    {
                        // Generate Server objects
                        (new Generator(WrapperConstants.GENERATOR_WRAPPER_C,
                            wscontext))
                            .generate();
                        (new Generator(WrapperConstants.GENERATOR_WRAPPER_H,
                            wscontext))
                            .generate();
                        (new Generator(WrapperConstants.GENERATOR_SERVICE_C,
                            wscontext))
                            .generate();
                        (new Generator(WrapperConstants.GENERATOR_CLASSLOADER_C,
                            wscontext))
                            .generate();
                        (new Generator(WrapperConstants.GENERATOR_DEPLOYMENT,
                            wscontext))
                            .generate();
                        (new Generator(WrapperConstants.GENERATOR_UNDEPLOYMENT,
                            wscontext))
                            .generate();
                    }
                    else
                    {
                        // Generate Client Objects
                        (new Generator(WrapperConstants.GENERATOR_CLIENT_STUB_C,
                            wscontext))
                            .generate();
                        (new Generator(WrapperConstants.GENERATOR_CLIENT_STUB_H,
                            wscontext))
                            .generate();

                    }
                    // Generate objects common to Client and Server
                    (new Generator(WrapperConstants.GENERATOR_PARAM_C_ALL,
                        wscontext))
                        .generate();
                }
                else
                {
                    throw new WrapperFault("Unsupported Language" + language);
                }
            }
            /*
            * Ensure the BuildScript generator is called last.
            * If called earlier not all files will be added
            * to the build script(Ex : to Makefile.am).
            */ 
            (new Generator(WrapperConstants.GENERATOR_BUILDSCRIPT, wscontext))
                .generate();
        }
    }
}
