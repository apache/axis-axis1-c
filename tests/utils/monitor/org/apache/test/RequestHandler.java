package org.apache.test;
import java.io.IOException;

/**
 * @author hawkeye
 * This class is given an incoming request. It can do with it what it will. the idea is that
 * this class could potentially output the message to a log and then forward the message
 * to another URI.
 *
 */

public abstract class RequestHandler {
	/**
	 * handle any exceptions that happen while we are writing out the output to the forwarding uri
	 * @param exception
	 */
	public abstract void handleWritingException(IOException exception);

	/**
	 * 
	 * Handle exceptions that happen when reading in the request. 
	 * 
	 * @param exception
	 */
	public abstract void handleReadingException(Throwable exception);

	/**
	 * As the lines come in from the initial request this method is called. 
	 * The handler can choose to print them out to a file etc.
	 * This will not change what is sent to the server.
	 *  
	 * @param line a line coming in from the requestor
	 */
	public abstract void incomingRequestLine(String line) throws IOException;

	/**
	 * Call close on ant open files
	 *
	 */
	public abstract void close();
}
