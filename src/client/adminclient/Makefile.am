bin_PROGRAMS = adminclient
SUBDIRS =
AM_CPPFLAGS = $(CPPFLAGS)
adminclient_SOURCES = AxisAdminService.cpp AdminClient.cpp

adminclient_LDADD   =  $(LDFLAGS) ../../engine/client/libaxiscpp_client.la -ldl
INCLUDES = -I$(AXISCPP_HOME)/include
