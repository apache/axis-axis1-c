AUTOMAKE_OPTIONS = gnu	
if TRUE
#bin_PROGRAMS = tspp
#tspp_SOURCES = main.cpp XmlPullParser.cpp FileInputStream.cpp unicode.cpp

if UNICODE_OUT
INCLUDES = -I../include -DUNICODE_OUT -ggdb3
else
INCLUDES = -I../include -ggdb3
endif

lib_LTLIBRARIES = libguththila.la
libguththila_la_SOURCES = XmlPullParser.cpp FileInputStream.cpp unicode.cpp
endif












