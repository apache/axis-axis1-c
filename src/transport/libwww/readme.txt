The implementation of SOAPTransport interface using LibWWW.

The Axis C++ server side fails to work with 100-continue. 
Axis Java is capable of managing 100-continue. 
This is the default mode used in LibWWW. 
I used a macro in Makefile.am to enable/disable 100-continue. 
(use -DHT_EXT_CONTINUE to enable or -UHT_EXT_CONTINUE to disable in 
AM_CPPFLAGS setting)

I observed that the transport is much faster when it is used without 
100-continue. However, to disable 100-continue, LibWWW need to be built 
with –with-extension option  (--./configure with-extension)

You do not need to bother about location of LibWWW headers and libraries, 
provided that you have done the LibWWW installation properly. 
I have used libwww-config in the Makefile.am to pick LibWWW specific settings.

Once you build the library, you could use it by speci the location of the 
lib in $AXIS_HOME/axiscpp.conf file. 
e.g.
Transport_http:/usr/local/Axis/libs/libaxis_LibWWWTransport.so

For more information on LibWWW please see http://www.w3.org/Library/User/

Issues:
The thread test in tests/client/threadSafe fails with this implementation. 
Bit of surfing lead me to http://www.w3.org/Library/User/Architecture/Events.html, 
which says “LibWWW is not posix thread safe but it uses a 'pseudo-thread' 
model based on non-blocking sockets and interleaved IO.” 
Bit of research is needed to figure out how to make this implementation 
thread safe. It remains a TODO as of now.

- Samisa...
