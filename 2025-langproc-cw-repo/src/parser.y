// Adapted from: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

// TODO: you can either continue adding to this grammar file or
// rename parser_full.y to parser.y once you're happy with
// how this example works.

%code requires{
    #include "ast.hpp"

	using namespace ast;

	extern int yylineno;
	extern char* yytext;
    extern Node* g_root;
    extern FILE* yyin;
    int yylex(void);
    void yyerror(const char*);
	int yylex_destroy(void);
}

%union{
  Node*				node;
  NodeList*			node_list;
  int          		number_int;
  double       		number_float;
  std::string*		string;
  TypeSpecifier 	type_specifier;
  yytokentype  		token;
}

%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token TYPE_NAME TYPEDEF EXTERN STATIC AUTO REGISTER SIZEOF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <node> external_declaration function_definition primary_expression postfix_expression
%type <node> unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression
%type <node> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> conditional_expression assignment_expression expression declarator direct_declarator statement compound_statement jump_statement declaration Assignment
%type <node> constant_initialiser
%type <node> selection_statement iteration_statement
%type <node> parameter_declaration argument_expression

%type <node_list> statement_list declaration_list parameter_list translation_unit argument_expression_list

%type <number_int> INT_CONSTANT STRING_LITERAL
%type <number_float> FLOAT_CONSTANT
%type <string> IDENTIFIER
%type <type_specifier> type_specifier declaration_specifiers


%start ROOT
%%

ROOT
    : translation_unit { g_root = $1; }

translation_unit
	: external_declaration { $$ = new NodeList(NodePtr($1));}
    | translation_unit external_declaration { $1->PushBack(NodePtr($2)); $$=$1; }
	;

external_declaration
	: function_definition { $$ = $1; }
	| declaration {$$ = $1;}
	| declaration_specifiers declarator declaration_list ';' {
		$$ = new Externdef($1, NodePtr($2), NodePtr($3));
	}
	| declaration_specifiers declarator ';' {
		$$ = new Externdef($1,NodePtr($2), nullptr);
	}
	;

function_definition
	: declaration_specifiers declarator compound_statement {
		$$ = new FunctionDefinition($1, NodePtr($2), nullptr , NodePtr($3));
	}
    | declaration_specifiers declarator declaration_list compound_statement {
        $$ = new FunctionDefinition($1,NodePtr($2),NodePtr($3), NodePtr($4));
    }
	;

declaration_specifiers
	: type_specifier { $$ = $1; }
	;

type_specifier
	: INT {
		$$ = TypeSpecifier::INT;
	}
	;

declarator
	: direct_declarator { $$ = $1; }
	;

declaration
	:declaration_specifiers IDENTIFIER ';' {
		$$ = new Variable($1,std::move(*$2));
		delete $2;
	}
	;



declaration_list
	: declaration{
		$$ = new NodeList(NodePtr($1));
	}
	| declaration_list declaration { $1->PushBack(NodePtr($2)); $$=$1; }
	;

constant_initialiser
	:declaration_specifiers declarator '='  expression ';'{
		$$ = new InitDecl($1,NodePtr($2),NodePtr($4));
	}

Assignment
	: declarator '=' expression ';' {
		$$ = new Assignment(NodePtr($1),NodePtr($3));
	}


direct_declarator
	: IDENTIFIER {
		$$ = new Identifier(std::move(*$1));
		delete $1;
	}
	| direct_declarator '(' ')' {
		$$ = new DirectDeclarator(NodePtr($1),nullptr);
	}
	| direct_declarator '(' parameter_list ')'{
        $$ = new DirectDeclarator(NodePtr($1),NodePtr($3));
    }
	;

parameter_list
	: parameter_declaration {$$ = new NodeList(NodePtr($1)); }
	| parameter_list ',' parameter_declaration{
        $1->PushBack(NodePtr($3)); $$=$1;
    }
	;

parameter_declaration
	: declaration_specifiers declarator{
        $$ = new ParamDecl($1,NodePtr($2));
    }
	| declaration_specifiers
	;

