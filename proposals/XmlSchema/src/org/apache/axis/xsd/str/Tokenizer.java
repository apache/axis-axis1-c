/*
 * Tokenizer.java
 *
 * Created on November 8, 2001, 5:13 PM
 */

package org.apache.axis.xsd.str;

import java.util.Vector;
import java.util.StringTokenizer;

/**
 *
 * @author  mukund
 */

public class Tokenizer {

    /** Cannot create new Tokenizer */
    private Tokenizer() {
    }
    
    public static final String[] tokenize(String in, String delim) {
		Vector tmp = new Vector();
		StringTokenizer stk = new StringTokenizer(in, delim);
		while( stk.hasMoreTokens() ) {
			String str = stk.nextToken();
			if( str.trim().length() != 0 )
				tmp.addElement(str);
		}
		return (String[])tmp.toArray(new String[tmp.size()]);
    }
    
    public static final String[] firstToken(String in, String delim) {
        int x = in.indexOf(delim);
        if( x == -1 )
            return new String[] { in, "" };
        return new String[] { in.substring(0, x), 
							  in.substring(x + delim.length(), in.length()) };
    }
    
    public static final String[] lastToken(String in, String delim) {
        int x = in.lastIndexOf(delim);
        if( x == -1 )
            return new String[] { "", in };
        return new String[] { in.substring(0, x), 
							  in.substring(x + delim.length(), in.length()) };
    }
}
