bin_PROGRAMS =doclitbase
SUBDIRS =
AM_CPPFLAGS = -Wshadow -Wall -pedantic -ansi
doclitbase_SOURCES = InteropBaseClient.cpp InteropTestPortType.cpp  SOAPStruct.cpp 

doclitbase_LDADD   = -L$(AXISCPP_HOME)/bin -laxiscpp_client -L$(AXISCPP_HOME)/lib/expat -lexpat -lltdl -lssl -lstdc++
INCLUDES = -I$(AXISCPP_HOME)/include
