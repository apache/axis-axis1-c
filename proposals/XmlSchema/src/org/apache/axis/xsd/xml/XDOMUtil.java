/*
 * XDOMUtil.java
 *
 * Created on February 21, 2002, 12:33 AM
 */

package org.apache.axis.xsd.xml;

import org.w3c.dom.*;

/**
 *
 * @author  mukund
 */
public class XDOMUtil extends DOMUtil {
    
    /** Creates a new instance of XDOMUtil */
    private XDOMUtil() {
    }
    
    public static Element getFirstChildElementNS(Node parent, String uri) {

        // search for node
        Node child = parent.getFirstChild();
        while (child != null) {
            if (child.getNodeType() == Node.ELEMENT_NODE) {
                String childURI = child.getNamespaceURI();
                if (childURI != null && childURI.equals(uri) ) {
                    return (Element)child;
                }
            }
            child = child.getNextSibling();
        }

        // not found
        return null;
        
    }
    
    public static Element getNextSiblingElementNS(Node node, String uri) {
        // search for node
        Node sibling = node.getNextSibling();
        while (sibling != null) {
            if (sibling.getNodeType() == Node.ELEMENT_NODE) {
                String siblingURI = sibling.getNamespaceURI();
                if (siblingURI != null && siblingURI.equals(uri) ) {
                    return (Element)sibling;
                }
            }
            sibling = sibling.getNextSibling();
        }

        // not found
        return null;
        
    }
    
}
