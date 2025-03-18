#include "ast/ast_context.hpp"
#include <stdexcept>

namespace ast {

Context::Context() 
    : scope_manager(this), 
      stack_manager(this), 
      label_manager(this), 
      register_manager(this) {
}

Context::~Context() {
}

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
            return 0;
        default:
            return 4;
    }
}

std::string Context::GetLoadInstruction(TypeSpecifier type) {
    switch (type) {
        case TypeSpecifier::INT:
        case TypeSpecifier::UNSIGNED_INT:
        case TypeSpecifier::LONG:
        case TypeSpecifier::UNSIGNED_LONG:
        case TypeSpecifier::SHORT:
        case TypeSpecifier::UNSIGNED_SHORT:
            return "lw";
        case TypeSpecifier::FLOAT:
            return "flw";
        case TypeSpecifier::DOUBLE:
        case TypeSpecifier::LONG_DOUBLE:
            return "fld";
        case TypeSpecifier::CHAR:
            return "lb";
        case TypeSpecifier::UNSIGNED_CHAR:
            return "lbu";
        default:
            return "lw";
    }
}

std::string Context::GetStoreInstruction(TypeSpecifier type) {
    switch (type) {
        case TypeSpecifier::INT:
        case TypeSpecifier::UNSIGNED_INT:
        case TypeSpecifier::LONG:
        case TypeSpecifier::UNSIGNED_LONG:
        case TypeSpecifier::SHORT:
        case TypeSpecifier::UNSIGNED_SHORT:
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
            return "sw";
    }
}

//=============================================================================
// ScopeManager Implementation
//=============================================================================

ScopeManager::~ScopeManager() {
}

void ScopeManager::EnterNewScope() {
    variable_scopes_.push_back(std::unordered_map<std::string, Variable_s>());
}

void ScopeManager::ExitScope(std::ostream& dst) {
    if (variable_scopes_.size() > 1) {
        variable_scopes_.pop_back();
    } else {
        throw std::runtime_error("Cannot exit global scope");
    }
}

void ScopeManager::AddVariable(const std::string& name, TypeSpecifier type, int stack_offset) {
    Variable_s var;
    var.type = type;
    var.stack_offset = stack_offset;
    
    variable_scopes_.back()[name] = var;
}

void ScopeManager::AddArray(const std::string& name, TypeSpecifier type, const std::vector<int>& dimensions, int stack_offset) {
    Variable_s var;
    var.type = type;
    var.is_array = true;
    var.array_dimensions = dimensions;
    var.stack_offset = stack_offset;
    
    variable_scopes_.back()[name] = var;
}

void ScopeManager::AddPointer(const std::string& name, TypeSpecifier type, int stack_offset) {
    Variable_s var;
    var.type = type;
    var.is_pointer = true;
    var.stack_offset = stack_offset;
    
    variable_scopes_.back()[name] = var;
}

void ScopeManager::AddFunction(const std::string& name, TypeSpecifier return_type, const std::vector<TypeSpecifier>& param_types) {
    Function_s func;
    func.return_type = return_type;
    func.param_types = param_types;
    
    function_table_[name] = func;
}

void ScopeManager::AddEnum(const std::string& enum_name) {
    enum_table_[enum_name] = std::map<std::string, int>();
}

void ScopeManager::AddEnumValue(const std::string& enum_name, const std::string& value_name, int value) {
    auto it = enum_table_.find(enum_name);
    if (it != enum_table_.end()) {
        it->second[value_name] = value;
    } else {
        throw std::runtime_error("Enum not found: " + enum_name);
    }
}

void ScopeManager::AddStruct(const std::string& name, const std::map<std::string, TypeSpecifier>& members, int size) {
}

Variable_s ScopeManager::GetVariable(const std::string& name) const {
    for (auto it = variable_scopes_.rbegin(); it != variable_scopes_.rend(); ++it) {
        auto var_it = it->find(name);
        if (var_it != it->end()) {
            return var_it->second;
        }
    }
    
    throw std::runtime_error("Variable not found: " + name);
}

Function_s ScopeManager::GetFunction(const std::string& name) const {
    auto it = function_table_.find(name);
    if (it != function_table_.end()) {
        return it->second;
    }
    
    throw std::runtime_error("Function not found: " + name);
}

int ScopeManager::GetEnumValue(const std::string& enum_name, const std::string& value_name) const {
    auto enum_it = enum_table_.find(enum_name);
    if (enum_it != enum_table_.end()) {
        auto value_it = enum_it->second.find(value_name);
        if (value_it != enum_it->second.end()) {
            return value_it->second;
        }
    }
    
    throw std::runtime_error("Enum value not found: " + enum_name + "::" + value_name);
}

