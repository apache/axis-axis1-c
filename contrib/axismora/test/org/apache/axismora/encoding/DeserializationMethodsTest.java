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

/**
 * @author Dimuthu Leelarathne(muthulee@opensource.lk)
 */

import junit.framework.TestCase;
import org.apache.axismora.soap.XMLTextData;

public class DeserializationMethodsTest extends TestCase {
    DeserializationMethods ds;
    boolean ok;

    public void testGetValue() {
        try {
            System.out.println("\n\ngetText()\n");
            ds = new DeserializationMethods("getTextTest.txt");
            while (true) {
                System.out.println("Text" + ds.getValue());
            }
        } catch (Exception e) {
            System.out.println("Get Text ***** " + e.getMessage());
        }
    }

    public void testGetValueQName() {
        try {
            String str;
            System.out.println("\n\nQNametest()\n");
            ds = new DeserializationMethods("QNameTagTest.txt");
            while (true) {
                //test for no value	
                str = ds.getValue("http://vajira.arawinda/NameSpace", "op1");
                System.out.println(str);
                if (str == null)
                    break;
            }
            while (true) {
                //test for lot of values
                str = ds.getValue("http://vajira.arawinda/NameSpace", "op3");
                System.out.println(str);
                if (str == null)
                    break;
            }
            while (true) {
                //test for one value
                str = ds.getValue("http://vajira.arawinda/NameSpace", "op4");
                System.out.println(str);
                if (str == null)
                    break;
            }
            while (true) {
                //test for wrong input i.e. not available stuff
                str = ds.getValue("http://vajira.arawinda/NameSpace", "op1");
                System.out.println(str);
                if (str == null)
                    break;
            }

        } catch (Exception e) {
            System.out.println("Get Text ***** " + e.getMessage());
        }
    }

    public void testGetValueOREnd() {
        //		   testing for getValueOREnd()
        try {
            String str;
            System.out.println("\n\ngetValueOREnd() test\n");
            ds = new DeserializationMethods("EndTest.txt");
            while (true) {
                str = ds.getValueOREnd();
                System.out.println(str);
                if (str == null)
                    break;
            }

            ds.resetBlindLevel();

            ds = new DeserializationMethods("EndTest.txt");
            ds.resetBlindLevel();
            ds.mmmNext();
            while (true) {
                str = ds.getValueOREnd();
                System.out.println(str);
                if (str == null)
                    break;
            }

        } catch (Exception e) {
            System.out.println("Get tag ***** " + e.getMessage());
        }
    }

    public void testGetTag() {
        /*-------------------------------------------------*/
        //		   get Tag  
        try {
            String str;
            XMLTextData dt;
            System.out.println("\n\ngetTag() test\n");
            ds = new DeserializationMethods("AttrTest.txt");
            dt = ds.getTag();
            System.out.println(
                "Tag1...."
                    + dt.getUri()
                    + "\t"
                    + dt.getType()
                    + "\t"
                    + dt.getLocalpart());
            dt = ds.getTag();
            System.out.println(
                "Tag2 ...."
                    + dt.getUri()
                    + "\t"
                    + dt.getType()
                    + "\t"
                    + dt.getLocalpart());
            dt = ds.getTag();
            System.out.println(
                "Tag3 ....."
                    + dt.getUri()
                    + "\t"
                    + dt.getType()
                    + "\t"
                    + dt.getLocalpart());
            dt = ds.getTag();
            System.out.println(
                "Tag3 ....."
                    + dt.getUri()
                    + "\t"
                    + dt.getType()
                    + "\t"
                    + dt.getLocalpart()
                    + "\t"
                    + dt.getAttrType());
            dt = ds.getTag();
            System.out.println(
                "Tag3 ....."
                    + dt.getUri()
                    + "\t"
                    + dt.getType()
                    + "\t"
                    + dt.getLocalpart()
                    + "\t"
                    + dt.getAttrType());
            dt = ds.getTag();
            System.out.println(
                "Tag3 ....."
                    + dt.getUri()
                    + "\t"
                    + dt.getType()
                    + "\t"
                    + dt.getLocalpart()
                    + "\t"
                    + dt.getAttrType());
        } catch (Exception e) {
            System.out.println("Get End tag ***** " + e.getMessage());
        }

    }

}
