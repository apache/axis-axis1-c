bin_PROGRAMS = groupb
SUBDIRS =
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
groupb_SOURCES = InteropGroupBClient.cpp InteropTestPortTypeB.cpp SOAPArrayStruct.cpp SOAPStruct.cpp SOAPStructStruct.cpp

groupb_LDADD   =  -L$(AXISCPP_HOME)/bin -laxiscpp_client -L$(AXISCPP_HOME)/lib/expat -lexpat -ldl
INCLUDES = -I$(AXISCPP_HOME)/include
