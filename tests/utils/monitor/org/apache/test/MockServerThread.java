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
import java.text.ParsePosition;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

/**
 * @author hawkeye
 * This class is responsible for handling the socket from the client.
 */
public class MockServerThread extends ChildHandler implements Runnable
{    
    public static final String STOPMOCKSERVER_STRING ="STOPMOCKSERVER";

    // NOTE: We read in this string plus two bytes (the end of the request)
    private static String   ENVELOPE_TAG    ="</SOAP-ENV:Envelope>";
    private static String   MIME_BOUNDARY   ="MIME_BOUNDARY";

    private static int      CHARBUFFER_SIZE =32768; // 32K
    protected boolean continueToRun;

    // Only store the socket so we can close it
    private Socket socket;
    BufferedReader          inputStream;
    BufferedWriter          outputStream;

    private static int      requests        =0;

    private static Response[] responses;
    private static boolean loopOnResponses = false;
    
    protected boolean closedConnection=false;

    /** 
     * Any classes that override this class need this constructor 
     *
     */
    protected MockServerThread ()
    {
    }
    public MockServerThread(Socket socket)
            throws IOException , StopRequestException
    {
        System.out.println("MockServerThread(): entry");
        
        inputStream = null;
        outputStream = null;
        this.socket = socket; 
//        setSocketTimeouts();
        
        try
        {
            inputStream=new BufferedReader(new InputStreamReader(socket.getInputStream( )));
        }
        catch (IOException e)
        {
            // TODO Auto-generated catch block
            e.printStackTrace( );
        }
        try
        {
            outputStream=new BufferedWriter(new OutputStreamWriter(socket.getOutputStream( )));
        }
        catch (IOException e1)
        {
            // TODO Auto-generated catch block
            e1.printStackTrace( );
        }

        // Now check that the first few bytes are not a stop message
        try
        {
            checkForStopMessage( );
        }
        catch(StopRequestException stopRequestException)
        {
            close();
            throw stopRequestException;
        }

        // we just ignore the incoming message because we don't store it or
        // anything
        System.out.println("MockServerThread(): exit");
    }

