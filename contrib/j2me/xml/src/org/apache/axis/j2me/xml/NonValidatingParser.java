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

package org.apache.axis.j2me.xml;

import org.apache.axis.j2me.xml.sax.AttributesImpl;
import org.apache.axis.j2me.xml.sax.LocatorImpl;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.Hashtable;
import java.util.Stack;

import javax.microedition.io.Connector;

import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;
import org.xml.sax.helpers.DefaultHandler;

/**
 * This is a non-validating parser implementation for J2ME JAXP
 * @author Ias (iasandcb@tmax.co.kr)
 *  
 */
public class NonValidatingParser {

    protected Hashtable attributeDefaultValues;
    protected Hashtable attributeTypes;
    private Hashtable elementTypes;
    private boolean endOfDocument;
    private EntityResolver entityResolver;

    private DefaultHandler handler;
    private LocatorImpl locator;
    private Hashtable namespaces;

    private EntityResolver parameterEntityResolver;
    private Stack prefixes;
    private PushBackReader reader;

    private String rootElement;
    private SAXParserImpl saxParser;

    /**
	 * Constructor with source, handler and SAXParserImpl
	 * 
	 * @param source
	 * @param handler
	 * @param saxParser
	 * @throws IOException
	 */
    public NonValidatingParser(InputSource source, DefaultHandler handler, SAXParserImpl saxParser) throws IOException {
        Reader sourceReader = source.getCharacterStream();
        if (sourceReader == null) {
            InputStream ips = source.getByteStream();
            if (ips == null) {
                String systemId = source.getSystemId();
                ips = Connector.openInputStream(systemId);
                if (ips == null) {
                    throw new IOException();
                }
            }
            sourceReader = new InputStreamReader(ips);
        }

        locator = new LocatorImpl(source.getPublicId(), source.getSystemId(), 1, 1);
        reader = new PushBackReader(sourceReader, locator);
        namespaces = new Hashtable();
        prefixes = new Stack();
        this.handler = handler;
        this.saxParser = saxParser;

        attributeDefaultValues = new Hashtable();
        attributeTypes = new Hashtable();

        entityResolver = new EntityResolver();
        parameterEntityResolver = new EntityResolver();

        elementTypes = new Hashtable();
    }

    private boolean checkLiteral(String literal) throws Exception {
        for (int i = 0; i < literal.length(); i++) {
            if (reader.read() != literal.charAt(i)) {
                return false;
            }
        }

        return true;
    }

    private String closeCdataTag() throws Exception {
        boolean closed = false;
        StringBuffer buffer = new StringBuffer();
        while (!closed) {
            char ch = reader.read();

            if (ch == ']') {
                char ch2 = reader.read();

                if (ch2 == ']') {
                    char ch3 = reader.read();

                    if (ch3 == '>') {
                        closed = true;
                    }
                    else {
                        buffer.append(ch);
                        buffer.append(ch2);
                        buffer.append(ch3);
                    }
                }
                else {
                    buffer.append(ch);
                    buffer.append(ch2);
                }
            }
            else {
                buffer.append(ch);
            }
        }
        return buffer.toString();
    }

    private String closeDtdTag() throws Exception {
        boolean closed = false;
        StringBuffer buffer = new StringBuffer();
        while (!closed) {
            char ch = reader.read();

            if (ch == '?') {
                char ch2 = reader.read();

                if (ch2 == '>') {
                    closed = true;
                }
                else {
                    buffer.append(ch);
                    buffer.append(ch2);
                }
            }
            else {
                buffer.append(ch);
            }
        }
        return buffer.toString();
    }

    private String closeInstructionTag() throws Exception {
        boolean closed = false;
        StringBuffer buffer = new StringBuffer();
        while (!closed) {
            char ch = reader.read();

            if (ch == '?') {
                char ch2 = reader.read();

                if (ch2 == '>') {
                    closed = true;
                }
                else {
                    buffer.append(ch);
                    buffer.append(ch2);
                }
            }
            else {
                buffer.append(ch);
            }
        }
        return buffer.toString();
    }

