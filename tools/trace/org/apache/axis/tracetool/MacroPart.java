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

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.StringTokenizer;

/**
 * A C or C++ macro as it is used in the source code
 * TODO This is a simple implementation that could be improved considerably.
 * This implementation is just good enough for Axis C++.
 */
class MacroPart extends FilePart {

	private final static Set knownDefines =
		new HashSet(
			Arrays.asList(
				new Object[] {
					"AXIS_CPP_NAMESPACE_START",
					"AXIS_CPP_NAMESPACE_END",
					"AXIS_CPP_NAMESPACE_USE",
					"AXIS_CPP_NAMESPACE_PREFIX",
                              "XERCES_CPP_NAMESPACE_USE",
					"TXPP_NAMESPACE_START",
					"TXPP_NAMESPACE_END" }));
	private final static Set knownMacros =
		new HashSet(
			Arrays.asList(
				new Object[] {
					"DEFINE_UTF16_TO_UTF8",
					"DEFINE_UTF16_TO_UTF16" }));

	/**
	 * Factory method to create a MacroPart.
	 * @param s unparsed source code which may start with a define or macro.
	 */
	static MacroPart create(String s) {
		String orig = getOriginalText(s);
		if (null == orig)
			return null;
		return new MacroPart(orig);
	}

	MacroPart(String s) {
		super(s, FilePart.MACRO);
	}

	/**
	 * @param s unparsed source code which may start with a define or macro.
	 * @return all of s up to the end of the define or macro.
	 */
	private static String getOriginalText(String s) {
		String name = getName(s);
		int len = name.length();
		if (null == name)
			return null;
		else if (knownDefines.contains(name)) {
			return s.substring(0, len);
		} else if (knownMacros.contains(name)) {
			String rest = s.substring(len);
			len += Utils.findMatching(rest, '(', ')');
			return s.substring(0, len + 1);
		} else
			return null;
	}

	static boolean isAMacro(String s) {
		if (s == null || 0 == s.length())
			return false;
		String name = getName(s);
		return knownMacros.contains(name) || knownDefines.contains(name);
	}

	private static String getName(String s) {
		int i;
		for (i = 0; i < s.length(); i++)
			if (!Character.isLetterOrDigit(s.charAt(i)) && '_' != s.charAt(i))
				break;
		if (s.length() == i)
			return null;
		return s.substring(0, i);
	}
}
