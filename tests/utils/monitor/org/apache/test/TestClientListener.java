package org.apache.test;

import java.lang.*;
import java.io.*;
import java.net.*;

/**
 * TestClientListener runs as a thread of the @see TestSingleton class and
 * creates a ServerSocket object on port <b>6323<b> and from this creates 
 * a socket that accepts incoming requests. When a request is received new
 * threads are created of type @see TestClientThread which do all the 
 * communication.
 *
 * @author Andrew Perry
 * @since 1.0
 */

public class TestClientListener implements Runnable {

	int listenPort = 0;
	int servicePort = 0;
	String serviceHost = null;
	boolean stayAlive = false;
	ServerSocket server = null;
	Thread T = null;

	public static final int CAPTURE_REQUEST = 1;
	public static final int CAPTURE_RESPONSE = 2;

	public TestClientListener() { }

	public TestClientListener(int listenPort, String serviceHost, int servicePort) {
		this.listenPort  = listenPort;
		this.serviceHost = serviceHost;
		this.servicePort = servicePort;
	}

	public void startListener() {
		if (T != null && T.isAlive())
			throw new IllegalStateException("ServerManager already running");
        
		try {
			server = new ServerSocket(listenPort);
			T = new Thread(this);
			T.start();
		} catch (Exception ioe) {
			ioe.printStackTrace(System.err);
		}
	}

	public void stopListener() {
		stayAlive = false;
		try {
			if(T.isAlive()){
				T.join(500);
			}
		} catch (Exception e) {
		}
	}

	/**
	 * Implementation of @see Runnable run method required for @see Thread
	 */
	public void run() {
		stayAlive = true;
		Socket clientSocket = null;
		Socket serviceSocket = null;
		try {
			TestClientThread requestReader = null;
			TestClientThread responseReader = null;
			while (stayAlive == true) {
				//server.setSoTimeout(500);
				try {
					clientSocket = server.accept();
					try {
						serviceSocket = new Socket(serviceHost, servicePort);
					} catch (Exception se) {
						System.err.println("Failed to open socket to service");
						stayAlive = false;
						continue;
					}
					requestReader = new TestClientThread(clientSocket, serviceSocket, CAPTURE_REQUEST);
					responseReader = new TestClientThread(clientSocket, serviceSocket, CAPTURE_RESPONSE);
					requestReader.start();
					responseReader.start();
					try {
						if(requestReader.isAlive()) {
							requestReader.join(10000);
						}
						// If the response reader is still running then
						// ask it to stop and wait for it.
						if(responseReader.isAlive()) {
							responseReader.cease();
						// Wait for upto another .5 secs for the request reader to finish
							responseReader.join(2000);
						}
					} catch (Exception me) {
						;
					} finally {
						try {
							if(clientSocket != null)
								clientSocket.close();
							if(serviceSocket != null)
								serviceSocket.close();
						} catch (IOException mie) {
							;
						}
					}
				}
				catch (SocketTimeoutException ste) {
					// interrupt the accept call so the loop can end gracefully
				}
			}
		} catch (Exception e) {
			System.out.println("TestClientListener: " + e.getMessage());
		}
		if (server != null)
		try {
			if(clientSocket != null)
				clientSocket.close();
			if(serviceSocket != null)
				serviceSocket.close();
			server.close();
		} catch (IOException ioe) {
			//ioe.printStackTrace(System.err);
		}
		server = null;
		stayAlive = false;
	}
}

