lib_LTLIBRARIES = libaxiscpp_client.la
SUBDIRS = transport
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
libaxiscpp_client_la_SOURCES =	Call.cpp
libaxiscpp_client_la_LIBADD   = ./transport/axis/libtransport.la -ldl -lstdc++

INCLUDES = -I$(AXISCPP_HOME)/include -I$(AXISCPP_HOME)/src/common
