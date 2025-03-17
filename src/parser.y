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
%type <node> unary_operator

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
	| translation_unit external_declaration 	{ $1->Push(NodePtr($2)); $$ = $1; }
	;

external_declaration
	: function_definition 		{ $$ = std::move($1); }
	| declaration 				{ $$ = std::move($1); }
	;

function_definition
	: declaration_specifiers declarator compound_statement { $$ = new FunctionDefinition(); }
	// | declarator compound_statement											// ignore
	// | declaration_specifiers declarator declaration_list compound_statement 	// OLD K&R STYLE
	// | declarator declaration_list compound_statement 						// OLD K&R STYLE
	;

primary_expression
	: IDENTIFIER 			{ $$ = new Identifier(*$1); }
	| INT_CONSTANT 			{ $$ = new Integer($1); }
	| FLOAT_CONSTANT 		{ $$ = new Float($1); }
	| STRING_LITERAL 		{ $$ = new String(*$1); }
	| CHAR_LITERAL 			{ $$ = new Char(*$1); }
	| '(' expression ')'	{ $$ = std::move($2); }
	;

postfix_expression
	: primary_expression									{ $$ = std::move($1); }
	| postfix_expression '[' expression ']'					{ $$ = new ArrayAccess(NodePtr($1), NodePtr($3)); }
	| postfix_expression '(' ')'							{ $$ = new FunctionCall(NodePtr($1), nullptr); }
	| postfix_expression '(' argument_expression_list ')'	{ $$ = new FunctionCall(NodePtr($1), NodePtr($3)); }
	| postfix_expression '.' IDENTIFIER						{ /* Struct member access */ }
	| postfix_expression PTR_OP IDENTIFIER					{ /* Struct pointer access */ }
	| postfix_expression INC_OP								{ $$ = new PostInc(NodePtr($1)); }
	| postfix_expression DEC_OP								{ $$ = new PostDec(NodePtr($1)); }
	;

argument_expression_list
	: assignment_expression									{ $$ = new NodeList(NodePtr($1)); }
	| argument_expression_list ',' assignment_expression	{ $1->Push(NodePtr($3)); $$ = $1; }
	;

unary_expression
	: postfix_expression				{ $$ = std::move($1); }
	| INC_OP unary_expression			{ $$ = new PostInc(NodePtr($2)); }
	| DEC_OP unary_expression			{ $$ = new PostDec(NodePtr($2)); }
	| unary_operator unary_expression	{ if ($1) { ((UnaryOperator*)$1)->SetOperand(NodePtr($2)); $$ = $1; } else { $$ = $2; } }
	| SIZEOF unary_expression			{ $$ = new SizeOf(NodePtr($2)); }
	| SIZEOF '(' type_name ')'			{ $$ = new SizeOf(NodePtr($3)); }
	;

unary_operator
	: '&'	{ $$ = new AddressOp(); }
	| '*'	{ $$ = new DereferenceOp(); }
	| '+'	{ $$ = nullptr; } // do nothing for this - just pass the operand
	| '-'	{ $$ = new NegativeOp(); }
	| '~'	{ $$ = new BitwiseNotOp(); }
	| '!'	{ $$ = new LogicalNotOp(); }
	;

multiplicative_expression
	: unary_expression 									{ $$ = std::move($1); }
	| multiplicative_expression '*' unary_expression	{ $$ = new Multiply(NodePtr($1), NodePtr($3)); }
	| multiplicative_expression '/' unary_expression	{ $$ = new Divide(NodePtr($1), NodePtr($3)); }
	| multiplicative_expression '%' unary_expression	{ $$ = new Modulus(NodePtr($1), NodePtr($3)); }
	;

additive_expression
	: multiplicative_expression								{ $$ = std::move($1); }
	| additive_expression '+' multiplicative_expression		{ $$ = new Add(NodePtr($1), NodePtr($3)); }
	| additive_expression '-' multiplicative_expression		{ $$ = new Sub(NodePtr($1), NodePtr($3)); }
	;

