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

import java.util.ArrayList;
import java.util.Hashtable;

public class CLArgParser 
{
    private boolean optionsAreValid = true;
    public Hashtable bag;
    public ArrayList args;

    public CLArgParser(String[] args) 
    {
        this.bag = new Hashtable();
        this.args = new ArrayList();
        
        for (int i = 0; i < args.length; i++) 
        {
            if (!args[i].startsWith("-"))
                this.args.add(args[i]);
            else 
            {
                //System.out.println("args " + args[i].substring(1,2) + " = " + args[i].substring(2));
                String option       = args[i].substring(1, 2);
                String optionValue  = args[i].substring(2);
                
                if (option.equals("l")) 
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
                    if (!"wrapped".equalsIgnoreCase(optionValue))
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
     * This method checks that we do not have extraneous inputs to the tool that we do not support
     * @return true if the args are all supported false otherwise.
     */
    public boolean areOptionsValid()
    {
        return optionsAreValid;
    }    
    
    /**
     * These are direct arguments not - type options
     * @param i
     */
    public String getArgument(int i) 
    {
        Object obj = args.get(i);
        if(obj == null) 
            return null;
        else 
            return (String)obj;
    }

    /**
     * These are direct arguments not - type options
     */
    public int getArgumentCount() 
    {
        return this.args.size();
    }

    public String getOptionBykey(String key) 
    {
        return (String) bag.get(key);
    }

    public boolean isSet(String key) 
    {
        return bag.containsKey(key);
    }
}
