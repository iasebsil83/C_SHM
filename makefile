#executables
run1: shm.o prog1.o prog2.o
	gcc -Wall -o run1 prog1.o shm.o -O2
	gcc -Wall -o run2 prog2.o shm.o -O2
	rm -f *.o



#example programs
prog1.o: src/prog1.c lib/shm.h
	gcc -Wall -c src/prog1.c -O2

prog2.o: src/prog2.c lib/shm.h
	gcc -Wall -c src/prog2.c -O2



#shm library
shm.o: lib/shm.c lib/shm.h
	gcc -Wall -c lib/shm.c -O2
