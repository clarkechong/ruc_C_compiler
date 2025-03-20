#include "ast/array/ast_array_declarator.hpp"
#include "ast/primary/ast_identifier.hpp"
#include "ast/primary/ast_integer.hpp"

namespace ast {

ArrayDeclarator::ArrayDeclarator() 
    : direct_declarator_(nullptr), constant_expression_(nullptr)
{
}

ArrayDeclarator::ArrayDeclarator(NodePtr direct_declarator, NodePtr constant_expression)
    : direct_declarator_(std::move(direct_declarator)), constant_expression_(std::move(constant_expression))
{
}

void ArrayDeclarator::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    if (direct_declarator_) {
        direct_declarator_->EmitRISCV(stream, dst_reg, context);
    }
}

void ArrayDeclarator::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "ArrayDeclarator [" << std::endl;
    
    stream << indent << "Direct Declarator:" << std::endl;
    if (direct_declarator_) {
        direct_declarator_->Print(stream, indent++);
    } else {
        stream << indent++ << "null" << std::endl;
    }
    
    stream << indent << "Size Expression:" << std::endl;
    if (constant_expression_) {
        constant_expression_->Print(stream, indent++);
    } else {
        stream << indent++ << "null" << std::endl;
    }
    
    stream << indent << "]" << std::endl;
}

std::string ArrayDeclarator::GetID() const 
{
    if (direct_declarator_) {
        if (Identifier* id = dynamic_cast<Identifier*>(direct_declarator_.get())) {
            return id->GetID();
        } else if (Declarator* decl = dynamic_cast<Declarator*>(direct_declarator_.get())) {
            return decl->GetID();
        }
    }
    return ""; 
}

std::vector<int> ArrayDeclarator::GetArrayIndexSpecifiers() const
{
    std::vector<int> dimensions;
    
    // Try to extract the dimension from this array declarator
    if (constant_expression_) {
        if (Integer* int_expr = dynamic_cast<Integer*>(constant_expression_.get())) {
            dimensions.push_back(int_expr->GetValue());
        }
    }
    
    // If this is a multi-dimensional array, recursively get dimensions from the direct_declarator
    if (direct_declarator_) {
        if (ArrayDeclarator* nested_array = dynamic_cast<ArrayDeclarator*>(direct_declarator_.get())) {
            std::vector<int> nested_dimensions = nested_array->GetArrayIndexSpecifiers();
            dimensions.insert(dimensions.end(), nested_dimensions.begin(), nested_dimensions.end());
        }
    }
    
    return dimensions;
}

} // namespace ast