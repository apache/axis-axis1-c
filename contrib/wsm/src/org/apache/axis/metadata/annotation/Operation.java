package org.apache.axis.metadata.annotation;

import java.lang.annotation.*;

/**
 * @author Ias
 * @deprecated
 */

@Target({ElementType.METHOD})
@Retention(RetentionPolicy.RUNTIME)
public @interface Operation {
	String value() default "";
}
