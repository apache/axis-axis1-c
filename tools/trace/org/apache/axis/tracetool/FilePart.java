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
 * A piece of C++ source code 
 */
class FilePart {
	final static int UNKNOWN = 0;
	final static int COMMENT = 1;
	final static int METHOD = 2;
	final static int FIELD = 3;
	final static int BEGINSCOPE = 4;
	final static int ENDSCOPE = 5;
	final static int DIRECTIVE = 6;
	final static int WHITESPACE = 7;
	final static int MACRO = 8;
	final static int CLASSATTRIBUTE = 9;
	final static int ENUM = 10;

	protected String cppsource;
	protected int type;
	
	FilePart(String s, int type) {
		cppsource = s;
		this.type = type;
	}
	
    int getType() { return type; }	
    
	int length() {
		return cppsource.length();
	}
	
	public String toString() {
		return cppsource;
	}
}
