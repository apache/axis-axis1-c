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

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.UnrecoverableGenerationFault;

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
			String path,boolean firstmodule)throws UnrecoverableGenerationFault{
		return createPackageModule(path,Thread.currentThread().getContextClassLoader(),firstmodule);
	}
			
			
    public static PackageModule createPackageModule(
        String path,
    	ClassLoader parentCL,
        boolean firstmodule)throws UnrecoverableGenerationFault{
        try {
            if (path != null) {
            	File file = new File(path);
                if(!file.exists())
                    throw new UnrecoverableGenerationFault("file not found "+file.getAbsolutePath());
            	if(file.isDirectory()){
            		return new DirPackageModule(path,parentCL);
            	}else if (path.endsWith(".jar") || path.endsWith(".JAR"))
                    return new JarPackageModule(path,parentCL,firstmodule);
                else if (path.endsWith(".war") || path.endsWith(".WAR"))
                    return new WARPackageModule(path, parentCL, firstmodule);
                else if (path.endsWith(".ear") || path.endsWith(".EAR"))
                    return new EARPackageModule(path, parentCL, firstmodule);
                else if(path.endsWith(".xml"))
					return new DirPackageModule(new File(path));
                else
					throw new UnrecoverableGenerationFault("unknown type of file");
            }
        } catch (GenerationFault e) {
            throw new UnrecoverableGenerationFault(path + " not found ",e);
        }
        throw new UnrecoverableGenerationFault("path is null");
    }
}
