EXECUTABLE = bin/rpg
SOURCES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=obj/%.o)

DEPS = deps/interface-dialogue
INCLUDES = -Iinclude $(shell pkg-config sdl2 --cflags) 
LIBS = $(shell pkg-config sdl2 --libs)

.PHONY = all clean run

all: ${EXECUTABLE}

clean: 
	rm ${EXECUTABLE} ${OBJECTS}

run: ${EXECUTABLE}
	${EXECUTABLE}

${EXECUTABLE}: ${OBJECTS}
	${CXX} $^ -o $@ ${LIBS}

./obj/%.o: src/%.cpp $(wildcard include/%.h)
	${CXX} $< -c -o $@ ${INCLUDES}