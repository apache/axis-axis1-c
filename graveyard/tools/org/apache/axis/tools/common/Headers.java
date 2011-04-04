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

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Headers implements FileActor {
	private ArrayList instanceMethods = new ArrayList();
	private ArrayList staticMethods = new ArrayList();
	private ArrayList allMethods = new ArrayList();
	private ArrayList classNames = new ArrayList();
	private boolean failed = false;

	public void actOnFile(File header, File ignored, int depth)
		throws Exception {
		if (Configuration.fileExcluded(header.getName())) {
			Utils.outputDebugString("excluding " + header + "...");
			return;
		}

		Utils.outputDebugString("pre-parsing " + header + "...");
		FileReader fr = new FileReader(header);
		BufferedReader inputFile = new BufferedReader(fr);

		try {
			InputCppSourceCode code =
				new InputCppSourceCode(inputFile, header.getName());
			Iterator it = code.getPartIterator();
			while (it.hasNext()) {
				FilePart fp = (FilePart) (it.next());
				if (fp.getType() != FilePart.PROTOTYPE)
					continue;
				PrototypePart pp = (PrototypePart) fp;
				String className = pp.className();
				if (null==className)
					continue;
				String trimClassName = className;
				if (className.endsWith("::"))
					trimClassName =
						className.substring(0, className.length() - 2);
				if (!classNames.contains(trimClassName))
					classNames.add(trimClassName);
				
				Signature sign = new Signature(fp.toString());
				sign.setClassName(className);
				
				// "Clean" the signature by stripping off attributes, 
				// semicolons, etc
				Signature cleaned = new Signature(sign.toStringWithoutAttrs());
				if (-1 == sign.getAttributes().indexOf("static"))
					instanceMethods.add(cleaned);
				else
					staticMethods.add(cleaned);
			}
		} catch (ParsingException pe) {
			failed = true;
		}

		inputFile.close();
		allMethods.addAll(staticMethods);
		allMethods.addAll(instanceMethods);
	}

	public boolean failed() {
		return failed;
	}

	public boolean isInstanceMethod(Signature sign) {
		Iterator it = instanceMethods.iterator();
		while (it.hasNext()) {
			Signature s = (Signature) it.next();
			if (s.equals(sign))
				return true;
		}
		return false;
	}

	public boolean isStaticMethod(Signature sign) {
		Iterator it = staticMethods.iterator();
		while (it.hasNext()) {
			Signature s = (Signature) it.next();
			if (s.equals(sign))
				return true;
		}
		return false;
	}
	
	public List getMethods(String method) {
		ArrayList list = new ArrayList();
		if (null == method)
			return list;

		Iterator it = allMethods.iterator();
		while (it.hasNext()) {
			Signature s = (Signature) it.next();
			if (method.equals(s.getMethodName()))
				list.add(s);
		}
		return list;
	}
	
	public boolean isClassName(String text) {
		return classNames.contains(text);
	}
}
