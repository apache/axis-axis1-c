lib_LTLIBRARIES = libserver_engine.la
AM_CPPFLAGS = -Wall -DUSE_EXPAT_PARSER -DUSE_LTDL
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
                ../SharedObject.cpp
		
libserver_engine_la_LIBADD = ../../common/libcommon.la ../../soap/libsoap.la ../../wsdd/libwsdd.la ../../xml/libxml.la -L$(AXISCPP_HOME)/lib/expat -lexpat -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
