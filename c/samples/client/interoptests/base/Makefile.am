bin_PROGRAMS = interopbase
SUBDIRS =
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
interopbase_SOURCES = InteropBaseClient.cpp InteropTestPortType.cpp  SOAPStruct.cpp 

interopbase_LDADD   =  $(AXISCPP_HOME)/lib/axis/libaxiscpp_client.a $(AXISCPP_HOME)/bin/libaxiscpp_mod.a -L$(AXISCPP_HOME)/lib/expat -lexpat -lltdl -lssl
#interopbase_LDADD   =  $(AXISCPP_HOME)/lib/axis/libaxiscpp_client.a $(AXISCPP_HOME)/bin/libaxiscpp_mod.a -L$(AXISCPP_HOME)/lib/expat -lexpat -ldl -lssl
INCLUDES = -I$(AXISCPP_HOME)/include
