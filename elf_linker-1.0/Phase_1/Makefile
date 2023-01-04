readelf: readelf.o read_header.o
	gcc -g readelf.o read_header.o -o readelf

readelf.o: readelf.c read_header.h
	gcc -g -c readelf.c

read_header.o: read_header.c read_header.h
	gcc -g -c read_header.c

clean:
	rm readelf *.o
