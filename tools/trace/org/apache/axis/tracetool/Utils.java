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

/**
 * Static utility methods. Some of these methods are similar to the methods on
 * java.lang.String except they are aware of C/C++ comments and string literals.
 * 
 * TODO: Many of these methods would perform better using StringBuffer not String
 */
final class Utils {
	public static final String whitespace =
		" \t" + System.getProperty("line.separator");
	private static final String letters =
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	private static final String alphanumerics =
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	/** Never instantiate this class */
	private Utils() {
	}

	static boolean isSpace(char c) {
		return whitespace.indexOf(c) != -1;
	}

	/**
	 * Is this string all whitespace?
	 */
	static boolean isSpace(String s) {
		for (int i = 0; i < s.length(); i++)
			if (-1 != whitespace.indexOf(s.charAt(i)))
				return false;
		return true;
	}

	static boolean startsWithALetter(String s) {
		return letters.indexOf(s.charAt(0)) != -1;
	}

	static boolean isAlphaNumeric(char c) {
		return alphanumerics.indexOf(c) != -1;
	}

	// TODO look for other trailing chars like { (because of class{)
	static boolean startsWith(String source, String target) {
		if (source == null || target == null)
			return false;
		if (!source.startsWith(target))
			return false;
		if (source.length() == target.length())
			return true;
		if (isSpace(source.charAt(target.length())))
			return true;
		return false;
	}

	/**
	 * Performs a C-aware version of String.indexOf(char) in
	 * that it skips characters in string literals and comments.
	 */
	static int indexOf(String s, char c) throws ParsingException {
		if ('"' == c)
			rude("Utils.indexOf cannot be passed quotes");

		for (int i = 0; i < s.length(); i++) {
			if (s.charAt(i) == c)
				return i;

			i = skip(s.substring(i), i);
			if (-1 == i)
				return -1;
		}
		return -1;
	}

	/**
	 * Performs a C-aware version of String.indexOf(String) in
	 * that it skips characters in string literals and comments and makes
	 * sure that the target string is not embedded in a longer word.
	 */
	static int indexOf(String s, String t) {
		char t0 = t.charAt(0);
		for (int i = 0; i < s.length(); i++) {
			if (s.charAt(i) == t0
				&& s.substring(i).startsWith(t)
				&& (0 == i || !Utils.isAlphaNumeric(s.charAt(i - 1)))
				&& (s.length() == (i + t.length())
					|| !Utils.isAlphaNumeric(s.charAt(i + t.length()))))
				return i;

			i = skip(s.substring(i), i);
			if (-1 == i)
				return -1;
		}
		return -1;
	}

	/**
	 * Matches braces or quotes and is C-aware. 
	 * It skips characters in string literals and comments.
	 */
	static int findMatching(String s, char c1, char c2) {
		int depth = 0;
		for (int i = 0; i < s.length(); i++) {
			if (s.charAt(i) == c1)
				depth++;
			else if (s.charAt(i) == c2) {
				depth--;
				if (depth == 0)
					return i;
			} else {
				i = skip(s.substring(i), i);
				if (-1 == i)
					return -1;
			}
		}
		return -1;
	}

	/**
	 * Failed to parse the source code for some reason. This method 
	 * prints out a suitably rude message, and then what? I haven't 
	 * quite decided yet.
	 * 
	 * TODO: Do something sensible here like throw an Exception which
	 * will give up on this file completely and tidy up the output file.
	 * It may be just too dangerous to try to carry on. But we need to 
	 * fail in such a way that the build system knows that we've failed
	 * for this file and can build this file without trace.
	 */
	static void rude(
		String reason,
		String filename,
		int lineno,
		String codefragment)
		throws ParsingException {

		String text = "Bad C++ code!! ";
		if (reason != null)
			text += reason;
		if (filename != null)
			text += " " + filename + " lineno=" + lineno;
		if (codefragment != null)
			text += " <" + codefragment + ">";
		System.err.println(text);
		throw new ParsingException();
	}

	/**
	 * @see Utils.rude(String,String,int,String)
	 */
	static void rude(String reason) throws ParsingException {
		rude(reason, null, 0, null);
	}

	private static boolean startsWithComment(String s) {
		if (null == s || s.length() < 2)
			return false;
		if (s.startsWith("//"))
			return true;
		if (s.startsWith("/*"))
			return true;
		return false;
	}

	private static int endOfComment(String s) {
		int idx;
		if (s.startsWith("//"))
			idx = s.indexOf("\n");
		else {
			idx = s.indexOf("*/");
			if (-1 != idx)
				idx++; // Step over */
		}
		return idx;
	}

	private static boolean startsWithStringLiteral(String s) {
		if (null == s || s.length() < 1)
			return false;
		if (s.startsWith("\"") ||
			s.startsWith("'"))
			return true;
		return false;
	}

	private static int endOfStringLiteral(String s) {
		boolean escape = false;
		char c0 = s.charAt(0);
		for (int i = 1; i < s.length(); i++) {
			if (!escape && s.charAt(i) == c0)
				return i;
				
			// \" or \' does not end the literal
			if ('\\' == s.charAt(i))
				escape = true;
			else
				escape = false;
		}
		return -1;
	}

	private static int skip(String s, int i) {
		int j = 0;
		if (startsWithStringLiteral(s)) {
			j = endOfStringLiteral(s);
			if (-1 == j)
				return -1;
		} else if (startsWithComment(s)) {
			j = endOfComment(s);
			if (-1 == j)
				return -1;
		}
		return i + j;
	}
}
