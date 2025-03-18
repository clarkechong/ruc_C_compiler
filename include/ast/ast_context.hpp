#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include "type/ast_type_specifier.hpp"

class indent_t {
    public:
        indent_t(int level = 1) : level_(level) {};
    
        friend std::ostream& operator<<(std::ostream& os, const indent_t& indent) {
            for (int i = 0; i < indent.level_; ++i) {
                os << "    ";
            }
            return os;
        }

        indent_t& operator++(int) {
            ++level_;
            return *this;
        }
    
    private:
        int level_;
};

namespace ast {

struct Variable_s {
    TypeSpecifier type;
    int stack_offset;
    bool is_pointer = false;
    bool is_array = false;
    std::vector<int> array_dimensions = {};
};

struct Function_s {
    TypeSpecifier return_type;
    std::vector<TypeSpecifier> param_types;
};

struct Struct_s {
    std::map<std::string, TypeSpecifier> members;
    std::map<std::string, int> member_offsets;
    int size;
};

class Context 
{
public:
    Context();
    ~Context();

    // Register allocation and management
    std::string AllocateRegister(bool is_float = false);
    std::string ReturnRegister(bool is_float = false);
    std::string ArgRegister(int arg_num, bool is_float = false);
    void DeallocateRegister(const std::string& reg);
    void SpillRegister(const std::string& reg, std::ostream& dst);
    void UnspillRegister(const std::string& reg, std::ostream& dst);
    void PushRegisters(std::ostream& dst);
    void RestoreRegisters(std::ostream& dst);
    void ResetRegisters();
    
    // Stack and frame management
    int AllocateStackSpace(int bytes);
    void InitiateFrame(std::ostream& dst);
    void TerminateFrame(std::ostream& dst);
    int CalculateStackSize();
    void ResetFramePointer();
    void ResetStackPointer();
    
    // Scope management
    void EnterScope();
    void ExitScope(std::ostream& dst);
    
    // Symbol table operations
    void AddVariable(const std::string& name, TypeSpecifier type);
    void AddArray(const std::string& name, TypeSpecifier type, const std::vector<int>& dimensions);
    void AddPointer(const std::string& name, TypeSpecifier type);
    void AddFunction(const std::string& name, TypeSpecifier return_type, const std::vector<TypeSpecifier>& param_types);
    void AddEnum(const std::string& enum_name);
    void AddEnumValue(const std::string& enum_name, const std::string& value_name, int value);
    void AddStruct(const std::string& name, const std::map<std::string, TypeSpecifier>& members);
    
    // Symbol lookup
    int GetEnumValue(const std::string& enum_name, const std::string& value_name) const;
    Variable_s GetVariable(const std::string& name) const;
    Function_s GetFunction(const std::string& name) const;
    Struct_s GetStruct(const std::string& name) const;
    bool VariableExists(const std::string& name) const;
    bool FunctionExists(const std::string& name) const;
    bool StructExists(const std::string& name) const;
    
    // Control flow management
    std::string CreateLabel(const std::string& prefix);
    std::string GetCurrentLoopStart() const;
    std::string GetCurrentLoopEnd() const;
    std::string GetCurrentLoopUpdate() const;
    
    // String literal management
    std::string AddStringLiteral(const std::string& value);
    void EmitDataSection(std::ostream& dst) const;
    
    // Type utility functions
    static int GetSizeOfType(TypeSpecifier type);
    static std::string GetLoadInstruction(TypeSpecifier type);
    static std::string GetStoreInstruction(TypeSpecifier type);

private:
    // Register allocation
    int regs_[32] = {
        1,                                  // x0:          zero - Zero register
        1,                                  // x1:          ra - Return address
        1,                                  // x2:          sp - Stack pointer
        1,                                  // x3:          gp - Global pointer
        1,                                  // x4:          tp - Thread pointer
        0, 0, 0,                            // x5-x7:       t0-t2 - Temporaries
        1, 1,                               // x8-x9:       s0-s1 - Saved registers
        0, 0, 0, 0, 0, 0, 0, 0,             // x10-x17:     a0-a7 - Function arguments
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,       // x18-x27:     s2-s11 - Saved registers
        0, 0, 0, 0                          // x28-x31:     t3-t6 - Temporaries
    };

    // Floating-point register allocation
    int regs_float_[32] = {
        0, 0,                               // f0-f1:       ft0-ft1 - Temporaries
        0, 0, 0, 0, 0, 0,                   // f2-f7:       ft2-ft7 - Temporaries
        1, 1,                               // f8-f9:       fs0-fs1 - Saved registers
        0, 0,                               // f10-f11:     fa0-fa1 - Function args/return
        0, 0, 0, 0, 0, 0,                   // f12-f17:     fa2-fa7 - Function arguments
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,       // f18-f27:     fs2-fs11 - Saved registers
        0, 0, 0, 0                          // f28-f31:     ft8-ft11 - Temporaries
    };

    // Label generation
    int label_counter_ = 0;

    // Memory management
    int stack_offset_ = 0;
    int frame_pointer_offset_ = 0;
    int default_stack_size_ = 128;
    int min_alignment_ = 4;

    // Symbol tables
    std::vector<std::unordered_map<std::string, Variable_s>> variable_scopes_;
    std::unordered_map<std::string, Function_s> function_table_;
    std::map<std::string, std::map<std::string, int>> enum_table_;
    std::map<std::string, Struct_s> struct_table_;

    // Control flow state
    std::vector<std::string> loop_start_labels_;
    std::vector<std::string> loop_end_labels_;
    std::vector<std::string> loop_update_labels_;

    // String literals
    std::vector<std::pair<std::string, std::string>> string_literals_;
};

} // namespace ast