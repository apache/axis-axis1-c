lib_LTLIBRARIES = libaxis3_transport_channel.la
SUBDIRS = 
AM_CPPFLAGS = $(CPPFLAGS) -DAXISTRACE_LIBRARY
libaxis3_transport_channel_la_SOURCES = HTTPChannel.cpp \
				        HTTPChannelInstantiator.cpp \
                                        ../URL.cpp \
                                        ../HTTPTransportException.cpp
libaxis3_transport_channel_la_LIBADD = -lstdc++
INCLUDES = -I../../../../include

