noinst_LTLIBRARIES = libclient_engine.la
AM_CPPFLAGS = -Wall -DUSE_EXPAT_PARSER -DUSE_LTDL
libclient_engine_la_SOURCES = Axis.cpp \
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
                ../SharedObject.cpp
		
libclient_engine_la_LIBADD = -L$(AXISCPP_HOME)/lib/expat -lexpat -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