    /**
	 * start to parse the given document
	 * 
	 * @throws SAXException
	 * @throws IOException
	 */
    public void parse() throws SAXException, IOException {
        handler.setDocumentLocator(locator);
        String token;
        try {
            while (!reader.isEof()) {
                token = readToken('&');
                char leading = token.charAt(0);
                switch (leading) {
                    case '<' :
                        if (endOfDocument) {
                            handler.fatalError(new SAXParseException("End of Document", locator));
                            break;
                        }
                        parseTag(false);
                        break;

                    case '\n' :
                        break;
                    case ' ' :
                        break;
                    case '\t' :
                        break;
                    case '\r' :
                        break;

                    default :
                        if (reader.isEof()) {
                            break;
                        }
                        if (endOfDocument) {
                            handler.fatalError(new SAXParseException("End of Document", locator));
                            break;
                        }
                        handler.fatalError(new SAXParseException("'" + leading + "' invaid input", locator));
                }
            }
        }
        catch (SAXException se) {
            throw se;
        }
        catch (IOException ie) {
            throw ie;
        }
        catch (Exception e) {
            throw new SAXException(e.getMessage());
        }
        finally {
            handler.endDocument();
        }

    }

    protected void parseAttribute(AttributesImpl attributes) throws Exception {
        String key = readIdentifier();
        skipWhitespace();

        if (!readToken('&').equals("=")) {
            handler.fatalError(new SAXParseException("'=' expected", locator));
        }

        skipWhitespace();
        String type = attributes.getTypeFromDeclaration(key);
        String value = readAttributeValue(!type.equals("CDATA"), entityResolver);
        if (key.equals("xmlns")) {
            String prefix = "";
            namespaces.put(prefix, value);
            prefixes.push(prefix);
            if (saxParser.isNamespacePrefixAware()) {
                attributes.add(key, type, value);
            }
            else {
                handler.startPrefixMapping(prefix, value);
            }
        }
        else if (key.startsWith("xmlns:")) {
            String prefix = key.substring(6);
            namespaces.put(prefix, value);
            prefixes.push(prefix);
            if (saxParser.isNamespacePrefixAware()) {
                attributes.add(key, type, value);
            }
            else {
                handler.startPrefixMapping(prefix, value);
            }
        }
        else {
            attributes.add(key, type, value);
        }
    }

    private void parseCdata() throws Exception {
        if (checkLiteral("CDATA[")) {
            String data = closeCdataTag();
            handler.characters(data.toCharArray(), 0, data.length());
        }
        else {
            handler.fatalError(new SAXParseException("'<![[CDATA[' expected", locator));
        }
    }

    private char parseCharLiteral(String entity) throws Exception {
        if (entity.charAt(2) == 'x') {
            entity = entity.substring(3, entity.length() - 1);
            return (char) Integer.parseInt(entity, 16);
        }
        else {
            entity = entity.substring(2, entity.length() - 1);
            return (char) Integer.parseInt(entity, 10);
        }
    }

    private void parseDocType() throws Exception {
        if (!checkLiteral("OCTYPE")) {
            handler.fatalError(new SAXParseException("'<!DOCTYPE' expected", locator));
        }

        skipWhitespace();
        String systemID = null;
        StringBuffer publicID = new StringBuffer();
        rootElement = readIdentifier();
        skipWhitespace();
        char ch = reader.read();
        if (ch == 'P') {
            systemID = readPublicId(publicID);
            handler.skippedEntity("[dtd]");
            skipWhitespace();
            ch = reader.read();
        }
        else if (ch == 'S') {
            systemID = readSystemId();
            handler.skippedEntity("[dtd]");
            skipWhitespace();
            ch = reader.read();
        }

        if (ch == '[') {
            parseDtd();
            skipWhitespace();
            ch = reader.read();
        }

        if (ch != '>') {
            handler.fatalError(new SAXParseException("'>' expected", locator));
        }

    }

    private void parseDtd() throws Exception {
        skipWhitespace();
        for (;;) {
            String str = readToken('%');
            char ch = str.charAt(0);

            if (ch == '%') {
                parseDtdEntity(parameterEntityResolver);
                continue;
            }
            else if (ch == '<') {
                parseDtdDeclaration(entityResolver);
            }
            else if (ch == ']') {
                return; // end internal DTD
            }
            else {
                handler.fatalError(new SAXParseException("'" + str + "' invalid input", locator));
            }
            do {
                ch = reader.read();
            }
            while ((ch == ' ') || (ch == '\t') || (ch == '\n') || (ch == '\r'));

            reader.unread();
        }
    }

