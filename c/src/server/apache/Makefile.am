lib_LTLIBRARIES = libaxiscpp_mod.la
AM_CFLAGS = $(CFLAGS)
libaxiscpp_mod_la_SOURCES = mod_axis.c

libaxiscpp_mod_la_LIBADD   = $(LDFLAGS) -L$(AXISCPP_HOME)/src/engine/server -lserver_engine -lltdl

INCLUDES = -I$(AXISCPP_HOME)/include
