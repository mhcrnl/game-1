all: build/game

C_SOURCES=game.c marching_cubes.c

all: build/game build/cube

clean:
	rm -rf build

build/game: $(C_SOURCES) 
	mkdir -p build
	$(CC) -ggdb -O3 -Wall -o $@ $^ -lGL -lglut -lGLU -lm

build/cube: cube.c
	mkdir -p build
	$(CC) -ggdb -O2 -Wall -o $@ $^ -lGL -lglut -lGLU -lm


.PHONY: all

