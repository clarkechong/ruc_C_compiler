#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ast/type/ast_type_specifier.hpp"
#include "ast/type/ast_declaration_type.hpp"

#include "ast/ast_context.hpp"
#include "ast/ast_declaration.hpp"
#include "ast/ast_declarator.hpp"
#include "ast/ast_init_declarator.hpp"
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

#include "ast/function/ast_function_call.hpp"
#include "ast/function/ast_function_declarator.hpp"
#include "ast/function/ast_function_definition.hpp"
#include "ast/function/ast_function_parameter.hpp"

#include "ast/operator/ast_assign.hpp"
#include "ast/operator/ast_binary_operator.hpp"
#include "ast/operator/ast_unary_operator.hpp"

#include "ast/operator/binary_operation/ast_add.hpp"
#include "ast/operator/binary_operation/ast_bitwise_and.hpp"
#include "ast/operator/binary_operation/ast_bitwise_or.hpp"
#include "ast/operator/binary_operation/ast_bitwise_xor.hpp"
#include "ast/operator/binary_operation/ast_divide.hpp"
#include "ast/operator/binary_operation/ast_equal.hpp"
#include "ast/operator/binary_operation/ast_greater_than.hpp"
#include "ast/operator/binary_operation/ast_greater_than_eq.hpp"
#include "ast/operator/binary_operation/ast_left_shift.hpp"
#include "ast/operator/binary_operation/ast_less_than.hpp"
#include "ast/operator/binary_operation/ast_less_than_eq.hpp"
#include "ast/operator/binary_operation/ast_logical_and.hpp"
#include "ast/operator/binary_operation/ast_logical_or.hpp"
#include "ast/operator/binary_operation/ast_modulus.hpp"
#include "ast/operator/binary_operation/ast_multiply.hpp"
#include "ast/operator/binary_operation/ast_not_equal.hpp"
#include "ast/operator/binary_operation/ast_right_shift.hpp"
#include "ast/operator/binary_operation/ast_sub.hpp"

#include "ast/operator/unary_operation/ast_address_op.hpp"
#include "ast/operator/unary_operation/ast_bitwise_not_op.hpp"
#include "ast/operator/unary_operation/ast_dereference_op.hpp"
#include "ast/operator/unary_operation/ast_logical_not_op.hpp"
#include "ast/operator/unary_operation/ast_negative_op.hpp"
#include "ast/operator/unary_operation/ast_post_dec.hpp"
#include "ast/operator/unary_operation/ast_post_inc.hpp"
#include "ast/operator/unary_operation/ast_sizeof.hpp"

#include "ast/pointer/ast_pointer.hpp"
#include "ast/pointer/ast_pointer_declarator.hpp"

#include "ast/primary/ast_char.hpp"
#include "ast/primary/ast_float.hpp"
#include "ast/primary/ast_identifier.hpp"
#include "ast/primary/ast_integer.hpp"
#include "ast/primary/ast_string.hpp"

#include "ast/statement/ast_break.hpp"
#include "ast/statement/ast_continue.hpp"
#include "ast/statement/ast_return.hpp"

ast::NodePtr ParseAST(std::string file_name);