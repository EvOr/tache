proj_NAME = test

CC      = gcc 
CXX     = gfilt
CONFIG_GUESS = i686-pc-linux-gnu
#CC          = /export/shop/stow/gcc-4.0.2/$(CONFIG_GUESS)/bin/gcc
#CXX         = /export/shop/stow/gcc-4.0.2/$(CONFIG_GUESS)/bin/g++
CXX_VERSION = g++-$(shell $(CXX) -dumpversion)

RANLIB  = ranlib
AR      = ar
INSTALL = install -p

# CPPFLAGS += -DNDEBUG
CCFLAGS  += -O2 -funroll-loops -fexceptions
CXXFLAGS += -O2 -funroll-loops
LDFLAGS  += -time
DEPFLAGS = -MM -MG -MP


