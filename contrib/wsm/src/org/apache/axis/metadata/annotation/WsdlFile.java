package org.apache.axis.metadata.annotation;

import java.lang.annotation.*;

/**
 * @author Ias
 *
 */

@Retention(RetentionPolicy.RUNTIME)
public @interface WsdlFile {
    String value();
}
