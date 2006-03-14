/*
 * Created on 14-Mar-2006
 *
 */
package org.apache.test;

import java.util.Vector;

/**
 * @author hawkeye
 * Connection handlers handleconnections and have a common goal of ensuring that they are 
 * all closed when they need to be
 */
public abstract class ChildHandler
{
    protected Vector children;
    protected ChildHandler()
    {
        System.out.println( "Constructing "+this);
        children=new Vector();
        
    }
    /**
     * This method can be overridden to do specific things for the class but this superclass methodf
     * should always be called  
     *
     */
    protected void close()
    {
        System.out.println( "Closing "+this);
        for(int i=0; i<children.size(); i++)
        {
            ChildHandler child = (ChildHandler)children.remove(i);
            child.close();
        }
        children=null;
        System.out.println( "Closed "+this);
    }
    protected void addChild(ChildHandler handler)
    {
        children.add(handler);
    }
    
    public String toString()
    {
        String name = this.getClass().getName(); 
        return name;
    }
    public void finalize()throws Throwable
    {
        System.out.println( "Destroying: "+this);
        super.finalize();
    }
}
