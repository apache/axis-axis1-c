noinst_LTLIBRARIES = libtransport.la
AM_CPPFLAGS = -Wshadow -Wall -pedantic
libtransport_la_SOURCES = Channel.cpp HttpTransport.cpp Receiver.cpp Sender.cpp \
	Transport.cpp TransportFactory.cpp Url.cpp AxisTransport.cpp

libtransport_la_LIBADD = -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
