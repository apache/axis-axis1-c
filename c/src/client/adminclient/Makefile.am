bin_PROGRAMS = adminclient
SUBDIRS =
AM_CPPFLAGS = $(CPPFLAGS)
adminclient_SOURCES = AxisAdminService.cpp AdminClient.cpp

adminclient_LDADD   =  $(LDFLAGS)  -L$(AXISCPP_HOME)/bin -laxiscpp_client -lltdl
INCLUDES = -I$(AXISCPP_HOME)/include
