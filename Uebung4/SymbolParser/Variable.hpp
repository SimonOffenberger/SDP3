/*****************************************************************//**
 * \file   Variable.hpp
 * \brief  Abstract class for parsing types
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/

#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <memory>
#include <string>

#include "Identifier.hpp"
#include "Type.hpp"

class Variable: public Identifier
{
public:
    /**
     * \brief Unique pointer type for variable
     */
    using Uptr = std::unique_ptr<Variable>;

    /**
     * \brief Returns formatted line of a variables declaration
     * 
     * \return string of variable
     */
    virtual std::string GetSaveLine() const = 0;
    
    /**
     * \brief Loads the name of a variables type
     *
     * \param string fileLine
     * \return string of type - SymbolParser has to check type for validity
     */
    virtual std::string LoadTypeName(std::string const& fileLine) const  = 0;

    /**
     * \brief Loads name of a variable
     *
     * \param string fileLine
     * \return string of variables name
     */
    virtual std::string LoadVarName(std::string const& fileLine) const = 0;

    /**
     * \brief Sets the type of a variable
     *
     * \param shared pointer of type
     * \return void
     * \throw ERROR_NULLPTR
     */
    void SetType(Type::Sptr type);
    

    /**
     * \brief Name getter
     *
     * \return string of variable
     */
    std::string GetTypeName() const;


protected:
    Variable(const std::string& name) : Identifier{ name } {}
    Variable() = default;

    Type::Sptr m_type;

private:
};
#endif