include $(BASE_PATH)/platform.mk



CPPFLAGS = \
	$(LOCAL_INCLUDES) \
	-I. \
	-I$(XERCES_INC_DIR) \
	-I$(AX_DIR)/src

OPTFLAGS=-g

CCFLAGS = $(CFLAGS) $(OPTFLAGS)

LDFLAGS =

COMPILE.cpp = $(CCC) $(CCFLAGS) $(CPPFLAGS) -c
COMPILE.gcc = $(GCC) $(CCFLAGS) $(CPPFLAGS) -c

LINK.cc = $(CCC)

$(AX_OBJ_DIR_WEBSERVICE)/%.o: %.cpp
	$(COMPILE.cpp) -o $@ $<
	@touch $(AX_OBJ_DIR_WEBSERVICE)/timestamp

$(AX_OBJ_DIR_WEBSERVICEWRAPPER)/%.o: %.cpp
	$(COMPILE.cpp) -o $@ $<
	@touch $(AX_OBJ_DIR_WEBSERVICEWRAPPER)/timestamp

$(AX_OBJ_DIR_COMMON)/%.o: %.cpp
	$(COMPILE.cpp) -o $@ $<
	@touch $(AX_OBJ_DIR_COMMON)/timestamp

$(AX_OBJ_DIR_SOAP)/%.o: %.cpp
	$(COMPILE.cpp) -o $@ $<
	@touch $(AX_OBJ_DIR_SOAP)/timestamp

$(AX_OBJ_DIR_XML)/%.o: %.cpp
	$(COMPILE.cpp) -o $@ $<
	@touch $(AX_OBJ_DIR_XML)/timestamp

$(AX_OBJ_DIR_WSDD)/%.o: %.cpp
	$(COMPILE.cpp)  -o $@ $<
	@touch $(AX_OBJ_DIR_WSDD)/timestamp

$(AX_OBJ_DIR_ENGINE)/%.o: %.cpp
	$(COMPILE.cpp) -o $@ $<
	@touch $(AX_OBJ_DIR_ENGINE)/timestamp

$(AX_OBJ_DIR_APACHE)/%.o: %.c
	$(COMPILE.gcc) -o $@ $<
	@touch $(AX_OBJ_DIR_APACHE)/timestamp

$(AX_OBJ_DIR_SECURITY)/%.o: %.cpp
	$(COMPILE.gcc) -o $@ $<
	@touch $(AX_OBJ_DIR_SECURITY)/timestamp


