.PHONY: all clean

CC = gcc
CFLAGS = -c -I include -Wall -Wextra -Wpedantic

all: buildProject
	
buildProject:	./build/PKCS7.o ./build/PKCS7_test.out

./build/PKCS7.o:	./src/PKCS7.c ./include/PKCS7.h
	$(CC) $(CFLAGS) ./src/PKCS7.c -o ./build/PKCS7.o

./build/PKCS7_test.o:	./test/PKCS7_test.c ./test/PKCS7_test.h ./include/PKCS7.h
	$(CC) $(CFLAGS) ./test/PKCS7_test.c -o ./build/PKCS7_test.o

./build/PKCS7_test.out:	./build/PKCS7_test.o ./build/PKCS7.o
	$(CC) ./build/PKCS7_test.o ./build/PKCS7.o -o ./build/PKCS7_test.out

clean:
	rm -f ./build/*.o ./build/*.out