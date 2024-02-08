CFLAGS= -I ./include -pedantic -Wall -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable

all: ./build/gfx.o ./build/irem.o ./build/oguzhan.o ./build/umut.o ./build/yahya.o
	gcc $(CFLAGS) ./build/gfx.o ./build/irem.o ./build/oguzhan.o ./build/umut.o ./build/yahya.o -o Iedit -lX11 -lm

debug: CFLAGS += -g
debug: purge all

clean:
	rm -f ./build/*.o

purge: clean
	rm -f Iedit

./build/gfx.o: ./src/gfx.c
	gcc $(CFLAGS) -c ./src/gfx.c -o ./build/gfx.o

./build/irem.o: ./src/irem.c
	gcc $(CFLAGS) -c ./src/irem.c -o ./build/irem.o

./build/oguzhan.o: ./src/oguzhan.c
	gcc $(CFLAGS) -c ./src/oguzhan.c -o ./build/oguzhan.o

./build/umut.o: ./src/umut.c
	gcc $(CFLAGS) -c ./src/umut.c -o ./build/umut.o

./build/yahya.o: ./src/yahya.c
	gcc $(CFLAGS) -c ./src/yahya.c -o ./build/yahya.o
