/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:  
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written 
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

package org.apache.axis.j2me.xml;

import org.apache.axis.j2me.xml.sax.LocatorImpl;

import java.io.IOException;
import java.io.Reader;

/**
 * This is designed to work for CLDC just like PushbackReader of CDC and J2SE
 * @author Ias (iasandcb@tmax.co.kr)
 */
public class PushBackReader {

    /** default buffer size */
	public static final int DEFAULT_BUFFER_SIZE = 1024;
	private Reader reader;
	private char[] buffer;
	private int pointer;
	private int length;
	private boolean eof;
	private LocatorImpl locator;
	
    /** 
     * Constructor with reader and locator
     * @param reader
     * @param locator
     */
	public PushBackReader(Reader reader, LocatorImpl locator) {
		this.reader = reader;
		this.locator = locator;
		buffer = new char[DEFAULT_BUFFER_SIZE];
	}
	
    /**
     * Read a single character.
     */
	public char read() throws IOException {
		char result;
		if (pointer == length) {
			length = reader.read(buffer);
			if (length == -1) {
				eof = true;
				return (char) length;
			}
			pointer = 0;			
		}
		result = buffer[pointer];
		pointer++;
		switch (result) {
			case '\t':
				locator.addColumnNumber(8);
				break;
			case '\n':
				locator.incrementLineNumber();
				break;
			default:
				locator.incrementColumnNumber();
		}
		return result;
	}
	
    /**
     * Push a String to this reader
     * @param insertString
     */
	public void addString(String insertString) {
		int insertStringLength = insertString.length();
		int bufferLength = buffer.length;
		char[] enlargedBuffer = new char[bufferLength + insertStringLength];
		System.arraycopy(buffer, 0, enlargedBuffer, 0, pointer);
		System.arraycopy(insertString.toCharArray(), 0, enlargedBuffer, pointer, insertStringLength);
		System.arraycopy(buffer, pointer, enlargedBuffer, pointer + insertStringLength, bufferLength - pointer - insertStringLength);
		buffer = enlargedBuffer;
		length += insertStringLength;
	}
	
    /**
     * Push back a single character.
     *
     */
	public void unread() {
		pointer--;
		switch (buffer[pointer]) {
			case '\t':
				locator.addColumnNumber(-8);
				break;
			case '\n':
				locator.decrementLineNumber();
				break;
			default:
				locator.addColumnNumber(-1);
		}
	}

    /**
     * check out whether this reader reaches End Of File
     * @return a boolean value indicating the result
     */
	public boolean isEof() {
		return eof;
	}
}