    protected void parseDtdAttributeList(EntityResolver entityResolver) throws Exception {
        if (!checkLiteral("TTLIST")) {
            skipTag();
            return;
        }

        skipWhitespace();
        String str = readToken('%');
        char ch = str.charAt(0);
        while (ch == '%') {
            parseEntity(str, parameterEntityResolver);
            str = readToken('%');
            ch = str.charAt(0);
        }
        reader.unread();
        String elementName = readIdentifier();
        skipWhitespace();

        str = readToken('%');
        ch = str.charAt(0);
        while (ch == '%') {
            parseEntity(str, parameterEntityResolver);
            str = readToken('%');
            ch = str.charAt(0);
        }

        Hashtable defaultValues = new Hashtable();
        Hashtable types = new Hashtable();

        while (ch != '>') {
            reader.unread();
            String attName = readIdentifier();
            skipWhitespace();
            str = readToken('%');
            ch = str.charAt(0);
            while (ch == '%') {
                parseEntity(str, parameterEntityResolver);
                str = readToken('%');
                ch = str.charAt(0);
            }

            if (ch == '(') {
                StringBuffer typeBuffer = new StringBuffer();
                typeBuffer.append(str);
                while (ch != ')') {
                    str = readToken('%');
                    ch = str.charAt(0);
                    while (ch == '%') {
                        parseEntity(str, parameterEntityResolver);
                        str = readToken('%');
                        ch = str.charAt(0);
                    }
                    typeBuffer.append(str);
                }
                types.put(attName, typeBuffer.toString());
            }
            else {
                reader.unread();
                String type = readIdentifier();
                types.put(attName, type);
            }

            skipWhitespace();
            str = readToken('%');
            ch = str.charAt(0);
            while (ch == '%') {
                parseEntity(str, parameterEntityResolver);
                str = readToken('%');
                ch = str.charAt(0);
            }

            if (ch == '#') {
                str = readIdentifier();
                skipWhitespace();

                if (!str.equals("FIXED")) {
                    skipWhitespace();

                    str = readToken('%');
                    ch = str.charAt(0);
                    while (ch == '%') {
                        parseEntity(str, parameterEntityResolver);
                        str = readToken('%');
                        ch = str.charAt(0);
                    }

                    continue;
                }
            }
            else {
                reader.unread();
            }

            String value = readString('%', parameterEntityResolver);
            defaultValues.put(attName, value);
            skipWhitespace();

            str = readToken('%');
            ch = str.charAt(0);
            while (ch == '%') {
                parseEntity(str, parameterEntityResolver);
                str = readToken('%');
                ch = str.charAt(0);
            }
        }

        if (!types.isEmpty()) {
            attributeTypes.put(elementName, types);
        }

        if (!defaultValues.isEmpty()) {
            attributeDefaultValues.put(elementName, defaultValues);
        }
    }

    private void parseDtdConditionalSection(EntityResolver entityResolver) throws Exception {
        skipWhitespace();

        // paramete entity should be supported. call readString instead.
        String str = readString('%', entityResolver);
        char ch = str.charAt(0);

        if (ch != 'I') {
            skipTag();
            return;
        }

        str = readToken('%');
        ch = str.charAt(0);

        switch (ch) {
            case 'G' :
                parseDtdIgnoreSection(entityResolver);
                return;

            case 'N' :
                break;

            default :
                skipTag();
                return;
        }

        if (!checkLiteral("CLUDE")) {
            skipTag();
            return;
        }

        skipWhitespace();

        str = readToken('%');
        ch = str.charAt(0);

        if (ch != '[') {
            skipTag();
            return;
        }

        reader.addString(closeCdataTag());
    }

    private void parseDtdDeclaration(EntityResolver entityResolver) throws Exception {
        String str = readToken('%');
        char ch = str.charAt(0);

        if (ch != '!') {
            skipTag();
            return;
        }

        str = readToken('%');
        ch = str.charAt(0);

        switch (ch) {
            case '-' :
                skipComment();
                break;

            case '[' :
                parseDtdConditionalSection(entityResolver);
                break;

            case 'E' :
                ch = reader.read();
                if (ch == 'L') {
                    parseDtdElement(entityResolver);
                }
                else {
                    reader.unread();
                    parseDtdEntity(entityResolver);
                }
                break;

            case 'A' :
                parseDtdAttributeList(entityResolver);
                break;

            case 'N' :
                parseDtdNotation(entityResolver);
                break;

            default :
                skipTag();
        }
    }

