noinst_LTLIBRARIES = libengine.la
AM_CPPFLAGS = -Wall -DUSE_EXPAT_PARSER
libengine_la_SOURCES = Axis.cpp \
		AxisEngine.cpp \
                ServerAxisEngine.cpp \
		ClientAxisEngine.cpp \
                HandlerChain.cpp \
                HandlerLoader.cpp \
                HandlerPool.cpp \
		AppScopeHandlerPool.cpp \
		DeserializerPool.cpp \
		RequestScopeHandlerPool.cpp \
		SerializerPool.cpp \
		SessionScopeHandlerPool.cpp \
		SharedObject.cpp
		

libengine_la_LIBADD = -L$(AXISCPP_HOME)/lib/expat -lexpat -lstdc++ -L$(AXISCPP_HOME)/lib/axis -laxiscpp_client
INCLUDES = -I$(AXISCPP_HOME)/include
