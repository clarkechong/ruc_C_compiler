CPPFLAGS += -std=c++20
CPPFLAGS += -W -Wall -g 
CPPFLAGS += -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable
CPPFLAGS += -I include/
CPPFLAGS += -I src/ -I src/generated

# $< expands to the first listed dependency
# $@ expands to the build target path
# @D expands to the (parent) directory part of the target path
# -c to specify only compilation, not linking, and produces obj .o file

.PHONY: all clean

all: bin/lexer_main bin/parser_main

build/%.o: src/%.cpp
	@mkdir -p $(@D)
	g++ ${CPPFLAGS} -c $< -o $@

build/%.o: src/generated/%.cpp
	@mkdir -p $(@D)
	g++ ${CPPFLAGS} -c $< -o $@

build/%.o: src/mains/%.cpp
	@mkdir -p $(@D)
	g++ ${CPPFLAGS} -c $< -o $@

src/generated/lexer.yy.cpp: src/lexer.flex
	@mkdir -p $(@D)
	flex -o src/generated/lexer.yy.cpp src/lexer.flex

src/generated/parser.tab.hpp src/generated/parser.tab.cpp: src/parser.y
	@mkdir -p $(@D)
	bison -d src/parser.y -o src/generated/parser.tab.cpp

bin/lexer_main: build/parser.tab.o build/lexer.yy.o build/lexer_main.o
	@mkdir -p $(@D)
	g++ ${CPPFLAGS} $^ -o $@

bin/parser_main: build/parser.tab.o build/lexer.yy.o build/parser_main.o
	@mkdir -p $(@D)
	g++ ${CPPFLAGS} $^ -o $@

clean:
	rm -rf src/generated/*
	rm -rf build/*
	rm -rf bin/*