CPPFLAGS += -std=c++20
CPPFLAGS += -W -Wall -g 
CPPFLAGS += -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable
CPPFLAGS += -I include/
CPPFLAGS += -I src/ -I src/generated

CPPFILES := $(shell find src/ -type d -name "mains" -prune -o -type f -name "*.cpp" -print)
CPPFILES += $(filter-out $(CPPFILES), src/generated/parser.tab.cpp src/generated/lexer.yy.cpp) # make sure parser, lexer not added twice

OBJECTS := $(addprefix build/, $(notdir $(CPPFILES:.cpp=.o)))

# $< expands to the first listed dependency
# $@ expands to the build target path
# $* expands to the target stem
# @D expands to the (parent) directory part of the target path
# -c to specify only compilation, not linking, and produces obj .o file

.PHONY: all clean

all: bin/lexer_main bin/parser_main

build/%.o: src/mains/%.cpp
	@mkdir -p $(@D)
	g++ ${CPPFLAGS} -MMD -MP -c $< -o $@

build/%.o: ${CPPFILES}
	@mkdir -p ${@D}
	g++ $(CPPFLAGS) -MMD -MP -c $(filter %/$*.cpp, $(CPPFILES)) -o $@

src/generated/lexer.yy.cpp: src/lexer.flex
	@mkdir -p $(@D)
	flex -o src/generated/lexer.yy.cpp src/lexer.flex

src/generated/parser.tab.hpp src/generated/parser.tab.cpp: src/parser.y
	@mkdir -p $(@D)
	bison -d src/parser.y -o src/generated/parser.tab.cpp

bin/lexer_main: ${OBJECTS} build/lexer_main.o
	@mkdir -p $(@D)
	g++ ${CPPFLAGS} -MMD -MP $^ -o $@

bin/parser_main: ${OBJECTS} build/parser_main.o
	@mkdir -p $(@D)
	g++ ${CPPFLAGS} -MMD -MP $^ -o $@

clean:
	rm -rf src/generated/*
	rm -rf build/*
	rm -rf bin/*