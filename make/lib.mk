vpath %.cpp $(DEV_DIR)/src/lattice

TARGET_PROJ := $(INSTALL_DIR)/lib/lib$(PROJ_NAME).a

BUILD_DIR_PROJ := $(BUILD_DIR)/$(PROJ_NAME)

OBJECTS_PROJ := \
	$(BUILD_DIR_PROJ)/DiscreteGaussianSampler.o \
	$(BUILD_DIR_PROJ)/Constants.o \
	$(BUILD_DIR_PROJ)/PolyRingBase.o \
	$(BUILD_DIR_PROJ)/PolyRingFLINT.o

$(OBJECTS_PROJ) : | $(INSTALL_DIR)/include/$(PROJ_NAME) \
										$(INSTALL_DIR)/bin/resources/$(PROJ_NAME) \
										$(INSTALL_DIR)/test/resources/$(PROJ_NAME)

$(INSTALL_DIR)/include/$(PROJ_NAME) :
	$(MKDIR) $@
	$(RSYNC) $(DEV_DIR)/include/$(PROJ_NAME)/ $@/

$(INSTALL_DIR)/bin/resources/$(PROJ_NAME) :
	$(MKDIR) $@
	$(RSYNC) $(DEV_DIR)/resources/$(PROJ_NAME)/ $@/

$(INSTALL_DIR)/test/resources/$(PROJ_NAME) :
	$(MKDIR) $@
	$(RSYNC) $(DEV_DIR)/resources/$(PROJ_NAME)/ $@/

ARTIFACTS += $(INSTALL_DIR)/include/$(PROJ_NAME)
ARTIFACTS += $(INSTALL_DIR)/bin/resources/$(PROJ_NAME)
ARTIFACTS += $(INSTALL_DIR)/test/resources/$(PROJ_NAME)

