Transport Abstraction Layer - Windows 

Test cases for Apache 2.0 and Apache 1.3


Case 1: Test all samples/tests with transport.

Case 2: Test with transport not in place as specified by axiscpp.conf        
       
       Create a temporary folder named temp in your place of choice.
              
       Cut the AxisTransport.dll from [APACHE_HOME]\Axis\libs\ folder and 
       place it in temp directory.             
       
       Run the samples and test.
       
Case 3: Test with no transport specified in axiscpp.conf        

       Copy AxisTransport.dll from temp directory and paste AxisTransport.dll 
       in [APACHE_HOME]\Axis\libs\ folder.

       Comment "Transport_http" in axiscpp.conf as follows:

       //Transport_http:[APACHE_HOME]\Axis\libs\AxisTransport.dll
       
        Run the samples and test.




