/*****************************************************************//**
 * \file   Variable.hpp
 * \brief
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#ifndef VARIABLE_HPP
#define VARIABLE_HPP
#include <memory>
#include <vector>
#include <string>

#include "Object.h"
#include "Type.hpp"

class Variable: public Object
{
public:
    using Uptr = std::unique_ptr<Variable>;

    inline static const std::string ERROR_EMPTY_STRING = "ERROR: Empty String";

    virtual std::string GetSaveLine() = 0;
    
    //returns string of type - SymbolParser has to check type for validity
    virtual std::string LoadTypeName(std::string const& fileLine) = 0;
    virtual std::string LoadVarName(std::string const& fileLine) = 0;

    void SetType(Type::Sptr type) { m_type = std::move(type); }
    
    std::string GetName() const;

    std::string GetType() const;

    void SetName(const std::string & name);

protected:
    Variable(const std::string& name) : m_name{ name } {}
    Variable() = default;
    std::string m_name;
    Type::Sptr m_type;
private:
};
#endif