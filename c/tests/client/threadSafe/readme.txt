This test case can be used to test the thread safety of the Axis C++ client
engine.
This sample used thread package; and hence would only work on Linux/Unix
platforms.
You are invited to write a threaded test for Windows like this (or a better
one;-) )

I tested this with Axis Java echo sample. (Axis Java service and C++ client)
BTW: echo sample is equivalent to base sample of Axis C++ sample set.

Usage:
You can run the sample by simply running:
./thSafeTest hostname port [use-same]

1. If you run with just hostname and port the client will create a stub object
for each thread.
2. If the third argument is present, then the client will use a single stub
object for multiple threads.
I am not sure if the second scenario is much useful.

The number of threads used is hard coded with NUM_THREADS macro in Client.cpp.
(yes you can improve it by making it a command line option)
If you have set  NUM_THREADS to some number, say 30, and if you want to know
if all threads were successful you could use the following command:
./thSafeTest localhost 8080 | grep Done | nl
and count the Done lines in output to see how many threads succeeded. 
(Note: I have printf( "%ld Done\n", pthread_self() ); as the last line of my
run function)
I mentioned this tip because you will find the output confusing at times if
you are using large number of threads. However I have the thread IDs on the
output so that those you have patience can verify the creation and completion
of the threads one by one.

- Samisa
