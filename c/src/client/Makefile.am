lib_LTLIBRARIES = libaxiscpp_client.la
SUBDIRS = transport
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
libaxiscpp_client_la_SOURCES =	Call.cpp
libaxiscpp_client_la_LIBADD   = ../common/libcommon.la ../engine/client/libclient_engine.la ../soap/libsoap.la ../wsdd/libwsdd.la ../xml/libxml.la ./transport/axis/libtransport.la -lltdl -lstdc++

INCLUDES = -I$(AXISCPP_HOME)/include
