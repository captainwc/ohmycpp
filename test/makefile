CXX = g++

CXXFLAGS = -std=c++11 -I../include -pthread -lgtest -lgtest_main

SOURCES := $(wildcard *.cpp)
TARGETS := $(patsubst %.cpp, bin/%.exe, $(SOURCES))

default:run

all: $(TARGETS)

bin/%.exe: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

define run_target
	@echo
	@echo "========/////////////// $(patsubst bin/%.exe,%,$(1)) \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\========"
	@./$1 -ni -nv
endef

run: $(TARGETS)
	$(foreach target,$(TARGETS),$(call run_target,$(target)))

clean:
	rm -f bin/*

.PHONY: all run clean
