lib_LTLIBRARIES = libaxis_tspp.la
AM_CPPFLAGS = $(CPPFLAGS)
libaxis_tspp_la_SOURCES = AxisInputStream.cpp \
			   Buffer.cpp \
			   ParserLoader.cpp \
			   XMLParserAxis.cpp \
			   XmlPullParser.cpp \
			   XmlPullParserException.cpp \
			   ../AxisParseException.cpp

libaxis_tspp_la_LIBADD =  @XERCESCLIB@ -lstdc++
INCLUDES = @XERCESCINC@ -I../../../include

