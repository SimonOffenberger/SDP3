/*****************************************************************//**
 * \file   SymbolFactory.cpp
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/

# include <algorithm>
#include "SymbolParser.hpp"
#include "ISymbolFactory.hpp"

using namespace std;

void SymbolParser::SetFactory(ISymbolFactory& Factory)
{
    m_Factory = Factory;
}

void SymbolParser::AddType(std::string const& name)
{
    Type::Uptr pName = m_Factory.CreateType(name);
    m_typeCont.push_back(move(pName));
}

void SymbolParser::AddVariable(std::string const& name, std::string const& type)
{
    // look up if type even exists if yes add to type container
    Variable::Uptr pVar = m_Factory.CreateVariable(name);
    for (auto const& m_type : m_typeCont)
    {
        if (type == m_type->GetType())
        {
            pVar->SetType(m_type);
            m_variableCont.push_back(move(pVar));
        }
    }
}
