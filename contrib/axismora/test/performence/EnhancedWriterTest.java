package performence;

import java.io.BufferedOutputStream;
import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Writer;

import org.apache.axismora.encoding.ser.EnhancedWriter;

/**
 * @author hemapani
 */
public class EnhancedWriterTest {
	public static void main(String[] args)throws IOException{
		System.out.println("started");
		String[] write = new String[10000];
		for(int i = 0;i<write.length;i++){
			write[i] = "Hello Line is "+i + "\n";
		}
		
		Writer out = new PrintWriter(new BufferedWriter(new FileWriter("temp.txt"))); 
		
		long start = System.currentTimeMillis();
		
		for(int i = 0;i<write.length;i++){
			out.write(write[i]);
		}
		
		long end = System.currentTimeMillis();
		
		System.out.println("\nnoraml use " +  end +" - " + start +" ="+(end-start));
		out.close();

		
		Writer out2 = new EnhancedWriter(new BufferedOutputStream(new FileOutputStream("temp2.txt")));
		
		start = System.currentTimeMillis();
		char[] buffer = new char[1024];
		int index = 0;
		for(int i = 0;i<write.length;i++){
			out2.write(write[i]);
		}
		end = System.currentTimeMillis();
		System.out.println("\noptimized use " +  end +" - " + start +" = "+(end-start));
		out2.close();
	}

}
