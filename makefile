EXECUTABLE = bin/rpg
SOURCES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=obj/%.o)

DEPS = deps/interface-dialogue
INCLUDES = -Iinclude $(shell pkg-config sdl2 SDL2_ttf SDL2_image --cflags) 
LIBS = $(shell pkg-config SDL2_ttf SDL2_image --libs)

CPPFLAGS := -std=c++11

.PHONY = all clean run

all: ${EXECUTABLE}

clean: 
	rm ${EXECUTABLE} ${OBJECTS}

run: ${EXECUTABLE}
	${EXECUTABLE}

${EXECUTABLE}: ${OBJECTS}
	${CXX} $^ -o $@ ${LIBS} ${CFLAGS} ${CPPFLAGS}

./obj/%.o: src/%.cpp $(wildcard include/%.h)
	${CXX} $< -c -o $@ ${INCLUDES} ${CFLAGS} ${CPPFLAGS}