/*
 * Copyright 2003-2004 The Apache Software Foundation. 
 * (c) Copyright IBM Corp. 2005
 *  
 * All Rights Reserved Licensed under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0 Unless required by applicable law
 * or agreed to in writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 */

/**
 * @author hawkeye
 */
package org.apache.test;

import java.io.File;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.rmi.server.SocketSecurityException;
import java.util.Vector;

import javax.net.SocketFactory;

/**
 * This class sits listening on a port. When a client connects to it it returns a predefined response
 * These responses are stored in a file that is given to this program on start-up.
 * @see printUsage() for further details
 */

public class MockServer extends ChildHandler implements Runnable 
{
    private static int SOCKET_TIMEOUT = 700000;
    // The port that we will listen on for the client to connect to
    private int           port;
    // File that contains the http responses that the client is expecting back.
    private File          responseFile;
    private boolean       continueToRun =true;
    ServerSocket serverSocket;
    
    public static final void printUsage( )
    {
        System.out
                .println("Usage: java MockServer -p <port> -r <responseFile>");
        System.out.println("port: the port to listen for requests on");
        System.out
                .println("responseFile: The file to write out when a request is received");
    }

    public static void main(String[] args)
    {
        // check that we have the required params
        if (args.length<2)
        {
            printUsage( );
            System.exit(-1);
        }

        // We have the params now let's run the server !
        try
        {
            MockServer server=new MockServer(args);
            Thread serverThread=new Thread(server);
            serverThread.start( );
        }
        catch (IOException ioException)
        {
            ioException.printStackTrace( System.err);
            
            throw new RuntimeException("Failed to start MockServer due to IOException: "+ioException);
        }
    }




    /**
     * @param the arguments as they were passed into main
     */
    public MockServer(String[] arguments) throws IOException ,
            NumberFormatException
    {
        for(int i=0; i<arguments.length; i++)
        {
            if (arguments[i].equalsIgnoreCase("-p"))
            {
                String portString=arguments[++i];
                try
                {
                    port=Integer.parseInt(portString);
                    continue;
                }
                catch (NumberFormatException numberFormatException)
                {
                    printUsage( );
                    throw new NumberFormatException("port is not an integer "
                            +portString);
                }
            }
            if (arguments[i].equals("-r"))
            {
                responseFile=new File(arguments[++i]);
                continue;
            }

            // check the responsefile is there
            if (!this.responseFile.canRead( ))
            {
                throw new IOException("Can't read the response file <"
                        +responseFile+">");
            }
        }
        // cache the response file (this is a necessary optimisation - if the file is big then the connection blows)
        MockServerThread.cacheResponseFile(responseFile);

        // no point in going on if we can;'t create a server socket
        serverSocket = TCPMonitor.getServerSocket(port);
        serverSocket.setReuseAddress(true);
    }


    /*
     * (non-Javadoc)
     * This is the Thread run method. In this method we wait for a client to connect to us.
     * When they do we spin off a new MockServerThread and then continue to listen for further requests
     *  
     * @see java.lang.Runnable#run()
     */
    public void run( )
    {
        System.out.println("MockServer listening on port: "+port);
        System.out.println("Returning Output file: "+responseFile);
        Socket incoming=null;

        do
        {
            try
            {
                System.out
                        .println("Mockserver#run(): About to wait for incoming client request");
                incoming=serverSocket.accept( );
                System.out.println("Mockserver#run(): Got a new client request");
            }
            catch (SocketTimeoutException socketTimeoutException)
            {
                // that's fine - just means that we can go round the loop and
                // see if we
                // should continue to listen
            }
            catch (IOException exception)
            {
                // uh oh !
                System.err
                        .println("IOException when accepting a client request on the serverSocket");
                exception.printStackTrace(System.err);
                continueToRun=false;
            }
            if (incoming!=null)
            {
                try
                {
                    MockServerThread mockServer;
                    mockServer=new MockServerThread(incoming, responseFile);
                    addChild(mockServer);
                    Thread mockServerThread = new Thread(mockServer);
                    mockServerThread.start( );
                }
                catch (IOException e1)
                {
                    e1.printStackTrace( );
                }
                catch (StopRequestException e1)
                {
                    System.out.println("MockServer has been told to stop");
                    continueToRun=false;
                }
            }
        }
        while (continueToRun);
        
        close();
    }
    
    protected void close()
    {
        // clean up
        try
        {
            serverSocket.close();
        }
        catch(IOException exception)
        {
            System.err.println( "MockServer#run(): IOException when closing the serverSocket: ");
            exception.printStackTrace(System.err);
        }
        
        super.close();
    }
}
 