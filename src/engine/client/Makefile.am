lib_LTLIBRARIES = libaxiscpp_client.la
AM_CPPFLAGS = -Wall -DUSE_EXPAT_PARSER -DUSE_LTDL -DAXIS_CLIENT_LIB
libaxiscpp_client_la_SOURCES = ../Axis.cpp \
		ClientAxisEngine.cpp \
		../server/ServerAxisEngine.cpp \
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
		Call.cpp
		
libaxiscpp_client_la_LIBADD = ../../common/libcommon.la ../../soap/libsoap.la ../../wsdd/libwsdd.la ../../xml/libxml.la ../../transport/axis/libtransport.la -L$(AXISCPP_HOME)/lib/expat -lexpat -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
