all: build/game

C_FILES = $(shell ls src/*.c)
DEPS    = $(C_FILES:src/%.c=build/%.deps)
OBJS    = $(C_FILES:src/%.c=build/%.o)
CC      = gcc

CFLAGS  = -ggdb -Wall 

all: build build/game build/TAGS $(DEPS)

clean:
	rm -rf build

build/TAGS: $(C_FILES)
	etags -o $@ $^

build/game: $(OBJS)
	mkdir -p build
	$(CC) $(CFLAGS)-o $@ $^ -lGL -lglut -lGLU -lm

build/%.o : src/%.c
	mkdir -p build
	$(CC) -c $(CFLAGS) -o $@ $< -lGL -lglut -lGLU -lm

build/%.deps : src/%.c
	mkdir -p build
	$(CC) -MM -MT $(<:src/%.c=build/%.o) -o $@ $<

include $(DEPS)

.PHONY: all

