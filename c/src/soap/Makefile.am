noinst_LTLIBRARIES = libsoap.la

AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
libsoap_la_SOURCES = Attribute.cpp \
        BasicNode.cpp \
        CharacterElement.cpp \
        ComplexElement.cpp \
        HeaderBlock.cpp \
        SoapBody.cpp \
        SoapDeSerializer.cpp \
        SoapEnvelope.cpp \
        SoapFault.cpp \
        SoapHeader.cpp \
        SoapMethod.cpp \
        SoapSerializer.cpp \
        URIMapping.cpp \
        XMLStreamHandler.cpp \
	SoapKeywordMapping.cpp

libsoap_la_LIBADD = -L$(AXISCPP_HOME)/lib/xerces-c -lxerces-c
INCLUDES = -I$(AXISCPP_HOME)/include
