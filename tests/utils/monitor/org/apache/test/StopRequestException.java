/*
 * Copyright 2003-2004 The Apache Software Foundation. 
 * (c) Copyright IBM Corp. 2005
 *  
 * All Rights Reserved Licensed under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0 Unless required by applicable law
 * or agreed to in writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 */

package org.apache.test;

/**
 * @author hawkeye
 * This class is an exception that is used to denote a stop request happening and informing the hierarchy to stop processing. 
 */
public class StopRequestException extends Exception
{
    public StopRequestException(String exceptionMessage)
    {
        super(exceptionMessage);
    }

}
