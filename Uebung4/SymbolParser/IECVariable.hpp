/*****************************************************************//**
 * \file   IECVariable.hpp
 * \brief  A Class for parsing IEC variables
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/

#ifndef IEC_VARIABLE_HPP
#define IEC_VARIABLE_HPP

#include "Variable.hpp"

class IECVariable : public Variable
{
public:
    /**
     * \brief Returns formatted line of a Variable declaration
     *
     * \return string of variable
     */
    virtual std::string GetSaveLine() const override;

    /**
     * \brief Loads the name of a variables type
     *
     * \param string fileLine
     * \return string of type - SymbolParser has to check type for validity
     */
    virtual std::string LoadTypeName(std::string const& fileLine) const override;

    /**
     * \brief Loads name of a variable
     *
     * \param string fileLine
     * \return string of variables name
     */
    virtual std::string LoadVarName(std::string const& fileLine) const override;

    IECVariable() = default;

    IECVariable(const std::string& name) : Variable{ name } {}

protected:
private:
};
#endif