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
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.Hashtable;

/**
 * A Buffered write that also contains the methods to add in in trace
 * TODO: Add in &this and threadid into each trace record
 * TODO: Sort out indentation
 */
class Tracer extends BufferedWriter {
	private Signature signature = null;
	private final static String SIGNATURE = "  /* AUTOINSERTED TRACE */";

      // Escape ?'s here to avoid trigraphs which map ??) to ]
	private final static String UNKNOWN_FORMAT = "\\?\\?\\?\\?";

	private static Hashtable primitives = new Hashtable();
	static {
		primitives.put("int", "%i");
		primitives.put("unsigned int", "%u");
		primitives.put("unsigned", "%u");
		primitives.put("short", "%hi");
		primitives.put("short int", "%hi");
		primitives.put("unsigned short int", "%hu");
		primitives.put("unsigned short", "%hu");
		primitives.put("long", "%li");
		primitives.put("long int", "%li");
		primitives.put("unsigned long int", "%lu");
		primitives.put("unsigned long", "%lu");
		primitives.put("double", "%f");
		primitives.put("float", "%f");
		primitives.put("char", "%c");
		primitives.put("unsigned char", "%c");
		primitives.put("bool", "%s");
		// TODO: More primitives go in here
	}

	/**
	 * @param writer a writer to the output file.
	 */
	Tracer(Writer writer, int depth) throws IOException {
		super(writer);

		String prefix = "";
		if (depth > 1)
			for (int i = 1; i < depth; i++)
				prefix += "../";

		write(
			"#ifdef ENABLE_AXISTRACE\n"
				+ "/* TRACE ADDED BY THE AXISCPP TRACE TOOL */\n"
				+ "#include \""
				+ prefix
				+ "common/AxisTrace.h\"\n"
				+ "extern AXIS_CPP_NAMESPACE_PREFIX AxisTrace* g_pAT;\n"
				+ "#endif\n");
		flush();
	}

	/**
	 * @param signature the signature of this method 
	 */
	void traceEntry(Signature signature) throws IOException {
		this.signature = signature;
		if (!signature.traceable())
			return;

		String line =
			"\n"
				+ "    #ifdef ENABLE_AXISTRACE\n"
				+ "    if (g_pAT) {\n"
				+ "        char traceLine[256];\n"
				+ "        sprintf(traceLine,\"> ";
		if (null != signature.getClassName())
			line += signature.getClassName();
		line += signature.getMethodName();
		line += "(";

		Parameter[] parms = signature.getParameters();
		for (int i = 0; null != parms && i < parms.length; i++) {
			String f = getFormat(parms[i]);
			if (0 != i)
				line += ",";
			if (null == f)
				line += UNKNOWN_FORMAT;
			else
				line += f;
		}
		line += ")\"";

		for (int i = 0; null != parms && i < parms.length; i++) {
			if (null == getFormat(parms[i]))
				continue;
			line += "," + getName(parms[i]);
		}

		line += ");\n";
		line += "        AXISTRACE1(traceLine,INFO);" + SIGNATURE + "\n";
		line += "    }\n";
		line += "    #endif\n";
		write(line);
		flush();
	}

	void traceExit() throws Exception {
		if (!signature.traceable())
			return;

        // Check this method really should return void
		if (null != signature.getReturnType().getType())
			Utils.rude(
				"Expecting to return void from a method that returns a value: "
					+ signature.toString());

		// Enclose the printf/return in {} in case if/then doesn't have {}
		write("{");
		write(
			"\n    #ifdef ENABLE_AXISTRACE\n"
				+ "    if (g_pAT) AXISTRACE1(\"<  "
				+ signature.getMethodName()
				+ "\",INFO);"
				+ SIGNATURE
				+ "\n    #endif\n");

		// now print out the return line itself
		write("    return;\n    }\n");
		flush();
	}

	/**
	 * Takes in the return statement and traces out the exit trace statement for it
	 * This method prints out the complete return line as well so the user
	 * does not need to print this out themselves. 
	 */
	void traceExit(String value) throws Exception {
		if (!signature.traceable())
			return;

        // Check this method doesn't return void
		if (null == signature.getReturnType().getType())
			Utils.rude(
				"Expecting to return a value from a method that returns void: "
					+ signature.toString());

        // Figure out the method name
		String methodName = "";
		if (null != signature.getClassName())
			methodName = signature.getClassName();
		methodName += signature.getMethodName();
		
		// We can't trace all kinds of C types unfortunately
		Parameter retType = signature.getReturnType();
		String format = getFormat(retType);
		String retValue;
		if (null == format) {
			format = UNKNOWN_FORMAT;
			retValue = "";
		} else
			retValue = ", " + getName(retType);

		// Enclose the printf/return in {} in case if/then doesn't have {}
		// Copy the return value into a local called traceRet in case the
		// return value has side-effects such as "return i++;" or "return func();"
		// This makes sure that we don't execute the return value twice.
		// Unfortunately if the return value is a class we will invoke 
		// a copy constructor. When initialising traceRet with value, put value
            // in brackets in case it contains an operator that might be invoked
            // after the assignment, like another assignment.
		String line = "    {\n";
		line += "        #ifdef ENABLE_AXISTRACE\n";
		line += "            "
			+ retType.getType()
			+ " traceRet = ("
			+ value
			+ ");\n";
		line += "            if (g_pAT) {\n";
		line += "                char traceLine[256];\n";
		line += "                sprintf(traceLine,\"< "
			+ methodName
			+ "("
			+ format
			+ ")\""
			+ retValue
			+ ");\n";
		line += "                AXISTRACE1(traceLine,INFO);" + SIGNATURE + "\n";
		line += "            }\n";
		line += "            return traceRet;\n";
		line += "        #else\n";
		line += "            return " + value + ";\n";
		line += "        #endif\n";
		line += "    }\n";
		write(line);
		flush();
	}

	public void write(String s) throws IOException {
		super.write(s);
		if (AddEntryAndExitTrace.verbose)
			System.out.print(s);
	}

	private String getFormat(Parameter p) {
		String format = null;
		String type = p.getTypeWithoutConst();
		if (null == type || 0 == type.length())
			format = null;
		else if (type.endsWith("*"))
			// TODO print out contents of pointers where possible
			format = "%p";
		else if (primitives.keySet().contains(type))
			format = (String) primitives.get(type);
		// else System.err.println("Unknown format type "+type);
		// TODO: more elses should go in here
		return format;
	}

	private String getName(Parameter p) {
		String name = p.getName();
		if (null == name)
			name = "traceRet";

		if ("bool".equals(p.getTypeWithoutConst())) {
			return "(" + name + "?\"true\":\"false\")";
		} else
			return name;
	}
	
}
