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
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;

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

    public static void main(String[] args) {
        try {
            JARFile jfile = new JARFile(new File(args[0]));
            for(int i = 1;i<args.length;i++){
            	if(args[i].endsWith(".jar")){
					jfile.addJarFile(args[i]);            	
            	}else{
            		File file = new File(args[i]);
            		if(file.isDirectory()){
            			ArrayList list = new ArrayList();
						getSourceFiles(list,file);
						for(int j = 1;j<list.size();j++){
							File temp = new File((String)list.get(i));
							JARFileEntry newEntry =
								new JARFileEntry(temp.getName(),
													new FileInputStream(temp));
							jfile.addJarEntry(newEntry);
						}	
            		}
            	}

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
	private static void getSourceFiles(ArrayList list, File location) {
		String[] dirs = location.list();
		if (dirs == null)
			return;
		for (int i = 0; i < dirs.length; i++) {
			String filename = location.getAbsolutePath() + "/" + dirs[i];
			File file = new File(filename);
			if (file.isFile()) {
				list.add(filename);
			} else {
					getSourceFiles(list, new File(filename));
			}

		}
	}

}
