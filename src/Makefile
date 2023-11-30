ifeq (, $(shell which sst-config))
    $(error "No can do with the sst-config  in $(PATH), add 'sst-config' to your PATH")
endif


CXX=$(shell sst-config --CXX)
CXXFLAGS=$(shell sst-config --ELEMENT_CXXFLAGS)
LDFLAGS=$(shell sst-config --ELEMENT_LDFLAGS)
#ELEMENT_HEADERS=$(shell sst-config SST_ELEMENT_LIBRARY SST_ELEMENT_LIBRARY_HOME)/include
CPPFLAGS= -I./
OPTIMIZE_FLAGS=-O2

COMPONENT_LIB=libPizzaProject.so

PIZZAPROJECT_SOURCES := $(wildcard *.cc)

PIZZAPROJECT_HEADERS := $(wildcard *.h)

PIZZAPROJECT_OBJS := $(patsubst %.cc,%.o,$(wildcard *.cc))

all: $(COMPONENT_LIB)

debug: CXXFLAGS += -DDEBUG -g
debug: $(COMPONENT_LIB)

$(COMPONENT_LIB): $(PIZZAPROJECT_OBJS)
	$(CXX) $(OPTIMIZE_FLAGS) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ *.o
%.o:%.cc $(SIMPLEEXAMPLE_HEADERS)
	$(CXX) $(OPTIMIZE_FLAGS) $(CXXFLAGS) $(CPPFLAGS)  -c $<
install: $(COMPONENT_LIB)
	sst-register PizzaProject PizzaProject_LIBDIR=$(CURDIR)
clean:
	rm -Rf *.o $(COMPONENT_LIB)