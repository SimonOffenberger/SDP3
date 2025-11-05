/*****************************************************************//**
 * \file   SymbolParser
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#ifndef SYMBOL_PARSER_HPP
#define SYMBOL_PARSER_HPP

#include <vector>

#include "Object.h"
#include "Variable.hpp"
#include "Type.hpp"
#include "ISymbolFactory.hpp"
#include "iterator"

class SymbolParser : public Object
{
public:
    using TVariableCont = std::vector<Variable::Uptr>;
    using TTypeCont = std::vector<Type::Uptr>;
    
    void SetFactory(ISymbolFactory& Factory);
    void AddType(std::string const& name);
    void AddVariable(std::string const& name, std::string const& type);
protected:
private:
    TTypeCont m_typeCont;
    TVariableCont m_variableCont;
    ISymbolFactory &Factory;
};
#endif