bool ScopeManager::VariableExists(const std::string& name) const {
    for (auto it = variable_scopes_.rbegin(); it != variable_scopes_.rend(); ++it) {
        if (it->find(name) != it->end()) {
            return true;
        }
    }
    
    return false;
}

bool ScopeManager::FunctionExists(const std::string& name) const {
    return function_table_.find(name) != function_table_.end();
}

bool ScopeManager::StructExists(const std::string& name) const {
    return false;
}

//=============================================================================
// StackManager Implementation
//=============================================================================

StackManager::~StackManager() {
}

int StackManager::AllocateStackSpace(int bytes) {
    int aligned_size = (bytes + min_alignment_ - 1) & ~(min_alignment_ - 1);
    stack_offset_ -= aligned_size;
    return stack_offset_;
}

void StackManager::InitiateFrame(std::ostream& dst) {
    int ra_location = (default_stack_size_ - 4);
    int s0_location = ra_location - 4;

    dst << "    addi sp, sp, -" << default_stack_size_ << std::endl;
    dst << "    sw ra, " << ra_location << "(sp)" << std::endl;
    dst << "    sw s0, " << s0_location << "(sp)" << std::endl;
    dst << "    addi s0, sp, " << default_stack_size_ << std::endl;

    frame_pointer_offset_ = -min_alignment_;
}

void StackManager::TerminateFrame(std::ostream& dst) {
    int ra_location = (default_stack_size_ - 4);
    int s0_location = ra_location - 4;

    dst << "    lw ra, " << ra_location << "(sp)" << std::endl;
    dst << "    lw s0, " << s0_location << "(sp)" << std::endl;
    dst << "    addi sp, sp, " << default_stack_size_ << std::endl;
}

void StackManager::ResetFramePointer() {
    frame_pointer_offset_ = 0;
}

void StackManager::ResetStackPointer() {
    stack_offset_ = 0;
}

//=============================================================================
// LabelManager Implementation
//=============================================================================

LabelManager::~LabelManager() {
}

std::string LabelManager::CreateLabel(const std::string& prefix) {
    return "." + prefix + "_" + std::to_string(++label_counter_);
}

std::string LabelManager::GetCurrentLoopStart() const {
    if (!loop_start_labels_.empty()) {
        return loop_start_labels_.back();
    }
    throw std::runtime_error("No active loop");
}

std::string LabelManager::GetCurrentLoopEnd() const {
    if (!loop_end_labels_.empty()) {
        return loop_end_labels_.back();
    }
    throw std::runtime_error("No active loop");
}

std::string LabelManager::GetCurrentLoopUpdate() const {
    if (!loop_update_labels_.empty()) {
        return loop_update_labels_.back();
    }
    throw std::runtime_error("No active loop");
}

void LabelManager::PushLoopStart(const std::string& label) {
    loop_start_labels_.push_back(label);
}

void LabelManager::PushLoopEnd(const std::string& label) {
    loop_end_labels_.push_back(label);
}

void LabelManager::PushLoopUpdate(const std::string& label) {
    loop_update_labels_.push_back(label);
}

void LabelManager::PopLoopStart() {
    if (!loop_start_labels_.empty()) {
        loop_start_labels_.pop_back();
    } else {
        throw std::runtime_error("No loop labels to pop");
    }
}

void LabelManager::PopLoopEnd() {
    if (!loop_end_labels_.empty()) {
        loop_end_labels_.pop_back();
    } else {
        throw std::runtime_error("No loop labels to pop");
    }
}

void LabelManager::PopLoopUpdate() {
    if (!loop_update_labels_.empty()) {
        loop_update_labels_.pop_back();
    } else {
        throw std::runtime_error("No loop labels to pop");
    }
}

std::string LabelManager::AddStringLiteral(const std::string& value) {
    std::string label = CreateLabel("str");
    string_literals_.push_back(std::make_pair(label, value));
    return label;
}

void LabelManager::EmitDataSection(std::ostream& dst) const {
    if (string_literals_.empty()) {
        return;
    }
    
    dst << "\n.rodata\n";
    
    for (const auto& str : string_literals_) {
        dst << str.first << ":\n";
        dst << "    .string \"" << str.second << "\"\n";
    }
}

//=============================================================================
// RegisterManager Implementation
//=============================================================================

RegisterManager::~RegisterManager() {
}

std::string RegisterManager::AllocateRegister(bool is_float) {
    if (is_float) {
        for (int i = 0; i < 32; i++) {
            if (regs_float_[i] == 0) {
                regs_float_[i] = 1;
                return "f" + std::to_string(i);
            }
        }
    } else {
        for (int i = 5; i < 32; i++) {
            if (regs_[i] == 0) {
                regs_[i] = 1;
                return "x" + std::to_string(i);
            }
        }
    }
    
    throw std::runtime_error("No available registers");
}

