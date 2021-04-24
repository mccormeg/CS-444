concurr: concurr4.o mt19937ar.o driver.o
	gcc -lpthread concurr4.o mt19937ar.o driver.o -o concurr
concurrp2: concurr4p2.o mt19937ar.o driverp2.o
	gcc -lpthread concurr4p2.o mt19937ar.o driverp2.o -o concurrp2
concurr4.o: concurr4.c
	gcc -c concurr4.c
concurr4p2.o: concurr4p2.c
	gcc -c concurr4p2.c
mt19937ar.o: mt19937ar.c
	gcc -c mt19937ar.c
driver.o:
	gcc -c driver.c
driverp2.o:
	gcc -c driverp2.c
clean:
	rm -f *.out *.o concurr concurrp2
