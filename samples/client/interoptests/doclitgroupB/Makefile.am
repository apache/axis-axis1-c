bin_PROGRAMS = interopgroupb
SUBDIRS =
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
interopgroupb_SOURCES = InteropGroupBClient.cpp InteropTestPortTypeB.cpp SOAPArrayStruct.cpp SOAPStruct.cpp SOAPStructStruct.cpp

interopgroupb_LDADD   =  $(AXISCPP_HOME)/lib/axis/libaxiscpp_client.a $(AXISCPP_HOME)/bin/libaxiscpp_mod.a -L$(AXISCPP_HOME)/lib/xerces-c -lxerces-c -ldl
INCLUDES = -I$(AXISCPP_HOME)/include
