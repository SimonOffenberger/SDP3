/*****************************************************************//**
 * \file   SymbolParser.cpp
 * \brief  A multi language parser for types and variables
 * \author Simon
 * \date   Dezember 2025
 *********************************************************************/


#include <algorithm>
#include <fstream>
#include <iostream>
#include "SymbolParser.hpp"
#include "ISymbolFactory.hpp"

using namespace std;

void SymbolParser::SaveState(const std::string & type_file, const std::string & var_file)
{
    ofstream type_File;
    ofstream var_File;

    type_File.open(m_Factory.GetTypeFileName());

    for_each(m_typeCont.cbegin(), m_typeCont.cend(), [&](const auto& type) { type_File << type->GetSaveLine(); });

    type_File.close();


    var_File.open(m_Factory.GetVariableFileName());

    for_each(m_variableCont.cbegin(), m_variableCont.cend(), [&](const auto& var) { var_File << var->GetSaveLine(); });

    var_File.close();
}

void SymbolParser::LoadNewState(const std::string& type_file, const std::string& var_file)
{
    ifstream type_File;
    ifstream var_File;

    m_typeCont.clear();
    m_variableCont.clear();

    type_File.open(m_Factory.GetTypeFileName());

    string line;

    while (getline(type_File, line)) {

        Type::Uptr pType = m_Factory.CreateType("");

        pType->SetType(pType->LoadTypeName(line));

        m_typeCont.push_back(move(pType));
    }

    type_File.close();


    var_File.open(m_Factory.GetVariableFileName());

    while (getline(var_File, line)) {

        auto pVar = m_Factory.CreateVariable("");

        const string type = pVar->LoadTypeName(line);
        const string name = pVar->LoadVarName(line);

        pVar->SetName(name);

        // look up if type even exists if yes add to type container
        for (const auto& m_type : m_typeCont)
        {
            if (type == m_type->GetType())
            {

                pVar->SetType(m_type);

                // If each variable should only match one type, break early
                break;
            }
        }

        if (pVar->GetType() != "") {
            m_variableCont.push_back(move(pVar));
        }
    }

    var_File.close();
}


void SymbolParser::SetFactory(ISymbolFactory& Factory)
{

    SaveState(m_Factory.GetTypeFileName(), m_Factory.GetVariableFileName());

    m_Factory = Factory;

    LoadNewState(m_Factory.GetTypeFileName(), m_Factory.GetVariableFileName());
}

void SymbolParser::AddType(std::string const& name)
{
    if (name.empty())
        throw SymbolParser::ERROR_EMPTY_STRING;

    Type::Uptr pType = m_Factory.CreateType(name);
    m_typeCont.push_back(move(pType));
}

void SymbolParser::AddVariable(std::string const& name, std::string const& type)
{
    if (name.empty())
        throw SymbolParser::ERROR_EMPTY_STRING;
    
    if (type.empty())
        throw SymbolParser::ERROR_EMPTY_STRING;

    // look up if type even exists if yes add to type container
    for (const auto& m_type : m_typeCont)
    {
        if (type == m_type->GetType())
        {
            auto pVar = m_Factory.CreateVariable(name);
            pVar->SetType(m_type);

            // Move ownership into container
            m_variableCont.push_back(std::move(pVar));

            // If each variable should only match one type, return early
            return;
        }
    }

    throw ERROR_NONEXISTING_TYPE;
}

