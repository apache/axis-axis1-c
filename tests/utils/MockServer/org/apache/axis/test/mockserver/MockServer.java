/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/**
 * @author hawkeye (hawkinsj@uk.ibm.com)
 */
package org.apache.axis.test.mockserver;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintStream;
import java.io.Reader;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketImpl;

import javax.net.ServerSocketFactory;

import org.apache.xerces.parsers.IntegratedParserConfiguration;

/**
 * This class is meant to solve the problem of how we debug problems when we don't have the service at the back end e.g. when 
 * a user puts an issue on the mailing list and only gives us the captured output from e.g. tcpmon. 
 * 
 * This class mocks up a back end server for testing purposes. It listens on a port of choice and sends back an expected response as 
 * defined in a response file.
 * The response files must have the complete http header information (I suggest the response file is the captured output from tcpmon).
 * This program does not add anything to the outgoing stream.
 * 
 * 
 * The input to the service is ignored.
 * 
 * Possible enhancements to this program:
 * 1. allow multiple response files by looking to see what service is being called and having a lookup table of response files
 * 2. Not requiring http header info in the response file by using a default set of headers.
 */

public class MockServer
{
    private int port;
    File responseFile;
    public static final void printUsage()
    {
        System.out.println("Usage: java MockServer <port> <responseFile>");
    }

    public static void main(String[] args)
    {
        // check that we have the required params
        if (args.length < 2)
        {
            printUsage();
            System.exit(-1);
        }

        // We have the params now let's run the server !
        try
        {
            MockServer server = new MockServer(args[0], args[1]);
            //    server.accept();

            server.start();
        }
        catch (IOException ioException)
        {
            ioException.printStackTrace();
        }
    }

    /**
     * This method starts the server listening on the port. When any request comes in on that port we return the 
     * responseFile contents verbatum. When we have finished reading the file and sending it back to the client we 
     * close the connection and terminate this program.
     *  
     */
    private void start() throws IOException
    {
        System.out.println("MockServer listening on port " + port);

        ServerSocket serverSocket = new ServerSocket(port);
        Socket incoming = serverSocket.accept();
        System.out.println("Got the socket " + incoming);
        InputStream inputStream = incoming.getInputStream();

        InputStreamReader inputStreamReader =
            new InputStreamReader(inputStream);

        // For debug for now print out what we get.
        // read until the \n\n
        String completeInput = "";
        int nextByte = 0;
        System.out.println("Reading in from the socket ");

        while (!completeInput.endsWith("\n\n")
            && !completeInput.toLowerCase().endsWith("connection: keep-alive")
            && (nextByte = inputStreamReader.read()) != -1)
        {
            completeInput += (char) nextByte;
            //        	System.out.println(completeInput);
        }
        // System.out.println(completeInput);
        System.out.println(
            "Read the incoming now writing out the responseFile");

        // reply with the file
        outputFile(incoming.getOutputStream());

        // Now close the socket
        incoming.close();

    }

    /**
     * this method opens the input file and streams it out to the given outputstream
     * @param outputStream the stream to output the file to 
     */
    private void outputFile(OutputStream outputStream)
        throws FileNotFoundException, IOException
    {
        // open the file
        FileReader reader = new FileReader(responseFile);

        while (reader.ready())
        {
            int readInt = reader.read();
            outputStream.write((byte) readInt);
        }
    }

    /**
     * @param portNumber the port to listen on
     * @param responseFile the responseFile to send back
     */
    public MockServer(String portNumber, String responseFile)
        throws IOException
    {
        // parse the portNumber
        try
        {
            port = Integer.parseInt(portNumber);
        }
        catch (NumberFormatException numberFormatException)
        {
            System.out.println(
                "The portNumber <" + portNumber + "> is not a valid integer ");
            printUsage();
            System.exit(-2);
        }

        // check the responsefile is there
        this.responseFile = new File(responseFile);

        if (!this.responseFile.canRead())
        {
            System.out.println(
                "Can't read the response file <" + responseFile + ">");
            printUsage();
            System.exit(-3);
        }
    }
}
