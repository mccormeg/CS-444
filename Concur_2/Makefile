concurr: concurr2.o mt19937ar.o driver.o
	gcc -lpthread concurr2.o mt19937ar.o driver.o -o concurr
concurr2.o: concurr2.c
	gcc -c concurr2.c
mt19937ar.o: mt19937ar.c
	gcc -c mt19937ar.c
driver.o:
	gcc -c driver.c
clean:
	rm -f *.out *.o concurr
