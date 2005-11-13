//Copyright 2003-2004 The Apache Software Foundation.
//(c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License./*
package org.apache.test;

import java.io.BufferedWriter;
import java.io.IOException;

/**
 * @author hawkeye
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class ResponseSender implements Runnable
{
    private Response response;
    private BufferedWriter writer;
    // we need to keep a hold of the parent that created us so we can tell them if we closed the connection
    private MockServerThread parent;
    
    
    ResponseSender (Response responseToSend, BufferedWriter writerToClient, MockServerThread mockServerThread)
    {
//        System.out.println( "NEW RESPONDER");
        response = responseToSend;
        writer = writerToClient;
        parent = mockServerThread;
    }
    

    /* (non-Javadoc)
     * @see java.lang.Runnable#run()
     */
    public void run( )
    {
        // send the response message back to the client !
        try
        {
//            System.out.println( "nulls? "+response+", "+writer+", "+response.length);
            // send it in chunks
//            int chunkSize=300;
//            int lastPosition=0;
//            for(int i=0; i<response.length; i+=chunkSize)
//            {
//                System.out.println( "HERE ");
//               writer.write(response, lastPosition, chunkSize);
            
            writer.write(response.getMessage());
            writer.flush();
//               lastPosition+=chunkSize;
//               System.out.println( "HERE "+lastPosition);
//            }
        }
        catch(IOException exception)
        {
            exception.printStackTrace(System.err);
        }
        System.out.println( "ResponseSender: Sent response To Client");
        
        if(response.hasCloseConnectionHeader())
        {
            // Then we need to close the connection
            System.out.println( "ResponseSender: Closing connection now");
            parent.setClosedConnection(true);
            try
            {
                writer.close();
            }
            catch(IOException exception)
            {
                exception.printStackTrace(System.err);
            }
        }
    }

}

