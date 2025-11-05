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

    virtual std::string const& Save() = 0;
    
    //returns string of type - SymbolParser has to check type for validity
    virtual std::string const& Load(std::string const& fileLine) = 0;

    void SetType(Type::Sptr type) { m_type = std::move(type); }

protected:
    Variable(const std::string& name);
private:
    std::string m_name;
    Type::Sptr m_type;
};
#endif