package org.apache.axis.metadata.annotation;

import java.lang.annotation.*;

/**
 * @author Ias
 *
 */
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
public @interface Protocol {
    boolean httpSoap() default true;
    boolean formGet() default false;
    boolean formPost() default false;
    boolean httpXML() default false;
    EncodingType soapStyle();
}
