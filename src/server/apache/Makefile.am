lib_LTLIBRARIES = libaxiscpp_mod.la
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
libaxiscpp_mod_la_SOURCES = mod_axis.c

libaxiscpp_mod_la_LIBADD   = -L$(AXISCPP_HOME)/src/engine/server -lserver_engine -L$(AXISCPP_HOME)/lib/expat -lexpat -lstdc++ -lltdl

INCLUDES = -I$(AXISCPP_HOME)/include
