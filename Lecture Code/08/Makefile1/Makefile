# Target: my_program depends on object files
my_program: main.o functions.o
	gcc -o my_program main.o functions.o

# Rule to create main.o
main.o: main.c
	gcc -c main.c

# Rule to create functions.o
functions.o: functions.c
	gcc -c functions.c

# Phony target to clean up object files and executable
clean:
	rm -f *.o my_program
