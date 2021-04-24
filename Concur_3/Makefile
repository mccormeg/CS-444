prob1: prob1.o mt19937ar.o driver1.o
	gcc -lpthread prob1.o mt19937ar.o driver1.o -o prob1
prob2: prob2.o mt19937ar.o driver2.o
	gcc -lpthread prob2.o mt19937ar.o driver2.o -o prob2
prob1.o: prob1.c
	gcc -c prob1.c
mt1997ar.o: mt1997ar.c
	gcc -c mt1997ar.c
driver1.o: driver1.c
	gcc -c driver1.c
clean:
	rm -f *.o prob1 prob2

