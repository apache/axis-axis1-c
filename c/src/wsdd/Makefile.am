noinst_LTLIBRARIES = libwsdd.la
AM_CPPFLAGS = -Wall -DUSE_EXPAT_PARSER
libwsdd_la_SOURCES = WSDDDeployment.cpp \
                WSDDHandler.cpp \
                WSDDService.cpp \
                WSDDTransport.cpp \
                WSDDDocumentExpat.cpp \
		WSDDKeywords.cpp

libwsdd_la_LIBADD = -L$(AXISCPP_HOME)/lib/expat -lexpat
INCLUDES = -I$(AXISCPP_HOME)/include
