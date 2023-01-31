EXECUTABLE = bin/rpg
SOURCES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=obj/%.o)

INCLUDE_DIR = include
DEPS = deps/interface-dialogue

.PHONY = all clean run

all: ${EXECUTABLE}

clean: 
	rm ${EXECUTABLE} ${OBJECTS}

run: ${EXECUTABLE}
	${EXECUTABLE}

${EXECUTABLE}: ${OBJECTS}
	${CXX} $^ -o $@

./obj/%.o: src/%.cpp $(wildcard include/%.h)
	${CXX} $< -c -o $@ -I"${INCLUDE_DIR}"