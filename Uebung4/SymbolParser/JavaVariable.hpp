/*****************************************************************//**
 * \file   JavaVariable.hpp
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#ifndef JAVA_VARIABLE_HPP
#define JAVA_VARIABLE_HPP
#include "Object.h"
#include "Variable.hpp"

class JavaVariable :public Variable
{
public:
    virtual std::string Save() override;

    //returns string of type - SymbolParser has to check type for validity
    virtual std::string LoadTypeName(std::string const& fileLine) override;
    virtual std::string LoadVarName(std::string const& fileLine) override;

    JavaVariable() = default;

    JavaVariable(const std::string& name) : Variable{ name } {}

protected:
private:
};
#endif