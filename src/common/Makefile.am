noinst_LTLIBRARIES = libcommon.la
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
libcommon_la_SOURCES = Param.cpp TypeMapping.cpp Packet.cpp MessageData.cpp \
 BasicTypeSerializer.cpp ArrayBean.cpp AxisTime.cpp \
 GDefine.cpp AxisUtils.cpp AxisTrace.cpp AxisException.cpp AxisConfig.cpp

libcommon_la_LIBADD = -L$(AXISCPP_HOME)/lib -lxerces-c -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
