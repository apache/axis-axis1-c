noinst_LTLIBRARIES = libengine.la

libengine_la_SOURCES = Axis.cpp \
                AxisEngine.cpp \
                HandlerChain.cpp \
                HandlerLoader.cpp \
                HandlerPool.cpp \
		AppScopeHandlerPool.cpp \
		DeserializerPool.cpp \
		RequestScopeHandlerPool.cpp \
		SerializerPool.cpp \
		SessionScopeHandlerPool.cpp \
		SharedObject.cpp

libengine_la_LIBADD = -L$(AXISCPP_HOME)/lib/xerces-c -lxerces-c
INCLUDES = -I$(AXISCPP_HOME)/include
