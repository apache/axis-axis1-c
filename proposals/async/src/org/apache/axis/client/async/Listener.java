package org.apache.axis.client.async;

import java.rmi.Remote;
import java.rmi.RemoteException;
import org.apache.axis.MessageContext;
import org.apache.axis.AxisFault;

/**
 * This is the asynchronous call back interface used by the 
 * Call object to receive responses and faults from the 
 * AsyncCall implementation.  By default, the Call object
 * will use default impl's of this interface to handle the 
 * basic waitForReturnValue() and getAsyncStatus() operations.
 * Advanced users can specify their own callback interface 
 * implementations by setting the ASYNC_CALL_LISTENER property
 * on the Call object.  By doing so, the user becomes responsible
 * for handling the state of the async call and all of the async
 * support functions (getAsyncStatus, getReturnValue, 
 * getReturnedFault, waitForReturnValue) become useless.
 * 
 * @author James Snell (jasnell@us.ibm.com)
 */
public interface Listener
  extends Remote {

  /**
   * Indicates that the async invocation is complete.
   * The Call object should reset it's state to ASYNC_READY
   */
  public void invokeComplete() 
    throws RemoteException;

  /**
   * Indicates that a response message has been received
   */
  public void onResponse(
    MessageContext context)
      throws RemoteException;
  
  /**
   * Indicates that a fault has been received
   */
  public void onFault(
    AxisFault fault)
      throws RemoteException;

}