shift_expression
	: additive_expression								{ $$ = std::move($1); }
	| shift_expression LEFT_OP additive_expression		{ $$ = new LeftShift(NodePtr($1), NodePtr($3)); }
	| shift_expression RIGHT_OP additive_expression		{ $$ = new RightShift(NodePtr($1), NodePtr($3)); }
	;

relational_expression
	: shift_expression									{ $$ = std::move($1); }
	| relational_expression '<' shift_expression		{ $$ = new LessThan(NodePtr($1), NodePtr($3)); }
	| relational_expression '>' shift_expression		{ $$ = new GreaterThan(NodePtr($1), NodePtr($3)); }
	| relational_expression LE_OP shift_expression		{ $$ = new LessThanEq(NodePtr($1), NodePtr($3)); }
	| relational_expression GE_OP shift_expression		{ $$ = new GreaterThanEq(NodePtr($1), NodePtr($3)); }
	;

equality_expression
	: relational_expression								{ $$ = std::move($1); }
	| equality_expression EQ_OP relational_expression	{ $$ = new Equal(NodePtr($1), NodePtr($3)); }
	| equality_expression NE_OP relational_expression	{ $$ = new NotEqual(NodePtr($1), NodePtr($3)); }
	;

and_expression
	: equality_expression						{ $$ = std::move($1); }
	| and_expression '&' equality_expression	{ $$ = new BitwiseAnd(NodePtr($1), NodePtr($3)); }
	;

exclusive_or_expression
	: and_expression								{ $$ = std::move($1); }
	| exclusive_or_expression '^' and_expression	{ $$ = new BitwiseXor(NodePtr($1), NodePtr($3)); }
	;

inclusive_or_expression
	: exclusive_or_expression								{ $$ = std::move($1); }
	| inclusive_or_expression '|' exclusive_or_expression	{ $$ = new BitwiseOr(NodePtr($1), NodePtr($3)); }
	;

logical_and_expression
	: inclusive_or_expression									{ $$ = std::move($1); }
	| logical_and_expression AND_OP inclusive_or_expression		{ $$ = new LogicalAnd(NodePtr($1), NodePtr($3)); }
	;

logical_or_expression
	: logical_and_expression								{ $$ = std::move($1); }
	| logical_or_expression OR_OP logical_and_expression	{ $$ = new LogicalOr(NodePtr($1), NodePtr($3)); }
	;

conditional_expression
	: logical_or_expression												{ $$ = std::move($1); }
	| logical_or_expression '?' expression ':' conditional_expression	{ $$ = new IfElse(); /* Use IfElse for ternary */ }
	;

assignment_expression
	: conditional_expression										{ $$ = std::move($1); }
	| unary_expression assignment_operator assignment_expression	{ $$ = new Assign(NodePtr($1), NodePtr($3)); }
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
	: assignment_expression					{ $$ = std::move($1); }
	| expression ',' assignment_expression	{ /* Comma expressions */ $$ = std::move($3); /* For now, just take the last expr */ }
	;

constant_expression
	: conditional_expression				{ $$ = std::move($1); }
	;

declaration
	: declaration_specifiers ';'						{ $$ = new Declaration(NodePtr($1), nullptr); }
	| declaration_specifiers init_declarator ';'		{ $$ = new Declaration(NodePtr($1), NodePtr($2)); }
	;

declaration_specifiers // only considering single types
	// : storage_class_specifier
	// | storage_class_specifier declaration_specifiers
	: TYPEDEF declaration_specifiers				{ }
	| type_specifier								{ $$ = std::move($1); }
	| type_specifier declaration_specifiers			{ }
	// | type_qualifier
	// | type_qualifier declaration_specifiers
	;

// init_declarator_list
// 	: init_declarator								{ }
// 	| init_declarator_list ',' init_declarator		{ }
// 	;

init_declarator
	: declarator					{ $$ = std::move($1); }
	| declarator '=' initializer	{ /* Add initializer to declarator */ }
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
	| struct_specifier		{ $$ = std::move($1); }
	| enum_specifier		{ $$ = std::move($1); }
	| TYPE_NAME				{ /* Type name from typedef */ }
	;

