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
 * TestClientThread is a child thread of TestClientListener and handles all
 * communication between the original requestor and the TCPMonitor class.
 * 
 * @author Andrew Perry
 * @since 1.0
 * @see TestClientListener
 */

public class TestClientThread extends Thread
{

    private Socket          clientSocket     =null;
    private Socket          serviceSocket    =null;
    private int             mode             =0;
    private int             clientPort       =0;
    boolean         continueToRun    =true;
    private int             totalBytesRead   =0;

    public static final int CAPTURE_REQUEST  =1;
    public static final int CAPTURE_RESPONSE =2;

    /**
     * Class constructor with the client socket used to communitate with the
     * client.
     * 
     * @param socket reference to the socket connected to the client
     */
    public TestClientThread(Socket clientSocket, Socket serviceSocket, int mode)
    {
        this.clientSocket=clientSocket;
        this.serviceSocket=serviceSocket;
        this.mode=mode;
    }

    public void cease( )
    {
        // we only cease if we have are capturing the request from the client
        // if we are capturing the request from the server, and we have got some already
        // then we must continue to capture the request and end nicely
        if(mode == CAPTURE_REQUEST)
        {
            continueToRun=false;
//            System.out.println( "been told to cease");
        }
        else
        {
//            System.out.println( "been told to cease but ignoring because I haven't finished");
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
        BufferedWriter dos=null;
        BufferedReader dis=null;
        String strMode="unknown";
        int readReturn=0;

        try
        {
            char[] buffer=new char[4096]; // 4K buffer

            if (mode==CAPTURE_REQUEST)
            {
                strMode="REQUEST - ";
                dos=new BufferedWriter(new OutputStreamWriter(serviceSocket
                        .getOutputStream( )));
                dis=new BufferedReader(new InputStreamReader(clientSocket
                        .getInputStream( )));
            }
            else
                if (mode==CAPTURE_RESPONSE)
                {
                    strMode="RESPONSE - ";
                    dos=new BufferedWriter(new OutputStreamWriter(clientSocket
                            .getOutputStream( )));
                    dis=new BufferedReader(new InputStreamReader(serviceSocket
                            .getInputStream( )));
                }
            while (continueToRun && (readReturn=dis.read(buffer, 0, 4096))!=-1)
            {
                totalBytesRead+=readReturn;
                String inputLine=new String(buffer, 0, readReturn);
                try
                {
                    if (inputLine.startsWith(StopTCPMonitor.STOPTCPMON))
                    {
                        continueToRun=false;
                        TCPMonitor.getInstance( ).stop( );
                    }
                    else
                    {
                        if (mode==CAPTURE_REQUEST)
                        {
                            TCPMonitor.getInstance( ).writeRequest(inputLine);
                        }
                        else
                        {
                            if (mode==CAPTURE_RESPONSE)
                        {
                                TCPMonitor.getInstance( ).writeResponse(inputLine);
                        	}
                        }
                    }
                }
                catch (Exception exception)
                {
                    exception.printStackTrace();
                }
                if(continueToRun)
                {
                    dos.write(inputLine);
                    dos.flush( );
                }
            }
        }
        catch (EOFException eof)
        {
            eof.printStackTrace( );
        }
        catch (IOException e)
        {
            // ignore these becuase we haven't quite managed to make this system as nice 
            // as we would like so we get these (when it's working correctly) when
            // the readers and writers have been closed by the TCPMonitor instance
            // this is fine because it's when the system is shuuting down and we don't need them
        }
        finally
        {
            try
            {
                dis.close( );
                dos.close( );
            }
            catch (Exception e)
            {
                e.printStackTrace( );
            }
        }
    }

    /**
     * This method tells the starting thread whether this objec has started to
     * read in bytes yet. If it has then the requestor of this method can tell
     * how many bytes have been received and thus see whether the bytes are a
     * message to stop or not
     * 
     * @return the number of bytes received by this reader
     */
    public int getBytes( )
    {
        return totalBytesRead;
    }
}

