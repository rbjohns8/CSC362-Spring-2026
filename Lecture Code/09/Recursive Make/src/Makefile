# src/Makefile

CC = gcc
CFLAGS = -Wall -g
OBJS = main.o util.o

# Include the library path and link with libmath.a
LIB_DIR = ../lib
LIBS = -L$(LIB_DIR) -lmath

# Target: final executable
myprogram: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
.PHONY: clean
clean:
	rm -f *.o myprogram
