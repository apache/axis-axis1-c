noinst_LTLIBRARIES = libsoap.la

AM_CPPFLAGS = -Wall
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
        XMLSimpleHandler.cpp \
	SoapKeywordMapping.cpp

libsoap_la_LIBADD = -L$(AXISCPP_HOME)/lib/arabica -lArabica
INCLUDES = -I$(AXISCPP_HOME)/include
