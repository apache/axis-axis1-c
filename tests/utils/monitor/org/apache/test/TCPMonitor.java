
package org.apache.test;

import java.io.FileWriter;

/**
 * @author perryan
 * This class is designed to listen on a given port and send the request received on that
 * port to the given RequestHandler. 
 * This class is meant to be used in a test suite scenario. where an instance of this class
 * is created per call to a test.
 * 
 */
public class TCPMonitor {

	private static TCPMonitor singleton = null;
	private static FileWriter requestFileWriter;
	private static FileWriter responseFileWriter;
	private static boolean responseFileWriterOpen = false;
	private static TestClientListener T = null;

	/**
	 * Creates a new TCPMonitor listening on the given port for incoming requests (this is always on localhost of course!)
	 * 
	 * @param listenerPort the port to listen for incoming requests
	 * @throws IOException if any issues occur listening for connections or supporting them. 
	 */
	private TCPMonitor(
		int listenerPort,
		String serviceHost,
		int servicePort,
		String requestFile,
		String responseFile)
		throws Exception {

		requestFileWriter = new FileWriter(requestFile);
		if(! responseFile.equals("")) {
			responseFileWriter = new FileWriter(responseFile);
			responseFileWriterOpen = true;
		}

		/*
		 * Create a thread which listens for incoming requests
		 */
		T = new TestClientListener(listenerPort, serviceHost, servicePort);
		T.startListener();
	}

	public static TCPMonitor getInstance() throws Exception {
		if(singleton == null) {
			throw new Exception("TCPMonitor has not been initialised.");
		}
		return singleton;
	}

	public static TCPMonitor getInstance(
		int listenerPort,
		String serviceHost,
		int servicePort,
		String requestFile,
		String responseFile) throws Exception {
		if(singleton == null) {
			singleton = new TCPMonitor(listenerPort,serviceHost,servicePort,requestFile,responseFile);
		}
		return singleton;
	}

	public static void stop() {
		T.stopListener();
		try {
			requestFileWriter.close();
			responseFileWriter.close();
		} catch (Exception e) {
			;
		}
		singleton=null;
		System.exit(0);
	}

	public void writeRequest(String inputLine) {
		try {
			requestFileWriter.write(inputLine);
			requestFileWriter.flush();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void writeResponse(String inputLine) {
		try {
			if(responseFileWriterOpen) {
				responseFileWriter.write(inputLine);
				responseFileWriter.flush();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {

		try {
			int listener_port = 0;
			int forward_port = 0;
			String forward_host = "";
			String request_file = "";
			String response_file = "";
			for (int i = 0; i < args.length; i++) {
				if (args[i].equals("-l")) {
					listener_port = Integer.parseInt(args[++i]);
					continue;
				}
				if (args[i].equals("-p")) {
					forward_port = Integer.parseInt(args[++i]);
					continue;
				}
				if (args[i].equals("-h")) {
					forward_host = new String(args[++i]);
					continue;
				}
				if (args[i].equals("-o")) {
					request_file = new String(args[++i]);
					continue;
				}
				if (args[i].equals("-r")) {
					response_file = new String(args[++i]);
					continue;
				}
			}
			if (listener_port == 0
				|| forward_port == 0
				|| forward_host.equals("")
				|| request_file.equals("")) {
				System.out.println(
					"usage: TCPMonitor <-l listen port> <-p forward port> <-h forward host> <-o request output file> [-r response output file]");
				return;
			}
			TCPMonitor monitor =
				TCPMonitor.getInstance(listener_port, forward_host, forward_port, request_file, response_file);
		} catch (Exception exception) {
			exception.printStackTrace();
		}
	}
}

