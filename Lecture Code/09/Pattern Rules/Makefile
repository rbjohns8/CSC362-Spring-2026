# Define compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Target: final executable
myprogram: main.o util.o
	$(CC) -o $@ $^

# Pattern rule to compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files and executable
.PHONY: clean
clean:
	rm -f *.o myprogram

run: myprogram
	./myprogram