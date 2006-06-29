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
import java.net.SocketTimeoutException;
import java.util.Vector;


import org.apache.tools.ant.BuildException;

/**
 * This class sits listening on a port. When a client connects to it it returns a predefined response
 * These responses are stored in a file that is given to this program on start-up.
 * @see printUsage() for further details
 */

public class MockServer extends ChildHandler implements Runnable 
{
    private static MockServer singleton;
    
    private static int SOCKET_TIMEOUT = 700000;
    // The port that we will listen on for the client to connect to
    private int           port;
    protected String responseFileName;
    // File that contains the http responses that the client is expecting back.
    protected  File          responseFile;
    protected boolean       continueToRun =true;
    private ServerSocket serverSocket;
    
    // When this is an ANT task - whether to stop the current MockServer or not.
    private boolean stop; 
    
    public static final void printUsage( )
    {
        System.out.println("Usage: java MockServer -p <port> -r <responseFile>");
        System.out.println("port: the port to listen for requests on");
        System.out.println("responseFile: The file to write out when a request is received");
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
        int port=0;
        String fileName=null;
            for(int i=0; i<args.length; i++)
            {
                if (args[i].equalsIgnoreCase("-p"))
                {
                    String portString=args[++i];
                    try
                    {
                        port = Integer.parseInt(portString);
                        continue;
                    }
                    catch (NumberFormatException numberFormatException)
                    {
                        printUsage( );
                        throw new NumberFormatException("port is not an integer " +portString);
                    }
                }
                if (args[i].equals("-r"))
                {
                    fileName= args[++i];
                    continue;
                }
            }

            MockServer server=new MockServer();
            server.setPort(port);
            server.setResponseFileName(fileName);
            server.execute();
    }


    public MockServer()
    {
        System.out.println( "MockServer()");
    }
    public void execute() throws BuildException
    {
        // If we are closing then get the singleton and close it
        if(isStop())
        {
            System.out.println( "Closing the mockServer in ANT");
            if(singleton!=null)
            {
                singleton.close();
            }
            else
            {
                throw new RuntimeException( "Been told to close the MockServer but there isn't one");
            }
        }
        else
        {
            if(singleton==null)
            {
                try
                {
                    singleton = new MockServer(responseFileName, port);
                    Thread serverThread=new Thread(singleton);
                    serverThread.start( );
                }
                catch(IOException exception)
                {
                    throw new BuildException("MockServer threw IOException: "+exception);
                }
            }
            else
            {
                // This means we should reset the current singletons files
                try
                {
                    System.out.println( "MockServer; resetting the response file");
                    singleton.reset(responseFileName);
                }
                catch(IOException exception)
                {
                    //throw new 
                }
            }
        }
                
    }

    /**
     * This method closes the current response file and opens up a new one
     * @param responseFileName
     */
    protected void reset(String responseFileName)throws IOException
    {
        // close all the connections we got from the client
        super.close();
        // unfortunately super.close is an unnatural act so we'll have to recreate the children vector
        children = new Vector();
        this.responseFileName = responseFileName;
        // deal with the responsefile first
        responseFile=new File(responseFileName);
        // check the responsefile is there
        if (!this.responseFile.canRead( ))
        {
            throw new IOException("Can't read the response file <"
                    +responseFile+">");
        }
        
        // now deal with the port and threads
        // cache the response file (this is a necessary optimisation - if the file is big then the connection blows)
        MockServerThread.cacheResponseFile(responseFile);
    }

    /**
     * 
     */
    private MockServer( String responseFileName, int port) throws IOException
    {
        this(responseFileName);
        System.out.println( "MockServer(responseFile, port)");
        this.port =port;
        // no point in going on if we can;'t create a server socket
        //serverSocket = TCPMonitor.getServerSocket(port);
    }
    


    /**
     * This method is required when this class is being used as a superclass.
     * @param responseFileName2
     */
    protected MockServer(String responseFileName)throws IOException
    {
        this.responseFileName = responseFileName;
        // deal with the responsefile first
        responseFile=new File(responseFileName);
        // check the responsefile is there
        if (!this.responseFile.canRead( ))
        {
            throw new IOException("Can't read the response file <"
                    +responseFile+">");
        }
    
        cacheResponseFile();
        // now deal with the port and threads
    }

    /**
     * caches the response file ready to send it back. 
     */
    protected void cacheResponseFile( )throws IOException
    {
        // cache the response file (this is a necessary optimisation - if the file is big then the connection blows)
        MockServerThread.cacheResponseFile(responseFile);
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
        System.out.println("MockServer listening on port: "+getPort());
        System.out.println("Returning Output file: "+responseFile);
        System.out.println( "singleton="+singleton);
        Socket incoming=null;
        try
        {
            serverSocket = TCPMonitor.getServerSocket(port);
        }
        catch(IOException exception)
        {
            exception.printStackTrace();
            continueToRun=false;
        }

        do
        {
            try
            {
                System.out.println("Mockserver#run(): About to wait for incoming client request");
                incoming=null;
                incoming=serverSocket.accept( );

                // Set keep-alive option to ensure that if server crashes we do not 
                // hang waiting on TCP/IP response.
//                incoming.setKeepAlive(true);
                
//                System.out.println("Mockserver#run(): Got a new client request");
            }
            catch (SocketTimeoutException socketTimeoutException)
            {
                // that's fine - just means that we can go round the loop and
                // see if we
                // should continue to listen
            }
            catch (IOException exception)
            {
                if(continueToRun)
                {
                    // uh oh !
                    System.err
                        	.println("IOException when accepting a client request on the serverSocket");
                    exception.printStackTrace(System.err);
                    continueToRun=false;
                }
                else
                {
                    // that's fine we're stopping
                }
            }
            
            if (incoming!=null)
            {
                try
                {
                    MockServerThread mockServer;
                    mockServer=new MockServerThread(incoming);
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
    }
    
    protected void close()
    {
        System.out.println( "Closing MockServer");
        continueToRun=false;
        singleton=null;
        // clean up
        try
        {
            if(serverSocket!=null)
            {
                serverSocket.close();
            }
        }
        catch(IOException exception)
        {
            System.err.println( "MockServer#run(): IOException when closing the serverSocket: ");
            exception.printStackTrace(System.err);
        }
        
        super.close();
    }

    /**
     * @param stop The stop to set.
     */
    public void setStop(boolean stop)
    {
        this.stop=stop;
    }

    /**
     * @return Returns the stop.
     */
    public boolean isStop( )
    {
        return stop;
    }

    /**
     * @param port The port to set.
     */
    public void setPort(int port)
    {
        this.port=port;
    }

    /**
     * @return Returns the port.
     */
    public int getPort( )
    {
        return port;
    }

    /**
     * @param responseFileName The responseFileName to set.
     */
    public void setResponseFileName(String responseFileName)
    {
        System.out.println( "Setting response file to "+responseFileName);
        this.responseFileName=responseFileName;
    }

    /**
     * @return Returns the responseFileName.
     */
    public String getResponseFileName( )
    {
        return responseFileName;
    }
}
 