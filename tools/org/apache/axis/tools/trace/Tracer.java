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
package org.apache.axis.tools.trace;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.Set;
import java.util.StringTokenizer;

import org.apache.axis.tools.common.*;

/**
 * A Buffered write that also contains the methods to add in in trace
 * TODO: Add in &this and threadid into each trace record
 */
class Tracer extends BufferedWriter {
	private Signature signature = null;
	private final static String SIGNATURE = "  /* AUTOINSERTED TRACE */";
	private Headers headers;
	private String namespace = null;
	private String hashifdef = null;
	private String hashelse = null;
	private String hashendif = null;
	private String module = null;

	private static Hashtable typetable = new Hashtable();
	static {
		typetable.put("char", "CHAR");
		typetable.put("unsigned char", "CHAR");
		typetable.put("unsigned short", "USHORT");
		typetable.put("short", "SHORT");
		typetable.put("signed short", "SHORT");
		typetable.put("unsigned", "UINT");
		typetable.put("unsigned int", "UINT");
		typetable.put("int", "INT");
		typetable.put("signed int", "INT");
		typetable.put("signed", "INT");
		typetable.put("unsigned long", "ULONG");
		typetable.put("long", "LONG");
		typetable.put("signed long", "LONG");
		typetable.put("unsigned double", "UDOUBLE");
		typetable.put("double", "DOUBLE");
		typetable.put("float", "FLOAT");
		typetable.put("bool", "BOOL");
		typetable.put("string", "STLSTRING");
		typetable.put("AxisString", "STLSTRING");
		typetable.put("AxisXMLString", "STLSTRING");
		typetable.put("xsd__string", "STLSTRING");
	}

	private final static Set charSet =
		new HashSet(
			Arrays.asList(
				new Object[] { "char", "AxisChar", "AxisXMLChar", "XML_Ch" }));

	/**
	 * @param writer a writer to the output file.
	 */
	Tracer(Writer writer, int depth, Headers headers, boolean isInLib) throws IOException {
		super(writer);
		this.headers = headers;
		namespace = Configuration.getConfigured("namespace");
		if (null != namespace)
			namespace += "::";
		else
			namespace = "";
		
		hashifdef = Configuration.getConfigured("ifdef");
		if (null != hashifdef) {
			hashifdef = "#ifdef " + hashifdef + "\n";
			hashelse = "#else\n";
			hashendif = "#endif\n";
		} else {
			hashifdef = "";
			hashelse = "";
			hashendif = "";
		}

		module = Configuration.getConfigured("module");
		if (null != module)
			module += "::";
		else
			module = ""; // C-style function

            String libDirDef = "";
            if (isInLib) libDirDef = "#define AXISTRACE_LIBRARY\n";

		String include = Configuration.getConfigured("include");
		String includefile = "";
		if (null == include) {
			String prefix = "";
			if (depth > 1)
				for (int i = 1; i < depth; i++)
					prefix += "../";
			includefile = "\"" + prefix + "common/AxisTrace.h\"";

		} else {
			includefile = include;
		}

		String prefix = "";
		if (depth > 1)
			for (int i = 1; i < depth; i++)
				prefix += "../";

		String line =
			hashifdef
				+ "/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */\n"
                        + libDirDef
				+ "#include "
				+ includefile
				+ "\n"
				+ hashendif;
		writeTrace(line);
		flush();
	}

	/**
	 * @param signature the signature of this method
	 * TODO: Can't tell the difference between static and non-static 
	 * methods so can't tell whether to pass this or not. If we pass
	 * this in a static method it won't compile. 
	 */
	void traceEntry(Signature signature) throws IOException {
		this.signature = signature;
		if (!signature.traceable())
			return;

		Parameter[] parms = signature.getParameters();
		int len = 0;
		if (null != parms) {
			if (parms[parms.length - 1].isDotDotDot())
				len = parms.length - 1;
			else
				len = parms.length;
		}

		String that = "NULL";
		if (headers.isInstanceMethod(signature))
			that = "this";

		String line =
			"\n"
				+ "\t"
				+ hashifdef
				+ "\t\tif ("
				+ namespace
				+ module
				+ "isTraceOn())\n"
				+ "\t\t\t"
				+ namespace
				+ module
				+ "traceEntry("
				+ getClassName()
				+ ", \""
				+ signature.getMethodName()
				+ "\", "
				+ that
				+ ", "
				+ len;
		for (int i = 0; null != parms && i < parms.length; i++)
			line += getTypeParms(parms[i]);
		line += ");\t" + SIGNATURE + "\n";
		line += "\t" + hashendif;
		writeTrace(line);
		flush();
	}

	void traceExit(int returnIndex) throws Exception {
		if (!signature.traceable())
			return;

		// Check this method really should return void
		if (null != signature.getReturnType().getType())
			Utils.rude(
				"Expecting to return void from a method that returns a value: "
					+ signature.toString());

		// Enclose the printf/return in {} in case if/then doesn't have {}
		String line = "\t{\n";
		line += "\t\t" + hashifdef;
		line += "\t\t\tif (" + namespace + module + "isTraceOn())\n";
		line += "\t\t\t\t"
			+ namespace
			+ module
			+ "traceExit("
			+ getClassName()
			+ ", \""
			+ signature.getMethodName()
			+ "\", "
			+ returnIndex
			+ ");\t"
			+ SIGNATURE
			+ "\n";
		line += "\t\t" + hashendif;

		// now print out the return line itself
		line += "\t\treturn;\n";
		line += "\t}\n";
		writeTrace(line);
		flush();
	}

