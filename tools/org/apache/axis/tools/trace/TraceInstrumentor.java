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
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.apache.axis.tools.common.BodyPart;
import org.apache.axis.tools.common.CParsingTool;
import org.apache.axis.tools.common.Configuration;
import org.apache.axis.tools.common.DirectoryTree;
import org.apache.axis.tools.common.FileActor;
import org.apache.axis.tools.common.FilePart;
import org.apache.axis.tools.common.InputCppSourceCode;
import org.apache.axis.tools.common.MethodPart;
import org.apache.axis.tools.common.ParsingException;
import org.apache.axis.tools.common.Utils;

/**
 * This class is a tool that adds entry/exit/catch trace to C and C++ 
 * source code. It contains a main program:-
 * 
 * usage: Java TraceInstrumentor -source <dir> -target <dir> -include <dir>
 */
public class TraceInstrumentor extends CParsingTool implements FileActor {
	private static Set cExtensions =
		new HashSet(Arrays.asList(new Object[] { "c", "cpp", "h", "hpp" }));

	private TraceInstrumentor(String[] args) throws Exception {
		super(args);
	}

	/**
	 * This method is called by the DirectoryTree with two files: the
	 * input (source) file and the output (target) file. This method parses 
	 * the source file and writes out the target files with trace in it.
	 * The depth is how deep in the source directory tree we are. Files are
	 * excluded if they are listed in the configuration because they shouldn't
	 * have trace added to them.
	 */
	public void actOnFile(File source, File target, int depth)
		throws Exception {
		String sourceName = source.getName();
		int dot = sourceName.lastIndexOf(".");
		String ext = new String();
		if (-1 != dot)
			ext = sourceName.substring(dot + 1);

		String targetName =
			DirectoryTree.maybeAppendSeparator(target.toString());
		File outputFile = new File(targetName + sourceName);

		if (cExtensions.contains(ext)
			&& !Configuration.fileExcluded(sourceName)) {
			Utils.outputDebugString("parsing " + source + "...");

                  boolean isInLib = false;
                  Iterator itDir = Configuration.getLibraryDirs().iterator();
                  while (itDir.hasNext()) {
                      String libdir= (String)(itDir.next());
                      isInLib = isInLib || (-1 != source.getPath().indexOf(libdir));
                  }

			// create a tracer to the output file 
			Tracer output =
				new Tracer(new FileWriter(outputFile, false), depth, headers, isInLib);

			// OK, now we have the output file let's read in the input file !
			FileReader fr = new FileReader(source);
			BufferedReader inputFile = new BufferedReader(fr);

			try {
				parseFile(
					new InputCppSourceCode(inputFile, source.getName()),
					output);
			} catch (ParsingException pe) {
				failed = true;
			}

			output.flush();
			output.close();
			inputFile.close();
		} else {
			System.out.println("excluding file " + source);
			FileInputStream fis = new FileInputStream(source);
			FileOutputStream fos = new FileOutputStream(outputFile);
			int b = fis.read();
			while (-1 != b) {
				fos.write(b);
				b = fis.read();
			}
		}
	}

	/**
	 * Parses the given file and adds trace to it, placing the newly traced code 
	 * into the outputfile
	 * 
	 * @param inputFile the input file reader
	 * @param outputFile the output file writer
	 */
	private void parseFile(InputCppSourceCode inputFile, Tracer outputFile)
		throws Exception {
		Iterator it = inputFile.getPartIterator();
		while (it.hasNext()) {
			FilePart fp = (FilePart) (it.next());
			if (fp.getType() == FilePart.METHOD) {
				MethodPart mp = (MethodPart) fp;
				outputFile.writeTrace(mp.getOriginalSignature() + "{");
				outputFile.traceEntry(mp.getSignature());
				BodyPart[] bps = mp.getBodyParts();

				int returnCount = 0,
					catchCount = 0,
					returnIndex = 0,
					catchIndex = 0;
				for (int i = 0; i < bps.length - 1; i++)
					if (bps[i].isReturn())
						returnCount++;
				for (int i = 0; i < bps.length - 1; i++)
					if (bps[i].isCatch())
						catchCount++;

				for (int i = 0; i < bps.length; i++) {
					outputFile.writeTrace(bps[i].getCodeFragment());
					if (bps[i].isReturn()) {
						if (returnCount > 1)
							returnIndex++;
						outputFile.traceExit(
							bps[i].getReturnValue(),
							returnIndex);
					} else if (bps[i].isCatch()) {
						if (catchCount > 1)
							catchIndex++;
						outputFile.traceCatch(
							bps[i].getCaughtValue(),
							catchIndex);
					} else if (i < bps.length - 1) {
						if (returnCount > 1)
							returnIndex++;
						outputFile.traceExit(returnIndex);
					}
				}
			} else {
				outputFile.writeTrace(fp.toString());
			}
		}
	}

	public static void main(String[] args) {
		try {
			TraceInstrumentor ti = new TraceInstrumentor(args);
			File source = ti.checkFile("-source");
			File target = ti.maybeCreateDirectory("-target");
			ti.headers = ti.preparseHeaders("-include");

			DirectoryTree tree = new DirectoryTree(ti, null);
			tree.walkTree(source, target, 0);
			if (ti.failed) {
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
			"usage: Java TraceInstrumentor "
				+ "-config <file> -source <dir> "
				+ "-target <dir> -include <dir>");
	}

}
