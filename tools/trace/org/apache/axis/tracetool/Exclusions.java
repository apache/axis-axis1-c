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

public class Exclusions {

	private final static Set badFiles =
		new HashSet(Arrays.asList(new Object[] {
		// Tool fails on these files
		"Url.cpp",
			"libAxiscpp.cpp",
			"cpplex.cpp",
			"cppyacc.cpp",
			"asciitab.h",
			"iasciitab.h",
			"latin1tab.h",
			"spp_converter.h",
			"spp_converter.c",
			"spp_tokenizer.c",
			"utf8tab.h",
			"SoapBinInputStream.h",
			"SoapInputSource.h",
			"XMLParserXerces.h",
			"apr_base64.c",
			"apr_base64.h",
			"apr_xlate.h",
			"Channel.hpp",
			"Channel.h",
			"Channel.cpp",
                  "Param.h",
                  "Array.hpp",
                  "Buffer.hpp",
                  "SOAPTransport.h",
                  "SoapDeSerializer.h",
                  "SoapDeSerializer.cpp",
                  "Call.cpp",
		// Axis.cpp contains a copyright sign (circle with a "C" in it) which 
		// makes readline throw a MalformedInputException on linux possibly due to 
		// locale/charset problems.
		"Axis.cpp",
		// spp.c contains a bad return statement that looks like it 
		// shouldn't compile
		"spp.c",
		//Don't trace trace
		"AxisTrace.cpp", "AxisTrace.h", "GDefine.h", "AxisFile.h" }));

	static boolean shouldTraceFile(String s) {
		return !badFiles.contains(s);
	}

	// TODO: needs implementing
	static boolean shouldTraceClass(String s) {
		return true;
	}

	// TODO: needs implementing
	static boolean shouldTraceMethod(String className, String method) {
		return true;
	}
}
