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
 
package org.apache.geronimo.ews;

import java.io.File;

import junit.framework.TestCase;

/**
 * Abstract base class for test cases.
 *
 * @author <a href="jason@zenplex.com">Jason van Zyl</a>
 */
public abstract class AbstractTestCase
	extends TestCase 
{
	protected String testDir = "test/";
	protected String sampleDir = "samples/";
	protected String outDir = "target/generated/samples/";
	/** 
	 * Basedir for all file I/O. Important when running tests from
	 * the reactor.
	 */
	public String basedir = System.getProperty("basedir");
    
	/**
	 * Constructor.
	 */
	public AbstractTestCase(String testName)
	{
		super(testName);
	}
    
	/**
	 * Get test input file.
	 *
	 * @param path Path to test input file.
	 */
	public String getTestFile(String path)
	{
		return new File(basedir,path).getAbsolutePath();
	}
}

