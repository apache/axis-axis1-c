bin_PROGRAMS = groupB
SUBDIRS =
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
groupB_SOURCES = InteropGroupBClient.cpp InteropTestPortTypeB.cpp SOAPArrayStruct.cpp SOAPStruct.cpp SOAPStructStruct.cpp

groupB_LDADD   =  -L$(AXISCPP_HOME)/bin -laxiscpp_client -L$(AXISCPP_HOME)/lib/expat -lexpat -lltdl
INCLUDES = -I$(AXISCPP_HOME)/include
