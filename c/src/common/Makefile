# Makefile for axiscommon
#
#
# Modify the TOPDIR variable to point to the top of the
# directory tree where the Axis_Lib dir may be found.
#

BASE_PATH = ../..
include ../../inc.mk


PACKAGE_SRCS = AccessBean.cpp \
	AxisException.cpp \
	Debug.cpp \
	BasicTypeSerializer.cpp \
	MessageData.cpp \
	Param.cpp \


PACKAGE_OBJS = $(PACKAGE_SRCS:%.cpp=$(AX_OBJ_DIR_COMMON)/%.o)

all: MAKE_LIB

MAKE_LIB:OBJS
	echo "making common.a" ;
	$(AX_AR) $(AX_LIB_COMMON) $(AX_OBJ_DIR_COMMON)/*.o
#$(AX_OBJ_DIR_COMMON)/timestamp objects:
#	@( cd $(AX_SRC_DIR) ; $(MAKE) -$(MAKEFLAGS) )

OBJS: $(PACKAGE_OBJS)


clean:
	-@rm -rf $(AX_OBJ_DIR)/common/*
	-@rm -rf $(OBJS) *~