    protected void parseDtdElement(EntityResolver entityResolver) throws Exception {
        if (!checkLiteral("EMENT")) {
            skipTag();
            return;
        }

        skipWhitespace();
        String str = readToken('%');
        char ch = str.charAt(0);
        while (ch == '%') {
            parseEntity(str, parameterEntityResolver);
            str = readToken('%');
            ch = str.charAt(0);
        }
        reader.unread();
        String elementName = readIdentifier();
        skipWhitespace();

        str = readToken('%');
        ch = str.charAt(0);
        while (ch == '%') {
            parseEntity(str, parameterEntityResolver);
            str = readToken('%');
            ch = str.charAt(0);
        }

        StringBuffer typeBuffer = new StringBuffer();
        reader.unread();
        skipWhitespace();
        while (ch != '>') {
            str = readToken('%');
            ch = str.charAt(0);
            while (ch == '%') {
                parseEntity(str, parameterEntityResolver);
                str = readToken('%');
                ch = str.charAt(0);
            }
            typeBuffer.append(str);
        }
        elementTypes.put(elementName, typeBuffer.toString());

    }

    private void parseDtdEntity(EntityResolver entityResolver) throws Exception {
        if (!checkLiteral("NTITY")) {
            skipTag();
            return;
        }

        skipWhitespace();
        char ch = readChar('\0');

        if (ch == '%') {
            skipWhitespace();
            entityResolver = parameterEntityResolver;
        }
        else {
            reader.unread();
        }

        String name = readIdentifier();
        skipWhitespace();
        ch = readChar('%');
        String systemId = null;
        String publicId = null;
        String notationMark = null;
        String notationName = null;

        switch (ch) {
            case 'P' :
                if (!checkLiteral("UBLIC")) {
                    skipTag();
                    return;
                }

                skipWhitespace();
                publicId = readString('%', parameterEntityResolver);
                skipWhitespace();
                systemId = readString('%', parameterEntityResolver);
                skipWhitespace();
                notationMark = readString('%', parameterEntityResolver);
                if (notationMark.startsWith("NDATA")) {
                    skipWhitespace();
                    notationName = readString('%', parameterEntityResolver);
                }
                break;

            case 'S' :
                if (!checkLiteral("YSTEM")) {
                    skipTag();
                    return;
                }

                skipWhitespace();
                systemId = readString('%', parameterEntityResolver);
                skipWhitespace();
                notationMark = readString('%', parameterEntityResolver);
                if (notationMark.startsWith("NDATA")) {
                    skipWhitespace();
                    notationName = readString('%', parameterEntityResolver);
                }
                break;

            case '"' :
            case '\'' :
                reader.unread();
                String value = readString('%', parameterEntityResolver);
                entityResolver.addInternalEntity(name, value);
                skipWhitespace();
                readChar('%');
                break;

            default :
                skipTag();
        }

        if (notationName != null) {
            handler.unparsedEntityDecl(name, publicId, systemId, notationName);
        }
        if (systemId != null) {
            entityResolver.addExternalEntity(name, publicId, systemId);
        }
    }

    private void parseDtdIgnoreSection(EntityResolver entityResolver) throws Exception {
        if (!checkLiteral("NORE")) {
            skipTag();
            return;
        }

        skipWhitespace();

        String str = readToken('%');
        char ch = str.charAt(0);

        if (ch != '[') {
            skipTag();
            return;
        }

        closeCdataTag();
    }

    private void parseDtdNotation(EntityResolver entityResolver) throws Exception {
        if (!checkLiteral("OTATION")) {
            skipTag();
            return;
        }
        skipWhitespace();
        char ch = readChar('\0');

        if (ch == '%') {
            skipWhitespace();
            entityResolver = parameterEntityResolver;
        }
        else {
            reader.unread();
        }

        String name = readIdentifier();
        skipWhitespace();
        ch = readChar('%');
        String systemId = null;
        String publicId = null;

        switch (ch) {
            case 'P' :
                if (!checkLiteral("UBLIC")) {
                    skipTag();
                    return;
                }

                skipWhitespace();
                publicId = readString('%', parameterEntityResolver);
                skipWhitespace();
                systemId = readString('%', parameterEntityResolver);
                skipWhitespace();
                readChar('%');
                break;

            case 'S' :
                if (!checkLiteral("YSTEM")) {
                    skipTag();
                    return;
                }

                skipWhitespace();
                systemId = readString('%', parameterEntityResolver);
                skipWhitespace();
                readChar('%');
                break;

            default :
                skipTag();
        }

        handler.notationDecl(name, publicId, systemId);
    }

