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

public class StopMockServer
{
    public static final String STOPMOCKSERVER_STRING ="STOPMOCKSERVER";

    private String             hostname              =null;
    private int                port                  =0;

    public StopMockServer(String monitorHost, int monitorPort)
    {
        hostname=monitorHost;
        port=monitorPort;
    }

    public void stopMonitor( )
    {
        Socket socket=null;
        BufferedWriter dos=null;
        try
        {
            System.out.println( "Going to send a stop message to "+hostname+":"+port);
            socket=TCPMonitor.getClientSocket(hostname, port);
            dos=new BufferedWriter(new OutputStreamWriter(socket
                    .getOutputStream( )));
            dos.write(STOPMOCKSERVER_STRING);
        }
        catch (UnknownHostException uhe)
        {
            uhe.printStackTrace( System.err);
        }
        catch (ConnectException ce)
        {
            ce.printStackTrace(System.err);
        }
        catch (IOException ie)
        {
            ie.printStackTrace( System.err);
        }
        finally
        {
            try
            {
                if(dos!=null)
                {
                    dos.close( );
                }
                if(socket!=null)
                {
                    socket.close( );
                }
            }
            catch (Exception exe)
            {
                exe.printStackTrace(System.err);
            }
        }
        System.out.println( "Sent the stop message");
    }

    public static void main(String[] args)
    {
        int monitorPort=0;
        String monitorHost="localhost";

        for(int i=0; i<args.length; i++)
        {
            if (args[i].equals("-p"))
            {
                monitorPort=Integer.parseInt(args[++i]);
                continue;
            }
        }

        if (monitorPort==0||monitorHost.equals(""))
        {
            System.out.println("usage: StopTCPmonitor <-p port>");
            return;
        }

        StopMockServer stop=new StopMockServer(monitorHost, monitorPort);
        stop.stopMonitor( );
        System.gc();
    }
}

