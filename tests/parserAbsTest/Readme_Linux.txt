Parser Abstraction Layer - Linux 

Test cases for Apache2 and Apache1.3

case 1:Test all samples/tests with each parser   

case 2:Test with parser not in place as specified by $AXIS_HOME/axiscpp.conf	
       
       Parser entry is in $AXIS_HOME/axiscpp.conf as given below
       
       XMLParser:/usr/local/Axis/libs/libaxis_xmlparser.so
       
       Create a temporary folder named temp in your place of choice.
       
       $ mkdir temp
             
       Move $AXIS_HOME/libs/libaxis_xmlparser.so file to the temp directory
        
       $ mv $AXISCPP_HOME/libs/libaxis_xmlparser.so [Place of choice]/temp/        
       
       Run the samples and test.             

case 3:Test with no parser specified in $AXIS_HOME/axiscpp.conf
	
       Move [Place of choice]/temp/libaxis_xmlparser.so file back 
       to original location on $AXIS_HOME/libs/
        
       $ mv [Place of choice]/temp/libaxis_xmlparser.so $AXISCPP_HOME/libs/ 

       Comment XMLParser in $AXIS_HOME/axiscpp.conf as follows:
       
       #XMLParser:/usr/local/Axis/libs/libaxis_xmlparser.so
       
       Run the samples and test.