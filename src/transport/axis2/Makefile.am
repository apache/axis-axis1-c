lib_LTLIBRARIES = libaxis2_transport.la
SUBDIRS = ipv6 @SSLBUILD@
AM_CPPFLAGS = $(CPPFLAGS)
libaxis2_transport_la_SOURCES = SecureChannel.cpp \
				Channel.cpp \
				URL.cpp \
				Axis2Transport.cpp \
				AxisTransportException.cpp \
				Axis2TransportInstantiator.cpp \
				SSLChannelFactory.cpp

libaxis2_transport_la_LIBADD = -lstdc++
INCLUDES = -I../../../include

