lib_LTLIBRARIES = libaxis_transport.la
AM_CPPFLAGS = $(CPPFLAGS)
libaxis_transport_la_SOURCES = Channel.cpp \
                               HttpTransport.cpp \
                               Receiver.cpp Sender.cpp \
                               Transport.cpp \
                               TransportFactory.cpp \
                               Url.cpp \
                               AxisTransport.cpp \
                               AxisTransportException.cpp

libaxis_transport_la_LIBADD = -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include

