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
import java.util.ArrayList;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class FileSerachAgent {
    private ArrayList acceptedFiles;
    private ArrayList rejectedFiles;
    private boolean selectAll;
    private String startingDir = ".";
    private boolean recursive = true;

    //this says what to do with the files that are not in 
    //acccpeted or rejected lists
    private boolean defaultForUnspsecified = false;

    public FileSerachAgent(String startingDir) {
        this.startingDir = startingDir;
        acceptedFiles = new ArrayList();
        rejectedFiles = new ArrayList();
    }

    /**
     * add file to be accepted
     * 
     * @param extension e.g. ".class"
     */
    public void addAcceptedFile(String extension) {
        acceptedFiles.add(extension);
    }

    public void addRejectedFile(String extension) {
        rejectedFiles.add(extension);
    }

    /**
     * @return 
     */
    public boolean isSelectAll() {
        return selectAll;
    }

    /**
     * @param b 
     */
    public void setSelectAll(boolean b) {
        selectAll = b;
    }

    public ArrayList serach() {
        ArrayList result = new ArrayList();
        getSourceFiles(result, new File(startingDir));
        return result;
    }

    /**
     * fill the supplied vector with the selected files
     * 
     * @param list     
     * @param location 
     */
    private void getSourceFiles(ArrayList list, File location) {

        String[] dirs = location.list();
        if (dirs == null)
            return;

        for (int i = 0; i < dirs.length; i++) {
            String filename = location.getAbsolutePath() + "/" + dirs[i];
            File file = new File(filename);
            if (file.isFile()) {
                if (!isAcceptedFile(filename))
                    continue;
                list.add(filename);
            } else {
                if (recursive)
                    getSourceFiles(list, new File(filename));
            }

        }
    }

    private boolean isAcceptedFile(String filename) {
        if (!(new File(filename)).isFile())
            return true;
        if (selectAll)
            return true;
        for (int i = 0; i < rejectedFiles.size(); i++) {
            if (filename.endsWith((String) rejectedFiles.get(i)))
                return false;
        }
        for (int i = 0; i < acceptedFiles.size(); i++) {
            if (filename.endsWith((String) acceptedFiles.get(i)))
                return true;
        }
        return defaultForUnspsecified;
    }

    /**
     * @return 
     */
    public boolean isDefaultForUnspsecified() {
        return defaultForUnspsecified;
    }

    /**
     * @param b 
     */
    public void setDefaultForUnspsecified(boolean b) {
        defaultForUnspsecified = b;
    }

    /**
     * @return 
     */
    public boolean isRecursive() {
        return recursive;
    }

    /**
     * @param b 
     */
    public void setRecursive(boolean b) {
        recursive = b;
    }

}
