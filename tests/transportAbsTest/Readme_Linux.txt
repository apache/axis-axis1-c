Transport Abstraction Layer - Linux 

Test cases for Apache 2.0 and Apache 1.3


Case 1: Test all samples/tests with transport.

Case 2: Test with transport not in place as specified by axiscpp.conf        
       
       Transport entry is in $AXISCPP_DEPLOY/axiscpp.conf as given below 
       
       Transport_http:/usr/local/Axis/libs/libaxis_transport.so
       
       Create a temporary folder named temp in your place of choice.
       
       $ mkdir temp
             
       Move $AXISCPP_DEPLOY/libs/libaxis_transport.so file to the temp directory
        
       $ mv $AXISCPP_HOME/libs/libaxis_transport.so [Place of choice]/temp/        
       
       Run the samples and test.             

Case 3: Test with no transport specified in axiscpp.conf
        
       Move [Place of choice]/temp/libaxis_transport.so file back 
       to original location on $AXISCPP_DEPLOY/libs/
        
       $ mv [Place of choice]/temp/libaxis_transport.so $AXISCPP_HOME/libs/ 

       Comment "Transport_http" in $AXISCPP_DEPLOY/axiscpp.conf as follows:
       
       #Transport_http:/usr/local/Axis/libs/libaxis_transport.so
       
       Run the samples and test.
