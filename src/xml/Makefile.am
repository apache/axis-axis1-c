noinst_LTLIBRARIES = libxml.la
SUBDIRS = @XERCESCBUILD@ @TSPPBUILD@ 

AM_CPPFLAGS = $(CPPFLAGS) -DAXISTRACE_LIBRARY
libxml_la_SOURCES = QName.cpp Element.cpp Event.cpp StartElement.cpp SimpleAttribute.cpp

INCLUDES = -I../../include
