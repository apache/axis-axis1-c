BASE_PATH = .
include inc.mk

all:: $(AX_SO_ENGINE)

#Axis_Release: objects $(AX_LIB)
#	( cd Axis_Release ; $(MAKE) -$(MAKEFLAGS) ; )

#axlib: objects $(AX_LIB)


$(AX_SO_ENGINE): $(AX_DIR_RELEASE)/timestamp
	@echo "Making axisengine.so shared library"
	@#$(AX_SO) $(AX_SO_ENGINE) $(AX_LIB_DIR)/*.a $(AX_INC_DIR_APACHE)/mod_axis.c $(XERCES_LNK_COMMON)
	$(AX_SO) $(AX_SO_ENGINE) $(AX_OBJ_DIR_ENGINE)/*.o $(AX_OBJ_DIR_SOAP)/*.o $(AX_OBJ_DIR_COMMON)/*.o $(AX_OBJ_DIR_APACHE)/*.o $(AX_OBJ_DIR_WSDD)/*.o $(XERCES_LNK_COMMON)
	@#$(AX_SO) AxisEngine $(AX_OBJ_DIR_ENGINE)/*.o $(AX_OBJ_DIR_SOAP)/*.o $(AX_OBJ_DIR_COMMON)/*.o $(AX_OBJ_DIR_WSDD)/*.o $(XERCES_LNK_COMMON)
	@#$(AX_SO) $(AX_SO_ENGINE) $(AX_OBJ_DIR_APACHE)/*.o

$(AX_DIR_RELEASE)/timestamp objects:
	@( cd $(AX_SRC_DIR) ; $(MAKE) -$(MAKEFLAGS) )



# Create the javadoc-like documentation for AXIS Client Lib

#doxygen-docs:
#	( cd $(DOXYGEN_DIR); $(DOXYGEN_EXE_DIR)/doxygen AxisDoc.cfg )

tst:
	@echo AX_LIB_DIR: $(AX_LIB_DIR)
	@echo CFLAGS: $(CFLAGS)
	@echo TARGET_PLATFORM:  $(TARGET_PLATFORM)

clean:
	rm -rf $(AX_LIB_DIR)/*.so
	rm -rf $(AX_DIR_RELEASE)/*


	( cd $(AX_SRC_DIR) ; $(MAKE) -$(MAKEFLAGS) clean )

#clobber: clean
#	( cd Axis_Release ; $(MAKE) -$(MAKEFLAGS) clean )

