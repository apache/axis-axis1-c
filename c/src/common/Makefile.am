noinst_LTLIBRARIES = libcommon.la

libcommon_la_SOURCES = Param.cpp TypeMapping.cpp Packet.cpp MessageData.cpp \
 BasicTypeSerializer.cpp ArrayBean.cpp AxisTime.cpp \
 GDefine.cpp AxisUtils.cpp

libcommon_la_LIBADD = -L$(XERCES_HOME)/lib -lxerces-c -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
