lib_LTLIBRARIES = libaxiscpp_mod.la
AM_CFLAGS = $(CFLAGS)
libaxiscpp_mod_la_SOURCES = mod_axis.cpp ApacheTransport.cpp

libaxiscpp_mod_la_LIBADD   = $(LDFLAGS) -L$(AXISCPP_HOME)/src/engine/server -lserver_engine -ldl

INCLUDES = -I$(AXISCPP_HOME)/include
