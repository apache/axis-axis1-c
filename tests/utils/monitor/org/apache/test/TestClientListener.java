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

import java.lang.*;
import java.io.*;
import java.net.*;

/**
 * TestClientListener runs as a thread of the
 * 
 * @see TestSingleton class and creates a ServerSocket object on port <b>6323
 *      <b>and from this creates a socket that accepts incoming requests. When
 *      a request is received new threads are created of type
 * @see TestClientThread which do all the communication.
 * @author Andrew Perry
 * @since 1.0
 */

public class TestClientListener implements Runnable
{
    private int             CREATE_SOCKET_TO_SERVER_RETRY =5;
    int                     listenPort                    =0;
    int                     servicePort                   =0;
    String                  serviceHost                   =null;
    boolean                 stayAlive                     =false;
    ServerSocket            server                        =null;
    Thread                  T                             =null;

    public static final int CAPTURE_REQUEST               =1;
    public static final int CAPTURE_RESPONSE              =2;

    public TestClientListener( )
    {}

    public TestClientListener(int listenPort, String serviceHost,
            int servicePort)
    {
        this.listenPort=listenPort;
        this.serviceHost=serviceHost;
        this.servicePort=servicePort;
    }

    public void startListener( )
    {
        if (T!=null&&T.isAlive( ))
            throw new IllegalStateException("ServerManager already running");

        try
        {
            server=new ServerSocket(listenPort);
            T=new Thread(this);
            T.start( );
        }
        catch (Exception ioe)
        {
            ioe.printStackTrace(System.err);
        }
    }

    public void stopListener( )
    {
        stayAlive=false;
        try
        {
            if (T.isAlive( ))
            {
                T.join(500);
            }
        }
        catch (Exception e)
        {
        }
    }

    /**
     * Implementation of
     * 
     * @see Runnable run method required for
     * @see Thread
     */
    public void run( )
    {
        stayAlive=true;
        Socket clientSocket=null;
        Socket serviceSocket=null;
        try
        {
            TestClientThread requestReader=null;
            TestClientThread responseReader=null;
            while (stayAlive==true)
            {
                //server.setSoTimeout(500);
                try
                {
                    clientSocket=server.accept( );

                    // Now create the socket to the server
                    int retry=CREATE_SOCKET_TO_SERVER_RETRY;
                    do
                    {
                        try
                        {
                            serviceSocket=new Socket(serviceHost, servicePort);
                        }
                        catch (Exception se)
                        {
                            System.err
                                    .println("Failed to open socket to service: "
                                            +se);
                            if (retry<=0)
                            {
                                stayAlive=false;
                                continue;
                            }
                            else
                            {
                                // go to sleep
                                System.err.println("Going to sleep");
                                Thread.currentThread( ).sleep(2500);
                                System.err.println("Woke up ");
                            }
                        }
                    }
                    while (serviceSocket==null&&retry-->0);
                    if (serviceSocket==null)
                    {
                        continue;
                    }

                    requestReader=new TestClientThread(clientSocket,
                            serviceSocket, CAPTURE_REQUEST);
                    responseReader=new TestClientThread(clientSocket,
                            serviceSocket, CAPTURE_RESPONSE);
                    requestReader.start( );
                    responseReader.start( );
                    try
                    {
                        if (requestReader.isAlive( ))
                        {
                            requestReader.join(10000);
                        }
                        // If the response reader is still running then
                        // ask it to stop and wait for it.
                        if (responseReader.isAlive( ))
                        {
                            responseReader.cease( );
                            // Wait for upto another .5 secs for the request
                            // reader to finish
                            responseReader.join(2000);
                        }
                    }
                    catch (Exception me)
                    {
                        me.printStackTrace(System.err);
                    }
                    finally
                    {
                        try
                        {
                            if (clientSocket!=null)
                                clientSocket.close( );
                            if (serviceSocket!=null)
                                serviceSocket.close( );
                        }
                        catch (IOException mie)
                        {
                            mie.printStackTrace(System.err);
                        }
                    }
                }
                catch (SocketTimeoutException ste)
                {
                    // interrupt the accept call so the loop can end gracefully
                }
            }
        }
        catch (Exception e)
        {
            System.out.println("TestClientListener: "+e.getMessage( ));
        }
        if (server!=null)
            try
            {
                if (clientSocket!=null)
                    clientSocket.close( );
                if (serviceSocket!=null)
                    serviceSocket.close( );
                server.close( );
            }
            catch (IOException ioe)
            {
                //ioe.printStackTrace(System.err);
            }
        server=null;
        stayAlive=false;
    }
}

