# Makefile for VariadicCommandProcessor

CC = gcc
CFLAGS = -Wall -Wextra -I./include -I./config
LDFLAGS = -lpthread

SRCS = src/main.c src/command_processor.c src/dynamic_logger.c src/utils.c
OBJS = $(SRCS:.c=.o)
TARGET = variadic-command-processor

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
