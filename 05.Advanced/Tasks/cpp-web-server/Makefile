# Compiler and flags
# CXX is the variable for the C++ compiler
# CXXFLAGS contains the flags passed to the C++ compiler:
# -Wall enables all the warnings about constructions that some users consider questionable
# -Wextra enables additional warning flags that are not enabled by -Wall
# -Iincludes tells the compiler to add the 'includes' directory to the list of directories to be searched for header files
# -std=c++11 specifies the C++ standard to be used
CXX = g++
CXXFLAGS = -Wall -Wextra -Iincludes -std=c++11

# Directories
# SRCDIR is the directory containing the source files
# INCDIR is the directory containing the header files
# BUILDDIR is the directory where object files will be stored
# TARGET is the final executable file to be built
SRCDIR = src
INCDIR = includes
BUILDDIR = build
TARGET = bin/webserver

# Source and object files
# SOURCES contains all the .cpp files in the SRCDIR directory
# OBJECTS is derived from SOURCES by replacing the source directory prefix and .cpp extension with the build directory prefix and .o extension
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Build target
# This rule specifies how to build the final executable TARGET
# It depends on all the object files in OBJECTS
# The command uses the C++ compiler to link the object files into the final executable
# $@ is an automatic variable that represents the target (bin/webserver)
# $^ is an automatic variable that represents all the dependencies (all object files)
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build objects
# This rule specifies how to build each object file from the corresponding source file
# It depends on the existence of the build directory (specified as an order-only prerequisite with |)
# The command uses the C++ compiler to compile the source file into an object file
# $@ is an automatic variable that represents the target (the object file)
# $< is an automatic variable that represents the first prerequisite (the source file)
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Create build directory
# This rule specifies how to create the build directory if it does not exist
# The command uses mkdir -p to create the directory and any necessary parent directories
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Clean build files
# This rule specifies how to clean up the build directory and the final executable
# The command uses rm -rf to remove the build directory and the executable
clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Phony target
# This specifies that 'clean' is a phony target
# A phony target is not a file name, but just a name for a recipe to be executed when explicitly requested
.PHONY: clean
