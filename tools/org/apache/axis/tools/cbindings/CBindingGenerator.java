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
package org.apache.axis.tools.cbindings;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.tools.common.CParsingTool;
import org.apache.axis.tools.common.Configuration;
import org.apache.axis.tools.common.DirectoryTree;
import org.apache.axis.tools.common.FileActor;
import org.apache.axis.tools.common.FilePart;
import org.apache.axis.tools.common.InputCppSourceCode;
import org.apache.axis.tools.common.Parameter;
import org.apache.axis.tools.common.ParsingException;
import org.apache.axis.tools.common.PrototypePart;
import org.apache.axis.tools.common.Signature;
import org.apache.axis.tools.common.Utils;

/**
 * This class is a tool that generates C bindings (header files) from C++
 * header files. It contains a main program:-
 * 
 * usage: Java CBindingGenerator -config <file> -source <dir> -target <dir>
 */
public class CBindingGenerator extends CParsingTool implements FileActor {
	private CBindingGenerator(String[] args) throws Exception {
		super(args);
	}

	/**
	 * This method is called by the DirectoryTree with two files: the
	 * input (source) file and the output (target) file. This method parses 
	 * the source (header) file and writes out the C bindings to the target 
	 * file. The depth is how deep in the source directory tree we are. Files are
	 * excluded if they are listed in the configuration because they shouldn't
	 * have trace added to them.
	 */
	public void actOnFile(File source, File target, int depth)
		throws Exception {
		if (Configuration.fileExcluded(source.getName()))
			return;
		Utils.outputDebugString("parsing " + source + "...");
		String targetName =
			DirectoryTree.maybeAppendSeparator(target.toString());
		targetName
			+= source.getName().substring(0, source.getName().lastIndexOf("."))
			+ ".h";
		FileWriter fw = new FileWriter(new File(targetName), false);
		BufferedWriter bw = new BufferedWriter(fw);
		FileReader fr = new FileReader(source);
		BufferedReader inputFile = new BufferedReader(fr);

		try {
			InputCppSourceCode sourceCode =
				new InputCppSourceCode(inputFile, source.getName());
			generateHeader(sourceCode, bw);
		} catch (ParsingException pe) {
			failed = true;
		}

		bw.flush();
		bw.close();
		inputFile.close();
	}

	/**
	 * Generates a C header file from a C++ header file.
	 */
	private void generateHeader(
		InputCppSourceCode inputFile,
		BufferedWriter outputFile)
		throws Exception {

		String text;
		Iterator it = inputFile.getPartIterator();
		while (it.hasNext()) {
			FilePart fp = (FilePart) (it.next());
			switch (fp.getType()) {
				case FilePart.COMMENT :
					outputFile.write(fp.toString().trim());
					break;

				case FilePart.DIRECTIVE :
					//TODO: replace axis with axisc, etc
					text = fp.toString().trim();
					if (-1 != text.indexOf("include")) {
						StringBuffer sb = new StringBuffer(text);
						int ext = sb.indexOf(".hpp");
						if (-1 != ext) {
							sb.delete(ext + 2, ext + 4);
							text = sb.toString();
						}
					}

					outputFile.write(fp.toString().trim());
					break;

				case FilePart.ENUM :
					//TODO: replace axis with axisc, etc
					outputFile.write(fp.toString().trim());
					break;

				case FilePart.PROTOTYPE :
					text = generateFunctionPrototype((PrototypePart) fp);
					outputFile.write(text);
					break;
					// do nothing for other file parts
			}
			outputFile.newLine();
		}
	}

	private String generateFunctionPrototype(PrototypePart pp)
		throws Exception {
		Signature sign = pp.getSignature();
		String text = sign.getReturnType().toString() + " ";

		text += "axisc";
		String method = sign.getMethodName();
		text += Character.toUpperCase(method.charAt(0));
		text += method.substring(1);
		text += "(";

		Parameter[] parms = sign.getParameters();
		String classname = sign.getClassName();
		if (null != classname
			&& -1 != sign.getAttributes().indexOf("static")) {
			text += "AXISCHANDLE ";
			text += Character.toLowerCase(classname.charAt(0));
			text += classname.substring(1);
			if (null != parms)
				text += ",";
		}

		if (parms != null)
			for (int i = 0; i < parms.length; i++) {
				if (0 != i)
					text += ",";
				String type = parms[i].getType();
				if (null != type)
					text += type + " ";
				String name = parms[i].getName();
				if (null != name)
					text += name;
			}
		text += ");";
		return text;
	}

	public static void main(String[] args) {
		try {
			CBindingGenerator gen = new CBindingGenerator(args);
			File source = gen.checkFile("-source");
			File target = gen.maybeCreateDirectory("-target");
			gen.headers = gen.preparseHeaders("-source");

			DirectoryTree tree =
				new DirectoryTree(
					gen,
					new HashSet(Arrays.asList(new Object[] { "hpp" })));
			tree.walkTree(source, target, 0);
			if (gen.failed) {
				Utils.outputDebugString("Finished! (but encountered problems)");
				System.exit(-2);
			}
		} catch (Exception exception) {
			exception.printStackTrace();
		} finally {
			Utils.outputDebugString("Finished!");
		}
	}

	protected void printUsage() {
		System.out.println(
			"usage: Java CBindingGenerator "
				+ "-config <file> -source <dir> -target <dir>");
	}

}
