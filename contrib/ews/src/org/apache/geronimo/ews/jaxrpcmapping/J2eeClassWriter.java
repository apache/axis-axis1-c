/*
 * Created on 2003. 11. 6.
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package org.apache.geronimo.ews.jaxrpcmapping;

import org.apache.axis.wsdl.toJava.JavaClassWriter;

/**
 * @author Ias (iasandcb@tmax.co.kr)
 * @deprecated no more used by J2eeGeneratorFactory
 */
public abstract class J2eeClassWriter extends JavaClassWriter {
  
  /**
   * Constructor.
   * @param emitter The emitter instance
   * @param fullClassName The fully qualified class name of the class
   *        to be generated.
   * @param type
   */
  
  protected JaxRpcMapper jaxRpcMapper;
  
  protected J2eeClassWriter(
          J2eeEmitter emitter,
          String fullClassName,
          String type) {
      super(emitter, fullClassName, type);
      jaxRpcMapper = emitter.getJaxRpcMapper();
  } // ctor

}
