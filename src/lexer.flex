%{
  #include "parser.tab.hpp"
  #include <unordered_map>
  #include "ast/type/ast_declaration_type.hpp"

  // LEXER HACK cus everybodys done it...
  std::unordered_map<std::string, ast::TypeSpecifier> type_map;

  void update_type_map(const std::string& id, ast::TypeSpecifier type) {
    type_map[id] = type;
  }

  int check_type_map(const std::string& id) {
    if (type_map.find(id) != type_map.end()) {
      return TYPE_NAME;
    }
    return IDENTIFIER;
  }
%}

D	  [0-9]
L	  [a-zA-Z_]
H   [a-fA-F0-9]
E	  [Ee][+-]?{D}+
FS  (f|F|l|L)
IS  (u|U|l|L)*

%x COMMENT

%%

"/*"                { BEGIN COMMENT; }
<COMMENT>[^*/]+     { /* ignore anything not '*' or '/' */ }
<COMMENT>("*"+)"/"  { BEGIN INITIAL; }
<COMMENT>[*/]       { }

"//"[^\n]*"\n"      { /* single line comment */ }

"auto"			{return(AUTO);}
"break"			{return(BREAK);}
"case"			{return(CASE);}
"char"			{return(CHAR);}
"const"			{return(CONST);}
"continue"  {return(CONTINUE);}
"default"		{return(DEFAULT);}
"do"			  {return(DO);}
"double"		{return(DOUBLE);}
"else"			{return(ELSE);}
"enum"			{return(ENUM);}
"extern"		{return(EXTERN);}
"float"			{return(FLOAT);}
"for"			  {return(FOR);}
"goto"			{return(GOTO);}
"if"			  {return(IF);}
"int"			  {return(INT);}
"long"			{return(LONG);}
"register"	{return(REGISTER);}
"return"		{return(RETURN);}
"short"			{return(SHORT);}
"signed"		{return(SIGNED);}
"sizeof"		{return(SIZEOF);}
"static"		{return(STATIC);}
"struct"		{return(STRUCT);}
"switch"		{return(SWITCH);}
"typedef"		{return(TYPEDEF);}
"union"			{return(UNION);}
"unsigned"	{return(UNSIGNED);}
"void"			{return(VOID);}
"volatile"	{return(VOLATILE);}
"while"			{return(WHILE);}

{L}({L}|{D})*		        {yylval.string = new std::string(yytext); return(check_type_map(*yylval.string));}

0[xX]{H}+{IS}?		      {yylval.number_int = (int)strtol(yytext, NULL, 0); return(INT_CONSTANT);}
0{D}+{IS}?		          {yylval.number_int = (int)strtol(yytext, NULL, 0); return(INT_CONSTANT);}
{D}+{IS}?		            {yylval.number_int = (int)strtol(yytext, NULL, 0); return(INT_CONSTANT);}
L?'(\\.|[^\\'])+'	      {yylval.string = new std::string(yytext); return(CHAR_LITERAL);}

{D}+{E}{FS}?		        {yylval.number_float = strtod(yytext, NULL); return(FLOAT_CONSTANT);}
{D}*"."{D}+({E})?{FS}?	{yylval.number_float = strtod(yytext, NULL); return(FLOAT_CONSTANT);}
{D}+"."{D}*({E})?{FS}?	{yylval.number_float = strtod(yytext, NULL); return(FLOAT_CONSTANT);}

L?\"(\\.|[^\\"])*\"	    { yylval.string = new std::string(yytext); return(STRING_LITERAL);}

"..."      {return(ELLIPSIS);}
">>="			 {return(RIGHT_ASSIGN);}
"<<="      {return(LEFT_ASSIGN);}
"+="			 {return(ADD_ASSIGN);}
"-="       {return(SUB_ASSIGN);}
"*="       {return(MUL_ASSIGN);}
"/="			 {return(DIV_ASSIGN);}
"%="			 {return(MOD_ASSIGN);}
"&="       {return(AND_ASSIGN);}
"^="			 {return(XOR_ASSIGN);}
"|="       {return(OR_ASSIGN);}
">>"       {return(RIGHT_OP);}
"<<"       {return(LEFT_OP);}
"++"			 {return(INC_OP);}
"--"			 {return(DEC_OP);}
"->"			 {return(PTR_OP);}
"&&"			 {return(AND_OP);}
"||"			 {return(OR_OP);}
"<="			 {return(LE_OP);}
">="			 {return(GE_OP);}
"=="			 {return(EQ_OP);}
"!="			 {return(NE_OP);}
";"			   {return(';');}
("{"|"<%") {return('{');}
("}"|"%>") {return('}');}
","			   {return(',');}
":"			   {return(':');}
"="			   {return('=');}
"("		     {return('(');}
")"			   {return(')');}
("["|"<:") {return('[');}
("]"|":>") {return(']');}
"."			   {return('.');}
"&"			   {return('&');}
"!"			   {return('!');}
"~"			   {return('~');}
"-"			   {return('-');}
"+"			   {return('+');}
"*"			   {return('*');}
"/"			   {return('/');}
"%"			   {return('%');}
"<"			   {return('<');}
">"			   {return('>');}
"^"			   {return('^');}
"|"			   {return('|');}
"?"			   {return('?');}

[ \a\b\t\v\f\n\r]		{/* ignore new lines and special sequences */}
.			              {/* ignore bad characters */}

%%

// yywrap() called when EOF of a single file reached. implement if processing multiple files.
int yywrap() {
  return 1;
}

void yyerror (char const *s)
{
  fprintf(stderr, "yyerror() called with message: %s\n", s);
  exit(1);
}
