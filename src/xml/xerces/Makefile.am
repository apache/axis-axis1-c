lib_LTLIBRARIES = libaxis_xercesc.la
AM_CPPFLAGS = $(CPPFLAGS) -DAXISTRACE_LIBRARY
libaxis_xercesc_la_SOURCES = SoapBinInputStream.cpp \
                           SoapInputSource.cpp \
                           XMLParserXerces.cpp \
                           ParserLoader.cpp \
                           XercesHandler.cpp \
			   ../AxisParseException.cpp

libaxis_xercesc_la_LIBADD =  @XERCESCLIB@ -lstdc++
INCLUDES = @XERCESCINC@ -I../../../include

