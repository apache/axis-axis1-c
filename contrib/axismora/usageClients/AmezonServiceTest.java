/*
 * Created on Sep 7, 2003
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
import java.io.FileWriter;
import java.io.Writer;
import java.net.URL;

import com.bookshop.soap.AmazonSearchPort;
import com.bookshop.soap.AmazonSearchServiceLocator;

/**
 * @author administrator
 *
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public class AmezonServiceTest {
	private static int LOAD_REPEAT = 5;
	private static int TEST_REPEAT = 100;
	
	public static void main(String[] args)throws Exception{
		Writer w = new FileWriter("testdata"+System.currentTimeMillis()+".txt",true);
		
		AmazonSearchServiceLocator service1 = new AmazonSearchServiceLocator();
		AmazonSearchPort port1 = service1.getAmazonSearchPort(new URL("http://127.0.0.1:8080/axis/services/AmazonSearchPort"));
				
		AmazonSearchServiceLocator service2 = new AmazonSearchServiceLocator(); 
		AmazonSearchPort port2 = service2.getAmazonSearchPort(new URL("http://127.0.0.1:4444/axismora/servlet/AxisServlet"));
   
		com.bookshop.soap.KeywordRequest req2  = new com.bookshop.soap.KeywordRequest();
		com.bookshop.soap.ModifyShoppingCartItemsRequest req  = new com.bookshop.soap.ModifyShoppingCartItemsRequest();
				 
		

		for(int i=0;i<LOAD_REPEAT;i++){
			System.out.println("calling");
			port1.keywordSearchRequest(req2);
			port2.keywordSearchRequest(req2);
		}

		long[] axis = new long[TEST_REPEAT];
		long[] axis2 = new long[TEST_REPEAT];

		long start,end;
	

		 for(int i=0;i<TEST_REPEAT;i++){
			start = System.currentTimeMillis();
			port1.keywordSearchRequest(req2);
			end = System.currentTimeMillis();
			axis[i] = end - start;
			System.out.println("1 = "+i+" try "+i);

			start = System.currentTimeMillis();
			port2.keywordSearchRequest(req2);
			end = System.currentTimeMillis();
			axis2[i] = end - start;
			System.out.println("2 = "+i+" try "+i);
		}

		long axismeanTot = 0;
		long axis2meanTot = 0;
		for(int i=0;i<TEST_REPEAT;i++){
			axismeanTot = axismeanTot + axis[i];
			axis2meanTot = axis2meanTot + axis2[i];
		}

		float axismean = axismeanTot/TEST_REPEAT;
		float axis2mean = axis2meanTot/TEST_REPEAT;

		float axissdvTot = 0;
		float axis2sdvTot = 0;
		for(int i=0;i<TEST_REPEAT;i++){
			axissdvTot = axissdvTot + (axis[i]-axismean)*(axis[i]-axismean);
			axis2sdvTot = axis2sdvTot + (axis2[i]-axis2mean)*(axis2[i]-axis2mean);
		}

		System.out.println("********************* Result ************************");
		System.out.println("Axis 1.1 ");
		System.out.println("Totel time   : "+axismeanTot+" milliseconds");
		System.out.println("Average      : "+axismean+" miliseconds per request");
		System.out.println("Stdev        : "+axissdvTot/TEST_REPEAT+" miliseconds per request\n");

		System.out.println("Axis2.0");
		System.out.println("Totel time   : "+axis2meanTot+" milliseconds");
		System.out.println("Average      : "+axis2mean+" per request");
		System.out.println("Stdev        : "+axis2sdvTot/TEST_REPEAT+" miliseconds per request\n");

		w.write("********************* Result ************************\n");
		w.write("Axis 1.1\n ");
		w.write("Totel time   : "+axismeanTot+" milliseconds\n");
		w.write("Average      : "+axismean+" miliseconds per request\n");
		w.write("Stdev        : "+axissdvTot/TEST_REPEAT+" miliseconds per request\n\n");

		w.write("Axis2.0\n");
		w.write("Totel time   : "+axis2meanTot+" milliseconds\n");
		w.write("Average      : "+axis2mean+" per request\n");
		w.write("Stdev        : "+axis2sdvTot/TEST_REPEAT+" miliseconds per request\n\n");
		w.flush();

		
	}

}
