/*****************************************************************//**
 * \file   SymbolParser.cpp
 * \brief  A multi language parser for types and variables
 * \author Simon
 * \date   Dezember 2025
 *********************************************************************/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cassert>
#include "SymbolParser.hpp"
#include "ISymbolFactory.hpp"

using namespace std;

void SymbolParser::SaveState(const std::string & type_file, const std::string & var_file)
{
    assert(m_Factory != nullptr);

    ofstream type_File;
    ofstream var_File;

    type_File.open(type_file);

    // check if file is good
    if (!type_File.good()) {
        type_File.close();
        return;
    }

    for_each(m_typeCont.cbegin(), m_typeCont.cend(), [&](const auto& type) { type_File << type->GetSaveLine(); });

    type_File.close();


    var_File.open(var_file);

    // check if file is good
    if (!var_File.good()) {
        var_File.close();
        return;
    }

    for_each(m_variableCont.cbegin(), m_variableCont.cend(), [&](const auto& var) { var_File << var->GetSaveLine(); });

    var_File.close();
}

void SymbolParser::LoadNewState(const std::string& type_file, const std::string& var_file)
{
    assert(m_Factory != nullptr);

    ifstream type_File;
    ifstream var_File;

    m_typeCont.clear();
    m_variableCont.clear();

    type_File.open(type_file);

    // check if file is good
    if (!type_File.good()) {
        type_File.close();
        return;
    }

    string line;

    // Set Name can throw an exception
    // the file must be closed !!!
    try {
        while (getline(type_File, line)) {

            Type::Uptr pType = m_Factory->CreateType("");

            assert(pType != nullptr);

            pType->SetName(pType->LoadTypeName(line));

            m_typeCont.push_back(move(pType));
        }
    }
    catch (...) {
        // file closes automatically due to RAII but here it is anyway
        type_File.close();
        throw; // rethrow
    }


    var_File.open(var_file);

    // check if file is good
    if (!var_File.good()) {
        var_File.close();
        return;
    }

    // Set Name can throw an exception
    // the file must be closed !!!
    try {
        while (getline(var_File, line)) {

            auto pVar = m_Factory->CreateVariable("");

            assert(pVar != nullptr);

            const string type = pVar->LoadTypeName(line);
            const string name = pVar->LoadVarName(line);

            pVar->SetName(name);

            // look up if type even exists if yes add to type container
            for (const auto& m_type : m_typeCont)
            {
                if (type == m_type->GetName())
                {
                    pVar->SetType(m_type);
                }
            }

            if (pVar->GetTypeName() != "") {
                m_variableCont.push_back(move(pVar));
            }
        }
    }
    catch (...) {
        // file closes automatically due to RAII but here it is anyway
        var_File.close();
        throw; // rethrow
    }

    var_File.close();
}


void SymbolParser::SetFactory(const ISymbolFactory& Factory)
{
    if (m_Factory == nullptr)
        throw SymbolParser::ERROR_NULLPTR;

    SaveState(m_Factory->GetTypeFileName(), m_Factory->GetVariableFileName());

    m_Factory = &Factory;

    LoadNewState(m_Factory->GetTypeFileName(), m_Factory->GetVariableFileName());
}

void SymbolParser::AddType(std::string const& name)
{
    if (m_Factory == nullptr)
        throw SymbolParser::ERROR_NULLPTR;

    if (name.empty())
        throw SymbolParser::ERROR_EMPTY_STRING;

    // check if type already exists
    auto it = find_if(m_typeCont.cbegin(), m_typeCont.cend(), [&](const auto& t) { return t->GetName() == name;});

    if (it != m_typeCont.cend()) {
        std::cerr << "Error type already exists !! \n";
        throw ERROR_DUPLICATE_TYPE;
    }

    Type::Uptr pType = m_Factory->CreateType(name);

    if (pType == nullptr)
        throw SymbolParser::ERROR_NULLPTR;

    m_typeCont.push_back(move(pType));

}

void SymbolParser::AddVariable(std::string const& name, std::string const& type)
{
    if (m_Factory == nullptr)
        throw SymbolParser::ERROR_NULLPTR;

    if (name.empty())
        throw SymbolParser::ERROR_EMPTY_STRING;
    
    if (type.empty())
        throw SymbolParser::ERROR_EMPTY_STRING;

    // check if variable already exists
    auto it = find_if(m_variableCont.cbegin(), m_variableCont.cend(), 
        [&](const auto& t) { return t->GetTypeName() == type && t->GetName() == name;});

    // instead of a fixed output to the console
    // an exception is thrown!!
    // but here it is anyway
    if (it != m_variableCont.cend()) {
        std::cerr << "Error Variable already exists !! \n";
        throw ERROR_DUPLICATE_VAR;
    }

    // look up if type even exists if yes add to type container
    for (const auto& m_type : m_typeCont)
    {
        if (type == m_type->GetName())
        {
            auto pVar = m_Factory->CreateVariable(name);

            if (pVar == nullptr)
                throw SymbolParser::ERROR_NULLPTR;

            pVar->SetType(m_type);

            // Move ownership into container
            m_variableCont.push_back(std::move(pVar));

            // If each variable should only match one type, return early
            return;
        }
    }

    // Error is thrown instead of a console output!
    // in our opinion this is more flexible than a
    // fixed output to the console!!
    // but here it is anyway because it is in the specification for the excersice
    std::cerr << "Error Type for Variable does not exist !! \n";

    throw ERROR_NONEXISTING_TYPE;
}

SymbolParser::SymbolParser(const ISymbolFactory& fact) : m_Factory{ &fact }
{
    // Load State from previos parsing
    LoadNewState(m_Factory->GetTypeFileName(), m_Factory->GetVariableFileName());
}

SymbolParser::~SymbolParser()
{
    // Save Previos state on destruction of Object
    SaveState(m_Factory->GetTypeFileName(), m_Factory->GetVariableFileName());
}

