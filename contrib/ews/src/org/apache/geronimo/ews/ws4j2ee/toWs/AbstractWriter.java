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

package org.apache.geronimo.ews.ws4j2ee.toWs;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;


import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;

/**
 * <p>This is a conveniance class to wite the Writers</p>
 * @author Srinath Perera(hemapani@opensource.lk)
 */

public abstract class AbstractWriter implements Writer {
    /**
     * <p>this parameter act as a mediator, It contains all the information
     * this will be passed to the each writer. This will make sure
     * even if the information that should passed around it will keep
     * method signatures intact.</p>
     */
	protected static Log log =
				LogFactory.getLog(AbstractWriter.class.getName());
    protected J2EEWebServiceContext j2eewscontext;
    /* this is used to write the file */
    protected PrintWriter out;
    private String fileName;
    private boolean verbose;
    
	public AbstractWriter(J2EEWebServiceContext j2eewscontext,String filename)
			throws GenerationFault {
		this.j2eewscontext = j2eewscontext;
		this.fileName = filename;
		verbose = j2eewscontext.getMiscInfo().isVerbose();
	}
	
    protected abstract void writeCode() throws GenerationFault;
    protected final void prepare()throws GenerationFault{
		try {
			File file = new File(this.fileName);
			if(verbose){
				log.info("genarating ... " + file.getAbsolutePath());
			}
			if (!isOverWrite() && file.exists()) {
				out = null;
				if(verbose){
					log.info("the file already exists .. tool will not overwrite it ");
				}

			} else {
				File parent = file.getParentFile();
				if (parent != null)
					parent.mkdirs();
				file.createNewFile();
				out = new PrintWriter(new FileWriter(file, false));
			}

		} catch (IOException e) {
			throw GenerationFault.createGenerationFault(e);
		}
    }
	protected final void cleanUp()throws GenerationFault{
		if(out != null)
			out.close();
	}
    
    protected boolean isOverWrite(){
    	return true;
    }
    
    public final void write() throws GenerationFault {
    	try{
			prepare();
			writeCode();
    	}finally{
			cleanUp();    	
    	}
    }
}
