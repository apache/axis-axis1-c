package org.apache.test;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

//import javax.net.ServerSocketFactory;
//import javax.net.SocketFactory;

/**
 * @author hawkeye
 * This class is designed to listen on a given port and send the request received on that
 * port to the given RequestHandler. 
 * This class is meant to be used in a test suite scenario. where an instance of this class
 * is created per call to a test.
 * 
 */
public class TCPMonitor {
	private ServerSocket serverSocket;
	private String forwardingURL;
	private String responseFile;
	private int forwardingPort;

	/**
	 * Creates a new TCPMonitor listening on the given port for incoming requests (this is always on localhost of course!)
	 * 
	 * @param listenerPort the port to listen for incoming requests
	 * @throws IOException if any issues occur listening for connections or supporting them. 
	 */
	public TCPMonitor(
		int listenerPort,
		String urlToForwardTo,
		int forwardingPort,
		String responseFile)
		throws IOException {
		serverSocket = new ServerSocket(listenerPort);
		this.forwardingURL = urlToForwardTo;
		this.forwardingPort = forwardingPort;
		this.responseFile = responseFile;
	}

	/**
	 * Listen for incoming connections and give them to the handler.
	 * 
	 * Only one listen is called on the server socket. If more than one incoming connection is
	 * expected then this will not be handled.
	 *   
	 * @param handler
	 */
	public void listen(RequestHandler handler) throws IOException {
		Socket clientSocket = serverSocket.accept();

		// Create a reader to read the request sent from the client
		BufferedReader bufferedReader =
			new BufferedReader(
				new InputStreamReader(clientSocket.getInputStream()));

		// Open the socket to the server to forward the request
		Socket outputSocket = new Socket(forwardingURL, forwardingPort);

		// Create a writer to write the incoming client request to
		BufferedWriter urlOutputWriter =
			new BufferedWriter(
				new OutputStreamWriter(outputSocket.getOutputStream()));

		// We have to read in parallel thread.
		RequestForwarder requestReader =
			new RequestForwarder(bufferedReader, urlOutputWriter, handler);
		
		// spin off the thread to listen for a client request
		requestReader.start();

		// Now handle the reply coming back from the forwarded URL
		
		// Create a reader to read the response from the server
		BufferedReader uriBufferedReader =
			new BufferedReader(
				new InputStreamReader(outputSocket.getInputStream()));

		// Create the writer to send it back to the client
		BufferedWriter bufferedWriter =
			new BufferedWriter(
				new OutputStreamWriter(clientSocket.getOutputStream()));

		RequestForwarder responseReader =
			new RequestForwarder(
				uriBufferedReader,
				bufferedWriter,
				new MyRequestHandler(responseFile));
		
		// spin off the thread to listen for a client request
		responseReader.start();
		try {
			// Wait for the request reader to finish
			requestReader.join(25000);

			// If the response reader is still running then
			// ask it to stop and wait for it.
			if(responseReader.isAlive()) {
				responseReader.cease();
				responseReader.join(2000);
			}
		} catch (Exception me) {
			;
		} finally {
			try {
				outputSocket.close();
				clientSocket.close();
				serverSocket.close();
			} catch (IOException mie) {
				;
			}
		}
	}

	public static void main(String[] args) {

		try {
			int listener_port = 0;
			int forward_port = 0;
			String forward_host = "";
			String output_file = "";
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
					output_file = new String(args[++i]);
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
				|| output_file.equals("")) {
				System.out.println(
					"usage: TCPMonitor <-l listen port> <-p forward port> <-h forward host> <-o request output file> [-r response output file]");
				return;
			}
			TCPMonitor monitor =
				new TCPMonitor(listener_port, forward_host, forward_port, response_file);
			long now = System.currentTimeMillis();
			monitor.listen(new MyRequestHandler(output_file));
			System.err.println("**** Listened for " + (System.currentTimeMillis() - now) + " ms" );
		} catch (IOException exception) {
			exception.printStackTrace();
		}
	}
}

class MyRequestHandler extends RequestHandler {
	private FileWriter output;
	private boolean output_set = false;

	public MyRequestHandler() {
		output_set = false;
	}

	public MyRequestHandler(String output_file) throws IOException {
		if(output_file.equals("")) {
			output_set = false;
		} else {
			output = new FileWriter(output_file);
			output_set = true;
		}
	}
	/* (non-Javadoc)
	 * @see RequestHandler#handleWritingException(java.io.IOException)
	 */
	public void handleWritingException(IOException exception) {
		exception.printStackTrace();
	}
	/* (non-Javadoc)
	 * @see RequestHandler#handleReadingException(java.io.IOException)
	 */
	public void handleReadingException(Throwable exception) {
		exception.printStackTrace();
	}

	/* (non-Javadoc)
	 * @see RequestHandler#incomingRequestLine(java.lang.String)
	 */
	public void incomingRequestLine(String line) throws IOException {
		if (output_set) {
			output.write(line);
		}
	}

	public void close() {
		if (output_set) {
			try {
				output.close();
			} catch (IOException e) {
				// do nothing
			}
		}
	}
}
