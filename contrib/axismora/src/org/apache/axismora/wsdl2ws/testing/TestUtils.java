package org.apache.axismora.wsdl2ws.testing;

import java.util.HashMap;
import java.util.Random;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class TestUtils {
	public static String ENDPOINT_URI = "http://127.0.0.1:8080/axismora/servlet/AxisServlet";
	private static Random rand = new Random();
	private HashMap initializeMap = new HashMap();
	
	public static int getRandomInt(){
		return rand.nextInt();
	}
	
	public static int getRandomInt(int d){
			return rand.nextInt(d);
		}
	
	public static char getRandomchar(){
		return (char)rand.nextInt();
	}

	public static long getRandomLong(){
		return rand.nextLong();
	}
	public static short getRandomShort(){
		return (short)rand.nextInt(200);
	}
	
	public static boolean getRandomBoolean(){
			return rand.nextBoolean();
	}
	public static double getRandomDouble(){
			return rand.nextDouble();
	}
	
	public static float getRandomFloat(){
				return rand.nextFloat();
	}
	public static byte[] getRandomBytes(){
			return "fix this".getBytes();
	}
	public static byte getRandomByte(){
			return '1';
	}
	
	public static String getRandomString(){
		int length = rand.nextInt(50);
		char[] chars = new char[length];
		for(int i = 0;i<length;i++){
			chars[i] = (char)rand.nextInt(24);
		}
		return new String(chars);
	}
	
	
}
