/*
 * Copyright 2001-2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.geronimo.ews.ws4j2ee.context.impl;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import org.apache.geronimo.ews.ws4j2ee.context.InputOutputFile;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author hemapani@opensource.lk
 */
public class InputOutputFileImpl implements InputOutputFile {
    private InputStream instream;
    private String fileName;
    private OutputStream outstream;

    public InputOutputFileImpl(InputStream instream) {
        this.instream = instream;
    }

    public InputOutputFileImpl(String fileName) throws GenerationFault {
        this.fileName = fileName;
    }

    public InputOutputFileImpl(String fileName, InputStream instream) {
        this.instream = instream;
        this.fileName = fileName;
    }

    public String fileName() {
        if (fileName == null)
            throw new UnsupportedOperationException(
                "asking for file name when input/output is a stream");
        return fileName;
    }

    public InputStream getInputStream() throws GenerationFault {
        try {
            if (instream == null) {
                File file = new File(fileName);
                this.instream = new FileInputStream(file);
            }
            return instream;
        } catch (FileNotFoundException e) {
            throw GenerationFault.createGenerationFault(e);
        }
    }

    public OutputStream getOutStream() throws GenerationFault {
        try {
            if (outstream == null) {
                File file = new File(fileName);
                File parent = file.getParentFile();
                if (!parent.exists())
                    parent.mkdirs();
                this.outstream = new FileOutputStream(file);
            }
            return outstream;
        } catch (FileNotFoundException e) {
            throw GenerationFault.createGenerationFault(e);
        }
    }
    /* (non-Javadoc)
     * @see java.lang.Object#finalize()
     */
    protected void finalize() throws Throwable {
        try {
            if (outstream != null)
                outstream.close();
            if (instream != null) {
                instream.close();
            }
        } catch (IOException e) {
        }
        super.finalize();
    }

}