    protected void parseElement() throws Exception {
        String qName = readIdentifier();
        String localName = qName;
        skipWhitespace();
        String prefix = null;
        int colonIndex = qName.indexOf(':');

        if (colonIndex > 0) {
            prefix = qName.substring(0, colonIndex);
            localName = qName.substring(colonIndex + 1);
        }

        Hashtable belongedAttributeDefaultValues = (Hashtable) attributeDefaultValues.get(qName);
        Hashtable belongedAttributeTypes = (Hashtable) attributeTypes.get(qName);
        AttributesImpl attributes = new AttributesImpl(namespaces, belongedAttributeDefaultValues, belongedAttributeTypes);
        int previousPrefixesSize = prefixes.size();

        char ch;
        for (;;) {
            ch = reader.read();

            if ((ch == '/') || (ch == '>')) {
                break;
            }

            reader.unread();

            parseAttribute(attributes);
            skipWhitespace();
        }

        String namespaceUri = "";
        if (saxParser.isNamespaceAware()) {
            if (prefix == null) {
                String defaultNamespaceUri = (String) namespaces.get("");
                if (defaultNamespaceUri != null) {
                    namespaceUri = defaultNamespaceUri;
                }
            }
            else {
                String mappedNamespaceUri = (String) namespaces.get(prefix);
                if (mappedNamespaceUri != null) {
                    namespaceUri = mappedNamespaceUri;
                }
            }
        }
        if (rootElement == null) {
            rootElement = qName;
        }
        handler.startElement(namespaceUri, localName, qName, attributes);

        if (ch == '/') {
            if (reader.read() != '>') {
                handler.fatalError(new SAXParseException("'>' expected", locator));
            }

            handler.endElement(namespaceUri, localName, qName);
            int currentPrefixesSize = prefixes.size();
            for (int i = currentPrefixesSize; i > previousPrefixesSize; i--) {
                String mappedPrefix = (String) prefixes.pop();
                handler.endPrefixMapping(mappedPrefix);
                namespaces.remove(mappedPrefix);
            }
            if (qName.equals(rootElement)) {
                endOfDocument = true;
            }
            return;
        }

        StringBuffer buffer = new StringBuffer();
        String str;

        for (;;) {

            for (;;) {
                if (buffer.length() == 0) {
                    String elementType = (String) elementTypes.get(qName);
                    if ((elementType != null) && ((elementType.equals("EMPTY") || elementType.indexOf("#PCDATA") < 0))) {
                        char[] whitespaces = parseWhitespace();
                        if (whitespaces.length > 0) {
                            handler.ignorableWhitespace(whitespaces, 0, whitespaces.length);
                        }
                    }
                    else {
                        skipWhitespace();
                    }
                }
                str = readToken('&');

                if ((str.charAt(0) == '&') && (str.charAt(1) != '#')) {
                    parseEntity(str, entityResolver);
                }
                else {
                    break;
                }
            }

            if (str.charAt(0) == '<') {
                if (buffer.length() > 0) {
                    char[] characters = new char[buffer.length()];
                    buffer.getChars(0, buffer.length(), characters, 0);
                    handler.characters(characters, 0, buffer.length());
                    buffer.setLength(0);
                }
                str = readToken('\0');

                if (str.charAt(0) == '/') {
                    skipWhitespace();
                    str = readIdentifier();

                    if (!str.equals(qName)) {
                        handler.fatalError(new SAXParseException("Wrong closing tag: " + str, locator));
                    }

                    skipWhitespace();

                    if (reader.read() != '>') {
                        handler.fatalError(new SAXParseException("closing tag must be empty", locator));
                    }

                    handler.endElement(null, localName, qName);
                    int currentPrefixesSize = prefixes.size();
                    for (int i = currentPrefixesSize; i > previousPrefixesSize; i--) {
                        String mappedPrefix = (String) prefixes.pop();
                        handler.endPrefixMapping(mappedPrefix);
                        namespaces.remove(mappedPrefix);
                    }
                    if (qName.equals(rootElement)) {
                        endOfDocument = true;
                    }
                    break;
                }
                else { // <[^/]
                    reader.unread();
                    parseTag(true);
                }
            }
            else { // [^<]
                if (str.charAt(0) == '&') {
                    ch = parseCharLiteral(str);
                    buffer.append(ch);
                }
                else {
                    buffer.append(str);
                }
            }
        }
    }

