/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999 The Apache Software Foundation.  All rights 
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
 * 4. The names "Xerces" and "Apache Software Foundation" must
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
 * individuals on behalf of the Apache Software Foundation and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

package org.apache.axis.client ;

import java.net.*;
import java.io.*;
import java.util.*;

public class AdminClient {
  static void main(String args[]) {

    String hdr = "POST /axis/servlet/AxisServlet HTTP/1.0\n" +
                 "Host: localhost:8080\n" +
                 "Content-Type: text/xml;charset=utf-8\n" +
                 "SOAPAction: AdminService\n";

    String msg = null ;

    try {
      String  host = "localhost" ;
      int     port = 8080 ;

      for ( int i = 0 ; i < args.length ; i++ ) {
        if ( args[i].charAt(0) == '-' ) {
          switch( args[i].toLowerCase().charAt(1) ) {
            case 'h': if (args[i].length() > 2 )
                        host = args[i].substring(2);
                      break ;
            case 'p': if (args[i].length() > 2 )
                        port = Integer.parseInt(args[i].substring(2));
                      break ;
            default: System.err.println( "Unknown option '" + 
                                         args[i].charAt(1) + "'" );
                     System.exit(1);
          }
        }
        else {
          InputStream    input = null ;
          long           length ;
        
          System.out.println( "Processing file: " + args[i] );
          File           file = new File(args[i]);
          length = file.length();
          input = new FileInputStream( args[i] );

          Socket         sock = new Socket( host, port );
          InputStream    inp  = sock.getInputStream();
          OutputStream   out  = sock.getOutputStream();
          String         cl   = "Content-Length: " + length + "\n\n" ;
    
          out.write( hdr.getBytes() );
          out.write( cl.getBytes() );

          byte[]          buf = new byte[1000];
          int             rc ;
          while ( (rc = input.read(buf)) > 0 )
            out.write( buf, 0, rc );

          while ( (rc = inp.read(buf,0,1000)) > 0 )
            System.out.write( buf,0,rc );
            
          sock.close();
          input.close();
        }
      }
    }
    catch( Exception e ) {
      System.err.println( e );
      e.printStackTrace( System.err );
    }
  };

};
