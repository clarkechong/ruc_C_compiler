#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ast/ast_context.hpp"

#include "ast/ast_node.hpp"
#include "ast/ast_nodelist.hpp"
#include "ast/ast_type_specifier.hpp"

ast::NodePtr parseAST(std::string file_name);
