/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2004 The Apache Software Foundation.  All rights
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
 *        Apache Software Foundation (http://www.apache.org/)."
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

package org.apache.geronimo.ews.ws4j2ee.utils.packager;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * <p>Package the ws4j2ee genarated classes. For the time been a file
 * with the list of classes should be given as input and the compilation of the
 * class should be done by the user. Let us see what is the best way.</p>
 * 
 * @author Srinath Perera(hemapani@opensorce.lk)
 */
public class Packager {
    public static String JARCONF_FILE = "jarinfo.txt";
    private JARFile ejbjar = null;
    private JARFile jaxrpcjar = null;

    public Packager() {
        ejbjar = new JARFile(new File("x-ejb.jar"));
        jaxrpcjar = new JARFile(new File("x-jaxrpc.jar"));
		InputStream in = Packager.class.getClassLoader()
					.getResourceAsStream("org.apache.axis.deployment.wsdd.Provider");
        JARFileEntry jentry1 
        	= new JARFileEntry("META-INF/services/org.apache.axis.deployment.wsdd.Provider",in);
		in = Packager.class.getClassLoader()
					.getResourceAsStream("org/apache/axis/deployment/wsdd/WSDDJavaJ2EEProvider.class");
        JARFileEntry jentry2 = new JARFileEntry("org.apache.axis.deployment.wsdd.WSDDJavaJ2EEProvider.class",in);
		in = Packager.class.getClassLoader()
					.getResourceAsStream("org/apache/axis/J2EEProvider.class");
        JARFileEntry jentry3 = new JARFileEntry("org.apache.axis.J2EEProvider.class",in);

        jaxrpcjar.addJarEntry(jentry1);
        jaxrpcjar.addJarEntry(jentry2);
        jaxrpcjar.addJarEntry(jentry3);
    }

//    public void loadFromDir(String ejbDir,
//                            String jaxrpcDir) {
//        //get EJBClass files							
//        FileSerachAgent searcher = new FileSerachAgent(ejbDir);
//        searcher.addAcceptedFile(".class");
//        ArrayList ejbClassFiles = searcher.serach();
//
//        for (int i = 0; i < ejbClassFiles.size(); i++) {
//            String filename = (String) ejbClassFiles.get(i);
//            JARFileEntry jentry =
//                    new JARFileEntry(filename, getOutClassFileName(filename, ejbDir));
//            ejbjar.addJarEntry(jentry);
//            jaxrpcjar.addJarEntry(jentry);
//        }
//
//        searcher = new FileSerachAgent(ejbDir);
//        searcher.addRejectedFile(".class");
//        searcher.setDefaultForUnspsecified(true);
//        ArrayList ejbDDFiles = searcher.serach();
//
//        for (int i = 0; i < ejbDDFiles.size(); i++) {
//            String filename = (String) ejbDDFiles.get(i);
//            JARFileEntry jentry =
//                    new JARFileEntry(filename, getOutDDName(filename));
//            ejbjar.addJarEntry(jentry);
//        }
//
//        searcher = new FileSerachAgent(jaxrpcDir);
//        searcher.addAcceptedFile(".class");
//        ArrayList jaxrpcClassFiles = searcher.serach();
//
//        for (int i = 0; i < jaxrpcClassFiles.size(); i++) {
//            String filename = (String) jaxrpcClassFiles.get(i);
//            JARFileEntry jentry =
//                    new JARFileEntry(filename, getOutClassFileName(filename, jaxrpcDir));
//            jaxrpcjar.addJarEntry(jentry);
//            ejbjar.addJarEntry(jentry);
//        }
//
//        searcher = new FileSerachAgent(jaxrpcDir);
//        searcher.addRejectedFile(".class");
//        searcher.setDefaultForUnspsecified(true);
//        ArrayList jaxrpcDDFiles = searcher.serach();
//
//        for (int i = 0; i < jaxrpcDDFiles.size(); i++) {
//            String filename = (String) jaxrpcDDFiles.get(i);
//            JARFileEntry jentry =
//                    new JARFileEntry(filename, getOutDDName(filename));
//            jaxrpcjar.addJarEntry(jentry);
//        }
//    }

//    public void loadFromCL(String[] args) {
//        try {
//            BufferedReader reader = new BufferedReader(new FileReader(JARCONF_FILE));
//            String line = null;
//            String inputfilename = null;
//            String outfilename = null;
//            InputStream inputStream = null;
//
//            for (int i = 0; i < args.length; i++) {
//                line = args[i];
//                if (line.length() < 2)
//                    continue;
//                if (!(line.endsWith(".xml") || line.endsWith(".wsdl") || line.endsWith(".class"))) {
//                    inputfilename = (line.substring(line.indexOf(':') + 1)).replace('.', '/') + ".class";
//                    outfilename = (line.substring(line.indexOf(':') + 1)).replace('.', '/') + ".class";
//                } else {
//                    inputfilename = (line.substring(line.indexOf(':') + 1));
//                    outfilename = "META-INF/" + (line.substring(line.indexOf(':') + 1));
//                }
//
//                JARFileEntry jentry = new JARFileEntry(outfilename, inputfilename);
//
//                if (line.startsWith("ejb:")) {
//                    ejbjar.addJarEntry(jentry);
//                } else if (line.startsWith("jaxrpc:")) {
//                    jaxrpcjar.addJarEntry(jentry);
//                }
//            }
//        } catch (FileNotFoundException e) {
//            throw new UnrecoverableGenarationFault(e.getMessage());
//        }
//    }
//
//    private void loadFromFile() {
//        try {
//            BufferedReader reader = new BufferedReader(new FileReader(JARCONF_FILE));
//            String line = null;
//            String inputfilename = null;
//            String outfilename = null;
//            InputStream inputStream = null;
//
//            while ((line = reader.readLine()) != null) {
//                if (line.length() < 2)
//                    continue;
//                if (!(line.endsWith(".xml") || line.endsWith(".wsdl") || line.endsWith(".class"))) {
//                    inputfilename = (line.substring(line.indexOf(':') + 1)).replace('.', '/') + ".class";
//                    outfilename = (line.substring(line.indexOf(':') + 1)).replace('.', '/') + ".class";
//                } else {
//                    inputfilename = (line.substring(line.indexOf(':') + 1));
//                    outfilename = "META-INF/" + (line.substring(line.indexOf(':') + 1));
//                }
//
//                File file = new File(inputfilename);
//                if (file.exists())
//                    inputStream = new FileInputStream(file);
//                else
//                    inputStream = Packager.class.getClassLoader().getResourceAsStream(inputfilename);
//
//                JARFileEntry jentry = new JARFileEntry(outfilename, inputfilename);
//
//                if (line.startsWith("ejb:")) {
//                    ejbjar.addJarEntry(jentry);
//                } else if (line.startsWith("jaxrpc:")) {
//                    jaxrpcjar.addJarEntry(jentry);
//                }
//            }
//
//        } catch (FileNotFoundException e) {
//            throw new UnrecoverableGenarationFault(e.getMessage());
//        } catch (IOException e) {
//            throw new UnrecoverableGenarationFault(e.getMessage());
//        }
//
//    }
//
//    public void createNewJarFile() throws IOException {
//        ejbjar.createNewJarFile();
//        jaxrpcjar.createNewJarFile();
//    }
//
//    private String getOutClassFileName(String filename, String dir) {
//        String out = filename.substring(dir.length());
//        if (out.startsWith("/"))
//            out = out.substring(1);
//        return out;
//    }
//
//    private String getOutDDName(String filename) {
//        String out = "META-INF/" + filename.substring(filename.lastIndexOf("/"));
//        return out;
//    }
//
    public static void main(String[] args) {
//        Packager packager = new Packager();
//		if(args.length > 0)
//			packager.loadFromCL(args);
//		else
//			packager.loadFromFile();
//		packager.createNewJarFile();
//        packager.loadFromDir();	
//		
//		File file = new File(JARCONF_FILE);
//		if(file.exists()){
//			file.delete();
//		}
        try {
            JARFile jfile = new JARFile(new File(args[0]));
            for(int i = 1;i<args.length;i++){
            	jfile.addJarFile(args[i]);
            	System.out.println(args[i]);
            }
            jfile.createNewJarFile();
            
        } catch (GenerationFault e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
