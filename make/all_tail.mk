BUILD_DIRS := $(sort $(BUILD_DIR_PROJ) \
							$(BUILD_DIR_PROJ_DEMO) \
							$(BUILD_DIR_PROJ_TEST))

TARGETS := 	$(sort $(TARGET_PROJ) \
						$(TARGET_PROJ_DEMO) \
						$(TARGET_PROJ_TEST))

all : $(TARGETS)
lib : $(TARGET_PROJ)
demo : $(TARGET_PROJ_DEMO) 
test : $(TARGET_PROJ_TEST)

COMPILE_CXX = $(CXX) -c -o $@ -fopenmp $< $(INCLUDE_FLAGS) $(CXXFLAGS) $(DEBUG_FLAGS)

release : COMPILE_CXX = $(CXX) -c -o $@ -fopenmp $< $(INCLUDE_FLAGS) $(CXXFLAGS) $(RELEASE_FLAGS)
release : all

%.a : | $(INSTALL_DIR)/lib $(INSTALL_DIR)/include
	$(AR) rcs $@ $^

%.x : | $(INSTALL_DIR)/bin $(INSTALL_DIR)/bin/resources
	$(CXX) -o $@ -fopenmp $^ $(LDFLAGS)

%-test.xx : | $(INSTALL_DIR)/test $(INSTALL_DIR)/test/resources
	$(CXX) -o $@ -fopenmp $^ $(LDFLAGS)
	$@

$(TARGET_PROJ) : $(OBJECTS_PROJ)
$(TARGET_PROJ_DEMO) : $(OBJECTS_PROJ_DEMO)
$(TARGET_PROJ_TEST) : $(OBJECTS_PROJ_TEST)

$(OBJECTS_PROJ) $(patsubst %.o,%.d, $(OBJECTS_PROJ)) : | $(BUILD_DIR_PROJ)
$(OBJECTS_PROJ_DEMO) $(patsubst %.o,%.d, $(OBJECTS_PROJ_DEMO)) : | $(BUILD_DIR_PROJ_DEMO)
$(OBJECTS_PROJ_TEST) $(patsubst %.o,%.d, $(OBJECTS_PROJ_TEST)) : | $(BUILD_DIR_PROJ_TEST)

OBJECTS := $(sort $(OBJECTS_PROJ) $(OBJECTS_PROJ_DEMO) $(OBJECTS_PROJ_TEST))
$(OBJECTS) : %.o : %.d

# templates
$(addsuffix /%.d, $(BUILD_DIRS)) : %.hpp
	$(SHELL) -ec "$(CXX) -std=c++11 $(INCLUDE_FLAGS) -I$(DEV_DIR)/include -MM $< \
	| sed 's|$(notdir $*)\.o[ ]*:|$*\.o $@ :|g' > $@; \
	[ -s $@ ] || $(RM) $@"

# source code
$(addsuffix /%.d, $(BUILD_DIRS)) : %.cpp
	$(SHELL) -ec "$(CXX) -std=c++11 $(INCLUDE_FLAGS) -I$(DEV_DIR)/include -MM $< \
	| sed 's|$(notdir $*)\.o[ ]*:|$*\.o $@ :|g' > $@; \
	[ -s $@ ] || $(RM) $@"

# gtest-all.cc
$(addsuffix /%.d, $(BUILD_DIRS)) : %.cc
	$(SHELL) -ec "$(CXX) -std=c++11 $(INCLUDE_FLAGS) -I$(DEV_DIR)/include -MM $< \
	| sed 's|$(notdir $*)\.o[ ]*:|$*\.o $@ :|g' > $@; \
	[ -s $@ ] || $(RM) $@"

$(BUILD_DIR_PROJ)/%.o : %.cpp ; $(COMPILE_CXX)
$(BUILD_DIR_PROJ)/%.o : %.hpp ; $(COMPILE_CXX)

$(BUILD_DIR_PROJ_DEMO)/%.o : %.cpp ; $(COMPILE_CXX)

$(BUILD_DIR_PROJ_TEST)/%.o : %.cpp ; $(COMPILE_CXX)
$(BUILD_DIR_PROJ_TEST)/%.o : %.cc ; $(COMPILE_CXX)


ifneq ($(MAKECMDGOALS), clean)
-include $(patsubst %.o,%.d,$(OBJECTS))
endif

clean :
	$(RM) -rf $(TARGETS) $(BUILD_DIRS) $(ARTIFACTS)

install: release
	$(MKDIR) -p /usr/local/lib
	$(MKDIR) -p /usr/local/include/$(PROJ_NAME)
	$(CP) $(TARGET_PROJ) /usr/local/lib
	$(CP) $(DEV_DIR)/include/$(PROJ_NAME)/* /usr/local/include/$(PROJ_NAME)

$(BUILD_DIRS) $(INSTALL_DIR)/bin \
							$(INSTALL_DIR)/bin/resources \
							$(INSTALL_DIR)/include \
							$(INSTALL_DIR)/lib \
							$(INSTALL_DIR)/test/resources \
							$(INSTALL_DIR)/test :
	$(MKDIR) $@

.PHONY : all clean release lib demo test fresh

.PRECIOUS : %-test.x

