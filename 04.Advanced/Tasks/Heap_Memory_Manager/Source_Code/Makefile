.PHONY: clean_all clean_obj doc

cc = gcc
CFLAGS = -Wall -Wextra

#List of Source files
SRC = $(wildcard *.c)

#List of Source files except the memory_manager_test
LIB_SRC = $(filter-out memory_manager_test.c, $(wildcard *.c))

# List of header files
HDR = $(wildcard *.h) 

# List of object files
OBJ = $(SRC:.c=.o)

# List of object files for shared build
OBJ_SHARED = $(LIB_SRC:.c=_shared.o)

# List of object files for static build
OBJ_STATIC = $(LIB_SRC:.c=_static.o)

# Name of the executable
TARGET = hmm

# Name of the static library
STATIC_LIB = lib$(TARGET).a

# Name of the shared library
SHARED_LIB = lib$(TARGET).so

# Command to remove files
RM = rm -f

# Default target
all: $(TARGET)

# Rules to link object files and create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Static library target
static: $(OBJ_STATIC)
	ar rcs $(STATIC_LIB) $(OBJ_STATIC)

# Shared library target
shared: $(OBJ_SHARED)
	$(CC) -shared -o $(SHARED_LIB) $(OBJ_SHARED)

# Rule to compile C source files into object files
%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile C source files to object files for shared build
%_shared.o: %.c $(HDR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Rule to compile C source files to object files for static build
%_static.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean_all:
	$(RM) $(TARGET)	$(OBJ) $(OBJ_STATIC) $(OBJ_SHARED) $(STATIC_LIB) $(SHARED_LIB)

# Clean object files
clean_obj:
	$(RM) $(OBJ_SHARED) $(OBJ_STATIC)

# Generate documentation
doc:
	doxygen Doxyfile
