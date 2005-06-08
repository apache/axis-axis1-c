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

public class TestClientThread extends Thread
{
    private boolean          continueToRun                 =true;
    // the responder back to the client
    private ClientReturner   clientReturner                =null;

    // I didn't want to make this global but it has to be for the constructor
    // pattern to work :-(
    private int              bytesRead                     =0;
    private static final int READ_BUFFER_SIZE              =10000;                     // 4096=4k
    private char[]           readBuffer                    =new char[READ_BUFFER_SIZE];

    // the request from the client 
    private BufferedReader   clientRequestStream           =null;
    // the connection to the server where we forwaard the clients request to.
    private BufferedWriter   streamToServer                =null;

    // How many times to try to connect to the server before giving in
    private static final int CREATE_SOCKET_TO_SERVER_RETRY =5;

    /**
     * Class constructor with the client socket used to communicate with the
     * client. This is quite a powerful constructor it actually reads in bytes
     * from the client socket to work out whether it should stay alive or not if
     * not then it throws an exception
     * 
     * @param socket reference to the socket connected to the client
     * @exception StopRequestException if a stoprequest is received from the
     *                client
     * @exception ConnectException if the first read off the wire gave us -1
     *                i.e. the stream from the client is closed
     */
    public TestClientThread(Socket clientSocket, String serviceHostName,
            int servicePort) throws StopRequestException , IOException ,
            ConnectException
    {
        //        System.out.println( "TestClientThread(3): entry");
        IsStopMessage(clientSocket);
        Socket serviceSocket=createSocketToServer(serviceHostName, servicePort);
        writeToServer(readBuffer, bytesRead);

        // OK, now we've done that we can create the new thread to stream
        // the result back to the client
        clientReturner=new ClientReturner(clientSocket, serviceSocket);
        clientReturner.start( );

    }

    private void IsStopMessage(Socket clientSocket) throws IOException,
            StopRequestException
    {
        // Get the input stream from the client
        clientRequestStream=new BufferedReader(new InputStreamReader(
                clientSocket.getInputStream( )));

        // Read in the first few bytes to ensure that we are not being told to
        // stop
        try
        {
            bytesRead=clientRequestStream.read(readBuffer, 0,
                    StopTCPMonitor.STOPTCPMON.length( ));
        }
        catch (ConnectException connectException)
        {
            // did we manage to read any bytes in?
            if (bytesRead>0)
            {
                // Well we did !
                System.err
                        .println("Got a connectException when reading in the first few bytes from the stream");
                System.err
                        .println("Read in some bytes but not enough to work out whether we should stop or not");
                System.err
                        .println("Highly unlikely this is good so we'll stop !");
                throw connectException;
            }
            else
            {
                System.err
                        .println("Read in zero bytes before the client shut the connection");
                System.err.println("Continuing to read in future requests");
            }
        }
        catch (IOException exception)
        {
            System.err
                    .println("IOException when reading the clients initial request: "
                            +exception);
        }
        if (bytesRead!=-1)
        {
            String inputLine=new String(readBuffer, 0, bytesRead);
            if (inputLine.startsWith(StopTCPMonitor.STOPTCPMON))
            {
                clientRequestStream=null;
                throw new StopRequestException(
                        "Received a stop monitor message");
            }
            else
            {
                // now put the line into the request file for later processing
                TCPMonitor.getInstance( ).writeRequest(readBuffer, bytesRead);
            }
        }
        else
        {
            // looks like they closed the connection so throw an exception to
            // say we have closed
            throw new ConnectException(
                    "Connection closed when reading first few bytes of client's request");
        }

    }

    /**
     * Reads the request from the client and if of a valid format will extract
     * the test ID and required data and call the TestSingleton class to set or
     * get the information. It is assumed that all requests are UTF Strings.
     * <p>
     * If the incoming request does not contain a test ID, or is not of a
     * recognised format then the socket will be closed and this object will
     * finish.
     * </p>
     */
    public void run( )
    {
        try
        {
            while (continueToRun
                    &&(bytesRead=clientRequestStream.read(readBuffer, 0,
                            READ_BUFFER_SIZE))!=-1)
            {
                //                System.out.println( "About to write some bytes to the
                // server");
                writeToServer(readBuffer, bytesRead);
                //System.out.println("Wrote some bytes to the server: "
                  //      +new String(readBuffer, 0, bytesRead));

                TCPMonitor.getInstance( ).writeRequest(readBuffer, bytesRead);
            }
            // so we've either got continueToRun=false or read =-1;
            //            System.out.println( "TestClientThread#run(): TestClientThread
            // bytesRead = "+bytesRead);
            //            System.out.println( "TestClientThread#run(): continueToRun =
            // "+continueToRun);
        }
        catch (SocketException socketException)
        {
            System.err
                    .println("TestClientThread#run(): SocketException when reading client request:");
            socketException.printStackTrace(System.err);
        }
        catch (IOException exception)
        {
            System.err
                    .println("TestClientThread#run(): IOException when reading clients request: "
                            +exception);
            throw new RuntimeException(
                    "TestClientThread#run(): IOException when reading clients request: "
                            +exception);
        }

        // need to ensure we close down the clientFileReturner we created for
        // this connection
        clientReturner.continueToRun=false;

        //        System.out.println( "TestClientThread#run(): exit");
    }

    public Socket createSocketToServer(String serviceHostName, int servicePort)
            throws IOException
    {
        Socket serviceSocket=null;
        int retry=CREATE_SOCKET_TO_SERVER_RETRY;
        do
        {
            try
            {
                serviceSocket=new Socket(serviceHostName, servicePort);
            }
            catch (UnknownHostException unknownHostException)
            {
                // oh dear !
                throw unknownHostException;
            }
            catch (Exception se)
            {
                System.err.println("Failed to open socket to service: "+se);
                if (retry>0)
                {
                    // go to sleep
                    System.err.println("Going to sleep before retrying");
                    try
                    {
                        Thread.currentThread( ).sleep(2500);
                    }
                    catch (InterruptedException interruptedException)
                    {
                        // don't know if this is an issue?
                        System.out
                                .println("Got an interruptedxception sleeping on this thread "
                                        +interruptedException);
                    }
                    System.err.println("Woke up ");
                }
            }
        }
        while (serviceSocket==null&&retry-->0);

        try
        {
            streamToServer=new BufferedWriter(new OutputStreamWriter(
                    serviceSocket.getOutputStream( )));
        }
        catch (IOException exception)
        {
            System.err
                    .println("IOEXception when getting the writer to the service "
                            +exception);
            throw exception;
        }

        return serviceSocket;
    }

    private void writeToServer(char[] request, int bytesToWrite)
            throws IOException
    {
        //System.out.println( "writeToServer: "+new String(request, 0,
        // bytesToWrite));
        streamToServer.write(request, 0, bytesToWrite);
        streamToServer.flush( );
    }

}

