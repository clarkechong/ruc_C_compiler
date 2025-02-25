// Adapted from: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

%code requires{
    #include "ast.hpp"

	using namespace ast;

    extern Node* g_root;
    extern FILE* yyin;
    int yylex(void);
    void yyerror(const char*);
	int yylex_destroy(void);
}

// Represents the value associated with any kind of AST node.
%union{
  Node*        	node;
  NodeList*    	node_list;
  int          	number_int;
  double       	number_float;
  std::string* 	string;
  TypeSpecifier	type_specifier;
  yytokentype  	token;
}

%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token TYPE_NAME TYPEDEF EXTERN STATIC AUTO REGISTER SIZEOF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%start ROOT
%%

ROOT
  : 

%%

Node* g_root;

NodePtr ParseAST(std::string file_name)
{
  yyin = fopen(file_name.c_str(), "r");
  if(yyin == NULL){
    std::cerr << "Couldn't open input file: " << file_name << std::endl;
    exit(1);
  }
  g_root = nullptr;
  yyparse();
  fclose(yyin);
  yylex_destroy();
  return NodePtr(g_root);
}
