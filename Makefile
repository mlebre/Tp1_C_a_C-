all: ppm.exe
ppm.exe: ppm.cpp ppm_file.o
	g++ -o ppm.exe ppm.cpp ppm_file.o
ppm_file.o: ppm_file.cpp ppm_file.h
	g++ -o ppm_file.o ppm_file.cpp -c