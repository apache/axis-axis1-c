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
	SoapKeywordMapping.cpp \
	SoapParser.cpp

libsoap_la_LIBADD = -L$(AXISCPP_HOME)/lib/expat -lexpat
INCLUDES = -I$(AXISCPP_HOME)/include
