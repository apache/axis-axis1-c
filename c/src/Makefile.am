lib_LTLIBRARIES = libaxiscpp_mod.la
SUBDIRS = common engine server soap wsdd xml
AM_CPPFLAGS = -Wall -DUSE_EXPAT_PARSER
libaxiscpp_mod_la_SOURCES =	
libaxiscpp_mod_la_LIBADD   = ./common/libcommon.la ./engine/libengine.la ./server/apache/libapache.la ./soap/libsoap.la ./wsdd/libwsdd.la ./xml/libxml.la -L$(AXISCPP_HOME)/lib/expat -lexpat -ldl -lstdc++

#LDADD = -L$(XERCES_HOME)/lib/arabica -lArabica -ldl -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
