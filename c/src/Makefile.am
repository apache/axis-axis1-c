lib_LTLIBRARIES = libaxiscpp_mod.la
SUBDIRS = common engine server soap wsdd xml
libaxiscpp_mod_la_SOURCES =	
libaxiscpp_mod_la_LIBADD   = ./common/libcommon.la ./engine/libengine.la ./server/apache/libapache.la ./soap/libsoap.la ./wsdd/libwsdd.la ./xml/libxml.la -L$(AXISCPP_HOME)/lib/xerces-c -lxerces-c -ldl -lstdc++

#LDADD = -L$(XERCES_HOME)/lib -lxerces-c -ldl -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
