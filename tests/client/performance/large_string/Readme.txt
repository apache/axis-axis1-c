The largestring test allows to send a multiple number of echoString webservice requests to 
the interop base service. With each request, a string of length equal to current iteration number is 
sent .the n the number of iterations can be specified an argument to the test. 

This test will check two aspects. The size of a payload and repated invocations of soap method 
from one stub object.


Building and running on win32
To build the sample and run generate stubs in to a folder named gen_src beneath this folder and 
compile using the alltests workspace, and then run.