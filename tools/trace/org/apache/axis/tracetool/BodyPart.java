/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
package org.apache.axis.tracetool;

/**
 * A snippet of C or C++ source code. If this snippet ends with a return 
 * statement, this body part also contains the return value.
 */
public class BodyPart {
	String codeFragment;
	String returnValue = null;

	BodyPart(String cf, String rv) {
		codeFragment = cf;
		if (null != rv && !Utils.isSpace(rv))
			returnValue = rv;
	}

	String getCodeFragment() {
		return codeFragment;
	}

	String getReturnValue() {
		if (returnValue != null)
			return returnValue.trim();
		else
			return null;
	}
}
