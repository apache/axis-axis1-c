noinst_LTLIBRARIES = libtransport.la
AM_CPPFLAGS = -Wshadow -Wall -pedantic -D_SSL_ENABLED_
libtransport_la_SOURCES = Channel.cpp HttpTransport.cpp Receiver.cpp Sender.cpp \
        Transport.cpp TransportFactory.cpp Url.cpp AxisTransport.cpp SecureChannel.cpp

libtransport_la_LIBADD = -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include

