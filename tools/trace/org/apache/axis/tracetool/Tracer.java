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
import java.awt.image.IndexColorModel;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Writer;

/**
 * A Buffered write that also contains the methods to add in in trace
 * TODO: Add in &this and threadid into each trace record
 */
class Tracer extends BufferedWriter {
	private Signature signature = null;
	private final static String SIGNATURE = "  /* AUTOINSERTED TRACE */";

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
		// TODO: System.out.println warm fuzzy about excluding 
		// method here would be nice
		if (!signature.traceable())
			return;

		//		TODO trace parameters
		write(
			"\n#ifdef ENABLE_AXISTRACE\n"
				+ "if (g_pAT) AXISTRACE1(\"> "
				+ pretty(signature.toString())
				+ "\",INFO);"
				+ SIGNATURE
				+ "\n#endif\n");
		flush();
	}

	void traceExit() throws IOException {
		if (!signature.traceable())
			return;

		// TODO check this method returns void
		// Enclose the printf/return in {} in case if/then doesn't have {}
		write("{");
		write(
			"\n#ifdef ENABLE_AXISTRACE\n"
				+ "if (g_pAT) AXISTRACE1(\"<  "
				+ signature.getMethodName()
				+ "\",INFO);"
				+ SIGNATURE
				+ "\n#endif\n");

		// now print out the return line itself
		write("return; }");
		flush();
	}

	/**
	 * Takes in the return statement and traces out the exit trace statement for it
	 * This method prints out the complete return line as well so the user
	 * does not need to print this out themselves. 
	 */
	void traceExit(String value) throws IOException {
		if (!signature.traceable())
			return;

		// TODO avoid side effects such as return i++;

		// Enclose the printf/return in {} in case if/then doesn't have {}
		write("{");
		// write out the actual exit trace line
		// TODO trace the return value properly
		write(
			"\n#ifdef ENABLE_AXISTRACE\n"
				+ "if (g_pAT) AXISTRACE1(\"< "
				+ signature.getMethodName()
				+ " = "
				+ pretty(value)
				+ "\",INFO);"
				+ SIGNATURE
				+ "\n#endif\n");

		// now print out the return line itself
		write("return " + value + "; }");
		flush();
	}

	public void write(String s) throws IOException {
		super.write(s);
		if (AddEntryAndExitTrace.verbose)
			System.out.print(s);
	}

	/**
	 * Escapes special characters like " so that they can be output 
	 * in a C string literal. Also removes newlines, since C string
	 * literals can't be split over lines.
	 */
	private String pretty(String s) {
		StringBuffer sb = new StringBuffer(s);
		for (int i = 0; i < sb.length(); i++)
			switch (sb.charAt(i)) {
				case '"' :
					sb = sb.insert(i, '\\');
					i++;
					break;
				case '\n' :
					sb = sb.deleteCharAt(i);
					i--;
					break;
			}
		return sb.toString();
	}
}
