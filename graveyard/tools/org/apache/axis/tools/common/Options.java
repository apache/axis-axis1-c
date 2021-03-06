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

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/**
 * Command line options passed to a tool's main program. All 
 * command line options should begin with a dash "-". Some 
 * command line options take a value which is the next parameter 
 * after the option. Others do not.
 */
public class Options {
	static HashMap pairs = new HashMap();
	static List values = new ArrayList();

    /**
     * No one constructs this class.
     */
	private Options() {
	}

    /**
     * Initialises the options based on the args passed to main
     */
	public static void set(String args[]) {
		for (int i = 0; i < args.length; i++) {
			if (args[i].startsWith("-")) {
				if (i + 1 < args.length || !args[i + 1].startsWith("-")) {
					String key = args[i];
					Object pairValue = pairs.get(key);
					if (null == pairValue){
						pairs.put(args[i], args[i + 1]);
					} else if (pairValue instanceof String) {
						List l = new ArrayList();
						l.add(pairValue);
						l.add(args[i + 1]);
						pairs.put(key, l);
					} else if (pairValue instanceof List){
						 ((List) pairValue).add(args[i + 1]);
					}
					i++; // Step over value for this key
				} else
					values.add(args[i]);
			}
		}
	}

	public static Object getOption(String key) {
		return pairs.get(key);
	}

	static boolean isOptionSet(String key) {
		return values.contains(key);
	}

	public static boolean verbose() {
		return isOptionSet("-verbose");
	}

	public static boolean quiet() {
		return isOptionSet("-quiet");
	}
}
