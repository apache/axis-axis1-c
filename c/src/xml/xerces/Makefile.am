lib_LTLIBRARIES = libaxis_xercesc.la
AM_CPPFLAGS = $(CPPFLAGS)
libaxis_xercesc_la_SOURCES = SoapBinInputStream.cpp \
                           SoapInputSource.cpp \
                           XMLParserXerces.cpp \
                           ParserLoader.cpp \
                           XercesHandler.cpp 

libaxis_xercesc_la_LIBADD =  -L$(XERCESC_HOME)/lib -lxerces-c -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include

