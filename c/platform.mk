# platform.mk defines platform-dependent variables
# for compiling Axis Client lib:
#
# TARGET_PLATFORM
# CCC
# CFLAGS

# AX_DIR
# AX_LIB_DIR
# AX_LIB
# AX_LIB_WEBSERVICE
# AX_LIB_WEBSERVICEWRAPPER
# AX_SO_WEBSERVICEWRAPPER
# AX_SO_ENGINE
# AX_LIB_COMMON
# AX_LIB_SOAP
# AX_LIB_XML
# AX_LIB_SECURITY
# AX_LIB_HANDLERS
# AX_LNK
# AX_OBJ_DIR
# AX_OBJ_DIR_WEBSERVICE
# AX_OBJ_DIR_WEBSERVICEWRAPPER
# AX_OBJ_DIR_COMMON
# AX_OBJ_DIR_SOAP
# AX_OBJ_DIR_XML
# AX_OBJ_DIR_WSDD
# AX_OBJ_DIR_ENGINE
# AX_OBJ_DIR_APACHE
# AX_OBJ_DIR_SECURITY
# AX_OBJ_DIR_HANDLERS
# AX_DIR_RELEASE
# AX_DIR_AXIS

# AX_INC_DIR_COMMON
# AX_INC_DIR_SOAP
# AX_INC_DIR_XML
# AX_INC_DIR_WSDD
# AX_INC_DIR_ENGINE
# AX_INC_DIR_APACHE
# AX_INC_DIR_SECURITY
# AX_INC_DIR_HANDLERS

# AX_AR
# AX_SO
# AX_TEST_LINK_FLAGS
# AX_TEST_LINK_LIBS
# AX_LD_LIB_PATH

# XERCES_INC_DIR
# XERCES_LIB_DIR
# XERCES_LNK
# LINK.cc
# LD_LIB_PATH_NAME

# To run a test compile with gcc on a Solaris machine, add
# "GCC_TEST_COMPILE=TRUE" to the gmake command line, eg
# "gmake GCC_TEST_COMPILE=TRUE optimal".  It won't link, but
# it doesn't need to... we just want to see what warnings
# gcc emits.  It would be a good idea to add "-k" to the
# gmake command line also, since some files don't compile,
# mostly because of the lack of vector<>::at() in gcc.

#DOXYGEN_DIR = ./doxygen
#DOXYGEN_EXE_DIR = /usr/local/doxygen/bin

#SC_DIR=$(shell pwd)
TOPDIR	:= $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)

SC_DIR=$(BASE_PATH)

AX_DIR = $(SC_DIR)

TARGET_PLATFORM = $(shell $(AX_DIR)/getplatform.sh PLATFORMNAME)
TARGET_DEFINE   = $(shell $(AX_DIR)/getplatform.sh PLATFORMDEFINE)
TARGET_DEFINE	= AXIS_LINUX

COMPILER_BASE   = /usr/tools/compilers/$(TARGET_PLATFORM)
LOCAL_BASE      = /usr/local/$(TARGET_PLATFORM)

AX_SRC_DIR        = $(AX_DIR)/src
AX_LIB_DIR        = $(AX_DIR)/lib/$(TARGET_PLATFORM)
AX_OBJ_DIR        = $(AX_DIR)/bin/$(TARGET_PLATFORM)
AX_OBJ_DIR_WEBSERVICE = $(AX_OBJ_DIR)/server/samples/webservice
AX_OBJ_DIR_WEBSERVICEWRAPPER = $(AX_OBJ_DIR)/server/samples/webservicewrapper
AX_OBJ_DIR_COMMON = $(AX_OBJ_DIR)/common
AX_OBJ_DIR_SOAP   = $(AX_OBJ_DIR)/soap
AX_OBJ_DIR_XML   = $(AX_OBJ_DIR)/xml
AX_OBJ_DIR_WSDD   = $(AX_OBJ_DIR)/wsdd
AX_OBJ_DIR_ENGINE   = $(AX_OBJ_DIR)/engine
AX_OBJ_DIR_APACHE   = $(AX_OBJ_DIR)/server/apache
AX_OBJ_DIR_SECURITY   = $(AX_OBJ_DIR)/security
AX_OBJ_DIR_HANDLERS   = $(AX_OBJ_DIR)/server/handlers
AX_DIR_RELEASE   = $(AX_DIR)/release/$(TARGET_PLATFORM)
AX_DIR_AXIS = $(AX_DIR)/axis

AX_INC_DIR_COMMON = $(AX_SRC_DIR)/common
AX_INC_DIR_SOAP = $(AX_SRC_DIR)/soap
AX_INC_DIR_WSDD = $(AX_SRC_DIR)/wsdd
AX_INC_DIR_ENGINE = $(AX_SRC_DIR)/engine
AX_INC_DIR_APACHE = $(AX_SRC_DIR)/apache

AX_LIB_WEBSERVICE=$(AX_OBJ_DIR_WEBSERVICE)/webservice.a
AX_LIB_WEBSERVICEWRAPPER=$(AX_OBJ_DIR_WEBSERVICEWRAPPER)/webservicewrapper.a

