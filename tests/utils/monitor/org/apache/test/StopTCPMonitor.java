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

public class StopTCPMonitor {
    public static final String STOPTCPMON = "STOPTCPM";

	private String hostname = null;
	private int port = 0;

	public StopTCPMonitor(String monitorHost, int monitorPort) {
		hostname = monitorHost;
		port = monitorPort;
	}

	public void stopMonitor() {
	    System.out.println( "StopTCPMonitor#stopMonitor(): Sending stop message to monitor");
		Socket socket = null;
		BufferedWriter dos = null;
		try {
		    socket = TCPMonitor.getClientSocket(hostname, port);
			dos = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
			dos.write(STOPTCPMON);
			dos.flush();
		} catch (UnknownHostException uhe) {
			uhe.printStackTrace();
		} catch (ConnectException ce) {
		    ce.printStackTrace();
		} catch (IOException ie) {
			ie.printStackTrace();
		} finally {
			try {
				dos.close();
				socket.close();
			} catch (Exception exe) {
			    exe.printStackTrace();
			}
		}
	}

	public static void main(String[] args) {
		int monitorPort = 0;
		String monitorHost = "";

		for (int i = 0; i < args.length; i++) {
			if (args[i].equals("-p")) {
				monitorPort = Integer.parseInt(args[++i]);
				continue;
			}
			if (args[i].equals("-h")) {
				monitorHost = new String(args[++i]);
				continue;
			}
		}

		if(monitorPort == 0 || monitorHost.equals("")) {
			System.out.println("usage: StopTCPmonitor <-p port> <-h host>");
			return;
		}

		StopTCPMonitor stop = new StopTCPMonitor(monitorHost, monitorPort);
		stop.stopMonitor();
		System.gc();
	}
}

