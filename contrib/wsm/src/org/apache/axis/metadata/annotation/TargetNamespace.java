package org.apache.axis.metadata.annotation;

import java.lang.annotation.*;

/**
 * @author Ias
 * @deprecated
 */

@Retention(RetentionPolicy.RUNTIME)
public @interface TargetNamespace {
    String value();
}
