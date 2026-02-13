# Define compiler and flags
CC = gcc
CFLAGS = -Wall -g

all: myprogram

# Target: final executable
myprogram: main.o foo.o bar.o
	$(CC) -o $@ $^

# Pattern rule to compile .c to .o using the first prerequisite
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executable
.PHONY: clean
clean:
	rm -f *.o myprogram

run: myprogram
	./myprogram