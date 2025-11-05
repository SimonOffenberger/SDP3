/*****************************************************************//**
 * \file   IECVariable.hpp
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#ifndef IEC_VARIABLE_HPP
#define IEC_VARIABLE_HPP

#include "Variable.hpp"

class IECVariable : public Variable
{
public:
    virtual std::string const& Save() override;

    //returns string of type - SymbolParser has to check type for validity
    virtual std::string const& Load(std::string const& fileLine) override;

    IECVariable(const std::string& name) : Variable{ name } {}
protected:
private:
};
#endif