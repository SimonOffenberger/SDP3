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
    virtual std::string const& Save() override;

    //returns string of type - SymbolParser has to check type for validity
    virtual std::string const& Load(std::string const& fileLine) override;

    JavaVariable(const std::string& name) : Variable{ name } {}

protected:
private:
};
#endif