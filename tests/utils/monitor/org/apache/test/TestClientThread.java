
package org.apache.test;

import java.io.*;
import java.net.*;

/**
 * TestClientThread is a child thread of TestClientListener and 
 * handles all communication between the original requestor and 
 * the TCPMonitor class.
 *
 * @author Andrew Perry
 * @since 1.0
 * @see TestClientListener
 */

public class TestClientThread extends Thread {

	private Socket clientSocket = null;
	private Socket serviceSocket = null;
	private int mode = 0;
	private int clientPort = 0;
	boolean continueToRun = true;

	public static final int CAPTURE_REQUEST = 1;
	public static final int CAPTURE_RESPONSE = 2;

	/**
	 * Class constructor with the client socket used to communitate
	 * with the client.
	 * @param socket	reference to the socket connected to the client
	 */ 
	public TestClientThread(Socket clientSocket, Socket serviceSocket, int mode) {
		this.clientSocket = clientSocket;
		this.serviceSocket = serviceSocket;
		this.mode = mode;
	}

	public void cease() {
		continueToRun = false;
	}

	/**
	 * Reads the request from the client and if of a valid format will 
	 * extract the test ID and required data and call the
	 * TestSingleton class to set or get the information.
	 * It is assumed that all requests are UTF Strings.
	 * <p>
	 * If the incoming request does not contain a test ID, or is not of a
	 * recognised format then the socket will be closed and this object will
	 * finish.
	 * </p>
	 */
	public void run() {
		BufferedWriter dos = null;
		BufferedReader dis = null;
		String strMode = "unknown";
		
		try {
			char[] buffer = new char[4096]; // 4K buffer

			if(mode == CAPTURE_REQUEST) {
				strMode = "REQUEST - ";
				dos = new BufferedWriter(new OutputStreamWriter(serviceSocket.getOutputStream()));
				dis = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
			} else if(mode == CAPTURE_RESPONSE) {
				strMode = "RESPONSE - ";
				dos = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
				dis = new BufferedReader(new InputStreamReader(serviceSocket.getInputStream()));
			}
			int readReturn = 0;
			while( (readReturn = dis.read(buffer, 0, 4096)) != -1 ){
				String inputLine = new String(buffer, 0 , readReturn);

				try {
					if(inputLine.indexOf("STOPTCPM") != -1) {
						TCPMonitor.getInstance().stop();
						continueToRun = false;
						break;
					}
					if(mode == CAPTURE_REQUEST) {
						TCPMonitor.getInstance().writeRequest(inputLine);
					} else if(mode == CAPTURE_RESPONSE) {
						TCPMonitor.getInstance().writeResponse(inputLine);
					}
				} catch (Exception exe) {
				}
				dos.write(inputLine);
				dos.flush();
			}

		} catch (EOFException eof) {
		} catch (IOException e) {
		} finally {
			try {
				dis.close();
				dos.close();
			} catch (Exception e) { }
		}
	}
}

