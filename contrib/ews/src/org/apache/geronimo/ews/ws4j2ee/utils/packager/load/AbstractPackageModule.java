
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

import java.io.IOException;
import java.io.InputStream;
import java.util.jar.JarFile;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public abstract class AbstractPackageModule implements PackageModule {
    protected InputStream wscfFile;
    protected InputStream webddfile;
    protected InputStream ejbJarfile;
    protected InputStream wsdlfile;
    protected InputStream jaxrpcfile;
    protected ZipFile zip;

    public AbstractPackageModule(String jarFile) throws GenerationFault {
        try {
            zip = new JarFile(jarFile);
        } catch (IOException e) {
            e.printStackTrace();
            throw GenerationFault.createGenerationFault(e);
        }
    }
    public InputStream getInputStreamForJarEntry(String path)
        throws GenerationFault {
        try {
            ZipEntry zentry = zip.getEntry(path);
            if (zentry != null) {
                return zip.getInputStream(zentry);
            } else {
                return null;
            }
        } catch (IOException e) {
            e.printStackTrace();
            throw GenerationFault.createGenerationFault(e);
        }
    }

    public InputStream getInputStreamForJarEntry(String jarFile, String path)
        throws GenerationFault {
        try {
            ZipEntry zentry = zip.getEntry(path);
            if (zentry != null) {
                return zip.getInputStream(zentry);
            } else {
                return null;
            }
        } catch (IOException e) {
            e.printStackTrace();
            throw GenerationFault.createGenerationFault(e);
        }
    }

    public void loadtheClassesInJarFile() throws GenerationFault {
    }

    /**
     * @return
     */
    public InputStream getEjbJarfile() {
        return ejbJarfile;
    }

    /**
     * @return
     */
    public InputStream getWebddfile() {
        return webddfile;
    }

    /**
     * @return
     */
    public InputStream getWscfFile() {
        return wscfFile;
    }

    /**
     * @param stream
     */
    public void setEjbJarfile(InputStream stream) {
        ejbJarfile = stream;
    }

    /**
     * @param stream
     */
    public void setWebddfile(InputStream stream) {
        webddfile = stream;
    }

    /**
     * @param stream
     */
    public void setWscfFile(InputStream stream) {
        wscfFile = stream;
    }

}
