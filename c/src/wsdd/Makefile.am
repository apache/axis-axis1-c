noinst_LTLIBRARIES = libwsdd.la
AM_CPPFLAGS = -Wall
libwsdd_la_SOURCES = WSDDDeployment.cpp \
                WSDDHandler.cpp \
                WSDDService.cpp \
                WSDDTransport.cpp \
                WSDDDocument.cpp \
		WSDDKeywords.cpp

libwsdd_la_LIBADD = -L$(AXISCPP_HOME)/lib/expat -lexpat
INCLUDES = -I$(AXISCPP_HOME)/include
