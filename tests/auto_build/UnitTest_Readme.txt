Testing of the client can be done without the need for a server to be in place. 
In order to do this you have to have an expected response file. This file must contain exactly what
you expect the server to send back to the client (there are numerous examples in the test directories)


Running against no server:
In order to run the tests without a server you must do the following:

1.	In your test.<platform>.properties file change the mockserver value to "true" i.e.
	e.g. mockserver=true
	This will run all the requested tests against the pseudo server and not against the real endpoint set in the test file.
	
2. You then must ensure that for each test in your test list you are trying to run that the test has a suitable response file 
	(see "creating a test" below)
	
3. Run the test.xml ANT script as per usual.




Creating a test:
In order to create a new test you must do the following 3 things:

1. If necessary create a new <testname>.xml file
	e.g. (from tests/auto_build/testcases/client/cpp/CalculatorDoc.xml)
	<test>
	    <name>CalculatorDoc</name>
    	<description>CalculatorDoc</description>
	    <clientLang>cpp</clientLang>
	    <clientCode>CalculatorDocClient.cpp</clientCode>
	    <wsdl>CalculatorDoc.wsdl</wsdl>
	    <expected>
	        <output>
	            CalculatorDoc.cpp.out
	        </output>
	    </expected>
		<endpoint>http://localhost:80/Calculator/services/Calculator</endpoint>
	</test>

2. Add the <serverResponse> file  to the test xml in the <expected> output :
	e.g. (from tests/auto_build/testcases/client/cpp/CalculatorDoc.xml)
	<test>
	    <name>CalculatorDoc</name>
	    ...
 	    <expected>
	        <output>
	            CalculatorDoc.cpp.out
	        </output>
			<serverResponse>
				CalculatorDoc_ServerResponse.expected
			</serverResponse>
	    </expected>
		<endpoint>http://localhost:80/Calculator/services/Calculator</endpoint>
	</test>
	
3. Place the expected server response into the output directory
	e.g. tests/auto_build/testcases/output/CalculatorDoc_serverResponse.expected
	The server response file has a length after the HTTP headers but before the SOAP envelope. This is the
	length in hex of the remainder of the message. Since this is awkward to calculate manually, it may 
	be left as ### and the mock server will automatically calculate the length.
	
Please see the file tests/auto_build/testcases/output/ComplexLists_ServerResponse.expected for an example of 
a test that calls a server multiple times.