# Target to build the program
all: my_program

# Target to build the executable from object files
my_program: main.o file_utils.o
	gcc -o my_program main.o file_utils.o

# Rule to compile main.o
main.o: main.c file_utils.h
	gcc -c main.c

# Rule to compile file_utils.o
file_utils.o: file_utils.c file_utils.h
	gcc -c file_utils.c

# Clean up the directory (delete object files and executable)
clean:
	rm -f *.o my_program

# Phony targets declaration
.PHONY: all clean





