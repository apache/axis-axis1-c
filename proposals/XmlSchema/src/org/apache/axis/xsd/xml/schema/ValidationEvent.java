/*
 * ValidationEvent.java
 *
 * Created on September 27, 2001, 3:03 AM
 */

package org.apache.axis.xsd.xml.schema;

import java.util.EventObject;

/**
 *
 * @author  mukund
 */

public class ValidationEvent extends EventObject {

    /** Creates new ValidationEvent */
    public ValidationEvent(Object source) {
		super(source);
    }

}
