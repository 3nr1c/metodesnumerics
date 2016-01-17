CFLAGS = -Wall -g -lm -O2 -pedantic -ansi

all:
	make p1e1
	make p1e2
	make p1e3
	make p1e4
	make p2e1
	make p2e2
	make p2e3
	make p3e1
	make p3e2
	make p4e1
	make p4e2
	make p4e3
	make p5e2
	make p5e3
	make p6e1

p4e1: matrixio.o
p4e2: solveLU.o matrixio.o
p4e3: matrixio.o
p5e2: p5e1.o matrixio.o
p5e3: solveLU.o p5e1.o matrixio.o
p6e1: solveLU.o matrixio.o

clean:
	rm -rf p1e1 p1e2 p1e3 p1e4
	rm -rf p2e1 p2e2 p2e3
	rm -rf p3e1 p3e2
	rm -rf p4e1 p4e2 p4e3 
	rm -rf p5e1 p5e2 p5e3
	rm -rf p6e1
	rm *.o
	rm -rf *.dSYM
