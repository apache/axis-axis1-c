lib_LTLIBRARIES = libaxis3_transport_ssl_channel.la
SUBDIRS = 
AM_CPPFLAGS = $(CPPFLAGS) -DAXISTRACE_LIBRARY
libaxis3_transport_ssl_channel_la_SOURCES = HTTPSSLChannel.cpp \
				        HTTPSSLChannelInstantiator.cpp \
					../URL.cpp \
					../HTTPTransportException.cpp
libaxis3_transport_ssl_channel_la_LIBADD = @SSLLIB@ -lstdc++
INCLUDES = -I../../../../include @SSLINC@

