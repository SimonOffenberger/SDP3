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
    inline static const std::string ERROR_EMPTY_STRING = "ERROR: Provided string is empty.";
    inline static const std::string ERROR_NONEXISTING_TYPE = "ERROR: Provided type does not exist.";
    inline static const std::string ERROR_DUPLICATE_TYPE = "ERROR: Provided type already exists.";
    inline static const std::string ERROR_DUPLICATE_VAR = "ERROR: Provided Variable already exists.";

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
    void SetFactory(const ISymbolFactory& Factory);

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

    /**
     * \brief CTOR of a Symbol Parser Object.
     * Loads the current state form the sym files
     * \param fact
     */
    SymbolParser(const ISymbolFactory& fact);

    /**
     * \brief DTOR of Symbol Parser.
     * Saves the current state to the sym Files
     */
    virtual ~SymbolParser();

    // Delete CopyCtor and Assign Op to prevent untestet behaviour.
    SymbolParser(SymbolParser& s) = delete;
    void operator=(SymbolParser s) = delete;

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

    const ISymbolFactory * m_Factory;
};
#endif