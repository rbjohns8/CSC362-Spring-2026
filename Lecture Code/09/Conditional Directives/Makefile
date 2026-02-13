# Define compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Detect the operating system and set variables accordingly
ifeq ($(shell uname), Darwin)  # macOS
    CFLAGS += -arch arm64
    EXT = 
else                           # Linux or other systems
    CFLAGS += -lpthread
    EXT =
endif

# Target: final executable
myprogram: main.o util.o
	$(CC) $(CFLAGS) -o $@$(EXT) $^

# Pattern rule to compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files and executable
.PHONY: clean
clean:
	rm -f *.o myprogram

run: myprogram
	./myprogram