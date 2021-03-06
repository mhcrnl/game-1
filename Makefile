all: build/game

C_FILES       = $(shell ls src/*.c | grep -v src/game.c)
TEST_FILES    = $(shell ls test-src/*.c)
TESTS         = $(TEST_FILES:test-src/%.c=run-%)
DEPS          = $(C_FILES:src/%.c=build/%.deps)
OBJS          = $(C_FILES:src/%.c=build/%.o)
CC            = gcc

CFLAGS  = -ggdb -Wall -Isrc
LDFLAGS = -lGL -lglut -lGLU -lGLEW -lm -l3ds

all: build build/game build/TAGS $(DEPS) $(TESTS)
	echo "Tests: $(TESTS)"

clean:
	rm -rf build

build/TAGS: $(C_FILES)
	etags -o $@ $^

build/game: $(OBJS)
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ src/game.c $(OBJS) $(LDFLAGS)

build/%: test-src/%.c $(OBJS)
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $< $(OBJS) $(LDFLAGS)

run-%: build/%
	$<

build/%.o : src/%.c
	mkdir -p build
	$(CC) -c $(CFLAGS) -o $@ $< -lGL -lglut -lGLU -lm

build/%.deps : src/%.c
	mkdir -p build
	$(CC) -MM -MT $(<:src/%.c=build/%.o) -o $@ $<

include $(DEPS)

.PHONY: all

