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

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 * A C or C++ method signature with the ability to parse it.
 * TODO: properly support variable length argument lists using "..."
 * TODO: passing or returning function pointers (hopefully not needed)
 * TODO: Cope with ~<space>Classname()
 */
class Signature {
	private String originalText;
	private String attributes;
	private String className = null;
	private String methodName = null;
	private Parameter returnType = null;
	private Parameter[] params = null;
	private String trailingAttributes;
	private boolean failed = false;
	private boolean traceable = true;

	private final static Set knownAttrs =
		new HashSet(
			Arrays.asList(
				new Object[] {
					"public",
					"private",
					"extern",
					"\"C\"",
					"virtual",
					"static",
					"inline",
					"STORAGE_CLASS_INFO",
					"AXISCALL" }));

	private final static Set spuriousAttrs =
		new HashSet(
			Arrays.asList(
				new Object[] {
					"AXISCALL" }));

	private final static Set specialOperators =
		new HashSet(
			Arrays.asList(new Object[] { "(", ")", "*", ",", "&", "]", "[" }));

	/**
	 * Takes an unparsed signature string and parses it.
	 *
	 * TODO: Should optionally pass in the className here in case it's an 
	 * inline method implementation inside the class{}. Just so the className
	 * comes out in the trace.
	 */
	Signature(String s) {
		originalText = s;

		try {
			List tokens = tokenise(s);

			ArrayList alAttrs = new ArrayList();
			ArrayList alName = new ArrayList();
			ArrayList alParms = new ArrayList();
			ArrayList alTrailAttrs = new ArrayList();
			ArrayList alInits = new ArrayList();
			if (!splitUp(tokens,
				alAttrs,
				alName,
				alParms,
				alTrailAttrs,
				alInits)) {
				failed = true;
				return;
			}

			parseAttributes(alAttrs);
			parseNameAndRetType(alName);
			parseParameters(alParms);
			parseTrailingAttributes(alTrailAttrs);

			// Ignore any tokens after the ) since these are (hopefully) 
			// constructor initialisers
			
			traceable = Exclusions.shouldTraceMethod(className, methodName);
		} catch (NullPointerException npe) {
			failed = true;
			traceable = false;
		}
	}

	/**
	 * Parse the signature into tokens. This removes whitespace and comments
	 * and separates out "*", ",", "(", ")", "&", "[" and "]".
	 */
	private static List tokenise(String s) {
		ArrayList tokens = new ArrayList();
		String tok = null;
		boolean space = true;
		for (int i = 0; i < s.length(); i++) {
			char c = s.charAt(i);
			if (Character.isWhitespace(c)) {
				space = true;
				continue;
			}
			if (space) {
				if (tok != null)
					tokens.add(tok);
				tok = "" + c;
			} else
				tok += c;
			space = false;

			if (tok.endsWith("/*")) {
				String sub = s.substring(i);
				int endcomm = sub.indexOf("*/");
				if (endcomm == -1)
					break;
				i += endcomm + 1;
				if (tok.equals("/*"))
					tok = "";
				else
					tok = tok.substring(0, tok.length() - 2);
				continue;
			}

			if (tok.endsWith("//")) {
				String sub = s.substring(i);
				int endcomm = sub.indexOf("\n");
				if (endcomm == -1)
					break;
				i += endcomm;
				if (tok.equals("//"))
					tok = "";
				else
					tok = tok.substring(0, tok.length() - 1);
				continue;
			}

			if (tok.endsWith("::"))
				space = true;

			String sc = "" + c;
			if (specialOperators.contains(sc)) {
				if (!tok.equals(sc)) {
					tokens.add(tok.substring(0, tok.length() - 1));
					tok = sc;
				}
				space = true;
			}
		}
		tokens.add(tok);
		return tokens;
	}

	/**
	 * Split up a tokenised method signature into a list of attributes, a list of 
	 * name and return type tokens, a list of parameter tokens and a list of 
	 * initialiser tokens. 
	 */
	private static boolean splitUp(
		List tokens,
		List attrs,
		List nameAndRet,
		List parms,
		List trailAttrs,
		List inits) {

        // nameStart points to the start of the return type if there is one
        // else the start of the method name
		int nameStart;
		for (nameStart = 0; nameStart < tokens.size(); nameStart++)
			if (!knownAttrs.contains(tokens.get(nameStart)))
				break;
		if (nameStart == tokens.size())
			return false;

        // initStart points to the initialisers, or thrown exceptions after 
        // the parameter list. throw is a keyword so we can safely search for it.
		int initStart = tokens.size();
		for (int i = nameStart; i < tokens.size(); i++) {
			String tok = (String) tokens.get(i);
			if ((tok.startsWith(":") && !tok.startsWith("::"))
				|| "throw".equals(tok))
				initStart = i;
		}

		int parmEnd;
		for (parmEnd = initStart - 1; parmEnd > nameStart; parmEnd--)
			if (")".equals(tokens.get(parmEnd)))
				break;
		if (parmEnd == nameStart)
			return false;

		int parmStart = parmEnd;
		for (parmStart = parmEnd; parmStart > nameStart; parmStart--)
			if ("(".equals(tokens.get(parmStart)))
				break;

		for (int i = 0; i < tokens.size(); i++) {
			Object tok = tokens.get(i);
			if (i < nameStart || spuriousAttrs.contains(tok))
				attrs.add(tok);
			else if (i < parmStart)
				nameAndRet.add(tok);
			else if (i <= parmEnd)
				parms.add(tok);
			else if (i < initStart)
				trailAttrs.add(tok);
			else
				inits.add(tok);
		}
		return true;
	}

