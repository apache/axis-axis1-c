lib_LTLIBRARIES = libaxiscpp_client.la
AM_CPPFLAGS = $(CPPFLAGS) -DAXIS_CLIENT_LIB
libaxiscpp_client_la_SOURCES = ../Axis.cpp \
		ClientAxisEngine.cpp \
		../AxisEngine.cpp \
                ../HandlerChain.cpp \
                ../HandlerLoader.cpp \
                ../HandlerPool.cpp \
                ../AppScopeHandlerPool.cpp \
                ../DeserializerPool.cpp \
                ../RequestScopeHandlerPool.cpp \
                ../SerializerPool.cpp \
                ../SessionScopeHandlerPool.cpp \
                ../SharedObject.cpp \
		Call.cpp \
		Stub.cpp \
                ../AxisEngineException.cpp \
                ../SOAPTransportFactory.cpp \
                ../XMLParserFactory.cpp 
		
libaxiscpp_client_la_LIBADD = $(LDFLAGS) -lpthread ../../common/libcommon.la ../../soap/libsoap.la ../../wsdd/libwsdd.la ../../xml/libxml.la
INCLUDES = -I../../../include
