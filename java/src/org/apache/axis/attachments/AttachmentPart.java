/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
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

package org.apache.axis.attachments;

import org.apache.axis.Part;
import org.apache.axis.Message;
import org.apache.log4j.Category;

import javax.activation.DataHandler;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.IOException;

/**
 * An AttachmentPart contains attachment data along with MIME
 * headers, and implements the standard Part API.
 * <p>
 * It provides access to attachment content via
 * javax.activation.DataHandlers, so it will not be built if Axis
 * is built without activation.jar, and core Axis code must not
 * import it (lest it also become dependent on axis.jar).
 * Attachment-aware code, of course, is no problem.
 * 
 * @author Rob Jellinghaus (robj@unrealities.com)
 * @author Rick Rineholt (rineholt@us.ibm.com)
 */
public class AttachmentPart extends Part {
    static Category category = Category.getInstance(Message.class.getName());
    
    /**
     * Do not call this directly!  This should only be called by the
     * AttachmentsImpl object.
     */ 
    public AttachmentPart (Message parent) {
        super(parent);
    }

    /**
     * TODO: everything!
     */ 
    public int getContentLength() {
        return 0;
    }

    /**
     * TODO: everything!
     */ 
    public String getContentType() {
        return null;
    }

    /**
     * TODO: everything!
     */ 
    public int getSize() {
        return 0;
    }

    /**
     * TODO: everything!
     */ 
    public void writeTo(OutputStream out) throws IOException {
    }
}

