# Makefile for Client
#
#
# Modify the TOPDIR variable to point to the top of the
# directory tree where the Axis_Lib dir may be found.
#

BASE_PATH = ../..
include ../../inc.mk


PACKAGE_SRCS = WSDDDeployment.cpp \
		WSDDHandler.cpp \
		WSDDService.cpp \
		WSDDTransport.cpp \
		WSDDDocument.cpp

PACKAGE_OBJS = $(PACKAGE_SRCS:%.cpp=$(AX_OBJ_DIR_WSDD)/%.o)

all: MAKE_LIB

MAKE_LIB:OBJS
	@echo "making wsdd.a" ;
	$(AX_AR) $(AX_LIB_WSDD) $(AX_OBJ_DIR_WSDD)/*.o
#$(AX_OBJ_DIR_WSDD)/timestamp objects:
#	@( cd $(AX_SRC_DIR) ; $(MAKE) -$(MAKEFLAGS) )

OBJS: $(PACKAGE_OBJS)

clean:
	-@rm -rf $(AX_OBJ_DIR)/wsdd/*
	-@rm -rf $(OBJS) *~
