/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *    Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

package org.apache.axismora.server;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

import org.apache.axismora.Constants;
import org.apache.axismora.engine.AxisEngine;

import org.apache.axis.components.logger.LogFactory;
import org.apache.commons.logging.Log;
/**
 * This is a standalone axis Server, this is not intended for used in havy loads. Under
 * Certian Stressful conditons it would failed eventually. It is for the conveniance of testing 
 * debuging ect.
 * 
 * The Server only parse the SOAPAction parameter for the time been.
 * Other headers should be process to pass the username , password ect to the SOAPEngine.    
 * @author Srinath(hemapani@opensource.lk)
 */
public class SimpleAxisServer {
    Log log = LogFactory.getLog(SimpleAxisServer.class.getName());

    private Socket clientSocket;
    private ServerSocket serverSocket;
    private AxisEngine engine;

    public SimpleAxisServer(int port) throws Exception {
        this.engine = new AxisEngine(Constants.SERVER_CONFIG_FILE);
        serverSocket = null;
        try {
            serverSocket = new ServerSocket(port);
            System.out.println("sever listning in port " + port + " .....................");
        } catch (IOException e) {
            System.err.println("Could not listen on port: " + port + ".");
            System.exit(1);
        }
    }

    public void start() {
        try {
            while (true) {
                clientSocket = serverSocket.accept();
                Processor p = new Processor(clientSocket, engine);
                p.start();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public class Processor extends Thread {
        private InputStream in;
        private OutputStream out;
        private Socket clientSocket;
        private AxisEngine engine;

        public Processor(Socket clientSocket, AxisEngine engine) {
            this.clientSocket = clientSocket;
            this.engine = engine;
        }

        public void run() {
            try {

                this.out = clientSocket.getOutputStream();
                this.in = clientSocket.getInputStream();

                /* BufferedReader reader = new BufferedReader(new InputStreamReader(in));
                 String soapAction="";
                 boolean pass = true;
                 String line;
                 int index=0;
                 while(pass){
                     System.out.println("test");
                
                     line = reader.readLine();
                     System.out.println(line);
                     if(line == null) pass = false;
                     if(line.indexOf("SOAPAction")>=0){
                         index =line.indexOf("\"");
                         if((index!=-1)){
                           soapAction = line.substring(index+1,line.length()-1);
                           pass = false;
                         }
                     }
                 } */

                StringBuffer buff = new StringBuffer();
                String soapAction = "";

                int inC;

                while (((inC = in.read()) != -1) && (((char) inC) != '<')) {
                    if (((char) (inC)) == '\n')
                        buff = buff.delete(0, buff.length() - 1);
                    else if (
                        ((char) (inC)) == ':' && "SOAPAction".equals(buff.toString().trim())) {
                        buff = buff.delete(1, buff.length());
                        while (((inC = in.read()) != -1) && ((char) inC) != '\n') {
                            buff.append((char) inC);
                        }
                        if (inC != -1) {
                            String temp = buff.toString().trim();
                            soapAction = temp.substring(1, temp.length() - 1);
                        }
                        while (((inC = in.read()) != -1) && ((char) inC) != '>') {
                        }
                        break;
                    } else
                        buff.append((char) inC);
                }

                out.write(
                    "HTTP/1.1 200 OK\nContent-Type: text/xml; charset=\"utf-8\"\n\n".getBytes());

                this.engine.process(soapAction.toString(), in, out, null, null, null, null);
                out.write('\n');
                this.out.close();
                this.in.close();
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    protected void stop() throws IOException {
        serverSocket.close();
    }

    public static void main(String[] args) throws Exception {
        SimpleAxisServer server = new SimpleAxisServer(4444);
        server.start();
    }
}