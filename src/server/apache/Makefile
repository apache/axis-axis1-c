# Makefile for apache
#
#
# Modify the TOPDIR variable to point to the top of the
# directory tree where the Axis_Lib dir may be found.
#

BASE_PATH = ../../..
include ../../../inc.mk
LOCAL_INCLUDES = -I/usr/local/apache/include

PACKAGE_SRCS = mod_axis.c

PACKAGE_OBJS = $(PACKAGE_SRCS:%.c=$(AX_OBJ_DIR_APACHE)/%.o)

all: MAKE_LIB

MAKE_LIB:OBJS
	@echo "making apache.a" ;
	$(AX_AR) $(AX_LIB_APACHE) $(AX_OBJ_DIR_APACHE)/*.o
#$(AX_OBJ_DIR_APACHE)/timestamp objects:
#	@( cd $(AX_SRC_DIR) ; $(MAKE) -$(MAKEFLAGS) )

OBJS: $(PACKAGE_OBJS)


clean:
	-@rm -rf $(AX_OBJ_DIR)/server/apache/*
	-@rm -rf $(OBJS) *~
