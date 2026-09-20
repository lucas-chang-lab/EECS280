# ==========================================
# 1. CONFIGURATION (Change these if needed)
# ==========================================
# Name of your final executable program
TARGET   = test.exe

# Automatically finds ALL .cpp files in the folder (e.g., test.cpp, gg.cpp, stats.cpp)
SRCS     = $(wildcard *.cpp)

# Automatically changes the .cpp list into a list of .o object files
OBJS     = $(SRCS:.cpp=.o)

# Compiler to use
CXX      = g++

# Compiler flags (-Wall -Wextra catch bugs, -std=c++17 sets language standard)
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -O2  # -Werror

# ==========================================
# 2. BUILD RULES
# ==========================================
# Default rule called when you just type 'make'
all: $(TARGET)

# Links ALL detected object files together into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile individual source files (.cpp) into object files (.o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# ==========================================
# 3. UTILITIES
# ==========================================
# Clean up compiled files to start fresh (Run with 'make clean')
clean:
	rm -f $(TARGET) *.o

# Tells make that 'all' and 'clean' are commands, not physical files
.PHONY: all clean
