bin_PROGRAMS = runtestsuite
#SUBDIRS = transport
AM_CPPFLAGS = $(CPPFLAGS)
runtestsuite_SOURCES = runCppUnitTests.cpp
runtestsuite_LDADD   =  transport/axis2/libaxis2test.la -L${CPPUNIT_HOME}/lib -lcppunit -ldl

INCLUDES = -I$(AXISCPP_HOME)/include -I${CPPUNIT_HOME}/include
