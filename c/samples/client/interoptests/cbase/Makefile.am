bin_PROGRAMS = cbase
SUBDIRS =
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
cbase_SOURCES = InteropBaseClient.c InteropTestPortType.c  SOAPStruct.c

cbase_LDADD   =  -L$(AXISCPP_HOME)/bin -laxiscpp_client -L$(AXISCPP_HOME)/lib/expat -lexpat -lltdl -lssl -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
