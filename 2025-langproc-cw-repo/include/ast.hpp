#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>


#include "ast_direct_declarator.hpp"
#include "ast_function_definition.hpp"
#include "ast_identifier.hpp"
#include "ast_jump_statement.hpp"
#include "ast_node.hpp"
#include "ast_type_specifier.hpp"
#include "ast_constant.hpp"
#include "ast_context.hpp"
#include "ast_variable.hpp"
#include "ast_symboltable.hpp"
#include "ast_initdeclaration.hpp"
#include "ast_assignment.hpp"
#include "ast_externdef.hpp"
#include "ast_paramdecl.hpp"
#include "ast_argdecl.hpp"
#include "ast_funcprim.hpp"
#include "ast_globarr.hpp"
#include "ast_array.hpp"
#include "ast_localarrdecl.hpp"
#include "ast_arrayassign.hpp"
#include "Operators/Arithmetic/ast_addition.hpp"
#include "Operators/Arithmetic/ast_subtraction.hpp"
#include "Operators/Arithmetic/ast_multiply.hpp"
#include "Operators/Arithmetic/ast_divide.hpp"
#include "Operators/Arithmetic/ast_modulus.hpp"
#include "Operators/Arithmetic/ast_unary.hpp"
#include "Operators/Arithmetic/ast_incr.hpp"
#include "Operators/Arithmetic/ast_decr.hpp"
#include "Operators/Comparison/ast_equality.hpp"
#include "Operators/Comparison/ast_neq.hpp"
#include "Operators/Comparison/ast_graa.hpp"
#include "Operators/Comparison/ast_less.hpp"
#include "Operators/Comparison/ast_geq.hpp"
#include "Operators/Comparison/ast_leq.hpp"
#include "Branch/ast_if.hpp"
#include "Branch/ast_while.hpp"



ast::NodePtr ParseAST(std::string file_name);
