lib_LTLIBRARIES = libaxiscpp_mod2.la
AM_CFLAGS = $(CFLAGS)
libaxiscpp_mod2_la_SOURCES = mod_axis2.cpp Apache2Transport.cpp AttachmentHelper.cpp AttachmentHelper.h

libaxiscpp_mod2_la_LIBADD   = $(LDFLAGS) -L$(AXISCPP_HOME)/src/engine/server -lserver_engine -ldl


INCLUDES = @APACHE2INC@ -I../../../include
