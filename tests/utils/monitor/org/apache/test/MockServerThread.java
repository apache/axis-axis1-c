// Copyright 2003-2004 The Apache Software Foundation.
//(c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License./*

package org.apache.test;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author hawkeye
 */
public class MockServerThread implements Runnable
{
    // NOTE: We read in this string plus two bytes (the end of the request)
    private static String   ENVELOPE_TAG    ="</SOAP-ENV:Envelope>";
    private static String   MIME_BOUNDARY   ="MIME_BOUNDARY";

    private static int      CHARBUFFER_SIZE =20000;

    BufferedReader          inputStream;
    BufferedWriter          outputStream;

    private static int      requests        =0;

    // We cache the entire output file in an array of char[]
    private static Object[] responses;

    public MockServerThread(Socket socket, File responseFile)
            throws IOException , StopRequestException
    {
        System.out.println("MockServerThread(): entry");
        try
        {
            // get the input and outputstreams
            inputStream=new BufferedReader(new InputStreamReader(socket
                    .getInputStream( )));
        }
        catch (IOException e)
        {
            // TODO Auto-generated catch block
            e.printStackTrace( );
        }
        try
        {
            outputStream=new BufferedWriter(new OutputStreamWriter(socket
                    .getOutputStream( )));
        }
        catch (IOException e1)
        {
            // TODO Auto-generated catch block
            e1.printStackTrace( );
        }

        // Now check that the first few bytes are not a stop message
        checkForStopMessage( );

        // we just ignore the incoming message because we don't store it or
        // anything
        System.out.println("MockServerThread(): exit");
    }

