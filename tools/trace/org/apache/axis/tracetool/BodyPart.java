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
      public final static int TRAILING = 0;
      public final static int RETURN = 1;
      public final static int CATCH = 2;

	private String codeFragment;
	private String returnValue = null;
      private Parameter caughtValue = null;
      private int type;

	BodyPart(String cf) {
		codeFragment = cf;
            type = TRAILING;
	}

	BodyPart(String cf, String rv) {
		codeFragment = cf;
		if (null != rv && !Utils.isSpace(rv)) {
                  type = RETURN;
			returnValue = rv;
            } else type = TRAILING;
	}

	BodyPart(String cf, Parameter cv) {
		codeFragment = cf;
		caughtValue = cv;
            type = CATCH;
	}

	String getCodeFragment() {
		return codeFragment;
	}

	boolean isTrailing() {
		return TRAILING==type;
	}

	boolean isReturn() {
		return RETURN==type;
	}

	boolean isCatch() {
		return CATCH==type;
	}

	String getReturnValue() {
		if (returnValue != null)
			return returnValue.trim();
		else
			return null;
	}

	Parameter getCaughtValue() {
		return caughtValue;
	}
}
