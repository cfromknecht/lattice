vpath %.cpp $(DEV_DIR)/src/$(PROJ_NAME)
vpath %.hpp $(DEV_DIR)/include/$(PROJ_NAME)

TARGET_PROJ := $(INSTALL_DIR)/lib/lib$(PROJ_NAME).a

BUILD_DIR_PROJ := $(BUILD_DIR)/$(PROJ_NAME)

OBJECTS_PROJ := \
	$(BUILD_DIR_PROJ)/BernoulliSampler.o \
	$(BUILD_DIR_PROJ)/DiscreteGaussianSampler.o \
  $(BUILD_DIR_PROJ)/EncodedBlock.o \
  $(BUILD_DIR_PROJ)/EncodedFSM.o \
  $(BUILD_DIR_PROJ)/EncodedFSMPublicKey.o \
  $(BUILD_DIR_PROJ)/EncodedFSMSecretKey.o \
	$(BUILD_DIR_PROJ)/FSM.o \
	$(BUILD_DIR_PROJ)/FSMState.o \
	$(BUILD_DIR_PROJ)/FSMTransition.o \
  $(BUILD_DIR_PROJ)/GTrapdoor.o \
  $(BUILD_DIR_PROJ)/Helper.o \
	$(BUILD_DIR_PROJ)/PolyRing.o \
	$(BUILD_DIR_PROJ)/PolyRingBase.o \
	$(BUILD_DIR_PROJ)/PolyRingFLINT.o \
	$(BUILD_DIR_PROJ)/PolyRingMatrix.o \
  $(BUILD_DIR_PROJ)/StreamState.o \
  $(BUILD_DIR_PROJ)/StreamingDelegator.o \
	$(BUILD_DIR_PROJ)/Trapdoor.o

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

