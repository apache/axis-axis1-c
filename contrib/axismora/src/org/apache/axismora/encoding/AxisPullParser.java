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

package org.apache.axismora.encoding;

import java.io.IOException;

import org.apache.axis.AxisFault;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;

/**
 * @author Dimuthu Leelarathne.
 * 
 * It is strongly recomended that you reset the LsfAxisPullParser each time you use it
 *
 */
public class AxisPullParser {
    XmlPullParser xpp;
    private int state, level;

    public AxisPullParser(XmlPullParser xp) {
        this.level = 0;
        this.xpp = xp;
    }

    public XmlPullParser getParser() {
        return this.xpp;
    }

    // removes unnecassary whitespaces.
    /**
     * Removes whitespaces 
     *  1)between two start tags
     *  2)two end tags
     *  3)between end tag that follows the starttag
     */
    public int next() throws AxisFault {
        try {
            state = xpp.next();

            if (state != XmlPullParser.TEXT) {
                return state;
            } else {
                if (xpp.isWhitespace())
                    return xpp.next(); // next one musn't be whitesapce
                else
                    return state;
            }
        } catch (XmlPullParserException e) {
            e.printStackTrace();
            throw new AxisFault("", e);
        } catch (IOException e) {
            e.printStackTrace();
            throw new AxisFault("", e);
        }
    }
    /*
    if(level==0){ // initial state
        	if(state!=XmlPullParser.TEXT){
    	         level=state;
    	         return level;
    		}else{
    			if(xpp.isWhitespace()){
    				level=xpp.next();
    				// next cannot be whitespace. So return it.
    				return level;
    			}else{
    				level=state;
    			    return level;
    			}    
    		}
     //level=2 i.e. is a start tag before.		
     }else if(level==XmlPullParser.START_TAG){
    	  
    	  if(state!=XmlPullParser.TEXT){
    					 level=state;
    					 return level;
    	  }else{
    		    if(xpp.isWhitespace()){
                    //whitespace after start tag
    	         	level=xpp.next();
    				// next() doesn't return a whitesapce again
    				return level;
    		    }else{ // Text but not whitespace 
    				level=state;
    			    return level;
    		    } 
    	  }          	
      	
     }else{ 
     	// we are here because (level==XmlPullParser.END_TAG)
    	if(state!=XmlPullParser.TEXT){
    		level=state;
    		return level;
    	}else{
    		if(xpp.isWhitespace()){
    			//whitespace after end tag
    			level=xpp.next();
    			// next() doesn't return a whitesapce again
    			return level;
    		}else{ // Text but not whitespace 
    			level=state;
    			return level;
    	    }			    
    	}   
    }	
    	
    	
    } catch (XmlPullParserException e) {
    	e.printStackTrace();
        throw new AxisFault("",e);
    } catch (IOException e) {
    	e.printStackTrace();
    	throw new AxisFault("",e);
    }   
    
    
            
    }// next()=
    */

    public int getEventType() throws XmlPullParserException {
        return this.xpp.getEventType();
    }

    public int getAttributeCount() {
        return this.xpp.getAttributeCount();
    }

    public String getAttributeName(int index) {
        return this.xpp.getAttributeName(index);
    }

    public String getAttributeNamespace(int index) {
        return this.xpp.getAttributeNamespace(index);
    }

    public String getAttributeValue(int index) {
        return this.xpp.getAttributeValue(index);
    }

    public String getName() {
        return this.xpp.getName();
    }

    public String getNamespace() {
        return this.xpp.getNamespace();
    }

    public String getText() {
        return this.xpp.getText();
    }

}
