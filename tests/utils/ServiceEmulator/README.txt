This directory holds a utility called MockServer. It allows the debugging of problems where the service
is not available e.g. where a user puts a problem on to the user list but cannot provide the service, for what ever reason.

The program listens on a port and waits for a request (from the stub that you have written).
When it receives the request it throws the result away and returns back the complete contents of a given file.
The file must contain all of the http headers, soap headers etc. This file will probably be the captured output of tcpmon.

The server will sit there for x requests where x=numberOfTimesToListen


Usage: java -jar MockServer.jar <port> <responsefile> <numberOfTimesTolisten>