/*
 * Created on 19-Apr-2006
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package org.apache.test;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.net.ConnectException;
import java.net.Socket;

/**
 * @author hawkeye
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class ClientReturnerFactory
{
    private static Class clientReturnerClass;
    public static void setClientReturnerClass(Class clientReturner)
    {
        ClientReturnerFactory.clientReturnerClass = clientReturner;
    }
    
    

    /**
     * @param clientSocket
     * @param serviceHostNme
     * @param servicePort
     * @return
     */
    public static ClientReturner getClientReturner(Socket clientSocket, Socket serviceSocket, TestClientThread ourParent)throws NoSuchMethodException, InvocationTargetException,IllegalAccessException, InstantiationException, StopRequestException,ConnectionNotEstablishedException,ConnectException
    {
        if(clientReturnerClass==null)
        {
            // Set it to the default for Axis
            clientReturnerClass = ClientReturner.class;
        }
        //System.out.println( "client returner class = "+clientReturnerClass);
        
        Class[] constructorArgs = new Class[3];
        constructorArgs[0] = clientSocket.getClass();
        constructorArgs[1] = Socket.class;
        constructorArgs[2] = ourParent.getClass();
        Constructor constructor = clientReturnerClass.getConstructor(constructorArgs);
        Object[] args = new Object[3];
        args[0] = clientSocket;
        args[1] = serviceSocket;
        args[2] = ourParent; 
        return (ClientReturner)constructor.newInstance(args);
    }

}
