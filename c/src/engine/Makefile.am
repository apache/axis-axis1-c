noinst_LTLIBRARIES = libengine.la
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
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
		

libengine_la_LIBADD = -L$(AXISCPP_HOME)/lib/xerces-c -lxerces-c -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
