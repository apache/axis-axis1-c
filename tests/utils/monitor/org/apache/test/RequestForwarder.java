package org.apache.test;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.net.SocketException;

/*
 * Created on 31-Aug-2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */

/**
 * @author Andrew Perry
 *
 * Read data from an input socket, pass the data to a handler to do what it
 * wants to its copy of the data, then write the data to an output socket.
 * 
 * Data on the input socket is either the request from the client or the 
 * response from the server.
 * 
 */
public class RequestForwarder extends Thread {
	private BufferedReader reader;
	private BufferedWriter writer;
	private RequestHandler requestHandler;
	private boolean continueToRun = true;

	/**
	 * @param bufferedReader
	 * @param urlOutputWriter
	 * @param requestHandler
	 */
	public RequestForwarder(
		BufferedReader bufferedReader,
		BufferedWriter urlOutputWriter,
		RequestHandler requestHandler) {
		this.reader = bufferedReader;
		this.writer = urlOutputWriter;
		this.requestHandler = requestHandler;
	}

	public void cease() {
		continueToRun = false;
	}

	public void run() {
		char[] buffer = new char[1024];
		try {
			int ret = 0;
			while ((ret = reader.read(buffer, 0, 1023)) != -1 && continueToRun) {
				String line = new String(buffer, 0, ret);
				if(line.equalsIgnoreCase("STOPTCPM")) {
					System.err.println("*** RECEIVED STOP COMMAND. Stopping ***");
					break;
				}

				// give the incoming line to the handler
				requestHandler.incomingRequestLine(line);

				// Output the line to the real URL
				writer.write(line);
				writer.flush();
			}
		} catch (SocketException socketException) {
			//System.out.println("socketException: " + socketException);
		} catch (IOException exception) {
			requestHandler.handleWritingException(exception);
		} catch (RuntimeException runtimeException) {
			System.out.println("runtimeException: " + runtimeException);
		} catch (Throwable exception) {
			requestHandler.handleReadingException(exception);
		} finally {
			try {
				writer.close();
				reader.close();
			} catch (IOException ioe) {
				;
			}
			requestHandler.close();
		}
	}
}
