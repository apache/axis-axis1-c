Parser Abstraction Layer - Windows 

Test cases for Apache2 and Apache1.3

case 1:Test all samples/tests with each parser 	

case 2:Test with parser not in place as specified by axiscpp.conf	
       
       Create a temporary folder named temp in your place of choice.
              
       Cut the AxisXMLParser.dll from [APACHE_HOME]\Axis\libs\ folder and 
       place it in temp directory.             
       
       Run the samples and test.
       
case 3:Test with no parser specified in axiscpp.conf	

       Copy AxisXMLParser.dll from temp directory and paste AxisXMLParser.dll
       in [APACHE_HOME]\Axis\libs\ folder.

       Comment XMLParser in axiscpp.conf as follows:

       //XMLParser:[APACHE_HOME]\Axis\libs\AxisXMLParser.dll
       
        Run the samples and test.