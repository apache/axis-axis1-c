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

package org.apache.axismora.wrappers.simpleType;

import java.io.ByteArrayOutputStream;
import java.io.IOException;

import org.apache.axis.AxisFault;
import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.message.SOAPFault;
import org.apache.axismora.MessageContext;
import org.apache.axismora.encoding.InOutParameter;
import org.apache.axismora.encoding.InParameter;
import org.apache.axismora.wsdl2ws.testing.TestUtils;

/**
 * Created on Sep 19, 2003
 * @author vtpavan(vtpavan@opensource.lk)
 * 
 * Custom in built wrapper for supporting primitive XSD data type hexBinary.
 */
public class HexBinaryParam implements InOutParameter{
	
	
	private byte[] param = null;
	
	public HexBinaryParam() {
	}
	
	public HexBinaryParam(HexBinaryParam in) {
		this.param = in.param;
	}

	public HexBinaryParam(MessageContext msgcontext){
		try{
			this.desierialize(msgcontext);
		}catch(AxisFault e){
			msgcontext.setSoapFault(new SOAPFault(e));
		}
				
	}

	public HexBinaryParam(String string){
		param = decode(string);
	}

	public HexBinaryParam(byte[] bytes){
		param = bytes;
	}
	/* (non-Javadoc)
	 * @see org.apache.axismora.encoding.InOutParameter#desierialize(org.apache.axismora.MessageData)
	 */
	public InParameter desierialize(MessageContext msgdata) throws AxisFault {
		String value = msgdata.nextText();
		this.param=decode(value);
		return this;	
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.encoding.Parameter#serialize(org.apache.axis.encoding.SerializationContext)
	 */
	public void serialize(SerializationContext context) {
//		String type_name = "HexBinary";
//		StringBuffer buf = new StringBuffer();
//		buf.append("<HexBinary xsi:type=\"ns1:").append(type_name + "\" xmlns:ns1 =\"");
//		buf.append(org.apache.axis.Constants.URI_DEFAULT_SCHEMA_XSD + "/#HexBinary\">");
//		buf.append(encode(param));
//		buf.append("</HexBinary>\n");
		try {
			context.writeString(encode(param));
		} catch (IOException e) {
			e.printStackTrace();	//ioexception
		}

		}
		public byte[] getBytes(){
			return param;
		}

		
		
		public static final String ERROR_ODD_NUMBER_OF_DIGITS 
			="ERROR_ODD_NUMBER_OF_DIGITS";
		public static final String ERROR_BAD_CHARACTER_IN_HEX_STRING 
			="ERROR_BAD_CHARACTER_IN_HEX_STRING";
			
		// Code from Ajp11, from Apache's JServ

		// Table for HEX to DEC byte translation
		public static final int[] DEC = {
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			00, 01, 02, 03, 04, 05, 06, 07,  8,  9, -1, -1, -1, -1, -1, -1,
			-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		};

		/**
		 * Convert a String of hexadecimal digits into the corresponding
		 * byte array by encoding each two hexadecimal digits as a byte.
		 *
		 * @param digits Hexadecimal digits representation
		 *
		 * @exception IllegalArgumentException if an invalid hexadecimal digit
		 *  is found, or the input string contains an odd number of hexadecimal
		 *  digits
		 */
		public static byte[] decode(String digits) {

			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			for (int i = 0; i < digits.length(); i += 2) {
				char c1 = digits.charAt(i);
				if ((i+1) >= digits.length())
					throw new IllegalArgumentException
						(ERROR_ODD_NUMBER_OF_DIGITS);
				char c2 = digits.charAt(i + 1);
				byte b = 0;
				if ((c1 >= '0') && (c1 <= '9'))
					b += ((c1 - '0') * 16);
				else if ((c1 >= 'a') && (c1 <= 'f'))
					b += ((c1 - 'a' + 10) * 16);
				else if ((c1 >= 'A') && (c1 <= 'F'))
					b += ((c1 - 'A' + 10) * 16);
				else
					throw new IllegalArgumentException
						(ERROR_BAD_CHARACTER_IN_HEX_STRING);
				if ((c2 >= '0') && (c2 <= '9'))
					b += (c2 - '0');
				else if ((c2 >= 'a') && (c2 <= 'f'))
					b += (c2 - 'a' + 10);
				else if ((c2 >= 'A') && (c2 <= 'F'))
					b += (c2 - 'A' + 10);
				else
					throw new IllegalArgumentException
						(ERROR_BAD_CHARACTER_IN_HEX_STRING);
				baos.write(b);
			}
			return (baos.toByteArray());

		}


		/**
		 * Convert a byte array into a printable format containing a
		 * String of hexadecimal digit characters (two per byte).
		 *
		 * @param bytes Byte array representation
		 */
		public static String encode(byte bytes[]) {

			StringBuffer sb = new StringBuffer(bytes.length * 2);
			for (int i = 0; i < bytes.length; i++) {
				sb.append(convertDigit((int) (bytes[i] >> 4)));
				sb.append(convertDigit((int) (bytes[i] & 0x0f)));
			}
			return (sb.toString());

		}

		/**
		 * Convert 4 hex digits to an int, and return the number of converted
		 * bytes.
		 *
		 * @param hex Byte array containing exactly four hexadecimal digits
		 *
		 * @exception IllegalArgumentException if an invalid hexadecimal digit
		 *  is included
		 */
		public static int convert2Int( byte[] hex ) {
			// Code from Ajp11, from Apache's JServ

			// assert b.length==4
			// assert valid data
			int len;
			if(hex.length < 4 ) return 0;
			if( DEC[hex[0]]<0 )
				throw new IllegalArgumentException(ERROR_BAD_CHARACTER_IN_HEX_STRING);
			len = DEC[hex[0]];
			len = len << 4;
			if( DEC[hex[1]]<0 )
				throw new IllegalArgumentException(ERROR_BAD_CHARACTER_IN_HEX_STRING);
			len += DEC[hex[1]];
			len = len << 4;
			if( DEC[hex[2]]<0 )
				throw new IllegalArgumentException(ERROR_BAD_CHARACTER_IN_HEX_STRING);
			len += DEC[hex[2]];
			len = len << 4;
			if( DEC[hex[3]]<0 )
				throw new IllegalArgumentException(ERROR_BAD_CHARACTER_IN_HEX_STRING);
			len += DEC[hex[3]];
			return len;
		}

		/**
		 * [Private] Convert the specified value (0 .. 15) to the corresponding
		 * hexadecimal digit.
		 *
		 * @param value Value to be converted
		 */
		private static char convertDigit(int value) {

			value &= 0x0f;
			if (value >= 10)
				return ((char) (value - 10 + 'a'));
			else
				return ((char) (value + '0'));

		}
		public HexBinaryParam getParam(){
			return this;
		}
		public int getIntParam(){
			return convert2Int(param);
		}
		
		
		
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		return encode(param);
	}
	public void init(){
			this.param = TestUtils.getRandomBytes();
	}

}