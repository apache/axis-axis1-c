package org.apache.axismora.util;

/**
 * @author hemapani
 */
public class ByteArrayStack {
	public byte[][] stack;
	
	private static int initalSize = 20;
	private static int increament = 20;
	private int index = 0;
	
	public ByteArrayStack(){
		stack = new byte[initalSize][];
	}
	
	public void push(byte[] bytes){
		if(index < stack.length){
			stack[index] = bytes;
		}
		byte[][] temp = stack;
		stack = new byte[stack.length + initalSize][];
		System.arraycopy(temp, 0,stack,0,temp.length) ;
		stack[index] = bytes;	
		index ++;
	}
	
	public byte[] pop(){
		if(index == 0 )
			throw new RuntimeException("stack is empty");
		index--;
		byte[] ret = stack[index];
		return ret;
	}
	
}