	/**
	 * Takes in the return statement and traces out the exit trace statement for it
	 * This method prints out the complete return line as well so the user
	 * does not need to print this out themselves. 
	 */
	void traceExit(String value, int returnIndex) throws Exception {
		if (!signature.traceable())
			return;

		// Check this method doesn't return void
		if (null == signature.getReturnType().getType())
			Utils.rude(
				"Expecting to return a value from a method that returns void: "
					+ signature.toString());

		// Enclose the printf/return in {} in case if/then doesn't have {}
		// Copy the return value into a local called traceRet in case the
		// return value has side-effects such as "return i++;" or "return func();"
		// This makes sure that we don't execute the return value twice.
		// Unfortunately if the return value is a class we will invoke 
		// a copy constructor. When initialising traceRet with value, put value
		// in brackets in case it contains an operator that might be invoked
		// after the assignment, like another assignment.
		String line = "\t{\n";
		line += "\t\t" + hashifdef;
		line += "\t\t\t"
			+ signature.getReturnType().getType()
			+ " traceRet = ("
			+ value
			+ ");\n";
		line += "\t\t\tif (" + namespace + module + "isTraceOn())\n";
		line += "\t\t\t\t"
			+ namespace
			+ module
			+ "traceExit("
			+ getClassName()
			+ ", \""
			+ signature.getMethodName()
			+ "\", "
			+ returnIndex
			+ getTypeParms(signature.getReturnType())
			+ ");\t"
			+ SIGNATURE
			+ "\n";
		line += "\t\t\treturn traceRet;\n";
		line += "\t\t" + hashelse;
		if (hashelse.length() > 0)
			line += "\t\t\treturn " + value + ";\n";
		line += "\t\t" + hashendif;
		line += "\t}\n";
		writeTrace(line);
		flush();
	}

	void traceCatch(Parameter value, int catchIndex) throws Exception {
		if (!signature.traceable())
			return;

		String line =
			"\n"
				+ "\t"
				+ hashifdef
				+ "\t\tif ("
				+ namespace
				+ module
				+ "isTraceOn())\n"
				+ "\t\t\t"
				+ namespace
				+ module
				+ "traceCatch("
				+ getClassName()
				+ ", \""
				+ signature.getMethodName()
				+ "\", "
				+ catchIndex
				+ getTypeParms(value);
		line += ");\t" + SIGNATURE + "\n";
		line += "\t" + hashendif;
		writeTrace(line);
		flush();
	}

	/*
	 * This method is careful to get the line separators because other
	 * other methods have been careless assuming that the line separator
	 * is always only \n, whereas it maybe \r\n.
	 */
	public void writeTrace(String s) throws IOException {
		if (s.startsWith("\n") || s.startsWith("\r"))
			super.newLine();
		StringTokenizer st = new StringTokenizer(s, "\n\r");
		while (st.hasMoreTokens()) {
			super.write(st.nextToken());
			if (st.hasMoreTokens())
				super.newLine();
		}
		if (s.endsWith("\n") || s.endsWith("\r"))
			super.newLine();
		if (Options.verbose())
			System.out.print(s);
	}

	// TODO cope with STL strings
	// TODO cope with pointers to primitives
	// TODO cope with references
	private String getTypeParms(Parameter p) {
		// copes with catch (...)
		if ("...".equals(p.getType()))
			return " ";

		String parms = ",\n\t\t\t\t\tTRACETYPE_";
		String name = p.getName();
		if (null == name)
			name = "traceRet";
		name = "((void*)&" + name + ")";

		String type = p.getTypeWithoutConst();
		if (null == type || 0 == type.length()) {
			parms += "UNKNOWN, 0, NULL";
		} else if (typetable.keySet().contains(type)) {
			parms += (String) typetable.get(type) + ", 0, " + name;
		} else if (type.endsWith("*")) {
			String contents = type.substring(0, type.length() - 1);
			if (charSet.contains(contents)) {
				parms += "STRING, 0, " + name;
			} else if ("void".equals(contents)) {
				// We just don't know what this void* is pointing at 
				// so that best we can do is to print out the first byte.
				parms += "POINTER, 1, " + name;
			} else {
				parms += "POINTER, sizeof(" + contents + "), " + name;
			}
		} else if (type.endsWith("&")) {
			String contents = type.substring(0, type.length() - 1);
			if (typetable.keySet().contains(contents)) {
				parms += (String) typetable.get(contents) + ", 0, " + name;
			} else {
				parms += "DATA, sizeof(" + type + "), " + name;
			}
		} else {
			parms += "DATA, sizeof(" + type + "), " + name;
		}

		return parms;
	}

	private String getClassName() {
		String name;
		if (null != signature.getClassName()) {
			name = signature.getClassName();
			name = name.substring(0, name.indexOf("::"));
			name = "\"" + name + "\"";
		} else
			name = "NULL";
		return name;
	}
}
