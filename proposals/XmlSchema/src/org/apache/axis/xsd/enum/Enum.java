/*
 * Enum.java
 *
 * Created on October 12, 2001, 3:25 PM
 */

package org.apache.axis.xsd.enum;

/**
 *
 * @author  mukund
 */

public abstract class Enum {
    
    public static String NULL = "NULL";

    protected Enum(String value) {
	setValue(value);
    }

    protected Enum() {
	this(NULL);
    }

    protected abstract String[] getValues();

    protected String value = NULL;

    public void setValue(String value) {
	if( value.equals(Enum.NULL) )
	    this.value = Enum.NULL;
	else {
	    String values[] = getValues();
	    for( int i = 0; i < values.length; i++ ) {
		if( values[i].equals(value) ) {
		    this.value = value;
		    break;
		}
		if( i == values.length - 1 )
		    throw new EnumValueException("Bad Enumeration value");
	    }
	}
    }

    public String getValue() {
	return value;
    }

    public String toString() {
	return value;
    }
    
    public boolean equals(Object what) {
        return what.getClass().equals(this.getClass()) && 
			((Enum)what).getValue().equals(this.getValue());
    }
    
    public static class EnumValueException extends RuntimeException {
	public EnumValueException(String mesg) {
	    super(mesg);
	}
    }
    
    protected static final int index(String value, String values[]) {
        for( int i = 0; i < values.length; i++ ) {
            if( value.equals(values[i]) )
                return i;
        }
        return -1;
    }
}

