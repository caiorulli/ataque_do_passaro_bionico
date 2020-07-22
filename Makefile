CFLAGS=  -Wall --ansi -g -lm -O2 -pedantic
LDFLAGS= -lglut -lGLU -lGL -lm

all: main
	./main

main: main.o cenario.o tiro.o defesa.o nave.o dinamico.o objeto.o

clean:
	rm *.o