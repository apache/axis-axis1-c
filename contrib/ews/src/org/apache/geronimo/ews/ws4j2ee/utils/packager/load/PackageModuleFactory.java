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

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class PackageModuleFactory {

    /**
     * @param path - path to the package
     * @param firstmodule - is it the first module or a module inside other module
     * @return
     * @throws GenerationFault
     */
    public static PackageModule createPackageModule(
        String path,boolean firstmodule)throws GenerationFault {
        if (path != null) {
            if (path.endsWith(".jar") || path.endsWith(".JAR"))
                return new JarPackageModule(path, firstmodule);
            else if (path.endsWith(".war") || path.endsWith(".WAR"))
                return new WARPackageModule(path, firstmodule);
            else if (path.endsWith(".ear") || path.endsWith(".EAR"))
                return new EARPackageModule(path, firstmodule);
            else
                throw new GenerationFault("unknown type of file");
        }
        throw new GenerationFault("path is null");
    }
}
