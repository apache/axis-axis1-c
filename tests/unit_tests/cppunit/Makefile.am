bin_PROGRAMS = runtestsuite
AM_CPPFLAGS = $(CPPFLAGS)
runtestsuite_SOURCES = runCppUnitTests.cpp
runtestsuite_LDADD   =  $(LDFLAGS) ../../../src/transport/axis2/libaxis2_transport.la @CPPUNITLIB@ 

INCLUDES = -I$(AXISCPP_HOME)/include @CPPUNITINC@
