# Makefile

# Compiler
CXX ?= g++

# # Compiler flags
# CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment
# Compiler flags - Added sanitizer tools
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment -fsanitize=address,undefined

simulate.exe: simulate.cpp Dataset.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Disable built-in Makefile rules
.SUFFIXES:

clean:
	rm -rvf *.exe *.dSYM *.stackdump




