/* -*- Java -*- */

/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
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
 * 4. The names "SOAP" and "Apache Software Foundation" must
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

/*
 * Axis C++ JNI Content Handler.
 *
 * @author Lilantha Darshana (lilantha@virtusa.com)
 *
 */

import java.io.*;
import java.util.Vector;			   


public class AxisCppContentHandler
{
	private static final boolean DEBUG = Boolean.getBoolean("debug");
	static {
        try {
			System.loadLibrary("libAxiscpp");
         
		 if(DEBUG)
            System.out.println("* Native library 'libAxiscpp' loaded");

        } catch (Throwable e) {
            e.printStackTrace();
        }
     }

	public static native void processContent(InputStream in, 
											 Vector headers, 
											 OutputStream out,
											 int contentLength);

	public static void main(String [] args)
	{
		byte [] str = new String("Hello World").getBytes();
		ByteArrayInputStream input = new ByteArrayInputStream(str);
		int contentLength = "Hello World".length();
		Vector v = new Vector();
		v.add("Name1");
		v.add("Value1");
		v.add("Name2");
		v.add("Value2");
		try{
			System.in.read();
		
			AxisCppContentHandler.processContent(input, v, System.out, contentLength);
		}catch(IOException ex){
			ex.printStackTrace();
		}
		
		for(int i=0;i<v.size()/2;i++)
			System.out.println(v.elementAt(i*2) + " : " + v.elementAt(i*2+1));
	}
}



