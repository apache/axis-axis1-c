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
import java.util.Vector;

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.utils.UncompressingJarClassLoader;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class WARPackageModule extends AbstractPackageModule {
    private UncompressingJarClassLoader cl;
    /**
     * @param jarFile
     * @throws GenerationFault
     */
    public WARPackageModule(String jarFile, boolean firstmodule)
        throws GenerationFault {
        super(jarFile);
        if (firstmodule) {
            cl =
                new UncompressingJarClassLoader(
					GenerationConstants.CONFIG_STORE,
                    new File(zip.getName()),
                    "WEB-INF/classes",
                    "WEB-INF/lib");
        }
        wscfFile = getInputStreamForJarEntry(jarFile, "WEB-INF/webservice.xml");
        if (wscfFile == null) {
            wscfFile = getInputStreamForJarEntry(jarFile, "webservice.xml");
        }
        webddfile = getInputStreamForJarEntry(jarFile, "WEB-INF/web.xml");
        if (webddfile == null)
            webddfile = getInputStreamForJarEntry(jarFile, "web.xml");
        if (wscfFile == null && firstmodule)
            throw new GenerationFault("wscf file must not be null");
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.utils.packager.load.PackageModule#getClassLoaderWithPackageLoaded()
     */
    public ClassLoader getClassLoaderWithPackageLoaded() throws GenerationFault {
        return cl.getClassLoader();
    }
	public Vector getClassPathElements() {
		return cl.getURLs();
	}

}
