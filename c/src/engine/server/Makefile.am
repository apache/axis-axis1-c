lib_LTLIBRARIES = libserver_engine.la
AM_CPPFLAGS = $(CPPFLAGS)
libserver_engine_la_SOURCES = ../Axis.cpp \
		ServerAxisEngine.cpp \
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
                ../../transport/SOAPTransportFactory.cpp \
                ../AxisEngineException.cpp \
                ../SOAPTransportFactory.cpp \
                ../XMLParserFactory.cpp 
		
libserver_engine_la_LIBADD = $(LDFLAGS) ../../common/libcommon.la ../../soap/libsoap.la ../../wsdd/libwsdd.la ../../xml/libxml.la
INCLUDES = -I$(AXISCPP_HOME)/include
