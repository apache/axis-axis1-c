/* -*- C++ -*- */
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



