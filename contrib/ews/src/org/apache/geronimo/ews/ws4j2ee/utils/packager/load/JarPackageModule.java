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

package org.apache.geronimo.ews.ws4j2ee.utils.packager.load;

import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.Vector;

import org.apache.axis.utils.ClassUtils;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.UnrecoverableGenerationFault;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class JarPackageModule extends AbstractPackageModule {
    private ClassLoader cl;
    private Vector list = new Vector(1);
    /**
     * @param jarFile
     * @throws GenerationFault
     */
    public JarPackageModule(String jarFile, ClassLoader parentCL,boolean firstmodule)
        throws GenerationFault {
        super(jarFile,parentCL);
        try {
            this.parentCL = parentCL;
            list.add(new File(jarFile));
            if (firstmodule){
                if(parentCL == null){
                    throw new UnrecoverableGenerationFault("parent class loader must not be null");
                }
                cl = new URLClassLoader(new URL[]{(new File(jarFile)).toURL()},parentCL);
            }
            wscfFile =
                getInputStreamForJarEntry(jarFile, "META-INF/webservice.xml");
            if (wscfFile == null) {
                wscfFile = getInputStreamForJarEntry(jarFile, "webservice.xml");
            }
            webddfile = getInputStreamForJarEntry(jarFile, "META-INF/web.xml");
            if (wscfFile == null) {
                webddfile = getInputStreamForJarEntry(jarFile, "web.xml");
            }
            ejbJarfile = getInputStreamForJarEntry(jarFile, "META-INF/ejb-jar.xml");
            if (wscfFile == null && firstmodule)
                throw new GenerationFault("wscf file must not be null");
        } catch (MalformedURLException e) {
            throw GenerationFault.createGenerationFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.utils.packager.load.PackageModule#getClassLoaderWithPackageLoaded()
     */
    public ClassLoader getClassLoaderWithPackageLoaded() {
        return cl;
    }
	public Vector getClassPathElements() {
		return list;
	}
}
