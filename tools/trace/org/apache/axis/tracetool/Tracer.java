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
		if (null != parms)
			len = parms.length;
		String line =
			"\n"
				+ "\t#ifdef ENABLE_AXISTRACE\n"
				+ "\t\tif (g_pAT && g_pAT->isTraceOn())\n"
				+ "\t\t\tg_pAT->traceEntry("
				+ getClassName()
				+ ", \""
				+ signature.getMethodName()
				+ "\", NULL, "
				+ len;
		for (int i = 0; null != parms && i < parms.length; i++)
			line += getTypeParms(parms[i]);
		line += ");\t" + SIGNATURE + "\n";
		line += "\t#endif\n";
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
		String line = "\t{\n";
		line += "\t\t#ifdef ENABLE_AXISTRACE\n";
		line += "\t\t\tif (g_pAT && g_pAT->isTraceOn())\n";
		line += "\t\t\t\tg_pAT->traceExit("
			+ getClassName()
			+ ", \""
			+ signature.getMethodName()
			+ "\");\t"
			+ SIGNATURE
			+ "\n";
		line += "\t\t#endif\n";

		// now print out the return line itself
		line += "\t\treturn;\n";
		line += "\t}\n";
		write(line);
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

		// Enclose the printf/return in {} in case if/then doesn't have {}
		// Copy the return value into a local called traceRet in case the
		// return value has side-effects such as "return i++;" or "return func();"
		// This makes sure that we don't execute the return value twice.
		// Unfortunately if the return value is a class we will invoke 
		// a copy constructor. When initialising traceRet with value, put value
		// in brackets in case it contains an operator that might be invoked
		// after the assignment, like another assignment.
		String line = "\t{\n";
		line += "\t\t#ifdef ENABLE_AXISTRACE\n";
		line += "\t\t\t"
			+ signature.getReturnType().getType()
			+ " traceRet = ("
			+ value
			+ ");\n";
		line += "\t\t\tif (g_pAT && g_pAT->isTraceOn())\n";
		line += "\t\t\t\tg_pAT->traceExit("
			+ getClassName()
			+ ", \""
			+ signature.getMethodName()
			+ "\""
			+ getTypeParms(signature.getReturnType())
			+ ");\t"
			+ SIGNATURE
			+ "\n";
		line += "\t\t\treturn traceRet;\n";
		line += "\t\t#else\n";
		line += "\t\t\treturn " + value + ";\n";
		line += "\t\t#endif\n";
		line += "\t}\n";
		write(line);
		flush();
	}

	void traceCatch(Parameter value) throws Exception {
		if (!signature.traceable())
			return;

		String line =
			"\n"
				+ "\t#ifdef ENABLE_AXISTRACE\n"
				+ "\t\tif (g_pAT && g_pAT->isTraceOn())\n"
				+ "\t\t\tg_pAT->traceCatch("
				+ getClassName()
				+ ", \""
				+ signature.getMethodName()
				+ "\""
                        + getTypeParms(value);
		line += ");\t" + SIGNATURE + "\n";
		line += "\t#endif\n";
		write(line);
		flush();
	}

	public void write(String s) throws IOException {
		super.write(s);
		if (AddEntryAndExitTrace.verbose)
			System.out.print(s);
	}

	// TODO cope with STL strings
	// TODO cope with pointers to primitives
	// TODO cope with references
	private String getTypeParms(Parameter p) {
            // copes with catch (...)
            if ("...".equals(p.getType())) return " ";

		String parms = ",\n\t\t\t\t\tAXIS_CPP_NAMESPACE_PREFIX TRACETYPE_";
		String name = p.getName();
		if (null == name)
			name = "traceRet";
            name = "((void*)&"+name+")";

		String type = p.getTypeWithoutConst();
		if (null == type || 0 == type.length())
			parms += "UNKNOWN, 0, NULL";
		else if (type.endsWith("*")) {
			String contents = type.substring(0, type.length() - 1);
			if ("char".equals(contents))
				parms += "STRING, 0, " + name;
			else if ("void".equals(contents))
				// We just don't know what this void* is pointing at 
				// so that best we can do is to print out the first byte.
				parms += "POINTER, 1, " + name;
			else
				parms += "POINTER, sizeof(" + contents + "), " + name;
		} else if (typetable.keySet().contains(type))
			parms += (String) typetable.get(type) + ", 0, " + name;
		else if (-1 != type.indexOf("&")) {
			// TODO: cope with references
			parms += "UNKNOWN, 0, " + name;
		} else
			parms += "DATA, sizeof(" + type + "), " + name;

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