struct_specifier
	: STRUCT IDENTIFIER '{' struct_declaration_list '}' 	{ /* Struct definition */ }
	| STRUCT '{' struct_declaration_list '}' 				{ /* Anonymous struct */ }
	| STRUCT IDENTIFIER 									{ /* Struct reference */ }
	;

struct_declaration_list
	: struct_declaration									{ $$ = new NodeList(NodePtr($1)); }
	| struct_declaration_list struct_declaration			{ $1->Push(NodePtr($2)); $$ = $1; }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'	{ /* Struct member declaration */ }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list				{ $$ = new NodeList(NodePtr($1)); }
	| type_specifier										{ $$ = new NodeList(NodePtr($1)); }
	;

struct_declarator_list
	: struct_declarator										{ $$ = new NodeList(NodePtr($1)); }
	| struct_declarator_list ',' struct_declarator			{ $1->Push(NodePtr($3)); $$ = $1; }
	;

struct_declarator
	: declarator											{ $$ = std::move($1); }
	| ':' constant_expression								{ /* Bit field */ }
	| declarator ':' constant_expression					{ /* Named bit field */ }
	;

enum_specifier
	: ENUM '{' enumerator_list '}'					{ /* Enum definition */ }
	| ENUM IDENTIFIER '{' enumerator_list '}'		{ /* Named enum definition */ }
	| ENUM IDENTIFIER								{ /* Enum reference */ }
	;

enumerator_list
	: enumerator						{ $$ = new NodeList(NodePtr($1)); }
	| enumerator_list ',' enumerator	{ $1->Push(NodePtr($3)); $$ = $1; }
	;

enumerator
	: IDENTIFIER							{ /* Enum value */ }
	| IDENTIFIER '=' constant_expression	{ /* Enum value with explicit value */ }
	;

// type_qualifier
// 	: CONST
// 	| VOLATILE
// 	;

declarator
	: pointer direct_declarator		{ $$ = new PointerDeclarator(NodePtr($1), NodePtr($2)); }
	| direct_declarator				{ $$ = std::move($1); }
	;

direct_declarator
	: IDENTIFIER										{ $$ = new Identifier(*$1); } // new Identifier
	| '(' declarator ')' 								{ $$ = std::move($2); }	// { /* $$ = std::move($2) */ }
	| direct_declarator '[' constant_expression ']' 	{ $$ = new ArrayDeclarator(); /* Array with size */ }
	| direct_declarator '[' ']' 						{ $$ = new ArrayDeclarator(); /* Array without size */ }
	| direct_declarator '(' parameter_list ')'			{ $$ = new FunctionDeclarator(); /* Function with parameters */ }
	| direct_declarator '(' ')'							{ $$ = new FunctionDeclarator(); /* Function without parameters */ }
	// | direct_declarator '(' identifier_list ')' // OLD K&R STYLE
	;

pointer
	: '*'			{ $$ = new Pointer(); }
	| '*' pointer	{ $$ = new Pointer(); /* Nested pointers */ }
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
	: parameter_declaration								{ $$ = new NodeList(NodePtr($1)); }
	| parameter_list ',' parameter_declaration			{ $1->Push(NodePtr($3)); $$ = $1; }
	;

parameter_declaration
	: declaration_specifiers declarator					{ /* Parameter with name */ }
	| declaration_specifiers abstract_declarator		{ /* Parameter with abstract declarator */ }
	| declaration_specifiers							{ /* Parameter with type only */ }
	;

// NO LONGER REQURIED AS ONLY USED WITHIN K&R STYLE (DIRECT DECLARATOR) FUNCTION DECLARATION
// identifier_list
// 	: IDENTIFIER
// 	| identifier_list ',' IDENTIFIER
// 	;

type_name
	: specifier_qualifier_list							{ $$ = std::move($1); }
	| specifier_qualifier_list abstract_declarator		{ /* Type with abstract declarator */ }
	;

