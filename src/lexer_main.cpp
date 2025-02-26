/*
    TEST LEXER FUNCTIONALITY:
        - READ in from input txt
        - PRINT yytext, which is simply the text associated with any given token retrieved by yylex()
*/

#include <stdio.h>
#include <iostream>
#include "parser.tab.hpp"

extern int      yylex();
extern char*    yytext;
extern int      yyleng;
extern FILE*    yyin;
extern FILE*    yyout;
// some union yyval

int main(int argc, char** argv) {
    int count = 0;

    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w");
    while(yylex()) {
        std::cout << yytext << std::endl;
        count++;
    }
    std::cout << "# of tokens received: " << count << std::endl;
    return 0;
    
}