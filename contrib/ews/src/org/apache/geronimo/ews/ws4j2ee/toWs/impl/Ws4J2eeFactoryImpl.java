/*
 * Copyright 2001-2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.geronimo.ews.ws4j2ee.toWs.impl;

import org.apache.geronimo.ews.ws4j2ee.context.ContextFactory;
import org.apache.geronimo.ews.ws4j2ee.context.impl.ContextFactoryImpl;
import org.apache.geronimo.ews.ws4j2ee.parsers.ParserFactory;
import org.apache.geronimo.ews.ws4j2ee.parsers.impl.ParserFactoryImpl;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFactory;
import org.apache.geronimo.ews.ws4j2ee.toWs.Ws4J2eeFactory;

/**
 * @author hemapani@opensource.lk
 */
public class Ws4J2eeFactoryImpl implements Ws4J2eeFactory {
    public ContextFactory getContextFactory() {
        return new ContextFactoryImpl();
    }

    public GenerationFactory getGenerationFactory() {
        return new GenerationFactoryImpl();
    }

    public ParserFactory getParserFactory() {
        return new ParserFactoryImpl();
    }
}
