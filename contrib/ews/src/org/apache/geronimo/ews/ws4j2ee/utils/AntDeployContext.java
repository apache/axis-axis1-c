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

package org.apache.geronimo.ews.ws4j2ee.utils;

import org.apache.axis.wsdl.fromJava.Emitter;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;
import org.apache.geronimo.ews.ws4j2ee.toWs.Ws4J2eeDeployContext;
import org.apache.geronimo.ews.ws4j2ee.utils.packager.load.PackageModule;
import org.apache.geronimo.ews.ws4j2ee.utils.packager.load.PackageModuleFactory;

/**
 * @author hemapani@opensource.lk
 */
public class AntDeployContext implements Ws4J2eeDeployContext{
        private boolean compile = false;
		/**
		 * Field module
		 */
		private PackageModule module;

		/**
		 * Field moduleLocation
		 */
		private String moduleLocation;

		/**
		 * Field outputLocation
		 */
		private String outputLocation;

		/**
		 * Constructor GeronimoWsDeployContext
		 *
		 * @param moduleLocation
		 * @param outputLocation
		 */
		public AntDeployContext(String moduleLocation,
									   String outputLocation,ClassLoader parentCL) {
			module =
					PackageModuleFactory.createPackageModule(moduleLocation,parentCL, true);
			this.moduleLocation = moduleLocation;
			this.outputLocation = outputLocation;
		}

		/**
		 * Method getMode
		 *
		 * @return
		 */
		public int getMode() {
			return Emitter.MODE_ALL;
		}

		/**
		 * Method getWsdlImplFilename
		 *
		 * @return
		 */
		public String getWsdlImplFilename() {
			return null;
		}

		/**
		 * Method getModule
		 *
		 * @return
		 */
		public PackageModule getModule() {
			return module;
		}

		/**
		 * Method getModuleLocation
		 *
		 * @return
		 */
		public String getModuleLocation() {
			return moduleLocation;
		}

		/**
		 * Method getContanier
		 *
		 * @return
		 */
		public String getContanier() {
			return GenerationConstants.GERONIMO_CONTAINER;
		}

		/**
		 * Method getImplStyle
		 *
		 * @return
		 */
		public String getImplStyle() {
			return GenerationConstants.USE_INTERNALS;
		}

		/**
		 * Method getOutPutLocation
		 *
		 * @return
		 */
		public String getOutPutLocation() {
			return outputLocation;
		}
        /**
         * @return
         */
        public boolean isCompile() {
            return compile;
        }

	}
