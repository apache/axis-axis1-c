bin_PROGRAMS = cbase
SUBDIRS =
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
cbase_SOURCES = InteropBaseClient.c InteropTestPortType.c  SOAPStruct.c

cbase_LDADD   =  $(AXISCPP_HOME)/bin/libaxiscpp_client.a -L$(AXISCPP_HOME)/lib/expat -lexpat -lltdl -lssl -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
