#include "ast/ast_context.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

namespace ast {

Context::Context() {
    // Initialize the first (global) scope
    variable_scopes_.push_back(std::unordered_map<std::string, Variable_s>());
}

Context::~Context() {
}

// Register allocation
std::string Context::AllocateRegister(bool is_float) {
    if (is_float) {
        // Allocate a floating-point register
        for (int i = 0; i < 32; i++) {
            if (regs_float_[i] == 0) {
                regs_float_[i] = 1;
                return "f" + std::to_string(i);
            }
        }
    } else {
        // Allocate an integer register
        for (int i = 5; i < 32; i++) {
            if (regs_[i] == 0) {
                regs_[i] = 1;
                return "x" + std::to_string(i);
            }
        }
    }
    
    // No registers available
    throw std::runtime_error("No available registers");
}

void Context::FreeRegister(const std::string& reg) {
    if (reg.empty()) return;
    
    if (reg[0] == 'f') {
        // Free floating-point register
        int reg_num = std::stoi(reg.substr(1));
        if (reg_num >= 0 && reg_num < 32) {
            regs_float_[reg_num] = 0;
        }
    } else if (reg[0] == 'x') {
        // Free integer register
        int reg_num = std::stoi(reg.substr(1));
        if (reg_num >= 5 && reg_num < 32) {
            regs_[reg_num] = 0;
        }
    }
}

// Memory management
void Context::EnterScope() {
    // Push a new scope onto the stack
    variable_scopes_.push_back(std::unordered_map<std::string, Variable_s>());
    
}

void Context::ExitScope(std::ostream& dst) {
    // Pop the current scope
    if (variable_scopes_.size() > 1) {
        variable_scopes_.pop_back();
    } else {
        throw std::runtime_error("Cannot exit global scope");
    }
    
}

int Context::AllocateStackSpace(int size) {
    // Align the size to maintain stack alignment
    int aligned_size = (size + min_alignment_ - 1) & ~(min_alignment_ - 1);
    stack_offset_ -= aligned_size;
    return stack_offset_;
}

// Symbol table operations
void Context::AddVariable(const std::string& name, TypeSpecifier type) {
    Variable_s var;
    var.type = type;
    var.stack_offset = AllocateStackSpace(GetSizeOfType(type));
    
    // Add to current scope
    variable_scopes_.back()[name] = var;
}

void Context::AddArray(const std::string& name, TypeSpecifier type, const std::vector<int>& dimensions) {
    Variable_s var;
    var.type = type;
    var.is_array = true;
    var.array_dimensions = dimensions;
    
    // Calculate total size
    int total_size = GetSizeOfType(type);
    for (int dim : dimensions) {
        total_size *= dim;
    }
    
    var.stack_offset = AllocateStackSpace(total_size);
    
    // Add to current scope
    variable_scopes_.back()[name] = var;
}

void Context::AddPointer(const std::string& name, TypeSpecifier type) {
    Variable_s var;
    var.type = type;
    var.is_pointer = true;
    var.stack_offset = AllocateStackSpace(4); // Pointers are 4 bytes on 32-bit systems
    
    // Add to current scope
    variable_scopes_.back()[name] = var;
}

void Context::AddFunction(const std::string& name, TypeSpecifier return_type, const std::vector<TypeSpecifier>& param_types) {
    Function_s func;
    func.return_type = return_type;
    func.param_types = param_types;
    
    function_table_[name] = func;
}

void Context::AddEnumValue(const std::string& name, int value) {
    // For unscoped enums, we simply map the name directly to its integer value
    enum_values_[name] = value;
}

// Variable and function lookup
Variable_s Context::GetVariable(const std::string& name) const {
    // Search scopes from innermost to outermost
    for (auto it = variable_scopes_.rbegin(); it != variable_scopes_.rend(); ++it) {
        auto var_it = it->find(name);
        if (var_it != it->end()) {
            return var_it->second;
        }
    }
    
    throw std::runtime_error("Variable not found: " + name);
}

Function_s Context::GetFunction(const std::string& name) const {
    auto it = function_table_.find(name);
    if (it != function_table_.end()) {
        return it->second;
    }
    
    throw std::runtime_error("Function not found: " + name);
}

int Context::GetEnumValue(const std::string& name) const {
    auto it = enum_values_.find(name);
    if (it != enum_values_.end()) {
        return it->second;
    }
    
    throw std::runtime_error("Enum value not found: " + name);
}

bool Context::VariableExists(const std::string& name) const {
    // Search scopes from innermost to outermost
    for (auto it = variable_scopes_.rbegin(); it != variable_scopes_.rend(); ++it) {
        if (it->find(name) != it->end()) {
            return true;
        }
    }
    
    return false;
}

bool Context::FunctionExists(const std::string& name) const {
    return function_table_.find(name) != function_table_.end();
}

// Control flow management
void Context::PushLoopLabels(const std::string& start, const std::string& end, const std::string& update) {
    loop_start_labels_.push_back(start);
    loop_end_labels_.push_back(end);
    loop_update_labels_.push_back(update);
}

void Context::PopLoopLabels() {
    if (!loop_start_labels_.empty()) {
        loop_start_labels_.pop_back();
        loop_end_labels_.pop_back();
        loop_update_labels_.pop_back();
    } else {
        throw std::runtime_error("No loop labels to pop");
    }
}

std::string Context::GetCurrentLoopStart() const {
    if (!loop_start_labels_.empty()) {
        return loop_start_labels_.back();
    }
    throw std::runtime_error("No active loop");
}

std::string Context::GetCurrentLoopEnd() const {
    if (!loop_end_labels_.empty()) {
        return loop_end_labels_.back();
    }
    throw std::runtime_error("No active loop");
}

std::string Context::GetCurrentLoopUpdate() const {
    if (!loop_update_labels_.empty()) {
        return loop_update_labels_.back();
    }
    return ""; // Update label may be empty for while loops
}

// Label generation
std::string Context::CreateLabel(const std::string& prefix) {
    return "_" + prefix + "_" + std::to_string(++label_counter_);
}

// String literal management
std::string Context::AddStringLiteral(const std::string& value) {
    std::string label = CreateLabel("str");
    string_literals_.push_back(std::make_pair(label, value));
    return label;
}

void Context::EmitDataSection(std::ostream& dst) const {
    if (string_literals_.empty()) {
        return;
    }
    
    dst << "\n.data\n";
    
    for (const auto& str : string_literals_) {
        dst << str.first << ":\n";
        dst << "    .string \"" << str.second << "\"\n";
    }
}

// Type utility functions
int Context::GetSizeOfType(TypeSpecifier type) {
    switch (type) {
        case TypeSpecifier::INT:
        case TypeSpecifier::UNSIGNED_INT:
        case TypeSpecifier::LONG:
        case TypeSpecifier::UNSIGNED_LONG:
        case TypeSpecifier::FLOAT:
            return 4;
        case TypeSpecifier::DOUBLE:
        case TypeSpecifier::LONG_DOUBLE:
            return 8;
        case TypeSpecifier::CHAR:
        case TypeSpecifier::UNSIGNED_CHAR:
            return 1;
        case TypeSpecifier::SHORT:
        case TypeSpecifier::UNSIGNED_SHORT:
            return 2;
        case TypeSpecifier::VOID:
            return 0;
        case TypeSpecifier::STRUCT:
            return 0; // Struct size depends on its members, this will be handled elsewhere
        default:
            return 4; // Default to int size
    }
}

std::string Context::GetLoadInstruction(TypeSpecifier type) {
    switch (type) {
        case TypeSpecifier::INT:
        case TypeSpecifier::UNSIGNED_INT:
        case TypeSpecifier::LONG:
        case TypeSpecifier::UNSIGNED_LONG:
        case TypeSpecifier::SHORT:
        case TypeSpecifier::UNSIGNED_SHORT: // Promote to word
            return "lw";
        case TypeSpecifier::FLOAT:
            return "flw";
        case TypeSpecifier::DOUBLE:
        case TypeSpecifier::LONG_DOUBLE:
            return "fld";
        case TypeSpecifier::CHAR:
            return "lb";
        case TypeSpecifier::UNSIGNED_CHAR:
            return "lbu"; // Load unsigned byte
        default:
            return "lw"; // Default to word load
    }
}

std::string Context::GetStoreInstruction(TypeSpecifier type) {
    switch (type) {
        case TypeSpecifier::INT:
        case TypeSpecifier::UNSIGNED_INT:
        case TypeSpecifier::LONG:
        case TypeSpecifier::UNSIGNED_LONG:
        case TypeSpecifier::SHORT:
        case TypeSpecifier::UNSIGNED_SHORT: // Promote to word
            return "sw";
        case TypeSpecifier::FLOAT:
            return "fsw";
        case TypeSpecifier::DOUBLE:
        case TypeSpecifier::LONG_DOUBLE:
            return "fsd";
        case TypeSpecifier::CHAR:
        case TypeSpecifier::UNSIGNED_CHAR:
            return "sb";
        default:
            return "sw"; // Default to word store
    }
}

} // namespace ast