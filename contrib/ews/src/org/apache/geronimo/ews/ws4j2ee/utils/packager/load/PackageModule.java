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

import java.io.InputStream;
import java.util.Vector;

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * <p>This reprsents a packaged module jar,WAR,EAR file. the implementation
 * classes of this interface should provide the acsses to the DD files and give
 * a class loader that load the class files in the jar file.</p>
 * @author hemapani
 */
public interface PackageModule {
    public InputStream getEjbJarfile() throws GenerationFault;
    public InputStream getWebddfile() throws GenerationFault; 
    public InputStream getWscfFile() throws GenerationFault;
    public void setEjbJarfile(InputStream stream) throws GenerationFault;
    public void setWebddfile(InputStream stream) throws GenerationFault;
    public void setWscfFile(InputStream stream) throws GenerationFault;
    public ClassLoader getClassLoaderWithPackageLoaded() throws GenerationFault;
    public Vector getClassPathElements() throws GenerationFault;
}
