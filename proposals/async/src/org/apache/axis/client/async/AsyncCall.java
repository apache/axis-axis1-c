package org.apache.axis.client.async;

import org.apache.axis.AxisEngine;
import org.apache.axis.MessageContext;
import org.apache.axis.client.async.simple.SimpleAsyncCallFactory;

/**
 * Provides a pluggable mechanism for implementing (client-side)
 * asynchronous support.  
 * 
 * @author James Snell (jasnell@us.ibm.com)
 */
public abstract class AsyncCall {

  public static final String ASYNC_CALL_PROPERTY = 
    "org.apache.axis.client.async.AsyncCall"; // MUST be a Boolean

  public static final String ASYNC_CALL_LISTENER = 
    "org.apache.axis.client.async.Listener"; // MUST be a Listener impl

  private static AsyncCallFactory factory;
  
  public static synchronized void setAsncCallFactory(
    AsyncCallFactory factory) {
      AsyncCall.factory = factory;
  }

  /**
   * This will return an instance of the configured or default
   * AsyncCallFactory.  The factory is configured either by
   * specifying a Java system property or Axis engine config
   * property (both with the name 
   * "org.apache.axis.client.async.AsyncCallFactory") whose value
   * is the classname of the impl.  If no factory is configured,
   * the default SimpleAsyncCallFactory will be used.  This will
   * create an instance of SimpleAsyncCall that will handle async
   * requests by simple spawning a new thread.
   */
  public static synchronized AsyncCallFactory getAsyncCallFactory(
    AxisEngine engine) {
    if (AsyncCall.factory == null) {
      String factoryName = System.getProperty(
        AsyncCallFactory.class.getName());
      if (factoryName == null) {
        factoryName = (String)engine.getOption(AsyncCallFactory.class.getName());
      }
      if (factoryName != null) {
        try {
          AsyncCall.factory = 
            (AsyncCallFactory)Class.forName(factoryName).newInstance();
        } catch (Exception e) {}
      }
      if (AsyncCall.factory == null)
        AsyncCall.factory = new SimpleAsyncCallFactory();
    }
    return AsyncCall.factory;
  }

  /**
   * Uses the configured AsyncCallFactory to create a new instance
   */
  public static AsyncCall instance(AxisEngine engine) {
    return getAsyncCallFactory(engine).createInstance(engine);
  }

  /**
   * Invokes the asynchronous call.  Implementations of this
   * method MUST be nonblocking.
   */
  public abstract void invoke(
    MessageContext context,
    Listener listener);

}
