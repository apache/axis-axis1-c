noinst_LTLIBRARIES = libsoap.la
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
        XMLStreamHandler.cpp

libsoap_la_LIBADD = -L$(XERCES_HOME)/lib -lxerces-c
INCLUDES = -I$(XERCES_HOME)/include
