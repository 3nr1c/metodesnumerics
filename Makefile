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
	make p7e1
	make p7e2
	make p8e1
	make p9e1
	make p10e1
	make p10e2
	make p11e1
	make p11e1-2

p4e1: matrixio.o
p4e2: solveLU.o matrixio.o
p4e3: matrixio.o
p5e2: p5e1.o matrixio.o
p5e3: solveLU.o p5e1.o matrixio.o
p7e1: solveLU.o matrixio.o
p7e2: solveLU.o matrixio.o horner.o
p8e1: matrixio.o horner.o
p9e1: horner.o

clean:
	rm -rf p1e1 p1e2 p1e3 p1e4
	rm -rf p2e1 p2e2 p2e3
	rm -rf p3e1 p3e2
	rm -rf p4e1 p4e2 p4e3 
	rm -rf p5e1 p5e2 p5e3
	rm -rf p7e1 p7e2
	rm -rf p8e1
	rm -rf p9e1
	rm -rf p10e1 p10e2 f
	rm -rf p11e1 p11e1-2
	rm *.o
	rm -rf *.dSYM