	private void parseAttributes(List list) {
		attributes = new String();
		Iterator it = list.iterator();
		while (it.hasNext()) {
			if (attributes.length() > 0)
				attributes += " ";
			attributes += (String) it.next();
		}
	}

	private void parseNameAndRetType(List list) {
		int size = list.size();
		int idx;
		// "operator" is a key word so if it's present we know we're
		// dealing with operator overloading. The operator that's been
		// overloaded might have been split up into multiple tokens.
		for (idx = 0; idx < size; idx++)
			if ("operator".equals(list.get(idx)))
				break;

		if (idx < size) {
			methodName = "";
			for (int i = idx; i < size; i++)
				methodName += (String) list.get(i);
		} else { // No operator overloading
			methodName = "" + list.get(size - 1);
			idx = size - 1;
		}

            // The class name comes before the method name
		while (idx > 0 && ((String) list.get(idx - 1)).endsWith("::")) {
                  if (null == className)
			      className = (String) list.get(idx - 1);
                  else
			      className = (String) list.get(idx - 1) + className;
			idx--;
		}

            // Whatever's left before the classname/methodname must be the 
            // return type
		ArrayList retParm = new ArrayList();
		for (int i = 0; i < idx; i++)
			retParm.add(list.get(i));

		returnType = new Parameter(retParm, true);
	}

	/**
	 * Constructs the parameter list
	 */
	private void parseParameters(List list) {
		ArrayList alParams = new ArrayList();
		Iterator it = list.iterator();
		String token = (String) it.next(); // step over the (
		while (it.hasNext() && !")".equals(token)) {
			token = (String) it.next();

			int template = 0; // Depth of template scope
			ArrayList parm = new ArrayList();
			while (!token.equals(")")
				&& (!token.equals(",") || template > 0)) {
				parm.add(token);
				if (contains(token, "<"))
					template++;
				if (contains(token, ">"))
					template--;
				token = (String) it.next();
			}
			
			// No parameters so break out
			if (token.equals(")") && 0 == parm.size())
				break;

			Parameter p = new Parameter(parm);
			if (p.failed()) {
				failed = true;
				return;
			}
			
			// Copes with void func(void)
			if (!p.isVoid())
				alParams.add(p);
		}

		int size = alParams.size();
		if (size > 0) {
			params = new Parameter[size];
			System.arraycopy(alParams.toArray(), 0, params, 0, size);
		}
	}

	private void parseTrailingAttributes(List list) {
		trailingAttributes = new String();
		Iterator it = list.iterator();
		while (it.hasNext()) {
			if (trailingAttributes.length() > 0)
				trailingAttributes += " ";
			trailingAttributes += (String) it.next();
		}
	}

	String getOriginal() {
		return originalText;
	}

	int originalLength() {
		return originalText.length();
	}

	boolean failed() {
		return failed;
	}

	String getAttributes() {
		return attributes;
	}

	String getClassName() {
		return className;
	}

	String getMethodName() {
		return methodName;
	}

	Parameter getReturnType() {
		return returnType;
	}

	Parameter[] getParameters() {
		return params;
	}

    /**
     * Should this method be traced?
     */	
	boolean traceable() {
		return traceable;
	}

	private static boolean contains(String src, String tgt) {
		if (src == null || tgt == null)
			return false;
		if (-1 == src.indexOf(tgt))
			return false;
		return true;
	}

	public String toString() {
		String s = attributes;
		if (attributes.length() > 0)
			s += " ";
		if (returnType != null)
			s += returnType + " ";
		if (className != null)
			s += className;
		s += methodName + "(";
		for (int i = 0; params != null && i < params.length; i++) {
			if (i > 0)
				s += ", ";
			s += params[i].toString();
		}
		s += ")";
		if (trailingAttributes.length() > 0)
			s += " " + trailingAttributes;
		return s;
	}
}
