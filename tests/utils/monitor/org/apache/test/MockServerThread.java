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

    private static Response[] responses;
    
    private boolean closedConnection=false;

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
            if(!closedConnection)
            {
                exception.printStackTrace(System.err);
            }
            else
            {
                System.out.println( "MockServerThread#run(): Connection Has Been Closed");
            }
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
//        System.out.println( "responsemessage ======="+responseMessage);
//        System.out.println( "===================================================");
        if (responseMessage!=null)
        {
            ResponseSender responseSender=new ResponseSender(responseMessage,
                    outputStream, this);
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
    private Response getResponseMessage( ) throws IOException,
            ArrayIndexOutOfBoundsException
    {
        return (Response) responses[requests++];
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
            date.setTime(date.getTime() - calendar.getTimeZone().getRawOffset());

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
            
            int hashPos = orgResponse.indexOf( hash);
            String newResponse = orgResponse;
            
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
		            {
		                chunkLength = hashPos - 4; // Take into account the CR+LF's that surround the chunk size, so subtract 4.
		            }
		            else
		            {
		                chunkLength = hashPos - 2; // Take into account the LF's that surround the chunk size, so subtract 2.
		            }
	
					// Add the next chunk length and data from the original to the new response.
		                
				    newResponse += Integer.toHexString( chunkLength) + orgResponse.substring( 0, hashPos);
	
				    // Remove the old chunk from the original response message.
				    if( eom)
				    {
					    newResponse += orgResponse.substring( hashPos);
					    orgResponse = "";
				    }
				    else
				    {
					    orgResponse = orgResponse.substring( hashPos + hash.length());
				    }
				}
            }

            responses[i - 1] = new Response( newResponse);
        }
        
        System.out.println( "MockServer got " + (responses.length - 1) + " responses");
    }

