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

package org.apache.axismora.encoding.ser;

import java.io.IOException;
import java.io.OutputStream;
import java.io.Writer;

/**
 * <p>This is a enhanced BufferedWriter. But can both write bytes and the 
 * char's</p>
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class EnhancedWriter extends Writer{
	private static final int BUF_LENGHTH = 8*1024;
	private OutputStream writer; 
	private byte[] buffer = new byte[BUF_LENGHTH];
	private int index = 0; //index the position next byte to be written
	
	
		
	public EnhancedWriter(OutputStream writer){
		this.writer = writer;
	}
	
    public void close() throws IOException {
		writer.write(buffer,0,index);
		writer.close();
    }

    /* (non-Javadoc)
     * @see java.io.Writer#flush()
     */
    public void flush() throws IOException {
		writer.write(buffer,0,index);
		writer.flush();
		index = 0;
	}

    /* (non-Javadoc)
     * @see java.io.Writer#write(char[], int, int)
     */
    public void write(char[] cbuf, int off, int len) throws IOException {
		byte[] bval = String.valueOf(cbuf,off,len).getBytes();
		int length = bval.length;
		for(int j = 0;j<length;j++){
			buffer[index] = bval[j];
			index++;
			if(index == BUF_LENGHTH){
				writer.write(buffer);
				index = 0;
			}
		}	
    }

	public void write(byte[] subBuf, int off, int len) throws IOException {
		int subBufLen = len;
		if(subBufLen + index < BUF_LENGHTH){
			System.arraycopy(subBuf, off,buffer,index ,subBufLen) ;
			index = index + subBufLen;
		}else{
			//add one as the index is not written
			int towrite = BUF_LENGHTH - index; 
			//copy till the buffer fill
			System.arraycopy(subBuf, off,buffer,index ,towrite) ; 
			//write the buffer
			writer.write(buffer);
			//write the what is left
			int lefttowrite =  subBufLen - towrite;
			System.arraycopy(subBuf, towrite,buffer,0,lefttowrite) ;
			index = lefttowrite;
		}
	}
	
	public void write(byte[] subBuf) throws IOException {
		int subBufLen = subBuf.length;
		if(subBufLen + index < BUF_LENGHTH){
			System.arraycopy(subBuf, 0,buffer,index ,subBufLen) ;
			index = index + subBufLen;
		}else{
			//add one as the index is not written
			int towrite = BUF_LENGHTH - index; 
			//copy till the buffer fill
			System.arraycopy(subBuf, 0,buffer,index ,towrite) ; 
			//write the buffer
			writer.write(buffer);
			//write the what is left
			int lefttowrite =  subBufLen - towrite;
			System.arraycopy(subBuf, towrite,buffer,0,lefttowrite) ;
			index = lefttowrite;
		}
	}



    /* (non-Javadoc)
     * @see java.io.Writer#write(char[])
     */
    public void write(char[] cbuf) throws IOException {
		write(cbuf,0,cbuf.length);
    }

    /* (non-Javadoc)
     * @see java.io.Writer#write(int)
     */
    public void write(int c) throws IOException {
		buffer[index] = (byte)c;
		index++;
    }

    /**
     * @see java.io.Writer#write(java.lang.String, int, int)
     */
    public void write(String str, int off, int len) throws IOException {
    	//this would used rarely the integirty of the code 
    	//more valuble
		write(str.substring(off,off + len));
     }

    /* (non-Javadoc)
     * @see java.io.Writer#write(java.lang.String)
     */
    public void write(String str) throws IOException {
		byte[] subBuf = str.getBytes();
		int subBufLen = subBuf.length;
		if(subBufLen + index < BUF_LENGHTH){
			System.arraycopy(subBuf, 0,buffer,index ,subBufLen) ;
			index = index + subBufLen;
		}else{
			//add one as the index is not written
			int towrite = BUF_LENGHTH - index; 
			//copy till the buffer fill
			System.arraycopy(subBuf, 0,buffer,index ,towrite) ; 
			//write the buffer
			writer.write(buffer);
			//write the what is left
			int lefttowrite =  subBufLen - towrite;
			System.arraycopy(subBuf, towrite,buffer,0,lefttowrite) ;
			index = lefttowrite;
		}
    }

}
