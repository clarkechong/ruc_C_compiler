#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <stack>
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
        
        int GetLevel() const {
            return level_;
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

class Context;

class ScopeManager 
{
public:
    ScopeManager(Context* context);
    ~ScopeManager();
    
    void EnterNewScope();
    void ExitScope(std::ostream& dst);
    
    void AddVariable(const std::string& name, TypeSpecifier type, int stack_offset);
    void AddArray(const std::string& name, TypeSpecifier type, const std::vector<int>& dimensions, int stack_offset);
    void AddPointer(const std::string& name, TypeSpecifier type, int stack_offset);
    void AddFunction(const std::string& name, TypeSpecifier return_type, const std::vector<TypeSpecifier>& param_types);
    void AddEnum(const std::string& enum_name);
    void AddEnumValue(const std::string& enum_name, const std::string& value_name, int value);
    void AddStruct(const std::string& name, const std::map<std::string, TypeSpecifier>& members, int size);
    
    int GetEnumValue(const std::string& enum_name, const std::string& value_name) const;
    Variable_s GetVariable(const std::string& name) const;
    Function_s GetFunction(const std::string& name) const;
    
    bool VariableExists(const std::string& name) const;
    bool FunctionExists(const std::string& name) const;
    bool StructExists(const std::string& name) const;

private:
    Context* context_;
    
    std::vector<std::unordered_map<std::string, Variable_s>> variable_scopes_;
    std::vector<std::unordered_map<std::string, std::map<std::string, Variable_s>>> struct_table_;

    std::unordered_map<std::string, Function_s> function_table_;
    std::unordered_map<std::string, std::map<std::string, int>> enum_table_;
};

class StackManager 
{
public:
    StackManager(Context* context);
    ~StackManager();
    
    int AllocateStackSpace(int bytes);
    void InitiateFrame(std::ostream& dst);
    void TerminateFrame(std::ostream& dst);

    void ResetFramePointer();
    void ResetStackPointer();
    
    int GetStackOffset() const { return stack_offset_; }
    int GetMinAlignment() const { return min_alignment_; }

private:
    Context* context_;
    
    int stack_offset_ = 0;
    int frame_pointer_offset_ = 0;
    int default_stack_size_ = 512;
    int min_alignment_ = 4;
};

class LabelManager 
{
public:
    LabelManager(Context* context);
    ~LabelManager();
    
    std::string CreateLabel(const std::string& prefix);
    
    // current function tracking
    void PushFunctionContext(const std::string& func_name);
    void PopFunctionContext();
    std::string GetCurrentFunction() const;
    std::string GetCurrentFunctionEndLabel() const;
    
    // loop label management
    std::string GetCurrentLoopStart() const;
    std::string GetCurrentLoopEnd() const;
    std::string GetCurrentLoopUpdate() const;
    void PushLoopStart(const std::string& label);
    void PushLoopEnd(const std::string& label);
    void PushLoopUpdate(const std::string& label);
    void PopLoopStart();
    void PopLoopEnd();
    void PopLoopUpdate();
    
    // string literal management
    std::string AddStringLiteral(const std::string& value);
    void EmitDataSection(std::ostream& dst) const;

private:
    Context* context_;
    
    int label_counter_ = 0;
    
    // track current function context for returns
    std::stack<std::string> function_stack_;
    std::stack<std::string> function_end_labels_;
    
    // loop label stacks
    std::vector<std::string> loop_start_labels_;
    std::vector<std::string> loop_end_labels_;
    std::vector<std::string> loop_update_labels_;
    
    // string literals for .data section
    std::vector<std::pair<std::string, std::string>> string_literals_;
};

class RegisterManager 
{
public:
    RegisterManager(Context* context);
    ~RegisterManager();
    
    std::string AllocateRegister(bool is_float = false);
    std::string AllocateReturnRegister(bool is_float = false);
    std::string AllocateArgumentRegister(int arg_num, bool is_float = false);

    void DeallocateRegister(const std::string& reg);
    void SpillRegister(const std::string& reg, std::ostream& dst);
    void UnspillRegister(const std::string& reg, std::ostream& dst);
    void PushRegisters(std::ostream& dst);
    void RestoreRegisters(std::ostream& dst);
    void ResetRegisters();

private:
    Context* context_;
    
    int regs_[32] = {0};          // Integer registers (x0-x31)
    int regs_float_[32] = {0};    // Floating-point registers (f0-f31)
    
    struct SpilledRegister {
        std::string reg_name;
        int stack_offset;
        bool is_float;
    };
    std::vector<SpilledRegister> spilled_registers_;
    
    struct SavedRegister {
        std::string reg_name;
        int stack_offset;
        bool is_float;
    };
    std::vector<SavedRegister> saved_registers_;
};

class Context 
{
public:
    Context();
    ~Context();
    
    static int GetSizeOfType(TypeSpecifier type);
    static std::string GetLoadInstruction(TypeSpecifier type);
    static std::string GetStoreInstruction(TypeSpecifier type);

    ScopeManager        scope_manager;
    StackManager        stack_manager;
    LabelManager        label_manager;
    RegisterManager     register_manager;
};

}