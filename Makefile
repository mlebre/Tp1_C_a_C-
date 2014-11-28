all: ppm.out
ppm.out: ppm.cpp image.o
	g++ -o ppm.out ppm.cpp image.o 

image.o: image.cpp image.h
	g++ -o image.o image.cpp -c

