noinst_LTLIBRARIES = libsoap.la

AM_CPPFLAGS = $(CPPFLAGS)
libsoap_la_SOURCES = Attribute.cpp \
        Namespace.cpp \
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
	apr_base64.c \
	HexCoder.cpp \
        AxisSoapException.cpp \
	SoapAttachment.cpp \
	SoapAttachementHeaders.cpp

libsoap_la_LIBADD = $(LDFLAGS)
INCLUDES = -I../../include
