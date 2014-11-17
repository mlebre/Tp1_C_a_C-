all: ppm.exe
ppm.exe: ppm.c ppm_file.o
	gcc -o ppm.exe ppm.c ppm_file.o
ppm_file.o: ppm_file.c ppm_file.h
	gcc -o ppm_file.o ppm_file.c -c