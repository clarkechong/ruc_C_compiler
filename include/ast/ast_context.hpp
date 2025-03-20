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
    
    bool InGlobalScope() const;
    
    void AddVariable(const std::string& name, TypeSpecifier type, int stack_offset);
    void AddArray(const std::string& name, TypeSpecifier type, const std::vector<int>& dimensions, int stack_offset);
    void AddPointer(const std::string& name, TypeSpecifier type, int stack_offset);
    void AddFunction(const std::string& name, TypeSpecifier return_type, const std::vector<TypeSpecifier>& param_types);
    void AddEnum(const std::string& enum_name);
    void AddEnumValue(const std::string& enum_name, const std::string& value_name, int value);
    // void AddStruct(const std::string& name, const std::map<std::string, TypeSpecifier>& members, int size);
    // void AddStructMember(struct's name, member name, member type); // depends whether you construct the struct THEN add it, or add members individually
    
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
    
    int DecrementFrameOffset(int bytes); // returns the frame pointer offset after new allocation
    int AllocateStackAndLink(TypeSpecifier type, const std::string& id, bool is_ptr = false, bool is_array = false, const std::vector<int>& array_dimensions = {});
    void InitiateFrame(std::ostream& dst);
    void TerminateFrame(std::ostream& dst);
    void StoreRegisterToVariable(std::ostream& dst, const std::string& reg, const std::string& id);
    void LoadVariableToRegister(std::ostream& dst, const std::string& reg, const std::string& id);

    void ResetFrameOffset();
    
    int GetFrameOffset() const;

private:
    Context* context_;
    
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
    std::string AllocateArgumentRegister(bool is_float = false);

    void DeallocateRegister(const std::string& reg);
    void SpillRegister(const std::string& reg, std::ostream& dst);
    void UnspillRegister(const std::string& reg, std::ostream& dst);
    void PushRegisters(std::ostream& dst); // FOR FUNCTION CALLS (ENTIRELY NEW SCOPE)
    void RestoreRegisters(std::ostream& dst); // FOR RETURNING FROM FUNCTION CALL (RETURN TO OLD SCOPE)
    void ResetRegisters();

private:
    Context* context_;
    
    int regs_[32] = {0};          // Integer registers (x0-x31)
    int regs_float_[32] = {0};    // Floating-point registers (f0-f31)
    
    const std::unordered_map<std::string, int> register_map = {
        {"zero", 0}, {"ra", 1}, {"sp", 2}, {"gp", 3}, {"tp", 4},
        {"t0", 5}, {"t1", 6}, {"t2", 7}, {"s0", 8}, {"s1", 9},
        {"a0", 10}, {"a1", 11}, {"a2", 12}, {"a3", 13}, {"a4", 14},
        {"a5", 15}, {"a6", 16}, {"a7", 17}, {"s2", 18}, {"s3", 19},
        {"s4", 20}, {"s5", 21}, {"s6", 22}, {"s7", 23}, {"s8", 24},
        {"s9", 25}, {"s10", 26}, {"s11", 27}, {"t3", 28}, {"t4", 29},
        {"t5", 30}, {"t6", 31}
    };

    const std::unordered_map<std::string, int> register_map_f = {
        {"ft0", 0}, {"ft1", 1}, {"ft2", 2}, {"ft3", 3}, {"ft4", 4},
        {"ft5", 5}, {"ft6", 6}, {"ft7", 7}, {"fs0", 8}, {"fs1", 9},
        {"fa0", 10}, {"fa1", 11}, {"fa2", 12}, {"fa3", 13}, {"fa4", 14},
        {"fa5", 15}, {"fa6", 16}, {"fa7", 17}, {"fs2", 18}, {"fs3", 19},
        {"fs4", 20}, {"fs5", 21}, {"fs6", 22}, {"fs7", 23}, {"fs8", 24},
        {"fs9", 25}, {"fs10", 26}, {"fs11", 27}, {"ft8", 28}, {"ft9", 29},
        {"ft10", 30}, {"ft11", 31}
    };
    
    struct SpilledRegister {
        std::string reg_name;
        int stack_offset;
        bool is_float;
    };
    std::vector<SpilledRegister> spilled_registers_; 
    // push to when spilling, when unspilling iterate through for stack_offset then erase
    // do not care whether float or not, just store the register name either way.
    
    struct SavedRegister {
        std::string reg_name;
        int stack_offset;
        bool is_float;
    };
    std::vector<SavedRegister> saved_registers_;
    // push to when saving registers when entering function call
    // pull from when returning from function call

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