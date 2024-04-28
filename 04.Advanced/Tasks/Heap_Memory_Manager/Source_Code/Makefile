.PHONY: clean_all clean_obj doc

cc = gcc
CFLAGS = -Wall -Wextra

#List of Source files
SRC = datatype_size_lookup.c \
      glthread.c \
      memory_manager.c \
      memory_manager_test.c \
      parse_datatype.c \

# List of header files
HDR = colors.h \
      datatype_size_lookup.h \
      glthread.h \
      memory_manager.h \
      memory_manager_api.h \
      parse_datatype.h \
      memory_manager_api.h \


# List of object files for shared build
OBJ_SHARED = $(SRC:.c=_shared.o)

# List of object files for static build
OBJ_STATIC = $(SRC:.c=_static.o)

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
$(TARGET): $(OBJ_STATIC)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile C source files to object files for shared build
%_shared.o: %.c $(HDR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Rule to compile C source files to object files for static build
%_static.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

# Static library target
static: $(OBJ_STATIC)
	ar rcs $(STATIC_LIB) $(OBJ_STATIC)

# Shared library target
shared: $(OBJ_SHARED)
	$(CC) -shared -o $(SHARED_LIB) $(OBJ_SHARED)

# Clean target
clean_all:
	$(RM) $(TARGET)	$(OBJ_STATIC) $(OBJ_SHARED) $(STATIC_LIB) $(SHARED_LIB)

# Clean object files
clean_obj:
	$(RM) $(OBJ_SHARED) $(OBJ_STATIC)

# Generate documentation
doc:
	doxygen Doxyfile
