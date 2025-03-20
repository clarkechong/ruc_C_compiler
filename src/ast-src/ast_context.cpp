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

ScopeManager::ScopeManager(Context* context) : context_(context) {
    variable_scopes_.push_back(std::unordered_map<std::string, Variable_s>());
    struct_scopes_.push_back(std::unordered_map<std::string, std::map<std::string, Variable_s>>());
}

ScopeManager::~ScopeManager() {
}

void ScopeManager::EnterNewScope() {
    variable_scopes_.push_back(std::unordered_map<std::string, Variable_s>());
    struct_scopes_.push_back(std::unordered_map<std::string, std::map<std::string, Variable_s>>());
}

void ScopeManager::ExitScope() {
    if (variable_scopes_.size() > 1) {
        variable_scopes_.pop_back();
        struct_scopes_.pop_back();
    } else {
        throw std::runtime_error("Cannot exit global scope");
    }
}

bool ScopeManager::InGlobalScope() const {
    return variable_scopes_.size() == 1;
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

void ScopeManager::AddStruct(const std::string& name) {
    // Add an empty struct to the current scope
    struct_scopes_.back()[name] = std::map<std::string, Variable_s>();
}

void ScopeManager::AddStructMember(const std::string& struct_name, const std::string& member_name, 
                                  TypeSpecifier type, int offset, bool is_pointer, bool is_array, 
                                  const std::vector<int>& array_dimensions) {
    // Find the struct in the current scope
    auto it = struct_scopes_.back().find(struct_name);
    if (it != struct_scopes_.back().end()) {
        // Create the member variable
        Variable_s member;
        member.type = type;
        member.stack_offset = offset;
        member.is_pointer = is_pointer;
        member.is_array = is_array;
        member.array_dimensions = array_dimensions;
        
        // Add it to the struct's member map
        it->second[member_name] = member;
    } else {
        // Look for the struct in parent scopes
        for (auto scope_it = struct_scopes_.rbegin() + 1; scope_it != struct_scopes_.rend(); ++scope_it) {
            auto struct_it = scope_it->find(struct_name);
            if (struct_it != scope_it->end()) {
                // Create the member variable
                Variable_s member;
                member.type = type;
                member.stack_offset = offset;
                member.is_pointer = is_pointer;
                member.is_array = is_array;
                member.array_dimensions = array_dimensions;
                
                // Add it to the struct's member map
                struct_it->second[member_name] = member;
                return;
            }
        }
        
        throw std::runtime_error("Struct not found: " + struct_name);
    }
}

Variable_s ScopeManager::GetStructMember(const std::string& struct_name, const std::string& member_name) const {
    // Search for the struct in all scopes, starting from the innermost
    for (auto scope_it = struct_scopes_.rbegin(); scope_it != struct_scopes_.rend(); ++scope_it) {
        auto struct_it = scope_it->find(struct_name);
        if (struct_it != scope_it->end()) {
            // Found the struct, now look for the member
            auto member_it = struct_it->second.find(member_name);
            if (member_it != struct_it->second.end()) {
                return member_it->second;
            }
        }
    }
    
    throw std::runtime_error("Struct member not found: " + struct_name + "." + member_name);
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
    // Search for the struct in all scopes, starting from the innermost
    for (auto it = struct_scopes_.rbegin(); it != struct_scopes_.rend(); ++it) {
        if (it->find(name) != it->end()) {
            return true;
        }
    }
    return false;
}

//=============================================================================
// StackManager Implementation
//=============================================================================

StackManager::StackManager(Context* context) : context_(context) {
}

StackManager::~StackManager() {
}

// RETURN THE NEW STACK POINTER OFFSET WHILST UR AT IT MATE
int StackManager::DecrementFrameOffset(int bytes) {
    int aligned_size = (bytes + min_alignment_ - 1) & ~(min_alignment_ - 1);
    frame_pointer_offset_ -= aligned_size;
    return frame_pointer_offset_;
}

// for variables only. not enums or structs
int StackManager::AllocateStackAndLink(TypeSpecifier type, const std::string& id, bool is_ptr, bool is_array, const std::vector<int>& array_dimensions) {
    int bytes = 0;
    
    if (is_array) {
        int multiplier = 1;
        for (int dim : array_dimensions) {
            multiplier *= dim;
        }
        bytes = Context::GetSizeOfType(type) * multiplier;
        int frame_offset = DecrementFrameOffset(bytes);
        context_->scope_manager.AddArray(id, type, array_dimensions, frame_offset);
        return frame_offset;
    } 
    else if (is_ptr) {
        bytes = 4;
        int frame_offset = DecrementFrameOffset(bytes);
        context_->scope_manager.AddPointer(id, type, frame_offset);
        return frame_offset;
    } 
    else {
        bytes = Context::GetSizeOfType(type);
        int frame_offset = DecrementFrameOffset(bytes);
        context_->scope_manager.AddVariable(id, type, frame_offset);
        return frame_offset;
    }
}

void StackManager::StoreRegisterToVariable(std::ostream& dst, const std::string& reg, const std::string& id, bool is_ptr, bool is_array, const std::vector<int>& array_indices) {
    try {
        Variable_s var = context_->scope_manager.GetVariable(id);
        int offset = var.stack_offset;
        
        // Handle array access with indices
        if (is_array && !array_indices.empty()) {
            if (!var.is_array) {
                dst << "    # Error: Variable is not an array but array access attempted: " << id << std::endl;
                return;
            }
            
            // Calculate the byte offset based on indices
            int element_size = Context::GetSizeOfType(var.type);
            
            // Debug information
            dst << "    # STORE TO ARRAY: " << id << "[" << array_indices[0] << "] = " << reg << std::endl;
            dst << "    # ELEMENT TYPE SIZE: " << element_size << " bytes" << std::endl;
            
            if (array_indices.size() == 1) {
                int byte_offset = -array_indices[0] * element_size;
                dst << "    # Calculating array element offset: index=" << array_indices[0] 
                    << " * size=" << element_size << " = " << byte_offset << std::endl;
                    
                // Create the address calculation: base + index*element_size
                std::string store_instruction = Context::GetStoreInstruction(var.type);
                dst << "    # Array base offset: " << offset << std::endl;
                dst << "    # Final offset: " << (offset + byte_offset) << std::endl;
                dst << "    " << store_instruction << " " << reg << ", " << (offset + byte_offset) << "(s0)" << std::endl;
                return;
            }
            // TODO: Handle multi-dimensional arrays
        }
        else if (is_ptr) {
            // Pointer handling goes here
            if (!var.is_pointer) {
                dst << "    # Error: Variable is not a pointer but pointer access attempted: " << id << std::endl;
                return;
            }
            
            // TODO: Implement pointer store
            dst << "    # Pointer store not yet implemented for: " << id << std::endl;
            return;
        }
        
        // Default case - regular variable or pointer variable
        if (context_->scope_manager.InGlobalScope()) {
            dst << "    # Global variable store - needs implementation with %hi and %lo" << std::endl;
        } else {
            std::string store_instruction = Context::GetStoreInstruction(var.type);
            dst << "    " << store_instruction << " " << reg << ", " << offset << "(s0)" << std::endl;
        }
    } catch (const std::runtime_error& e) {
        dst << "    # Error: Variable not found: " << id << std::endl;
    }
}

void StackManager::LoadVariableToRegister(std::ostream& dst, const std::string& reg, const std::string& id, bool is_ptr, bool is_array, const std::vector<int>& array_indices) {
    try {
        Variable_s var = context_->scope_manager.GetVariable(id);
        int offset = var.stack_offset;
        
        // Handle array access with indices
        if (is_array && !array_indices.empty()) {
            if (!var.is_array) {
                dst << "    # Error: Variable is not an array but array access attempted: " << id << std::endl;
                return;
            }
            
            // Calculate the byte offset based on indices
            int element_size = Context::GetSizeOfType(var.type);
            
            // Debug information
            dst << "    # Array load: " << reg << " = " << id << "[" << array_indices[0] << "]" << std::endl;
            dst << "    # Element size: " << element_size << " bytes" << std::endl;
            
            // For single-dimensional array access (handle multi-dimensional later)
            if (array_indices.size() == 1) {
                int byte_offset = array_indices[0] * element_size;
                dst << "    # Calculating array element offset: index=" << array_indices[0] 
                    << " * size=" << element_size << " = " << byte_offset << std::endl;
                    
                // Create the address calculation: base + index*element_size
                std::string load_instruction = Context::GetLoadInstruction(var.type);
                dst << "    # Array base offset: " << offset << std::endl;
                dst << "    # Final offset: " << (offset + byte_offset) << std::endl;
                dst << "    " << load_instruction << " " << reg << ", " << (offset + byte_offset) << "(s0)" << std::endl;
                return;
            }
            // TODO: Handle multi-dimensional arrays
        }
        else if (is_ptr) {
            // Pointer handling goes here
            if (!var.is_pointer) {
                dst << "    # Error: Variable is not a pointer but pointer access attempted: " << id << std::endl;
                return;
            }
            
            // TODO: Implement pointer load
            dst << "    # Pointer load not yet implemented for: " << id << std::endl;
            return;
        }
        
        // Default case - regular variable or pointer variable
        if (context_->scope_manager.InGlobalScope()) {
            dst << "    # Global variable load - needs implementation with %hi and %lo" << std::endl;
        } else {
            std::string load_instruction = Context::GetLoadInstruction(var.type);
            dst << "    " << load_instruction << " " << reg << ", " << offset << "(s0)" << std::endl;
        }
    } catch (const std::runtime_error& e) {
        dst << "    # Error: Variable not found: " << id << std::endl;
    }
}

// ONLY INITIATE FRAME WHEN A FUNCTION CALL OCCURS. UNNECESSARY TO INITIATE FRAME FOR EVERY SCOPE
void StackManager::InitiateFrame(std::ostream& dst) {
    int save_ra_location = default_stack_size_ - 4;
    int save_s0_location = save_ra_location - 4;

    dst << "    addi sp, sp, -" << default_stack_size_ << std::endl;
    dst << "    sw ra, " << save_ra_location << "(sp)" << std::endl;
    dst << "    sw s0, " << save_s0_location << "(sp)" << std::endl;
    dst << "    addi s0, sp, " << default_stack_size_ << std::endl;

    frame_pointer_offset_ -= 16;
}

void StackManager::TerminateFrame(std::ostream& dst) {
    int save_ra_location = (default_stack_size_ - 4);
    int save_s0_location = save_ra_location - 4;

    dst << "    lw ra, " << save_ra_location << "(sp)" << std::endl;
    dst << "    lw s0, " << save_s0_location << "(sp)" << std::endl;
    dst << "    addi sp, sp, " << default_stack_size_ << std::endl;
}

void StackManager::ResetFrameOffset() {
    frame_pointer_offset_ = 0;
}

int StackManager::GetFrameOffset() const { 
    return frame_pointer_offset_; 
}


//=============================================================================
// LabelManager Implementation
//=============================================================================

LabelManager::LabelManager(Context* context) : context_(context) {
}

LabelManager::~LabelManager() {
}

std::string LabelManager::CreateLabel(const std::string& prefix) {
    return "." + prefix + "_" + std::to_string(++label_counter_);
}

void LabelManager::PushFunctionContext(const std::string& func_name) {
    function_stack_.push(func_name);
    function_end_labels_.push(func_name + "_end");
}

void LabelManager::PopFunctionContext() {
    if (!function_stack_.empty()) {
        function_stack_.pop();
        function_end_labels_.pop();
    } else {
        throw std::runtime_error("No function context to pop");
    }
}

std::string LabelManager::GetCurrentFunction() const {
    if (function_stack_.empty()) {
        throw std::runtime_error("Not in a function context");
    }
    return function_stack_.top();
}

std::string LabelManager::GetCurrentFunctionEndLabel() const {
    if (function_end_labels_.empty()) {
        throw std::runtime_error("Not in a function context");
    }
    return function_end_labels_.top();
}

// Loop label management
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

// Switch label management
void LabelManager::PushSwitchContext(const std::string& switch_reg) {
    switch_reg_stack_.push(switch_reg);
}

void LabelManager::PopSwitchContext() {
    if (!switch_reg_stack_.empty()) {
        switch_reg_stack_.pop();
    } else {
        throw std::runtime_error("No switch context to pop");
    }
}

std::string LabelManager::GetCurrentSwitchReg() const {
    if (switch_reg_stack_.empty()) {
        throw std::runtime_error("Not in a switch context");
    }
    return switch_reg_stack_.top();
}

//=============================================================================
// RegisterManager Implementation
//=============================================================================

RegisterManager::RegisterManager(Context* context) : context_(context) {
    // Reserve registers that shouldn't be allocated
    regs_[0] = 1; // x0 is hardwired to zero
    regs_[1] = 1; // x1 (ra) is return address
    regs_[2] = 1; // x2 (sp) is stack pointer
    regs_[3] = 1; // x3 (gp) is global pointer
    regs_[4] = 1; // x4 (tp) is thread pointer
    
    // f0-f1 are reserved for return values
    regs_float_[0] = 1;
    regs_float_[1] = 1;
}

RegisterManager::~RegisterManager() {
}

// EXCLUDE REGISTER FUNCTIONALITY? SUCH THAT IF REGISTER NEEDS TO SPILL, IT DOESNT SPILL ONE THAT IS SPECIFIED TO BE IN USE
// OR JUST MAKE IT SO THAT IT SPILLS LEAST RECENTLY USED. THAT SHOULD BE SUFFICIENT FOR ANY TESTS
// E.G. EVERY TIME REGS_[I] IS SET, PUSH BACK TO A FIFO BUFFER
// IF NEED TO SPILL, POP ELEMENT [0]
std::string RegisterManager::AllocateRegister(bool is_float) {
    if (is_float) {
        for (int i = 0; i <= 7; i++) { // ft0-ft7
            if (regs_float_[i] == 0) {
                regs_float_[i] = 1;
                return "ft" + std::to_string(i);
            }
        }
        
        for (int i = 8; i <= 9; i++) { // fs0-fs1
            if (regs_float_[i] == 0) {
                regs_float_[i] = 1;
                return "fs" + std::to_string(i - 8);
            }
        }
        
        for (int i = 18; i <= 27; i++) { // fs2-fs11
            if (regs_float_[i] == 0) {
                regs_float_[i] = 1;
                return "fs" + std::to_string(i - 16);
            }
        }
        
        for (int i = 28; i <= 31; i++) { // ft8-ft11
            if (regs_float_[i] == 0) {
                regs_float_[i] = 1;
                return "ft" + std::to_string(i - 20); // ft8 = 28-20, ft9 = 29-20, etc.
            }
        }
    } else {
        for (int i = 5; i <= 7; i++) { // t0-t2
            if (regs_[i] == 0) {
                regs_[i] = 1;
                return "t" + std::to_string(i - 5);
            }
        }
        
        for (int i = 9; i <= 9; i++) { // s1
            if (regs_[i] == 0) {
                regs_[i] = 1;
                return "s1";
            }
        }
        
        for (int i = 18; i <= 27; i++) { // s2-s11
            if (regs_[i] == 0) {
                regs_[i] = 1;
                return "s" + std::to_string(i - 16);
            }
        }
        
        for (int i = 28; i <= 31; i++) { // t3-t6
            if (regs_[i] == 0) {
                regs_[i] = 1;
                return "t" + std::to_string(i - 25); // t3 = 28-25, t4 = 29-25, etc.
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

std::string RegisterManager::AllocateArgumentRegister(bool is_float) {
    if (is_float) {
        for (int i = 0; i <= 7; ++i) {
            std::string register_name = "fa" + std::to_string(i);
            int reg_index = 10 + i; // fa0-fa7 are mapped to regs 10-17
            
            if (regs_float_[reg_index] == 0) {
                regs_float_[reg_index] = 1;
                return register_name;
            }
        }
    } else {
        for (int i = 0; i <= 7; ++i) {
            std::string register_name = "a" + std::to_string(i);
            int reg_index = 10 + i; // a0-a7 are mapped to regs 10-17
            
            if (regs_[reg_index] == 0) {
                regs_[reg_index] = 1;
                return register_name;
            }
        }
    }
    
    throw std::runtime_error("No available argument registers. all been taken or some shit. who knows.");
}

void RegisterManager::DeallocateRegister(const std::string& reg) {
    if (reg.empty()) return;
    
    if (reg[0] == 'f') {
        auto it = register_map_f.find(reg);
        if (it != register_map_f.end()) {
            int reg_num = it->second;
            regs_float_[reg_num] = 0;
            return;
        }
    } else {
        auto it = register_map.find(reg);
        if (it != register_map.end()) {
            int reg_num = it->second;
            regs_[reg_num] = 0;
            return;
        }
    }
}

void RegisterManager::SpillRegister(const std::string& reg, std::ostream& dst) {
    if (reg.empty()) {
        throw std::runtime_error("SpillRegister but reg argument empty???");
        return;
    }
    
    bool is_float = (reg[0] == 'f');
    
    int frame_offset = context_->stack_manager.DecrementFrameOffset((is_float ? 8 : 4));
    
    SpilledRegister spilled;
    spilled.reg_name = reg;
    spilled.stack_offset = frame_offset;
    spilled.is_float = is_float;
    
    spilled_registers_.push_back(spilled);
    
    if (is_float) {
        dst << "    fsw " << reg << ", " << frame_offset << "(s0)" << std::endl;
    } else {
        dst << "    sw " << reg << ", " << frame_offset << "(s0)" << std::endl;
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
    
    throw std::runtime_error("TRYING TO UNSPILL REGISTER THAT IS NOT SPILLED???: " + reg);
}

void RegisterManager::PushRegisters(std::ostream& dst) {
    dst << "    # Pushing registers to stack" << std::endl;
    saved_registers_.clear();
    
    // Save floating point temporary registers (ft0-ft7, ft8-ft11)
    for (int i = 0; i <= 7; ++i) {
        std::string reg_name = "ft" + std::to_string(i);
        auto it = register_map_f.find(reg_name);
        if (it != register_map_f.end() && regs_float_[it->second] == 1) {
            SavedRegister saved;
            saved.reg_name = reg_name;
            saved.stack_offset = context_->stack_manager.DecrementFrameOffset(4);
            saved.is_float = true;
            
            saved_registers_.push_back(saved);
            regs_float_[it->second] = 0;  // Mark as available during the function call
            
            dst << "    fsw " << reg_name << ", " << saved.stack_offset << "(s0)" << std::endl;
        }
    }
    
    for (int i = 8; i <= 11; ++i) {
        std::string reg_name = "ft" + std::to_string(i);
        auto it = register_map_f.find(reg_name);
        if (it != register_map_f.end() && regs_float_[it->second] == 1) {
            SavedRegister saved;
            saved.reg_name = reg_name;
            saved.stack_offset = context_->stack_manager.DecrementFrameOffset(4);
            saved.is_float = true;
            
            saved_registers_.push_back(saved);
            regs_float_[it->second] = 0;  // Mark as available during the function call
            
            dst << "    fsw " << reg_name << ", " << saved.stack_offset << "(s0)" << std::endl;
        }
    }
    
    // Save integer temporary registers (t0-t2, t3-t6)
    for (int i = 0; i <= 2; ++i) {
        std::string reg_name = "t" + std::to_string(i);
        auto it = register_map.find(reg_name);
        if (it != register_map.end() && regs_[it->second] == 1) {
            SavedRegister saved;
            saved.reg_name = reg_name;
            saved.stack_offset = context_->stack_manager.DecrementFrameOffset(4);
            saved.is_float = false;
            
            saved_registers_.push_back(saved);
            regs_[it->second] = 0;  // Mark as available during the function call
            
            dst << "    sw " << reg_name << ", " << saved.stack_offset << "(s0)" << std::endl;
        }
    }
    
    for (int i = 3; i <= 6; ++i) {
        std::string reg_name = "t" + std::to_string(i);
        auto it = register_map.find(reg_name);
        if (it != register_map.end() && regs_[it->second] == 1) {
            SavedRegister saved;
            saved.reg_name = reg_name;
            saved.stack_offset = context_->stack_manager.DecrementFrameOffset(4);
            saved.is_float = false;
            
            saved_registers_.push_back(saved);
            regs_[it->second] = 0;  // Mark as available during the function call
            
            dst << "    sw " << reg_name << ", " << saved.stack_offset << "(s0)" << std::endl;
        }
    }
    
    // Save argument registers (a0-a7)
    for (int i = 0; i <= 7; ++i) {
        std::string reg_name = "a" + std::to_string(i);
        auto it = register_map.find(reg_name);
        if (it != register_map.end() && regs_[it->second] == 1) {
            SavedRegister saved;
            saved.reg_name = reg_name;
            saved.stack_offset = context_->stack_manager.DecrementFrameOffset(4);
            saved.is_float = false;
            
            saved_registers_.push_back(saved);
            regs_[it->second] = 0;  // Mark as available during the function call
            
            dst << "    sw " << reg_name << ", " << saved.stack_offset << "(s0)" << std::endl;
        }
    }
}

void RegisterManager::RestoreRegisters(std::ostream& dst) {
    dst << "    # Restoring registers from stack" << std::endl;
    
    // Restore in reverse order (LIFO)
    for (auto it = saved_registers_.rbegin(); it != saved_registers_.rend(); ++it) {
        if (it->is_float) {
            // Handle floating-point registers
            dst << "    flw " << it->reg_name << ", " << it->stack_offset << "(s0)" << std::endl;
            
            // Mark the register as in use again
            auto map_it = register_map_f.find(it->reg_name);
            if (map_it != register_map_f.end()) {
                regs_float_[map_it->second] = 1;
            }
        } else {
            // Handle integer registers
            dst << "    lw " << it->reg_name << ", " << it->stack_offset << "(s0)" << std::endl;
            
            // Mark the register as in use again
            auto map_it = register_map.find(it->reg_name);
            if (map_it != register_map.end()) {
                regs_[map_it->second] = 1;
            }
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