lib_LTLIBRARIES = libaxis2_ssl_channel.la
AM_CPPFLAGS = $(CPPFLAGS)
libaxis2_ssl_channel_la_SOURCES = SSLChannelLoader.cpp \
                                  OpenSSLChannel.cpp \
                                  AxisSSLChannelException.cpp

libaxis2_ssl_channel_la_LIBADD = @SSLLIB@ -lstdc++
INCLUDES = -I../../../../include @SSLINC@

