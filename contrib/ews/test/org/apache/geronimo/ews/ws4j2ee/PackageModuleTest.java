/*
 * Copyright 2001-2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.geronimo.ews.ws4j2ee;

import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;

import org.apache.geronimo.ews.AbstractTestCase;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.utils.packager.load.PackageModule;
import org.apache.geronimo.ews.ws4j2ee.utils.packager.load.PackageModuleFactory;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class PackageModuleTest extends AbstractTestCase {

    /**
     * @param testName
     */
    public PackageModuleTest(String testName) {
        super(testName);
    }

    public void testLoadWarFile()
        throws GenerationFault, ClassNotFoundException {
        PackageModule wmod =
            PackageModuleFactory.createPackageModule(
                "target/generated/samples/simple.war",
                true);
        ClassLoader cl = wmod.getClassLoaderWithPackageLoaded();
        //TODO uncommnet this when the classloading fixed
        //cl.loadClass("com.jwsbook.jaxrpc.BookQuote");
    }
    public void testLoadEarFile()
        throws GenerationFault, ClassNotFoundException {
        PackageModule wmod =
            PackageModuleFactory.createPackageModule(
                "target/generated/samples/bookquote.ear",
                true);
        ClassLoader cl = wmod.getClassLoaderWithPackageLoaded();
        cl.loadClass("com.jwsbook.jaxrpc.BookQuote");
    }
    
    public void testLoadJarUsingURLClassLoader() throws MalformedURLException, ClassNotFoundException{
    	URLClassLoader cl = new URLClassLoader(new URL[]{(new File("target/temp/bookquote.jar")).toURL()});
		cl.loadClass("com.jwsbook.jaxrpc.BookQuote");
    }

}
