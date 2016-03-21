BINDIR := .
DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

SRC := $(wildcard *.cpp) ## all cpp files

INCLUDEDIR:=. include include/libunwind
INCLUDE:=$(foreach d, $(INCLUDEDIR), -I$d)

#LDFLAGS = -mkl
LIB += $(wildcard ../lib/libunwind*.a)
# MKLLIB := -Wl,--start-group $(wildcard ../lib/libmkl*.a) -Wl,--end-group -pthread -lm
# LIB += $(MKLLIB)

CXX = g++

CPPFLAGS = -g -Wall -Winline -pipe

################################################################
## Boost related variables
USE_BOOST := t
USE_STATIC_BOOST := f
ifeq ($(USE_STATIC_BOOST), t)
USE_BOOST := t
endif

ifeq ($(USE_BOOST), t)
  ifeq ($(WHOAMI), scinart)
    BOOST_DIR := /usr/lib/x86_64-linux-gnu
  else
    BOOST_DIR := /YOUR/HOME/boost_1_60_0/stage/lib
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
      LDFLAGS += -lboost_iostreams -lboost_program_options -lboost_thread -lboost_timer -lboost_filesystem -lboost_system ## and others
  endif
endif
## End Boost part
################################################################

export CPPFLAGS

.PHONY: all clean


all : main

main : main.o
	$(CXX) -o $(BINDIR)/$@ $(filter %.o,$^) $(LDFLAGS) $(LIB) $(LIB)

%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d
	$(CXX) $(DEPFLAGS) $(CPPFLAGS) -c $< -o $@ $(INCLUDE)
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d


clean :
	-rm -f $(SRC:%.cpp=%.o)
	-rm -f main

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRC)))
