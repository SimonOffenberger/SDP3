/*****************************************************************//**
 * \file   Variable.hpp
 * \brief  Abstract class for parsing types
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/

#ifndef VARIABLE_HPP
#define VARIABLE_HPP
#include <memory>
#include <vector>
#include <string>

#include "Object.h"
#include "Type.hpp"

class Variable: public Object
{
public:
    /**
     * \brief Unique pointer type for variable
     */
    using Uptr = std::unique_ptr<Variable>;


    inline static const std::string ERROR_EMPTY_STRING = "ERROR: Empty String";

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
     */
    void SetType(Type::Sptr type);
    
    /**
     * \brief Retuns the name of a variable
     *
     * \return string name
     */
    std::string GetName() const;

    /**
     * \brief Name getter
     *
     * \return string of variable
     */
    std::string GetType() const;

    /**
     * \brief Sets name of variable
     *
     * \return void
     */
    void SetName(const std::string & name);

protected:
    Variable(const std::string& name) : m_name{ name } {}
    Variable() = default;
    std::string m_name;
    Type::Sptr m_type;
private:
};
#endif