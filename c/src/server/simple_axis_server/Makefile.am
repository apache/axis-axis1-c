bin_PROGRAMS = simple_axis_server
SUBDIRS =
AM_CPPFLAGS = $(CPPFLAGS)
simple_axis_server_SOURCES = ServerHelper.cpp SimpleAxisServer.cpp 

simple_axis_server_LDADD = $(LDFLAGS) -L$(AXISCPP_HOME)/src/engine/server -lserver_engine -lltdl
INCLUDES = -I$(AXISCPP_HOME)/include
