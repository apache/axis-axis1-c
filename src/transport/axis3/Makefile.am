lib_LTLIBRARIES = libaxis3_transport.la
SUBDIRS = HTTPChannel @AXIS3SSLBUILD@
AM_CPPFLAGS = $(CPPFLAGS) -DAXISTRACE_LIBRARY
libaxis3_transport_la_SOURCES = ChannelFactory.cpp \
				 HTTPTransport.cpp \
				 HTTPTransportException.cpp \
				 HTTPTransportInstantiator.cpp \
				 URL.cpp
libaxis3_transport_la_LIBADD = -lstdc++
INCLUDES = -I../../../include

