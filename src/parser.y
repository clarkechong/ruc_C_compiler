%code requires{
    #include "ast.hpp"
	
	using namespace ast;

    extern Node* g_root;
    extern FILE* yyin;

    int yylex(void);
	int yylex_destroy(void);
    void yyerror(const char*);
}

// Represents the value associated with any kind of AST node.
%union {
	Node*       		node;
	NodeList*   		node_list;
	int          		number_int;
	double       		number_float;
	std::string* 		string;
	TypeSpecifier		type_specifier;
	yytokentype  		token;
}

%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL CHAR_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME
%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <node> primary_expression postfix_expression unary_expression
%type <node> multiplicative_expression additive_expression shift_expression
%type <node> relational_expression equality_expression and_expression
%type <node> exclusive_or_expression inclusive_or_expression logical_and_expression
%type <node> logical_or_expression conditional_expression assignment_expression
%type <node> expression constant_expression

%type <node> declaration init_declarator
%type <node> declaration_specifiers type_specifier
%type <node> struct_specifier struct_declaration
%type <node> struct_declarator declarator
%type <node> enum_specifier enumerator direct_declarator pointer

%type <node> parameter_declaration type_name abstract_declarator direct_abstract_declarator
%type <node> initializer statement labeled_statement compound_statement
%type <node> expression_statement selection_statement iteration_statement
%type <node> jump_statement external_declaration function_definition

%type <node_list> translation_unit struct_declaration_list argument_expression_list
%type <node_list> specifier_qualifier_list struct_declarator_list
%type <node_list> enumerator_list parameter_list
%type <node_list> initializer_list declaration_list statement_list

%type <string> IDENTIFIER STRING_LITERAL CHAR_LITERAL
%type <number_int> INT_CONSTANT
%type <number_float> FLOAT_CONSTANT

%start ROOT

%%

ROOT
	: translation_unit 		{ g_root = $1; }
	;

translation_unit
	: external_declaration 						{ $$ = new NodeList(NodePtr($1)); }
	| translation_unit external_declaration 	{ $1->Push(NodePtr($2)); }
	;

external_declaration
	: function_definition 		{ $$ = $1; }
	| declaration 				{ $$ = $1; }
	;

function_definition
	: declaration_specifiers declarator compound_statement { }
	// | declarator compound_statement											// ignore
	// | declaration_specifiers declarator declaration_list compound_statement 	// OLD K&R STYLE
	// | declarator declaration_list compound_statement 						// OLD K&R STYLE
	;

primary_expression
	: IDENTIFIER 			{ new Identifier(*$1); }
	| INT_CONSTANT 			{ new Integer($1); }
	| FLOAT_CONSTANT 		{ new Float($1); }
	| STRING_LITERAL 		{ new String(*$1); }
	| CHAR_LITERAL 			{ new Char(*$1); }
	| '(' expression ')'	{ $$ = $2; }
	;

postfix_expression
	: primary_expression									{ }
	| postfix_expression '[' expression ']'					{ }
	| postfix_expression '(' ')'							{ }
	| postfix_expression '(' argument_expression_list ')'	{ }
	| postfix_expression '.' IDENTIFIER						{ }
	| postfix_expression PTR_OP IDENTIFIER					{ }
	| postfix_expression INC_OP								{ }
	| postfix_expression DEC_OP								{ }
	;

argument_expression_list
	: assignment_expression									{ }
	| argument_expression_list ',' assignment_expression	{ }
	;

unary_expression
	: postfix_expression				{ }
	| INC_OP unary_expression			{ }
	| DEC_OP unary_expression			{ }
	| unary_operator unary_expression	{ }
	| SIZEOF unary_expression			{ }
	| SIZEOF '(' type_name ')'			{ }
	;

unary_operator
	: '&'	{ }
	| '*'	{ }
	| '+'	{ } // do nothing for this
	| '-'	{ }
	| '~'	{ }
	| '!'	{ }
	;

multiplicative_expression
	: unary_expression 									{ }
	| multiplicative_expression '*' unary_expression	{ }
	| multiplicative_expression '/' unary_expression	{ }
	| multiplicative_expression '%' unary_expression	{ }
	;

additive_expression
	: multiplicative_expression								{ }
	| additive_expression '+' multiplicative_expression		{ }
	| additive_expression '-' multiplicative_expression		{ }
	;

shift_expression
	: additive_expression								{ }
	| shift_expression LEFT_OP additive_expression		{ }
	| shift_expression RIGHT_OP additive_expression		{ }
	;

