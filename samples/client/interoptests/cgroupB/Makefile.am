bin_PROGRAMS = cgroupb
SUBDIRS =
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
cgroupb_SOURCES = InteropGroupBClient.cpp InteropTestPortTypeB.cpp SOAPArrayStruct.cpp SOAPStruct.cpp SOAPStructStruct.cpp

cgroupb_LDADD   =  -L$(AXISCPP_HOME)/bin -laxiscpp_client -L$(AXISCPP_HOME)/lib/expat -lexpat -lltdl
INCLUDES = -I$(AXISCPP_HOME)/include
