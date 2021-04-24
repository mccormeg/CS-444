concurr: concurr1.o mt19937ar.o driver.o
	gcc -lpthread concurr1.o mt19937ar.o driver.o -o concurr
concurr1.o: concurr1.c
	gcc -c concurr1.c
mt19937ar.o: mt19937ar.c
	gcc -c mt19937ar.c
driver.o:
	gcc -c driver.c
clean:
	rm -f *.out *.o concurr
