all:

PROJ_NAME := lattice

# directories
DEV_DIR := .
BUILD_DIR := $(DEV_DIR)/build
INSTALL_DIR := $(DEV_DIR)/install
THIRD_PARTY_DIR := $(DEV_DIR)/third_party
GTEST_DIR := $(THIRD_PARTY_DIR)/gtest

# commands
SHELL := /bin/sh
CXX := g++-4.9 # g++ (LLVM) does not support OPM
LD := $(CXX)
CP := cp -r
RSYNC := rsync -iCau --exclude='\.*' --delete
AR := ar
RM := rm -f
ZIP := zip
MKDIR := mkdir -p

# flags
INCLUDE_FLAGS := 	-I$(INSTALL_DIR)/include \
									-I$(DEV_DIR)/include \
                  -I$(THIRD_PARTY_DIR) \
									-I$(GTEST_DIR)/include \
									-I$(GTEST_DIR) \
                  -I/usr/local/include

FLAGS := -m64 -Wall -Wextra -Wshadow -Werror -pedantic
CXXFLAGS := -std=c++11 -Weffc++ $(FLAGS)
LDFLAGS := 	-L$(INSTALL_DIR)/lib \
						-lm \
						-lpthread \
						-lmpfr \
            -lgmp \
            -L/usr/local/lib \
            -lflint \
            -L$(THIRD_PARTY_DIR)/flint


DEBUG_FLAGS := -g -D _DEBUG
RELEASE_FLAGS := -O2 -D NDEBUG

# cleanup
ARTIFACTS := 