    /**
     * This program is made to stop when it receives a specific stop message.
     * This method checks for that message and throws a StopRequestException if
     * it finds that it's been given it
     */
    private String checkForStopMessage( ) throws IOException,
            StopRequestException
    {
        // Read in the first few bytes of the message to see if it's a stop
        // message
        char[] charBuffer=new char[StopMockServer.STOPMOCKSERVER_STRING
                .length( )];
        int totalBytesRead=0;
        String message="";
        int bytesRead=0;
        System.out.println("MockServerThread#run():About to wait for stop msg");
        System.out
                .println("----------------------------------MockServer Thread new Request------------------------");

        while (totalBytesRead<StopMockServer.STOPMOCKSERVER_STRING.length( ))
        {
            try
            {
                bytesRead=inputStream.read(charBuffer, 0,
                        StopMockServer.STOPMOCKSERVER_STRING.length( ));
                System.out.println("MockServerThread#run(): Got some bytes: "
                        +bytesRead);
            }
            catch (IOException exception)
            {
                exception.printStackTrace(System.err);
                throw exception;
            }
            if (bytesRead>-1)
            {
                message+=new String(charBuffer, 0, bytesRead);
                totalBytesRead+=bytesRead;
            }
            else
            {
                System.out.println("got -1 but Got message "+message);
                return message;
                //                throw new IOException(
                //                        "read in -1 bytes when trying to read the initial few bytes
                // from the client");
            }
        }

        if (message.equals(StopMockServer.STOPMOCKSERVER_STRING))
        {
            // we've been told to stop
            System.out
                    .println("--------------------------------------------------------------------");
            throw new StopRequestException("MockServer has been told to stop");
        }
        else
        {
            System.out.println("Got message "+message);
            return message;
        }
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Runnable#run()
     */
    public void run( )
    {
        int bytesRead=0;
        char[] charBuffer=new char[CHARBUFFER_SIZE];
        try
        {
            System.out
                    .println("MockServerThread#run(): About to wait on the inputstream");
            while ((bytesRead=inputStream.read(charBuffer))!=-1)
            {
                System.out
                        .println("MockServerThread#run(): Got some more bytes "
                                +bytesRead);

                // See whether this ends with an envelope
                if (bytesRead>ENVELOPE_TAG.length( )+2)
                {
                    String envelopeString=new String(charBuffer, bytesRead
                            -(ENVELOPE_TAG.length( )+2),
                            ENVELOPE_TAG.length( )+2);
                    System.out
                            .println("MockServerThread#run():EnvelopeString = "
                                    +envelopeString);
                    // Check whether this is an envelope or not
                    if (envelopeString.startsWith(ENVELOPE_TAG)
                            ||envelopeString.indexOf(MIME_BOUNDARY)!=-1)
                    {
                        System.out
                                .println("MockServerThread#run():Got an envelope");
                        // OK, so now output the response message to the
                        // client
                        sendResponseToClient( );
                        System.out
                                .println("-------------------------------MockServer new request---------------------------------");
                    }
                }
                System.out.println("MockServerThread#run(): Going round again "
                        +inputStream);
            }
        }
        catch (IOException exception)
        {
            exception.printStackTrace(System.err);
        }
        System.out.println("MockServerThread#run(): exit");
    }

    /**
     * This method opens the input file and streams it out to the given
     * outputstream
     * 
     * @param outputStream the stream to output the file to
     */
    private void sendResponseToClient( ) throws FileNotFoundException,
            IOException
    {
        // Create a seperate thread and return
        char[] responseMessage=getResponseMessage( );
        if (responseMessage!=null)
        {
            ResponseSender responseSender=new ResponseSender(responseMessage,
                    outputStream);
            Thread responseSenderThread=new Thread(responseSender);
            responseSenderThread.start( );
        }
        else
        {
            System.err
                    .println("We've run out of responses to send back to the client");
            throw new IOException("No more responses to send to clients");
        }
    }

    /**
     * This method reads the response file. Each file may have multiple
     * responses in it which are to be sent to the client in sequence. This
     * method returns back each individual response.
     * 
     * @return a complete HTTP response
     */
    private char[] getResponseMessage( ) throws IOException,
            ArrayIndexOutOfBoundsException
    {
        return (char[]) responses[requests++];
    }

    static void cacheResponseFile(File responseFile)
            throws FileNotFoundException, IOException
    {
        // open the response file for reading in
        FileReader reader=new FileReader(responseFile);
        BufferedReader responseFileStream=new BufferedReader(reader);

        int readInt=0;
        char[] charBuffer=new char[CHARBUFFER_SIZE];
        // read in the complete file
        String completeFile="";
        while (readInt!=-1)
        {
            readInt=responseFileStream.read(charBuffer);
            if (readInt!=-1)
            {
                String tmpString=new String(charBuffer, 0, readInt);
                completeFile=completeFile.concat(tmpString);
            }
        }

        // now split the file by "HTTP"
        String[] responseStrings=completeFile.split("HTTP");

        // now convert these into char[] and store them
        responses=new Object[responseStrings.length];
        // the first line always has "HTTP" in it so the first response is null
        // so I have to do the wierd loop below
        for(int i=1; i<responseStrings.length; i++)
        {
            String tmpString="HTTP"+responseStrings[i];
            int hash=tmpString.indexOf("###");
            if (-1!=hash)
            {
                String len=Integer.toHexString(tmpString.length( )-hash-3);
                if (3!=len.length( ))
                    throw new RuntimeException(
                            "Message length in hex was not 3 characters long "
                                    +len);
                tmpString=tmpString.substring(0, hash)+len
                        +tmpString.substring(hash+3);
            }
            responses[i-1]=tmpString.toCharArray( );
        }

        setCRLF( );
    }

    /**
     * Because the repositories we use accomodate the dos2unix conversion we
     * have a problem. On unix the response files have the crlf converted to
     * just cr. this method returns the crlf !
     */
    private static void setCRLF( )
    {
        if (System.getProperty("os.name").toLowerCase( ).startsWith("windows"))
        {
            System.out
                    .println("Windows operating system - not converting crlf's");
        }
        else
        {
            for(int i=0; i<responses.length; i++)
            {
                if (responses[i]!=null)
                {
                    String request=new String((char[]) responses[i]);
                    // check the last two digits for CRLF - if they are LFLF
                    // then this is wrong
                    // e.g. 0a 0a converts to 0d0a 0d0a
                    // I'm doing it using a matcher because this could get
                    // complicated !
                    Pattern pattern=Pattern.compile("\n");
                    Matcher matcher=pattern.matcher(request);
                    StringBuffer stringBuffer=new StringBuffer( );
                    while (matcher.find( ))
                    {
                        char[] tmpStr=matcher.group( ).toCharArray( );
                        matcher.appendReplacement(stringBuffer, "\r\n");
                    }
                    matcher.appendTail(stringBuffer);
                    // Now put it back into the responses
                    responses[i]=stringBuffer.toString( ).toCharArray( );
                }
            }
        }

        // Irrespective of platform ensure that all responses end with \r\n\r\n
        for(int i=0; i<responses.length; i++)
        {
            if (responses[i]!=null)
            {
                String request=new String((char[]) responses[i]);
                Pattern pattern=Pattern.compile("([^\r\n])(\r\n)*$");
                Matcher matcher=pattern.matcher(request);
                StringBuffer stringBuffer=new StringBuffer(request);
                while (matcher.find( ))
                {
                    char[] tmpStr=matcher.group( ).toCharArray( );
                    // and replace them with the proper sentence !
                    matcher.appendReplacement(stringBuffer, "$1\r\n\r\n");
                }
                matcher.appendTail(stringBuffer);
                // Now put it back into the responses
                responses[i]=stringBuffer.toString( ).toCharArray( );
            }
        }
    }
}