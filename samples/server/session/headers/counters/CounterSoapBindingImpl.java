/**
 * CounterSoapBindingImpl.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2beta Mar 31, 2004 (12:47:03 EST) WSDL2Java emitter.
 */

package counters;

public class CounterSoapBindingImpl implements counters.Counter_Port{

    int board = 97;

    public int count(int in0) throws java.rmi.RemoteException {
	board = board + in0;
        return board;
    }

}
