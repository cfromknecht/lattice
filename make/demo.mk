vpath %.cpp $(DEV_DIR)/src/demo

TARGET_PROJ_DEMO := $(INSTALL_DIR)/bin/$(PROJ_NAME)-demo.x
BUILD_DIR_PROJ_DEMO := $(BUILD_DIR)/$(PROJ_NAME)-demo

$(TARGET_PROJ_DEMO) : | $(INSTALL_DIR)/lib/lib$(PROJ_NAME).a \
												$(INSTALL_DIR)/include/$(PROJ_NAME)-demo

$(TARGET_PROJ_DEMO) : LDFLAGS += $(INSTALL_DIR)/lib/lib$(PROJ_NAME).a

OBJECTS_PROJ_DEMO := $(BUILD_DIR_PROJ_DEMO)/main.o

$(INSTALL_DIR)/include/$(PROJ_NAME)-demo :
	$(MKDIR) $@
	$(RSYNC) $(DEV_DIR)/include/$(PROJ_NAME)-demo/ $@/

ARTIFACTS += $(INSTALL_DIR)/include/$(PROJ_NAME)-demo

