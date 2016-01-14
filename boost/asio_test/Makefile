# yum install redhat-lsb-core

ifeq (, $(shell which lsb_release))
    $(warning lsb_release not found)
else
    OS=$(shell lsb_release -si)
    ARCH=$(shell uname -m | sed 's/x86_//;s/i[3-6]86/32/')
    VER=$(shell lsb_release -sr)
endif

# OS:   Ubuntu RedHatEnterpriseServer CentOS
# ARCH: 64     64                     64
# VER:  15.04  6.5                    6.7

CPPFLAGS = -g -Wall
CPPFLAGS += -std=c++11 
# CPPFLAGS += -static

LDFLAGS = -pthread -lrt

################################################################
## Boost related variables
USE_STATIC_BOOST := f
ifeq ($(OS), Ubuntu)
  BOOST_DIR := /usr/lib/x86_64-linux-gnu
else
  BOOST_DIR := /usr/local/lib
endif
## BOOST_LIB := $(wildcard $(BOOST_DIR)/libboost*.a)
## BOOST_LIB := $(filter-out libboost_python.a, $(BOOST_LIB))
## common boost static libraries.
BOOST_LIB += $(BOOST_DIR)/libboost_chrono.a
BOOST_LIB += $(BOOST_DIR)/libboost_filesystem.a
BOOST_LIB += $(BOOST_DIR)/libboost_iostreams.a
BOOST_LIB += $(BOOST_DIR)/libboost_log.a
BOOST_LIB += $(BOOST_DIR)/libboost_locale.a
BOOST_LIB += $(BOOST_DIR)/libboost_program_options.a
BOOST_LIB += $(BOOST_DIR)/libboost_system.a
BOOST_LIB += $(BOOST_DIR)/libboost_serialization.a
BOOST_LIB += $(BOOST_DIR)/libboost_signals.a
BOOST_LIB += $(BOOST_DIR)/libboost_random.a
BOOST_LIB += $(BOOST_DIR)/libboost_regex.a
BOOST_LIB += $(BOOST_DIR)/libboost_thread.a
BOOST_LIB += $(BOOST_DIR)/libboost_timer.a

ifeq ($(USE_STATIC_BOOST),t)
    LIB += $(BOOST_LIB)
else
    ## comman boost links
    LDFLAGS += -lboost_iostreams -lboost_program_options -lboost_thread -lboost_timer -lboost_system ## and others
endif
## End Boost part
################################################################

################################################################
## Main Part

LIB += $(wildcard ./lib/*.a) ## local lib
SRC = $(wildcard *.cpp)      ## all cpp files
target = asio                ## all targets

base = $(filter-out $(target:%=%.cpp), $(SRC))  ## all file except targets
CXX = g++

.PHONY: all clean

all: $(SRC:%.cpp=%.o)
	$(foreach t,$(target), $(CXX) $(base:%.cpp=%.o) $(t:%=%.o) $(LIB) $(LIB) $(LDFLAGS) -o $(t) ;)

# ar: the_lib.a
# the_lib.a: $(base:%.cpp=%.o)
# 	ar rcs $@ $^

clean:
	rm -f $(SRC:%.cpp=%.o)
	rm -f $(target)

################################################################
