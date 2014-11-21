all: ppm.exe
ppm.exe: ppm.cpp image.o
	g++ -o ppm.exe ppm.cpp image.o 

image.o: image.cpp image.h
	g++ -o image.o image.cpp -c

