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

import java.util.Iterator;
import java.util.List;

/**
 * A parameter from a method signature. The parameter is the datatype plus its 
 * name but not its value. 
 */
class Parameter {
	private String type = null;
	private String name = null;
	private boolean failed = false;

	Parameter(List parts) {
		this(parts, false);
	}

	Parameter(List parts, boolean isRetType) {
		if (parts == null || parts.size() == 0)
			return;

		if (!isRetType && parts.size() == 1) {
			if (!"void".equals(parts.get(0)))
				failed = true; // Seems like bad C++ code here
			return;
		}

		if (isRetType) {
			Iterator it = parts.iterator();
			while (it.hasNext()) {
				String next = (String) it.next();
				if (null == type)
					type = next;
				else if ("*".equals(next) || "&".equals(next))
					type += next;
				else
					type += " " + next;
			}
			
			// Some methods return have void on their signature and others
			// have nothing. So to make them both the same, if a method 
			// doesn't return anything make type null.
			if ("void".equals(type))
				type = null;

		} else {
			// Keeping track of next and prev ensures we don't append the
			// parameter name onto the type. 
			Iterator it = parts.iterator();
			String next = null, prev = (String) it.next();
			while (it.hasNext()) {
				next = (String) it.next();
				if (null == type)
					type = prev;
				else if ("*".equals(prev) || "&".equals(prev))
					type += prev;
				else
					type += " " + prev;
				prev = next;
			}
			name = next;
		}
	}

	boolean failed() {
		return failed;
	}

	String getType() {
		return type;
	}

	String getName() {
		return name;
	}

	boolean isVoid() {
		return null == type;
	}

	public String toString() {
		if (null == type)
			return "void";
		if (null == name)
			return type;
		return type + " " + name;
	}
}
