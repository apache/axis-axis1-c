lib_LTLIBRARIES = libaxis2_transport.la
SUBDIRS = ipv6 
AM_CPPFLAGS = $(CPPFLAGS)
libaxis2_transport_la_SOURCES = SecureChannel.cpp \
					  Channel.cpp \
                               URL.cpp \
                               Axis2Transport.cpp \
                               AxisTransportException.cpp

libaxis2_transport_la_LIBADD = -lstdc++
INCLUDES = -I../../../include

