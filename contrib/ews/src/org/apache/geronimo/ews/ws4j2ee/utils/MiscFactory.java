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

import java.io.InputStream;

import org.apache.geronimo.ews.ws4j2ee.context.InputOutputFile;
import org.apache.geronimo.ews.ws4j2ee.context.impl.InputOutputFileImpl;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author hemapani@opensource.lk
 */
public class MiscFactory {
	public static InputOutputFile getInputFile(
			String fileName,
			InputStream instream) {
			return new InputOutputFileImpl(fileName, instream);
		}
    
		public static InputOutputFile getInputFile(
			String fileName) throws GenerationFault {
			return new InputOutputFileImpl(fileName);
		}
		public static InputOutputFile getInputFile(
			InputStream instream) {
			return new InputOutputFileImpl(instream);
		}	
}
