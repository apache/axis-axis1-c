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

package org.apache.axis.j2me.rpc.wsdl.tojava;

import java.io.IOException;
import java.util.Vector;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.gen.Generator;
import org.apache.axis.wsdl.symbolTable.SchemaUtils;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.toJava.Emitter;
import org.apache.axis.wsdl.toJava.JavaGeneratorFactory;
import org.apache.axis.wsdl.toJava.JavaWriter;
import org.apache.axis.wsdl.toJava.Utils;
import org.w3c.dom.Node;

/**
 * 
 * This class is customized for J2ME from Axis' JavaTypeWriter
 * 
 * @author Ias (iasandcb@tmax.co.kr)
 *  
 */
public class J2meTypeWriter implements Generator {

    /** Field typeWriter */
    private Generator typeWriter = null;

    /**
     * Constructor.
     * 
     * @param emitter     
     * @param type        
     * @param symbolTable 
     */
    public J2meTypeWriter(Emitter emitter, TypeEntry type,
                          SymbolTable symbolTable) {

        if (type.isReferenced() && !type.isOnlyLiteralReferenced()) {

            // Determine what sort of type this is and instantiate
            // the appropriate Writer.
            Node node = type.getNode();

            // If it's an array, don't emit a class
            if (!type.getName().endsWith("[]")) {

                // Generate the proper class for either "complex" or "enumeration" types
                Vector v = Utils.getEnumerationBaseAndValues(node, symbolTable);

                if (v != null) {
                    typeWriter = getEnumTypeWriter(emitter, type, v);
                } else {
                    TypeEntry base =
                            SchemaUtils.getComplexElementExtensionBase(node,
                                    symbolTable);

                    if (base == null) {
                        base = SchemaUtils.getComplexElementRestrictionBase(
                                node, symbolTable);
                    }

                    if (base == null) {
                        QName baseQName = SchemaUtils.getSimpleTypeBase(node);

                        if (baseQName != null) {
                            base = symbolTable.getType(baseQName);
                        }
                    }

                    typeWriter = getBeanWriter(
                            emitter, type,
                            SchemaUtils.getContainedElementDeclarations(
                                    node, symbolTable), base,
                            SchemaUtils.getContainedAttributeTypes(
                                    node, symbolTable));
                }
            }

        }
    }    // ctor

    /**
     * Write all the service bindnigs:  service and testcase.
     * 
     * @throws IOException 
     */
    public void generate() throws IOException {

        if (typeWriter != null) {
            typeWriter.generate();
        }

    }    // generate

    /**
     * getEnumWriter
     * 
     * @param emitter 
     * @param type    
     * @param v       
     * @return 
     */
    protected JavaWriter getEnumTypeWriter(Emitter emitter, TypeEntry type,
                                           Vector v) {
        return new J2meEnumTypeWriter(emitter, type, v);
    }

    /**
     * getBeanWriter
     * 
     * @param emitter    
     * @param type       
     * @param elements   
     * @param base       
     * @param attributes 
     * @return 
     */
    protected JavaWriter getBeanWriter(Emitter emitter, TypeEntry type,
                                       Vector elements, TypeEntry base,
                                       Vector attributes) {

        // If this complexType is referenced in a
        // fault context, emit a bean-like exception
        // class
        Boolean isComplexFault = (Boolean) type.getDynamicVar(
                JavaGeneratorFactory.COMPLEX_TYPE_FAULT);

        if ((isComplexFault != null) && isComplexFault.booleanValue()) {
            return new J2meBeanFaultWriter(emitter, type, elements, base,
                    attributes);
        }

        return new J2meBeanWriter(emitter, type, elements, base, attributes);
    }

}
