CFLAGS = -Wall -g -lm -O2 -pedantic

all:
	make test
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
	make p5e1

clean:
	rm -rf test p1e1 p1e2 p1e3 p1e4
	rm -rf p2e1 p2e2 p2e3
	rm -rf p3e1 p3e2
	rm -rf p4e1 p5e1