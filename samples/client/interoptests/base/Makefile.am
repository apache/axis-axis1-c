bin_PROGRAMS = base
SUBDIRS =
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
base_SOURCES = InteropBaseClient.cpp InteropTestPortType.cpp  SOAPStruct.cpp 

base_LDADD   =  -L$(AXISCPP_HOME)/bin -laxiscpp_client -L$(AXISCPP_HOME)/lib/expat -lexpat -lltdl -lssl
INCLUDES = -I$(AXISCPP_HOME)/include