abstract_declarator
	: pointer								{ $$ = std::move($1); }
	| direct_abstract_declarator			{ $$ = std::move($1); }
	| pointer direct_abstract_declarator	{ /* Pointer to abstract declarator */ }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'								{ $$ = std::move($2); }
	| '[' ']'													{ /* Array type */ }
	| '[' constant_expression ']'								{ /* Array type with size */ }
	| direct_abstract_declarator '[' ']'						{ /* Array of abstract type */ }
	| direct_abstract_declarator '[' constant_expression ']'	{ /* Array of abstract type with size */ }
	| '(' ')'													{ /* Function type without parameters */ }
	| '(' parameter_list ')'									{ /* Function type with parameters */ }
	| direct_abstract_declarator '(' ')'						{ /* Function returning abstract type without parameters */ }
	| direct_abstract_declarator '(' parameter_list ')'			{ /* Function returning abstract type with parameters */ }
	;

initializer
	: assignment_expression								{ $$ = std::move($1); }
	| '{' initializer_list '}'							{ $$ = std::move($2); /* Array initializer */ }
	| '{' initializer_list ',' '}'						{ $$ = std::move($2); /* Array initializer with trailing comma */ }
	;

initializer_list
	: initializer						{ $$ = new NodeList(NodePtr($1)); }
	| initializer_list ',' initializer	{ $1->Push(NodePtr($3)); $$ = $1; }
	;

statement
	: labeled_statement			{ $$ = std::move($1); }
	| compound_statement		{ $$ = std::move($1); }
	| expression_statement		{ $$ = std::move($1); }
	| selection_statement		{ $$ = std::move($1); }
	| iteration_statement		{ $$ = std::move($1); }
	| jump_statement			{ $$ = std::move($1); }
	;

labeled_statement
	: IDENTIFIER ':' statement					{ /* Labeled statement */ }
	| CASE constant_expression ':' statement	{ /* Case statement */ }
	| DEFAULT ':' statement						{ /* Default case */ }
	;

compound_statement // compound statement = block = scope
	: '{' '}' 									{ $$ = new Scope(); }				// { /* new scope null */}
	| '{' statement_list '}' 					{ }				// { /* new scope initiate with STATEMENTS */ }
	| '{' declaration_list '}' 					{ }				// { /* new scope initiate with DECLARATIONS */ }
	| '{' declaration_list statement_list '}' 	{ }				// { /* new scope initiate with STATEMENTS + DECLARATIONS $1 and $2 */ }
	;

declaration_list
	: declaration					{ $$ = new NodeList(NodePtr($1)); }
	| declaration_list declaration	{ $1->Push(NodePtr($2)); $$ = $1; }
	;

statement_list
	: statement						{ $$ = new NodeList(NodePtr($1)); }
	| statement_list statement		{ $1->Push(NodePtr($2)); $$ = $1; }
	;

expression_statement
	: ';'				{ $$ = nullptr; }
	| expression ';'	{ $$ = std::move($1); }
	;

selection_statement
	: IF '(' expression ')' statement						{ $$ = new IfElse(); /* Set condition and true branch */ }
	| IF '(' expression ')' statement ELSE statement		{ $$ = new IfElse(); /* Set condition, true and false branches */ }
	| SWITCH '(' expression ')' statement					{ $$ = new Switch(); /* Set expression and cases */ }
	;

iteration_statement
	: WHILE '(' expression ')' statement											{ $$ = new While(); /* Set condition and body */ }
	| DO statement WHILE '(' expression ')' ';'										{ $$ = new DoWhile(); /* Set body and condition */ }
	| FOR '(' expression_statement expression_statement ')' statement				{ $$ = new For(); /* Set init, condition, and body */ }
	| FOR '(' expression_statement expression_statement expression ')' statement 	{ $$ = new For(); /* Set init, condition, step, and body */ }
	;

jump_statement
	// : GOTO IDENTIFIER ';'
	: CONTINUE ';'				{ $$ = new Continue(); }
	| BREAK ';'					{ $$ = new Break(); }
	| RETURN ';'				{ $$ = new Return(nullptr); }
	| RETURN expression ';'		{ $$ = new Return(NodePtr($2)); }
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