    private void parseEntity(String entity, EntityResolver entityResolver) throws Exception {
        entity = entity.substring(1, entity.length() - 1);
        Object obj = entityResolver.getEntity(entity);

        if (obj == null) {
            handler.warning(new SAXParseException("'" + entity + "' invalid entity", locator));
        }
        else if (obj instanceof java.lang.String) {
            reader.addString((String) obj);
        }
        else {
            String[] id = (String[]) obj;
            // NOTE: The following implementation depends on my decision on how this parser should work.
            String publicId = id[0];
            String systemId = id[1];
            InputSource entitySource = handler.resolveEntity(publicId, systemId);
            if (entitySource == null) {
                if (systemId == null) {
                    handler.skippedEntity(entityResolver == parameterEntityResolver ? "&" + entity : entity);
                    return;
                }
                entitySource = new InputSource(systemId);
            }
            Reader entityReader = entitySource.getCharacterStream();
            if (entityReader == null) {
                InputStream ips = entitySource.getByteStream();
                if (ips == null) {
                    String entitySystemId = entitySource.getSystemId();
                    ips = Connector.openInputStream(entitySystemId);
                    if (ips == null) {
                        throw new IOException();
                    }
                }
                entityReader = new InputStreamReader(ips);
            }

            StringBuffer replaceTextBuffer = new StringBuffer();
            char[] buffer = new char[256];
            int length;
            while (((length = entityReader.read(buffer)) != -1)) {
                replaceTextBuffer.append(buffer, 0, length);
            }
            reader.addString(replaceTextBuffer.toString());
        }

    }

    private void parsePi() throws Exception {
        skipWhitespace();
        String target = readIdentifier();
        skipWhitespace();
        if (target.equals("xml")) {
            closeInstructionTag();
            handler.startDocument();
        }
        else {
            String data = closeInstructionTag();
            handler.processingInstruction(target, data);
        }
    }

    protected void parseSpecialTag(boolean allowCdata) throws Exception {
        String str = readToken('&');
        char ch = str.charAt(0);

        if (ch == '&') {
            handler.fatalError(new SAXParseException("No entity reference is expected here (" + str + ")", locator));
        }

        switch (ch) {
            case '[' :
                if (allowCdata) {
                    parseCdata();
                }
                else {
                    handler.fatalError(new SAXParseException("No CDATA section is expected here", locator));
                }

                return;

            case 'D' :
                parseDocType();
                return;

            case '-' :
                skipComment();
                return;
        }
    }

    private void parseTag(boolean allowCdata) throws Exception {
        String token = readToken('&');
        char leading = token.charAt(0);
        if (leading == '&') {
            handler.fatalError(new SAXParseException("No entity reference is expected here (" + token + ")", locator));
        }
        switch (leading) {
            case '?' :
                parsePi();
                break;

            case '!' :
                parseSpecialTag(allowCdata);
                break;

            default :
                reader.unread();
                parseElement();
        }

    }

    private char[] parseWhitespace() throws Exception {
        char ch;
        StringBuffer whitespaces = new StringBuffer();
        do {
            ch = reader.read();
            switch (ch) {
                case '\t' :
                    whitespaces.append(ch);
                    break;
                case '\r' :
                    break;
                case '\n' :
                    whitespaces.append(ch);
                    break;
                case ' ' :
                    whitespaces.append(ch);
                    break;
                default :
                    reader.unread();
            }
        }
        while ((ch == ' ') || (ch == '\t') || (ch == '\n') || (ch == '\r'));
        return whitespaces.toString().toCharArray();
    }

    private char readChar(char entityChar) throws Exception {
        String str = readToken(entityChar);
        char ch = str.charAt(0);

        if (ch == entityChar) {
            handler.fatalError(new SAXParseException("No entity reference is expected here (" + str + ")", locator));
        }

        return ch;
    }

    private String readPublicId(StringBuffer publicId) throws Exception {
        if (!checkLiteral("UBLIC")) {
            return null;
        }

        skipWhitespace();
        publicId.append(readString('\0', null));
        skipWhitespace();
        return readString('\0', null);
    }

