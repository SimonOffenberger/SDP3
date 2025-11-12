/*****************************************************************//**
 * \file   SymbolParser.hpp
 * \brief  A multi language parser for types and variables
 * \author Simon
 * \date   Dezember 2025
 *********************************************************************/

#ifndef SYMBOL_PARSER_HPP
#define SYMBOL_PARSER_HPP

#include <vector>

#include "Object.h"
#include "Variable.hpp"
#include "Type.hpp"
#include "ISymbolFactory.hpp"

class SymbolParser : public Object
{
public:
    /**
     * \brief Polymorphic conatiner for saving variables
     */
    using TVariableCont = std::vector<Variable::Uptr>;
    
    /**
     * \brief Polymorphic conatiner for saving types
     */
    using TTypeCont = std::vector<Type::Sptr>;
    
    /**
     * \brief Sets Factory for parsing a language
     * \brief Previus variables and types of prior factory get saved, 
     * \brief then the subsequent factories variables and types get loaded.
     * \param Reference to a SymbolFactory
     * \return void
     */
    void SetFactory(ISymbolFactory& Factory);

    /**
     * \brief Adds a new type to the language
     * \param string of typename
     * \return void
     */
    void AddType(std::string const& name);
    
    /**
     * \brief Adds a new variable if type exists
     * \param string of variable, string of type
     * \return void
     */
    void AddVariable(std::string const& name, std::string const& type);

    SymbolParser(ISymbolFactory & fact) : m_Factory{fact} {}

protected:
private:
    /**
     * \brief Saves the current state of a SymbolFacotry to its file
     * \param string of type files path, tring of variable files path
     * \return void
     */
    void SaveState(const std::string& type_file, const std::string& var_file);

    /**
     * \brief Loads a SymbolFactory's variables and types from file
     * \param string of type files path, tring of variable files path
     * \return void
     */
    void LoadNewState(const std::string& type_file, const std::string& var_file);

    TTypeCont m_typeCont;
    TVariableCont m_variableCont;
    ISymbolFactory & m_Factory;
};
#endif