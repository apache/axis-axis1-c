// SAX exception class.
// http://www.saxproject.org
// No warranty; no copyright -- use this as you will.
// $Id$

package org.xml.sax;

/**
 * Encapsulate a general SAX error or warning.
 *
 * <blockquote>
 * <em>This module, both source code and documentation, is in the
 * Public Domain, and comes with <strong>NO WARRANTY</strong>.</em>
 * See <a href='http://www.saxproject.org'>http://www.saxproject.org</a>
 * for further information.
 * </blockquote>
 *
 * <p>This class can contain basic error or warning information from
 * either the XML parser or the application: a parser writer or
 * application writer can subclass it to provide additional
 * functionality.  SAX handlers may throw this exception or
 * any exception subclassed from it.</p>
 *
 * <p>If the application needs to pass through other types of
 * exceptions, it must wrap those exceptions in a SAXException
 * or an exception derived from a SAXException.</p>
 *
 * <p>If the parser or application needs to include information about a
 * specific location in an XML document, it should use the
 * {@link org.xml.sax.SAXParseException SAXParseException} subclass.</p>
 *
 * @since SAX 1.0
 * @author David Megginson
 * @version 2.0.1 (sax2r2)
 * @see org.xml.sax.SAXParseException
 */
public class SAXException extends Exception {

    public SAXException (String message) {
		super(message);
    }
    
}

// end of SAXException.java
