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

package org.apache.geronimo.ews.ws4j2ee.utils.packager;

import java.io.InputStream;
import java.util.jar.JarEntry;

/**
 * <p>reprsent the information about a entry added to the JAR file.
 * the Entry reprsent a Jar entry and the the source represent the file
 * going to be added to the jar file.</p>
 * 
 * @author Srinath perera(hemapani@opensource.lk)
 */
public class JARFileEntry {
    private JarEntry jarEntry;
    private InputStream source;

    public JARFileEntry(String jarfilePath, InputStream source) {
        this.jarEntry = new JarEntry(jarfilePath);
        this.source = source;
        if (this.source == null || this.jarEntry == null)
            throw new RuntimeException("source or jar entry can't be null");
    }

    /**
     * @return 
     */
    public JarEntry getJarEntry() {
        return jarEntry;
    }

    /**
     * @return 
     */
    public InputStream getSource() {
        return source;
    }

}
