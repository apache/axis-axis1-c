/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

 
/**
 * @author Srinath Perera(hemapani@openource.lk)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Hashtable;

/**
 * Parsers user-specified options on the command.
 * 
 */
public class CLArgParser 
{
    private boolean optionsAreValid = true;
    
    public Hashtable bag  = new Hashtable();
    public ArrayList args = new ArrayList();

    /**
     * Not very good argument parser, could be improved.  For example, there can be no spaces between
     * a property starting with '-' and the property value (i.e. '-o/outdir' and not -o /outdir'). 
     * In addition, only single character options are allowed.
     */
    public CLArgParser(String[] args) 
    {        
        for (int i = 0; i < args.length; i++) 
        {
            if (!args[i].startsWith("-"))
                this.args.add(args[i]);
            else 
            {
                //System.out.println("args " + args[i].substring(1,2) + " = " + args[i].substring(2));
                String option       = args[i].substring(1, 2);
                String optionValue  = args[i].substring(2);
                
                if (option.equals("b"))
                {
                    if (optionValue.length() == 0)
                        optionsAreValid = false;
                }
                else if (option.equals("l")) 
                {
                    if (!optionValue.equals("c++") && !optionValue.equals("c"))
                        optionsAreValid = false;
                }
                else if (option.equals("s"))
                {
                    if (!optionValue.equals("server") 
                            && !optionValue.equals("client") && !optionValue.equals("both"))
                    optionsAreValid = false;
                }
                else if (option.equals("w")) 
                {
                    if (!"wrapped".equalsIgnoreCase(optionValue)
                            && !"unwrapped".equalsIgnoreCase(optionValue))
                        optionsAreValid = false;
                }
                else if (!option.equals("h") && !option.equals("o") 
                         && !option.equals("v") && !option.equals("t"))
                    optionsAreValid = false;
                
                if (optionsAreValid)
                    bag.put(option, optionValue);
                else
                    return;
            }
        }
    }
    
    /**
     * Return output directory.
     * 
     * @return
     * @throws IOException
     */
    public String getOutputDirectory() throws IOException
    {
        String targetoutputLocation = getOptionBykey("o");
        if (targetoutputLocation == null)
            targetoutputLocation = "." + File.separator;
        return (new File(targetoutputLocation)).getCanonicalPath();
    }
    
    /**
     * Return whether to generate wrapper-style
     * 
     * @return
     */
    public boolean isWrapperStyle()
    {
        String wsdlWrapStyle = getOptionBykey("w");
        if (wsdlWrapStyle == null || wsdlWrapStyle.equalsIgnoreCase("wrapped"))
            return true;
        
        return false;
    }
    
    /**
     * Return binding name.
     * 
     * @return
     */
    public String getBinding()
    {
        return getOptionBykey("b");
    }
    
    /**
     * Return target language.
     * @return
     */
    public String getTargetLanguage()
    {
        String language = getOptionBykey("l");
        if (language == null)
            language = "c++";
        return language;
    }

    /**
     * Return verbose information
     * 
     * @return
     */
    public boolean beVerbose()
    {
        return isSet("v");
    }
    
    /**
     * Return verbose information
     * 
     * @return
     */
    public boolean beVeryVerbose()
    {
        String v = getOptionBykey("v");
        if (v != null && v.equals("v"))
            return true;
        
        return false;
    }
    
    /**
     * Return timeout value
     * 
     * @return
     */
    public long getTimeout()
    {
        String t = getOptionBykey("t");
        if (t == null)
            t = "0";
        return Long.parseLong(t);
    }
    
    /**
     * Return target engine.
     * 
     * @return
     */
    public String getTargetEngine()
    {
        String targetEngine = getOptionBykey("s");
        if (targetEngine == null)
            targetEngine = "server";
        
        return targetEngine;
    }
    
    /**
     * Return URI to WSDL
     * 
     * @return
     */
    public String getURIToWSDL()
    {
        if (args.size() > 0)
            return (String)args.get(0);
        
        return null;
    }
    
    /**
     * This method checks that we do not have extraneous inputs to the tool that we do not support
     * 
     * @return true if the args are all supported false otherwise.
     */
    public boolean areOptionsValid()
    {
        return optionsAreValid;
    }    

    /**
     * These are direct arguments not - type options
     */
    public int getArgumentCount() 
    {
        return this.args.size();
    }

    /**
     * Return the value specified for an option.
     * 
     * @param key
     * @return
     */
    public String getOptionBykey(String key) 
    {
        return (String) bag.get(key);
    }

    /**
     * Determines whether an option is set.
     * 
     * @param key
     * @return
     */
    public boolean isSet(String key) 
    {
        return bag.containsKey(key);
    }
}
