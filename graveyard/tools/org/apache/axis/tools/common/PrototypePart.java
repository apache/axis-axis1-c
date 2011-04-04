/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
package org.apache.axis.tools.common;

/**
 * A function prototype in an include file and possibly in a class definition.
 */
public class PrototypePart extends FilePart {
	private Signature signature;

	public PrototypePart(String s, String className) {
		super(s, PROTOTYPE);
		signature = new Signature(s);
		if (null != className)
			signature.setClassName(className);
	}

	String className() {
		return signature.getClassName();
	}
	
	public Signature getSignature() {
		return signature;
	}
	
	public void setScope(String scope) {
		signature.setScope(scope);
	}
}