relational_expression
	: shift_expression									{ }
	| relational_expression '<' shift_expression		{ }
	| relational_expression '>' shift_expression		{ }
	| relational_expression LE_OP shift_expression		{ }
	| relational_expression GE_OP shift_expression		{ }
	;

equality_expression
	: relational_expression								{ }
	| equality_expression EQ_OP relational_expression	{ }
	| equality_expression NE_OP relational_expression	{ }
	;

and_expression
	: equality_expression						{ }
	| and_expression '&' equality_expression	{ }
	;

exclusive_or_expression
	: and_expression								{ }
	| exclusive_or_expression '^' and_expression	{ }
	;

inclusive_or_expression
	: exclusive_or_expression								{ }
	| inclusive_or_expression '|' exclusive_or_expression	{ }
	;

logical_and_expression
	: inclusive_or_expression									{ }
	| logical_and_expression AND_OP inclusive_or_expression		{ }
	;

logical_or_expression
	: logical_and_expression								{ }
	| logical_or_expression OR_OP logical_and_expression	{ }
	;

conditional_expression
	: logical_or_expression												{ }
	| logical_or_expression '?' expression ':' conditional_expression	{ }
	;

assignment_expression
	: conditional_expression										{ }
	| unary_expression assignment_operator assignment_expression	{ }
	;

assignment_operator
	: '='				{ }
	| MUL_ASSIGN		{ } // for these, just do e.g. new MulOperator(), then in assignment expression assign left_ and right_ 
	| DIV_ASSIGN		{ }
	| MOD_ASSIGN		{ }
	| ADD_ASSIGN		{ }
	| SUB_ASSIGN		{ }
	| LEFT_ASSIGN		{ }
	| RIGHT_ASSIGN		{ }
	| AND_ASSIGN		{ }
	| XOR_ASSIGN		{ }
	| OR_ASSIGN			{ }
	;

expression
	: assignment_expression					{ }
	| expression ',' assignment_expression	{ }
	;

constant_expression
	: conditional_expression				{ }
	;

declaration
	: declaration_specifiers ';'						{ }
	| declaration_specifiers init_declarator_list ';'	{ }
	;

declaration_specifiers // only considering single types
	// : storage_class_specifier
	// | storage_class_specifier declaration_specifiers
	: TYPEDEF declaration_specifiers				{ }
	| type_specifier								{ $$ = $1; }
	| type_specifier declaration_specifiers			{ }
	// | type_qualifier
	// | type_qualifier declaration_specifiers
	;

init_declarator_list
	: init_declarator								{ }
	| init_declarator_list ',' init_declarator		{ }
	;

init_declarator
	: declarator					{ }
	| declarator '=' initializer	{ }
	;

// storage_class_specifier
// 	: TYPEDEF
// 	| EXTERN
// 	| STATIC
// 	| AUTO
// 	| REGISTER
// 	;

type_specifier
	: VOID					{ $$ = new DeclarationType(TypeSpecifier::VOID); }
	| CHAR					{ $$ = new DeclarationType(TypeSpecifier::CHAR); }
	// | SHORT
	| INT					{ $$ = new DeclarationType(TypeSpecifier::INT); }
	// | LONG
	| FLOAT					{ $$ = new DeclarationType(TypeSpecifier::FLOAT); }
	| DOUBLE				{ $$ = new DeclarationType(TypeSpecifier::DOUBLE); }
	| SIGNED				{ $$ = new DeclarationType(TypeSpecifier::INT); }
	| UNSIGNED				{ $$ = new DeclarationType(TypeSpecifier::UNSIGNED_INT); }
	| struct_specifier		{ }
	| enum_specifier		{ }
	| TYPE_NAME				{ }
	;

struct_specifier
	: STRUCT IDENTIFIER '{' struct_declaration_list '}' 	{ }
	| STRUCT '{' struct_declaration_list '}' 				{ }
	| STRUCT IDENTIFIER 									{ }
	;

struct_declaration_list
	: struct_declaration									{ }
	| struct_declaration_list struct_declaration			{ }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'	{ }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list				{ }
	| type_specifier										{ }
	;

struct_declarator_list
	: struct_declarator										{ }
	| struct_declarator_list ',' struct_declarator			{ }
	;

struct_declarator
	: declarator											{ }
	| ':' constant_expression								{ }
	| declarator ':' constant_expression					{ }
	;

enum_specifier
	: ENUM '{' enumerator_list '}'					{ }
	| ENUM IDENTIFIER '{' enumerator_list '}'		{ }
	| ENUM IDENTIFIER								{ }
	;

