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
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

/**
 * This class adds entry and exit trace to the directories given to it
 * It works on any C++ file or directory. It contains a main program:-
 * 
 * usage: Java AddEntryAndExitTrace startingDirectory
 */
public class AddEntryAndExitTrace {

	public static boolean verbose = false;
	public static boolean quiet = false;

	private Tracer outputFile = null;

	private final static Set extensions =
		new HashSet(Arrays.asList(new Object[] { "cpp", "hpp", "c", "h" }));

	private AddEntryAndExitTrace() {
	}

	/**
	 * Starts adding trace into the given file.
	 * If the given file is a directory then this the starting directory and all
	 * code beneath and in this directory will be given trace. 
	 * @param startingFile - either the starting directory or one file to add trace to.
	 */
	private void addTrace(File startingFile, int depth) throws Exception {
		depth++;
		if (startingFile.isDirectory()) {
			File[] filesInDirectory = startingFile.listFiles();
			for (int i = 0; i < filesInDirectory.length; i++) {
				File file = filesInDirectory[i];
				String name = file.getName();
				int dot = name.lastIndexOf('.');
				String ext = null;
				if (-1 != dot)
					ext = name.substring(dot + 1);

				if (file.isDirectory())
					// recurse
					addTrace(file, depth);
				else if (
					file.isFile()
						&& !file.isHidden()
						&& extensions.contains(ext))
					// this is a file and we need to add trace into it !
					addEntryAndExitTrace(file, depth);
			}
		} else {
			addEntryAndExitTrace(startingFile, depth);
		}
	}

	/**
	 * This method adds entry and exit trace to the given file. It farms out most of the work to
	 * other objects but it is the key orchestrator of the work.
	 * 
	 * @param file the file to add trace to
	 */
	private void addEntryAndExitTrace(File file, int depth) throws Exception {
		if (Exclusions.shouldTraceFile(file.getName())) {
			String filename = file.toString();
			outputDebugString("parsing " + filename + "...");
			String backup = filename + ".back";
			file.renameTo(new File(backup));
			file = new File(backup);

			// we'll put the new file into a tmp file for now so we don't 
			// screw things up
			// TODO: this file should be a tmp file but for now rename 
			// so it's easier to find
			File tracedFile = new File(filename);

			// create a tracer to the output file 
			outputFile = new Tracer(new FileWriter(tracedFile), depth);

			// OK, now we have the output file let's read in the input file !
			FileReader fr = new FileReader(file);
			BufferedReader inputFile = new BufferedReader(fr);

			try {
				parseFile(
					new InputCppSourceCode(inputFile, file.getName()),
					outputFile);
			} catch (ParsingException pe) {
				// TODO: clean up the output file here
			}

			outputFile.flush();
			outputFile.close();
			inputFile.close();
		} else {
			System.out.println("excluding file " + file);
		}
	}

	/**
	 * Parses the given file and adds trace to it, placing the newly traced code 
	 * into the outputfile
	 * 
	 * @param inputFile the input file reader
	 * @param outputFile the output file writer
	 * @throws IOException if htere is a problem dealing with the files.
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

                        int returnCount = 0, catchCount = 0, returnIndex = 0, catchIndex = 0;
                        for (int i = 0; i < bps.length-1; i++) if (bps[i].isReturn()) returnCount++;
                        for (int i = 0; i < bps.length-1; i++) if (bps[i].isCatch()) catchCount++;

				for (int i = 0; i < bps.length; i++) {
					outputFile.writeTrace(bps[i].getCodeFragment());
					if (bps[i].isReturn()) {
                                    if (returnCount>1) returnIndex++;
						outputFile.traceExit(bps[i].getReturnValue(), returnIndex);
					} else if (bps[i].isCatch()) {
                                    if (catchCount>1) catchIndex++;
						outputFile.traceCatch(bps[i].getCaughtValue(), catchIndex);
					} else if (i < bps.length - 1) {
                                    if (returnCount>1) returnIndex++;
						outputFile.traceExit(returnIndex);
                              }
				}
			} else {
				outputFile.writeTrace(fp.toString());
			}
		}
	}

	public static void main(String[] args) {
		if (0 == args.length) {
			printUsage();
			System.exit(-1);
		}

		int idx = 0;
		if ("-v".equals(args[0])) {
			verbose = true;
			idx = 1;
		} else if ("-q".equals(args[0])) {
			quiet = true;
			idx = 1;
		}

		// check that a filename was given
		if (args.length < idx + 1) {
			printUsage();
			System.exit(-1);
		}

		File startFile = new File(args[idx]);
		if (!startFile.isFile() && !startFile.isDirectory()) {
			printUsage();
			System.exit(-2);
		}

		// OK, go for it !
		AddEntryAndExitTrace tracer = new AddEntryAndExitTrace();

		try {
			tracer.addTrace(startFile, 0);
		} catch (Exception exception) {
			exception.printStackTrace();
		} finally {
			outputDebugString("Finished!");
		}
	}

	private static void printUsage() {
		System.out.println(
			"usage: Java AddEntryAndExitTrace startingDirectory");
	}

	private static void outputDebugString(String line) {
		if (!quiet) {
			if (verbose)
				System.out.println();
			System.out.println(line);
		}
	}
}
