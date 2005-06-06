// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package org.apache.test;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

/**
 * @author perryan,hawkeye 
 * This class is designed to listen on a given port and send the
 * request received on that port to the given RequestHandler. This class
 * is meant to be used in a test suite scenario. where an instance of
 * this class is created per call to a test.
 */
public class TCPMonitor
{

    private static TCPMonitor         singleton              =null;
    private static BufferedWriter     requestFileWriter;
    private static BufferedWriter     responseFileWriter;
    private static boolean            responseFileWriterOpen =false;
    private static TestClientListener testClientListener     =null;

    
    /**
     * Creates a new TCPMonitor listening on the given port for incoming
     * requests (this is always on localhost of course!)
     * 
     * @param listenerPort the port to listen for incoming requests
     * @throws IOException if any issues occur listening for connections or
     *             supporting them.
     */
    private TCPMonitor(int listenerPort, String serviceHost, int servicePort,
            String requestFile, String responseFile) throws IOException
    {
      try
      {
          requestFileWriter=new BufferedWriter(new FileWriter(requestFile));
      }
      catch (IOException exception)
      {
          System.err
                  .println("IOEXCeption when creating filewriter to requestfile: "
                          +exception);
          throw exception;
      }
      if (!responseFile.equals(""))
      {
          try
          {
              responseFileWriter=new BufferedWriter(new FileWriter(
                      responseFile));
          }
          catch (IOException exception)
          {
              System.err
                      .println("IOException when creating writer to response file: "
                              +exception);
              throw exception;
          }
          responseFileWriterOpen=true;
      }
        /*
         * Create a thread which listens for incoming requests
         */
        testClientListener=new TestClientListener(listenerPort, serviceHost,
                servicePort);
        Thread testClientListenerThread=new Thread(testClientListener);
        testClientListenerThread.start( );
    }


    public static TCPMonitor getInstance( )
    {
        if (singleton==null)
        {
            throw new RuntimeException("TCPMonitor has not been initialised.");
        }
        return singleton;
    }

    public static TCPMonitor getInstance(int listenerPort, String serviceHost,
            int servicePort, String requestFile, String responseFile)
            throws IOException
    {
        if (singleton==null)
        {
            singleton=new TCPMonitor(listenerPort, serviceHost, servicePort,
                    requestFile, responseFile);
        }
        return singleton;
    }
    
    

    /**
     * We've been told to stop by an incoming Stop request so clean up.
     */
    public static void stop( ) throws IOException
    {
        // close() should flush() the streams but let's just be sure !
        System.out.println( "TCPMonitor#stop(): Flushing and closing the output files");
        IOException exception=null;
        try
        {
            requestFileWriter.flush( );
            requestFileWriter.close( );

            responseFileWriter.flush( );
            responseFileWriter.close( );
        }
        catch (IOException ioException)
        {
            exception=ioException;
        }
        finally
        {
            singleton=null;
        }
        if (exception!=null)
        {
            throw exception;
        }
    }

    public void writeRequest(char[] buffer, int howManyChars)
    {
        try
        {
            requestFileWriter.write(buffer, 0, howManyChars);
        }
        catch (IOException e)
        {
            e.printStackTrace( );
        }
    }

    public void writeResponse(char[] buffer, int howManyChars)
    {
        try
        {
            if (responseFileWriterOpen)
            {
                responseFileWriter.write(buffer, 0, howManyChars);
            }
        }
        catch (IOException e)
        {
            e.printStackTrace( );
        }
    }
    
    public static void main(String[] args)
    {

        try
        {
            int listener_port=0;
            int forward_port=0;
            String forward_host="";
            String request_file="";
            String response_file="";
            String serverResponse_file = null;
            for(int i=0; i<args.length; i++)
            {
                if (args[i].equalsIgnoreCase("-l"))
                {
                    listener_port=Integer.parseInt(args[++i]);
                    System.out.println( "TCPMonitor Listening on port "+listener_port);
                    continue;
                }
                if (args[i].equalsIgnoreCase("-p"))
                {
                    forward_port=Integer.parseInt(args[++i]);
                    continue;
                }
                if (args[i].equalsIgnoreCase("-h"))
                {
                    forward_host=new String(args[++i]);
                    continue;
                }
                if (args[i].equalsIgnoreCase("-o"))
                {
                    request_file=new String(args[++i]);
                    continue;
                }
                if (args[i].equalsIgnoreCase("-r"))
                {
                    response_file=new String(args[++i]);
                    continue;
                }
                if (args[i].equalsIgnoreCase("-s"))
                {
                    serverResponse_file=new String(args[++i]);
                    continue;
                }
            }
            if (listener_port==0||forward_port==0||forward_host.equals("")
                    ||request_file.equals(""))
            {
                System.out
                        .println("usage: TCPMonitor <-l listen port> <-p forward port> <-h forward host> <-o request output file> [-r response output file]");
                return;
            }
            TCPMonitor monitor=TCPMonitor.getInstance(listener_port,
                    forward_host, forward_port, request_file, response_file);
        }
        catch (Throwable exception)
        {
            exception.printStackTrace( );
        }
    }
    
    
}