AX_LIB_COMMON = $(AX_LIB_DIR)/common.a
AX_LIB_SOAP=$(AX_LIB_DIR)/soap.a
AX_LIB_XML=$(AX_LIB_DIR)/xml.a
AX_LIB_WSDD=$(AX_LIB_DIR)/wsdd.a
AX_LIB_ENGINE=$(AX_LIB_DIR)/engine.a
AX_LIB_APACHE=$(AX_LIB_DIR)/apache.a
AX_LIB_SECURITY=$(AX_LIB_DIR)/security.a
AX_LIB_HANDLERS=$(AX_LIB_DIR)/handlers.a
AX_SO_ENGINE=$(AX_DIR_RELEASE)/libaxiscpp_mod.so
AX_SO_HANDLERS=$(AX_DIR_AXIS)/handlers/custom/libcount.so
AX_SO_WEBSERVICEWRAPPER=$(AX_DIR_AXIS)/webservices/libwebservice.so
AX_LNK = -L$(AX_LIB_DIR) -l.

APACHE_INC_DIR = /usr/local/apache/include


XERCES_INC_DIR    = $(XERCES_HOME)/include
XERCES_LIB_DIR    = $(XERCES_HOME)/lib/
XERCES_LNK_COMMON = -L$(XERCES_LIB_DIR) -lxerces-c -ldl -lstdc++


LINK.cc = $(CCC)

.SUFFIXES: .cpp .c .h .hpp

#AXIS_FLAGS = -D__EXTENSIONS__ -D_UNIX -D$(TARGET_DEFINE) -D_REENTRANT -D_PTHREADS

ifeq "$(TARGET_DEFINE)" "AXIS_SUNOS"
    SUNLIB              = $(COMPILER_BASE)/lib

ifeq "$(GCC_TEST_COMPILE)" "TRUE"
    COMPILER_HOME       = /usr/local/bin
    CCC                 = $(COMPILER_HOME)/gcc
    CFLAGS              = $(AXIS_FLAGS) -fPIC -D_REENTRANT -D_PTHREADS $(LFS_COMPILE_FLAGS)
else
    COMPILER_HOME       = $(COMPILER_BASE)/bin
    CCC                 = $(COMPILER_HOME)/CC
    CFLAGS              = -mt -KPIC $(AXIS_FLAGS) $(LFS_COMPILE_FLAGS)
endif

    LFS_COMPILE_FLAGS   = $(shell getconf LFS_CFLAGS)
    AX_AR               = $(CCC) -xar -o
    AX_TEST_LINK_FLAGS  =
    AX_TEST_LINK_LIBS   =

    LIB_LINK.cc         = $(CCC)
    XERCES_LNK          = $(XERCES_LNK_COMMON) -lsocket

    LD_LIB_PATH_NAME    = LD_LIBRARY_PATH
else
# set default compiler to gcc on Linux
    TARGET_PLATFORM	= linux
    COMPILER_HOME       = /usr/bin
    CCC                 = $(COMPILER_HOME)/g++
    GCC                 = $(COMPILER_HOME)/gcc
    CFLAGS              = $(AXIS_FLAGS) -fPIC
    AX_AR               = ar cr
	  #AX_AR               = g++ -shared -o
    #AX_SO               = gcc -shared -Wl,-soname,libmod_axis.so -ldl -o
    AX_SO               = g++ -shared -o
	#AX_SO               = g++ -DEXE -ldl -o
    LIB_LINK.cc         = $(CCC)

endif

#solaris
#gcc version    CFLAGS = $(AXIS_FLAGS) -D$(TARGET_DEFINE) -fPIC -D_REENTRANT -D_PTHREADS $(LFS_COMPILE_FLAGS)
#gcc version    AX_LINK_ARGS = `lorder $(AX_OBJ_DIR)/*.o | /usr/ccs/bin/tsort`
#gcc version    AX_TEST_LINK_FLAGS = -l stdc++ -l pthread

# AIX code is always position independent, so it doesn't need -fPIC

ifeq "$(TARGET_PLATFORM)" "AIX_4.3"
    COMPILER_HOME       = $(COMPILER_BASE)/bin
    CCC                 = $(COMPILER_HOME)/xlC_r
    XERCES_LNK          = $(XERCES_LNK_COMMON)

    LFS_COMPILE_FLAGS   = -D_LARGE_FILES -D_LARGE_FILE_API
    CFLAGS              = $(AXIS_FLAGS) $(LFS_COMPILE_FLAGS) -qrtti=all
    AX_AR               = touch $(AX_LIB); echo lib not used:  ar -cr
    AX_TEST_LINK_FLAGS  = -brtl
    AX_TEST_LINK_LIBS   = $(XERCES_LNK)

    LIB_LINK.cc         = $(COMPILER_HOME)/makeC++SharedLib_r

    AXIS_EXPORT      = -EAxis_client_lib.exp

# AIX linker can't resolve all references from Axis_client_lib.a,
# so rather than using Axis_client_lib.a, we link in the object
# files contained in it directly.
    AX_LNK              = $(AX_OBJ_DIR)/*.o

    LD_LIB_PATH_NAME    = LIBPATH
endif

ifeq "$(TARGET_PLATFORM)" "NOPLATFORM"
    CFLAGS=NOVALUE
endif

AX_LD_LIB_PATH = /lib:/usr/lib:/usr/local/lib:$(AX_LIB_DIR):$(XERCES_LIB_DIR)

