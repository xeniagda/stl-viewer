CC ?= clang
CFLAGS ?= -O3 -flto -ffast-math

all : stl-viewer

stl-viewer : main.c vector.o stl.o triangle.o render.o
	$(CC) $(CFLAGS) main.c vector.o stl.o triangle.o render.o -o stl-viewer

vector.o : vector.c
	$(CC) $(CFLAGS) -c vector.c -o vector.o

stl.o : stl.c
	$(CC) $(CFLAGS) -c stl.c -o stl.o

triangle.o : triangle.c
	$(CC) $(CFLAGS) -c triangle.c -o triangle.o

render.o : render.c
	$(CC) $(CFLAGS) -c render.c -o render.o

clean :
	rm *.o stl-viewer
