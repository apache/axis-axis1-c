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
public class ServerConnectionFactory
{
    private static Class serverConnectionClass;
    public static void setServerConnectionClass(Class serverConnection)
    {
        ServerConnectionFactory.serverConnectionClass = serverConnection;
        System.out.println( "Setting it to "+serverConnection);
    }
    
    

    /**
     * @param clientSocket
     * @param serviceHostNme
     * @param servicePort
     * @return
     */
    public static TestClientThread getServerConnection(Socket clientSocket, String serviceHostNme, int servicePort)throws NoSuchMethodException, InvocationTargetException,IllegalAccessException, InstantiationException, StopRequestException,ConnectionNotEstablishedException,ConnectException
    {
        if(serverConnectionClass==null)
        {
            // Set it to the default for Axis
            serverConnectionClass = TestClientThread.class;
        }
        //System.out.println( "Server connection class = "+serverConnectionClass);
        
        Class[] constructorArgs = new Class[3];
        constructorArgs[0] = clientSocket.getClass();
        constructorArgs[1] = serviceHostNme.getClass();
        constructorArgs[2] = int.class;
        Constructor constructor = serverConnectionClass.getConstructor(constructorArgs);
        Object[] args = new Object[3];
        args[0] = clientSocket;
        args[1] = serviceHostNme;
        args[2] = new Integer(servicePort); 
        return (TestClientThread)constructor.newInstance(args);
    }

}
