bin_PROGRAMS = sslclient
SUBDIRS =
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
#sslclient_SOURCES = InteropBaseClient.c InteropTestPortType.c  SOAPStruct.c
sslclient_SOURCES = InteropBaseClient.c InteropTestPortType.c

sslclient_LDADD   =  -L$(AXISCPP_HOME)/bin -laxiscpp_client -L$(AXISCPP_HOME)/lib/expat -lexpat -lltdl -lssl -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
