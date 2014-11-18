all: ppm.exe
ppm.exe: ppm.cpp ppm_file.o
	gcc -o ppm.exe ppm.cpp ppm_file.o
ppm_file.o: ppm_file.cpp ppm_file.h
	gcc -o ppm_file.o ppm_file.cpp -c