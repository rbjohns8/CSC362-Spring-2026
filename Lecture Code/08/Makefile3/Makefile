# Variables for the compiler and flags
CC = gcc
CFLAGS = -Wall -g

# List of object files (using variables)
OBJ = main.o file_utils.o

# Target to build the program
all: my_program

# Target to build the executable, using 
# variables for compiler and object files
my_program: $(OBJ)
	$(CC) -o my_program $(OBJ)

# Pattern rule for compiling .c files into 
# .o files, using variables for compiler and 
# flags
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean up the directory (delete object 
# files and executable)
clean:
	rm -f *.o my_program

# Phony targets declaration
.PHONY: all clean
