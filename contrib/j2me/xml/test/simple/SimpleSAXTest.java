package test.simple;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.Locator;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;
import org.xml.sax.helpers.DefaultHandler;

/**
 * 
 * A simple tester for J2ME JAXP
 *  
 * @author Ias (iasandcb@tmax.co.kr)
 */
public class SimpleSAXTest {

    public static void main(String[] args) throws Exception {
        SAXParserFactory factory = SAXParserFactory.newInstance();
        SAXParser parser = factory.newSAXParser();
        Writer out = new OutputStreamWriter(System.out);
        SimpleHandler handler = new SimpleHandler(out);
        // For testing on a specific platform, you need to modify the following line.
        InputSource is = new InputSource("file:/home/zaurus/Documents/java/test/simple/sample.xml");
        try {
            parser.parse(is, handler);
        }
        catch (SAXParseException se) {
            se.printStackTrace();
            System.out.println(se.getMessage());
            System.out.println(se.getLineNumber());
            System.out.println(se.getColumnNumber());
        }
    }

    private static class SimpleHandler extends DefaultHandler {
        private Writer out;
        private String indentString = " "; // Amount to indent
        private int indentLevel = 0;
        private StringBuffer textBuffer;

        SimpleHandler(Writer out) {
            this.out = out;
        }

        private void emit(String s) throws SAXException {
            try {
                out.write(s);
                out.flush();
            }
            catch (IOException e) {
                throw new SAXException("I/O error");
            }
        }

        private void echoText() throws SAXException {
            if (textBuffer == null)
                return;
            nl();
            emit("CHARS:   ");
            String s = "" + textBuffer;
            if (!s.trim().equals(""))
                emit(s);
            textBuffer = null;
        }

        private void nl() throws SAXException {
            String lineEnd = System.getProperty("line.separator");
            try {
                out.write(lineEnd);
                for (int i = 0; i < indentLevel; i++)
                    out.write(indentString);
            }
            catch (IOException e) {
                throw new SAXException("I/O error");
            }
        }

        public void setDocumentLocator(Locator locator) {
            try {
                emit("LOCATOR SET");
                nl();
            }
            catch (Exception e) {
                // Ignore errors
            }
        }

        public void startDocument() throws SAXException {
            emit("<?xml version='1.0' encoding='UTF-8'?>");
            nl();
        }

        public void endDocument() throws SAXException {
            try {
                nl();
                out.flush();
            }
            catch (IOException e) {
                throw new SAXException("I/O error");
            }
        }

        public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
            echoText();
            indentLevel++;
            nl();
            emit("ELEMENT: ");
            String eName = localName; // element name
            if ("".equals(eName))
                eName = qName; // not namespaceAware
            emit("<" + eName);
            if (attributes != null) {
                for (int i = 0; i < attributes.getLength(); i++) {
                    String aName = attributes.getLocalName(i); // Attr name
                    if ("".equals(aName))
                        aName = attributes.getQName(i);
                    nl();
                    emit("   ATTR: ");
                    emit(aName);
                    emit("\t\"");
                    emit(attributes.getValue(i));
                    emit("\"");
                }
            }
            if (attributes.getLength() > 0)
                nl();
            emit(">");
        }

        public void endElement(String uri, String localName, String qName) throws SAXException {
            echoText();
            nl();
            emit("END_ELM: ");
            String eName = localName; // element name
            if ("".equals(eName))
                eName = qName; // not namespaceAware
            emit("</" + eName + ">");
            indentLevel--;
        }

        public void startPrefixMapping(String prefix, String uri) throws SAXException {
            System.out.println("start prefix uri " + uri);
            System.out.println("start prefix prefix " + prefix);
        }

        public void endPrefixMapping(String prefix) throws SAXException {
            System.out.println("end prefix prefix " + prefix);
        }

        public void characters(char[] ch, int start, int length) throws SAXException {
            String s = new String(ch, start, length);
            if (textBuffer == null) {
                textBuffer = new StringBuffer(s);
            }
            else {
                textBuffer.append(s);
            }
        }

        public void ignorableWhitespace(char buf[], int offset, int Len) throws SAXException {
            nl();
            emit("IGNORABLE");
        }

        public void processingInstruction(String target, String data) throws SAXException {
            nl();
            emit("PROCESS: ");
            emit("<?" + target + " " + data + "?>");
            nl();
        }

        public void skippedEntity(String name) throws SAXException {
            nl();
            emit("SKIPPED ENTITY: ");
            emit("<!" + name + ">");
            nl();
        }
    }
}