enumerator_list
	: enumerator						{ }
	| enumerator_list ',' enumerator	{ }
	;

enumerator
	: IDENTIFIER							{ }
	| IDENTIFIER '=' constant_expression	{ }
	;

// type_qualifier
// 	: CONST
// 	| VOLATILE
// 	;

declarator
	: pointer direct_declarator		{ }
	| direct_declarator				{ }
	;

direct_declarator
	: IDENTIFIER										{ } // new Identifier
	| '(' declarator ')' 								{ }	// { /* $$ = $2 */ }
	| direct_declarator '[' constant_expression ']' 	{ }	// array declarator
	| direct_declarator '[' ']' 						{ }	// array declarator
	| direct_declarator '(' parameter_list ')'			{ }	// function declarator
	| direct_declarator '(' ')'							{ }	// function declarator
	// | direct_declarator '(' identifier_list ')' // OLD K&R STYLE
	;

pointer
	: '*'			{ }
	| '*' pointer	{ }
	// | '*' type_qualifier_list
	// | '*' type_qualifier_list pointer
	;

// type_qualifier_list /* this would have referred to "const volatile <something>" */
// 	: type_qualifier
// 	| type_qualifier_list type_qualifier
// 	;


// parameter_type_list
// 	: parameter_list
// 	| parameter_list ',' ELLIPSIS
// 	;

parameter_list
	: parameter_declaration								{ }
	| parameter_list ',' parameter_declaration			{ }
	;

parameter_declaration
	: declaration_specifiers declarator					{ }
	| declaration_specifiers abstract_declarator		{ }
	| declaration_specifiers							{ }
	;

// NO LONGER REQURIED AS ONLY USED WITHIN K&R STYLE (DIRECT DECLARATOR) FUNCTION DECLARATION
// identifier_list
// 	: IDENTIFIER
// 	| identifier_list ',' IDENTIFIER
// 	;

type_name
	: specifier_qualifier_list							{ }
	| specifier_qualifier_list abstract_declarator		{ }
	;

abstract_declarator
	: pointer								{ }
	| direct_abstract_declarator			{ }
	| pointer direct_abstract_declarator	{ }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'								{ }
	| '[' ']'													{ }
	| '[' constant_expression ']'								{ }
	| direct_abstract_declarator '[' ']'						{ }
	| direct_abstract_declarator '[' constant_expression ']'	{ }
	| '(' ')'													{ }
	| '(' parameter_list ')'									{ }
	| direct_abstract_declarator '(' ')'						{ }
	| direct_abstract_declarator '(' parameter_list ')'			{ }
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'			{ }
	| '{' initializer_list ',' '}'		{ }
	;

initializer_list
	: initializer						{ }
	| initializer_list ',' initializer	{ }
	;

statement
	: labeled_statement			{ }
	| compound_statement		{ }
	| expression_statement		{ }
	| selection_statement		{ }
	| iteration_statement		{ }
	| jump_statement			{ }
	;

labeled_statement
	: IDENTIFIER ':' statement					{ }
	| CASE constant_expression ':' statement	{ }
	| DEFAULT ':' statement						{ }
	;

compound_statement // compound statement = block = scope
	: '{' '}' 									{ }				// { /* new scope null */}
	| '{' statement_list '}' 					{ }				// { /* new scope initiate with STATEMENTS */ }
	| '{' declaration_list '}' 					{ }				// { /* new scope initiate with DECLARATIONS */ }
	| '{' declaration_list statement_list '}' 	{ }				// { /* new scope initiate with STATEMENTS + DECLARATIONS $1 and $2 */ }
	;

declaration_list
	: declaration					{ }
	| declaration_list declaration	{ }
	;

statement_list
	: statement						{ }
	| statement_list statement		{ }
	;

expression_statement
	: ';'				{ }
	| expression ';'	{ }
	;

selection_statement
	: IF '(' expression ')' statement						{ }
	| IF '(' expression ')' statement ELSE statement		{ }
	| SWITCH '(' expression ')' statement					{ }
	;

iteration_statement
	: WHILE '(' expression ')' statement											{ }
	| DO statement WHILE '(' expression ')' ';'										{ }
	| FOR '(' expression_statement expression_statement ')' statement				{ }
	| FOR '(' expression_statement expression_statement expression ')' statement 	{ }
	;

jump_statement
	// : GOTO IDENTIFIER ';'
	: CONTINUE ';'				{ }
	| BREAK ';'					{ }
	| RETURN ';'				{ }
	| RETURN expression ';'		{ }
	;

%%

Node* g_root; // outside of parseAST so that yyparse() can access g_root

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