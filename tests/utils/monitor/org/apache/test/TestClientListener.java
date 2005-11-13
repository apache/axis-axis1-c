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

public class TestClientListener implements Runnable
{
    private int     servicePort    =0;
    private String  serviceHostNme =null;
    private boolean stayAlive      =false;
    ServerSocket    serverSocket   =null;

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

        // no point in carrying on if we can't listen to the client !
        serverSocket=new ServerSocket(listenPort);
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
            try
            {
                System.out
                        .println("TestClientListener#run(): Waiting for a new client request");
                clientSocket=serverSocket.accept( );
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
                System.err
                        .println("IOException when accepting a connection from the client: "
                                +exception);
                throw new RuntimeException(
                        "IOException when accepting a connection from the client: "
                                +exception);
            }

            if (clientSocket!=null)
            {
                // Wait until we have received our first bytes from the
                // client before we create the connection to the service.
                TestClientThread connectionToServer=null;
                try
                {

                        connectionToServer=new TestClientThread(clientSocket,
                                serviceHostNme, servicePort);
                    connectionToServer.start( );
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
                    System.err.println( "Cannot connect to server");
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
        System.out.println("Stopping monitor");
        // We've been told to stop
        // cleanup - hmm, well, we haven't created a connectionToServerThread
        // because that's what returned the Stop exception
        // therefore it hasn't created a thread either so nothing to do there
        // Tell the Monitor to stop writing things out and to tidy itself up
        try
        {
            TCPMonitor.stop( );
        }
        catch (IOException exception)
        {
            System.err
                    .println("Caught an IOException when stopping the monitor: "
                            +exception);
        }

        // release our server socket
        try
        {
            serverSocket.close( );
        }
        catch (IOException exception)
        {
            System.err.println("IOException when closing serverSocket: "
                    +exception);
        }
    }

}

