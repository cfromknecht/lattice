vpath %.cpp $(DEV_DIR)/test

TARGET_PROJ_TEST := $(INSTALL_DIR)/test/$(PROJ_NAME)-test.x
BUILD_DIR_PROJ_TEST := $(BUILD_DIR)/$(PROJ_NAME)-test

$(TARGET_PROJ_TEST) : $(INSTALL_DIR)/lib/lib$(PROJ_NAME).a
$(TARGET_PROJ_TEST) : LDFLAGS += --coverage $(INSTALL_DIR)/lib/lib$(PROJ_NAME).a

OBJECTS_PROJ_TEST := \
	$(BUILD_DIR_PROJ_TEST)/gtest-all.o \
	$(BUILD_DIR_PROJ_TEST)/$(PROJ_NAME)-test.o \
	$(BUILD_DIR_PROJ_TEST)/PolyRingTest.o \
	$(BUILD_DIR_PROJ_TEST)/PolyRingMatrixTest.o

$(OBJECTS_PROJ_TEST) : CXXFLAGS += -fprofile-arcs -ftest-coverage

vpath %.cc $(GTEST_DIR)/src

$(OBJECTS_PROJ_TEST) : CXXFLAGS := $(filter-out -Weffc++,$(CXXFLAGS))
$(BUILD_DIR_PROJ_TEST)/gtest-all.o : CXXFLAGS := $(filter-out -Wextra,$(CXXFLAGS))

$(OBJECTS_PROJ_TEST) : CXXFLAGS := $(filter-out -std=c++11,$(CXXFLAGS))
$(OBJECTS_PROJ_TEST) : CXXFLAGS := -std=gnu++0x $(CXXFLAGS)

