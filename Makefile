CC ?= gcc
CCOPTS ?=

all : stl-viewer

stl-viewer : main.c vector.o stl.o triangle.o render.o
	$(CC) $(CCOPTS) main.c vector.o stl.o triangle.o render.o -o stl-viewer

vector.o : vector.c
	$(CC) $(CCOPTS) -c vector.c -o vector.o

stl.o : stl.c
	$(CC) $(CCOPTS) -c stl.c -o stl.o

triangle.o : triangle.c
	$(CC) $(CCOPTS) -c triangle.c -o triangle.o

render.o : render.c
	$(CC) $(CCOPTS) -c render.c -o render.o

clean :
	rm *.o stl-viewer