std::string RegisterManager::AllocateReturnRegister(bool is_float) {
    if (is_float) {
        return "fa0";
    } else {
        return "a0";
    }
}

std::string RegisterManager::AllocateArgumentRegister(int arg_num, bool is_float) {
    if (arg_num < 0 || arg_num > 7) {
        throw std::runtime_error("Invalid argument number: " + std::to_string(arg_num));
    }
    
    if (is_float) {
        return "fa" + std::to_string(arg_num);
    } else {
        return "a" + std::to_string(arg_num);
    }
}

void RegisterManager::DeallocateRegister(const std::string& reg) {
    if (reg.empty()) return;
    
    if (reg[0] == 'f') {
        int reg_num = std::stoi(reg.substr(1));
        if (reg_num >= 0 && reg_num < 32) {
            regs_float_[reg_num] = 0;
        }
    } else if (reg[0] == 'x') {
        int reg_num = std::stoi(reg.substr(1));
        if (reg_num >= 5 && reg_num < 32) {
            regs_[reg_num] = 0;
        }
    }
}

void RegisterManager::SpillRegister(const std::string& reg, std::ostream& dst) {
    if (reg.empty()) return;
    
    bool is_float = (reg[0] == 'f');
    
    int stack_offset = context_->stack_manager.AllocateStackSpace(is_float ? 8 : 4);
    
    SpilledRegister spilled;
    spilled.reg_name = reg;
    spilled.stack_offset = stack_offset;
    spilled.is_float = is_float;
    
    spilled_registers_.push_back(spilled);
    
    if (is_float) {
        dst << "    fsw " << reg << ", " << stack_offset << "(s0)" << std::endl;
    } else {
        dst << "    sw " << reg << ", " << stack_offset << "(s0)" << std::endl;
    }
    
    DeallocateRegister(reg);
}

void RegisterManager::UnspillRegister(const std::string& reg, std::ostream& dst) {
    for (auto it = spilled_registers_.begin(); it != spilled_registers_.end(); ++it) {
        if (it->reg_name == reg) {
            if (it->is_float) {
                dst << "    flw " << reg << ", " << it->stack_offset << "(s0)" << std::endl;
            } else {
                dst << "    lw " << reg << ", " << it->stack_offset << "(s0)" << std::endl;
            }
            
            spilled_registers_.erase(it);
            return;
        }
    }
    
    throw std::runtime_error("Register not spilled: " + reg);
}

void RegisterManager::PushRegisters(std::ostream& dst) {
    saved_registers_.clear();
    
    for (int i = 0; i < 32; i++) {
        if (regs_[i] == 1 && i >= 5) {
            SavedRegister saved;
            saved.reg_name = "x" + std::to_string(i);
            saved.stack_offset = context_->stack_manager.AllocateStackSpace(4);
            saved.is_float = false;
            
            saved_registers_.push_back(saved);
            
            dst << "    sw " << saved.reg_name << ", " << saved.stack_offset << "(s0)" << std::endl;
        }
    }
    
    for (int i = 0; i < 32; i++) {
        if (regs_float_[i] == 1) {
            SavedRegister saved;
            saved.reg_name = "f" + std::to_string(i);
            saved.stack_offset = context_->stack_manager.AllocateStackSpace(8);
            saved.is_float = true;
            
            saved_registers_.push_back(saved);
            
            dst << "    fsw " << saved.reg_name << ", " << saved.stack_offset << "(s0)" << std::endl;
        }
    }
}

void RegisterManager::RestoreRegisters(std::ostream& dst) {
    for (auto it = saved_registers_.rbegin(); it != saved_registers_.rend(); ++it) {
        if (it->is_float) {
            dst << "    flw " << it->reg_name << ", " << it->stack_offset << "(s0)" << std::endl;
        } else {
            dst << "    lw " << it->reg_name << ", " << it->stack_offset << "(s0)" << std::endl;
        }
    }
    
    saved_registers_.clear();
}

void RegisterManager::ResetRegisters() {
    for (int i = 0; i < 32; i++) {
        regs_[i] = 0;
    }
    
    for (int i = 0; i < 32; i++) {
        regs_float_[i] = 0;
    }
    
    regs_[0] = 1;
    regs_[1] = 1;
    regs_[2] = 1;
    regs_[3] = 1;
    regs_[4] = 1;
    
    regs_float_[0] = 1;
    regs_float_[1] = 1;
    
    spilled_registers_.clear();
    saved_registers_.clear();
}

} // namespace ast