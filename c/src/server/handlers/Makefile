# Makefile for axishandlers
#
#
# Modify the TOPDIR variable to point to the top of the
# directory tree where the Axis_Lib dir may be found.
#

BASE_PATH = ../../..
include ../../../inc.mk

PACKAGE_SRCS = LogHandler.cpp \
		LogAccessCount.cpp

PACKAGE_OBJS = $(PACKAGE_SRCS:%.cpp=$(AX_OBJ_DIR_HANDLERS)/%.o)

all: MAKE_LIB

MAKE_LIB:OBJS
	echo "making handlers.a" ;
	$(AX_AR) $(AX_LIB_HANDLERS) $(AX_OBJ_DIR_HANDLERS)/*.o
	@echo "making libcount.so shared library" ;
	$(AX_SO) $(AX_SO_HANDLERS) $(AX_OBJ_DIR_HANDLERS)/*.o -ldl -lstdc++

#$(AX_OBJ_DIR_HANDLERS)/timestamp objects:
#	@( cd $(AX_SRC_DIR) ; $(MAKE) -$(MAKEFLAGS) )

OBJS: $(PACKAGE_OBJS)


clean:
	-@rm -rf $(AX_OBJ_DIR)/server/handlers/*
	-@rm -rf $(OBJS) *~


