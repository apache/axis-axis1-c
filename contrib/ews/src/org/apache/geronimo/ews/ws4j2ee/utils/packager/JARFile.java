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

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;
import java.util.jar.JarOutputStream;
import java.util.zip.ZipEntry;

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * create a jar file with given set of jar entries.
 * It works like
 * <ol>
 * <li>if no extension given the .class is added to the extenstion</li>
 * <li>then file with the given name is tried</li>
 * <li>if that failed the name is tired to load as a stream form the
 * class path</li>
 * </ol>
 * 
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class JARFile {
    private HashMap jarEntries;
    private File path;

    public JARFile(String path, HashMap entries) {
        jarEntries = entries;
        this.path = new File(path);
    }

    public JARFile(File path) {
        this.path = path;
        jarEntries = new HashMap();
    }

    public void addJarFile(String jarFile) throws GenerationFault {
        try {
            JarFile file = new JarFile(jarFile);
            Enumeration e = file.entries();
            while (e.hasMoreElements()) {
                ZipEntry entry = (ZipEntry) e.nextElement();
                JARFileEntry newEntry =
                    new JARFileEntry(
                        entry.getName(),
                        file.getInputStream(entry));
                this.jarEntries.put(entry.getName(), newEntry);
            }
        } catch (IOException e) {
            e.printStackTrace();
            throw GenerationFault.createGenerationFault(e);
        }
    }

    public void addJarEntry(JARFileEntry entry) {
        this.jarEntries.put(entry.getJarEntry().getName(), entry);
    }

    public void createNewJarFile() throws IOException {
        if (!path.exists())
            path.createNewFile();

        System.out.println("creating " + path.getAbsolutePath() + ".......");

        BufferedOutputStream bo =
            new BufferedOutputStream(new FileOutputStream(path));
        JarOutputStream jo = new JarOutputStream(bo);
        Iterator it = jarEntries.values().iterator();
        for (; it.hasNext();) {

            JARFileEntry jarentry = (JARFileEntry) it.next();
            System.out.println(jarentry.getJarEntry().getName() + " adding ..");
            InputStream instream = null;
            //            File input = new File(jarentry.getSource());

            //
            //            if (input.exists())
            //                instream = new FileInputStream(input);
            //            else
            //                instream = JARFile.class.getClassLoader()
            //                        .getResourceAsStream(jarentry.getSource());
            instream = jarentry.getSource();

            BufferedInputStream source = new BufferedInputStream(instream);

            JarEntry je = jarentry.getJarEntry();
            jo.putNextEntry(je);

            byte[] buf = new byte[1024];
            int anz;

            while ((anz = source.read(buf)) != -1) {
                jo.write(buf, 0, anz);
            }
            jo.flush();
            jo.closeEntry();
            instream.close();
            source.close();
        }
        jo.close();
        bo.close();
    }

}
