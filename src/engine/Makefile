# Makefile for Client
#
#
# Modify the TOPDIR variable to point to the top of the
# directory tree where the Axis_Lib dir may be found.
#

BASE_PATH = ../..
include ../../inc.mk


PACKAGE_SRCS = Axis.cpp \
		AxisEngine.cpp \
		HandlerChain.cpp \
		HandlerLoader.cpp \
		HandlerPool.cpp \
		Main.cpp

PACKAGE_OBJS = $(PACKAGE_SRCS:%.cpp=$(AX_OBJ_DIR_ENGINE)/%.o)

all: MAKE_LIB

MAKE_LIB:OBJS
	@echo "making engine.a" ;
	$(AX_AR) $(AX_LIB_ENGINE) $(AX_OBJ_DIR_ENGINE)/*.o
#$(AX_OBJ_DIR_ENGINE)/timestamp objects:
#	@( cd $(AX_SRC_DIR) ; $(MAKE) -$(MAKEFLAGS) )

OBJS: $(PACKAGE_OBJS)


clean:
	-@rm -rf $(AX_OBJ_DIR)/engine/*
	-@rm -rf $(OBJS) *~

