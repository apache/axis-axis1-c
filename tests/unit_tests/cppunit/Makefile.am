bin_PROGRAMS = runtestsuite
#SUBDIRS = transport
AM_CPPFLAGS = $(CPPFLAGS)
runtestsuite_SOURCES = runCppUnitTests.cpp
runtestsuite_LDADD   =  $(LDFLAGS) ../../../src/transport/axis2/libaxis2_transport.la -L${CPPUNIT_HOME}/lib -lcppunit -ldl 

INCLUDES = -I$(AXISCPP_HOME)/include -I${CPPUNIT_HOME}/include
