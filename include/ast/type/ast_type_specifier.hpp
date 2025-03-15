#pragma once

#include <string_view>
#include <stdexcept>
#include <iostream>

namespace ast {

enum class TypeSpecifier
{
    VOID,
    UNSIGNED_CHAR,
    CHAR,
    UNSIGNED_SHORT,
    SHORT,
    UNSIGNED_INT,
    INT,
    UNSIGNED_LONG,
    LONG,
    FLOAT,
    DOUBLE,
    LONG_DOUBLE,
    STRUCT
};

template<typename LogStream>
LogStream& operator<<(LogStream& ls, const TypeSpecifier& type)
{
    const auto TypeToString = [&type] {
        switch (type)
        {
        case TypeSpecifier::VOID:           return "void";
        case TypeSpecifier::UNSIGNED_CHAR:  return "unsigned char";
        case TypeSpecifier::CHAR:           return "char";
        case TypeSpecifier::UNSIGNED_SHORT: return "unsigned short";
        case TypeSpecifier::SHORT:          return "short";
        case TypeSpecifier::UNSIGNED_INT:   return "unsigned int";
        case TypeSpecifier::INT:            return "int";
        case TypeSpecifier::UNSIGNED_LONG:  return "unsigned long";
        case TypeSpecifier::LONG:           return "long";
        case TypeSpecifier::FLOAT:          return "float";
        case TypeSpecifier::DOUBLE:         return "double";
        case TypeSpecifier::LONG_DOUBLE:    return "long double";
        case TypeSpecifier::STRUCT:         return "struct";
        }
        throw std::runtime_error("Unexpected type specifier");
    };
    return ls << TypeToString();
}

} // namespace ast

/*
    << operator overloaded so that printing an enum class TypeSpecifier will return the type in string format.
    e.g. std::cout << TypeSpecifier::INT; prints "int"
    note that normally, enums will implicitly convert to their enum index, whilst enum classes don't print at all.
*/