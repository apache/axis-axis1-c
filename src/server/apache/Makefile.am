lib_LTLIBRARIES = libaxiscpp_mod.la
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
libaxiscpp_mod_la_SOURCES = mod_axis.c

libaxiscpp_mod_la_LIBADD   = -L$(AXISCPP_HOME)/src/engine/server -lserver_engine -L$(AXISCPP_HOME)/lib/expat -lexpat -lstdc++ -lltdl

#libaxiscpp_mod_la_LIBADD   = ../../common/libcommon.la ../../engine/server/libserver_engine.la ../../soap/libsoap.la ../../wsdd/libwsdd.la ../../xml/libxml.la -L$(AXISCPP_HOME)/lib/expat -lexpat -lstdc++ -lltdl

#libaxiscpp_mod_la_LIBADD   = ../../common/libcommon.la ../../engine/libengine.la ../../soap/libsoap.la ../../wsdd/libwsdd.la ../../xml/libxml.la -L$(AXISCPP_HOME)/lib/expat -lexpat -ldl -lstdc++


INCLUDES = -I$(AXISCPP_HOME)/include
