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
 * @author hemapani@opensource.lk
 */
public class EARPackageModule extends AbstractPackageModule {
    private UncompressingJarClassLoader cl;
	private Vector classPathElements;
    /**
     * @param jarFile
     * @throws GenerationFault
     */
    public EARPackageModule(String jarFile, boolean firstmodule)
        throws GenerationFault {
        super(jarFile);
        if (firstmodule) {
            cl =
                new UncompressingJarClassLoader(
                    GenerationConstants.CONFIG_STORE,
                    new File(zip.getName()),
                    null,
                    "");
        }
        wscfFile =
            getInputStreamForJarEntry(jarFile, "META-INF/webservice.xml");

        //TODO parse the application.xml and find the WAR and EAR files 
        File file = new File(cl.getDir());
        String[] files = file.list();
        PackageModule module = null;
        if(file != null){
			for (int i = 0; i < files.length; i++) {
				
				if (files[i].endsWith(".jar")) {
					module =
						PackageModuleFactory.createPackageModule(
						cl.getDir() + files[i],
							false);
					ejbJarfile = module.getEjbJarfile();		
					break;
				}
			}

            for (int i = 0; i < files.length; i++) {
                if (files[i].endsWith(".war")) {
                    module =
                        PackageModuleFactory.createPackageModule(
							cl.getDir() + files[i],
                            false);
                    webddfile = module.getWebddfile();
                    break;
                }
            }
            if (module == null)
                throw new GenerationFault("No jar module or war module find in EAR");
		}


        if (wscfFile == null && firstmodule)
            throw new GenerationFault("wscf file must not be null");
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.utils.packager.load.PackageModule#getClassLoaderWithPackageLoaded()
     */
    public ClassLoader getClassLoaderWithPackageLoaded() throws GenerationFault {
        return cl.getClassLoader();
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.utils.packager.load.PackageModule#getClassPathElements()
     */
    public Vector getClassPathElements() {
        return cl.getURLs();
    }

}
