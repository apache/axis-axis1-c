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

import java.io.*;
import java.lang.reflect.InvocationTargetException;
import java.net.*;

/**
 * TestClientListener runs as a thread of the
 * 
 * @see TestSingleton class and creates a ServerSocket object on a port and from
 *      this creates a socket that accepts incoming requests. When a request is
 *      received new threads are created of type
 * @see TestClientThread which do all the communication.
 * @author Andrew Perry, hawkeye
 * @since 1.0
 */

public class TestClientListener extends ChildHandler implements Runnable
{
    private int     servicePort    =0;
    private String  serviceHostNme =null;
    private boolean stayAlive      =false;
    private ServerSocket    serverSocket   =null;
    private int listenPort; // only kept to do sysout message

    /**
     * 
     * @param listenPort the port to listen for clients requests on
     * @param serviceHost the host that the service is on.
     * @param servicePort the port that the service is on
     * @throws IOException if we can't create a server socket listening for the
     *             client to send us a request
     */
    public TestClientListener(int listenPort, String serviceHost,
            int servicePort) throws IOException
    {
        this.serviceHostNme=serviceHost;
        this.servicePort=servicePort;
        this.listenPort = listenPort;

        // no point in carrying on if we can't listen to the client !
        serverSocket=TCPMonitor.getServerSocket(listenPort);
    }

    /**
     *
     * Sits waiting for a client thread and when one connects we start up a new TestClientThread to handle
     * the request. This method then goes round again waiting for future requests.
     *  
     * @see Thread
     */
    public void run( )
    {
        stayAlive=true;
        Socket clientSocket=null;
        //        try
        //        {
        //            //serverSocket.setSoTimeout(2000);
        //        }
        //        catch(SocketException exception)
        //        {
        //            exception.printStackTrace();
        //        }
        while (stayAlive==true)
        {
            // ensure clientSocket is an indicator of whether we got a new connection or not
            clientSocket=null;
            try
            {
                System.out
                        .println("TestClientListener#run(): Waiting for a new client request: "+listenPort);
                clientSocket=serverSocket.accept( );
                
                // Set keep-alive option to ensure that if client crashes we do not 
                // hang waiting on TCP/IP response.
                clientSocket.setKeepAlive(true);
                
                System.out
                        .println("TestClientListener#run():Got a client new client request");
            }
            catch (SocketTimeoutException socketTimeoutException)
            {
                // System.out.println( "socket timedout");
                // that's fine - this is what helps us get out of this loop
            }
            catch (IOException exception)
            {
                if(stayAlive)
                {
                System.err
                        .println("IOException when accepting a connection from the client: "
                                +exception);
                throw new RuntimeException(
                        "IOException when accepting a connection from the client: "
                                +exception);
                }
            }

            if (clientSocket!=null)
            {
                // Wait until we have received our first bytes from the
                // client before we create the connection to the service.
                TestClientThread connectionToServer=null;
                try
                {
                        connectionToServer=ServerConnectionFactory.getServerConnection(clientSocket, serviceHostNme, servicePort);
                        
                        addChild(connectionToServer);
                        Thread connectionToServerThread = new Thread(connectionToServer);
                        connectionToServerThread.start( );
                }
                catch(IllegalAccessException illegalAccessException)
                {
                    // this is thrown when we cannot instantiate the connection to server class
                    System.err.println( "Cannot connect to server");
                    illegalAccessException.printStackTrace();
                    stayAlive=false;
                    
                }
                catch(InstantiationException instantiationException)
                {
                    // this is thrown when we cannot instantiate the connection to server class
                    System.err.println( "InstatntiationException: Cannot connect to server");
                    instantiationException.printStackTrace();
                    stayAlive=false;
                }
                catch(NoSuchMethodException noSuchMethodException)
                {
                    // this is thrown when we cannot instantiate the connection to server class
                    System.err.println( "NoSuchMethodException: Cannot connect to server");
                    noSuchMethodException.printStackTrace();
                    stayAlive=false;
                }
                catch(InvocationTargetException invocationTargetException)
                {
                    if(invocationTargetException.getCause() instanceof StopRequestException)
                    {
                        // All is well !
                        System.out
                        .println("TestClientListener got a Stop monitor message");
                    }
                    else
                    {
                        // 	this is bad when we cannot instantiate the connection to server class
                        System.err.println( "InvocationTargetException: Cannot connect to server");
                        invocationTargetException.printStackTrace();
                    }
                    stayAlive=false;
                }
                catch (StopRequestException stopRequestException)
                {
                    System.out
                            .println("TestClientListener got a Stop monitor message");
                    stayAlive=false;
                }
                catch(ConnectionNotEstablishedException connectionNotEstablishedException)
                {
                    // this is thrown when we cannot connect to the server
                    System.err.println( "ConnectionNotEstablished: Cannot connect to server");
                    stayAlive=false;
                }
                catch (ConnectException connectException)
                {
                    // OK, well for whatever reasons the socket is closed so go
                    // around and try and listen again !
                    System.err
                            .println("Connection exception when reading in bytes from the client : "
                                    +connectException);
                }
                catch (IOException exception)
                {
                    System.err
                            .println("IOException when creating the connection to the server or getting the connection stream back to the client: "
                                    +exception);
                    throw new RuntimeException(
                            "IOException when creating the connection to the server or getting the connection stream back to the client: "
                                    +exception);
                }
            }
        }
    }
    protected void close()
    {
        // ensure that when we close the serversocket (which causes an ioexception) that we know it was us
        stayAlive=false;
        try
        {
            if(serverSocket!=null)
            {
                // closing the server socket will enable us to break out of the loop with an IOException
                // but this will be abosrbed becuase we reminded ourselves that we are closing
                serverSocket.close();
            }
        }
        catch(IOException exception)
        {
            // swallow exceptions on close
            exception.printStackTrace(System.err);
        }
        super.close();
    }
}