//        /**
//         * Because the repositories we use accomodate the dos2unix conversion we
//         * have a problem. On unix the response files have the crlf converted to
//         * just cr. this method returns the crlf !
//         * 
//         * The HTTP header and chunk sizes need to be delimited with CR LF's.
//         * The 'server response' expected files used to mimic the response of a
//         * server when performing unit tests also need to have the correct
//         * delimiting character combinations in the fake response messages
//         * (generated by the monitor). Problems arise because the expected
//         * response files have been captured on different operating systems (Unix
//         * and Windows) and then edited using a variety of editors that interpret
//         * the CR character differently. Thus the file may be stored with or
//         * without the CR characters. Also, the souce control application can be
//         * set to convert a single LF character into a CR LF combination. The
//         * outcome of all this character manipulation is that LF's may or may not
//         * have the necessary associated CR for it to be recognised by the HTTP
//         * transport. It is not just sufficient to look for every LF and to prefix
//         * it with a CR because the context of that LF must be taken into
//         * consideration. For example, if a LF is found in the HTTP header then it
//         * definitely needs a CR prefix. This also applies when the message is
//         * chunked and the chunk size must also be delimited by the CR LF sequence.
//         * But, when a LF appears inside a chunk of data it should remain unchanged
//         * unless the chunk size is different from the actual data size between
//         * chunks, in which case the CR has probably been stripped out and needs to
//         * be replaced. Below is a low level design of what should work in all
//         * instances...
//         * 
//         * Is the message chunked?
//         * NO: Convert all single LF sequences to CR+LF.
//         *     NB: Because the value associated with the 'Content-Length' label is
//         *         not used correctly, if the size of the file grows larger than the
//         *         Content-Length value, no action is taken.
//         *         Exit.
//         * YES: Convert all single LF sequences to CR+LF in the HTTP header.
//         *      Set Index = location of the first 'chunk' value.
//         *      Read the chunk size.
//         *      While the chunk size > 0
//         *        Convert any single LF sequences to CR+LF that surround the chunk
//         *        value.
//         *        Is the character at offset Index + chunk size equal to CR or LF?
//         *        NO: Count up the number of unaccompanied LF's in the chunk.
//         *            Is the difference between the expected and actual chunk data
//         *            length double the number of unaccompanied LF's?
//         *            NO: Error - Irreconcilable differences between expected and
//         *                        actual chunk data sizes.
//         *                Exit.
//         *            YES: Convert all single LF sequences to CR+LF in the chunk
//         *                 data.
//         *                 Continue.
//         *            Index = Index + chunk size.
//         *            Read the new chunk size.
//         *            End of while.
//         *      Exit.
//         */
//        private static void setCRLF( )
//        {
//    	    String sLF = "\n";
//    	    String sCR = "\r";
//    	    String sCRLF = sCR + sLF;
//            String sContentLength = "Content-Length:";
//    	    
//            for( int i = 0; i < responses.length; i++)
//            {
//                if( responses[i] != null)
//                {
//                    System.out.println( "WE HAVE "+responses[i].getMessage().length);
//    
//                    
//                    String sResponse = new String(responses[i].getMessage());
//                    String sModifiedResponse = "";
//                	boolean bChunked = sResponse.indexOf( sContentLength) == -1;
//                	
//                	if( bChunked)
//                	{
//                        System.out.println("Information - Response file is chunked.");
//    
//                        // Process HTTP header block.  At the end of each line in
//                        // the header block, if there is only a LF character,
//                        // prefix it with a CR.  The end of the HTTP header block
//                        // is denoted by an empty line (i.e. CR LF).
//                        String sLine;
//                        int	iIndex = 0;
//                        int iEoL = sResponse.indexOf( sLF, iIndex) + 1;
//                        
//                        do
//                        {
//                            sLine = getResponseLine( sResponse, sCRLF, iIndex, iEoL);
//                            
//                            sModifiedResponse += sLine;
//    
//                            // Get next line.
//                            iIndex = iEoL;
//    
//                            iEoL = sResponse.indexOf( sLF, iIndex) + 1;
//                        } while( iEoL > 0 && !sLine.equals( sCRLF));
//    
//                        // Immediately after the HTTP header block should be the
//                        // first chunk_size.  All chunk_sizes are in hex. A chunk
//                        // size gives the size in bytes of the data that follows
//                        // the value (i.e. CR LF 2 0 0 0 CR LF <---Data---> CR LF)
//                        // but any number of CR may be missing and need to be
//                        // accounted for if the response file is to be processed
//                        // correctly.
//                        // Do some 'first time' processing to initialise the loop
//                        // that will process the HTTP message until the chunk size
//                        // is zero (signifying the end of the message).
//                        sLine = getResponseLine(sResponse, sCRLF, iIndex, iEoL);
//    
//                        sModifiedResponse += sLine;
//    
//                        iIndex = iEoL;
//    
//                        // Evaluate chunk_size value.
//                        int iChunkSize = Integer.parseInt( sLine.trim(), 16);
//    
//                        // On entry to the loop, iChunkSize is the size of the data
//                        // chunk and iIndex is the current location that is being
//                        // processed.
//                        do
//                        {
//    	                    int	iChunkDataBlockBegin = iIndex;
//    	                    int	iChunkDataBlockEnd = iIndex + iChunkSize;
//    	                    int	iResponseSize = sResponse.length();
//    
//    	                    // If the chunk data block end is greater than the size
//    	                    // of the file, then the size of the chunk is incorrect.
//    	                    // If '###' was used, then the size of the chunk is
//    	                    // incorrectly calculated to include the chunk size in
//    	                    // the chunk length. 
//    	                    if( iChunkDataBlockEnd > iResponseSize)
//    	                    {
//    	                        if( iChunkDataBlockEnd - iResponseSize > 1)
//    	                        {
//    	                            System.out.println( "Warning - The chunk size is greater than the file size by " + (iChunkDataBlockEnd - iResponseSize) + " bytes.");
//    	                        }
//    	                        
//    	                        iChunkDataBlockEnd = sResponse.lastIndexOf( "0") - 1;
//    	                        iChunkSize = iChunkDataBlockEnd - iIndex;
//    	                    }
//    	                    
//    	                    String sChunkDataBlock = sResponse.substring( iChunkDataBlockBegin, iChunkDataBlockEnd);
//    
//    	                    iIndex += iChunkSize;
//    
//    	                    // Check that offset from current position + chunk_size is
//    	                    // another chunk_size.
//                            iEoL = sResponse.indexOf( sLF, iIndex) + 1;
//    
//                            if( iEoL == 0)
//                            {
//                                // There are no more LF's in the file.  This is
//                                // probably because there is no LF at the end of
//                                // the file.  Assume so and make sLine = "0".
//    	                        System.out.println( "Warning - The response file chunk sizes appear to be wrong.");
//    	                        
//    	                        sLine = "";
//                            }
//                            else
//                            {
//                                // Check if the chunk data size is bigger than
//                                // expected.  If it is, then count up the number
//                                // of CR LF in the data chunk and iff this number
//                                // matches the difference is actual and expected
//                                // chunk size, then remove all CR within the data
//                                // chunk.
//                                if( iEoL - iIndex > 2)
//                                {
//                                    int	iLFCount = 0;
//                                    int	iLF = 0;
//                                    
//                                    while( (iLF = sChunkDataBlock.indexOf( sLF, iLF) + 1) > 0)
//                                    {
//                                        iLFCount++;
//                                    }
//                                    
//                                    if( iLFCount == (iEoL - iIndex - 2))
//                                    {
//                                        System.out.println( "Warning - chunk data size is larger than expected.  Additional CR may have been added to LF within data chunk.  Fixed.");
//                                        
//                                        sChunkDataBlock = sChunkDataBlock.replaceAll( sCRLF, sLF);
//                                    }
//                                    else
//                                    {
//                                        System.out.println( "Warning - chunk data size is larger than expected.  Additional CR may have been added to LF within data chunk.  Unable to fix.");
//                                    }
//                                }
//                                
//                                sLine = getResponseLine( sResponse, sCRLF, iIndex, iEoL);
//    
//                                sChunkDataBlock += sLine;
//    
//    	                        // Get next line.
//    	                        iIndex = iEoL;
//    	
//    	                        iEoL = sResponse.indexOf( sLF, iIndex) + 1;
//    	
//    	                        if( iEoL == 0)
//    	                        {
//    	                            // There are no more LF's in the file.  This is
//    	                            // probably because there is no LF at the end of
//    	                            // the file.  Assume so and make sLine = "0".
//    		                        System.out.println( "Warning - The response file does not end with a LF.");
//    	                            
//    	                            sLine = "0" + sLF;
//    	                        }
//    	                        else
//    	                        {
//    	                            sLine = getResponseLine( sResponse, sCRLF, iIndex, iEoL);
//    	                        }
//    	                        
//    		                    if( !isStringAHexNumber( sLine.trim()))
//    		                    {
//    		                        // Next chunk_size not found at position.  Count the
//    		                        // number of LF's in the block.  Check if when this
//    		                        // number * 2 is added to the offset that the pointer
//    		                        // now points to the next chunk_size.
//    		                        System.out.println( "Error - The next chunk_size was not found in the correct position.  Check that the contents of the chunked data between " + iChunkDataBlockBegin + " and " + iChunkDataBlockEnd + " is correct.");
//    		                    }
//                            }
//    
//    	                    sModifiedResponse += sChunkDataBlock;
//    	                    sModifiedResponse += sLine;
//    
//    	                    iIndex = iEoL;
//    	                    
//    	                    // Evaluate chunk_size value.
//    	                    if( sLine.trim().length() > 0 && isStringAHexNumber( sLine.trim()))
//    	                    {
//    	                        iChunkSize = Integer.parseInt( sLine.trim(), 16);
//    	                    }
//    	                    else
//    	                    {
//    	                        System.out.println( "Warning - The response file does not appear to end with a 0 and LF characters.");
//    	                        
//    	                        iChunkSize = 0;
//    	                    }
//                        } while( iChunkSize > 0);
//    
//                        // Now put it back into the responses
//                        responses[i] = new Response(sModifiedResponse);
//                        
//                	}
//                	else
//                	{
//                        if (System.getProperty("os.name").toLowerCase( ).startsWith("windows"))
//                        {
//                            System.out
//                                    .println("Windows operating system - not converting crlf's");
//                        }
//                        else
//                        {
//                            String request=new String(responses[i].getMessage());
//    
//                            // check the last two digits for CRLF - if they
//                            // are LFLF
//                            // then this is wrong
//                            // e.g. 0a 0a converts to 0d0a 0d0a
//                            // I'm doing it using a matcher because this
//                            // could get
//                            // complicated !
//                            Pattern pattern=Pattern.compile("\n");
//                            Matcher matcher=pattern.matcher(request);
//                            StringBuffer stringBuffer=new StringBuffer( );
//    
//                            while (matcher.find( ))
//                            {
//                                char[] tmpStr=matcher.group( ).toCharArray( );
//                                matcher.appendReplacement(stringBuffer, "\r\n");
//                            }
//                            
//                            matcher.appendTail(stringBuffer);
//                            
//                            // Now put it back into the responses
//                            responses[i]=new Response(stringBuffer.toString( ));
//                        }
//                    }
//                }
//            }
//    
//            // Irrespective of platform ensure that all responses end with \r\n\r\n
//            for(int i=0; i<responses.length; i++)
//            {
//                if (responses[i]!=null)
//                {
//                    String request=new String(responses[i].getMessage());
//                    // this pattern looks for any chars then any non whitespace followed directly by the EOF 
//                    Pattern pattern=Pattern.compile("(.*)(\\s)*$");
//                    Matcher matcher=pattern.matcher(request);
//                    StringBuffer stringBuffer=new StringBuffer("");
//                    // We should only find one occurence (if any) of the sequence
//                    if(matcher.find())
//                    {
//                        System.out.println( "MATCHED");
//                        // and replace them with the proper sentence !
//                        matcher.appendReplacement(stringBuffer, "$1\r\n\r\n");
//                    }
//                    else
//                    {
//                        System.out.println( "NOT MATCHED");
//                        // We did not find the sequence so just tack on the grouping we need.
//                        stringBuffer.append(request);
//                        stringBuffer.append("\r\n\r\n");
//                        
//                    }
//                    // Now put it back into the responses
//                    responses[i]=new Response(stringBuffer.toString( ));
//                }
//            }
//            
//    //        System.out.println( "*******************************************");
//    //        System.out.println( responses[1]);
//        }

    /**
     * @param sResponse
     * @param sCRLF
     * @param iIndex
     * @param iEOL
     */
//    private static String getResponseLine(String sResponse, String sCRLF, int iIndex, int iEOL)
//    {
//        String sLine = sResponse.substring( iIndex, iEOL);
//
//        if( (!sLine.endsWith( sCRLF)) && (iEOL > iIndex))
//        {
//            sLine = sResponse.substring( iIndex, iEOL - 1) + sCRLF;
//        }
//        
//        return sLine;
//    }
    
//    private static boolean isStringAHexNumber( String sValue)
//    {
//        boolean bOutcome = true;
//        String sValidChars = "0123456789ABCDEFabcdef";
//        int iIndex = 0;
//        
//        while( bOutcome && iIndex < sValue.length())
//        {
//            if( sValidChars.indexOf( sValue.substring( iIndex, iIndex + 1)) == -1)
//            {
//                bOutcome = false;
//            }
//            else
//            {
//                iIndex++;
//            }
//        }
//        
//        return bOutcome;
//    }
    
    public void setClosedConnection(boolean closedConnection)
    {
        this.closedConnection = closedConnection;
    }
}