bin_PROGRAMS = interopbase
SUBDIRS =
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
interopbase_SOURCES = InteropBaseClient.c InteropTestPortType.c  SOAPStruct.c

interopbase_LDADD   =  $(AXISCPP_HOME)/lib/axis/libaxiscpp_client.a $(AXISCPP_HOME)/bin/libaxiscpp_mod.a -L$(AXISCPP_HOME)/lib/expat -lexpat -ldl -lssl -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
