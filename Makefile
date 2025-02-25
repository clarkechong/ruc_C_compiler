CPPFLAGS += -W -Wall -g 
CPPFLAGS += -Wno-unused-function -Wno-unused-parameter
CPPFLAGS += -std=c++20
CPPFLAGS += -I include/
CPPFLAGS += -I src/generated

.PHONY: default clean

default:

build/%.o: src/%.cpp
	g++ ${CPPFLAGS} -c $< -o $@

build/%.o: src/generated/%.cpp
	g++ ${CPPFLAGS} -c $< -o $@

# $< expands to the first listed dependency
# $@ expands to the build target path
# -c to specify only compilation, not linking, and produces obj .o file

src/generated/lexer.yy.cpp: src/lexer.flex
	flex -o src/generated/lexer.yy.cpp src/lexer.flex

src/generated/parser.tab.hpp src/generated/parser.tab.cpp: src/parser.y
	bison -d src/parser.y -o src/generated/parser.tab.cpp

bin/lexer_main: src/generated/parser.tab.hpp build/lexer_main.o build/lexer.yy.o build/parser.tab.o 
	g++ ${CPPFLAGS} $^ -o $@

clean:
	rm -rf src/generated/*
	rm -rf build/*
	rm -rf bin/*