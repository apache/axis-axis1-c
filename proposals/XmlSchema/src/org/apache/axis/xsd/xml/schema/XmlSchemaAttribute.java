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

/*
 * XmlSchemaAttribute.java
 *
 * Created on September 27, 2001, 3:09 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.xml.QualifiedName;

/**
 * Class for attribute types. Represents the World Wide Web Consortium
 * (W3C) attribute element.
 *
 * @author  mukund
 */

// October 15th - momo - initial implementation

public class XmlSchemaAttribute extends XmlSchemaAnnotated {

    Object attributeType;
    String defaultValue, fixedValue, name;
    XmlSchemaForm form;
    XmlSchemaSimpleType schemaType;
    QualifiedName schemaTypeName, qualifiedName, refName;
    XmlSchemaUse use;

    /** Creates new XmlSchemaAttribute */
    public XmlSchemaAttribute() {
        form = new XmlSchemaForm("None");
        use = new XmlSchemaUse("None");
    }

    public Object getAttributeType() {
        return attributeType;
    }

    public String getDefaultValue() {
        return defaultValue;
    }

    public void setDefaultValue(String defaultValue) {
        this.defaultValue = defaultValue;
    }

    public String getFixedValue() {
        return fixedValue;
    }

    public void setFixedValue(String fixedValue) {
        this.fixedValue = fixedValue;
    }

    public XmlSchemaForm getForm() {
        return form;
    }

    public void setSchemaForm(XmlSchemaForm form) {
        this.form = form;
    }

    public QualifiedName getQualifiedName() {
        return qualifiedName;
    }

    public void setQualifiedName(QualifiedName qualifiedName) {
        this.qualifiedName = qualifiedName;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public QualifiedName getRefName() {
        return refName;
    }

    public void setRefName(QualifiedName refName) {
        this.refName = refName;
    }

    public XmlSchemaSimpleType getSchemaType() {
        return schemaType;
    }

    public void setSchemaType(XmlSchemaSimpleType schemaType) {
        this.schemaType = schemaType;
    }

    public QualifiedName getSchemaTypeName() {
        return schemaTypeName;
    }

    public void setSchemaTypeName(QualifiedName schemaTypeName) {
        this.schemaTypeName = schemaTypeName;
    }

    public XmlSchemaUse getUse() {
        return use;
    }

    public void setUse(XmlSchemaUse use) {
        this.use = use;
    }

    public String toString(String prefix, int tab) {
        String xml = new String();

        if (!prefix.equals("") && prefix.indexOf(":") == -1)
            prefix += ":";

        for (int i = 0; i < tab; i++)
            xml += "\t";

        xml += "<" + prefix + "attribute name=\"" + name + "\" type=\"" + schemaTypeName + "\"/>\n";

        return xml;
    }
}
