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
import java.io.BufferedOutputStream;
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
import java.net.SocketException;
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
 * The input to the service is ignored.
 *
 * Usage: can be found in printUsage()
 * 
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
        System.out.println(
            "Usage: java MockServer <port> <responseFile> <howManyTimesToListen>");
        System.out.println("port: the port to listen for requests on");
        System.out.println(
            "responseFile: The file to write out when a request is received");
        System.out.println(
            "howManyTimesToListen: How many times for the server to listen on the port and send the file - this should the same as the amount of requests you need serving");
    }

    public static void main(String[] args)
    {
        // check that we have the required params
        if (args.length < 3)
        {
            printUsage();
            System.exit(-1);
        }

        // try to get the number of loops to do
        int loops = 0;
        try
        {

            loops = new Integer(args[2]).intValue();
        }
        catch (NumberFormatException e)
        {
            System.out.println(
                "NumberFormatException getting the number of loops to do");
            System.out.println("Got loops of " + args[2]);
            printUsage();
            System.exit(-4);
        }

        // We have the params now let's run the server !

        // Reduce the thread priority so it does not overload the buffer
        // becuase we are writing out and the exe does not get enough thread time
        // to consume
        System.out.println(
            "Thread priority = " + Thread.currentThread().getPriority());
        Thread.currentThread().setPriority(
            Thread.currentThread().getPriority() - 1);

        // Dumbest (but works) way to do the multiple listening is to put the loop here
        for (int i = 0; i < loops; i++)
        {
            try
            {
                MockServer server = new MockServer(args[0], args[1]);

                server.start();
            }
            catch (IOException ioException)
            {
                ioException.printStackTrace();
            }
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
        System.out.println("Output file = " + responseFile);

        ServerSocket serverSocket = new ServerSocket(port);
        Socket incoming = serverSocket.accept();
//        System.out.println("Got the socket " + incoming);
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
            System.out.println(completeInput);
        }
        // System.out.println(completeInput);
        System.out.println(
            "Read the incoming now writing out the responseFile");

        // reply with the file
        outputFile(incoming.getOutputStream());

        // Now close the socket
        incoming.getOutputStream().close();
        incoming.close();
        serverSocket.close();

        System.out.println("Written out response");
    }

    /**
     * this method opens the input file and streams it out to the given outputstream
     * @param outputStream the stream to output the file to 
     */
    private void outputFile(OutputStream outputStream)
        throws FileNotFoundException, IOException
    {
        int loop = 1;

        // open the file for reading
        FileReader reader = new FileReader(responseFile);
        BufferedReader bufferedReader = new BufferedReader(reader);

        // Create a buffered output stream for performance
        BufferedOutputStream bufferedOutputStream =
            new BufferedOutputStream(outputStream);
        int readInt = 0;
        char[] charBuffer = new char[2000];
        while (readInt != -1)
        {
            readInt = bufferedReader.read(charBuffer);

            if (readInt != -1)
            {

                // got to convert from char[] to byte[];
                String tmpString = new String(charBuffer);
                byte[] outArray = tmpString.getBytes();
                try
                {
                    bufferedOutputStream.write(outArray);
                    System.out.println(">" + outArray);
                }
                catch (SocketException exception)
                {
                    System.out.println("loop = " + loop);
                    throw exception;
                }
                bufferedOutputStream.flush();
                loop++;
            }
        }

        System.out.println(
            "Finished writing out the file and closed the stream.");
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
