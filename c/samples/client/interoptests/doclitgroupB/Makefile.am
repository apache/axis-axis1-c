bin_PROGRAMS = doclitgroupB
SUBDIRS =
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
doclitgroupB_SOURCES = InteropGroupBClient.cpp InteropTestPortTypeB.cpp SOAPArrayStruct.cpp SOAPStruct.cpp SOAPStructStruct.cpp

doclitgroupB_LDADD   = -L$(AXISCPP_HOME)/bin -laxiscpp_client -L$(AXISCPP_HOME)/lib/expat -lexpat -lltdl -lssl -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
