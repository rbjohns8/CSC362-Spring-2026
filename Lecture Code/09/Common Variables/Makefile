# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Target: Build everything
all: myprogram

# Target: Compile main.c into main.o
main.o:
	$(CC) $(CFLAGS) -c main.c -o main.o

# Target: Compile util.c into util.o
util.o:
	$(CC) $(CFLAGS) -c util.c -o util.o

# Target: Link main.o and util.o into the final executable
myprogram: main.o util.o
	$(CC) $(CFLAGS) -o myprogram main.o util.o

# Phony target: Clean up object files and the executable
.PHONY: clean
clean:
	rm -f main.o util.o myprogram
