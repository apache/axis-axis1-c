# Makefile for Client
#
#
# Modify the TOPDIR variable to point to the top of the
# directory tree where the Axis_Lib dir may be found.
#

BASE_PATH = ../..
include ../../inc.mk



PACKAGE_SRCS = Attribute.cpp \
	BasicNode.cpp \
	CharacterElement.cpp \
	ComplexElement.cpp \
	HeaderBlock.cpp \
	SoapBody.cpp \
	SoapDeSerializer.cpp \
	SoapEnvelope.cpp \
	SoapFault.cpp \
	SoapHeader.cpp \
	SoapMethod.cpp \
	SoapSerializer.cpp \
	TypeMapping.cpp \
	URIMapping.cpp \
	XMLStreamHandler.cpp


PACKAGE_OBJS = $(PACKAGE_SRCS:%.cpp=$(AX_OBJ_DIR_SOAP)/%.o)

all: MAKE_LIB

MAKE_LIB:OBJS
	@echo "making soap.a" ;
	$(AX_AR) $(AX_LIB_SOAP) $(AX_OBJ_DIR_SOAP)/*.o
#$(AX_OBJ_DIR_SOAP)/timestamp objects:
#	@( cd $(AX_SRC_DIR) ; $(MAKE) -$(MAKEFLAGS) )

OBJS: $(PACKAGE_OBJS)


clean:
	-@rm -rf $(AX_OBJ_DIR)/soap/*
	-@rm -rf $(OBJS) *~
