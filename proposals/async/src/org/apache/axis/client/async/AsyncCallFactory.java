package org.apache.axis.client.async;

import org.apache.axis.AxisEngine;

/**
 * @author James Snell (jasnell@us.ibm.com)
 */
public interface AsyncCallFactory {

  public AsyncCall createInstance(AxisEngine engine);

}
