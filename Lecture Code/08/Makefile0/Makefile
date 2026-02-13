my_program: file1.o file2.o
	gcc -o my_program file1.o file2.o

file1.o: file1.c file1.h
	gcc -c file1.c

file2.o: file2.c file1.h
	gcc -c file2.c

clean:
	rm -f *.o my_program
