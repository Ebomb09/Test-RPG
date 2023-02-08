GAME_NAME = rpg
EXECUTABLE = bin/${GAME_NAME}

ifeq (${OS},Windows_NT)
	EXECUTABLE := ${EXECUTABLE}.exe
endif

SOURCES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=obj/%.o)

DEPS = deps/interface-dialogue
INCLUDES = -Iinclude $(shell pkg-config sdl2 SDL2_ttf SDL2_image SDL2_mixer --cflags) -I$(DEPS:=/include)
LIBS = $(shell pkg-config sdl2 SDL2_ttf SDL2_image SDL2_mixer --libs) -L$(DEPS:=/lib) -ldialogue
CPPFLAGS := -std=c++14

.PHONY = all clean run init

all: ${DEPS} ${EXECUTABLE}

clean: 
	rm ${EXECUTABLE} ${OBJECTS}

run: all
	@cp -r $(wildcard resource/*) bin
	cd $(dir ${EXECUTABLE}) && ./$(notdir ${EXECUTABLE})

${EXECUTABLE}: ${OBJECTS}
	@mkdir -p $(dir EXECUTABLE)
	${CXX} $^ -o $@ ${LIBS} ${CFLAGS} ${CPPFLAGS}

obj/%.o: src/%.cpp $(wildcard include/%.h)
	@mkdir -p $(dir $@)
	${CXX} $< -c -o $@ ${INCLUDES} ${CFLAGS} ${CPPFLAGS}

deps/%:
	@mkdir -p deps
	git clone git@ebomb.asuscomm.com:repos/$(@F).git $@ && \
	cd $@ && $(MAKE) init && $(MAKE)