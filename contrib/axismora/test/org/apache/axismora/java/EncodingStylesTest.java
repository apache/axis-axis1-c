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
 *    Apache Software Foundation (http://www.apache.org/)."
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

package org.apache.axismora.java;

import org.apache.axis.encoding.Base64;

import junit.framework.*;

/**
 * US-ASCII Seven-bit ASCII, a.k.a. ISO646-US, a.k.a. the Basic Latin block of the Unicode character set 
 * ISO-8859-1   ISO Latin Alphabet No. 1, a.k.a. ISO-LATIN-1 
 * UTF-8 Eight-bit UCS Transformation Format  
 * UTF-16BE Sixteen-bit UCS Transformation Format, big-endian byte order 
 * UTF-16LE Sixteen-bit UCS Transformation Format, little-endian byte order 
 * UTF-16 Sixteen-bit UCS Transformation Format, byte order identified by an optional byte-order mark 
 * @author hemapani
 */
public class EncodingStylesTest extends TestCase {
    public void testEncoding(String encoding) throws Exception {
        byte[] b =
            encoding != null
                ? "testing encoidng".getBytes(encoding)
                : "testing encoidng".getBytes();
        System.out.println(encoding + " = " + b);
    }

    public void testBase64Encoding() {
        String b = Base64.encode("testing encoidng".getBytes());
        System.out.println(b);
        System.out.println(new String(Base64.decode(b)));
    }
    public static void main(String[] args) throws Exception {
        EncodingStylesTest test = new EncodingStylesTest();
        test.testEncoding(null);
        test.testEncoding("UTF-8");
        test.testEncoding("US-ASCII");
        test.testEncoding("ISO-8859-1");
        test.testEncoding("UTF-16BE");
        test.testEncoding("UTF-16LE");
        test.testEncoding("UTF-16");
        test.testBase64Encoding();
    }

}