    /**
     * NOTE: THIS METHOD IS NOT REQUIRED ANYMORE. NOW THAT THE MOCKSERVER IS AN ANTTASK
     * THE ANTTASK AND EXECUTE METOHDS ARE USED. HOWEVER, SO AS NOT TO REWRITE THIS
     * CLASS I LEFT THIS METHOD IN  - IT'S STILL CALLED BUT WILL NEVER FIND THE STRING.
     * This program is made to stop when it receives a specific stop message.
     * This method checks for that message and throws a StopRequestException if
     * it finds that it's been given it
     */
    private String checkForStopMessage( ) throws IOException,
            StopRequestException
    {
        // Read in the first few bytes of the message to see if it's a stop
        // message
        char[] charBuffer=new char[STOPMOCKSERVER_STRING.length( )];
        int totalBytesRead=0;
        String message="";
        int bytesRead=0;
        System.out.println("MockServerThread#run():About to wait for stop msg");
        System.out.println("----------------------------------MockServer Thread new Request------------------------");

        while (totalBytesRead<STOPMOCKSERVER_STRING.length( ))
        {
            try
            {
                bytesRead=inputStream.read(charBuffer, 0, STOPMOCKSERVER_STRING.length( ));
                System.out.println("MockServerThread#run(): Got some bytes: " +bytesRead);
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
            }
        }

        if (message.equals(STOPMOCKSERVER_STRING))
        {
            // we've been told to stop
            System.out.println("--------------------------------------------------------------------");
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
        continueToRun=true;
        int bytesRead=0;
        char[] charBuffer=new char[CHARBUFFER_SIZE];
        try
        {
            System.out.println("MockServerThread#run(): About to wait on the inputstream");
            while ((bytesRead=inputStream.read(charBuffer))!=-1)
            {
                System.out.println("MockServerThread#run(): Got some more bytes " +bytesRead);

                // See whether this ends with an envelope
                if (bytesRead>ENVELOPE_TAG.length( )+2)
                {
                    String envelopeString=new String(charBuffer, bytesRead
                            -(ENVELOPE_TAG.length( )+2), ENVELOPE_TAG.length( )+2);
                    System.out.println("MockServerThread#run():EnvelopeString = " +envelopeString);
                    // Check whether this is an envelope or not
                    if (envelopeString.startsWith(ENVELOPE_TAG)
                            ||envelopeString.indexOf(MIME_BOUNDARY)!=-1)
                    {
                        System.out.println("MockServerThread#run():Got an envelope");

                        sendResponseToClient( );
                        System.out.println("-------------------------------MockServer new request---------------------------------");
                    }
                }
                System.out.println("MockServerThread#run(): Going round again " +inputStream);
            }
        }
        catch (IOException exception)
        {
            if(!closedConnection)
                exception.printStackTrace(System.err);
            else
                System.out.println( "MockServerThread#run(): Connection Has Been Closed");
        }
        System.out.println("MockServerThread#run(): exit");
    }

    /**
     * This method opens the input file and streams it out to the given
     * outputstream
     * 
     * @param outputStream
     *            the stream to output the file to
     */
    private void sendResponseToClient( ) throws FileNotFoundException,
            IOException
    {
        // Create a seperate thread and return
        Response responseMessage=getResponseMessage( );

        if (responseMessage!=null)
        {
            ResponseSender responseSender=new ResponseSender(responseMessage,outputStream, this);
            addChild(responseSender);
            Thread responseSenderThread=new Thread(responseSender);
            responseSenderThread.start( );
        }
        else
        {
            System.err.println("We've run out of responses to send back to the client");
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
    protected Response getResponseMessage( ) throws IOException,
            ArrayIndexOutOfBoundsException
    {
        if (responses[requests] == null && loopOnResponses)
            requests = 0;
        
        return (Response) responses[requests++];
    }

    public static void cacheResponseFile(File responseFile, boolean _loopOnResponses)
            throws FileNotFoundException, IOException
    {
        loopOnResponses = _loopOnResponses;
        // If we already have a set of responses then they will be cleared later on
        
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
        
        // Swap all time occurances to be correct for local time zone
        int timePos = completeFile.indexOf("##TIME##");
        while (timePos != -1)
        {
            String timeText = completeFile.substring(timePos - 8, timePos + 8);

            // Parse time from response
            ParsePosition position = new ParsePosition(0);
            SimpleDateFormat format = new SimpleDateFormat();
            format.applyPattern("HH:mm:ss'##TIME##'");
            format.parse(timeText, position);

            // Recalculate time for local offset
            Calendar calendar = format.getCalendar();
            Date date = calendar.getTime();
            date.setTime(date.getTime() - calendar.getTimeZone().getOffset(date.getTime()));

            // Create new string to be placed in response
            format.applyPattern("HH:mm:ss'.000Z'");
            String gmText = format.format(date);
            
            // Replace in response
            completeFile = completeFile.replaceFirst(timeText, gmText);
            
            // Check for further occurances
            timePos = completeFile.indexOf("##TIME##");
        }

        // now split the file by "HTTP"
        String[] responseStrings=completeFile.split("HTTP");

        // now convert these into char[] and store them
        responses=new Response[responseStrings.length];
        // the first line always has "HTTP" in it so the first response is null
        // so I have to do the wierd loop below
        for( int i = 1; i < responseStrings.length; i++)
        {
            String orgResponse = "HTTP" + responseStrings[i];
            String hash = "###";
            String newResponse = orgResponse;
            
            int hashPos = -1;
            
            // The content length will be modified later, so skip if not chunked.
            if (newResponse.indexOf("Content-Length:")==-1)
                hashPos = orgResponse.indexOf( hash);
            
            if( hashPos != -1)
            {
                // Copy HTTP header into new response and remove header from original response.
			    newResponse = orgResponse.substring( 0, hashPos);
			    orgResponse = orgResponse.substring( hashPos + hash.length());
			    
	            while( hashPos != -1 && orgResponse.length() > 0)
	            {
				    // Find the next hash in the original response.
		            hashPos = orgResponse.indexOf( hash);
		            
		            boolean	eom = false;
		            
					if( hashPos == -1)
				    {
					    hashPos = orgResponse.lastIndexOf( "0");
					    eom = true;
				    }
	
					int chunkLength;
					
		            if( System.getProperty( "os.name").toLowerCase().startsWith( "windows"))
		                chunkLength = hashPos - 4; // Take into account the CR+LF's that surround the chunk size, so subtract 4.
		            else
		                chunkLength = hashPos - 2; // Take into account the LF's that surround the chunk size, so subtract 2.
	
					// Add the next chunk length and data from the original to the new response.
		                
				    newResponse += Integer.toHexString( chunkLength) + orgResponse.substring( 0, hashPos);
	
				    // Remove the old chunk from the original response message.
				    if( eom)
				    {
					    newResponse += orgResponse.substring( hashPos);
					    orgResponse = "";
				    }
				    else
					    orgResponse = orgResponse.substring( hashPos + hash.length());
				}
            }

            responses[i - 1] = new Response( newResponse);
        }
        reader.close();
        requests=0;
        System.out.println( "MockServer got " + (responses.length - 1) + " responses");
        System.out.println( "MockServer will loop on responses? " + loopOnResponses);
    }
   
    public void setClosedConnection(boolean closedConnection)
    {
        this.closedConnection = closedConnection;
    }
    
    /**
     * Ensure the input and outpustreams are closed
     */
    protected void close()
    {
        try
        {
            closedConnection=true;
            socket.close();
        }
        catch(IOException exception)
        {
            // swallow exceptions on close
            //exception.printStackTrace(System.err);
        }
        try
        {
            inputStream.close();
        }
        catch(IOException exception)
        {
            // swallow exceptions on close
            //exception.printStackTrace(System.err);
        }
        
        try
        {
            outputStream.close();
        }
        catch(IOException exception)
        {
            // swallow exceptions on close
           // exception.printStackTrace(System.err);
        }
        
        // just to make sure - clean up the response files
        responses = null;
        super.close();
    }

    public static Response[] getResponses()
    {
        return responses;
    }
//    private void setSocketTimeouts() throws SocketException
//    {
//        socket.setKeepAlive(false);
//        socket.setReuseAddress(true);
//        socket.setSoLinger(false, 1);
//        
//    }
}