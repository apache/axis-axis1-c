package org.apache.axis.client.async.simple;

import org.apache.axis.AxisFault;
import org.apache.axis.AxisEngine;
import org.apache.axis.MessageContext;
import org.apache.axis.client.async.AsyncCall;
import org.apache.axis.client.async.Listener;
import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.utils.JavaUtils;
import org.apache.commons.logging.Log;

/**
 * Implements async processing by spawning a new thread to 
 * handle the Axis engine invocation.
 * 
 * This mechanism is not very scaleable as it does not
 * implement any thread pooling mechanisms.  Threads are 
 * created ad hoc and without limit, potentially maxing out
 * the number of threads available on the system. A more robust 
 * implementation would provide basic thread pooling or work
 * queue functions that can be used to better manage the 
 * various tasks.
 * 
 * @author James Snell (jasnell@us.ibm.com)
 */
public class SimpleAsyncCall
  extends AsyncCall {

  protected static final Log log =
    LogFactory.getLog(SimpleAsyncCall.class.getName());

  private AxisEngine engine;
 
  private SimpleAsyncCall() {
    if (log.isDebugEnabled()) {
      log.debug("Enter: SimpleAsyncCall::init");
    }
    if (log.isDebugEnabled()) {
      log.debug("Exit: SimpleAsyncCall::init");
    }
  }
  
  protected SimpleAsyncCall(AxisEngine engine) {
    if (log.isDebugEnabled()) {
      log.debug("Enter: SimpleAsyncCall::init");
    }
    this.engine = engine;
    if (log.isDebugEnabled()) {
      log.debug("Exit: SimpleAsyncCall::init");
    }
  }

  public void invoke(
    final MessageContext context, 
    final Listener listener) {

    if (log.isDebugEnabled()) {
      log.debug("Enter: SimpleAsyncCall::invoke");
    }
      
    final AxisEngine engine = this.engine;
    final Runnable task = new Runnable() {
      public void run() {
        if (log.isDebugEnabled()) {
          log.debug("Enter: SimpleAsyncCall::invoke(Runnable::run)");
        }
        try {
          engine.invoke(context);
          if (context.getResponseMessage() != null) {
            listener.onResponse(context);
          } else {
          }
        } catch (AxisFault fault) {
          log.error(JavaUtils.getMessage("exception00"), fault);
          try {
            listener.onFault(fault);
          } catch (java.rmi.RemoteException re) {
            log.error(JavaUtils.getMessage("exception00"), re);
          }
        } catch (Exception e) {
          log.error(JavaUtils.getMessage("exception00"), e);
          try {
            listener.onFault(AxisFault.makeFault(e));
          } catch (java.rmi.RemoteException re) {
            log.error(JavaUtils.getMessage("exception00"), re);
          }
        } finally {
          try {
            listener.invokeComplete();
          } catch (java.rmi.RemoteException re) {
            log.error(JavaUtils.getMessage("exception00"), re);
          }
        }
        if (log.isDebugEnabled()) {
          log.debug("Exit: SimpleAsyncCall::invoke(Runnable::run)");
        }
      }
    };
    (new Thread(task)).start();
    if (log.isDebugEnabled()) {
      log.debug("Exit: SimpleAsyncCall::invoke");
    }
  }

}
