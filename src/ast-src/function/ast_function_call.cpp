#include "ast/function/ast_function_call.hpp"
#include "ast/primary/ast_identifier.hpp"
#include "ast/ast_nodelist.hpp"

namespace ast {

FunctionCall::FunctionCall() 
    : function_(nullptr), arguments_(nullptr)
{
}

FunctionCall::FunctionCall(NodePtr function, NodePtr arguments)
    : function_(std::move(function)), arguments_(std::move(arguments))
{
}

void FunctionCall::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string function_name;
    if (Identifier* ident = dynamic_cast<Identifier*>(function_.get())) {
        function_name = ident->GetID();
    } else {
        throw std::runtime_error("Function call with non-identifier function expression not supported");
    }
    
    if (arguments_) {
        NodeList* arg_list = dynamic_cast<NodeList*>(arguments_.get());
        if (arg_list) {
            const auto& children = arg_list->GetChildren();
            
            // pass up to 8 arguments in registers a0-a7
            for (size_t i = 0; i < children.size() && i < 8; i++) {
                std::string arg_reg = "a" + std::to_string(i);
                children[i]->EmitRISCV(stream, arg_reg, context);
            }
        }
    }
    
    stream << "    call " << function_name << "\n";
    
    // return value is automatically in a0 for integer returns
    // if destination is not a0, copy it
    if (dst_reg != "a0") {
        stream << "    mv " << dst_reg << ", a0\n";
    }
}

void FunctionCall::Print(std::ostream& stream, indent_t indent) const 
{
    if (function_) {
        function_->Print(stream, indent);
    }
    
    stream << "(";
    
    if (arguments_) {
        arguments_->Print(stream, indent);
    }
    
    stream << ")";
}

} // namespace ast
