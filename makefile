#executables
run1: shm.o prog1.o prog2.o
	gcc -Wall -o run1 prog1.o shm.o -O2
	gcc -Wall -o run2 prog2.o shm.o -O2
	rm -f *.o



#example programs
prog1.o: prog1.c shm.h
	gcc -Wall -c prog1.c -O2

prog2.o: prog2.c shm.h
	gcc -Wall -c prog2.c -O2



#shm library
shm.o: shm.c shm.h
	gcc -Wall -c shm.c -O2
