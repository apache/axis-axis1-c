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

package org.apache.axismora.wsdl4ws;

import java.util.Iterator;
import java.util.Vector;

import junit.framework.TestCase;

import org.apache.axismora.wsdl2ws.info.TypeMap;

import org.apache.axis.wsdl.gen.Parser;
import org.apache.axis.wsdl.symbolTable.ElementDecl;
import org.apache.axis.wsdl.symbolTable.SchemaUtils;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.w3c.dom.Node;

/**
 * @author hemapani
 */
public class Node2AttibutesTest extends TestCase {
    /** org.apache.axis.wsdl.symbolTable.SchemaUtils 360 to add the max occurances **/
    public void testNode2Atributes() throws Exception {
        TypeMap typeMap = new TypeMap();
        Parser wsdlParser = new Parser();
        wsdlParser.run("./samples/kumaran.wsdl");
        SymbolTable tb = wsdlParser.getSymbolTable();
        Iterator it = tb.getTypeIndex().values().iterator();
        TypeEntry type;
        Iterator attribs;
        while (it.hasNext()) {
            type = (TypeEntry) it.next();

            Node node = type.getNode();

            if (node != null) {
                System.out.println("--------- " + type.getQName() + " ---------");
                System.out.println("#" + type.getBaseType() + "#");
                Vector a = SchemaUtils.getContainedElementDeclarations(node, tb);
                if (a != null)
                    attribs = a.iterator();
                else
                    continue;
                while (attribs.hasNext()) {
                    ElementDecl ed = (ElementDecl) attribs.next();
                    System.out.print(ed.getName() + " = ");
                    System.out.println(ed.getType().getQName());
                    //System.out.println(ed.getMaxoccurs());
                }
            }
        }

    }
    public static void main(String[] args) throws Exception {
        Node2AttibutesTest dl = new Node2AttibutesTest();
        dl.testNode2Atributes();
    }

}
