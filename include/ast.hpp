#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ast/type/ast_type_specifier.hpp"

#include "ast/ast_context.hpp"
#include "ast/ast_declaration.hpp"
#include "ast/ast_declarator.hpp"
#include "ast/ast_node.hpp"
#include "ast/ast_nodelist.hpp"

#include "ast/array/ast_array_declarator.hpp"
#include "ast/array/ast_array_access.hpp"
#include "ast/array/ast_array_init_list.hpp"

#include "ast/block/switch/ast_case.hpp"
#include "ast/block/switch/ast_default.hpp"
#include "ast/block/switch/ast_switch.hpp"

#include "ast/block/ast_do_while.hpp"
#include "ast/block/ast_for.hpp"
#include "ast/block/ast_if_else.hpp"
#include "ast/block/ast_scope.hpp"
#include "ast/block/ast_while.hpp"

#include "ast/primary/ast_char.hpp"
#include "ast/primary/ast_float.hpp"
#include "ast/primary/ast_identifier.hpp"
#include "ast/primary/ast_integer.hpp"
#include "ast/primary/ast_string.hpp"


ast::NodePtr ParseAST(std::string file_name);
