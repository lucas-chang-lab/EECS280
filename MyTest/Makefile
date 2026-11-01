# ==========================================
# 1. CONFIGURATION
# ==========================================
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -O2

# Shared source files (excluding files with main functions)
SHARED_SRCS = header.cpp
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

# Main targets
MAIN_TARGET = test.exe
TEST_TARGET = unit_test.exe

# ==========================================
# 2. BUILD RULES
# ==========================================
# Typing 'make' will now build BOTH programs safely
all: $(MAIN_TARGET) $(TEST_TARGET)

# Build the main application (links header.o + test.o)
$(MAIN_TARGET): test.o $(SHARED_OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN_TARGET) test.o $(SHARED_OBJS)

# Build the unit test suite (links header.o + unit_test.o)
$(TEST_TARGET): unit_test.o $(SHARED_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) unit_test.o $(SHARED_OBJS)

# Generic compile rule for individual object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ==========================================
# 3. UTILITIES
# ==========================================
clean:
	rm -f $(MAIN_TARGET) $(TEST_TARGET) *.o

.PHONY: all clean