    private String readString(char entityChar, EntityResolver entityResolver) throws Exception {
        StringBuffer result = new StringBuffer();
        char delim = reader.read();

        if ((delim != '\'') && (delim != '"')) {
            handler.fatalError(new SAXParseException("delimitor expected", locator));
        }

        for (;;) {
            String str = readToken(entityChar);
            char ch = str.charAt(0);

            // time to normalize

            if (ch == entityChar) {
                if (str.charAt(1) == '#') {
                    result.append(parseCharLiteral(str));
                }
                else {
                    parseEntity(str, entityResolver);
                }
            }
            else if (ch == '&') {
                if (str.charAt(1) == '#') {
                    result.append(parseCharLiteral(str));
                }
                else {
                    result.append(str);
                }
            }
            else if (ch == delim) {
                break;
            }
            else {
                result.append(ch);
            }
        }

        return result.toString();
    }

    private String readAttributeValue(boolean isNotCdata, EntityResolver entityResolver) throws Exception {
        StringBuffer resultBuffer = new StringBuffer();
        boolean wasSpace = false;
        char delim = reader.read();

        if ((delim != '\'') && (delim != '"')) {
            handler.fatalError(new SAXParseException("delimitor expected", locator));
        }

        for (;;) {
            String str = readToken('&');
            char ch = str.charAt(0);

            // end of line normalization
            if (ch == '\r') {
                str = readToken('&');
                ch = str.charAt(0);
                if (ch != '\n') {
                    ch = '\n';
                }
            }

            if (ch == '&') {
                if (str.charAt(1) == '#') {
                    resultBuffer.append(parseCharLiteral(str));
                }
                else {
                    parseEntity(str, entityResolver);
                }
            }
            else if (ch == delim) {
                break;
            }
            else {
                if (ch == '\n' || ch == '\t') {
                    ch = ' ';
                }
                if (ch == ' ' && isNotCdata && wasSpace) {
                    continue;
                }
                resultBuffer.append(ch);
                if (ch == ' ' && isNotCdata && !wasSpace) {
                    wasSpace = true;
                }
                if (ch != ' ' && isNotCdata && wasSpace) {
                    wasSpace = false;
                }
            }
        }

        String result = resultBuffer.toString();
        if (isNotCdata) {
            result = result.trim();
        }
        return result;
    }

    private String readSystemId() throws Exception {
        if (!checkLiteral("YSTEM")) {
            return null;
        }

        skipWhitespace();
        return readString('\0', null);
    }

    private String readToken(char entityChar) throws Exception {
        char ch = reader.read();
        StringBuffer buf = new StringBuffer();
        buf.append(ch);

        if (ch == entityChar) {
            while (ch != ';') {
                ch = reader.read();
                buf.append(ch);
            }
        }

        return buf.toString();
    }
    private String readIdentifier() throws Exception {
        StringBuffer result = new StringBuffer();

        for (;;) {
            char ch = reader.read();

            if ((ch == '_')
                || (ch == ':')
                || (ch == '-')
                || (ch == '.')
                || ((ch >= 'a') && (ch <= 'z'))
                || ((ch >= 'A') && (ch <= 'Z'))
                || ((ch >= '0') && (ch <= '9'))
                || (ch > '\u007E')) {
                result.append(ch);
            }
            else {
                reader.unread();
                break;
            }
        }

        return result.toString();
    }

    private void skipComment() throws Exception {
        if (reader.read() != '-') {
            handler.fatalError(new SAXParseException("'<!--' expected", locator));
        }

        int dashesRead = 0;

        for (;;) {
            char ch = reader.read();

            switch (ch) {
                case '-' :
                    dashesRead++;
                    break;

                case '>' :
                    if (dashesRead == 2) {
                        return;
                    }

                default :
                    dashesRead = 0;
            }
        }
    }

    private void skipTag() throws Exception {
        int level = 1;

        while (level > 0) {
            char ch = reader.read();

            switch (ch) {
                case '<' :
                    ++level;
                    break;

                case '>' :
                    --level;
                    break;
            }
        }
    }

    private void skipWhitespace() throws Exception {
        char ch;
        do {
            ch = reader.read();
            switch (ch) {
                case '\t' :
                    break;
                case '\r' :
                    break;
                case '\n' :
                    break;
                case ' ' :
                    break;
                default :
                    reader.unread();
            }
        }
        while ((ch == ' ') || (ch == '\t') || (ch == '\n') || (ch == '\r'));
    }

}
