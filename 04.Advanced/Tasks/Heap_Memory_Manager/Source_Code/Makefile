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
      memory_manager_api.h

# List of object files
OBJ = $(SRC:.c=.o)

# Name of the executable
TARGET = exe

# Command to remove files
RM = rm -f

# Default target
all: $(TARGET)

# Rules to link object files and create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
	
# Rule to compile C source files object files
%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@
	
# Clean target
clean:
	$(RM) $(OBJ) $(TARGET)
	
