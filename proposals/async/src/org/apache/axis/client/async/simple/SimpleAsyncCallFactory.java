package org.apache.axis.client.async.simple;

import org.apache.axis.AxisEngine;
import org.apache.axis.client.async.AsyncCall;
import org.apache.axis.client.async.AsyncCallFactory;

/**
 * @author James Snell (jasnell@us.ibm.com)
 */
public class SimpleAsyncCallFactory
  implements AsyncCallFactory {

  public AsyncCall createInstance(AxisEngine engine) {
    return new SimpleAsyncCall(engine);
  }

}
