
package org.apache.test;

import java.io.*;
import java.net.*;

public class StopTCPMonitor {

	private String hostname = null;
	private int port = 0;

	public StopTCPMonitor(String monitorHost, int monitorPort) {
		hostname = monitorHost;
		port = monitorPort;
	}

	public void stopMonitor() {
		Socket socket = null;
		BufferedWriter dos = null;
		try {
			String stopString = "STOPTCPM";
			socket = new Socket(hostname, port);
			dos = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
			dos.write(stopString);
		} catch (UnknownHostException uhe) {
			uhe.printStackTrace();
		} catch (ConnectException ce) {
		} catch (IOException ie) {
			ie.printStackTrace();
		} finally {
			try {
				dos.close();
				socket.close();
			} catch (Exception exe) {
				;
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
	}
}

