# Makefile for axiscommon
#
#
# Modify the TOPDIR variable to point to the top of the
# directory tree where the Axis_Lib dir may be found.
#

BASE_PATH = ../..
include ../../inc.mk
LOCAL_INCLUDES = -I$(AX_DIR)/src/xml

PACKAGE_SRCS = QName.cpp
	

PACKAGE_OBJS = $(PACKAGE_SRCS:%.cpp=$(AX_OBJ_DIR_COMMON)/%.o)

all: MAKE_LIB

MAKE_LIB:OBJS
	@echo "making xml.a" ;
	$(AX_AR) $(AX_LIB_COMMON) $(AX_OBJ_DIR_COMMON)/*.o
#$(AX_OBJ_DIR_COMMON)/timestamp objects:
#	@( cd $(AX_SRC_DIR) ; $(MAKE) -$(MAKEFLAGS) )

OBJS: $(PACKAGE_OBJS)


clean:
	-@rm -rf $(AX_OBJ_DIR)/xml/*
	-@rm -rf $(OBJS) *~


