include ../conf/common.mk
include ../conf/boost_standard.mk
#include ../conf/boost_stow.mk
#include ../conf/cplex.mk

#############################################################################	
# Custom flags
#############################################################################

#CPPFLAGS += -DNO_CPLEX #-DNDEBUG

#############################################################################	

NAME = test
# Directories
INC_DIR   = ./src
SRC_DIR   = ./src
BUILD_DIR = ./build
STAGE_DIR = ../stage

CPPFLAGS += -I$(STAGE_DIR)/include -I$(INC_DIR)
CCFLAGS  += -fPIC 
CXXFLAGS += -fPIC
#LDFLAGS  += -L$(STAGE_DIR)/lib -Wl,-R$(STAGE_DIR)/lib
LDFLAGS  += -L$(STAGE_DIR)/lib
LDLIBS   += 
# SYSLIBS  += -lpcre  -lbz2 -lz -lboost_date_time -lboost_filesystem -lboost_program_options -lboost_serialization
SYSLIBS  += -lz -lboost_date_time -lboost_filesystem -lboost_program_options -lboost_serialization

EXE_SRCS := \
	$(shell find $(SRC_DIR) -follow -type f -name '*.cpp') \
	$(shell find $(SRC_DIR) -follow -type f -name '*.c')

EXES = $(NAME).exe

##############################################################################

BUILD_EXES = $(patsubst %, $(BUILD_DIR)/%, $(EXES))
BUILD_EXE_OBJS= $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%.o, $(basename $(EXE_SRCS)))

BUILD_OBJS    = $(BUILD_EXE_OBJS) 
BUILD_DEPS    = $(BUILD_OBJS:.o=.d)
BUILD_DEP_MK  = $(BUILD_DIR)/depend.mk
BUILD_SUBDIRS = $(sort $(dir $(BUILD_OBJS)))

STAGE_EXES    = $(patsubst $(BUILD_DIR)/bin/%,$(STAGE_DIR)/%, $(basename $(BUILD_EXES)))

STAGE_BIN_DIRS = $(STAGE_DIR)/bin $(sort $(dir $(STAGE_EXES)))

# Commands

DEPEND.cpp  = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(DEPFLAGS)
COMPILE.cpp = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
LINK.cpp    = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(CXX_LDFLAGS)

DEPEND.c    = $(CC) $(CCFLAGS) $(CPPFLAGS) $(DEPFLAGS)
COMPILE.c   = $(CC) $(CCFLAGS) $(CPPFLAGS) -c
LINK.c      = $(CC) $(CCFLAGS) $(CPPFLAGS) $(LDFLAGS)

##############################################################################
#
# Rules
#  

$(BUILD_DIR)/%.d : $(SRC_DIR)/%.cpp
	$(DEPEND.cpp) $< -MT $(@:.d=.o) -MF $@

$(BUILD_DIR)/%.d : $(SRC_DIR)/%.c
	$(DEPEND.c) $< -MT $(@:.d=.o) -MF $@
	
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(COMPILE.cpp) $< -o $@

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(COMPILE.c) $< -o $@

##############################################################################	
#
# Generic Targets
#

.PHONY: dump config depend
	  
all: $(BUILD_EXES)

config:
	mkdir -p $(BUILD_DIR) $(BUILD_SUBDIRS)
	
depend: $(BUILD_DEPS)
	rm -f $(BUILD_DEP_MK)
	for dep in $(BUILD_DEPS); do echo "-include $$dep" >> $(BUILD_DEP_MK); done
				
depclean:
	rm -f $(BUILD_DEPS)
			
objclean: 
	rm -f $(BUILD_OBJS)

clean: objclean
	
distclean: objclean depclean
	rm -f $(BUILD_DEP_MK)
	rm -f $(BUILD_EXES)

stage-exe: $(BUILD_EXES)
	$(INSTALL) -d $(STAGE_BIN_DIRS)
	for exe in $(patsubst $(BUILD_DIR)/%, %, $(BUILD_EXES)); do \
		echo "installing $(STAGE_DIR)/bin/$$exe" ; \
		$(INSTALL) $(BUILD_DIR)/$$exe $(STAGE_DIR)/bin/$$exe ; \
	done		
			
stage: stage-exe

unstage-exe:
	for exe in $(patsubst $(BUILD_DIR)/bin/%, %, $(BUILD_EXES)); do \
		echo "removing $(STAGE_DIR)/bin/$$exe" ; \
		rm -f $(STAGE_DIR)/bin/$$exe ; \
	done		
	
unstage: unstage-exe

##############################################################################	
#
# Custom Targets
#

$(BUILD_DIR)/$(EXES): $(BUILD_EXE_OBJS)
	$(LINK.cpp) -o $@ $(BUILD_EXE_OBJS) $(LDLIBS) $(SYSLIBS)

run: run_standard.sh $(BUILD_DIR)/$(EXES)
	./run_standard.sh

gdb: $(BUILD_DIR)/$(EXES)
	@echo r --asn 5511 --bgp data/test/bgptopology.txt --igp data/test/isis.txt --solve_method benders
	gdb $(BUILD_DIR)/$(EXES)

##############################################################################	
#
# Dependencies
#
	
-include $(BUILD_DEP_MK)
