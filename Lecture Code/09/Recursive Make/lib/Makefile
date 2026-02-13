# lib/Makefile

CC = gcc
CFLAGS = -Wall -g
OBJS = math.o

# Target: build static library libmath.a
libmath.a: $(OBJS)
	ar rcs libmath.a $(OBJS)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
.PHONY: clean
clean:
	rm -f *.o libmath.a
