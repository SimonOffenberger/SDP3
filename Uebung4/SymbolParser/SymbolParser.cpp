#include "SymbolParser.hpp"
/*****************************************************************//**
 * \file   SymbolFactory.cpp
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/

# include <algorithm>
#include "ISymbolFactory.hpp"

using namespace std;

void SymbolParser::SetFactory(ISymbolFactory& Factory)
{
    m_Factory = Factory;
}

void SymbolParser::AddType(std::string const& name)
{
    Type::Uptr pName = m_Factory.CreateType(name);
    m_typeCont.emplace_back(pName);
}

void SymbolParser::AddVariable(std::string const& name, std::string const& type)
{
    // look up if type even exists if yes add to type container
    Variable::Uptr pVar = m_Factory.CreateVariable(name);
    for (auto const& type : m_typeCont)
    {
        if (pVar->GetType() == type->GetType())
        {
            m_variableCont.emplace_back(pVar);
        }
    }
}