statement_list
	: statement { $$ = new NodeList(NodePtr($1)); }
	| declaration { $$ = new NodeList(NodePtr($1)); }
	| constant_initialiser { $$ = new NodeList(NodePtr($1)); }
	| Assignment { $$ = new NodeList(NodePtr($1)); }
	| statement_list statement { $1->PushBack(NodePtr($2)); $$=$1; }
	| statement_list declaration { $1->PushBack(NodePtr($2)); $$=$1; }
	| statement_list Assignment { $1->PushBack(NodePtr($2)); $$=$1; }
	| statement_list constant_initialiser { $1->PushBack(NodePtr($2)); $$=$1; }
	;

statement
	: jump_statement { $$ = $1; }
	| selection_statement { $$ = $1;}
	| compound_statement { $$ = $1;}
	| iteration_statement {$$ = $1;}
	;

compound_statement
	: '{' statement_list '}' { $$ = $2; }
	;

selection_statement
	: IF '(' expression ')' statement{
		$$ = new EILF(NodePtr($3),NodePtr($5),nullptr);
	}
	| IF '(' expression ')' statement ELSE statement{
		$$ = new EILF(NodePtr($3),NodePtr($5),NodePtr($7));
	}
	;

iteration_statement
	: WHILE '(' expression ')' statement{
		$$ = new Whilefunc(NodePtr($3),NodePtr($5));
	}

jump_statement
	: RETURN ';' {
		$$ = new ReturnStatement(nullptr);
	}
	| RETURN expression ';' {
		$$ = new ReturnStatement(NodePtr($2));
	}
	;

primary_expression
	: INT_CONSTANT {
		$$ = new IntConstant($1);
	}
	| IDENTIFIER {
		$$ = new Identifier(std::move(*$1));
		delete $1;
    }
	;

postfix_expression
	: primary_expression
	| postfix_expression INC_OP {
		$$ = new Incr(NodePtr($1));
	}
    | postfix_expression '(' ')' {
        $$ = new Funcprim(NodePtr($1),nullptr);
    }
    | postfix_expression '(' argument_expression_list ')' {
        $$ = new Funcprim(NodePtr($1),NodePtr($3));
    }
	;

argument_expression_list
    : argument_expression {$$ = new NodeList(NodePtr($1)); }
    | argument_expression_list ',' argument_expression{
        $1->PushBack(NodePtr($3)); $$=$1;
    }
    ;

argument_expression
	: assignment_expression {
		$$ = new Argdecl(NodePtr($1));
	}
	;

unary_expression
	: postfix_expression
	| '-' unary_expression {
		$$ = new Unary(NodePtr($2));
	}
	;

cast_expression
	: unary_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression{
		$$ = new Multiply(NodePtr($1),NodePtr($3));
	}
	| multiplicative_expression '/' cast_expression{
		$$ = new Divide(NodePtr($1),NodePtr($3));
	}
	| multiplicative_expression '%' cast_expression{
		$$ = new Modulus(NodePtr($1),NodePtr($3));
	}
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression{
		$$ = new Addition(NodePtr($1),NodePtr($3));
	}
	| additive_expression '-' multiplicative_expression{
		$$ = new Subtraction(NodePtr($1),NodePtr($3));
	}
	;

shift_expression
	: additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression  '>' shift_expression {
		$$ = new Greater(NodePtr($1),NodePtr($3));
	}
	| relational_expression  GE_OP shift_expression {
		$$ = new Geq(NodePtr($1),NodePtr($3));
	}
	| relational_expression  '<' shift_expression {
		$$ = new Less(NodePtr($1),NodePtr($3));
	}
	| relational_expression  LE_OP shift_expression {
		$$ = new Leq(NodePtr($1),NodePtr($3));
	}
	;

equality_expression
	: relational_expression
	| equality_expression  EQ_OP relational_expression{
		$$ = new Equality(NodePtr($1),NodePtr($3));
	}
	| equality_expression  NE_OP relational_expression{
		$$ = new Neq(NodePtr($1),NodePtr($3));
	}
	;

and_expression
	: equality_expression
	;

exclusive_or_expression
	: and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	;

conditional_expression
	: logical_or_expression
	;

assignment_expression
	: conditional_expression
	;

expression
	: assignment_expression
	;

%%

Node* g_root;

void yyerror (const char *s)
{
  std::cerr << "Error: " << s << " at line " << yylineno;
  std::cerr << " near '" << yytext << "'" << std::endl;
  std::exit(1);
}

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
