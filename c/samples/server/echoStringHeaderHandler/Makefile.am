lib_LTLIBRARIES = libeshhandler.la
SUBDIRS =
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
libeshhandler_la_SOURCES = ESHHandler.cpp EchoStringHeaderHandler.cpp 

libeshhandler_la_LIBADD   =  -L$(AXISCPP_HOME)/lib/xerces-c -lxerces-c -ldl $(AXISCPP_HOME)/release/libaxiscpp_mod.la
INCLUDES = -I$(AXISCPP_HOME)/include -I$(AXISCPP_HOME)/src/common
